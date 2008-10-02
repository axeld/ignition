/* gClass-diagram for ignition
 *
 * Copyright �1996-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the GNU General Public License, version 3.
 */


#include <graphics/gfxmacros.h>

#include "gclass.h"
#include "gclass_protos.h"
#include "gclass_pragmas.h"

#define CATCOMP_NUMBERS
#include "ignition_strings.h"

#include <string.h>
#include <stdio.h>
#include <math.h>

#define reg(x) register __ ## x
#define PUBLIC __saveds __asm

extern void kprintf(STRPTR,...);
#define bug kprintf

#define DEGREE_STEPS PI/128

const char *version = "$VER: circle_diagram.gc 0.3 (7.8.2003)";

/** private instance structure **/

struct gCircle {
    UBYTE gc_Frame;
	UBYTE gc_Pseudo3D;
	ULONG gc_StartAngle;
};

/** interface definition **/

#define GCA_Frame		(GOA_TagBase + 300)
#define GCA_Pseudo3D	(GOA_TagBase + 301)
#define GCA_StartAngle (GOA_TagBase + 302)

struct gInterface interface[] = {
	{GCA_Frame, NULL /*"Fl�che durch einen Rahmen begrenzen"*/, GIT_CHECKBOX, NULL, NULL},
	{GCA_Pseudo3D, NULL /*"Pseudo-3D"*/, GIT_CHECKBOX, NULL, NULL},
	{GCA_StartAngle, NULL /*"Pseudo-3D"*/, GIT_TEXT, NULL, NULL},
	{NULL}
};

const STRPTR superClass = "diagram";
ULONG instanceSize = sizeof(struct gCircle);

static struct Catalog *sCatalog;


void
gAreaArcMove(long x, long y, long xradius, long yradius, double degree)
{
    gAreaDraw((long)(x + sin(degree) * xradius + 0.5), (long)(y + cos(degree) * yradius + 0.5));
}


void
gAreaArc(long x, long y, long xradius, long yradius, double degree)
{
    gAreaDraw((long)(x + sin(degree) * xradius + 0.5), (long)(y + cos(degree) * yradius + 0.5));
}


void
DrawArc(struct RastPort *rp, long x, long y, long xradius, long yradius, double start, double end)
{
    double degree;

    start = start * PI / 180.0;
    end = end * PI / 180.0;

    gAreaMove(x, y);

	for (degree = start; degree < end; degree += DEGREE_STEPS) {
        gAreaArc(x, y, xradius, yradius, degree);
    }

    if (degree > end)
        gAreaArc(x, y, xradius, yradius, end);

    gAreaEnd(rp);
}


void
drawSide(struct RastPort *rp, long x, long y, long xradius, long yradius, long height, double start, double end)
{
    double degree;

    start = start * PI / 180.0;
    end = end * PI / 180.0;

    gAreaArcMove(x, y + height, xradius, yradius, start);
    gAreaArc(x, y, xradius, yradius, start);

    for (degree = start; degree < end; degree += DEGREE_STEPS)
        gAreaArc(x, y, xradius, yradius, degree);

    if (degree > end)
        gAreaArc(x, y, xradius, yradius, end);

    gAreaArc(x, y + height, xradius, yradius, end);

    for (degree = end; degree > start; degree -= DEGREE_STEPS)
        gAreaArc(x, y + height, xradius, yradius, degree);

    gAreaEnd(rp);
}


void PUBLIC
draw(reg (d0) struct Page *page,reg (d1) ULONG dpi,reg (a0) struct RastPort *rp,reg (a1) struct gClass *gc,
    reg (a2) struct gDiagram *gd,reg (a3) struct gBounds *gb)
{
    struct gCircle *this_gc = GINST_DATA(gc, gd);
    struct gLink *gl;
    double total = 0.0, degree;
    long   i;
    long   x, y, xradius, yradius, height;

    gSuperDraw(page, dpi, rp, gc, gd, gb);

    x = gb->gb_Left + (gb->gb_Right - gb->gb_Left) / 2;
    y = gb->gb_Top + (height = gb->gb_Bottom - gb->gb_Top) / 2;
    xradius = (x - gb->gb_Left) * 0.96;
    yradius = (y - gb->gb_Top) * 0.96;

	if (this_gc->gc_Pseudo3D) {
        height /= 6;
        yradius -= height / 2;
        y -= height / 2;
    }

	for (i = 0; i < gd->gd_Cols; i++) {
		if (!(gl = gGetLink(gd, i, 0)) || gl->gl_Value <= 0)
			continue;

        total += gl->gl_Value;
    }

	// this prevents some ugly drawing problems...
	if (total == 0)
		total = 1;

    if (this_gc->gc_Frame)
        SetOutlinePen(rp, 1);

	degree = this_gc->gc_StartAngle;
	for (i = 0; i < gd->gd_Cols; i++) {
        double part;
		if (!(gl = gGetLink(gd, i, 0)) || gl->gl_Value < 0)
          continue;

        part = 360.0 * gl->gl_Value / total;

        SetHighColor(rp, gl->gl_Color);
        DrawArc(rp, x, y, xradius, yradius, degree, degree + part);

        degree += part;
    }

	if (this_gc->gc_Pseudo3D) {
		degree = this_gc->gc_StartAngle;
		for (i = 0; i < gd->gd_Cols; i++) {
            double part;
			if (!(gl = gGetLink(gd, i, 0)) || gl->gl_Value < 0)
              continue;

            part = 360.0 * gl->gl_Value / total;
			if (degree < 90.0 || degree + part > 270.0) {
                double start = degree, end = degree + part;

                SetHighColor(rp, TintColor(gl->gl_Color, 0.7f));

				if (start < 90.0 && end > 270.0) {
                    drawSide(rp, x, y, xradius, yradius, height, start, 90.0);
                    drawSide(rp, x, y, xradius, yradius, height, 270.0, end);
				} else {
                    if (start < 270.0 && end > 270.0)
                        start = 270.0;
                    if (start < 90.0 && end > 90.0)
                        end = 90.0;

                    drawSide(rp, x, y, xradius, yradius, height, start, end);
                }
            }

            degree += part;
        }
    }

    BNDRYOFF(rp);
}


ULONG
set(struct gDiagram *gd, struct gCircle *gc, struct TagItem *tstate)
{
    struct TagItem *ti;
    ULONG  rc = GCPR_NONE;

    if (tstate == NULL)
        return GCPR_NONE;

	while (ti = NextTagItem(&tstate)) {
		switch (ti->ti_Tag) {
            case GCA_Frame:
				if (gc->gc_Frame != ti->ti_Data) {
                    gc->gc_Frame = ti->ti_Data;
                    rc |= GCPR_REDRAW;
                }
                break;
            case GCA_Pseudo3D:
				if (gc->gc_Pseudo3D != ti->ti_Data) {
                    gc->gc_Pseudo3D = ti->ti_Data;
                    rc |= GCPR_REDRAW;
                }
                break;
			case GCA_StartAngle:
				gc->gc_StartAngle = 90;
				rc |= GCPR_REDRAW;
				break;
        }
    }

    return rc;
}


ULONG PUBLIC
dispatch(reg (a0) struct gClass *gc, reg (a1) struct gDiagram *gd, reg (a2) Msg msg)
{
    struct gCircle *this_gc = GINST_DATA(gc, gd);
    ULONG  rc;

	switch (msg->MethodID) {
        case GCM_NEW:
			if (rc = gDoSuperMethodA(gc, gd, msg)) {
                this_gc = GINST_DATA(gc, rc);
                this_gc->gc_Frame = 1;

                set((struct gDiagram *)rc, this_gc, ((struct gcpSet *)msg)->gcps_AttrList);
            }
            break;

        case GCM_SET:
            return gDoSuperMethodA(gc,gd,msg) | set(gd, this_gc, ((struct gcpSet *)msg)->gcps_AttrList);

        case GCM_GET:
            rc = TRUE;

			switch (((struct gcpGet *)msg)->gcpg_Tag) {
                case GCA_Frame:
                    *((struct gcpGet *)msg)->gcpg_Storage = (ULONG)this_gc->gc_Frame;
                    break;
                case GCA_Pseudo3D:
                    *((struct gcpGet *)msg)->gcpg_Storage = (ULONG)this_gc->gc_Pseudo3D;
                    break;
				case GCA_StartAngle:
				{
					char buffer[64];
					sprintf(buffer, "%ld Grad", this_gc->gc_StartAngle);
					*((struct gcpGet *)msg)->gcpg_Storage = (ULONG)AllocString(buffer);
					break;
				}
                default:
                    rc = gDoSuperMethodA(gc, gd, msg);
            }
            break;

        default:
            return gDoSuperMethodA(gc,gd,msg);
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
	interface[0].gi_Label = GetCatalogStr(sCatalog, MSG_AREA_OUTLINE_GAD, "Fl�che durch einen Rahmen begrenzen");
	interface[1].gi_Label = GetCatalogStr(sCatalog, MSG_PSEUDO_3D_GAD, "Pseudo-3D");
	interface[2].gi_Label = GetCatalogStr(sCatalog, /*ToDo!*/MSG_PSEUDO_3D_GAD, "Anfangswinkel:");

	return TRUE;
}


void __stdargs
_XCEXIT(void)
{
}
