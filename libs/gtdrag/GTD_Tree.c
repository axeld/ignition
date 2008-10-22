/*
 * Copyright ©1999-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the MIT License.
 */

//!	Tree managing functions.


#include "gtdrag_includes.h"


#define NewList(l) NewList((struct List *)(l))
#define RemHead(l) RemHead((struct List *)(l))
#define AddTail(l,n) AddTail((struct List *)(l),(struct Node *)(n))
#define AddHead(l,n) AddHead((struct List *)(l),(struct Node *)(n))
#define FindName(l,s) (APTR)FindName((struct List *)(l),(s))


/** @short adds a TreeNode to a list
 *
 *  This function simplifies adding a new TreeNode to a tree list.
 *  You could also do this without the use of this function; there
 *  is no magic to add an item to a list.
 *  If TNF_SORT is set in the flags field, the TreeNode will be
 *  inserted in the list, sorted by name.\n
 *
 *  The name and the image pointer must be valid while the the tree
 *  is displayed; they are simply referenced not copied.\n
 *
 *  After the tree list is completed, you have to call InitTreeList()
 *  to create a view list out of it.
 *
 *  @param pool a pointer to the memory pool
 *  @param tree the tree list (e.g. tl_Tree of a TreeList)
 *  @param name the name of the TreeNode; this should always be defined,
 *         although it is not checked here
 *  @param image a pointer to an image, maybe NULL
 *  @param flags one of the TNF_xxx flags
 *
 *  @return treenode the TreeNode or NULL for failure
 *
 *  @see InitTreeList()
 *  @see FreeTreeNodes()
 */

struct TreeNode * PUBLIC AddTreeNode(reg (a0) APTR pool,reg (a1) struct MinList *tree,reg (a2) STRPTR name,reg (a3) struct Image *im,reg (d0) UWORD flags)
{
  struct TreeNode *tn;

  if (tn = AllocPooled(pool,sizeof(struct TreeNode)))
  {
    NewList(&tn->tn_Nodes);
    tn->tn_Node.in_Name = name;
    tn->tn_Node.in_Image = im;
    tn->tn_Flags = flags;
    if (flags & TNF_SORT)
    {
      struct TreeNode *stn;

      foreach(tree,stn)
        if (strcmp(stn->tn_Node.in_Name,name) > 0)
          break;
      Insert((struct List *)tree,(struct Node *)tn,(struct Node *)stn->tn_Node.in_Pred);
    }
    else
      AddTail(tree,tn);
  }
  return(tn);
}

/** @short frees the tree nodes
 *
 *  This function deletes the whole tree and its sub-trees recursively.
 *  Corresponding to AddTreeNode(), the name and the image are
 *  not freed.
 *
 *  @param pool the pointer to the memory pool the tree was allocated in
 *  @param list the tree list
 *
 *  @see AddTreeNode()
 */

void PUBLIC FreeTreeNodes(reg (a0) APTR pool,reg (a1) struct MinList *list)
{
  struct TreeNode *tn;

  while(tn = (APTR)RemHead(list))
  {
    if (tn->tn_Flags & TNF_CONTAINER)
      FreeTreeNodes(pool,&tn->tn_Nodes);

    FreePooled(pool,tn,sizeof(struct TreeNode));
  }
}

/** @short frees the TreeList contents
 *
 *  This function makes use of the FreeTreeNodes() function but
 *  in addition to this, it resets the view list.
 *
 *  @param the pointer to the memory pool
 *  @param the TreeList with view and tree list
 *
 *  @see FreeTreeNodes()
 */

void PUBLIC FreeTreeList(reg (a0) APTR pool,reg (a1) struct TreeList *tl)
{
  NewList(&tl->tl_View);
  FreeTreeNodes(pool,&tl->tl_Tree);
}

/** @short closes an open TreeNode
 *
 *  This function automatically removes all contents of a TreeNode
 *  and its sub-trees recursively.\n
 *
 *  It does not affect the TNF_OPEN flag of a TreeNode!
 *
 *  @param main the view list
 *  @param tn the TreeNode to be closed
 *
 *  @see OpenTreeNode()
 *  @see ToggleTreeNode()
 */

void PUBLIC CloseTreeNode(reg (a0) struct MinList *main,reg (a1) struct TreeNode *tn)
{
  struct TreeNode *itn;

  if (!main || !tn)
    return;

  foreach(&tn->tn_Nodes,itn)
  {
    if (itn->tn_ViewNode.mln_Succ)
    {
      Remove((struct Node *)&itn->tn_ViewNode);
      itn->tn_ViewNode.mln_Succ = NULL;
    }
    if ((itn->tn_Flags & (TNF_CONTAINER | TNF_OPEN)) == (TNF_CONTAINER | TNF_OPEN))
      CloseTreeNode(main,itn);
  }
}

/** @short opens a closed TreeNode
 *
 *  This function adds all contents of the TreeNode and its open
 *  sub-trees to the view list.\n
 *
 *  It does not affect the TNF_OPEN flag of the TreeNode!
 *
 *  @param main the view list
 *  @param tn the TreeNode to be opened
 *  @return count the number of TreeNodes added to the view list
 *
 *  @see CloseTreeNode()
 *  @see ToggleTreeNode()
 */

LONG PUBLIC OpenTreeNode(reg (a0) struct MinList *main,reg (a1) struct TreeNode *tn)
{
  struct MinNode *insertln;
  struct TreeNode *itn;
  long   count = 0;

  if (!main || !tn)
    return(0);

  insertln = &tn->tn_ViewNode;

  foreach(&tn->tn_Nodes,itn)
  {
    Insert((struct List *)main,(struct Node *)&itn->tn_ViewNode,(struct Node *)insertln);
    count++;

    insertln = itn->tn_ViewNode.mln_Succ;
    if ((itn->tn_Flags & (TNF_CONTAINER | TNF_OPEN)) == (TNF_CONTAINER | TNF_OPEN))
      count += OpenTreeNode(main,itn);
    insertln = insertln->mln_Pred;
  }
  return count;
}

/** @short toggles a TreeNode between closes/open
 *
 *  This function adds all contents of a closed TreeNode and its
 *  open sub-trees to the view list, or it removes the open TreeNode
 *  and its open sub-trees from the view list.
 *  It also takes care of the TNF_OPEN flag of the TreeNode.
 *
 *  @param main the view list
 *  @param tn the TreeNode to be opened
 *  @return count the number of TreeNodes added to the view list
 *
 *  @see CloseTreeNode()
 *  @see OpenTreeNode()
 */

LONG PUBLIC ToggleTreeNode(reg (a0) struct MinList *main,reg (a1) struct TreeNode *tn)
{
  if (!main || !tn)
    return(0);

  if (tn->tn_Flags & TNF_CONTAINER)
  {
    if (tn->tn_Flags & TNF_OPEN)
    {
      tn->tn_Flags &= ~TNF_OPEN;
      CloseTreeNode(main,tn);
      return(0);
    }
    tn->tn_Flags |= TNF_OPEN;
    return(OpenTreeNode(main,tn));
  }
  if (tn->tn_Flags & TNF_ADD)
    tn->tn_Flags = (tn->tn_Flags & ~TNF_ADD) | TNF_REPLACE;
  else if (tn->tn_Flags & TNF_REPLACE)
    tn->tn_Flags = (tn->tn_Flags & ~TNF_REPLACE) | TNF_ADD;

  return(0);
}


void PRIVATE FillTreeList(struct MinList *main,struct MinList *list,UBYTE depth,UBYTE flags,ULONG lines)
{
  struct TreeNode *tn;

  foreach(list,tn)
  {
    if (flags & TNF_OPEN)
      AddTail(main,&tn->tn_ViewNode);
    else
      tn->tn_ViewNode.mln_Succ = NULL;

    tn->tn_Depth = depth;
    tn->tn_DepthLines = lines;
    tn->tn_X = -1;
    if (!IsListEmpty((struct List *)&tn->tn_Nodes))
    {
      tn->tn_Flags |= TNF_CONTAINER;

      FillTreeList(main,&tn->tn_Nodes,depth+1,flags & TNF_OPEN ? tn->tn_Flags : tn->tn_Flags & ~TNF_OPEN,lines | (tn->tn_Node.in_Succ->in_Succ ? (1L << depth) : 0));
    }
    if (!tn->tn_Node.in_Succ->in_Succ)
      tn->tn_Flags |= TNF_LAST;
    else
      tn->tn_Flags &= ~TNF_LAST;
  }
}

/** @short inits a tree list contents for viewing
 *
 *  After the whole tree is built, this function inits the view
 *  list; the treeview callback hook can now display the tree.\n
 *
 *  This is not a trivial thing to do, the usage of this function
 *  is recommended.
 *
 *  @param tl a pointer to the TreeList
 */

void PUBLIC InitTreeList(reg (a0) struct TreeList *tl)
{
  NewList(&tl->tl_View);
  FillTreeList(&tl->tl_View,&tl->tl_Tree,0,TNF_OPEN,0);
}

/** @short gets the container of a TreeNode
 *
 *  This function searches for the container of a TreeNode; if the
 *  TreeNode is a root node, it returns NULL.
 *
 *  @param tn the TreeNode, may be NULL
 *  @return container the container TreeNode or NULL
 */

struct TreeNode * PUBLIC GetTreeContainer(reg (a0) struct TreeNode *tn)
{
  if (!tn || !tn->tn_Depth)
    return(NULL);

  for(;tn->tn_Node.in_Pred;tn = (APTR)tn->tn_Node.in_Pred);
  return((struct TreeNode *)((UBYTE *)tn - sizeof(struct MinNode) - sizeof(struct ImageNode)));
}

/** @short finds the path of a TreeNode
 *
 *  You can use this function to copy the TreeNode's path (without
 *  its name) to the provided buffer.
 *
 *  @param tn the TreeNode
 *  @param buffer a buffer large enough to hold the path
 *  @param len the length of the buffer
 *
 *  @return path returns the buffer or NULL for failure
 */

STRPTR PUBLIC GetTreePath(reg (a0) struct TreeNode *tn,reg (a1) STRPTR buffer,reg (d0) LONG len)
{
  long pos = 0;

  if (!tn || !buffer || !len)
    return(NULL);

  *buffer = 0;
  while(tn = GetTreeContainer(tn))
  {
    pos += strlen(tn->tn_Node.in_Name)+1;
    if (len <= pos)
      break;

    strins(buffer,"/");
    strins(buffer,tn->tn_Node.in_Name);
  }
  return(buffer);
}

/** @short finds a TreeNode with a path
 *
 *  If you have the whole path of a TreeNode, this function
 *  finds the pointer to the TreeNode for you.
 *
 *  @param tree the tree list
 *  @param path a path to the TreeNode, may be NULL
 *  @return treenode the TreeNode, if found any, or NULL
 */

struct TreeNode * PUBLIC FindTreePath(reg (a0) struct MinList *tree,reg (a1) STRPTR path)
{
  struct TreeNode *tn;
  long   i;

  if (!tree || !path)
    return(NULL);

  for(i = 0;*(path+i) && *(path+i) != '/';i++);
  if (!i)
    return(NULL);

  foreach(tree,tn)
  {
    if (!strnicmp(path,tn->tn_Node.in_Name,i))
    {
      if (*(path+i))
        return(FindTreePath(&tn->tn_Nodes,path+i+1));

      return(tn);
    }
  }
}

/** @short searches a tree for a special pointer
 *
 *  A TreeNode contains a special pointer like the UserData of a
 *  gadget or whatever.
 *  This function searches for the TreeNode with this special
 *  pointer, even NULL is accepted.
 *
 *  @param tree the tree list
 *  @param special the special pointer
 *  @return treenode the TreeNode found, or NULL, if there aren't any
 *
 *  @see FindListSpecial()
 */

struct TreeNode * PUBLIC FindTreeSpecial(reg (a0) struct MinList *tree,reg (a1) APTR special)
{
  struct TreeNode *tn;

  if (!tree)
    return(NULL);

  foreach(tree,tn)
  {
    if (special == tn->tn_Special)
      return(tn);
    if (tn->tn_Flags & TNF_CONTAINER)
    {
      struct TreeNode *ftn;

      if (ftn = FindTreeSpecial(&tn->tn_Nodes,special))
        return(ftn);
    }
  }
  return(NULL);
}

/** @short searches a list for the special pointer
 *
 *  This function is similar to FindTreeSpecial() but it does no
 *  recursive search. It simply scans the provided list for a
 *  TreeNode with this special pointer.
 *
 *  @param list the list to be scanned
 *  @param special the special pointer
 *  @return treenode the TreeNode found, or NULL, if there aren't any
 *
 *  @see FindTreeSpecial()
 */

struct TreeNode * PUBLIC FindListSpecial(reg (a0) struct MinList *list,reg (a1) APTR special)
{
  struct TreeNode *tn;

  if (!list)
    return(NULL);

  foreach(list,tn)
  {
    if (special == tn->tn_Special)
      return(tn);
  }
  return(NULL);
}

/** @short simplifies the usage of ToggleTreeNode()
 *
 *  You can use this function instead of ToggleTreeNode() if the user
 *  clicks on a TreeNode in your listview gadget.
 *  It automatically updates the gadget and takes care of changements
 *  to the position of the list due to additional nodes.
 *  The gadget must be registered via GTD_AddGadget() if it should do
 *  anything.
 *
 *  @param gad a pointer to a registered gadget
 *  @param tn the TreeNode the user clicked on
 *  @param msg a pointer to the IntuiMessage which reports the click
 *  @return toggled returns TRUE if it really toggled the TreeNode
 *
 *  @bugs In release 3.1 this function did perfectly nothing [if everything
 *    worked fine with GT_GetGadgetAttrs()].
 *
 *  @see GTD_AddGadget()
 *  @see GTD_ToggleTreeNode()
 */

BOOL PUBLIC ToggleTree(reg (a0) struct Gadget *gad,reg (a1) struct TreeNode *tn,reg (a2) struct IntuiMessage *msg)
{
  struct DragGadget *dg;
  struct List *list;
  long   top,h;

  if (!gad || !tn || !msg || !(dg = FindDragGadget(gad)))
	return FALSE;

  if (GT_GetGadgetAttrs(gad,dg->dg_Window,NULL,GTLV_Labels,&list,GTLV_Top,&top,TAG_END) < 2)
	return FALSE;

  h = gad->TopEdge+2+(msg->Code-top)*dg->dg_ItemHeight;

  if (MouseOverTreeKnob(tn,h,msg))
  {
    struct Window *win = dg->dg_Window;
    long in,height = (gad->Height-4)/dg->dg_ItemHeight;

    GT_SetGadgetAttrs(gad,win,NULL,GTLV_Labels,~0L,TAG_END);

    if ((in = ToggleTreeNode(list,tn)) && msg->Code+1+in > top+height)
      top += msg->Code+in+1-top-height;

    GT_SetGadgetAttrs(gad,win,NULL,GTLV_Labels,list,GTLV_Top,top,TAG_END);
	return TRUE;
  }
  return FALSE;
}
