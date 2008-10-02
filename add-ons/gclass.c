/* gClass base module for ignition
 *
 * Copyright �1996-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the MIT License.
 */


#include <exec/types.h>
#include <exec/lists.h>
#include <exec/nodes.h>
#include <exec/memory.h>
#include <dos/dos.h>
#include <libraries/gtdrag.h>

#include <clib/exec_protos.h>
#include <clib/dos_protos.h>
#include <pragmas/exec_pragmas.h>
#include <pragmas/dos_pragmas.h>

#include <string.h>
#include <math.h>

#include "gclass.h"

#define reg(x) register __ ## x
#define PUBLIC __saveds __asm

extern kprintf(STRPTR,...);
#define bug kprintf


struct __gClass {
	struct ImageNode gc_Node;   /* name and icon, only for non-diagrams */
	struct gClass *gc_Super;    /* super class */
	ULONG  gc_InstOffset;
	ULONG  gc_InstSize;
	ULONG  gc_Flags;
	struct gInterface *gc_Interface;
	BPTR   gc_Segment;
	ULONG  __asm (*gc_Dispatch)(reg (a0) struct gClass *,reg (a1) APTR,reg (a2) Msg);
	ULONG  __asm (*gc_Draw)(reg (d0) struct Page *,reg (d1) ULONG,reg (a0) struct RastPort *,reg (a1) struct gClass *,reg (a2) struct gObject *,reg (a3) struct gBounds *);
	ULONG  __asm (*gc_FreeClass)(reg (a0) struct gClass *);
	STRPTR gc_ClassName;        /* internal access (filename) */
};

struct ExecBase *SysBase;
struct GfxBase *GfxBase;
struct Library *UtilityBase, *LocaleBase;
struct Library *MathIeeeDoubBasBase, *MathIeeeDoubTransBase;
APTR   pool, gcBase;


/* Module functions */

extern ULONG PUBLIC dispatch(reg (a0) struct gClass *gc,reg (a1) APTR obj,reg (a2) Msg msg);
extern ULONG PUBLIC draw(reg (d0) struct Page *,reg (d0) ULONG,reg (a0) struct RastPort *,reg (a1) struct gClass *,reg (a2) struct gObject *,reg (a3) struct gBounds *);
extern ULONG PUBLIC freeClass(reg (a0) struct gClass *gc);
extern ULONG PUBLIC initClass(reg (a0) struct gClass *gc);
extern struct gInterface interface[];
extern ULONG instanceSize;
extern const STRPTR superClass;


BOOL PUBLIC
InitGClass(reg (a6) struct ExecBase *ExecBase, reg (a0) struct __gClass *gc, reg (a1) APTR table, reg (a2) APTR mainpool,
	reg (a3) APTR gfxbase, reg (d0) APTR mathbase, reg (d1) APTR mathtrans, reg (d2) APTR utilitybase, reg (d3) APTR localebase,
    reg (d4) long magic)
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

	if (!initClass(gc))
		return FALSE;

	return TRUE;
}

