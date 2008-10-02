/* image creating routines
 *
 * Copyright ©1996-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the GNU General Public License, version 3.
 */


#include "types.h"
#include "funcs.h"


struct Image *popImage, *toolImage[9];


void
FreeImageObj(struct ImageObj *io)
{
	if (io->io_Image->Depth == CUSTOMIMAGEDEPTH)
		DisposeObject(io->io_Image);
	else {
		FreeMem(io->io_Image->ImageData, (((io->io_Image->Width + 15) >> 4) << 1) * io->io_Image->Height * 3);
		FreePooled(pool, io->io_Image, sizeof(struct Image));
	}
	FreeString(io->io_Name);
	FreePooled(pool, io, sizeof(struct ImageObj));
}


void
FreeImage(struct Image *im)
{
	struct ImageObj *io;

	if (!im)
		return;

	for (io = (APTR)images.mlh_Head; io->io_Node.mln_Succ && io->io_Image != im; io = (APTR)io->io_Node.mln_Succ);
	if (io->io_Node.mln_Succ && io->io_Image == im) {
		if (--io->io_OpenCnt <= 0) {
			Remove((struct Node *)io);
			FreeImageObj(io);
		}
	}
}


void
RefreshImageObjs(struct Screen *scr)
{
	struct ImageObj *io;

	foreach (&images, io) {
		if (io->io_Image->Depth == CUSTOMIMAGEDEPTH)
			SetAttrs(io->io_Image, PDTA_Screen, scr, TAG_END);
	}
}


struct ImageObj *
AddImageObj(STRPTR t, struct Image *im)
{
	struct ImageObj *io;

	if (!im)
		return NULL;

	if (io = AllocPooled(pool, sizeof(struct ImageObj))) {
		io->io_Name = AllocString(t);
		io->io_OpenCnt = 1;
		io->io_Image = im;
		AddTail((struct List *)&images,(struct Node *)io);
	}

	return io;
}


struct Image *
InternalLoadImage(STRPTR t)
{
	struct FileInfoBlock __aligned fib;
	struct Image *im;
	long w, h, width;
	STRPTR buffer;
	APTR data;
	BPTR dat;

	if (im = NewObject(pictureiclass, NULL, DTA_Name, t, PIA_DelayLoad, TRUE, TAG_END))
		AddImageObj(t, im);
	else if ((dat = Open(t, MODE_OLDFILE)) && ExamineFH(dat, &fib)) {
		/* TODO: remove this?? */
		if (buffer = AllocPooled(pool, fib.fib_Size)) {
			if (fib.fib_Size == Read(dat, buffer, fib.fib_Size)) {
				Close(dat);  dat = NULL;
				if (!strncmp(buffer, "ign-icon", 8)) {
					// special ignition icon

					width = *(long *)(buffer + 8);
					w = ((width+15) >> 4) << 1;
					h = *(long *)(buffer+12);
					if (data = AllocMem(w*h*3,MEMF_CLEAR | MEMF_CHIP)) {
						CopyMem(buffer + 16, data, w * h * 3);

						if (im = AllocPooled(pool, sizeof(struct Image))) {
							im->Width = width;
							im->Height = h;
							im->Depth = 3;
							im->ImageData = data;
							im->PlanePick = 0x0007;
							im->PlaneOnOff = 0x0000;
							if (AddImageObj(t, im)) {
								FreePooled(pool, buffer, fib.fib_Size);
								return im;
							}
							FreePooled(pool, im, sizeof(struct Image));
						}
						FreeMem(data, w * h * 3);
					}
				}
			}
			FreePooled(pool, buffer, fib.fib_Size);
		}
		if (dat)
			Close(dat);
	}
	return im;
}


struct Image *
LoadImage(STRPTR t)
{
	struct ImageObj *io;
	struct Image *im;

	if (!t)
		return NULL;

	if (io = (struct ImageObj *)FindName((struct List *)&images, t)) {
		io->io_OpenCnt++;
		im = io->io_Image;
	} else if (!(im = InternalLoadImage(t))) {
		BPTR olddir,dir;

		if (dir = Lock(iconpath, SHARED_LOCK)) {
			olddir = CurrentDir(dir);

			im = InternalLoadImage(t);

			CurrentDir(olddir);
			UnLock(dir);
		}
	}
	return im;
}


void
FreeImages(void)
{
	long i;

	DisposeObject(popImage);

	for (i = 0; i < 9; i++) {
		DisposeObject(toolImage[i]);
	}
}


static void
CreateStyleImages(struct Screen *screen, struct TextAttr *ta, STRPTR t, long style)
{
	struct TextFont *tf;

	ta->ta_Style = style;
	if (tf = OpenBitmapFont(ta)) {
		SetFont(grp, tf);
		SetSoftStyle(grp, style, 0);
		itext.ITextFont = ta;
		itext.IText = t;
		itext.FrontPen = 1;
		PrintIText(grp, &itext, (boxwidth >> 1) - (IntuiTextLength(&itext) >> 1), 2);
		CloseFont(tf);
		itext.ITextFont = screen->Font;
	}
}


static struct Image *
AllocBitmapImage(struct Screen *screen, struct BitMap **bmA, struct BitMap **bmB, UWORD width, UWORD height)
{
	long depth = GetBitMapAttr(screen->RastPort.BitMap, BMA_DEPTH);

	if (*bmA = AllocBitMap(width, height, depth, BMF_MINPLANES, screen->RastPort.BitMap)) {
		if (*bmB = AllocBitMap(width, height, depth, BMF_MINPLANES, screen->RastPort.BitMap)) {
			struct Image *img;

			if (img = NewObject(bitmapiclass, NULL,
						IA_Width,           width,
						IA_Height,          height,
						BIA_Bitmap,         *bmA,
						BIA_SelectedBitmap, *bmB,
						TAG_END))
				return img;

			FreeBitMap(*bmB);
		}
		FreeBitMap(*bmA);
	}
	return NULL;
}


static void
PrepareBitmap(long selected,struct BitMap *bm,struct BitMap *selectedbm)
{
	if (selected) {
		grp->BitMap = selectedbm;
		SetAPen(grp,3);
		RectFill(grp,0,0,boxwidth-1,fontheight+2);
	} else {
		grp->BitMap = bm;
		EraseRect(grp,0,0,boxwidth-1,fontheight+2);
	}
}


void
AllocImages(struct Screen *screen)
{
	struct BitMap *bm,*selectedbm;
	struct TextFont *tf;
	struct TextAttr ta;
	long w,h,i,selected;

	grp->Layer = NULL;
	SetDrMd(grp,JAM2);

	if (popImage = AllocBitmapImage(screen, &bm, &selectedbm, boxwidth, fontheight + 4)) {
		for (selected = 0; selected < 2; selected++) {
			PrepareBitmap(selected, bm, selectedbm);

			/*SetOutlinePen(grp,1);*/  SetAPen(grp,1);
			w = boxwidth - 6;
			if (w % 2)
				w++;

			h = i = 2+fontheight*3/4;
			if (h-5 == 1+(w/2))
				i--;
			if (fontheight < 10)
				h++,i++;
			i -= 2;

			Move(grp,3,3);  Draw(grp,2+w/2,i);
			Move(grp,4,3);  Draw(grp,3+w/2,i);
			Move(grp,w+1,3);  Draw(grp,2+w/2,i);
			Move(grp,w+2,3);  Draw(grp,3+w/2,i);

			RectFill(grp, 3, h, boxwidth - 4, h + (fontheight < 10 ? 0 : 1));
			DrawBevelBox(grp, 0, 0, boxwidth, fontheight + 4, GT_VisualInfo, vi, GTBB_FrameType, BBFT_BUTTON,
				selected ? GTBB_Recessed : TAG_IGNORE, TRUE, TAG_END);
		}
	}

	ta = *screen->Font;  itext.DrawMode = JAM1;
	for (i = 0;i < 9;i++) {
		if (toolImage[i] = AllocBitmapImage(screen, &bm, &selectedbm, boxwidth, fontheight + 3)) {
			for (selected = 0; selected < 2; selected++) {
				PrepareBitmap(selected, bm, selectedbm);

				DrawBevelBox(grp, 0, 0, boxwidth, fontheight + 3, GT_VisualInfo, vi,
					GTBB_FrameType,							BBFT_BUTTON,
					selected ? GTBB_Recessed : TAG_IGNORE,	TRUE,
                    TAG_END);

				SetAPen(grp, 1);
				w = boxwidth-8;  h = (fontheight-2)/3;
				if (h*3 > fontheight-5)
					h--;

				switch (i) {
					case IMG_BOLD:
						CreateStyleImages(screen, &ta, GetString(&gLocaleInfo, MSG_FONT_BOLD_CHAR), FSF_BOLD);
						break;
					case IMG_ITALIC:
						CreateStyleImages(screen, &ta, GetString(&gLocaleInfo, MSG_FONT_ITALICS_CHAR), FSF_ITALIC);
						break;
					case IMG_UNDERLINED:
						CreateStyleImages(screen, &ta, GetString(&gLocaleInfo, MSG_FONT_UNDERLINED_CHAR), FSF_UNDERLINED);
						break;
					case IMG_JLEFT:
						Move(grp,4,3);  Draw(grp,4+w*7/10,3);
						Move(grp,4,3+h);  Draw(grp,3+w,3+h);
						Move(grp,4,3+h*2);  Draw(grp,4+w*8/10,3+h*2);
						Move(grp,4,3+h*3);  Draw(grp,4+w*4/10,3+h*3);
						break;
					case IMG_JCENTER:
						Move(grp,4,3);  Draw(grp,4+w,3);
						Move(grp,4+w*4/10,3+h);  Draw(grp,4+w*7/10,3+h);
						Move(grp,4+w*3/10,3+h*2);  Draw(grp,4+w*8/10,3+h*2);
						Move(grp,4+w*2/10,3+h*3);  Draw(grp,4+w*9/10,3+h*3);
						break;
					case IMG_JRIGHT:
						Move(grp,3+w,3);  Draw(grp,3+w*6/10,3);
						Move(grp,3+w,3+h);  Draw(grp,3+w*3/10,3+h);
						Move(grp,3+w,3+h*2);  Draw(grp,3+w*2/10,3+h*2);
						Move(grp,3+w,3+h*3);  Draw(grp,3+w*4/10,3+h*3);
						break;
					case IMG_JTOP:
						ta.ta_Name = "Times.font";  ta.ta_YSize = 11;  ta.ta_Style = 0;
						if (tf = OpenBitmapFont(&ta)) {
							SetFont(grp,tf);
							itext.ITextFont = &ta;
							itext.IText = GetString(&gLocaleInfo, MSG_VALIGN_TOP_CHAR);
							itext.FrontPen = 1;
							PrintIText(grp,&itext,(boxwidth >> 1)-(IntuiTextLength(&itext) >> 1),1);
							CloseFont(tf);
						}
						break;
					case IMG_JVCENTER:
						itext.IText = GetString(&gLocaleInfo, MSG_VALIGN_MIDDLE_CHAR);
						PrintIText(grp,&itext,(boxwidth >> 1)-(IntuiTextLength(&itext) >> 1),(fontheight-6) >> 1);
						break;
					case IMG_JBOTTOM:
						itext.IText = GetString(&gLocaleInfo, MSG_VALIGN_BOTTOM_CHAR);
						PrintIText(grp,&itext,(boxwidth >> 1)-(IntuiTextLength(&itext) >> 1),fontheight-7);
						break;
				}
			}
		}
	}
	itext.DrawMode = JAM2;
}
