#ifndef IOTYPE_H
#define IOTYPE_H
/* $VER: iotype.h 0.5 (1.3.2001)
** Developer Release 0.1
**
** ignition IO-module definitions
**
** Copyright ©2001-2008 pinc Software
** All Rights Reserved
*/

#include <exec/types.h>
#include <exec/lists.h>
#include <exec/nodes.h>
#include <exec/memory.h>
#include <dos/dos.h>

#include <clib/exec_protos.h>
#include <clib/dos_protos.h>
#include <clib/alib_stdio_protos.h>
#include <pragmas/exec_pragmas.h>
#include <pragmas/dos_pragmas.h>

#include <string.h>
#include <math.h>

#define foreach(l,v) for(v = (APTR)((struct List *)l)->lh_Head;((struct Node *)v)->ln_Succ;v = (APTR)((struct Node *)v)->ln_Succ)

#ifndef CELL_H
#include "cell.h"
#endif

#include "SDI_compiler.h"

/*** Project related ***/

struct Event
{
  UBYTE  ev_Type;
  STRPTR ev_Script;
  long   ev_Intervall;
};

#define EVT_NONE 0
#define EVT_INTERN 1
#define EVT_EXTERN 2

#define EVT_START 0
#define EVT_END 1
#define EVT_FIELDSELECT 2
#define EVT_FIELDEND 3
#define EVT_TIME 4
#define EVT_CALC 5
#define EVT_LBUTTON 6
#define EVT_RBUTTON 7
#define NUM_EVENTS 8

#define PG_DINA3 0      // Seitengrößen
#define PG_DINA4 1
#define PG_DINA5 2
#define PG_USLETTER 3
#define PG_USLEGAL 4

struct Mappe
{
  struct Node mp_Node;
  long   mp_Flags;
  STRPTR mp_Path;
  struct MinList mp_Pages;
  ULONG  mp_mmWidth,mp_mmHeight;
  ULONG  mp_MediumWidth,mp_MediumHeight;
  ULONG  mp_mmMediumWidth,mp_mmMediumHeight;
  struct MinList mp_Projects;
  struct Page *mp_actPage;
  struct Window *mp_Window;
  struct Event mp_Events[NUM_EVENTS];
  struct MinList mp_Names;
  struct MinList mp_Databases;
  struct MinList mp_Masks;
  long   mp_Modified;
  ULONG  mp_FileType;
};

#define MPF_SCRIPTS 1
#define MPF_NOTES 2
#define MPF_PAGEMARKED 4     /* Seitenbegrenzung */
#define MPF_PAGEONLY 8
#define MPF_UNNAMED 16
#define MPF_CUSIZE 32        /* Cell-Update */
#define MPF_CUTIME 64

struct Page
{
  struct Node pg_Node;
  struct Window *pg_Window;
  struct Mappe *pg_Mappe;
  long   pg_Width,pg_Height;
  BYTE   pg_Flags;
  long   pg_Cols,pg_Rows;
  struct MinList pg_Table;
  struct tableSize *pg_tfWidth,*pg_tfHeight;
  UWORD  pg_wTabX,pg_wTabY,pg_wTabW,pg_wTabH;
  long   pg_MarkCol,pg_MarkRow,pg_MarkWidth,pg_MarkHeight;
  long   pg_MarkX1,pg_MarkY1,pg_MarkX2,pg_MarkY2;
  long   pg_SelectCol,pg_SelectRow,pg_SelectWidth,pg_SelectHeight;
  struct Rect32 pg_Select;
  WORD   pg_SelectPos,pg_SelectLength;
  struct Node *pg_Family;
  ULONG  pg_DPI;
  ULONG  pg_PointHeight;
  long   pg_Style;
  struct {
           struct coordPkt cp;
           WORD DispPos;
           WORD FirstChar;
           struct tableField *tf;
           STRPTR Undo;
         } pg_Gad;
  long   pg_TabW,pg_TabH;     /* scroller gadgets */
  long   pg_TabX,pg_TabY;
  ULONG  pg_APen,pg_BPen;
  UWORD  pg_Zoom;             /* in percent */
  UWORD  pg_StdWidth,pg_StdHeight;
  ULONG  pg_mmStdWidth,pg_mmStdHeight;
  double pg_PropFactorX,pg_PropFactorY;
  struct MinList pg_gFrames;
  UBYTE  pg_FrameAction;
  UBYTE  pg_HotSpot;
  struct UndoNode *pg_CurrentUndo;
  struct MinList pg_Undos;
};

#define PGS_IGNORE -3        /* TabGadget-Status */
#define PGS_NONE -2
#define PGS_FRAME -1

#define PGFA_NONE 0          /* FrameAction */
#define PGFA_GENERATE 1
#define PGFA_MOVEHORIZ 2
#define PGFA_MOVEVERT 4
#define PGFA_MOVE 6
#define PGFA_SIZEHORIZ 8
#define PGFA_SIZEVERT 16
#define PGFA_SIZE 24
#define PGFA_MULTISELECT 32
#define PGFA_REFRESH 128

#define PGHS_CELL 0          /* HotSpot */
#define PGHS_OBJECT 1

#define PWA_NONE 0   /* Project Window Actions (wd_ExtData[6]) */
#define PWA_TITLE 1
#define PWA_MARK 2
#define PWA_CELL 3
#define PWA_FRAME 4

#define HTS_BEGIN 1  /* HideTableSpecial()-Modes */
#define HTS_END 2

#define CCS_STANDARD 0   /* ChangeCellSize()-Modes */
#define CCS_OPTWIDTH 1
#define CCS_OPTHEIGHT 2
#define CCS_MINWIDTH 4
#define CCS_MINHEIGHT 8

/*************************** Funktionen ***************************/


typedef enum {OP_OPEN = -6,OP_CLOSE,OP_TEXT,OP_VALUE,OP_CELL,OP_EXTCELL,
              OP_NONE,OP_GREATER,OP_EQGREATER,OP_LESS,OP_EQLESS,OP_EQUAL,
              OP_NOTEQUAL,OP_BITAND,OP_BITOR,OP_OR,OP_AND,OP_ADD,OP_SUB,
              OP_MUL,OP_DIV,OP_MOD,OP_NEG,OP_FAK,OP_BITNOT,OP_POT,OP_RANGE,
              OP_NAME,OP_TEXTVALUE,OP_FUNC} OPs;

struct FuncArg
{
  struct MinNode fa_Node;
  struct Term *fa_Root;
};

struct Function
{
  struct Node f_Node;
  double (*f_Value)(struct MinList *);
  STRPTR (*f_Text)(struct MinList *);
  UBYTE  (*f_RC)(struct MinList *);
  STRPTR f_Help;
  UBYTE  f_FormatFrom;
};

struct MaskField
{
  struct Node mf_Node;
  ULONG  mf_Col,mf_Row;
};

struct Mask
{
  struct Node ma_Node;
  struct Page *ma_Page;
  struct MinList ma_Fields;
};

struct Field
{
  struct Node fi_Node;
  STRPTR fi_Special;
};

#define FIT_STANDARD 0   /* fi_Node.ln_Type */
#define FIT_REFERENCE 1
#define FIT_CHOICE 2
#define FIT_COUNTER 3

struct Database
{
  struct Node db_Node;
  STRPTR db_Content;
  struct Term *db_Root;
  struct Page *db_Page;
  ULONG  db_PageNumber;
  struct MinList db_Fields;
  struct tablePos db_TablePos;
  ULONG  db_Current;
  UBYTE  db_IndexType;
  union
  {
    struct tablePos db_indexpos;
    struct MinList db_index;
  } db_index;
};

#define DBIT_NONE 0
#define DBIT_INTERN 1
#define DBIT_CELLS 2

#define db_IndexPos db_index.db_indexpos
#define db_Index db_index.db_index

struct Name
{
  struct Node nm_Node;
  STRPTR nm_Content;
  struct Term *nm_Root;
  struct Page *nm_Page;
  ULONG  nm_PageNumber;
};

#define NMT_NONE 0
#define NMT_SEARCH 1
#define NMT_DATABASE 2
#define NMT_REALDATABASE 3  // is set in db_Node.ln_Type
#define NMT_UNDEFINED 128   // as long nm_Page is not defined

struct Term
{
  struct Term *t_Left, *t_Right;
  OPs    t_Op;
  BYTE   t_Pri;
  union {
    struct {
             double t_value;
             STRPTR t_text;
           } t_val;
    struct {
             long t_col,t_row;
             BYTE t_abscol,t_absrow;
           } t_cell;
    struct {
             struct Function *t_function;
             struct MinList t_args;
           } t_func;
    struct {
             long t_col,t_row;
             STRPTR t_page;
             long   t_numpage;
             STRPTR t_mappe;
           } t_ext;
  } t_type;
};

#define t_Value t_type.t_val.t_value
#define t_Text t_type.t_val.t_text
#define t_Col t_type.t_cell.t_col
#define t_Row t_type.t_cell.t_row
#define t_AbsCol t_type.t_cell.t_abscol
#define t_AbsRow t_type.t_cell.t_absrow
#define t_Function t_type.t_func.t_function
#define t_Args t_type.t_func.t_args
#define t_Page t_type.t_ext.t_page
#define t_NumPage t_type.t_ext.t_numpage
#define t_Mappe t_type.t_ext.t_mappe


/*************************** Colors ***************************/

struct colorPen
{
  struct Node cp_Node;
  WORD   cp_Pen;
  UBYTE  cp_Red,cp_Green,cp_Blue;
  WORD   cp_PenA,cp_PenB;
  UBYTE  cp_Pattern;
  ULONG  cp_ID;
};

/* cp_Node.ln_Type == 1 -> Name wurde von FindColorName() gewählt
**
** cp_PenA,cp_PenB,cp_Pattern werden z.Z. nicht benutzt
*/

/*************************** Fonts ***************************/

#define FS_PLAIN 0
#define FS_BOLD 1
#define FS_ITALIC 2
#define FS_UNDERLINED 4
#define FS_UNSET 65536

/*************************** Preferences ***************************/

#define ID_IGNP  MAKE_ID('I','G','N','P')
#define ID_VERSION MAKE_ID('V','E','R','S')
#define IGNP_VERSION 0

#define ID_CMD   MAKE_ID('C','M','D',' ')
#define ID_CMDS  MAKE_ID('C','M','D','S')
#define ID_MENU  MAKE_ID('M','E','N','U')
#define ID_ICON  MAKE_ID('I','C','O','N')
#define ID_DISP  MAKE_ID('D','I','S','P')
#define ID_KEYS  MAKE_ID('K','E','Y','S')
#define ID_COLORS   MAKE_ID('C','O','L','S')
#define ID_SCREEN   MAKE_ID('S','C','R','N')
#define ID_FILE   MAKE_ID('F','I','L','E')
#define ID_FORMAT MAKE_ID('F','M','T',' ')
#define ID_TABLE  MAKE_ID('T','A','B','L')

#define PRF_DISP (1 << 0)
#define PRF_FILE (1 << 1)
#define PRF_SCREEN (1 << 2)
#define PRF_KEYS (1 << 3)
#define PRF_FORMAT (1 << 4)
#define PRF_PRINTER (1 << 5)
#define PRF_COLORS (1 << 6)
#define PRF_TABLE (1 << 7)
#define PRF_ICON (1 << 8)
#define PRF_CMDS (1 << 9)
#define PRF_MENU (1 << 10)

struct PrefDisp
{
  BYTE   pd_Rasta;
  struct TextFont *pd_AntiFont;
  struct TextAttr pd_AntiAttr;
  BYTE   pd_HelpBar,pd_ToolBar;
  BYTE   pd_IconBar,pd_FormBar;
  BYTE   pd_ShowAntis;
};

#define PDR_NONE 0       // Rasta look
#define PDR_POINTS 1
#define PDR_LINE 2

#define PDIB_NONE 0      // Bar positions
#define PDIB_LEFT 1
#define PDIB_TOP 2
#define PDFB_NONE 0
#define PDFB_BOTTOM 1
#define PDFB_TOP 2

#define PS_NAMELEN 64

struct PrefScreen
{
  UWORD  ps_Width, ps_Height, ps_Depth;
  UWORD  ps_dimWidth,ps_dimHeight;
  long   ps_ModeID, ps_Overscan;
  BYTE   ps_Interleaved;
  short  ps_Type;
  char   ps_PubName[PS_NAMELEN];
  BYTE   ps_BackFill;
  LONG   ps_BFColor;
  ULONG  ps_mmWidth,ps_mmHeight;
  struct TextFont *ps_Font;
  struct TextAttr ps_TextAttr;
};

#define PST_PUBLIC 0
#define PST_LIKEWB 1
#define PST_OWN 2

struct PrefFile
{
  BYTE   pf_CreateIcons,pf_Backup,pf_NoSuffix,pf_AutoSave;
  long   pf_AutoSaveIntervall;     /* in seconds */
};

#define PFAS_OFF 0          /* pf_AutoSave */
#define PFAS_REMEMBER 1
#define PFAS_ON 2

struct PrefTable
{
  UWORD pt_Flags;
};

#define PTF_SHOWFORMULA 1
#define PTF_SHOWZEROS 2
#define PTF_AUTOCELLSIZE 4
#define PTF_AUTOCENTURY 8
#define PTF_MARKSUM 16
#define PTF_MARKAVERAGE 32

struct PrefIcon
{
  UBYTE  pi_Width,pi_Height;
  UBYTE  pi_Spacing;
};

/***************************** interne Funktionen *******************************/

void   Error(STRPTR fmt,...);
void   ErrorA(STRPTR fmt,APTR args);
struct Page *NewPage(struct Mappe *mp);
void   CalculatePageDPI(struct Page *page);
struct Cell *NewCell(struct Page *page,LONG col,LONG row);
void   UpdateCellText(struct Page *,struct Cell *);
void   SetTableSize(struct Page *,LONG,LONG);
STRPTR Coord2String(BOOL,LONG,BOOL,LONG);
LONG   pixel(struct Page *,LONG,BOOL);
LONG   mm(struct Page *,LONG,BOOL);
ULONG  FindColorPen(UBYTE r,UBYTE g,UBYTE b);
struct colorPen *AddPen(STRPTR name,UBYTE r,UBYTE g,UBYTE b);
STRPTR AllocStringLength(STRPTR,LONG);
STRPTR AllocString(STRPTR);
void   FreeString(STRPTR);
STRPTR ita(double d,long komma ,UBYTE flags);

#pragma tagcall ioBase Error 5a 9802
#pragma libcall ioBase ErrorA 5a 9802
#pragma libcall ioBase NewPage 54 801
#pragma libcall ioBase CalculatePageDPI 4e 801
#pragma libcall ioBase NewCell 48 10803
#pragma libcall ioBase UpdateCellText 42 9802
#pragma libcall ioBase SetTableSize 3c 10803
#pragma libcall ioBase FindColorPen 36 21003
#pragma libcall ioBase AddPen 30 210804
#pragma libcall ioBase Coord2String 2a 321004
#pragma libcall ioBase pixel 24 10803
#pragma libcall ioBase mm 1e 10803
#pragma libcall ioBase AllocStringLength 18 0802
#pragma libcall ioBase AllocString 12 801
#pragma libcall ioBase FreeString c 801
#pragma libcall ioBase ita 6 32003

/********************************* Variables ************************************/

extern APTR pool,ioBase;
extern struct Library *DOSBase;

#endif  /* IOTYPE_H */
