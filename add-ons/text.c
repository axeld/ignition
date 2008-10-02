/* gClass for ignition
 *
 * Copyright �1996-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the GNU General Public License, version 3.
 */


#include "gclass.h"
#include "gclass_protos.h"
#include "gclass_pragmas.h"

#define CATCOMP_NUMBERS
#include "ignition_strings.h"

#include <string.h>

#define reg(x) register __ ## x
#define PUBLIC __saveds __asm

extern void kprintf(STRPTR,...);
#define bug kprintf

const char *version = "$VER: text.gc 0.2 (6.8.2003)";

struct gText {
	STRPTR gt_Text, gt_ShowText;
	struct Term *gt_Term;
	struct FontInfo *gt_FontInfo;
	ULONG gt_Color;
};

struct gInterface interface[] = {
	{GOA_Pen,      NULL/*"Textfarbe:"*/, GIT_PEN, NULL, NULL},
	{GOA_FontInfo, NULL, GIT_FONT, NULL, NULL},
	{GOA_Text,     NULL, GIT_FORMULA, NULL, NULL},
	{NULL}
};

const STRPTR superClass = "root";
ULONG instanceSize = sizeof(struct gText);

static struct Catalog *sCatalog;
 

void PUBLIC
draw(reg (d0) struct Page *page, reg (d1) ULONG dpi, reg (a0) struct RastPort *grp, reg (a1) struct gClass *gc,
	reg (a2) struct gObject *go, reg (a3) struct gBounds *gb)
{	
	struct gText *gt = GINST_DATA(gc, go);
	long w, h;
	long width = gb->gb_Right - gb->gb_Left;
	long height = gb->gb_Bottom - gb->gb_Top;

	if ((gt->gt_FontInfo = SetFontInfoA(gt->gt_FontInfo, dpi, NULL))
		&& (h = OutlineHeight(gt->gt_FontInfo, gt->gt_ShowText, -1)) < height)
	{
		w = OutlineLength(gt->gt_FontInfo, gt->gt_ShowText, -1);
		if (w < width) {
			SetHighColor(grp, gt->gt_Color);
			DrawText(grp, gt->gt_FontInfo, gt->gt_ShowText, gb->gb_Left + (width - w) / 2, gb->gb_Top + (height - h) / 2);
				// zentriert
		}
	}
}


ULONG
set(struct Page *page, struct gObject *go, struct gText *gt, struct TagItem *tstate)
{
	struct TagItem *ti;
	ULONG rc = GCPR_NONE;

	if (tstate == NULL)
		return GCPR_NONE;


	while (ti = NextTagItem(&tstate)) {
		switch (ti->ti_Tag) {
			case GOA_Text:
				// any changes to the text?
				if (!strcmp(gt->gt_Text ? gt->gt_Text : (STRPTR)"", ti->ti_Data ? (char *)ti->ti_Data : ""))
					break;

				FreeString(gt->gt_Text);
				FreeString(gt->gt_ShowText);
				DeleteTerm(gt->gt_Term);

				gt->gt_Text = AllocString((STRPTR)ti->ti_Data);
				gt->gt_Term = CreateTerm(page, gt->gt_Text);
				gt->gt_ShowText = CalcTerm(page, gt->gt_Text, gt->gt_Term, NULL);

				rc = GCPR_REDRAW;
				break;

			case GOA_FontInfo:
				FreeFontInfo(gt->gt_FontInfo);
				gt->gt_FontInfo = (struct FontInfo *)ti->ti_Data;
				rc = GCPR_REDRAW;
				break;

			case GOA_Pen:
				if (gt->gt_Color != ti->ti_Data) {
					gt->gt_Color = ti->ti_Data;
					rc = GCPR_REDRAW;
				}
				break;
		}
	}

	return rc;
}


ULONG PUBLIC
dispatch(reg (a0) struct gClass *gc, reg (a1) struct gObject *go, reg (a2) Msg msg)
{
	struct gText *gt = GINST_DATA(gc, go);
	ULONG rc = 0L;

	switch (msg->MethodID) {
		case GCM_NEW:
			if (rc = gDoSuperMethodA(gc, go, msg)) {
				go = (struct gObject *)rc;  gt = GINST_DATA(gc, go);

				go->go_Flags |= GOF_FRAMED;
				gt->gt_Color = 0x000000;
				gt->gt_FontInfo = NewFontInfoA(NULL, STANDARD_DPI, NULL);

				set(go->go_Page, go, gt, ((struct gcpSet *)msg)->gcps_AttrList);
			}
			break;

		case GCM_DISPOSE:
			FreeString(gt->gt_Text);
			FreeString(gt->gt_ShowText);
			FreeFontInfo(gt->gt_FontInfo);
			DeleteTerm(gt->gt_Term);

			rc = gDoSuperMethodA(gc, go, msg);
			break;

		case GCM_COPY:
		{
			struct gObject *cgo;

			if (cgo = (struct gObject *)(rc = gDoSuperMethodA(gc, go, msg))) {
				struct gText *cgt = GINST_DATA(gc, cgo);

				cgt->gt_Text = AllocString(gt->gt_Text);
				cgt->gt_Term = CopyTerm(gt->gt_Term);
				cgt->gt_ShowText = AllocString(gt->gt_ShowText);
				cgt->gt_FontInfo = CopyFontInfo(gt->gt_FontInfo);
			}
			break;
		}
		case GCM_SET:
			rc = gDoSuperMethodA(gc, go, msg) | set(go->go_Page, go, gt, ((struct gcpSet *)msg)->gcps_AttrList);
			break;

		case GCM_GET:
			rc = TRUE;

			switch (((struct gcpGet *)msg)->gcpg_Tag) {
				case GOA_Text:
					*((struct gcpGet *)msg)->gcpg_Storage = (ULONG)gt->gt_Text;
					break;
				case GOA_FontInfo:
					*((struct gcpGet *)msg)->gcpg_Storage = (ULONG)gt->gt_FontInfo;
					break;
				case GOA_Pen:
					*((struct gcpGet *)msg)->gcpg_Storage = gt->gt_Color;
					break;

				default:
					rc = gDoSuperMethodA(gc, go, msg);
			}
			break;

		case GCM_RECALC:
		{
			STRPTR t = gt->gt_ShowText;

			gt->gt_ShowText = CalcTerm(go->go_Page, gt->gt_Text, gt->gt_Term, NULL);

			if (strcmp(gt->gt_ShowText ? gt->gt_ShowText : (STRPTR)"", t ? t : (STRPTR)""))
				rc = GCPR_REDRAW;

			FreeString(t);
			break;
		}
		default:
			return gDoSuperMethodA(gc, go, msg);
  }

  return rc;
}


ULONG PUBLIC
freeClass(reg (a0) struct gClass *gc)
{
	CloseCatalog(sCatalog);
	return TRUE;
}


ULONG PUBLIC
initClass(reg (a0) struct gClass *gc)
{
	sCatalog = OpenCatalog(NULL, "ignition.catalog", OC_BuiltInLanguage, "deutsch", TAG_END);
	interface[0].gi_Label = GetCatalogStr(sCatalog, MSG_TEXT_COLOR_LABEL, "Textfarbe:");

	return TRUE;
}

