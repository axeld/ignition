/* Implementation of variadic "library" functions
 *
 * Copyright ©1996-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the MIT License.
 */

#include "gclass_protos.h"

ULONG gDoMethod(APTR go, LONG data, ...)
{
	return gDoMethodA(go, &data);
}

ULONG gDoSuperMethod(struct gClass *gc, APTR go, LONG data, ...)
{
	return gDoSuperMethodA(gc, go, &data);
}

struct FontInfo *SetFontInfo(struct FontInfo *fi, ULONG dpi, ULONG tag1, ...)
{
	return SetFontInfoA(fi, dpi, &tag1);
}
