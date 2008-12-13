/*
 * Copyright ©1999-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the MIT License.
 */

//!	AROS init functions.


#include "Scroller_includes.h"

#include <aros/symbolsets.h>

struct IClass *pscrollervar;
struct IClass *parrowvar;

int SC_Init(struct ClassBase *cb)
{
  cb->cb_ScrollerClass = pscrollervar;
  cb->cb_ArrowClass = parrowvar;
  return TRUE;
}

ADD2OPENLIB(SC_Init, 0);
