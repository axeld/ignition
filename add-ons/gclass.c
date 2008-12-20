/* gClass base module for ignition
 *
 * Copyright ©1996-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the MIT License.
 */


#include <exec/types.h>
#include <exec/lists.h>
#include <exec/nodes.h>
#include <exec/memory.h>
#include <dos/dos.h>
#include <libraries/gtdrag.h>
#include <libraries/iffparse.h>

#include <proto/exec.h>
#include <proto/dos.h>

#if defined(__SASC)
#	include <pragmas/exec_pragmas.h>
#	include <pragmas/dos_pragmas.h>
#elif defined(__AROS__)
#	include <aros/symbolsets.h>
#endif

#include <string.h>
#include <math.h>

#include "gclass.h"
#include "gclass_protos.h"

struct __gClass {
	struct ImageNode gc_Node;   /* name and icon, only for non-diagrams */
	struct gClass *gc_Super;    /* super class */
	ULONG  gc_InstOffset;
	ULONG  gc_InstSize;
	ULONG  gc_Flags;
	struct gInterface *gc_Interface;
	BPTR   gc_Segment;
	ULONG  ASM (*gc_Dispatch)(REG(a0, struct gClass *), REG(a2, APTR), REG(a1, Msg));
	ULONG  ASM (*gc_Draw)(REG(d0, struct Page *), REG(d1, ULONG), REG(a0, struct RastPort *), REG(a1, struct gClass *), REG(a2, struct gObject *), REG(a3, struct gBounds *));
	ULONG  ASM (*gc_FreeClass)(REG(a0, struct gClass *));
	STRPTR gc_ClassName;        /* internal access (filename) */
};

struct ExecBase *SysBase;
struct GfxBase *GfxBase;
struct UtilityBase *UtilityBase;
struct LocaleBase *LocaleBase;
struct Library *MathIeeeDoubBasBase, *MathIeeeDoubTransBase;
APTR   pool, gcBase;


/* Module functions */

extern ULONG PUBLIC dispatch(REG(a0, struct gClass *gc), REG(a2, APTR obj), REG(a1, Msg msg));
extern ULONG PUBLIC draw(REG(d0, struct Page *), REG(d0, ULONG), REG(a0, struct RastPort *), REG(a1, struct gClass *), REG(a2, struct gObject *), REG(a3, struct gBounds *));
extern ULONG PUBLIC freeClass(REG(a0, struct gClass *gc));
extern ULONG PUBLIC initClass(REG(a0, struct gClass *gc));
extern struct gInterface interface[];
extern ULONG instanceSize;
extern const STRPTR superClass;

#ifdef __AROS__
// ensure that InitGClass becomes 1st function in segment
BOOL PUBLIC
InitGClass(REG(a0, struct __gClass *gc), REG(a1, TableEntry *table), REG(a2, APTR mainpool), REG(a3, APTR gfxbase),
	REG(a6, struct ExecBase *ExecBase), REG(d0, APTR mathbase), REG(d1, APTR mathtrans), REG(d2, APTR utilitybase), REG(d3, APTR localebase),
    REG(d4, long magic)) __attribute__((section(".aros.startup")));
#endif

BOOL PUBLIC
InitGClass(REG(a0, struct __gClass *gc), REG(a1, TableEntry *table), REG(a2, APTR mainpool), REG(a3, APTR gfxbase),
	REG(a6, struct ExecBase *ExecBase), REG(d0, APTR mathbase), REG(d1, APTR mathtrans), REG(d2, APTR utilitybase), REG(d3, APTR localebase),
    REG(d4, long magic))
{
#ifdef IGNITION_LITE_EDITION
	if (magic != MAKE_ID('I', 'G', 'N', '\0') && magic != MAKE_ID('I', 'G', 'L', '\0'))
		return FALSE;
#else
	if (magic != MAKE_ID('I', 'G', 'N', '\0'))
		return FALSE;
#endif

    SysBase = ExecBase;
    GfxBase = gfxbase;
    UtilityBase = utilitybase;
    MathIeeeDoubBasBase = mathbase;
    MathIeeeDoubTransBase = mathtrans;
	LocaleBase = localebase;

    gc->gc_Dispatch = dispatch;
    gc->gc_Draw = draw;
    gc->gc_FreeClass = freeClass;
    gc->gc_Interface = interface;
	gc->gc_InstSize = gc->gc_InstOffset + instanceSize;

    gcBase = table;
    pool = mainpool;

	// Initialize function pointers
	AllocStringLength = table[-1].func;
	AllocString = table[-2].func;
	FreeString = table[-3].func;
	gDoMethodA = table[-4].func;
	gDoSuperMethodA = table[-5].func;
	SetHighColor = table[-6].func;
	SetColors = table[-7].func;
	FindColorPen = table[-8].func;
	DrawRect = table[-9].func;
	DrawLine = table[-10].func;
	gAreaMove = table[-11].func;
	gAreaDraw = table[-12].func;
	gAreaEnd = table[-13].func;
	GetDPI = table[-14].func;
	GetOffset = table[-15].func;
	FreeFontInfo = table[-16].func;
	SetFontInfoA = table[-17].func;
	CopyFontInfo = table[-18].func;
	NewFontInfoA = table[-19].func;
	DrawText = table[-20].func;
	OutlineLength = table[-21].func;
	OutlineHeight = table[-22].func;
	pixel = table[-23].func;
	mm = table[-24].func;
	CreateTerm = table[-25].func;
	DeleteTerm = table[-26].func;
	CopyTerm = table[-27].func;
	CalcTerm = table[-28].func;
	gInsertRemoveCellsTablePos = table[-29].func;
	gInsertRemoveCellsTerm = table[-30].func;
	TintColor = table[-31].func;
	gSuperDraw = table[-32].func;
	gGetLink = table[-33].func;
	SetLowColor = table[-34].func;
	SetOutlineColor = table[-35].func;

	if (!initClass(gc))
		return FALSE;

	return TRUE;
}
