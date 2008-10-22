/*
 * Copyright ©1999-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the MIT License.
 */

//!	Library part.


#include "gtdrag_includes.h"


struct GTDragBase
{
  struct Library          LibNode;
  struct ExecBase        *ExecBase;
  struct SignalSemaphore  LockSemaphore;
  BPTR                    LibSegment;
};


struct Library * PUBLIC LibInit(reg (a0) BPTR Segment,reg (d0) struct GTDragBase *GTDragBase,reg (a6) struct ExecBase *ExecBase);
struct Library * PUBLIC LibOpen(reg (a6) struct GTDragBase *GTDragBase);
BPTR PUBLIC LibExpunge(reg (a6) struct GTDragBase *GTDragBase);
BPTR PUBLIC LibClose(reg (a6) struct GTDragBase *GTDragBase);
LONG PUBLIC LibNull(reg (a6) struct GTDragBase *GTDragBase);
APTR PUBLIC LibNOP(void);

STATIC APTR LibVectors[] =
{
  LibOpen,
  LibClose,
  LibExpunge,
  LibNull,

  GTD_GetIMsg,
  GTD_ReplyIMsg,
  GTD_FilterIMsg,
  GTD_PostFilterIMsg,
  LibNOP,              // GTD_GetDragMsg()
  LibNOP,              // GTD_ReplyDragMsg()
  GTD_AddAppA,
  GTD_RemoveApp,
  GTD_AddWindowA,
  GTD_RemoveWindow,
  GTD_AddGadgetA,
  GTD_RemoveGadget,
  GTD_RemoveGadgets,
  GTD_SetAttrsA,
  GTD_GetAttr,
  GTD_GetHook,
  GTD_GetString,
  GTD_PrepareDrag,
  GTD_BeginDrag,
  GTD_HandleInput,
  GTD_StopDrag,

  FreeTreeList,
  InitTreeList,
  FreeTreeNodes,
  AddTreeNode,
  CloseTreeNode,
  OpenTreeNode,
  ToggleTreeNode,
  GetTreeContainer,
  GetTreePath,
  FindTreePath,
  FindTreeSpecial,
  FindListSpecial,
  ToggleTree,

  (APTR)-1
};

extern UBYTE __far LibName[], LibID[];
extern LONG __far LibVersion, LibRevision;

struct { ULONG DataSize; APTR Table; APTR Data; struct Library * (*Init)(); } __aligned LibInitTab =
{
  sizeof(struct GTDragBase),
  LibVectors,
  NULL,
  LibInit
};


struct Library * PUBLIC LibInit(reg (a0) BPTR Segment,reg (d0) struct GTDragBase *GTDragBase,reg (a6) struct ExecBase *ExecBase)
{
  if(ExecBase->LibNode.lib_Version < 37)
    return(NULL);

  GTDragBase->LibNode.lib_Node.ln_Type = NT_LIBRARY;
  GTDragBase->LibNode.lib_Node.ln_Name = LibName;
  GTDragBase->LibNode.lib_Flags        = LIBF_CHANGED | LIBF_SUMUSED;
  GTDragBase->LibNode.lib_Version      = LibVersion;
  GTDragBase->LibNode.lib_Revision     = LibRevision;
  GTDragBase->LibNode.lib_IdString     = (APTR)LibID;
  GTDragBase->LibSegment = Segment;
  GTDragBase->ExecBase = SysBase;

  /** init global data **/

  NewList((struct List *)&applist);
  NewList((struct List *)&gadlist);
  NewList((struct List *)&winlist);

  mx = 0;  my = 0;
  gdo = NULL;  dg = NULL;
  fakemsg = FALSE;  noreport = FALSE;

  /** init hooks **/

  treeHook.h_Entry = (APTR)TreeHook;
  renderHook.h_Entry = (APTR)RenderHook;
  iffstreamHook.h_Entry = (APTR)IFFStreamHook;

  /** init semaphores **/

  InitSemaphore(&ListSemaphore);
  InitSemaphore(&GTDragBase->LockSemaphore);

  return((struct Library *)GTDragBase);
}


struct Library * PUBLIC LibOpen(reg (a6) struct GTDragBase *GTDragBase)
{
  GTDragBase->LibNode.lib_Flags &= ~LIBF_DELEXP;
  GTDragBase->LibNode.lib_OpenCnt++;

  ObtainSemaphore(&GTDragBase->LockSemaphore);

  if(GTDragBase->LibNode.lib_OpenCnt == 1)
  {
    if (!GTD_Init())
    {
      GTD_Exit();

      GTDragBase->LibNode.lib_OpenCnt--;
      ReleaseSemaphore(&GTDragBase->LockSemaphore);
      return(NULL);
    }
  }
  ReleaseSemaphore(&GTDragBase->LockSemaphore);
  return((struct Library *)GTDragBase);
}


BPTR PUBLIC LibExpunge(reg (a6) struct GTDragBase *GTDragBase)
{
  struct DragApp *da;
  struct Node *n;

  if(!GTDragBase->LibNode.lib_OpenCnt && GTDragBase->LibSegment)
  {
    BPTR TempSegment = GTDragBase->LibSegment;

    while(n = RemHead((struct List *)&gadlist))
      FreeMem(n,sizeof(struct DragGadget));
    while(n = RemHead((struct List *)&winlist))
      FreeMem(n,sizeof(struct DragWindow));
    while(da = (struct DragApp *)RemHead((struct List *)&applist))
      FreeMem(da,sizeof(struct DragApp));

    Remove((struct Node *)GTDragBase);
    FreeMem((BYTE *)GTDragBase - GTDragBase->LibNode.lib_NegSize,GTDragBase->LibNode.lib_NegSize + GTDragBase->LibNode.lib_PosSize);
    return(TempSegment);
  }
  else
  {
    GTDragBase->LibNode.lib_Flags |= LIBF_DELEXP;
    return(NULL);
  }
}


BPTR PUBLIC LibClose(reg (a6) struct GTDragBase *GTDragBase)
{
  if(GTDragBase->LibNode.lib_OpenCnt)
    GTDragBase->LibNode.lib_OpenCnt--;

  if(!GTDragBase->LibNode.lib_OpenCnt)
  {
    ObtainSemaphore(&GTDragBase->LockSemaphore);
    GTD_Exit();
    ReleaseSemaphore(&GTDragBase->LockSemaphore);

    if(GTDragBase->LibNode.lib_Flags & LIBF_DELEXP)
      return(LibExpunge(GTDragBase));
  }
  return(NULL);
}


LONG PUBLIC LibNull(reg (a6) struct GTDragBase *GTDragBase)
{
  return(NULL);
}


APTR PUBLIC LibNOP(void)
{
  return(NULL);
}

