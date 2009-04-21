/*
    *** Automatically generated from '/home/mazze/projects/AROS/local/ignition/libs/gtdrag/gtdrag.conf'. Edits will be lost. ***
    Copyright © 1995-2009, The AROS Development Team. All rights reserved.
*/
#define NOLIBDEFINES
/* Be sure that the libbases are included in the stubs file */
#undef __NOLIBBASE__
#undef __GTDRAG_NOLIBBASE__
#include <proto/gtdrag.h>
#include <exec/types.h>
#include <aros/libcall.h>


struct IntuiMessage * GTD_GetIMsg(struct MsgPort *mp)
{
    return AROS_LC1(struct IntuiMessage *, GTD_GetIMsg,
                    AROS_LCA(struct MsgPort *,mp,A0),
                    struct Library *, GTDragBase, 5, Gtdrag);
}

void GTD_ReplyIMsg(struct IntuiMessage *msg)
{
    return AROS_LC1NR(void, GTD_ReplyIMsg,
                    AROS_LCA(struct IntuiMessage *,msg,A0),
                    struct Library *, GTDragBase, 6, Gtdrag);
}

struct IntuiMessage * GTD_FilterIMsg(struct IntuiMessage *msg)
{
    return AROS_LC1(struct IntuiMessage *, GTD_FilterIMsg,
                    AROS_LCA(struct IntuiMessage *,msg,A0),
                    struct Library *, GTDragBase, 7, Gtdrag);
}

struct IntuiMessage * GTD_PostFilterIMsg(struct IntuiMessage *msg)
{
    return AROS_LC1(struct IntuiMessage *, GTD_PostFilterIMsg,
                    AROS_LCA(struct IntuiMessage *,msg,A0),
                    struct Library *, GTDragBase, 8, Gtdrag);
}

int GTD_AddAppA(STRPTR t, struct TagItem *tag)
{
    return AROS_LC2(int, GTD_AddAppA,
                    AROS_LCA(STRPTR,t,A0),
                    AROS_LCA(struct TagItem *,tag,A1),
                    struct Library *, GTDragBase, 11, Gtdrag);
}

void GTD_RemoveApp()
{
    return AROS_LC0NR(void, GTD_RemoveApp,
                    struct Library *, GTDragBase, 12, Gtdrag);
}

void GTD_AddWindowA(struct Window *win, struct TagItem *tag)
{
    return AROS_LC2NR(void, GTD_AddWindowA,
                    AROS_LCA(struct Window *,win,A0),
                    AROS_LCA(struct TagItem *,tag,A1),
                    struct Library *, GTDragBase, 13, Gtdrag);
}

void GTD_RemoveWindow(struct Window *win)
{
    return AROS_LC1NR(void, GTD_RemoveWindow,
                    AROS_LCA(struct Window *,win,A0),
                    struct Library *, GTDragBase, 14, Gtdrag);
}

void GTD_AddGadgetA(ULONG type, struct Gadget *gad, struct Window *win, struct TagItem *tag)
{
    return AROS_LC4NR(void, GTD_AddGadgetA,
                    AROS_LCA(ULONG,type,D0),
                    AROS_LCA(struct Gadget *,gad,A0),
                    AROS_LCA(struct Window *,win,A1),
                    AROS_LCA(struct TagItem *,tag,A2),
                    struct Library *, GTDragBase, 15, Gtdrag);
}

void GTD_RemoveGadget(struct Gadget *gad)
{
    return AROS_LC1NR(void, GTD_RemoveGadget,
                    AROS_LCA(struct Gadget *,gad,A0),
                    struct Library *, GTDragBase, 16, Gtdrag);
}

void GTD_RemoveGadgets(struct Window *win)
{
    return AROS_LC1NR(void, GTD_RemoveGadgets,
                    AROS_LCA(struct Window *,win,A0),
                    struct Library *, GTDragBase, 17, Gtdrag);
}

void GTD_SetAttrsA(APTR gad, struct TagItem *tags)
{
    return AROS_LC2NR(void, GTD_SetAttrsA,
                    AROS_LCA(APTR,gad,A0),
                    AROS_LCA(struct TagItem *,tags,A1),
                    struct Library *, GTDragBase, 18, Gtdrag);
}

BOOL GTD_GetAttr(APTR gad, ULONG tag, ULONG *storage)
{
    return AROS_LC3(BOOL, GTD_GetAttr,
                    AROS_LCA(APTR,gad,A0),
                    AROS_LCA(ULONG,tag,D0),
                    AROS_LCA(ULONG *,storage,A1),
                    struct Library *, GTDragBase, 19, Gtdrag);
}

struct Hook * GTD_GetHook(ULONG type)
{
    return AROS_LC1(struct Hook *, GTD_GetHook,
                    AROS_LCA(ULONG,type,D0),
                    struct Library *, GTDragBase, 20, Gtdrag);
}

STRPTR GTD_GetString(struct ObjectDescription *od, STRPTR buf, LONG len)
{
    return AROS_LC3(STRPTR, GTD_GetString,
                    AROS_LCA(struct ObjectDescription *,od,A0),
                    AROS_LCA(STRPTR,buf,D1),
                    AROS_LCA(LONG,len,D0),
                    struct Library *, GTDragBase, 21, Gtdrag);
}

BOOL GTD_PrepareDrag(struct Gadget *gad, struct gpInput *gpi)
{
    return AROS_LC2(BOOL, GTD_PrepareDrag,
                    AROS_LCA(struct Gadget *,gad,A0),
                    AROS_LCA(struct gpInput *,gpi,A1),
                    struct Library *, GTDragBase, 22, Gtdrag);
}

BOOL GTD_BeginDrag(struct Gadget *gad, struct gpInput *gpi)
{
    return AROS_LC2(BOOL, GTD_BeginDrag,
                    AROS_LCA(struct Gadget *,gad,A0),
                    AROS_LCA(struct gpInput *,gpi,A1),
                    struct Library *, GTDragBase, 23, Gtdrag);
}

ULONG GTD_HandleInput(struct Gadget *gad, struct gpInput *gpi)
{
    return AROS_LC2(ULONG, GTD_HandleInput,
                    AROS_LCA(struct Gadget *,gad,A0),
                    AROS_LCA(struct gpInput *,gpi,A1),
                    struct Library *, GTDragBase, 24, Gtdrag);
}

void GTD_StopDrag(struct Gadget *gad)
{
    return AROS_LC1NR(void, GTD_StopDrag,
                    AROS_LCA(struct Gadget *,gad,A0),
                    struct Library *, GTDragBase, 25, Gtdrag);
}

void FreeTreeList(APTR pool, struct TreeList *tl)
{
    return AROS_LC2NR(void, FreeTreeList,
                    AROS_LCA(APTR,pool,A0),
                    AROS_LCA(struct TreeList *,tl,A1),
                    struct Library *, GTDragBase, 26, Gtdrag);
}

void InitTreeList(struct TreeList *tl)
{
    return AROS_LC1NR(void, InitTreeList,
                    AROS_LCA(struct TreeList *,tl,A0),
                    struct Library *, GTDragBase, 27, Gtdrag);
}

void FreeTreeNodes(APTR pool, struct MinList *list)
{
    return AROS_LC2NR(void, FreeTreeNodes,
                    AROS_LCA(APTR,pool,A0),
                    AROS_LCA(struct MinList *,list,A1),
                    struct Library *, GTDragBase, 28, Gtdrag);
}

struct TreeNode * AddTreeNode(APTR pool, struct MinList *tree, STRPTR name, struct Image *im, UWORD flags)
{
    return AROS_LC5(struct TreeNode *, AddTreeNode,
                    AROS_LCA(APTR,pool,A0),
                    AROS_LCA(struct MinList *,tree,A1),
                    AROS_LCA(STRPTR,name,A2),
                    AROS_LCA(struct Image *,im,A3),
                    AROS_LCA(UWORD,flags,D0),
                    struct Library *, GTDragBase, 29, Gtdrag);
}

void CloseTreeNode(struct MinList *main, struct TreeNode *tn)
{
    return AROS_LC2NR(void, CloseTreeNode,
                    AROS_LCA(struct MinList *,main,A0),
                    AROS_LCA(struct TreeNode *,tn,A1),
                    struct Library *, GTDragBase, 30, Gtdrag);
}

LONG OpenTreeNode(struct MinList *main, struct TreeNode *tn)
{
    return AROS_LC2(LONG, OpenTreeNode,
                    AROS_LCA(struct MinList *,main,A0),
                    AROS_LCA(struct TreeNode *,tn,A1),
                    struct Library *, GTDragBase, 31, Gtdrag);
}

LONG ToggleTreeNode(struct MinList *main, struct TreeNode *tn)
{
    return AROS_LC2(LONG, ToggleTreeNode,
                    AROS_LCA(struct MinList *,main,A0),
                    AROS_LCA(struct TreeNode *,tn,A1),
                    struct Library *, GTDragBase, 32, Gtdrag);
}

struct TreeNode * GetTreeContainer(struct TreeNode *tn)
{
    return AROS_LC1(struct TreeNode *, GetTreeContainer,
                    AROS_LCA(struct TreeNode *,tn,A0),
                    struct Library *, GTDragBase, 33, Gtdrag);
}

STRPTR GetTreePath(struct TreeNode *tn, STRPTR buffer, LONG len)
{
    return AROS_LC3(STRPTR, GetTreePath,
                    AROS_LCA(struct TreeNode *,tn,A0),
                    AROS_LCA(STRPTR,buffer,A1),
                    AROS_LCA(LONG,len,D0),
                    struct Library *, GTDragBase, 34, Gtdrag);
}

struct TreeNode * FindTreePath(struct MinList *tree, STRPTR path)
{
    return AROS_LC2(struct TreeNode *, FindTreePath,
                    AROS_LCA(struct MinList *,tree,A0),
                    AROS_LCA(STRPTR,path,A1),
                    struct Library *, GTDragBase, 35, Gtdrag);
}

struct TreeNode * FindTreeSpecial(struct MinList *tree, APTR special)
{
    return AROS_LC2(struct TreeNode *, FindTreeSpecial,
                    AROS_LCA(struct MinList *,tree,A0),
                    AROS_LCA(APTR,special,A1),
                    struct Library *, GTDragBase, 36, Gtdrag);
}

struct TreeNode * FindListSpecial(struct MinList *list, APTR special)
{
    return AROS_LC2(struct TreeNode *, FindListSpecial,
                    AROS_LCA(struct MinList *,list,A0),
                    AROS_LCA(APTR,special,A1),
                    struct Library *, GTDragBase, 37, Gtdrag);
}

BOOL ToggleTree(struct Gadget *gad, struct TreeNode *tn, struct IntuiMessage *msg)
{
    return AROS_LC3(BOOL, ToggleTree,
                    AROS_LCA(struct Gadget *,gad,A0),
                    AROS_LCA(struct TreeNode *,tn,A1),
                    AROS_LCA(struct IntuiMessage *,msg,A2),
                    struct Library *, GTDragBase, 38, Gtdrag);
}
