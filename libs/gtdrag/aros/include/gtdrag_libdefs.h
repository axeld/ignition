#ifndef _GTDRAG_LIBDEFS_H
#define _GTDRAG_LIBDEFS_H

#include <exec/types.h>

#define GM_UNIQUENAME(n) Gtdrag_ ## n
#define LIBBASE          GTDragBase
#define LIBBASETYPE      struct Library
#define LIBBASETYPEPTR   struct Library *
#define MOD_NAME_STRING  "gtdrag.library"
#define VERSION_NUMBER   3
#define MAJOR_VERSION    3
#define REVISION_NUMBER  6
#define MINOR_VERSION    6
#define VERSION_STRING   "gtdrag.library 3.6 (12.8.2003) Copyright (C) 1999-2008 pinc Software\r\n"
#define COPYRIGHT_STRING "Copyright (C) 1999-2008 pinc Software"
#define LIBEND           GM_UNIQUENAME(End)
#define LIBFUNCTABLE     GM_UNIQUENAME(FuncTable)
#define RESIDENTPRI      0
#define RESIDENTFLAGS    RTF_COLDSTART|RTF_AUTOINIT
#include "gtdrag_includes.h"

#endif /* _GTDRAG_LIBDEFS_H */
