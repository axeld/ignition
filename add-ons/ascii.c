/* ignition ASCII-I/O-Module
 *
 * Copyright �1996-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the GNU General Public License, version 3.
 */


#include <stdlib.h>
#include "iotype.h"


const STRPTR __version = "$VER: ascii.io 0.1 (5.3.2001)";

#ifdef DEBUG
	void kprintf(STRPTR,...);
#	define bug kprintf
#endif


void PUBLIC
closePrefsGUI(void)
{
}


void PUBLIC
openPrefsGUI(reg (a0) struct Screen *src)
{
}


STRPTR PUBLIC
getPrefs(void)
{
	return NULL;
}


long PUBLIC
setPrefs(reg (a0) STRPTR t)
{
	return TRUE;
}


long PUBLIC
load(reg (d0) BPTR file,reg (a0) struct Mappe *mp)
{
	struct Page *page;
	struct Cell *c;
	char t[512];
	ULONG row = 1;

	if (page = NewPage(mp)) {
		while (FGets(file, t, 512)) {
			if (c = NewCell(page,1,row++)) {
				if (t[strlen(t)-1] == '\n')
					t[strlen(t)-1] = 0;
				c->c_Text = AllocString(t);

				UpdateCellText(page,c);
			}
		}
	}
	return RETURN_OK;
}


long PUBLIC
save(reg (d0) BPTR file,reg (a0) struct Mappe *mp)
{
	struct Page *page;
	struct Cell *c;
	ULONG row = 1;

	foreach(&mp->mp_Pages, page) {
		foreach(&page->pg_Table, c) {
			if (c->c_Text) {
				FPuts(file, c->c_Text);
				FPutC(file, '\n');
				row = c->c_Row;
			} else while(row < c->c_Row) {
				FPutC(file,'\n');
				row++;
			}
		}
	}
	return RETURN_OK;
}


void __stdargs
_XCEXIT(long a)
{
}


