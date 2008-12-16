/* ignition TurboCalc-I/O-Module
 *
 * Copyright ©1996-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the GNU General Public License, version 3.
 */

#include "iotype.h"
#include "turbocalc.h"

extern APTR ioBase;


const STRPTR __version = "$VER: turbocalc.io 0.2 (4.3.2001)";

/*extern sprintf(STRPTR,STRPTR,...);*/
extern kprintf(STRPTR,...);

#define bug kprintf
#define D(x) ;

STRPTR
MapTCFuncs(UBYTE n)
{
	switch (n) {
		case 0x1a: return("abs");
		case 0x11: return("arccos");
		case 0x16: return("auswahl");
		case 0x4a: return("anzahl");
		case 37: return("mittelwert");
		case 78: return("summe");
		default: return("nop");
	}
	return NULL;
}


void
ConvertTCFormula(struct Cell *c,STRPTR t,long len)
{
	long i = 0,col,row;
	BYTE a,b;
	STRPTR dest;

	if (dest = AllocPooled(pool,len*2)) {
		for(;i < len;i++) {
			if (*(t+i) >= 0x08 && *(t+i) <= 0x0b) {
				/* relative & absolute references */
				col = *(WORD *)(t+i+1);	row = *(WORD *)(t+i+3);	i += 4;
				a = *(t+i) == 0x0a || *(t+i) == 0x08;
				b = *(t+i) == 0x09 || *(t+i) == 0x08;
				strcat(dest,Coord2String(a,(a ? 0 : c->c_Col)+col,b,(b ? 0 : c->c_Row)+row));
			} else if (*(t+i) == 0x04) {
				/* Function */
				if (MapTCFuncs(*(t+ ++i)))
					strcat(dest,MapTCFuncs(*(t+i)));
			} else if (*(t+i) < ' ') {
				D(bug("unknown: %ld\n",*(t+i)));
				break;
			} else {
				/* standard text */
				dest[strlen(dest)] = *(t+i);
			}
		}
		if (c->c_Text) {
			// bug("ctcf: old text: '%s'\n",c->c_Text);
			FreeString(c->c_Text);
		}
		c->c_Text = AllocString(dest);
		FreePooled(pool,dest,len*2);
	}
}


long PUBLIC
load(REG(d0, BPTR dat), REG(a0, struct Mappe *mp))
{
	struct Cell *c;
	struct Page *page;
	struct THeader th;
	struct TCell *tc;
	APTR buf = NULL;
	ULONG len = 0,size,l,col,row,*cols;
	char t[32];
	double d;
	UWORD w;
	UBYTE b,*cell,ieeemode,r,g;

	page = NewPage(mp);
	while (FRead(dat,&th,sizeof(struct THeader),1)) {
		size = (th.th_Size[0] << 16)+th.th_Size[1];
		if (len < size) {
			if (buf && len)
				FreePooled(pool,buf,len);
			buf = AllocPooled(pool,len = size);
		}
		if (buf) {
			// bug("Type: %ld - Chunklänge: %ld\n",th.th_Type,size);
			FRead(dat,buf,size,1);
			switch (th.th_Type) {
				case FILE_START:
					ieeemode = *((UBYTE *)buf+11);
					break;
				case FILE_END:
					D(bug("	Dateiende.\n"));
					break;
				/*case FILE_VERSION:
					if (((struct TVersion *)buf)->tv_Version > TC_VERSION || ((struct TVersion *)buf)->tv_Version == TC_VERSION&& ((struct TVersion *)buf)->tv_Revision > TC4_REVISION)
						ErrorRequest("Warnung!\nDas Dateiformat ist neuer als das bekannte.");
					break;*/
				case FILE_PASSWORD:
					D(bug("	Passwort.\n"));
					break;
				case FILE_OPT0:
					D(bug("	Optionen-0.\n"));
					break;
				case FILE_OPT1:
					D(bug("	Optionen-1.\n"));
					break;
				case FILE_WIDTH:
					l = *(ULONG *)(cell = buf);	w = *(UWORD *)(cell+4);
					SetTableSize(page,l+1,0);
					(page->pg_tfWidth+l)->ts_Pixel = w;
					(page->pg_tfWidth+l)->ts_mm = mm(page,w,TRUE);
					break;
				case FILE_HEIGHT:
					l = *(ULONG *)(cell = buf);	w = *(UWORD *)(cell+4);
					SetTableSize(page,0,l+1);
					(page->pg_tfHeight+l)->ts_Pixel = w;
					(page->pg_tfHeight+l)->ts_mm = mm(page,w,FALSE);
					break;
				case FILE_CELL:
				case FILE_LCELL:
					cell = buf;
					if (th.th_Type == FILE_CELL)
						col = *(UWORD *)cell, row = *(UWORD *)(cell+2), cell += 4;
					else
						col = *(ULONG *)cell, row = *(ULONG *)(cell+4), cell += 8;
					if (c = NewCell(page,col+1,row+1))
					{
						b = *cell++;
						if (b == TCT_TEXT)
						{
							w = *(UWORD *)cell;	cell += 2;
							c->c_Text = AllocStringLength(cell,w);
							cell += w;
						}
						else if (b != TCT_EMPTY)
						{
							if (/*ieeemode &&*/ b == TCT_FLOAT)
								cell += 4;
							d = *(double *)cell;
							l = *(long *)cell;
							cell += 8;
						}
						switch(b)
						{
							case TCT_TIME:
								sprintf(t,"%ld:%02ld:%02ld",l/3600,(l/60) % 60,l % 60);
								c->c_Text = AllocString(t);
								break;
							case TCT_FLOAT:
								c->c_Text = AllocString(ita(d,-1,ITA_NONE));
								break;
							case TCT_INT:
								sprintf(t,"%ld",l);
								c->c_Text = AllocString(t);
								break;
							case TCT_DATE:
								D(bug("date: %ld\n",l));
								break;
						}
						D(bug("Celltext: %s\n",c->c_Text));
						if (b != TCT_EMPTY)
						{
							w = *(UWORD *)cell;	cell += 2;
							ConvertTCFormula(c,cell,w);
							cell += w;
						}
						tc = (struct TCell *)cell;
						col = FindColorPen(0,0,0);
						for(row = 0;row < 4;row++)
							c->c_BorderColor[row] = col;
						c->c_APen = c->c_ReservedPen = tc->tc_Color1 & TC_COLOR_MASK;
						c->c_BPen = tc->tc_Color0 & TC_COLOR_MASK;
						if (tc->tc_Border & TC_BORDER_LEFT)
							c->c_Border[0] = (tc->tc_Border & TC_BORDER_LEFT) << 3;
						if (tc->tc_Border & TC_BORDER_RIGHT)
							c->c_Border[1] = (tc->tc_Border & TC_BORDER_RIGHT);
						if (tc->tc_Border & TC_BORDER_DOWN)
							c->c_Border[2] = (tc->tc_Border & TC_BORDER_DOWN) >> 6;
						if (tc->tc_Border & TC_BORDER_UP)
							c->c_Border[3] = (tc->tc_Border & TC_BORDER_UP) >> 3;
						/*if (tc->tc_Font & TC_STYLE_MASK)
							c->c_Style = ((tc->tc_Font & (1 << TC_STYLE_ITALIC)) ? FS_ITALIC : 0) |
														 ((tc->tc_Font & (1 << TC_STYLE_BOLD)) ? FS_BOLD : 0) |
														 ((tc->tc_Font & (1 << TC_STYLE_UNDERLINED)) ? FS_UNDERLINED : 0);*/
					}
					break;
				case FILE_NAME:
					w = *(UWORD *)(cell = buf);	cell += 2;
					D(bug("	Name: %s\n",cell));
					/* to be implemented... */
					break;
				case FILE_OPT2:
					D(bug("	Optionen-2.\n"));
					break;
				case FILE_WINDOW:
					D(bug("	Window.\n"));
					break;
				case FILE_FONTS:
					D(bug("	Fonts.\n"));
					break;
				/*case FILE_SCREEN:
					D(bug("	Screen.\n"));
					break;*/
				case FILE_COLOR:
					w = *(UWORD *)(cell = buf);
					if (cols = AllocPooled(pool,w*4+4))
					{
						struct colorPen *cp;

						*cols = w*4+4;
						for(cell += 2,col = 1;w;w--,cell += 2,col++)
						{
							row = *(UWORD *)cell;
							r = ((row & 0x0f00) >> 8) | ((row & 0x0f00) >> 4);
							g = ((row & 0x00f0) >> 4) | (row & 0x00f0);
							b = ((row & 0x000f) << 4) | (row & 0x000f);
							if (cp = AddPen(NULL,r,g,b))
								cols[col] = cp->cp_ID;
							else
								cols[col] = NULL;
						}
					}
					break;
				case FILE_DIAGRAM:
					D(bug("	Diagram.\n"));
					break;
				case FILE_STDFONTS:
					D(bug("	Std-Fonts.\n"));
					break;
				case FILE_PATTERNS:
					D(bug("	Patterns.\n"));
					break;
				case FILE_COLUMNFLAGS:
					D(bug("	Column-Flags.\n"));
					break;
				case FILE_ROWFLAGS:
					D(bug("	Row-Flags.\n"));
					break;
				/*case FILE_SHEETSIZE:
					D(bug("	Sheet-Size.\n"));
					break;*/
				case FILE_SYSTEMFONTS:
					D(bug("	System-Fonts.\n"));
					break;
				/*case FILE_FROZEN:
					D(bug("	Frozen.\n"));
					break;*/
				/*case FILE_SAVEOPT:
					D(bug("	Save-Options.\n"));
					break;*/
				case FILE_CRYPT:
					D(bug("	Crypt.\n"));
					break;
				case FILE_DIAGRAM2:
					D(bug("	Diagram-2.\n"));
					break;
				case FILE_GLOBALFLAGS:
					D(bug("	Global-Flags.\n"));
					break;
				case FILE_OBJECT:
					D(bug("	Object.\n"));
					break;
				case FILE_STDCHART:
					D(bug("	Std-Chart.\n"));
					break;
				case FILE_OPT3:
					D(bug("	Optionen-3.\n"));
					break;
				case FILE_LASTFILES:
					D(bug("	Lastfiles.\n"));
					break;
				case FILE_CURSOR:
					D(bug("	Cursor.\n"));
					break;
				case FILE_STARTUPOPTIONS:
					D(bug("	Startup-Options.\n"));
					break;
				case FILE_TURBOCALCOWNER:
					D(bug("	TC-Owner.\n"));
					break;
				case FILE_FILEINFO:
					D(bug("	File-Info.\n"));
					break;
				default:
					D(bug("	UNKNOWN (%ld).\n",th.th_Type));
					break;
			}
		}
	}
	if (buf && len)
		FreePooled(pool,buf,len);
	if (cols) {
		foreach (&mp->mp_Pages,page) {
			foreach(&page->pg_Table,c) {
				if (c->c_APen)
					c->c_APen = c->c_ReservedPen = cols[c->c_APen];
				else
					c->c_APen = c->c_ReservedPen = page->pg_APen;
				if (c->c_BPen)
					c->c_BPen = cols[c->c_BPen];
				else
					c->c_BPen = page->pg_BPen;
				UpdateCellText(page,c);
			}
		}
		FreePooled(pool,cols,*cols);
	}
	return RETURN_OK;
}


long PUBLIC
save(REG(d0, BPTR dat), REG(a0, struct Mappe *mp))
{
	return RETURN_WARN;
}


void PUBLIC
closePrefsGUI(void)
{
}


void PUBLIC
openPrefsGUI(REG(a0, struct Screen *scr))
{
}


STRPTR PUBLIC
getPrefs(void)
{
	return NULL;
}


long PUBLIC
setPrefs(REG(a0, STRPTR t))
{
	return TRUE;
}


void __stdargs
_XCEXIT(void)
{
}

