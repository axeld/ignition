/* Implementation of variadic "library" functions
 *
 * Copyright ©1996-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the MIT License.
 */

#include "iotype.h"

void ReportError(STRPTR fmt, ...)
{
	ReportErrorA(fmt, &fmt + 1);
}
