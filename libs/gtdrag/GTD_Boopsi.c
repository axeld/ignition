/*
 * Copyright ©1999-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the MIT License.
 */

//!	BOOPSI gadgets


#include "gtdrag_includes.h"


ULONG PRIVATE DoCustomMethod(struct Gadget *gad,ULONG method,...)
{
  return(CallHookPkt((struct Hook *)gad->MutualExclude,gad,&method));
}


ULONG PRIVATE DoRenderMethod(struct DragGadget *rdg,WORD x,WORD y,ULONG mode)
{
  struct GadgetInfo gi;
  struct RastPort *rp;
  struct Gadget *gad = rdg->dg_Gadget;
  ULONG  rc = 0L;

  memset(&gi,0,sizeof(struct GadgetInfo));
  gi.gi_Window = rdg->dg_Window;
  gi.gi_Screen = gi.gi_Window->WScreen;
  gi.gi_RastPort = gi.gi_Window->RPort;
  gi.gi_Layer = gi.gi_Window->WLayer;
  gi.gi_Domain.Left = rdg->dg_Gadget->LeftEdge;
  gi.gi_Domain.Top = rdg->dg_Gadget->TopEdge;
  gi.gi_Domain.Width = rdg->dg_Gadget->Width;
  gi.gi_Domain.Height = rdg->dg_Gadget->Height;
  gi.gi_DrInfo = GetScreenDrawInfo(gi.gi_Screen);

  if (rp = ObtainGIRPort(&gi))
  {
    if (mode != GRENDER_DELETE)
    {
      x += dg->dg_Window->LeftEdge-rdg->dg_Window->LeftEdge-gad->LeftEdge;
      y += dg->dg_Window->TopEdge-rdg->dg_Window->TopEdge-gad->TopEdge;
    }
    rc = DoCustomMethod(gad,GM_RENDERDRAG,&gi,rp,mode,words(x,y));
    ReleaseGIRPort(rp);
  }
  FreeScreenDrawInfo(gi.gi_Screen,gi.gi_DrInfo);

  return(rc);
}


ULONG PUBLIC GTD_HandleInput(reg (a0) struct Gadget *gad,reg (a1) struct gpInput *gpi)
{
  struct InputEvent *ie;
  long   x,y;

  if (!gpi || !gad || !gdo || gad != boopsigad || !(ie = gpi->gpi_IEvent))
    return(GMR_HANDLEYOURSELF);

  x = gpi->gpi_Mouse.X+gad->LeftEdge;
  y = gpi->gpi_Mouse.Y+gad->TopEdge;

  switch(ie->ie_Class)
  {
    case IECLASS_RAWMOUSE:
      if (ie->ie_Code == IECODE_NOBUTTON)
      {
        MouseMove(x,y);
        return(GMR_MEACTIVE);
      }
      else
      {
        if (ie->ie_Code == (IECODE_LBUTTON | IECODE_UP_PREFIX))
          MakeDropMessage(GetDragApp(dg->dg_Task),ie->ie_Qualifier,x,y);

        FreeDragObj(gdo);
        EndDrag();
        return(GMR_NOREUSE);
      }
    case IECLASS_TIMER:
      IntuiTick(x,y);
  }
  return(GMR_MEACTIVE);  // catches all input events
}


BOOL PUBLIC GTD_PrepareDrag(reg (a0) struct Gadget *gad,reg (a1) struct gpInput *gpi)
{
  struct DragGadget *dg;
  struct Window *win;

  if (!gad || !gpi || gdo || !gpi->gpi_IEvent || !(gpi->gpi_IEvent->ie_Qualifier & IEQUALIFIER_LEFTBUTTON) || !gpi->gpi_GInfo)
    return(FALSE);

  if (FindDragGadget(gad))  // gadget is already registered
    return(TRUE);

  win = gpi->gpi_GInfo->gi_Window;

  if (!GetDragApp(NULL))    // create an drag application for the input.device
  {
    ULONG tags[] = {GTDA_NewStyle,TRUE,TAG_END};

    GTD_AddAppA("intuition",(struct TagItem *)tags);
  }

  if (dg = AddDragGadget(gad,win,BOOPSI_KIND))
  {
    struct DragWindow *dw;

    foreach(&winlist,dw)      // search for the gadget's real application
      if (dw->dw_Window == win)
        break;

    if (dw->dw_Node.mln_Succ) // window found
      dg->dg_Task = dw->dw_Task;
    else                      // search gadget list
    {
      struct DragGadget *sdg;

      foreach(&gadlist,sdg)
      {
        if (sdg != dg && sdg->dg_Window == win)
        {
          dg->dg_Task = sdg->dg_Task;
          break;
        }
      }
    }
    return(TRUE);
  }
  return(FALSE);
}


BOOL PUBLIC GTD_BeginDrag(reg (a0) struct Gadget *gad,reg (a1) struct gpInput *gpi)
{
  if (dg = FindDragGadget(gad))
  {
    PrepareDrag(TRUE);
    boopsigad = gad;

    gdo = CreateDragObj(dg,gpi->gpi_Mouse.X+gad->LeftEdge,gpi->gpi_Mouse.Y+gad->TopEdge);
    return(TRUE);
  }
  return(FALSE);
}


void PUBLIC GTD_StopDrag(reg (a0) struct Gadget *gad)
{
  if (gad != boopsigad || !gdo)
    return;

  FreeDragObj(gdo);
  EndDrag();
}
