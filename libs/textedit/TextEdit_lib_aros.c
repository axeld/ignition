/*
 * Copyright ©1999-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the MIT License.
 */

//!	library init functions for AROS.


#include "TextEdit_includes.h"

#include <aros/symbolsets.h>

struct IClass *ptexteditvar;
struct Library *TextEditBase;

int TE_LibInit(struct ClassBase *cb)
{
	TextEditBase = (struct Library *)cb;
	InitSemaphore(&cb->cb_LockSemaphore);
	return TRUE;
}

int TE_Init(struct ClassBase *cb)
{
	cb->cb_IFFParseBase = IFFParseBase;
	cb->cb_Class = ptexteditvar;
	cb->cb_Console.io_Message.mn_Length = sizeof(struct IOStdReq);
	if (!OpenDevice("console.device",-1,(struct IORequest *)&cb->cb_Console,0))
	    return TRUE;

	return FALSE;
}

void TE_Exit(struct ClassBase *cb)
{
	CloseLibrary(cb->cb_ScrollerBase);
	cb->cb_ScrollerBase = NULL;
	CloseDevice((struct IORequest *)&cb->cb_Console);
}

ADD2INITLIB(TE_LibInit, 0);
ADD2OPENLIB(TE_Init, 0);
ADD2CLOSELIB(TE_Exit, 0);
