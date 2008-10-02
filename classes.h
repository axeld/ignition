/*
 * Several graphics base classes
 *
 * Copyright ©1996-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the GNU General Public License, version 3.
 */
#ifndef IGN_CLASSES_H
#define IGN_CLASSES_H


#include "graphic.h"


/*************************************** embedded-class ***************************************/

struct gEmbedded {
	struct Link ge_Link;
	struct gObject *ge_References;
	ULONG  ge_PageNumber,ge_Pos;
	ULONG  ge_Type;
};

#define GET_LINK 0	/* ge_Type */
#define GET_DIAGRAM 1
#define GET_UNRESOLVED 4096

#define GEA_References   GOA_TagBase + 100
#define GEA_Type         GOA_TagBase + 101
#define GEA_AdoptSize    GOA_TagBase + 102

extern ULONG PUBLIC gEmbeddedDispatch(reg (a0) struct gClass *gc,reg (a1) struct gObject *go,reg (a2) Msg msg);
extern void PUBLIC gEmbeddedDraw(reg (d0) struct Page *page,reg (d1) ULONG dpi,reg (a0) struct RastPort *rp,reg (a1) struct gClass *gc,reg (a2) struct gObject *go,reg (a3) struct gBounds *gb);

extern struct gInterface gEmbeddedInterface[];
extern struct gInterface gEmbedDiagramInterface[];


/*************************************** picture-class ***************************************/

struct gPicture {
	STRPTR 	gp_Name;
	STRPTR 	gp_FileName;
	struct 	Term *gp_Term;
	struct 	Image *gp_Image;
	LONG   	gp_Width,gp_Height;
	bool	gp_KeepAspectRatio;
	bool	gp_Center;
};

#define GPA_FileName		GOA_TagBase + 200
#define GPA_RealSize		GOA_TagBase + 201
#define GPA_KeepAspectRatio	GOA_TagBase + 202
#define GPA_Center			GOA_TagBase + 203

extern ULONG PUBLIC gPictureDispatch(reg (a0) struct gClass *gc,reg (a1) struct gObject *go,reg (a2) Msg msg);
extern void PUBLIC gPictureDraw(reg (d0) struct Page *page,reg (d1) ULONG dpi,reg (a0) struct RastPort *rp,reg (a1) struct gClass *gc,reg (a2) struct gObject *go,reg (a3) struct gBounds *gb);

extern struct gInterface gPictureInterface[];


/*************************************** diagrams ***************************************/

extern struct gInterface gDiagramInterface[];
extern struct gInterface gAxesInterface[];


/*************************************** class definitions ***************************************/
/*
extern const STRPTR gcNames[];
extern const STRPTR gcSuper[];
extern const UBYTE  gcTypes[];
extern const STRPTR gcLabels[];
extern const STRPTR gcImages[];
extern const APTR   gcDispatch[];
extern const APTR   gcDraw[];
extern struct gInterface *gcInterface[];
extern const ULONG  gcObjSize[];
*/

/*************************************** prototypes ***************************************/

// classes.c
extern void FreeLoadedGObjectTags(struct TagItem *tags);
extern struct TagItem *LoadGObjectTags(struct gcpIO *gcpio);
extern void SaveGInterface(struct gcpIO *gcpio,struct gInterface *gi,struct gObject *go);

// objects.c
extern ULONG PUBLIC gRootDispatch(reg (a0) struct gClass *gc,reg (a1) struct gObject *go,reg (a2) Msg msg);

// diagram.c
extern ULONG PUBLIC gDiagramDispatch(reg (a0) struct gClass *gc,reg (a1) struct gDiagram *gd,reg (a2) Msg msg);
extern ULONG PUBLIC gDiagram3dDispatch(reg (a0) struct gClass *gc,reg (a1) struct gDiagram3d *gd,reg (a2) Msg msg);
extern void PUBLIC gDiagram3dDraw(reg (d0) struct Page *page,reg (d1) ULONG dpi,reg (a0) struct RastPort *rp,reg (a1) struct gClass *gc,reg (a2) struct gObject *go,reg (a3) struct gBounds *gb);
extern ULONG PUBLIC gAxesDispatch(reg (a0) struct gClass *gc,reg (a1) struct gObject *go,reg (a2) Msg msg);
extern void PUBLIC gAxesDraw(reg (d0) struct Page *page,reg (d1) ULONG dpi,reg (a0) struct RastPort *rp,reg (a1) struct gClass *gc,reg (a2) struct gObject *go,reg (a3) struct gBounds *gb);
extern ULONG PUBLIC gBalkenDispatch(reg (a0) struct gClass *gc,reg (a1) struct gObject *go,reg (a2) Msg msg);
extern void PUBLIC gBalkenDraw(reg (d0) struct Page *page,reg (d1) ULONG dpi,reg (a0) struct RastPort *rp,reg (a1) struct gClass *gc,reg (a2) struct gObject *go,reg (a3) struct gBounds *gb);
extern ULONG PUBLIC gBalken3dDispatch(reg (a0) struct gClass *gc,reg (a1) struct gObject *go,reg (a2) Msg msg);
extern void PUBLIC gBalken3dDraw(reg (d0) struct Page *page,reg (d1) ULONG dpi,reg (a0) struct RastPort *rp,reg (a1) struct gClass *gc,reg (a2) struct gObject *go,reg (a3) struct gBounds *gb);
extern ULONG PUBLIC gEmbedDiagramDispatch(reg (a0) struct gClass *gc,reg (a1) struct gObject *go,reg (a2) Msg msg);
extern void PUBLIC gEmbedDiagramDraw(reg (d0) struct Page *page,reg (d1) ULONG dpi,reg (a0) struct RastPort *rp,reg (a1) struct gClass *gc,reg (a2) struct gObject *go,reg (a3) struct gBounds *gb);


#endif   /* IGN_CLASSES_H */

