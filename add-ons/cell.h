#ifndef CELL_H
#define CELL_H
/* $VER: cell.h 0.1 (1.3.2001)
** Developer Release 0.1
**
** ignition cell & related definitions
**
** Copyright ©2001-2008 pinc Software
** All Rights Reserved
*/

#include <exec/types.h>
#include <exec/lists.h>
#include <exec/nodes.h>
#include <exec/memory.h>
#include <dos/dos.h>


/*************************** formats ***************************/
/*
#ifdef __amigaos4__
	#ifdef __GNUC__
		#ifdef __PPC__
			#pragma pack(2)
		#endif
	#elif defined(__VBCC__)
		#pragma amiga-align
	#endif
#endif
*/
struct FormatVorlage
{
  struct Node fv_Node;
  STRPTR fv_Preview;
  BYTE   fv_Alignment;
  BYTE   fv_Flags;
  ULONG  fv_NegativePen;
  BYTE   fv_Komma;
};

/* fv_Node.ln_Pri -> Kommas */

#define FVT_VALUE 1     /* fv_Node.ln_Type */
#define FVT_PERCENT 2
#define FVT_DATE 3
#define FVT_TIME 4
#define FVT_EINHEIT 5

#define FVF_ONTHEFLY 1   /* fv_Flags */


#define ITA_NONE 0             /* ita()-Optionen */
#define ITA_SEPARATE 64
#define ITA_NEGPARENTHESES 128


/*************************** table & cells ***************************/

struct tableSize
{
  UWORD ts_Pixel;
  ULONG ts_mm;
  STRPTR ts_Title;
  struct Cell *ts_Cell;
};

struct Cell
{
  struct MinNode c_Node;
  UBYTE  c_Type;
  UWORD  c_Flags;
  long   c_Col,c_Row;
  ULONG  c_APen,c_BPen,c_ReservedPen,c_NegativePen;
  ULONG  c_BorderColor[4];
  UBYTE  c_Border[4];            /* 0-8 pt -> 1/32-Schritte */
  UBYTE  c_Pattern;
  ULONG  c_PatternColor;
  UBYTE  c_Alignment;
  BYTE   c_Komma;
  struct FontInfo *c_FontInfo;
  UWORD  c_Width,c_WidthSet,c_MaxWidth,c_OldWidth;    /* freie Felder rechts */
  STRPTR c_Text;
  STRPTR c_Original;
  double c_Value;
  STRPTR c_Format;
  struct Term *c_Root;
  STRPTR c_Note;
};

#define CT_TEXT 1
#define CT_VALUE 2
#define CT_FORMULA 3  /* ARexx-Einbindung über Funktion */

#define CF_ACTUAL 1
#define CF_REFRESH 2
#define CF_LOCKED 4
#define CF_RCTEXT 8
#define CF_FORMATSET 16
#define CF_KOMMASET 32
#define CF_SEPARATE 64
#define CF_NEGPARENTHESES 128
#define CF_NEGPENSET 256
#define CF_PENSET 512

#define CA_LEFT 1
#define CA_RIGHT 2
#define CA_HCENTER 3
#define CA_TOP 4
#define CA_BOTTOM 8
#define CA_VCENTER 12
#define CA_VIRGIN 16

struct tablePos
{
  LONG tp_Col,tp_Row,tp_Width,tp_Height;
};

struct coordPkt
{
  long cp_X,cp_Y,cp_W,cp_H;
  long cp_Col,cp_Row;
};

/*
 * X,Y,W,H - geben Werte in Pixeln an
 * Col,Row,Width,Height - in Felderpositionen
 */
/*
#ifdef __amigaos4__
	#ifdef __GNUC__
		#ifdef __PPC__
			#pragma pack()
		#endif
	#elif defined(__VBCC__)
		#pragma default-align
	#endif
#endif
*/
#endif  /* CELL_H */

