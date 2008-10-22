/*
 * Copyright ©1999-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the MIT License.
 */

//!	Private functions.


#include "gtdrag_includes.h"


struct ExecBase *SysBase;
struct IntuitionBase *IntuitionBase;
struct Library *DOSBase;
struct GfxBase *GfxBase;
struct Library *UtilityBase;
struct Library *LayersBase;
struct Library *GadToolsBase;
struct Library *CyberGfxBase;

struct MinList applist;
struct MinList gadlist;
struct MinList winlist;
struct DragObj *gdo;
struct DragGadget *dg,*hdg,*adg;
struct DropMessage dm;
struct BitMap *hbm;
struct Gadget *boopsigad;
struct RastPort hrp,hsrp;
int    mx,my,hx,hy,hw,hh;
BOOL   fakemsg,noreport;
struct MsgPort *dmport;
struct SignalSemaphore ListSemaphore;
struct Hook iffstreamHook,renderHook,treeHook;


void PRIVATE GTD_Exit(void)
{
  if (dmport)
  {
    struct IntuiMessage *msg;

    while(msg = (APTR)GetMsg(dmport))
      FreeDropMessage(msg);
    DeleteMsgPort(dmport);
  }
  CloseLibrary(CyberGfxBase);
  CloseLibrary(GadToolsBase);
  CloseLibrary(DOSBase);
  CloseLibrary(IntuitionBase);
  CloseLibrary((struct Library *)GfxBase);
  CloseLibrary(LayersBase);
  CloseLibrary(UtilityBase);
}


int PRIVATE GTD_Init(void)
{
  SysBase = *(struct ExecBase **)4;
  IntuitionBase = (struct IntuitionBase *)OpenLibrary("intuition.library",37);
  DOSBase = OpenLibrary("dos.library",37L);
  GfxBase = (struct GfxBase *)OpenLibrary("graphics.library",37);
  GadToolsBase = OpenLibrary("gadtools.library",37);
  LayersBase = OpenLibrary("layers.library",37);
  UtilityBase = OpenLibrary("utility.library",37);
  CyberGfxBase = OpenLibrary("cybergraphics.library",41);

  if (IntuitionBase && GfxBase && GadToolsBase && LayersBase && UtilityBase)
  {
    if (dmport = CreateMsgPort())
      return(TRUE);
  }
  return(FALSE);
}


int PRIVATE CountNodes(struct List *l)
{
  struct Node *n;
  int i = 0;

  if (!l)
    return(0);
  for(n = l->lh_Head;n->ln_Succ;n = n->ln_Succ,i++);
  return(i);
}


struct Node * PRIVATE FindListNumber(struct MinList *l,long num)
{
  struct Node *n;
  long    i;
  ULONG  listend = ~0L;

  if (IsListEmpty((struct List *)l))
    return(NULL);
  for(n = (struct Node *)l->mlh_Head,i = 0;(i < num) && (n->ln_Succ);i++,n = n->ln_Succ)
    if (n == (struct Node *)l->mlh_TailPred && listend == -1)
      listend = i;
  if (listend < num)
    return(NULL);
  return(n);
}


void PRIVATE FakeInputEvent(void)
{
  struct IOStdReq *ireq;
  struct MsgPort *iport;
  struct InputEvent *ie;

  if (iport = CreatePort(NULL,NULL))
  {
    if (ie = AllocMem(sizeof(struct InputEvent),MEMF_PUBLIC | MEMF_CLEAR))
    {
      if (ireq = (struct IOStdReq *)CreateExtIO(iport,sizeof(struct IOStdReq)))
      {
        if (!OpenDevice("input.device",NULL,(struct IORequest *)ireq,NULL))
        {
          ie->ie_NextEvent = NULL;
          ie->ie_Class = IECLASS_RAWMOUSE;
          ie->ie_Code = IECODE_LBUTTON | IECODE_UP_PREFIX;
          ie->ie_Qualifier = 0 /*IEQUALIFIER_RELATIVEMOUSE*/;
          ie->ie_X = 0;
          ie->ie_Y = 0;

          ireq->io_Data = (APTR)ie;
          ireq->io_Command = IND_WRITEEVENT;
          ireq->io_Flags = 0;
          ireq->io_Length = sizeof(struct InputEvent);
          fakemsg = TRUE;
          DoIO((struct IORequest *)ireq);
          CloseDevice((struct IORequest *)ireq);
        }
        DeleteExtIO((struct IORequest *)ireq);
      }
      FreeMem(ie,sizeof(struct InputEvent));
    }
    DeletePort(iport);
  }
}


