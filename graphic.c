/* General and 2D graphics routines
 *
 * Copyright ©1996-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the GNU General Public License, version 3.
 */


#include "types.h"
#include "funcs.h"
#include "classes.h"
#include <safeclip.h>


#define AREABUFFERS 300

struct MinList colors;
struct RastPort *grp, *doublerp, *irp;
static struct Layer_Info *gli;
static struct TmpRas sTempRaster;
static struct AreaInfo sAreaInfo;
static PLANEPTR sTempBitmap = NULL;
static APTR *sAreaBuffer = NULL;


void
gInitArea(long xmin, long ymin, long xmax, long ymax)
{
	CLP_xmin = xmin;
	CLP_ymin = ymin;
	CLP_xmax = xmax;
	CLP_ymax = ymax;
}


void PUBLIC
libAreaMove(reg (d0) LONG x, reg (d1) LONG y)
{
	gAreaMove(NULL, x, y);
}


void PUBLIC
libAreaDraw(reg (d0) LONG x, reg (d1) LONG y)
{
	gAreaDraw(NULL, x, y);
}


void PUBLIC
libAreaEnd(reg (a0) struct RastPort *rp)
{
	gAreaEnd(rp);
}


ULONG PUBLIC
GetDPI(reg (a0) struct Page *page)
{
	return page->pg_DPI;
}


LONG PUBLIC
GetOffset(reg (a0) struct Page *page,reg (d0) BOOL horiz)
{
	return horiz ? page->pg_wTabX - page->pg_TabX : page->pg_wTabY - page->pg_TabY;
}


void
RectFill32(struct RastPort *rp, long x1, long y1, long x2, long y2)
{
	x1 = max(x1, 0);  y1 = max(y1, 0);
	x2 = min(x2, 32567);  y2 = min(y2, 32567);
	RectFill(rp, x1, y1, x2, y2);
}


void
DrawHorizBlock(struct RastPort *rp, ULONG dpi, long x1, long y, long x2, ULONG points, UWORD flags)
{
	long width;

	width = (points * (dpi & 0xffff)) / (72*256);

	if (x2 < x1)
		RectFill(rp, x2, y - width, x1, y);
	else
		RectFill(rp, x1, y, x2, y + width);
}


void
DrawVertBlock(struct RastPort *rp, ULONG dpi, long x, long y1, long y2, ULONG points, UWORD flags)
{
	long width;

	width = (points * (dpi >> 16)) / (72*256);

	if (y2 < y1)
		RectFill(rp, x - width, y2, x, y1);
	else
		RectFill(rp, x, y1, x + width, y2);
}


void PUBLIC
DrawLine(reg (a0) struct RastPort *rp,reg (d0) ULONG dpi,reg (d1) long x1,reg (d2) long y1,reg (d3) long x2,reg (d4) long y2,reg (d5) ULONG points,reg (d6) UWORD flags)
{
	double f,a,b,c,border;
	long pen,xa,yb;

	grp->Layer = rp->Layer;   /* MERKER: das Zeugs könnte und sollte raus */
	grp->BitMap = rp->BitMap;
	pen = GetAPen(rp);
	SetAPen(grp, pen);
	SetOutlinePen(grp, pen);   /* MERKER: Darf die das?? */

	f = ((double)(dpi >> 16))/((double)(dpi & 0xffff));
	a = (double)(y2 - y1)*f;
	b = (double)(x2 - x1);
	c = sqrt(a*a + b*b);
	border = ((double)points*(dpi >> 16))/9437184.0;   // (72.0*65536.0*2)
	xa = (long)(border * a/c+0.5);  yb = -(long)((border*b/c)+0.5)/f;

	if (xa || yb) {
		gAreaMove(grp, x1 + xa, y1 + yb);
		gAreaDraw(grp, x2 + xa, y2 + yb);
		gAreaDraw(grp, x2 - xa, y2 - yb);
		gAreaDraw(grp, x1 - xa, y1 - yb);
		gAreaEnd(grp);
	} else {
		Move(rp, x1, y1);
		Draw(rp, x2, y2);
	}
	grp->Flags &= ~AREAOUTLINE;
}


void
FreeTmpRas(void)
{
	if (sTempBitmap)
		FreeVec(sTempBitmap);
}


void
MakeTmpRas(long width, long height)
{
	long bytes = ((width + 15) >> 3)*height;

	FreeTmpRas();
	if (sTempBitmap = AllocVec(bytes, MEMF_CHIP | MEMF_CLEAR))
		grp->TmpRas = InitTmpRas(&sTempRaster, sTempBitmap, bytes);

	gInitArea(0, 0, width - 1, height - 1);
}


void
FreeDoubleBufferBitMap(void)
{
	if (doublerp) {
		DeleteLayer(NULL, doublerp->Layer);
		FreeBitMap(doublerp->BitMap);
		doublerp->BitMap = NULL;
	}
}


void
AllocDoubleBufferBitMap(struct Screen *scr)
{
	if (doublerp) {
		if (doublerp->BitMap = AllocBitMap(scr->Width,scr->Height,GetBitMapAttr(scr->RastPort.BitMap,BMA_DEPTH),BMF_MINPLANES,scr->RastPort.BitMap))
			doublerp->Layer = CreateUpfrontLayer(gli,doublerp->BitMap,0,0,scr->Width-1,scr->Height-1,LAYERSIMPLE,NULL);
		else
			FreeDoubleBuffer();
	}
}


void
FreeDoubleBuffer(void)
{
	if (!doublerp)
		return;

	if (doublerp->BitMap)
		FreeDoubleBufferBitMap();

	DisposeLayerInfo(gli);
	FreePooled(pool, doublerp, sizeof(struct RastPort));
	doublerp = NULL;
}


void
InitDoubleBuffer(void)
{
	if (doublerp = AllocPooled(pool,sizeof(struct RastPort)))
	{
		gli = NewLayerInfo();
		InitRastPort(doublerp);
	}
}


void
FreeGraphics(void)
{
	FreeGClasses();

	if (sAreaBuffer)
		FreePooled(pool, sAreaBuffer, AREABUFFERS * 5);

	SafeClose();  /* safe area-functions by Peter Knight */
	FreeTmpRas();
	if (grp)
		FreePooled(pool, grp, sizeof(struct RastPort));

	FreeDoubleBuffer();
	if (irp)
		FreePooled(pool, irp, sizeof(struct RastPort));
}


void
InitGraphics(void)
{
	struct colorPen *cp;
	long   i;
	char   t[16];

	InitGClasses();

	if (IsListEmpty((struct List *)&colors)) {
		AddColor(&colors, NULL, 170, 170, 170);   // grey
		AddColor(&colors, NULL,   0,   0,   0);   // black
		AddColor(&colors, NULL, 255, 255, 255);   // white
		AddColor(&colors, NULL, 101, 138, 186);   // blue
		AddColor(&colors, NULL,  85, 223,  85);   // green
		AddColor(&colors, NULL, 239,  69,  69);   // red
		AddColor(&colors, NULL, 255, 239,  69);   // yellow
		AddColor(&colors, NULL,  97,  97,  97);   // dark grey
	}

	NewList(&scrcolors);
	for (i = 0; i < 8; i++) {
		if (cp = AllocPooled(pool, sizeof(struct colorPen))) {
			sprintf(t, GetString(&gLocaleInfo, MSG_COLOR), i + 1);
			cp->cp_Node.ln_Name = AllocString(t);
			cp->cp_Pen = i;
			cp->cp_Red = standardPalette[i * 3 + 1] >> 24;
			cp->cp_Green = standardPalette[i * 3 + 2] >> 24;
			cp->cp_Blue = standardPalette[i * 3 + 3] >> 24;
			AddTail(&scrcolors, cp);
		}
	}

	if (grp = AllocPooled(pool, sizeof(struct RastPort))) {
		InitRastPort(grp);
		if (sAreaBuffer = AllocPooled(pool, AREABUFFERS * 5))
			InitArea(grp->AreaInfo = &sAreaInfo, sAreaBuffer, AREABUFFERS);
		SafeInit(AREABUFFERS * 5);
		MakeTmpRas(800, 600);
	}
	if (irp = AllocPooled(pool, sizeof(struct RastPort)))
		InitRastPort(irp);
}


#define JSR 0x4ef9

struct {
	UWORD jsr;
	APTR func;
} gClassFuncTable[] = {
	/* -210 */		  {JSR, SetOutlineColor},
	/* -204 */		  {JSR, SetLowColor},
	/* -198 */		  {JSR, gGetLink},
	/* -192 */		  {JSR, gSuperDraw},
	/* -186 */		  {JSR, TintColor},
	/* -180 */		  {JSR, gInsertRemoveCellsTerm},
	/* -174 */		  {JSR, gInsertRemoveCellsTablePos},
	/* -168 */		  {JSR, CalcTerm},
	/* -162 */		  {JSR, CopyTerm},
	/* -156 */		  {JSR, DeleteTerm},
	/* -150 */		  {JSR, CreateTerm},
	/* -144 */		  {JSR, mm},
	/* -138 */		  {JSR, pixel},
	/* -132 */		  {JSR, OutlineHeight},
	/* -126 */		  {JSR, OutlineLength},
	/* -120 */		  {JSR, DrawText},
	/* -114 */		  {JSR, NewFontInfoA},
	/* -108 */		  {JSR, CopyFontInfo},
	/* -102 */		  {JSR, SetFontInfoA},
	/*  -96 */		  {JSR, FreeFontInfo},
	/*  -90 */		  {JSR, GetOffset},
	/*  -84 */		  {JSR, GetDPI},
	/*  -78 */		  {JSR, libAreaEnd},
	/*  -72 */		  {JSR, libAreaDraw},
	/*  -66 */		  {JSR, libAreaMove},
	/*  -60 */		  {JSR, DrawLine},
	/*  -54 */		  {JSR, DrawRect},
	/*  -48 */		  {JSR, FindColorPen},
	/*  -42 */		  {JSR, SetColors},
	/*  -36 */		  {JSR, SetHighColor},
	/*  -30 */		  {JSR, gDoSuperMethodA},
	/*  -24 */		  {JSR, gDoMethodA},
	/*  -18 */		  {JSR, FreeString},
	/*  -12 */		  {JSR, AllocString},
	/*   -6 */		  {JSR, AllocStringLength}
};

int32 gClassFuncTableSize = sizeof(gClassFuncTable);

