/*
 * Copyright ©1999-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the MIT License.
 */

//!	IntuiMessage handling.


#include "gtdrag_includes.h"


struct IntuiMessage * PRIVATE HandleIMsg(struct DragApp *da,struct IntuiMessage *msg)
{
  struct IntuiMessage *gmsg;
  int    class,mousex,mousey;

  if (!da || !msg)
    return(msg);

  class = msg->Class;
  mousex = msg->MouseX;
  mousey = msg->MouseY;
  da->da_GTMsg = FALSE;

  if (class == IDCMP_GADGETDOWN)   // DragGadget suchen
  {
    if (!IsListEmpty((struct List *)&gadlist))
    {
      foreach(&gadlist,dg)
      {
        if (dg->dg_Gadget == msg->IAddress)
          break;
      }
      if (!dg->dg_Node.mln_Succ)
        for(dg = (APTR)gadlist.mlh_Head;dg->dg_Node.mln_Succ && ((dg->dg_Gadget->GadgetID != ((struct Gadget *)msg->IAddress)->GadgetID) || (dg->dg_Window != msg->IDCMPWindow));dg = (APTR)dg->dg_Node.mln_Succ);

      if (dg->dg_Node.mln_Succ && dg->dg_Window == msg->IDCMPWindow && (dg->dg_Gadget->GadgetID == ((struct Gadget *)msg->IAddress)->GadgetID) && PointInDragGadget(dg,mousex,mousey,FALSE))
      {
        if (dg->dg_Type == LISTVIEW_KIND && !GT_GetGadgetAttrs(dg->dg_Gadget,dg->dg_Window,NULL,GTLV_Selected,&dg->dg_Selected,TAG_END))
          dg->dg_Selected = ~0L;

        mx = mousex;  my = mousey;
        PrepareDrag(FALSE);
      }
      else
        dg = NULL;
    }
    else
      dg = NULL;
  }
  else if (class == IDCMP_GADGETUP && !fakemsg && dg)
    EndDrag();
  else if (class == IDCMP_MOUSEMOVE)
  {
    if (gdo)
      MouseMove(mousex,mousey);
    else if (dg && !(dg->dg_Flags & DGF_NODRAG))
    {
      if (mx != ~0L && (msg->Qualifier & IEQUALIFIER_DRAGKEY || (dg->dg_Type == LISTVIEW_KIND && (abs(mx-mousex) > LVDRAGPIXEL) || dg->dg_Type != LISTVIEW_KIND && ((abs(my-msg->MouseY) > DRAGPIXEL) || (abs(mx-mousex) > DRAGPIXEL)))))
        gdo = CreateDragObj(dg,mousex,mousey);
    }
  }
  else if (gdo)
  {
    if (class == IDCMP_MOUSEBUTTONS && !fakemsg)
    {
      if (msg->Code == SELECTUP)
        MakeDropMessage(da,msg->Qualifier,mousex,mousey);

      FreeDragObj(gdo);
      EndDrag();
    }
    else if (class == IDCMP_INTUITICKS)
      IntuiTick(mousex,mousey);
  }
  else if (class == IDCMP_MOUSEBUTTONS && dg)
    EndDrag();

  if (gmsg = GT_FilterIMsg(msg))
  {
    da->da_GTMsg = TRUE;
    msg = gmsg;
    if (fakemsg && (class == IDCMP_GADGETUP || class == IDCMP_MOUSEBUTTONS))
    {
      msg = GT_PostFilterIMsg(msg);
      ReplyMsg(msg);
      fakemsg = FALSE;
      msg = NULL;
    }
  }
  return(msg);
}


struct IntuiMessage * PUBLIC GTD_GetIMsg(reg (a0) struct MsgPort *mp)
{
  struct IntuiMessage *msg;
  struct DragApp *da;

  if (da = GetDragApp(NULL))
  {
    while(msg = (struct IntuiMessage *)GetMsg(mp))
    {
      msg = HandleIMsg(da,msg);
      if (!da->da_GTMsg)
        ReplyMsg(msg);
      else
        return(msg);
    }
  }
  else
    return(GT_GetIMsg(mp));

  return(NULL);
}


struct IntuiMessage * PUBLIC GTD_FilterIMsg(reg (a0) struct IntuiMessage *msg)
{
  struct DragApp *da;

  if (da = GetDragApp(NULL))
    return(HandleIMsg(da,msg));

  return(GT_FilterIMsg(msg));
}


void PUBLIC GTD_ReplyIMsg(reg (a0) struct IntuiMessage *msg)
{
  struct DragApp *da;

  if (da = GetDragApp(NULL))
  {
    if (da->da_GTMsg)
      msg = GT_PostFilterIMsg(msg);

    ReplyMsg(msg);
  }
  else
    GT_ReplyIMsg(msg);

  if (msg = (APTR)GetMsg(dmport))
    FreeDropMessage(msg);
}


struct IntuiMessage * PUBLIC GTD_PostFilterIMsg(reg (a0) struct IntuiMessage *msg)
{
  struct DragApp *da;

  if (!(da = GetDragApp(NULL)) || da->da_GTMsg)
    return(GT_PostFilterIMsg(msg));

  return(msg);
}

