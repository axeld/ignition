/*
 * Copyright ©1999-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the MIT License.
 */

//!	window functions.


#include "gtdrag_includes.h"


struct DragWindow *FindDragWindow(struct Window *win)
{
  struct DragWindow *dw;

  foreach(&winlist,dw)
  {
    if (dw->dw_Window == win)
      return(dw);
  }
  return(NULL);
}


void PRIVATE SetWindowAttrs(struct Window *win,struct TagItem *tags)
{
  struct TagItem *tstate,*ti;
  struct DragWindow *dw;

  if (!(dw = FindDragWindow(win)))
    return;

  tstate = (struct TagItem *)tags;
  while(ti = NextTagItem(&tstate))
  {
    switch(ti->ti_Tag)
    {
      case GTDA_AcceptMask:
        dw->dw_AcceptMask = ti->ti_Data;
        break;
      case GTDA_AcceptFunc:
        dw->dw_AcceptFunc = (APTR)ti->ti_Data;
        break;
    }
  }

}


void PUBLIC GTD_RemoveWindow(reg (a0) struct Window *win)
{
  struct DragWindow *dw;

  ObtainSemaphore(&ListSemaphore);

  foreach(&winlist,dw)
  {
    if (dw->dw_Window == win)
    {
      Remove((struct Node *)dw);
      FreeMem(dw, sizeof(struct DragWindow));
      break;
    }
  }
  ReleaseSemaphore(&ListSemaphore);
}


void PUBLIC GTD_AddWindowA(reg (a0) struct Window *win,reg (a1) struct TagItem *tags)
{
  struct DragApp *da;
  struct DragWindow *dw;

  ObtainSemaphore(&ListSemaphore);
  if ((da = GetDragApp(NULL)) && win && (dw = AllocMem(sizeof(struct DragWindow),MEMF_PUBLIC | MEMF_CLEAR)))
  {
    dw->dw_Window = win;
    dw->dw_Task = da->da_Task;
    dw->dw_AcceptMask = 0xffffffff;
    SetWindowAttrs(win,tags);

    AddTail((struct List *)&winlist,(APTR)dw);
  }
  ReleaseSemaphore(&ListSemaphore);
}
