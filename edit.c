/* functions for the text/formula edit field
 *
 * Copyright �1996-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the GNU General Public License, version 3.
 */


#include "types.h"
#include "funcs.h"

#define RIGHTOFFSET 10

extern bool gSessionChanged;


bool
DocumentSecurity(struct Page *page, struct tableField *tf)
{
	// protection is applied from the whole document down to its elements

	if ((page->pg_Document->mp_Flags & MPF_CELLSLOCKED)	== 0)
		return false;
	
	if ((page->pg_Flags & PGF_IMMUTABLE) == 0)
		return false;

	if (tf != NULL && (tf->tf_Flags & TFF_SECURITY) == 0)
		return false;

	DrawStatusText(rxpage, GetString(&gLocaleInfo, MSG_PROTECTED_CELL));
	DisplayBeep(NULL);

	return true;
}


static STRPTR
InsertString(STRPTR a, STRPTR in, long pos, long len)
{
	STRPTR b;
	long alen;

	if (!in)
		return a;

	alen = a ? strlen(a) : 0;
	if (len == -1)
		len = strlen(in);

	if (!(b = AllocPooled(pool,alen+len+1)))
		return a;

	strncpy(b, a, pos);
	strncpy(b + pos, in, len);
	strcpy(b + pos + len, a + pos);
	FreeString(a);

	return b;
}


static STRPTR
RemoveString(STRPTR a, long pos, long len)
{
	STRPTR b;

	if (!a || !len)
		return a;

	if (!(b = AllocPooled(pool, strlen(a) - len + 1)))
		return a;

	strncpy(b, a, pos);
	strcpy(b + pos, a + pos + len);
	FreeString(a);

	return b;
}

extern struct MinList flangs;
long complen,comppos;

int
compcmp(STRPTR *a, STRPTR *b)
{
	return strnicmp(*a, *b, complen);
}


BOOL
CompleteFunctionNames(struct Page *page)
{
	static struct FunctionLanguage *fl;
	static struct Link *l;
	static long fpos;
	UBYTE second = FALSE;
	struct tableField *tf;
	struct Name *nm;
	long len = 0;
	BOOL rc = FALSE;
	STRPTR t;

	if (!page || page->pg_Gad.DispPos <= PGS_FRAME || !(tf = page->pg_Gad.tf) || !tf->tf_Text)
		return FALSE;

	if (!comppos) {
		comppos = page->pg_Gad.DispPos;
		fl = (APTR)flangs.mlh_Head;
		l = (APTR)page->pg_Mappe->mp_Names.mlh_Head;
		fpos = 0;
	} else {
		tf->tf_Text = RemoveString(tf->tf_Text,comppos,page->pg_Gad.DispPos-comppos);
		if (imsg.Qualifier & IEQUALIFIER_SHIFT)
			fpos--;
		else
			fpos++;
		second = TRUE;
		if (fl == (APTR)~0L && l) {
			if (imsg.Qualifier & IEQUALIFIER_SHIFT)
				l = (APTR)l->l_Node.mln_Pred;
			else
				l = (APTR)l->l_Node.mln_Succ;
		}
		if (imsg.Qualifier & IEQUALIFIER_ALT && fl != (APTR)~0L) {
			second = FALSE;
			rc = TRUE;
		}
	}
	if (!tf->tf_Text)
		return TRUE;

	complen = 0;
	for (t = tf->tf_Text+comppos-1;IsAlNum(loc,*t) || *t == '_';t--,complen++);
	t++;

	if (!(imsg.Qualifier & IEQUALIFIER_ALT) && fl != (APTR)~0L) {
		do {
			for (;fl->fl_Node.ln_Succ;fl = (APTR)fl->fl_Node.ln_Succ) {
				if (!fl->fl_Node.ln_Succ->ln_Succ)  // interne Funktionsnamen werden nicht gepr�ft
					break;

				while (fpos < fl->fl_Length && strnicmp(fl->fl_Array[fpos].fn_Name,t,complen) < 0)
					fpos++;

				if (fpos < fl->fl_Length && !strnicmp(fl->fl_Array[fpos].fn_Name,t,complen)) {
					for(;IsAlNum(loc,*(fl->fl_Array[fpos].fn_Name+len));len++);
					tf->tf_Text = InsertString(tf->tf_Text,fl->fl_Array[fpos].fn_Name+complen,comppos,len-complen);
					page->pg_Gad.DispPos = comppos+len-complen;
					return TRUE;
				}
			}
			if (second) {
				fl = (APTR)flangs.mlh_Head;
				fpos = 0;
			}
		} while (second);
	}
	fl = (APTR)~0L;

	do {
		for (;l->l_Node.mln_Succ;l = (APTR)l->l_Node.mln_Succ) {
			if (!strnicmp((nm = (struct Name *)l->l_Link)->nm_Node.ln_Name,t,complen)) {
				tf->tf_Text = InsertString(tf->tf_Text,nm->nm_Node.ln_Name+complen,comppos,(len = strlen(nm->nm_Node.ln_Name))-complen);
				page->pg_Gad.DispPos = comppos+len-complen;
				return TRUE;
			}
		}
		if (second)
			l = (APTR)page->pg_Mappe->mp_Names.mlh_Head;
	} while (second);

	page->pg_Gad.DispPos = comppos;
	comppos = 0;

	return rc;
}


BOOL
TestForCompletion(struct Page *page,struct tableField *tf)
{
	return (BOOL)(page->pg_Gad.DispPos > 1 && *tf->tf_Text == '=');
}


void
ShowFunctionHelp(struct Page *page)
{
	struct FunctionLanguage *fl;
	struct FunctionName *fn;
	struct tableField *tf;
	long   x,y;
	STRPTR t;

	if (!page || page->pg_Gad.DispPos <= PGS_FRAME || !(tf = page->pg_Gad.tf) || !tf->tf_Text || *(tf->tf_Text+page->pg_Gad.DispPos-1) != '(')
		return;

	t = tf->tf_Text+page->pg_Gad.DispPos-2;
	if (!IsAlNum(loc,*t))
		return;
	for(;IsAlNum(loc,*t) || *t == '_';t--);
	t++;

	x = page->pg_Gad.cp.cp_X;  y = page->pg_Gad.cp.cp_Y+page->pg_Gad.cp.cp_H;
	if (x < page->pg_wTabX)
		x = page->pg_wTabX;
	if (y > page->pg_wTabY+page->pg_wTabH)
		y = page->pg_wTabY+page->pg_wTabH;
	x += 5+page->pg_Window->LeftEdge;  y += 5+page->pg_Window->TopEdge;

	foreach (&flangs, fl)
	{
		if (!fl->fl_Node.ln_Succ->ln_Succ)  // interne Funktionsnamen werden nicht gepr�ft
			break;

		if (fn = bsearch(&t,fl->fl_Array,fl->fl_Length,sizeof(struct FunctionName),(APTR)cmdcmp))
		{
			ShowPopUpText(fn->fn_Name,x,y);
			return;
		}
	}
	ShowPopUpText(GetString(&gLocaleInfo, MSG_UNKNOWN_FUNCTION_NAME_ERR), x, y);
}


void
WriteTabGadget(struct Page *page, struct UndoNode *un)
{
	struct tableField *tf;

	if (tf = page->pg_Gad.tf)
	{
		page->pg_Gad.tf = NULL;
		UpdateCellText(page, tf);

		if (page->pg_Mappe->mp_Flags & MPF_SCRIPTS)
			UpdateMaskCell(page->pg_Mappe, page, tf, un);
		page->pg_Gad.tf = tf;
		//RecalcTableFields(page);
	}
}


struct tableField *
BeginTabGadget(struct Page *page)
{
	struct tableField *tf;
	bool oldCell = page->pg_Gad.tf != NULL;

	if (page->pg_Gad.tf = tf = AllocTableField(page, page->pg_Gad.cp.cp_Col, page->pg_Gad.cp.cp_Row))
	{
		if (page->pg_Gad.Undo)
			FreeTableField(page->pg_Gad.Undo);

		page->pg_Gad.Undo = NULL;

		if (oldCell)
			page->pg_Gad.Undo = CopyCell(page, tf);

		if (tf->tf_Original) {
			FreeString(tf->tf_Text);
			tf->tf_Text = tf->tf_Original;
			tf->tf_Original = NULL;
		}

		if (!tf->tf_Text && !(tf->tf_Flags & TFF_FONTSET))
		{
			tf->tf_FontInfo = SetFontInfo(tf->tf_FontInfo, page->pg_DPI,
									FA_Family,	   page->pg_Family,
									FA_PointHeight,  page->pg_PointHeight,
									TAG_END);
			if (prefs.pr_Table->pt_Flags & PTF_AUTOCELLSIZE)
			{
				char t[20];

				sprintf(t,"%ld pt",((page->pg_PointHeight*4) >> 16)/3);
				if (ConvertNumber(t,CNT_MM) > (page->pg_tfHeight+tf->tf_Row-1)->ts_mm/1024.0)
					ChangeCellSize(page,NULL,t,CCS_STANDARD,NULL);
			}
		}
	}
	return tf;
}


void
SetTabGadget(struct Page *page, STRPTR t, long pos)
{
	struct tableField *tf;
	BYTE   changed = FALSE;

	if (page->pg_Gad.DispPos == PGS_NONE)
		return;
	if ((!t || t == (STRPTR)~0L) && pos <= PGS_FRAME && !GetTableField(page,page->pg_Gad.cp.cp_Col,page->pg_Gad.cp.cp_Row))
		return;
	if (DocumentSecurity(page, tf = page->pg_Gad.tf))
		return;

	if (!t && tf || t != (STRPTR)~0L)
	{
		long prepos;

		prepos = page->pg_Gad.DispPos;
		if (prepos == PGS_FRAME)
			BeginTabGadget(page);
		if (tf)
		{
			FreeString(tf->tf_Text);
			tf->tf_Text = AllocString(t);
			SetTFWidth(page,tf);
			/* MERKER: falls cp_W-Aktualisierung aus SetTFWidth() rausfliegt, mu� sie hierhin...*/
			changed = TRUE;
		}
		if (prepos == PGS_FRAME && pos == PGS_IGNORE)
			CreateTabGadget(page,page->pg_Gad.cp.cp_Col,page->pg_Gad.cp.cp_Row,FALSE);
	}
	if (pos != PGS_IGNORE)
	{
		long len;

		if (pos == PGS_NONE)
			FreeTabGadget(page);
		else if (pos == PGS_FRAME)
		{
			if (page->pg_Gad.DispPos > PGS_FRAME)
				CreateTabGadget(page,page->pg_Gad.cp.cp_Col,page->pg_Gad.cp.cp_Row,FALSE);
		}
		else if (page->pg_Gad.DispPos == PGS_FRAME)
			BeginTabGadget(page);
		if ((tf = page->pg_Gad.tf) && pos > (len = tf->tf_Text ? strlen(tf->tf_Text) : 0))
			pos = len;
		page->pg_Gad.DispPos = pos;
		if (tf)
			changed = TRUE;
	}
	if (changed)
		DrawTableField(page,tf);
}


/** F�gt alle im Term enthaltenen Funktionen zu den zuletzt
 *  benutzten Funktionen hinzu, falls diese nicht bereits
 *  darin erfa�t waren.
 *  �ndert sich diese Liste, wird daf�r gesorgt, da� sie
 *  bei Programmende gespeichert wird (gSessionChanged).
 *
 *  @param t der zu untersuchende Term
 */

void
trackFunctions(struct Term *t)
{
	if (!t)
		return;

	if (t->t_Op == OP_FUNC)
	{
		struct Function *f = t->t_Function;
		struct FuncArg *fa;
		struct Node *ln;

		if (f == NULL)
			return;
		if (ln = (APTR)FindLink(&usedfuncs,f))
		{
			if ((APTR)usedfuncs.mlh_Head != ln)
				gSessionChanged = true;
			Remove(ln);
		}
		else if (ln = AllocPooled(pool,sizeof(struct Node)))
		{
			ln->ln_Name = (APTR)f;
			gSessionChanged = true;
		}

		if (ln)
			AddHead(&usedfuncs,ln);

		foreach(&t->t_Args,fa)
			trackFunctions(fa->fa_Root);
	}
	else
	{
		trackFunctions(t->t_Left);
		trackFunctions(t->t_Right);
	}
}


void
FreeTabGadget(struct Page *page)
{
	struct UndoNode *un = NULL;
	struct tableField *tf;
	char   t[128];
	int32  x,y,w,h,a,b;
	bool   changed = false;

	if (page->pg_Gad.DispPos == PGS_NONE)
		return;
	else if (page->pg_Gad.DispPos >= 0)
	{
		changed = true;  comppos = 0;
		if (strcmp(page->pg_Gad.tf->tf_Text ? page->pg_Gad.tf->tf_Text : (STRPTR)"",
				page->pg_Gad.Undo && page->pg_Gad.Undo->tf_Original ? page->pg_Gad.Undo->tf_Original : (STRPTR)""))
		{
			if (page->pg_Gad.tf->tf_Text)
			{
				int len;

				if (page->pg_Gad.Undo && page->pg_Gad.Undo->tf_Original)
					strcpy(t,GetString(&gLocaleInfo, MSG_CHANGE_CELL_TEXT_UNDO));
				else
					strcpy(t,GetString(&gLocaleInfo, MSG_CELL_TEXT_INPUT_UNDO));
				len = 124-strlen(t);  x = 0;
				if (strlen(page->pg_Gad.tf->tf_Text) > len)
					x = 1, len -= 3;
				strncat(t,page->pg_Gad.tf->tf_Text, len);
				if (x == 1)
					strcat(t,"...");
				strcat(t,"\"");
			}
			else
				strcpy(t, GetString(&gLocaleInfo, MSG_DELETE_CELL_TEXT_UNDO));

			if (un = CreateUndo(page, UNDO_CELL, t))
			{
				un->un_Type = UNT_BLOCK_CHANGED;
				if (tf = page->pg_Gad.Undo)
				{
					page->pg_Gad.Undo = NULL;
					AddTail((struct List *)&un->un_UndoList, (struct Node *)tf);
				}
			}
		}

		WriteTabGadget(page, un);

		if (un)
		{
			un->un_Node.ln_Type &= ~UNDO_NOREDO;
			if (tf = CopyCell(page, page->pg_Gad.tf))
				AddTail((struct List *)&un->un_RedoList, (struct Node *)tf);
		}
		handleEvent(page, EVT_FIELDEND, page->pg_Gad.cp.cp_Col, page->pg_Gad.cp.cp_Row);

		/*** benutzte Funktionen herausfiltern ***/

		if (page->pg_Gad.tf->tf_Type & TFT_FORMULA)
			trackFunctions(page->pg_Gad.tf->tf_Root);
	}
	x = page->pg_Gad.cp.cp_X;  y = page->pg_Gad.cp.cp_Y;
	w = page->pg_Gad.cp.cp_W;  h = page->pg_Gad.cp.cp_H;
	page->pg_Gad.DispPos = PGS_NONE;
	page->pg_Gad.tf = NULL;
	if (page->pg_Window)
	{
		if ((a = max(x-2,page->pg_wTabX)) < page->pg_wTabX+page->pg_wTabW && (b = max(y-2,page->pg_wTabY)) < page->pg_wTabY+page->pg_wTabH)
			DrawTableCoord(page,a,b,changed ? page->pg_wTabX+page->pg_wTabW : min(x+w,page->pg_wTabX+page->pg_wTabW),min(y+h,page->pg_wTabY+page->pg_wTabH));
	}
}


void
RefreshTabGadgetLine(struct Page *page)
{
	SetTFWidth(page,GetRealTableField(page,page->pg_Gad.cp.cp_Col,page->pg_Gad.cp.cp_Row));
	DrawTableCoord(page,page->pg_wTabX,page->pg_Gad.cp.cp_Y,page->pg_wTabX+page->pg_wTabW,page->pg_Gad.cp.cp_Y+page->pg_Gad.cp.cp_H);
}


void
HandleTabGadget(struct Page *page)
{
	struct tableField *tf;
	struct RastPort *rp = page->pg_Window->RPort;
	STRPTR t,st;
	BOOL   firsttab = FALSE,changed = FALSE;
	long   col,row,len = -1,i,j,oldw,oldfc,bspace = page->pg_CellTextSpace;

	if (imsg.Qualifier & (IEQUALIFIER_RCOMMAND | IEQUALIFIER_LCOMMAND))
		return;

	if (page->pg_Gad.DispPos == PGS_NONE)
	{
		CreateTabGadget(page, 1, 1, TRUE);
		if (!(imsg.Class == IDCMP_VANILLAKEY && imsg.Code != 13))
			return;
	}
	if (DocumentSecurity(page, tf = page->pg_Gad.tf))
		return;

	col = page->pg_Gad.cp.cp_Col;
	row = page->pg_Gad.cp.cp_Row;

	if (page->pg_Gad.DispPos == PGS_FRAME)
	{
		if (imsg.Class == IDCMP_VANILLAKEY && imsg.Code != 13)
		{
			if (imsg.Class == IDCMP_VANILLAKEY && imsg.Code == 9)
				firsttab = TRUE;
			if (tf = BeginTabGadget(page))
				page->pg_Gad.DispPos = tf->tf_Text ? strlen(tf->tf_Text) : 0;
			else
				return;
		}

		// draw cell with cursor
		if (page->pg_Gad.DispPos >= 0)
		{
			SetTFWidth(page, tf);
			DrawTableField(page, tf);
		}
	}

	if (tf && page->pg_Gad.DispPos >= 0)
	{
		i = page->pg_Gad.cp.cp_X + bspace
			+ OutlineLength(tf->tf_FontInfo, tf->tf_Text + page->pg_Gad.FirstChar, page->pg_Gad.DispPos - page->pg_Gad.FirstChar);

		if (i < wd->wd_TabX
			|| i > wd->wd_TabX + wd->wd_TabW
			|| page->pg_Gad.cp.cp_Y < wd->wd_TabY
			|| page->pg_Gad.cp.cp_Y > wd->wd_TabY + wd->wd_TabH)
		{
			page->pg_Gad.cp.cp_X -= wd->wd_TabX;
			page->pg_Gad.cp.cp_Y -= wd->wd_TabY;
			ShowTable(page, &page->pg_Gad.cp, 0, 0);
		}

		page->pg_Gad.DispPos = -page->pg_Gad.DispPos - 1;
		DrawTableCoord(page,i,page->pg_Gad.cp.cp_Y + 1, i + 1, page->pg_Gad.cp.cp_Y + page->pg_Gad.cp.cp_H - 3);
		page->pg_Gad.DispPos = -page->pg_Gad.DispPos - 1;

		if (imsg.Class == IDCMP_RAWKEY)
		{
			if (imsg.Code == CURSORLEFT && page->pg_Gad.DispPos > 0)
			{
				if (imsg.Qualifier & 3)
					page->pg_Gad.DispPos = 0;
				else
					page->pg_Gad.DispPos--;
			}
			else if (imsg.Code == CURSORRIGHT && tf->tf_Text && page->pg_Gad.DispPos < strlen(tf->tf_Text))
			{
				if (imsg.Qualifier & 3)
					page->pg_Gad.DispPos = strlen(tf->tf_Text);
				else
					page->pg_Gad.DispPos++;
			}
			else if (imsg.Code < 96 || imsg.Code > 101)
			{
				if (imsg.Code == 66 && TestForCompletion(page, tf))
				{
					if (CompleteFunctionNames(page))
						RefreshTabGadgetLine(page);
				}
				else
					page->pg_Gad.DispPos = PGS_FRAME;
			}
		}
		else
		{
			if (imsg.Code != 9)
				comppos = 0;

			switch (imsg.Code)
			{
				case 9:	 // Tab
					if (firsttab)
						break;
					if (TestForCompletion(page, tf))
					{
						if (CompleteFunctionNames(page))
							RefreshTabGadgetLine(page);
						break;
					}
				case 13:	// Return
					page->pg_Gad.DispPos = PGS_FRAME;
					break;
				case 27:  	// Escape
					page->pg_Gad.DispPos = PGS_FRAME;
					FreeString(tf->tf_Text);
					
					// Restore old text
					if (page->pg_Gad.Undo)
						tf->tf_Text = AllocString(page->pg_Gad.Undo->tf_Original);
					else
						tf->tf_Text = NULL;
					break;
				case 8:		// backspace
					if (page->pg_Gad.DispPos == 0)
					{
						DisplayBeep(NULL);
						break;
					}
					if (imsg.Qualifier & 3)
					{
						if (t = tf->tf_Text)
						{
							tf->tf_Text = AllocString(tf->tf_Text + page->pg_Gad.DispPos);
							FreeString(t);
							len = page->pg_Gad.DispPos = 0;
							break;
						}
						break;
					}
					page->pg_Gad.DispPos--;
				case 127:	// delete
					if (imsg.Qualifier & 3)
					{
						if ((t = tf->tf_Text) && (tf->tf_Text = AllocPooled(pool,page->pg_Gad.DispPos+1)))
						{
							CopyMem(t,tf->tf_Text,page->pg_Gad.DispPos);
							FreeString(t);
							len = page->pg_Gad.DispPos;
							break;
						}
						break;
					}
					if (tf->tf_Text && strlen(tf->tf_Text) > page->pg_Gad.DispPos)
					{
						if (strlen(tf->tf_Text) > 1 && (st = t = AllocPooled(pool,strlen(tf->tf_Text))))
						{
							for(i = 0;*(tf->tf_Text+i);i++)
							{
								if (i != page->pg_Gad.DispPos)
									*(st++) = *(tf->tf_Text+i);
							}
						}
						else
							t = NULL;
						FreeString(tf->tf_Text);
						tf->tf_Text = t;
						if (!tf->tf_Text)
							RefreshTabGadgetLine(page);
						len = page->pg_Gad.DispPos;
					}
					break;
				default:
					len = ((st = tf->tf_Text) ? strlen(st) : 0);
					if (t = AllocPooled(pool, len + 2))
					{
						for (i = 0; i < len + 1; i++)
						{
							if (i == page->pg_Gad.DispPos)
								*(t+i) = imsg.Code;
							else
								*(t+i) = *(st++);
						}
						FreeString(tf->tf_Text);
						len = page->pg_Gad.DispPos++;
						if (len == strlen(t)-1)
							len = -1;
						tf->tf_Text = t;
						if (!st)
							RefreshTabGadgetLine(page);
						
						// if it's a formula and the parameter starts '(', show function help
						if (imsg.Code == '(' && t[0] == '=')
							ShowFunctionHelp(page);
					}
					break;
			}
		}
		if (page->pg_Gad.DispPos == PGS_FRAME)
			changed = TRUE;
		else
		{
			i = bspace + OutlineLength(tf->tf_FontInfo, tf->tf_Text, tf->tf_Text ? strlen(tf->tf_Text) : 0);

			if (tf->tf_WidthSet == 0xffff && tf->tf_Width != tf->tf_MaxWidth)
			{
				oldw = page->pg_Gad.cp.cp_W;
				for(page->pg_Gad.cp.cp_W = 0,j = page->pg_Gad.cp.cp_Col;i > page->pg_Gad.cp.cp_W;page->pg_Gad.cp.cp_W += GetTFWidth(page,j++));
				if (oldw != page->pg_Gad.cp.cp_W)
				{
					SetTFWidth(page,tf);
					DrawTableCoord(page,min(oldw,page->pg_Gad.cp.cp_W)+page->pg_Gad.cp.cp_X-4,page->pg_Gad.cp.cp_Y-2,wd->wd_TabX+wd->wd_TabW,page->pg_Gad.cp.cp_Y+page->pg_Gad.cp.cp_H/*+2*/);
				}
			}

			oldfc = page->pg_Gad.FirstChar;

			if (page->pg_Gad.DispPos > page->pg_Gad.FirstChar)
			{
				i = bspace+OutlineLength(tf->tf_FontInfo,tf->tf_Text+page->pg_Gad.FirstChar,page->pg_Gad.DispPos-page->pg_Gad.FirstChar);
				for(;i > page->pg_Gad.cp.cp_W;i = bspace+OutlineLength(tf->tf_FontInfo,tf->tf_Text+ ++page->pg_Gad.FirstChar,page->pg_Gad.DispPos-page->pg_Gad.FirstChar));
			}
			else
			{
				i = bspace;
				if ((page->pg_Gad.FirstChar = page->pg_Gad.DispPos) < 0)
					page->pg_Gad.FirstChar = 0;
			}

			{
				char scroll = FALSE;

				i += page->pg_Gad.cp.cp_X;

				if (i > wd->wd_TabX+(wd->wd_TabW*(RIGHTOFFSET-1)/RIGHTOFFSET)-3)
					i += wd->wd_TabW/RIGHTOFFSET-wd->wd_TabW,  scroll = TRUE;
				else if (i < wd->wd_TabX)
					scroll = TRUE;

				// ScrollTable(page->pg_Window,page->pg_TabX-wd->wd_TabX+i,page->pg_TabY+j);

				if (scroll)
					ScrollTable(page->pg_Window,page->pg_TabX+(scroll ? i-wd->wd_TabX : 0),page->pg_TabY);
			}

			if (oldfc != page->pg_Gad.FirstChar)
				DrawTableCoord(page,page->pg_Gad.cp.cp_X,page->pg_Gad.cp.cp_Y,page->pg_Gad.cp.cp_X+page->pg_Gad.cp.cp_W,page->pg_Gad.cp.cp_Y+page->pg_Gad.cp.cp_H);
			else
			{
				i = page->pg_Gad.cp.cp_X+bspace+OutlineLength(tf->tf_FontInfo,tf->tf_Text+page->pg_Gad.FirstChar,page->pg_Gad.DispPos-page->pg_Gad.FirstChar);
				if (imsg.Class == IDCMP_VANILLAKEY)
				{
					j = 0;  oldw = page->pg_Gad.cp.cp_X+page->pg_Gad.cp.cp_W-3;
					if (len >= 0)
						j = page->pg_Gad.cp.cp_X+bspace+OutlineLength(tf->tf_FontInfo,tf->tf_Text+page->pg_Gad.FirstChar,len-page->pg_Gad.FirstChar);
					else if (page->pg_Gad.DispPos > 0)
					{
						j = page->pg_Gad.cp.cp_X+bspace+OutlineLength(tf->tf_FontInfo,tf->tf_Text+page->pg_Gad.FirstChar,page->pg_Gad.DispPos-1-page->pg_Gad.FirstChar);
						if (len == -1)
							oldw = i;
					}
					if (j)
						DrawTableCoord(page,j,page->pg_Gad.cp.cp_Y,oldw,page->pg_Gad.cp.cp_Y+page->pg_Gad.cp.cp_H-2);
				}
				makeClip(page->pg_Window,wd->wd_TabX,wd->wd_TabY,wd->wd_TabW,wd->wd_TabH);
				if (tf->tf_BPen == page->pg_APen)
					SetHighColor(rp,tf->tf_APen);
				else
					SetHighColor(rp,page->pg_APen);
				RectFill(rp,i,page->pg_Gad.cp.cp_Y+1,i+1,page->pg_Gad.cp.cp_Y+page->pg_Gad.cp.cp_H-3);
				freeClip(win);
			}
		}
	}

	if (page->pg_Gad.DispPos == PGS_FRAME)
	{
		struct Mask *ma = NULL;

		if (page->pg_MarkCol != -1)
			SetMark(page, -1, 0, 0, 0);

		if (imsg.Class == IDCMP_RAWKEY)
		{
			switch (imsg.Code)
			{
				case CURSORDOWN:
					row++;
					break;
				case CURSORUP:
					row--;
					break;
				case CURSORLEFT:
					col--;
					if (imsg.Qualifier & 3)
						col = 1;
					break;
				case CURSORRIGHT:
					col++;
					break;
				case 66:  // TAB
					if (imsg.Qualifier & 3)
						col--;
					else
						col++;
					break;
			}
		}
		else
		{
			if (page->pg_Mappe->mp_Flags & MPF_SCRIPTS && (imsg.Code == 13 || imsg.Code == 9) && (ma = IsOverMask(page)))
			{
				struct MaskField *mf;

				foreach (&ma->ma_Fields, mf)
				{
					if (mf->mf_Col == col && mf->mf_Row == row)
						break;
				}
				if ((mf = (struct MaskField *)mf->mf_Node.ln_Succ) && mf->mf_Node.ln_Succ)
				{
					col = mf->mf_Col;  row = mf->mf_Row;
					ma = NULL;
				}
				else if (!mf)  /* not the last field */
					ma = NULL;
			}
			else if (imsg.Code == 13)
				row++;
			else if (imsg.Code == 9)
				col++;
		}
		if (col <= 0 || row <= 0)
		{
			DisplayBeep(NULL);
			return;
		}

#ifdef IGNITION_LITE_EDITION
		// the maximum table size is 30 x 50
		if (col > 30)
			col = 30;
		if (row > 50)
			row = 50;
#endif

		if (changed)
			page->pg_Gad.DispPos = 0;
		if (changed || col != page->pg_Gad.cp.cp_Col || row != page->pg_Gad.cp.cp_Row)
			FreeTabGadget(page);

		if (ma)	  /* update indices/filter or start db-search */
		{
			struct Database *db;

			if (db = (APTR)FindName(&page->pg_Mappe->mp_Databases, ma->ma_Node.ln_Name))
			{
				if (ma->ma_Node.ln_Type)
					MakeSearchFilter(db, ma);
				else
					UpdateIndices(db);
				RecalcTableFields(page);
			}
		}

		if (changed || col != page->pg_Gad.cp.cp_Col || row != page->pg_Gad.cp.cp_Row)
			CreateTabGadget(page, col, row, TRUE);
	}
}


void
CreateTabGadget(struct Page *page, long col, long row, BOOL makevisible)
{
	struct coordPkt *cp;

	if (page->pg_Gad.DispPos != PGS_NONE)
		FreeTabGadget(page);

#ifdef IGNITION_LITE_EDITION
		// the maximum table size is 30 x 50
		if (col > 30)
			col = 30;
		if (row > 50)
			row = 50;
#endif

	DeselectGObjects(page);
	cp = &page->pg_Gad.cp;
	setCoordPkt(page, cp, col, row);

	if (makevisible)
		ShowTable(page, cp, 0, 0);
	else
	{
		cp->cp_X += page->pg_wTabX;
		cp->cp_Y += page->pg_wTabY;
	}

	page->pg_HotSpot = PGHS_CELL;
	page->pg_Gad.DispPos = PGS_FRAME;
	page->pg_Gad.FirstChar = 0;
	page->pg_Gad.tf = GetTableField(page, cp->cp_Col, cp->cp_Row);
	page->pg_SelectPos = -1;  page->pg_SelectLength = 0;

	DrawTableCoord(page, cp->cp_X - 2, cp->cp_Y - 2, cp->cp_X + cp->cp_W + 2, cp->cp_Y + cp->cp_H);
	DisplayTablePos(page);
	RefreshToolBar(page);
}


bool
QueryPassword(STRPTR t, STRPTR password)
{
	bool checked = FALSE, doit = TRUE;
	struct Gadget *gadlist, *pgad;
	struct IntuiMessage *msg;
	struct Window *win;
	STRPTR s[4];
	long i,w;

	if (!(gad = CreateContext(&gadlist)))
		return false;

	gHeight = fontheight*2 + 20 + barheight+bborder;
	for (i = 0; *t; i++) {
		gHeight += fontheight;
		s[i] = t;

		if ((w = TLn(t)) > gWidth)
			gWidth = w;

		for (;*t++;);
	}
	s[i] = NULL;
	gWidth += lborder+rborder;
	if (gWidth < (scr->Width >> 2))
		gWidth = scr->Width >> 2;

	ngad.ng_VisualInfo = vi;
	ngad.ng_TextAttr = scr->Font;
	ngad.ng_UserData = NULL;
	ngad.ng_TopEdge = barheight + 6 + fontheight*i;
	ngad.ng_Height = fontheight + 4;
	ngad.ng_GadgetText = GetString(&gLocaleInfo, MSG_PASSWORD_GAD);
	ngad.ng_LeftEdge = 8 + lborder + TLn(ngad.ng_GadgetText);
	ngad.ng_Width = gWidth - ngad.ng_LeftEdge - rborder;
	ngad.ng_Flags = PLACETEXT_LEFT;
	ngad.ng_GadgetID = 1;				   // 1
	if (pgad = CreateGadget(STRING_KIND,gad,&ngad,GT_Underscore,'_',GTST_String,NULL,GTST_EditHook,&passwordEditHook,GTST_MaxChars,32,TAG_END))
		pgad->UserData = AllocPooled(pool,32);

	ngad.ng_LeftEdge = lborder;
	ngad.ng_TopEdge += fontheight+8;
	ngad.ng_Width = TLn(GetString(&gLocaleInfo, MSG_CANCEL_GAD))+20;
	ngad.ng_GadgetText = GetString(&gLocaleInfo, MSG_OK_GAD);
	ngad.ng_Flags = PLACETEXT_IN;
	ngad.ng_GadgetID++;					 // 2
	gad = CreateGadget(BUTTON_KIND, pgad, &ngad, TAG_END);

	ngad.ng_LeftEdge = gWidth - rborder - ngad.ng_Width;
	ngad.ng_GadgetText = GetString(&gLocaleInfo, MSG_CANCEL_GAD);
	ngad.ng_GadgetID++;					 // 3
	gad = CreateGadget(BUTTON_KIND, gad, &ngad, TAG_END);

	if (win = OpenWindowTags(NULL, WA_Flags,		WFLG_DRAGBAR | WFLG_DEPTHGADGET | WFLG_ACTIVATE,
								   WA_Left,			(scr->Width - gWidth) >> 1,
								   WA_Top,			(scr->Height - gHeight) >> 1,
								   WA_Title,		GetString(&gLocaleInfo, MSG_SECURITY_CHECK_TITLE),
								   WA_Width,		gWidth,
								   WA_Height,		gHeight,
								   WA_PubScreen,	scr,
								   WA_Gadgets,		gadlist,
								   WA_IDCMP,		IDCMP_GADGETUP,
								   TAG_END)) {
		GT_RefreshWindow(win, NULL);
		for (i = 0, w = barheight + 3; s[i]; i++, w += fontheight) {
			itext.IText = s[i];
			PrintIText(win->RPort, &itext, (gWidth - IntuiTextLength(&itext)) >> 1,w);
		}

		while (doit) {
			WaitPort(win->UserPort);

			while (msg = GTD_GetIMsg(win->UserPort)) {
				switch (msg->Class) {
					case IDCMP_GADGETUP:
						if ((gad = msg->IAddress)->GadgetID == 2) {
							if (!strcmp(password, pgad->UserData))
								checked = TRUE;
						}
						if (gad->GadgetID == 1)
							break;
					case IDCMP_CLOSEWINDOW:
						doit = FALSE;
						break;
				}
				GTD_ReplyIMsg(msg);
			}
		}
		CloseWindow(win);
	}
	if (!checked && *(STRPTR)pgad->UserData) {
		DisplayBeep(NULL);
		ErrorRequest(GetString(&gLocaleInfo, MSG_WRONG_PASSWORD_ERR));
	}
	FreeGadgets(gadlist);

	return checked;
}


uint32 PUBLIC
PasswordEditHook(reg (a0) struct Hook *hook, reg (a1) ULONG *msg, reg (a2) struct SGWork *sgw)
{
	if (*msg == SGH_KEY) {
		STRPTR t = sgw->Gadget->UserData;
		int32 i;

		if (!t)
			return ~0L;

		switch (sgw->EditOp) {
			case EO_INSERTCHAR:
			case EO_REPLACECHAR:
				for(i = strlen(t);i > sgw->BufferPos-1;i--)
					t[i] = t[i-1];
				t[i] = sgw->Code;
				t[sgw->NumChars] = 0;
				sgw->WorkBuffer[i] = (UBYTE)'�';
				break;
			case EO_BIGCHANGE:
			case EO_UNDO:
			{
				STRPTR s = sgw->WorkBuffer;

				strcpy(t,s);
				for (;*s;s++)
					*s = (UBYTE)'�';
				break;
			}
			case EO_DELBACKWARD:
			case EO_DELFORWARD:
			{
				long diff = sgw->StringInfo->NumChars - sgw->NumChars;

				for (i = sgw->BufferPos;t[i];i++)
					t[i] = t[i+diff];
				break;
			}
			case EO_CLEAR:
				*t = 0;
				break;
		}
		return ~0L;
	}
	return 0;
}

