/* ignition TurboCalc-I/O-Module
 *
 * Licensed under the terms of the GNU General Public License, version 3.
 */

#ifdef __amigaos4__
	#include <proto/exec.h>
	#include <proto/utility.h>
#else
	#include <stdio.h>
#endif

#include "iotype.h"
#include "turbocalc.h"


extern APTR ioBase;

#ifdef __amigaos4__
	#undef  strlen
	#define strlen  Strlen
#endif

const STRPTR __version = "$VER: turbocalc.io 0.3 (01.12.2014)";

#ifdef __amigaos4__
	#define bug DebugPrintF
	#define D(x) ;//x;
	//#define DEBUG_OS4 
#else
	/*extern sprintf(STRPTR,STRPTR,...);*/
	extern kprintf(STRPTR,...);

	#define bug kprintf
	#define D(x) ;
#endif

STRPTR
MapTCFuncs(UBYTE n)
{
	D(bug("MapTCFuncs: %02X\n", n));
	switch (n) {
		case 0x11: return("ACS");
		case 0x16: return("SEL");
		case 0x1a: return("ABS");
		case 0x25: return("AVG");
		//case 0x4a: return("anzahl");
		case 0x4b: return("MIN");
		case 0x4c: return("MAX");
		case 0x4e: return("sum");
		case 0x84: return("GCD");
		case 0xa0: return("THR");
		case 0xa1: return("TMN");
		case 0xa2: return("TSC");
		case 0x3d: return("YER");
		case 0x3e: return("DAY");
		case 0x3f: return("MON");
		case 0x7d: return("VAR");
		default:   return("NOP");
	}
	return NULL;
}


void
ConvertTCFormula(struct Cell *c,STRPTR t,long len)
{
	long i = 0,col,row;
	BYTE a,b;
	STRPTR dest;

	D(bug("ConvertTCFormula: <%s> len=%d\n", t, len));
	if ((dest = AllocPooled(pool, len * 2)) != 0) {
		for(;i < len;i++) {
			if (*(t+i) >= 0x08 && *(t+i) <= 0x0b) {
				/* relative & absolute references */
				col = *(WORD *)(t+i+1);	row = *(WORD *)(t+i+3);
				a = *(t+i) == 0x0a || *(t+i) == 0x08;
				b = *(t+i) == 0x09 || *(t+i) == 0x08;
				D(bug("col: %d row: %d\n", col, row));
				D(bug("Coord2String-Para: %d %d %d %d\n",a,(a ? 0 : c->c_Col)+col,b,(b ? 0 : c->c_Row)+row ));
#ifdef __amigaos4__
				Strlcat(dest,Coord2String(a,(a ? 1 : c->c_Col)+col,b,(b ? 1 : c->c_Row)+row), len * 2);
#else
				strcat(dest,Coord2String(a,(a ? 1 : c->c_Col)+col,b,(b ? 1 : c->c_Row)+row));
#endif
				i += 4;
			} else if (*(t+i) == 0x04) {
				/* Function */
				if (MapTCFuncs(*(t+ ++i)))
#ifdef __amigaos4__
					Strlcat(dest,MapTCFuncs(*(t+i)), len * 2);
#else
					strcat(dest,MapTCFuncs(*(t+i)));
#endif
			} else if (*(t+i) < ' ') {
				D(bug("unknown: %ld\n",*(t+i)));
				break;
			} else {
				/* standard text */
				dest[strlen(dest)] = *(t+i);
				D(bug("Text: <%s>\n", dest));
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
	UWORD cols_size = 0;
	UBYTE b,*cell,ieeemode,r,g;
	uint16 spos;//Stringstartposition der Strings in Dateiinfo
	char tabver[3] = {"XX\0"};
	struct ClockData cd;
	uint8 dateflag;    //TC date is under 1.1.1978

#ifdef __amigaos4__
	STRPTR sp;
	long i;
#endif

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
				case FILE_VERSION:
					//if (((struct TVersion *)buf)->tv_Version > TC_VERSION || ((struct TVersion *)buf)->tv_Version == TC_VERSION&& ((struct TVersion *)buf)->tv_Revision > TC4_REVISION)
					//	ReportError("Warnung!\nDas Dateiformat ist neuer als das bekannte. (%d / %d)", ((uint8 *)buf)[0], ((uint8 *)buf)[1]);
					break;
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
					D(bug("	File Width\n"));
					l = *(ULONG *)(cell = buf);	w = *(UWORD *)(cell+4);
					SetTableSize(page,l+1,0);
					(page->pg_tfWidth+l)->ts_Pixel = w;
					(page->pg_tfWidth+l)->ts_mm = mm(page,w,TRUE);
					break;
				case FILE_HEIGHT:
					D(bug("	File height\n"));
					l = *(ULONG *)(cell = buf);	w = *(UWORD *)(cell+4);
					SetTableSize(page,0,l+1);
					(page->pg_tfHeight+l)->ts_Pixel = w;
					(page->pg_tfHeight+l)->ts_mm = mm(page,w,FALSE);
					break;
				case FILE_CELL:
				case FILE_LCELL:
#ifdef DEBUG_OS4
					DebugPrintF("Type: %02d Size: %05d Data: ", th.th_Type, size);
					for(i = 0; i < size; i++)
						DebugPrintF("%02X ", ((uint8 *)buf)[i]);
					DebugPrintF("\n");
#endif
					cell = buf;
					if (th.th_Type == FILE_CELL)
						col = *(UWORD *)cell, row = *(UWORD *)(cell+2), cell += 4;
					else
						col = *(ULONG *)cell, row = *(ULONG *)(cell+4), cell += 8;
					if ((c = NewCell(page, col + 1,row + 1)) != 0)
					{
						b = *cell++;
						if (b == TCT_TEXT)
						{
							D(bug("TCT_TEXT\n"));
							w = *(UWORD *)cell;	cell += 2;
							c->c_Text = AllocStringLength(cell,w);
							cell += w;
							c->c_Type = CT_TEXT;
						}
						else if (b != TCT_EMPTY)
						{
							D(bug(" not TCT_EMPTY\n"));
							if (/*ieeemode &&*/ b == TCT_FLOAT)
								cell += 4;
							d = *(double *)cell;
							l = *(long *)cell;
							cell += 8;
						}
						switch(b)
						{
							case TCT_TIME:
								D(bug("TCT_TIME\n"));
#ifdef __amigaos4__
								sp = ASPrintf("%ld:%02ld:%02ld",(l/3600),((l/60) % 60),(l % 60));
								c->c_Text = AllocString(sp);
								FreeVec(sp);
#else
								sprintf(t,"%ld:%02ld:%02ld",l/3600,(l/60) % 60,l % 60);
								c->c_Text = AllocString(t);
#endif
								break;
							case TCT_FLOAT:
								D(bug("TCT_FLOAT: %lf\n", d));
								c->c_Text = AllocString(ita(d,-1,ITA_NONE));
								c->c_Type = CT_VALUE;
								break;
							case TCT_INT:
								D(bug("TCT_INT\n"));
#ifdef __amigaos4__
								sp = ASPrintf("%ld",l);
								c->c_Text = AllocString(sp);
								FreeVec(sp);
#else
								sprintf(t,"%ld",l);
								c->c_Text = AllocString(t);
#endif
								break;
							case TCT_DATE:
								D(bug("date: %ld\n",l));

								if(l >= DATECORR)
								{
									l -= DATECORR;
									dateflag = 0;
								}
								else
									dateflag = 1;
								Amiga2Date(l * 24 * 60 * 60, &cd);
								D(bug("Amiga2Date: %02d.%02d.%04d\n", cd.mday, cd.month, cd.year));
#ifdef __amigaos4__
								sp = ASPrintf("%02ld.%02ld.%02ld", (long)cd.mday, (long)cd.month, (long)(dateflag ? cd.year - 78 : cd.year));
								c->c_Text = AllocString(sp);
								FreeVec(sp);
#else
								sprintf(t,"%02d.%02d.%04d", cd.mday, cd.month, (dateflag ? cd.year -78 : cd.year));
								c->c_Text = AllocString(t);
#endif
								c->c_Type = CT_TEXT;
								break;
						}
						D(bug("Celltext: %s\n",c->c_Text));
						if (b != TCT_EMPTY)
						{
							w = *(UWORD *)cell;	cell += 2;
							D(bug("Pos: %d\n",(long)cell - (long)buf));
							ConvertTCFormula(c,cell,w);
							cell += w;
						}
						tc = (struct TCell *)cell;
						//Farben setzen
						col = FindColorPen(0,0,0);
						for(row = 0;row < 4;row++)
							c->c_BorderColor[row] = col;
						c->c_APen = c->c_ReservedPen = tc->tc_Color1 & TC_COLOR_MASK;
						c->c_BPen = tc->tc_Color0 & TC_COLOR_MASK;
						//Rahmen bearbeiten
						if (tc->tc_Border & TC_BORDER_LEFT)
							c->c_Border[0] = (tc->tc_Border & TC_BORDER_LEFT) << 3;
						if (tc->tc_Border & TC_BORDER_RIGHT)
							c->c_Border[1] = (tc->tc_Border & TC_BORDER_RIGHT);
						if (tc->tc_Border & TC_BORDER_DOWN)
							c->c_Border[2] = (tc->tc_Border & TC_BORDER_DOWN) >> 6;
						if (tc->tc_Border & TC_BORDER_UP)
							c->c_Border[3] = (tc->tc_Border & TC_BORDER_UP) >> 3;
						//Schriftstile bearbeiten
						if (tc->tc_Font & TC_STYLE_MASK)
						{
							struct TagItem tags[2] = {{FA_Style, ((tc->tc_Font & (1 << TC_STYLE_ITALIC)) ? FS_ITALIC : 0) |
														((tc->tc_Font & (1 << TC_STYLE_BOLD)) ? FS_BOLD : 0) |
														((tc->tc_Font & (1 << TC_STYLE_UNDERLINED)) ? FS_UNDERLINED : 0)},
												{TAG_END, 0}};
							c->c_FontInfo = ChangeFontInfoA(NULL, page->pg_DPI, tags, FALSE);
						}
						else
						{
							struct TagItem tags[2] = {{FA_Style, 0}, {TAG_END, 0}};
							c->c_FontInfo = ChangeFontInfoA(NULL, page->pg_DPI, tags, FALSE);
						}
						//Ausrichtung in der Zelle bearbeiten
						if(tc->tc_Flags)
						{
							uint8 va[4] = {0, CA_TOP, CA_VCENTER, CA_BOTTOM};

							c->c_Alignment = (tc->tc_Flags & TCF_ALIGNMENT);
							c->c_Alignment += va[(tc->tc_Flags & TCF_VALIGNMENT)>>3];
						}
					}//END if(c=NewCell
					D(bug("End FILE_(L)CELL\n\n"));
					break;
				case FILE_NAME:
					w = *(UWORD *)(cell = buf);	cell += 2;
#ifdef DEBUG_OS4
					DebugPrintF("Type: %02d Size: %05d Data: ", th.th_Type, size);
					for(i = 0; i < size; i++)
						DebugPrintF("%02X ", ((uint8 *)buf)[i]);
					DebugPrintF("\n");
#endif
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
				case FILE_SCREEN:
					D(bug("	Screen.\n"));
					break;
				case FILE_COLOR:
					w = *(UWORD *)(cell = buf);
#ifdef DEBUG_OS4
					DebugPrintF("Type: %02d Size: %05d Data: ", th.th_Type, w);
					for(i = 0; i < w; i++)
						DebugPrintF("%02X ", ((uint8 *)buf)[i]);
					DebugPrintF("\n");
#endif
					if ((cols = AllocPooled(pool, w * sizeof(ULONG) + 4)) != 0)
					{
						struct colorPen *cp;

						cols_size = w * sizeof(ULONG) + 4;
						for(cell += 2,col = 1;w;w--,cell += 2,col++)
						{
							row = *(UWORD *)cell;
							r = ((row & 0x0f00) >> 8) | ((row & 0x0f00) >> 4);
							g = ((row & 0x00f0) >> 4) | (row & 0x00f0);
							b = ((row & 0x000f) << 4) | (row & 0x000f);
#ifdef __amigaos4__
							//Farbe hinzufügen
							//Dann ID bestimmen, dann gehts, sonst nicht, AddPen falsche ID liefert. Muß korregiert werden
							//Fehler nur in AOS4 Version, also Systembedingt.
							cp = AddPen(NULL, r, g, b);		
							cols[col] = FindColorPen(r,g,b);	 
#else
							if ((cp = AddPen(NULL, r, g, b)) != 0)
								cols[col] = cp->cp_ID;
							else
								cols[col] = 0;
#endif
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
				case FILE_SHEETSIZE:
					D(bug("	Sheet-Size.\n"));
					break;
				case FILE_SYSTEMFONTS:
					D(bug("	System-Fonts.\n"));
					break;
				case FILE_FROZEN:
					D(bug("	Frozen.\n"));
					break;
				case FILE_SAVEOPT:
					D(bug("	Save-Options.\n"));
					break;
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
#ifdef DEBUG_OS4
					DebugPrintF("Type: %02d Size: %05d Data: ", th.th_Type, size);
					for(i = 0; i < size; i++)
						DebugPrintF("%02X ", ((uint8 *)buf)[i]);
					DebugPrintF("\n");
#endif
					spos = 22;
					mp->mp_Author = AllocString(&((uint8 *)buf)[spos]);
					spos += ((uint8 *)buf)[spos - 1] + 2;
					mp->mp_CatchWords = AllocString(&((uint8 *)buf)[spos]);
					spos += ((uint8 *)buf)[spos - 1] + 2;
					mp->mp_Note = AllocStringLength(&((uint8 *)buf)[spos], (uint8)((uint8 *)buf)[spos - 1]);
					tabver[0] = (uint8)((uint8 *)buf)[15] / 10 + 0x30;
					tabver[1] = (uint8)((uint8 *)buf)[15] % 10 + 0x30;
					mp->mp_Version = AllocString(tabver);
					break;

				default:
					D(bug("	UNKNOWN (%ld).\n",th.th_Type));
#ifdef DEBUG_OS4
					DebugPrintF("Type: %02d Size: %05d Data: ", th.th_Type, size);
					for(i = 0; i < size; i++)
						DebugPrintF("%02X ", ((uint8 *)buf)[i]);
					DebugPrintF("\n");
#endif
					break;
			}
		}
	}
	if (buf && len)
		FreePooled(pool,buf,len);
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
	if(cols_size)
		FreePooled(pool,cols,cols_size);
	cols = NULL;
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


#if defined(__SASC)
void STDARGS
_XCEXIT(void)
{
}
#endif
