/* gClass-Diagram for ignition
 *
 * Copyright ©1996-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the GNU General Public License, version 3.
 */


#include <graphics/gfxmacros.h>

#include "gclass.h"
#include "gclass_protos.h"
#include "gclass_pragmas.h"

#define CATCOMP_NUMBERS
#include "ignition_strings.h"

#include <string.h>


const char *version = "$VER: line_diagram.gc 0.3 (7.8.2003)";

/** private instance structure **/

/*struct gLine
{
  UBYTE ga_Frame;
};*/

/** interface definition **/

//#define GAA_Frame GOA_TagBase+300

struct gInterface interface[] = {
//  {GAA_Frame,"Fläche durch einen Rahmen begrenzen",GIT_CHECKBOX,NULL,NULL},
	{GAA_Pseudo3D,"Pseudo-3D",GIT_CHECKBOX,NULL,NULL},
	{NULL,     NULL,NULL,NULL,NULL}
};

const STRPTR superClass = "diagram";
ULONG instanceSize = 0; //sizeof(struct gArea);
	
static struct Catalog *sCatalog;
 

void PUBLIC
draw(REG(d0, struct Page *page), REG(d1, ULONG dpi), REG(a0, struct RastPort *rp), REG(a1, struct gClass *gc), REG(a2, struct gDiagram *gd), REG(a3, struct gBounds *gb))
{
  struct gBounds *agb;
  /*struct gArea *this_ga = GINST_DATA(gc,gd);*/
  struct gLink *gl;
  long   pseudo3D,depth,offset;
  long   i,j,k;
  ULONG  color;

  gSuperDraw(page,dpi,rp,gc,gd,gb);

  gDoMethod(gd,GCM_GET,GAA_Bounds,&agb);
  gDoMethod(gd,GCM_GET,GAA_Pseudo3D,&pseudo3D);
  gDoMethod(gd,GCM_GET,GAA_DepthWidth,&depth);

  if (pseudo3D)
    offset = pixel(page, depth - GA_DEPTH_OFFSET, TRUE);

  j = gd->gd_Rows;

  for(k = 0;k < gd->gd_Rows;k++)
  {
    long right,left,x,y,width,zero;

    j--;  // Reihenfolge der Reihen verändern

    gDoMethod(gd,GCAM_GETBORDERS,j,&left,&right,&zero);
    width = right - left;
    if (gd->gd_Cols > 1)
      width /= gd->gd_Cols - 1;

    /** Oberseite **/
    if (pseudo3D)
    {
      //UBYTE lastsign,sign;
      //long lasty;

      for(x = left,i = 0;i < gd->gd_Cols;i++)
      {
        if (!(gl = gGetLink(gd,i,j)))
          continue;

        y = gDoMethod(gd,GCAM_GETCOORD,gl->gl_Value,j,1);

        if (y < agb->gb_Top)
          y = agb->gb_Top;
        else if (y > agb->gb_Bottom)
          y = agb->gb_Bottom;

        if (i != 0)
        {
          gAreaMove(x,y);
          gAreaDraw(x+offset,y-offset);

          gAreaEnd(rp);
        }
        else
          SetHighColor(rp,color = TintColor(gl->gl_Color,0.7f));

        if (i < gd->gd_Cols-1)
        {
          gAreaDraw(x+offset,y-offset);
          gAreaDraw(x,y);
        }
        x += width;
      }
    }

    /** Vorderseite **/
    if (!pseudo3D)
    {
      for(x = left,i = 0;i < gd->gd_Cols;i++)
      {
        if (!(gl = gGetLink(gd,i,j)))
          continue;

        y = gDoMethod(gd,GCAM_GETCOORD,gl->gl_Value,j,1);

        if (y < agb->gb_Top)
          y = agb->gb_Top;
        else if (y > agb->gb_Bottom)
          y = agb->gb_Bottom;

        if (i == 0)
        {
          SetHighColor(rp,color = gl->gl_Color);
          Move(rp,x,y);
        }
        else
          Draw(rp,x,y);

        x += width;
      }
    }
  }
  BNDRYOFF(rp);
}


ULONG set(struct gDiagram *gd,struct gArea *ga,struct TagItem *tstate)
{
  return GCPR_NONE;

/*  struct TagItem *ti;
  ULONG  rc = GCPR_NONE;

  if (tstate)
  {
    while(ti = NextTagItem(&tstate))
    {
      switch(ti->ti_Tag)
      {
        case GAA_Frame:
          if (ga->ga_Frame != ti->ti_Data)
          {
            ga->ga_Frame = ti->ti_Data;
            rc |= GCPR_REDRAW;
          }
          break;
      }
    }
  }
  return(rc);*/
}


ULONG PUBLIC dispatch(REG(a0, struct gClass *gc), REG(a1, struct gDiagram *gd), REG(a2, Msg msg))
{
//  struct gLine *gl = GINST_DATA(gc,gd);
  ULONG  rc;

  switch(msg->MethodID)
  {
    case GCM_NEW:
      if (rc = gDoSuperMethodA(gc,gd,msg))
      {
        set((struct gDiagram *)rc,NULL /*ga*/,((struct gcpSet *)msg)->gcps_AttrList);
      }
      break;
    case GCM_SET:
      rc = gDoSuperMethodA(gc,gd,msg) | set(gd,NULL /*ga*/,((struct gcpSet *)msg)->gcps_AttrList);
      break;
    case GCM_GET:
      rc = TRUE;

      switch(((struct gcpGet *)msg)->gcpg_Tag)
      {
        case GAA_Pseudo3DDepth:
          *((struct gcpGet *)msg)->gcpg_Storage = (ULONG)gd->gd_Rows;
          break;
        default:
          rc = gDoSuperMethodA(gc,gd,msg);
      }
      break;
    case GCDM_SETLINKATTR:
      if (rc = gDoSuperMethodA(gc,gd,msg))  // something has changed
      {
        struct gcpSetLinkAttr *gcps = (APTR)msg;
        ULONG  color = gcps->gcps_Color;
        ULONG  row = gcps->gcps_Link->gl_Row,i;
        struct gLink *gl;

        for(i = 0;i < gd->gd_Cols;i++)
        {
          if ((gl = gGetLink(gd,i,row)) == NULL)
            continue;

          if (color != ~0L)
            gl->gl_Color = color;
        }
        return(1L);
      }
      break;
    default:
	  return gDoSuperMethodA(gc, gd, msg);
  }
  return rc;
}


ULONG PUBLIC
freeClass(REG(a0, struct gClass *gc))
{
	CloseCatalog(sCatalog);
	return TRUE;
}


ULONG PUBLIC
initClass(REG(a0, struct gClass *gc))
{
	sCatalog = OpenCatalog(NULL, "ignition.catalog", OC_BuiltInLanguage, "deutsch", TAG_END);
	//interface[0].gi_Label = GetCatalogStr(sCatalog, MSG_AREA_OUTLINE_GAD, "Fläche durch einen Rahmen begrenzen");
	interface[0].gi_Label = GetCatalogStr(sCatalog, MSG_PSEUDO_3D_GAD, "Pseudo-3D");

	return TRUE;
}

