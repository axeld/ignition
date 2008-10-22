/*
 * Copyright ©1999-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the MIT License.
 */
#ifndef TEXTEDIT_INCLUDES_H
#define TEXTEDIT_INCLUDES_H

#define INTUI_V36_NAMES_ONLY
#define __USE_SYSBASE

#define SysBase cb->cb_SysBase
#define IntuitionBase cb->cb_IntuitionBase
#define GfxBase cb->cb_GfxBase
#define DOSBase cb->cb_DOSBase
#define UtilityBase cb->cb_UtilityBase
#define IFFParseBase cb->cb_IFFParseBase
#define ConsoleDevice ((struct Library *)cb->cb_Console.io_Device)

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

#include <clib/exec_protos.h>
#include <clib/iffparse_protos.h>
#include <clib/console_protos.h>
#include <clib/intuition_protos.h>
#include <clib/graphics_protos.h>
#include <clib/utility_protos.h>
#include <clib/dos_protos.h>

#include <pragmas/exec_pragmas.h>
#include <pragmas/iffparse_pragmas.h>
#include <pragmas/console_pragmas.h>
#include <pragmas/intuition_pragmas.h>
#include <pragmas/graphics_pragmas.h>
#include <pragmas/utility_pragmas.h>
#include <pragmas/dos_pragmas.h>

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define PUBLIC __asm __saveds
#define PRIVATE __regargs
#define reg(x) register __ ## x

extern void kprintf(STRPTR,...);
#define bug kprintf

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

struct EditGData
{
  APTR   ed_Pool;
  STRPTR ed_Text;
  long   ed_Size,ed_Pos,ed_MarkPos,ed_TextLines;
  struct MinList ed_List;
  struct MinNode *ed_Top;
  UWORD  ed_LineHeight,ed_Spacing,ed_MinSpace,ed_MaxSpace,ed_CharWidth;
  UWORD  ed_Width,ed_Lines,ed_MaxSpaces,ed_TabSpaces,ed_GadWidth;
  UBYTE  ed_APen,ed_BPen,ed_BorderH,ed_BorderV;
  UWORD  ed_Flags;
  long   ed_FrameType;
  struct Gadget *ed_Scroller;
  UBYTE  ed_ClipUnit;
};

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

extern Class * PUBLIC GetClass(reg (a6) APTR cb);
extern ULONG PUBLIC DispatchEditGadget(reg (a0) Class *cl,reg (a2) Object *o,reg (a1) Msg msg);
extern void PUBLIC Text2Clipboard(reg (d0) UBYTE clipunit,reg (a0) STRPTR t,reg (d1) long len,reg (a6) struct ClassBase *cb);
extern STRPTR PUBLIC TextFromClipboard(reg (d0) UBYTE clipunit,reg (a0) APTR pool,reg (a6) struct ClassBase *cb);
extern void PUBLIC FreeEditList(reg (a6) struct ClassBase *cb,reg (a0) struct EditGData *ed);
extern BOOL PUBLIC PrepareEditText(reg (a6) struct ClassBase *cb,reg (a0) struct EditGData *ed,reg (a1) struct RastPort *rp,reg (a2) STRPTR t);

#endif    // TEXTEDIT_H
