/*
    *** Automatically generated from '/home/mazze/projects/AROS/local/ignition/libs/textedit/pTextEdit.conf'. Edits will be lost. ***
    Copyright © 1995-2009, The AROS Development Team. All rights reserved.
*/
#define NOLIBDEFINES
/* Be sure that the libbases are included in the stubs file */
#undef __NOLIBBASE__
#undef __PTEXTEDIT_NOLIBBASE__
#include <proto/pTextEdit.h>
#include <exec/types.h>
#include <aros/libcall.h>


void Text2Clipboard(UBYTE clipunit, STRPTR t, LONG len)
{
    return AROS_LC3NR(void, Text2Clipboard,
                    AROS_LCA(UBYTE,clipunit,D0),
                    AROS_LCA(STRPTR,t,A0),
                    AROS_LCA(LONG,len,D1),
                    struct Library *, TextEditBase, 5, pTextEdit);
}

STRPTR TextFromClipboard(UBYTE clipunit, APTR pool)
{
    return AROS_LC2(STRPTR, TextFromClipboard,
                    AROS_LCA(UBYTE,clipunit,D0),
                    AROS_LCA(APTR,pool,A0),
                    struct Library *, TextEditBase, 6, pTextEdit);
}

void FreeEditList(struct EditGData *ed)
{
    return AROS_LC1NR(void, FreeEditList,
                    AROS_LCA(struct EditGData *,ed,A0),
                    struct Library *, TextEditBase, 7, pTextEdit);
}

void PrepareEditText(struct EditGData *ed, struct RastPort *rp, STRPTR t)
{
    return AROS_LC3NR(void, PrepareEditText,
                    AROS_LCA(struct EditGData *,ed,A0),
                    AROS_LCA(struct RastPort *,rp,A1),
                    AROS_LCA(STRPTR,t,A2),
                    struct Library *, TextEditBase, 8, pTextEdit);
}
