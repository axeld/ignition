/*
 * Copyright ©1999-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the MIT License.
 */
#ifndef SCROLLER_INCLUDES_H
#define SCROLLER_INCLUDES_H


#define INTUI_V36_NAMES_ONLY

#if defined(__SASC)
#	define __USE_SYSBASE

#	define SysBase cb->cb_SysBase
#	define IntuitionBase cb->cb_IntuitionBase
#	define GfxBase cb->cb_GfxBase
#	define UtilityBase cb->cb_UtilityBase
#endif

#include "SDI_compiler.h"
#include "compatibility.h"

#include <exec/execbase.h>
#include <exec/libraries.h>
#include <exec/nodes.h>
#include <exec/lists.h>
#include <exec/ports.h>
#include <exec/memory.h>
#include <exec/resident.h>
#include <devices/input.h>
#include <intuition/intuition.h>
#include <intuition/gadgetclass.h>
#include <intuition/imageclass.h>
#include <intuition/icclass.h>
#include <graphics/gfx.h>
#include <graphics/gfxmacros.h>
#include <gadgets/Scroller.h>
#include <dos/dos.h>

#include <proto/exec.h>
#include <proto/intuition.h>
#include <proto/graphics.h>
#include <proto/utility.h>

#if defined(__SASC)
#	include <pragmas/exec_pragmas.h>
#	include <pragmas/intuition_pragmas.h>
#	include <pragmas/graphics_pragmas.h>
#	include <pragmas/utility_pragmas.h>
#endif

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define ID_FTXT  MAKE_ID('F','T','X','T')
#define ID_CHRS  MAKE_ID('C','H','R','S')

/******************************* ClassBase *******************************/

struct ClassBase
{
  struct Library cb_LibNode;
  Class  *cb_ScrollerClass;
  struct SignalSemaphore cb_LockSemaphore;
  APTR   cb_SysBase;
  APTR   cb_UtilityBase;
  APTR   cb_IntuitionBase;
  APTR   cb_GfxBase;
  BPTR   cb_LibSegment;
  Class  *cb_ArrowClass;
};


/******************************* internal structures *******************************/

/** Scroller-Gadget **/

struct ScrollerGData
{
  struct Gadget *sd_Up,*sd_Down;
  struct Image *sd_UpImage,*sd_DownImage,*sd_Frame;
  UWORD  sd_ItemHeight;
};

/** Arrow-Image **/

struct ArrowIData
{
  struct Image *ad_Frame;
  long   ad_Type;
};

#define ADT_UP 0
#define ADT_DOWN 1


/** private functions **/

// main

extern int PRIVATE SC_Init(struct ClassBase *cb);
extern void PRIVATE SC_Exit(struct ClassBase *cb);

/** public functions **/
extern Class * PUBLIC GetClass(REG(a6, APTR classbase));
extern IPTR PUBLIC DispatchScrollerGadget(REG(a0, Class *cl),REG(a2, Object *o),REG(a1, Msg msg));
extern IPTR PUBLIC DispatchArrowImage(REG(a0, Class *cl),REG(a2,Object *o),REG(a1, Msg msg));

#endif    // SCROLLER_INCLUDES_H
