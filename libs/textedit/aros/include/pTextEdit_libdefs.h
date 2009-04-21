#ifndef _PTEXTEDIT_LIBDEFS_H
#define _PTEXTEDIT_LIBDEFS_H

#include <exec/types.h>

#define GM_UNIQUENAME(n) pTextEdit_ ## n
#define LIBBASE          TextEditBase
#define LIBBASETYPE      struct ClassBase
#define LIBBASETYPEPTR   struct ClassBase *
#define MOD_NAME_STRING  "pTextEdit.gadget"
#define VERSION_NUMBER   1
#define MAJOR_VERSION    1
#define REVISION_NUMBER  4
#define MINOR_VERSION    4
#define VERSION_STRING   "pTextEdit.gadget 1.4 (12.8.2006)\r\n"
#define COPYRIGHT_STRING ""
#define LIBEND           GM_UNIQUENAME(End)
#define LIBFUNCTABLE     GM_UNIQUENAME(FuncTable)
#define RESIDENTPRI      0
#define RESIDENTFLAGS    RTF_COLDSTART|RTF_AUTOINIT
#include "TextEdit_includes.h"
#include "TextEdit_private.h"
struct Class *ptexteditvar;
#define pTextEdit_STORE_CLASSPTR 1
#define GM_CLASSPTR_FIELD(lh) (ptexteditvar)
#define pTextEdit_CLASSPTR_FIELD(lh) (ptexteditvar)

#endif /* _PTEXTEDIT_LIBDEFS_H */
