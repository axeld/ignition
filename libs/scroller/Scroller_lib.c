/*
 * Copyright ©1999-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the MIT License.
 */

//!	library base functions.


#include "Scroller_includes.h"


struct Library * PUBLIC LibInit(REG(a0, BPTR Segment),REG(d0, struct ClassBase *cb),REG(a6, struct ExecBase *ExecBase);
struct Library * PUBLIC LibOpen(REG(a6, struct ClassBase *cb));
BPTR PUBLIC LibExpunge(REG(a6, struct ClassBase *cb));
BPTR PUBLIC LibClose(REG(a6, struct ClassBase *cb));
LONG PUBLIC LibNull(REG(a6, struct ClassBase *cb));


void PRIVATE SC_Exit(struct ClassBase *cb)
{
  if (FreeClass(cb->cb_ScrollerClass))
    cb->cb_ScrollerClass = NULL;
  if (FreeClass(cb->cb_ArrowClass))
    cb->cb_ArrowClass = NULL;

  CloseLibrary(cb->cb_IntuitionBase);
  CloseLibrary((struct Library *)cb->cb_GfxBase);
  CloseLibrary(cb->cb_UtilityBase);
}


int PRIVATE SC_Init(struct ClassBase *cb)
{
  if (cb->cb_IntuitionBase = OpenLibrary("intuition.library",37))
  {
    if (cb->cb_GfxBase = (APTR)OpenLibrary("graphics.library",37))
    {
      if (cb->cb_UtilityBase = OpenLibrary("utility.library",37))
      {
        Class *cl;

        if (cl = MakeClass("pinc-scrollergadget","propgclass",NULL,sizeof(struct ScrollerGData),0))
        {
          cl->cl_Dispatcher.h_Entry = (APTR)DispatchScrollerGadget;
          cl->cl_Dispatcher.h_Data = cb;
          cl->cl_UserData = (ULONG)cb;
          AddClass(cl);

          cb->cb_ScrollerClass = cl;

          if (cl = MakeClass("pinc-arrowimage","imageclass",NULL,sizeof(struct ArrowIData),0))
          {
            cl->cl_Dispatcher.h_Entry = (APTR)DispatchArrowImage;
            cl->cl_Dispatcher.h_Data = cb;
            cl->cl_UserData = (ULONG)cb;
            //AddClass(cl);

            cb->cb_ArrowClass = cl;
            return(TRUE);
          }
          FreeClass(cl);
        }
        CloseLibrary(cb->cb_UtilityBase);
      }
      CloseLibrary(cb->cb_GfxBase);
    }
    CloseLibrary(cb->cb_IntuitionBase);
  }
  return(FALSE);
}


Class * PUBLIC GetClass(REG(a6, APTR cb))
{
  return(((struct ClassBase *)cb)->cb_ScrollerClass);
}


STATIC APTR LibVectors[] =
{
  LibOpen,
  LibClose,
  LibExpunge,
  LibNull,

  GetClass,

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


struct Library * PUBLIC LibInit(REG(a0, BPTR segment),REG(d0, struct ClassBase *cb),REG(a6, struct ExecBase *ExecBase))
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


struct Library * PUBLIC LibOpen(REG(a6, struct ClassBase *cb))
{
  cb->cb_LibNode.lib_Flags &= ~LIBF_DELEXP;
  cb->cb_LibNode.lib_OpenCnt++;

  ObtainSemaphore(&cb->cb_LockSemaphore);

  if(cb->cb_LibNode.lib_OpenCnt == 1)
  {
    if (!SC_Init(cb))
    {
      SC_Exit(cb);

      cb->cb_LibNode.lib_OpenCnt--;
      ReleaseSemaphore(&cb->cb_LockSemaphore);
      return(NULL);
    }
  }
  ReleaseSemaphore(&cb->cb_LockSemaphore);
  return((struct Library *)cb);
}


BPTR PUBLIC LibExpunge(REG(a6, struct ClassBase *cb))
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


BPTR PUBLIC LibClose(REG(a6, struct ClassBase *cb))
{
  if (cb->cb_LibNode.lib_OpenCnt)
    cb->cb_LibNode.lib_OpenCnt--;

  if (!cb->cb_LibNode.lib_OpenCnt)
  {
    ObtainSemaphore(&cb->cb_LockSemaphore);
    SC_Exit(cb);
    ReleaseSemaphore(&cb->cb_LockSemaphore);

    if (cb->cb_LibNode.lib_Flags & LIBF_DELEXP)
      return(LibExpunge(cb));
  }
  return(NULL);
}


LONG PUBLIC LibNull(REG(a6, struct ClassBase *cb))
{
  return(NULL);
}
