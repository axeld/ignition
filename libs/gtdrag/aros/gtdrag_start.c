/*
    *** Automatically generated from '/home/mazze/projects/AROS/local/ignition/libs/gtdrag/gtdrag.conf'. Edits will be lost. ***
    Copyright © 1995-2009, The AROS Development Team. All rights reserved.
*/
#include <exec/types.h>
#include <exec/libraries.h>
#include <exec/resident.h>
#include <aros/libcall.h>
#include <aros/asmcall.h>
#include <aros/symbolsets.h>
#include <dos/dos.h>

#include "gtdrag_libdefs.h"

#ifdef SysBase
#undef SysBase
#endif

#include <proto/exec.h>
#include <proto/alib.h>
#ifndef __AROS__
struct ExecBase *SysBase = NULL;
#endif

#include <exec/exec.h>
#include <utility/utility.h>
#include <intuition/intuition.h>
#include <intuition/gadgetclass.h>
#include <libraries/gtdrag.h>
#ifndef GM_SEGLIST_FIELD
static BPTR GM_UNIQUENAME(seglist);
#define GM_SEGLIST_FIELD(lh) (GM_UNIQUENAME(seglist))
#endif
#define LIBBASESIZE sizeof(LIBBASETYPE)
AROS_LD1(struct IntuiMessage *, GTD_GetIMsg,
         AROS_LDA(struct MsgPort *, mp, A0),
         LIBBASETYPEPTR, GTDragBase, 5, Gtdrag
);
AROS_LD1(void, GTD_ReplyIMsg,
         AROS_LDA(struct IntuiMessage *, msg, A0),
         LIBBASETYPEPTR, GTDragBase, 6, Gtdrag
);
AROS_LD1(struct IntuiMessage *, GTD_FilterIMsg,
         AROS_LDA(struct IntuiMessage *, msg, A0),
         LIBBASETYPEPTR, GTDragBase, 7, Gtdrag
);
AROS_LD1(struct IntuiMessage *, GTD_PostFilterIMsg,
         AROS_LDA(struct IntuiMessage *, msg, A0),
         LIBBASETYPEPTR, GTDragBase, 8, Gtdrag
);
AROS_LD2(int, GTD_AddAppA,
         AROS_LDA(STRPTR, t, A0),
         AROS_LDA(struct TagItem *, tag, A1),
         LIBBASETYPEPTR, GTDragBase, 11, Gtdrag
);
AROS_LD0(void, GTD_RemoveApp,
         LIBBASETYPEPTR, GTDragBase, 12, Gtdrag
);
AROS_LD2(void, GTD_AddWindowA,
         AROS_LDA(struct Window *, win, A0),
         AROS_LDA(struct TagItem *, tag, A1),
         LIBBASETYPEPTR, GTDragBase, 13, Gtdrag
);
AROS_LD1(void, GTD_RemoveWindow,
         AROS_LDA(struct Window *, win, A0),
         LIBBASETYPEPTR, GTDragBase, 14, Gtdrag
);
AROS_LD4(void, GTD_AddGadgetA,
         AROS_LDA(ULONG, type, D0),
         AROS_LDA(struct Gadget *, gad, A0),
         AROS_LDA(struct Window *, win, A1),
         AROS_LDA(struct TagItem *, tag, A2),
         LIBBASETYPEPTR, GTDragBase, 15, Gtdrag
);
AROS_LD1(void, GTD_RemoveGadget,
         AROS_LDA(struct Gadget *, gad, A0),
         LIBBASETYPEPTR, GTDragBase, 16, Gtdrag
);
AROS_LD1(void, GTD_RemoveGadgets,
         AROS_LDA(struct Window *, win, A0),
         LIBBASETYPEPTR, GTDragBase, 17, Gtdrag
);
AROS_LD2(void, GTD_SetAttrsA,
         AROS_LDA(APTR, gad, A0),
         AROS_LDA(struct TagItem *, tags, A1),
         LIBBASETYPEPTR, GTDragBase, 18, Gtdrag
);
AROS_LD3(BOOL, GTD_GetAttr,
         AROS_LDA(APTR, gad, A0),
         AROS_LDA(ULONG, tag, D0),
         AROS_LDA(ULONG *, storage, A1),
         LIBBASETYPEPTR, GTDragBase, 19, Gtdrag
);
AROS_LD1(struct Hook *, GTD_GetHook,
         AROS_LDA(ULONG, type, D0),
         LIBBASETYPEPTR, GTDragBase, 20, Gtdrag
);
AROS_LD3(STRPTR, GTD_GetString,
         AROS_LDA(struct ObjectDescription *, od, A0),
         AROS_LDA(STRPTR, buf, D1),
         AROS_LDA(LONG, len, D0),
         LIBBASETYPEPTR, GTDragBase, 21, Gtdrag
);
AROS_LD2(BOOL, GTD_PrepareDrag,
         AROS_LDA(struct Gadget *, gad, A0),
         AROS_LDA(struct gpInput *, gpi, A1),
         LIBBASETYPEPTR, GTDragBase, 22, Gtdrag
);
AROS_LD2(BOOL, GTD_BeginDrag,
         AROS_LDA(struct Gadget *, gad, A0),
         AROS_LDA(struct gpInput *, gpi, A1),
         LIBBASETYPEPTR, GTDragBase, 23, Gtdrag
);
AROS_LD2(ULONG, GTD_HandleInput,
         AROS_LDA(struct Gadget *, gad, A0),
         AROS_LDA(struct gpInput *, gpi, A1),
         LIBBASETYPEPTR, GTDragBase, 24, Gtdrag
);
AROS_LD1(void, GTD_StopDrag,
         AROS_LDA(struct Gadget *, gad, A0),
         LIBBASETYPEPTR, GTDragBase, 25, Gtdrag
);
AROS_LD2(void, FreeTreeList,
         AROS_LDA(APTR, pool, A0),
         AROS_LDA(struct TreeList *, tl, A1),
         LIBBASETYPEPTR, GTDragBase, 26, Gtdrag
);
AROS_LD1(void, InitTreeList,
         AROS_LDA(struct TreeList *, tl, A0),
         LIBBASETYPEPTR, GTDragBase, 27, Gtdrag
);
AROS_LD2(void, FreeTreeNodes,
         AROS_LDA(APTR, pool, A0),
         AROS_LDA(struct MinList *, list, A1),
         LIBBASETYPEPTR, GTDragBase, 28, Gtdrag
);
AROS_LD5(struct TreeNode *, AddTreeNode,
         AROS_LDA(APTR, pool, A0),
         AROS_LDA(struct MinList *, tree, A1),
         AROS_LDA(STRPTR, name, A2),
         AROS_LDA(struct Image *, im, A3),
         AROS_LDA(UWORD, flags, D0),
         LIBBASETYPEPTR, GTDragBase, 29, Gtdrag
);
AROS_LD2(void, CloseTreeNode,
         AROS_LDA(struct MinList *, main, A0),
         AROS_LDA(struct TreeNode *, tn, A1),
         LIBBASETYPEPTR, GTDragBase, 30, Gtdrag
);
AROS_LD2(LONG, OpenTreeNode,
         AROS_LDA(struct MinList *, main, A0),
         AROS_LDA(struct TreeNode *, tn, A1),
         LIBBASETYPEPTR, GTDragBase, 31, Gtdrag
);
AROS_LD2(LONG, ToggleTreeNode,
         AROS_LDA(struct MinList *, main, A0),
         AROS_LDA(struct TreeNode *, tn, A1),
         LIBBASETYPEPTR, GTDragBase, 32, Gtdrag
);
AROS_LD1(struct TreeNode *, GetTreeContainer,
         AROS_LDA(struct TreeNode *, tn, A0),
         LIBBASETYPEPTR, GTDragBase, 33, Gtdrag
);
AROS_LD3(STRPTR, GetTreePath,
         AROS_LDA(struct TreeNode *, tn, A0),
         AROS_LDA(STRPTR, buffer, A1),
         AROS_LDA(LONG, len, D0),
         LIBBASETYPEPTR, GTDragBase, 34, Gtdrag
);
AROS_LD2(struct TreeNode *, FindTreePath,
         AROS_LDA(struct MinList *, tree, A0),
         AROS_LDA(STRPTR, path, A1),
         LIBBASETYPEPTR, GTDragBase, 35, Gtdrag
);
AROS_LD2(struct TreeNode *, FindTreeSpecial,
         AROS_LDA(struct MinList *, tree, A0),
         AROS_LDA(APTR, special, A1),
         LIBBASETYPEPTR, GTDragBase, 36, Gtdrag
);
AROS_LD2(struct TreeNode *, FindListSpecial,
         AROS_LDA(struct MinList *, list, A0),
         AROS_LDA(APTR, special, A1),
         LIBBASETYPEPTR, GTDragBase, 37, Gtdrag
);
AROS_LD3(BOOL, ToggleTree,
         AROS_LDA(struct Gadget *, gad, A0),
         AROS_LDA(struct TreeNode *, tn, A1),
         AROS_LDA(struct IntuiMessage *, msg, A2),
         LIBBASETYPEPTR, GTDragBase, 38, Gtdrag
);

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
    LIBBASETYPEPTR, lh, 3, Gtdrag
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
    if (set_open_libraries() && set_call_funcs(SETNAME(INIT), 1, 1) )
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
    LIBBASETYPEPTR, lh, 1, Gtdrag
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
    LIBBASETYPEPTR, lh, 2, Gtdrag
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
                   LIBBASETYPEPTR, lh, 3, Gtdrag
        );
    }

    return NULL;

    AROS_LIBFUNC_EXIT
}

AROS_LH1 (BPTR, GM_UNIQUENAME(ExpungeLib),
    AROS_LHA(LIBBASETYPEPTR, extralh, D0),
    LIBBASETYPEPTR, lh, 3, Gtdrag
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
        set_close_libraries();

        __freebase(lh);

        return seglist;
    }

    ((struct Library *)lh)->lib_Flags |= LIBF_DELEXP;

    return NULL;

    AROS_LIBFUNC_EXIT
}

AROS_LH0 (LIBBASETYPEPTR, GM_UNIQUENAME(ExtFuncLib),
    LIBBASETYPEPTR, lh, 4, Gtdrag
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


const APTR GM_UNIQUENAME(FuncTable)[]=
{
    &AROS_SLIB_ENTRY(GM_UNIQUENAME(OpenLib),Gtdrag),
    &AROS_SLIB_ENTRY(GM_UNIQUENAME(CloseLib),Gtdrag),
    &AROS_SLIB_ENTRY(GM_UNIQUENAME(ExpungeLib),Gtdrag),
    &AROS_SLIB_ENTRY(GM_UNIQUENAME(ExtFuncLib),Gtdrag),
    &AROS_SLIB_ENTRY(GTD_GetIMsg,Gtdrag),
    &AROS_SLIB_ENTRY(GTD_ReplyIMsg,Gtdrag),
    &AROS_SLIB_ENTRY(GTD_FilterIMsg,Gtdrag),
    &AROS_SLIB_ENTRY(GTD_PostFilterIMsg,Gtdrag),
    NULL,
    NULL,
    &AROS_SLIB_ENTRY(GTD_AddAppA,Gtdrag),
    &AROS_SLIB_ENTRY(GTD_RemoveApp,Gtdrag),
    &AROS_SLIB_ENTRY(GTD_AddWindowA,Gtdrag),
    &AROS_SLIB_ENTRY(GTD_RemoveWindow,Gtdrag),
    &AROS_SLIB_ENTRY(GTD_AddGadgetA,Gtdrag),
    &AROS_SLIB_ENTRY(GTD_RemoveGadget,Gtdrag),
    &AROS_SLIB_ENTRY(GTD_RemoveGadgets,Gtdrag),
    &AROS_SLIB_ENTRY(GTD_SetAttrsA,Gtdrag),
    &AROS_SLIB_ENTRY(GTD_GetAttr,Gtdrag),
    &AROS_SLIB_ENTRY(GTD_GetHook,Gtdrag),
    &AROS_SLIB_ENTRY(GTD_GetString,Gtdrag),
    &AROS_SLIB_ENTRY(GTD_PrepareDrag,Gtdrag),
    &AROS_SLIB_ENTRY(GTD_BeginDrag,Gtdrag),
    &AROS_SLIB_ENTRY(GTD_HandleInput,Gtdrag),
    &AROS_SLIB_ENTRY(GTD_StopDrag,Gtdrag),
    &AROS_SLIB_ENTRY(FreeTreeList,Gtdrag),
    &AROS_SLIB_ENTRY(InitTreeList,Gtdrag),
    &AROS_SLIB_ENTRY(FreeTreeNodes,Gtdrag),
    &AROS_SLIB_ENTRY(AddTreeNode,Gtdrag),
    &AROS_SLIB_ENTRY(CloseTreeNode,Gtdrag),
    &AROS_SLIB_ENTRY(OpenTreeNode,Gtdrag),
    &AROS_SLIB_ENTRY(ToggleTreeNode,Gtdrag),
    &AROS_SLIB_ENTRY(GetTreeContainer,Gtdrag),
    &AROS_SLIB_ENTRY(GetTreePath,Gtdrag),
    &AROS_SLIB_ENTRY(FindTreePath,Gtdrag),
    &AROS_SLIB_ENTRY(FindTreeSpecial,Gtdrag),
    &AROS_SLIB_ENTRY(FindListSpecial,Gtdrag),
    &AROS_SLIB_ENTRY(ToggleTree,Gtdrag),
    (void *)-1
};
