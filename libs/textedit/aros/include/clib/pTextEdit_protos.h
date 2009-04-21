#ifndef CLIB_PTEXTEDIT_PROTOS_H
#define CLIB_PTEXTEDIT_PROTOS_H

/*
    *** Automatically generated from '/home/mazze/projects/AROS/local/ignition/libs/textedit/pTextEdit.conf'. Edits will be lost. ***
    Copyright © 1995-2009, The AROS Development Team. All rights reserved.
*/

#include <aros/libcall.h>
#include <gadgets/TextEdit.h>
struct EditGData;
AROS_LP3(void, Text2Clipboard,
         AROS_LPA(UBYTE, clipunit, D0),
         AROS_LPA(STRPTR, t, A0),
         AROS_LPA(LONG, len, D1),
         LIBBASETYPEPTR, TextEditBase, 5, pTextEdit
);
AROS_LP2(STRPTR, TextFromClipboard,
         AROS_LPA(UBYTE, clipunit, D0),
         AROS_LPA(APTR, pool, A0),
         LIBBASETYPEPTR, TextEditBase, 6, pTextEdit
);
AROS_LP1(void, FreeEditList,
         AROS_LPA(struct EditGData *, ed, A0),
         LIBBASETYPEPTR, TextEditBase, 7, pTextEdit
);
AROS_LP3(void, PrepareEditText,
         AROS_LPA(struct EditGData *, ed, A0),
         AROS_LPA(struct RastPort *, rp, A1),
         AROS_LPA(STRPTR, t, A2),
         LIBBASETYPEPTR, TextEditBase, 8, pTextEdit
);

#endif /* CLIB_PTEXTEDIT_PROTOS_H */
