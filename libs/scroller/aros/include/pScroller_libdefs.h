#ifndef _PSCROLLER_LIBDEFS_H
#define _PSCROLLER_LIBDEFS_H

#include <exec/types.h>

#define GM_UNIQUENAME(n) pScroller_ ## n
#define LIBBASE          pScrollerBase
#define LIBBASETYPE      struct ClassBase
#define LIBBASETYPEPTR   struct ClassBase *
#define MOD_NAME_STRING  "pScroller.gadget"
#define VERSION_NUMBER   0
#define MAJOR_VERSION    0
#define REVISION_NUMBER  2
#define MINOR_VERSION    2
#define VERSION_STRING   "pScroller.gadget 0.2 (23.9.2000) Copyright (C) 1999-2008 pinc Software\r\n"
#define COPYRIGHT_STRING "Copyright (C) 1999-2008 pinc Software"
#define LIBEND           GM_UNIQUENAME(End)
#define LIBFUNCTABLE     GM_UNIQUENAME(FuncTable)
#define RESIDENTPRI      0
#define RESIDENTFLAGS    RTF_COLDSTART|RTF_AUTOINIT
#include "Scroller_includes.h"
extern struct IClass *pscrollervar;
extern struct IClass *parrowvar;
#define pScroller_STORE_CLASSPTR 1
#define GM_CLASSPTR_FIELD(lh) (pscrollervar)
#define pScroller_CLASSPTR_FIELD(lh) (pscrollervar)
#define pArrow_STORE_CLASSPTR 1
#define pArrow_CLASSPTR_FIELD(lh) (parrowvar)

#endif /* _PSCROLLER_LIBDEFS_H */
