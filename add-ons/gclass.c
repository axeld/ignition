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
#include <libraries/iffparse.h>

#include <clib/exec_protos.h>
#include <clib/dos_protos.h>
#include <pragmas/exec_pragmas.h>
#include <pragmas/dos_pragmas.h>

#include <string.h>
#include <math.h>

#include "gclass.h"


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


BOOL PUBLIC
InitGClass(REG(a0, struct __gClass *gc), REG(a1, APTR table), REG(a2, APTR mainpool), REG(a3, APTR gfxbase),
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

	if (!initClass(gc))
		return FALSE;

	return TRUE;
}
