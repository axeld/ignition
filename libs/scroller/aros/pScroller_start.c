/*
    *** Automatically generated from '/home/mazze/projects/AROS/local/ignition/libs/scroller/pScroller.conf'. Edits will be lost. ***
    Copyright © 1995-2009, The AROS Development Team. All rights reserved.
*/
#include <exec/types.h>
#include <exec/libraries.h>
#include <exec/resident.h>
#include <aros/libcall.h>
#include <aros/asmcall.h>
#include <aros/symbolsets.h>
#include <dos/dos.h>

#include "pScroller_libdefs.h"

#ifdef SysBase
#undef SysBase
#endif

#include <proto/exec.h>
#include <proto/alib.h>
#ifndef __AROS__
struct ExecBase *SysBase = NULL;
#endif

#include <gadgets/Scroller.h>
#ifndef GM_SEGLIST_FIELD
static BPTR GM_UNIQUENAME(seglist);
#define GM_SEGLIST_FIELD(lh) (GM_UNIQUENAME(seglist))
#endif
#define LIBBASESIZE sizeof(LIBBASETYPE)
#define GM_CLASSPTR_FIELD(lh) (pscrollervar)
#define pScroller_CLASSPTR_FIELD(lh) (pscrollervar)
#define pScroller_STORE_CLASSPTR 1
#define pArrow_CLASSPTR_FIELD(lh) (parrowvar)
#define pArrow_STORE_CLASSPTR 1

#include <intuition/classes.h>
#include <intuition/classusr.h>

#include <proto/utility.h>
#include <proto/intuition.h>

#include <aros/symbolsets.h>

#include <intuition/classes.h>
#include <intuition/classusr.h>

#include <proto/utility.h>
#include <proto/intuition.h>

#include <aros/symbolsets.h>

extern const int GM_UNIQUENAME(End);
extern const APTR GM_UNIQUENAME(FuncTable)[];
static const struct InitTable GM_UNIQUENAME(InitTable);

extern const char GM_UNIQUENAME(LibName)[];
extern const char GM_UNIQUENAME(LibID)[];
extern const char GM_UNIQUENAME(Copyright)[];

#define __freebase(lh)\
do {\
    UWORD negsize, possize;\
    UBYTE *negptr = (UBYTE *)lh;\
    negsize = ((struct Library *)lh)->lib_NegSize;\
    negptr -= negsize;\
    possize = ((struct Library *)lh)->lib_PosSize;\
    FreeMem (negptr, negsize+possize);\
} while(0)

AROS_UFP3 (LIBBASETYPEPTR, GM_UNIQUENAME(InitLib),
    AROS_UFPA(LIBBASETYPEPTR, lh, D0),
    AROS_UFPA(BPTR, segList, A0),
    AROS_UFPA(struct ExecBase *, sysBase, A6)
);
AROS_LP1(BPTR, GM_UNIQUENAME(ExpungeLib),
    AROS_LPA(LIBBASETYPEPTR, extralh, D0),
    LIBBASETYPEPTR, lh, 3, pScroller
);

struct Resident const GM_UNIQUENAME(ROMTag) =
{
    RTC_MATCHWORD,
    (struct Resident *)&GM_UNIQUENAME(ROMTag),
    (APTR)&GM_UNIQUENAME(End),
    RESIDENTFLAGS,
    VERSION_NUMBER,
    NT_LIBRARY,
    RESIDENTPRI,
    (CONST_STRPTR)&GM_UNIQUENAME(LibName)[0],
    (CONST_STRPTR)&GM_UNIQUENAME(LibID)[6],
    (APTR)&GM_UNIQUENAME(InitTable)
};

static struct InitTable
{
    IPTR              Size;
    const APTR       *FuncTable;
    struct DataTable *DataTable;
    APTR              InitLibTable;
}
const GM_UNIQUENAME(InitTable) =
{
    LIBBASESIZE,
    &GM_UNIQUENAME(FuncTable)[0],
    NULL,
    (APTR)GM_UNIQUENAME(InitLib)
};

const char GM_UNIQUENAME(LibName)[] = MOD_NAME_STRING;
const char GM_UNIQUENAME(LibID)[] = VERSION_STRING;
const char GM_UNIQUENAME(Copyright)[] = COPYRIGHT_STRING;

THIS_PROGRAM_HANDLES_SYMBOLSETS
DECLARESET(INIT)
DECLARESET(EXIT)
DECLARESET(CTORS)
DECLARESET(DTORS)
DECLARESET(INITLIB)
DECLARESET(EXPUNGELIB)
DECLARESET(OPENLIB)
DECLARESET(CLOSELIB)
DECLARESET(OPENDEV)
DECLARESET(CLOSEDEV)
DECLARESET(CLASSESINIT)
DECLARESET(CLASSESEXPUNGE)
#define ADD2INITCLASSES(symbol, pri) ADD2SET(symbol, classesinit, pri)
#define ADD2EXPUNGECLASSES(symbol, pri) ADD2SET(symbol, classesexpunge, pri)

AROS_UFH3 (LIBBASETYPEPTR, GM_UNIQUENAME(InitLib),
    AROS_UFHA(LIBBASETYPEPTR, lh, D0),
    AROS_UFHA(BPTR, segList, A0),
    AROS_UFHA(struct ExecBase *, sysBase, A6)
)
{
    AROS_USERFUNC_INIT

    int ok;

#ifndef __AROS__
    SysBase = sysBase;
#endif
#ifdef GM_SYSBASE_FIELD
    GM_SYSBASE_FIELD(lh) = sysBase;
#endif
    ((struct Library *)lh)->lib_Revision = REVISION_NUMBER;
    GM_SEGLIST_FIELD(lh) = segList;
    if (set_open_libraries() && set_call_libfuncs(SETNAME(CLASSESINIT), 1, 1, lh) && set_call_funcs(SETNAME(INIT), 1, 1) )
    {
        set_call_funcs(SETNAME(CTORS), -1, 0);

        ok = set_call_libfuncs(SETNAME(INITLIB), 1, 1, lh);
    }
    else
        ok = 0;

    if (!ok)
    {
        set_call_libfuncs(SETNAME(EXPUNGELIB), -1, 0, lh);
        set_call_funcs(SETNAME(DTORS), 1, 0);
        set_call_funcs(SETNAME(EXIT), -1, 0);
        set_call_libfuncs(SETNAME(CLASSESEXPUNGE), -1, 0, lh);
        set_close_libraries();

        __freebase(lh);
        return NULL;
    }
    else
    {
        return  lh;
    }

    AROS_USERFUNC_EXIT
}

AROS_LH1 (LIBBASETYPEPTR, GM_UNIQUENAME(OpenLib),
    AROS_LHA (ULONG, version, D0),
    LIBBASETYPEPTR, lh, 1, pScroller
)
{
    AROS_LIBFUNC_INIT

    if ( set_call_libfuncs(SETNAME(OPENLIB), 1, 1, lh) )
    {
        ((struct Library *)lh)->lib_OpenCnt++;
        ((struct Library *)lh)->lib_Flags &= ~LIBF_DELEXP;

        return lh;
    }

    return NULL;

    AROS_LIBFUNC_EXIT
}

AROS_LH0 (BPTR, GM_UNIQUENAME(CloseLib),
    LIBBASETYPEPTR, lh, 2, pScroller
)
{
    AROS_LIBFUNC_INIT

    ((struct Library *)lh)->lib_OpenCnt--;
    set_call_libfuncs(SETNAME(CLOSELIB), -1, 0, lh);
    if
    (
        (((struct Library *)lh)->lib_OpenCnt == 0)
        && (((struct Library *)lh)->lib_Flags & LIBF_DELEXP)
    )
    {
        return AROS_LC1(BPTR, GM_UNIQUENAME(ExpungeLib),
                   AROS_LCA(LIBBASETYPEPTR, lh, D0),
                   LIBBASETYPEPTR, lh, 3, pScroller
        );
    }

    return NULL;

    AROS_LIBFUNC_EXIT
}

AROS_LH1 (BPTR, GM_UNIQUENAME(ExpungeLib),
    AROS_LHA(LIBBASETYPEPTR, extralh, D0),
    LIBBASETYPEPTR, lh, 3, pScroller
)
{
    AROS_LIBFUNC_INIT


    if ( ((struct Library *)lh)->lib_OpenCnt == 0 )
    {
        BPTR seglist = GM_SEGLIST_FIELD(lh);

        if(!set_call_libfuncs(SETNAME(EXPUNGELIB), -1, 1, lh))
        {
            ((struct Library *)lh)->lib_Flags |= LIBF_DELEXP;
            return NULL;
        }

        Remove((struct Node *)lh);

        set_call_funcs(SETNAME(DTORS), 1, 0);
        set_call_funcs(SETNAME(EXIT), -1, 0);
        set_call_libfuncs(SETNAME(CLASSESEXPUNGE), -1, 0, lh);
        set_close_libraries();

        __freebase(lh);

        return seglist;
    }

    ((struct Library *)lh)->lib_Flags |= LIBF_DELEXP;

    return NULL;

    AROS_LIBFUNC_EXIT
}

AROS_LH0 (LIBBASETYPEPTR, GM_UNIQUENAME(ExtFuncLib),
    LIBBASETYPEPTR, lh, 4, pScroller
)
{
    AROS_LIBFUNC_INIT
    return NULL;
    AROS_LIBFUNC_EXIT
}

DEFINESET(INIT)
DEFINESET(EXIT)
DEFINESET(CTORS)
DEFINESET(DTORS)
DEFINESET(INITLIB)
DEFINESET(EXPUNGELIB)
DEFINESET(OPENLIB)
DEFINESET(CLOSELIB)
DEFINESET(OPENDEV)
DEFINESET(CLOSEDEV)
DEFINESET(CLASSESINIT)
DEFINESET(CLASSESEXPUNGE)


const APTR GM_UNIQUENAME(FuncTable)[]=
{
    &AROS_SLIB_ENTRY(GM_UNIQUENAME(OpenLib),pScroller),
    &AROS_SLIB_ENTRY(GM_UNIQUENAME(CloseLib),pScroller),
    &AROS_SLIB_ENTRY(GM_UNIQUENAME(ExpungeLib),pScroller),
    &AROS_SLIB_ENTRY(GM_UNIQUENAME(ExtFuncLib),pScroller),
    (void *)-1
};
/* Initialisation routines for a BOOPSI class */
/* ===========================================*/



/*** Custom dispatcher prototype ********************************************/
BOOPSI_DISPATCHER_PROTO(IPTR, DispatchScrollerGadget, CLASS, object, message);
#define pScroller_DATA_SIZE (sizeof(struct ScrollerGData))


/*** Library startup and shutdown *******************************************/
static int BOOPSI_pScroller_Startup(LIBBASETYPEPTR LIBBASE)
{
    struct IClass *cl = NULL;
    
    cl = MakeClass("pinc-scrollergadget", PROPGCLASS, NULL, pScroller_DATA_SIZE, 0);
    if (cl != NULL)
    {
#if pScroller_STORE_CLASSPTR
        pScroller_CLASSPTR_FIELD(LIBBASE) = cl;
#endif
        cl->cl_Dispatcher.h_Entry = (APTR)DispatchScrollerGadget;
        cl->cl_Dispatcher.h_SubEntry = NULL;
        cl->cl_UserData = (IPTR)LIBBASE
;
        AddClass(cl);

        return TRUE;
    }
    else
        return FALSE;
}

static void BOOPSI_pScroller_Shutdown(LIBBASETYPEPTR LIBBASE)
{
    struct IClass *cl = pScroller_CLASSPTR_FIELD(LIBBASE);
    
    if (cl != NULL)
    {
        RemoveClass(cl);
        FreeClass(cl);
#if pScroller_STORE_CLASSPTR
        pScroller_CLASSPTR_FIELD(LIBBASE) = NULL;
#endif
    }
}

ADD2INITCLASSES(BOOPSI_pScroller_Startup, -1);
ADD2EXPUNGECLASSES(BOOPSI_pScroller_Shutdown, -1);
/* Initialisation routines for a BOOPSI class */
/* ===========================================*/



/*** Custom dispatcher prototype ********************************************/
BOOPSI_DISPATCHER_PROTO(IPTR, DispatchArrowImage, CLASS, object, message);
#define pArrow_DATA_SIZE (sizeof(struct ArrowIData))


/*** Library startup and shutdown *******************************************/
static int BOOPSI_pArrow_Startup(LIBBASETYPEPTR LIBBASE)
{
    struct IClass *cl = NULL;
    
    cl = MakeClass("pinc-arrowimage", IMAGECLASS, NULL, pArrow_DATA_SIZE, 0);
    if (cl != NULL)
    {
#if pArrow_STORE_CLASSPTR
        pArrow_CLASSPTR_FIELD(LIBBASE) = cl;
#endif
        cl->cl_Dispatcher.h_Entry = (APTR)DispatchArrowImage;
        cl->cl_Dispatcher.h_SubEntry = NULL;
        cl->cl_UserData = (IPTR)LIBBASE
;
        AddClass(cl);

        return TRUE;
    }
    else
        return FALSE;
}

static void BOOPSI_pArrow_Shutdown(LIBBASETYPEPTR LIBBASE)
{
    struct IClass *cl = pArrow_CLASSPTR_FIELD(LIBBASE);
    
    if (cl != NULL)
    {
        RemoveClass(cl);
        FreeClass(cl);
#if pArrow_STORE_CLASSPTR
        pArrow_CLASSPTR_FIELD(LIBBASE) = NULL;
#endif
    }
}

ADD2INITCLASSES(BOOPSI_pArrow_Startup, -1);
ADD2EXPUNGECLASSES(BOOPSI_pArrow_Shutdown, -1);
