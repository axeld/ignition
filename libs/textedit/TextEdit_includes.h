/*
 * Copyright ©1999-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the MIT License.
 */
#ifndef TEXTEDIT_INCLUDES_H
#define TEXTEDIT_INCLUDES_H

#define INTUI_V36_NAMES_ONLY

#if !defined(__AROS__)
#	define __USE_SYSBASE

#	define SysBase cb->cb_SysBase
#	define IntuitionBase cb->cb_IntuitionBase
#	define GfxBase cb->cb_GfxBase
#	define DOSBase cb->cb_DOSBase
#	define UtilityBase cb->cb_UtilityBase
#	define IFFParseBase cb->cb_IFFParseBase
#endif

#define ConsoleDevice ((struct Library *)cb->cb_Console.io_Device)

#include "SDI_compiler.h"

#include <exec/execbase.h>
#include <exec/libraries.h>
#include <exec/nodes.h>
#include <exec/lists.h>
#include <exec/ports.h>
#include <exec/memory.h>
#include <devices/input.h>
#include <intuition/intuition.h>
#include <intuition/gadgetclass.h>
#include <intuition/imageclass.h>
#include <intuition/icclass.h>
#include <graphics/gfx.h>
#include <graphics/gfxmacros.h>
#include <libraries/gadtools.h>
#include <gadgets/TextEdit.h>
#include <dos/dos.h>

#include <proto/exec.h>
#include <proto/iffparse.h>
#include <proto/console.h>
#include <proto/intuition.h>
#include <proto/graphics.h>
#include <proto/utility.h>
#include <proto/dos.h>

#if defined(__SASC)
#	include <pragmas/exec_pragmas.h>
#	include <pragmas/iffparse_pragmas.h>
#	include <pragmas/console_pragmas.h>
#	include <pragmas/intuition_pragmas.h>
#	include <pragmas/graphics_pragmas.h>
#	include <pragmas/utility_pragmas.h>
#	include <pragmas/dos_pragmas.h>
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
  Class  *cb_Class;
  struct SignalSemaphore cb_LockSemaphore;
  APTR   cb_SysBase;
  APTR   cb_UtilityBase;
  APTR   cb_IntuitionBase;
  APTR   cb_GfxBase;
  APTR   cb_DOSBase;
  APTR   cb_IFFParseBase;
  struct IOStdReq cb_Console;
  BPTR   cb_LibSegment;
  APTR   cb_ScrollerBase;
};


/******************************* internal structures *******************************/


#define EDF_JUSTIFICATION 3 /* the mask        */
#define EDF_MARK 16
#define EDF_ACTIVE 32
#define EDF_SPECIAL 64      /* draw return/tabs */
#define EDF_AUTOINDENT 128

#define ELT_WORD 0
#define ELT_SPACE 1
#define ELT_TAB 2
#define ELT_NEWLINE 3
#define ELT_END 4

#define EDJ_JUSTIFY 0       /* justified lines */
#define EDJ_LEFT 1          /* left-aligned    */
#define EDJ_RIGHT 2         /* right-aligned   */
#define EDJ_CENTERED 3      /* centered        */

struct EditLine
{
  STRPTR el_Word;
  UWORD  el_Length;
  UWORD  el_Width;
  UBYTE  el_Type;
};

#define EDITLINE(mln) ((struct EditLine *)((UBYTE *)mln+sizeof(ULONG)+sizeof(struct MinNode)))
#define LINEOFFSET(mln) (*(LONG *)(mln+1))


/** private functions **/

// main

extern int PRIVATE TE_Init(struct ClassBase *cb);
extern void PRIVATE TE_Exit(struct ClassBase *cb);
extern void PRIVATE strdel(STRPTR t,long len);
extern long PRIVATE GetEditCursorPos(struct ClassBase *cb,struct RastPort *rp,struct EditGData *ed,long x,long y);
extern struct MinNode * PRIVATE GetEditCursorLine(struct EditGData *ed,ULONG pos,long *line);
extern void PRIVATE GetEditCursorCoord(struct ClassBase *cb,struct RastPort *rp,struct EditGData *ed,ULONG pos,long *x,long *y,long *width);
extern BOOL PRIVATE MakeEditCursorVisible(struct ClassBase *cb,struct RastPort *rp,struct Gadget *gad,struct GadgetInfo *gi,struct EditGData *ed);
extern BOOL PRIVATE MakeEditScroller(struct ClassBase *cb,struct EditGData *ed,struct Gadget *gad,struct Gadget *previous);
extern void PRIVATE SetEditBuffer(struct ClassBase *cb,struct EditGData *ed,long newsize);

// draw

extern void PRIVATE DrawEditCursor(struct ClassBase *cb,struct RastPort *rp,struct Gadget *gad,struct EditGData *ed);
extern void PRIVATE DrawEditGadget(struct ClassBase *cb,struct RastPort *rp,struct Gadget *gad,struct GadgetInfo *gi,struct EditGData *ed,BOOL all);

/** public functions **/


#if defined(__AROS__)
#	include <proto/pTextEdit.h>
#else
/* Mazze: ClassBase moved to end of argument list */
extern Class * PUBLIC GetClass(REG(a6, APTR cb));
extern void PUBLIC Text2Clipboard(REG(d0, UBYTE clipunit),REG(a0, STRPTR t),REG(d1, long len),REG(a6, struct ClassBase *cb));
extern STRPTR PUBLIC TextFromClipboard(REG(d0, UBYTE clipunit),REG(a0, APTR pool),REG(a6, struct ClassBase *cb));
extern IPTR PUBLIC DispatchEditGadget(REG(a0, Class *cl),REG(a2, Object *o),REG(a1, Msg msg));
extern void PUBLIC FreeEditList(REG(a0, struct EditGData *ed),REG(a6, struct ClassBase *cb));
extern BOOL PUBLIC PrepareEditText(REG(a0, struct EditGData *ed),REG(a1, struct RastPort *rp),REG(a2, STRPTR t),REG(a6, struct ClassBase *cb));
#endif

#endif    // TEXTEDIT_H
