/*
 * Copyright ©1999-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the MIT License.
 */

//!	library base functions


#include "TextEdit_includes.h"


struct Library * PUBLIC LibInit(reg (a0) BPTR Segment,reg (d0) struct ClassBase *cb,reg (a6) struct ExecBase *ExecBase);
struct Library * PUBLIC LibOpen(reg (a6) struct ClassBase *cb);
BPTR PUBLIC LibExpunge(reg (a6) struct ClassBase *cb);
BPTR PUBLIC LibClose(reg (a6) struct ClassBase *cb);
LONG PUBLIC LibNull(reg (a6) struct ClassBase *cb);

STATIC APTR LibVectors[] =
{
  LibOpen,
  LibClose,
  LibExpunge,
  LibNull,

  GetClass,
  Text2Clipboard,
  TextFromClipboard,
  FreeEditList,
  PrepareEditText,

  (APTR)-1
};

extern UBYTE __far LibName[], LibID[];
extern LONG __far LibVersion, LibRevision;

struct { ULONG DataSize; APTR Table; APTR Data; struct Library * (*Init)(); } __aligned LibInitTab =
{
  sizeof(struct ClassBase),
  LibVectors,
  NULL,
  LibInit
};


struct Library * PUBLIC LibInit(reg (a0) BPTR segment,reg (d0) struct ClassBase *cb,reg (a6) struct ExecBase *ExecBase)
{
  if(ExecBase->LibNode.lib_Version < 37)
    return(NULL);

  cb->cb_LibNode.lib_Node.ln_Type = NT_LIBRARY;
  cb->cb_LibNode.lib_Node.ln_Name = LibName;
  cb->cb_LibNode.lib_Flags        = LIBF_CHANGED | LIBF_SUMUSED;
  cb->cb_LibNode.lib_Version      = LibVersion;
  cb->cb_LibNode.lib_Revision     = LibRevision;
  cb->cb_LibNode.lib_IdString     = (APTR)LibID;
  cb->cb_LibSegment = segment;
  cb->cb_SysBase = ExecBase;

  InitSemaphore(&cb->cb_LockSemaphore);

  return((struct Library *)cb);
}


struct Library * PUBLIC LibOpen(reg (a6) struct ClassBase *cb)
{
  cb->cb_LibNode.lib_Flags &= ~LIBF_DELEXP;
  cb->cb_LibNode.lib_OpenCnt++;

  ObtainSemaphore(&cb->cb_LockSemaphore);

  if(cb->cb_LibNode.lib_OpenCnt == 1)
  {
    if (!TE_Init(cb))
    {
      TE_Exit(cb);

      cb->cb_LibNode.lib_OpenCnt--;
      ReleaseSemaphore(&cb->cb_LockSemaphore);
      return(NULL);
    }
  }
  ReleaseSemaphore(&cb->cb_LockSemaphore);
  return((struct Library *)cb);
}


BPTR PUBLIC LibExpunge(reg (a6) struct ClassBase *cb)
{
  if (!cb->cb_LibNode.lib_OpenCnt && cb->cb_LibSegment)
  {
    BPTR TempSegment = cb->cb_LibSegment;

    Remove((struct Node *)cb);
    FreeMem((BYTE *)cb - cb->cb_LibNode.lib_NegSize,cb->cb_LibNode.lib_NegSize + cb->cb_LibNode.lib_PosSize);
    return(TempSegment);
  }
  else
  {
    cb->cb_LibNode.lib_Flags |= LIBF_DELEXP;
    return(NULL);
  }
}


BPTR PUBLIC LibClose(reg (a6) struct ClassBase *cb)
{
  if (cb->cb_LibNode.lib_OpenCnt)
    cb->cb_LibNode.lib_OpenCnt--;

  if (!cb->cb_LibNode.lib_OpenCnt)
  {
    ObtainSemaphore(&cb->cb_LockSemaphore);
    TE_Exit(cb);
    ReleaseSemaphore(&cb->cb_LockSemaphore);

    if (cb->cb_LibNode.lib_Flags & LIBF_DELEXP)
      return(LibExpunge(cb));
  }
  return(NULL);
}


LONG PUBLIC LibNull(reg (a6) struct ClassBase *cb)
{
  return(NULL);
}


