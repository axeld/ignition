#ifndef DEFINES_PTEXTEDIT_H
#define DEFINES_PTEXTEDIT_H

/*
    *** Automatically generated from '/home/mazze/projects/AROS/local/ignition/libs/textedit/pTextEdit.conf'. Edits will be lost. ***
    Copyright © 1995-2009, The AROS Development Team. All rights reserved.
*/

/*
    Desc: Defines for pTextEdit
*/

#include <aros/libcall.h>
#include <exec/types.h>
#include <aros/preprocessor/variadic/cast2iptr.hpp>


#define __Text2Clipboard_WB(__TextEditBase, __arg1, __arg2, __arg3) \
        AROS_LC3NR(void, Text2Clipboard, \
                  AROS_LCA(UBYTE,(__arg1),D0), \
                  AROS_LCA(STRPTR,(__arg2),A0), \
                  AROS_LCA(LONG,(__arg3),D1), \
        struct Library *, (__TextEditBase), 5, pTextEdit)

#define Text2Clipboard(arg1, arg2, arg3) \
    __Text2Clipboard_WB(TextEditBase, (arg1), (arg2), (arg3))

#define __TextFromClipboard_WB(__TextEditBase, __arg1, __arg2) \
        AROS_LC2(STRPTR, TextFromClipboard, \
                  AROS_LCA(UBYTE,(__arg1),D0), \
                  AROS_LCA(APTR,(__arg2),A0), \
        struct Library *, (__TextEditBase), 6, pTextEdit)

#define TextFromClipboard(arg1, arg2) \
    __TextFromClipboard_WB(TextEditBase, (arg1), (arg2))

#define __FreeEditList_WB(__TextEditBase, __arg1) \
        AROS_LC1NR(void, FreeEditList, \
                  AROS_LCA(struct EditGData *,(__arg1),A0), \
        struct Library *, (__TextEditBase), 7, pTextEdit)

#define FreeEditList(arg1) \
    __FreeEditList_WB(TextEditBase, (arg1))

#define __PrepareEditText_WB(__TextEditBase, __arg1, __arg2, __arg3) \
        AROS_LC3NR(void, PrepareEditText, \
                  AROS_LCA(struct EditGData *,(__arg1),A0), \
                  AROS_LCA(struct RastPort *,(__arg2),A1), \
                  AROS_LCA(STRPTR,(__arg3),A2), \
        struct Library *, (__TextEditBase), 8, pTextEdit)

#define PrepareEditText(arg1, arg2, arg3) \
    __PrepareEditText_WB(TextEditBase, (arg1), (arg2), (arg3))

#endif /* DEFINES_PTEXTEDIT_H*/
