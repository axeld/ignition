#ifndef PROTO_PTEXTEDIT_H
#define PROTO_PTEXTEDIT_H

/*
    *** Automatically generated from '/home/mazze/projects/AROS/local/ignition/libs/textedit/pTextEdit.conf'. Edits will be lost. ***
    Copyright © 1995-2009, The AROS Development Team. All rights reserved.
*/

#include <exec/types.h>
#include <aros/system.h>

#include <clib/pTextEdit_protos.h>

#if !defined(TextEditBase) && !defined(__NOLIBBASE__) && !defined(__PTEXTEDIT_NOLIBBASE__)
 #ifdef __PTEXTEDIT_STDLIBBASE__
  extern struct Library *TextEditBase;
 #else
  extern struct Library *TextEditBase;
 #endif
#endif

#if !defined(NOLIBDEFINES) && !defined(PTEXTEDIT_NOLIBDEFINES)
#   include <defines/pTextEdit.h>
#endif

#endif /* PROTO_PTEXTEDIT_H */
