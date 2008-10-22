/*
 * Copyright ©1999-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the MIT License.
 */
#ifndef GTDRAG_INCLUDES_H
#define GTDRAG_INCLUDES_H

#define INTUI_V36_NAMES_ONLY

#include <exec/execbase.h>
#include <exec/libraries.h>
#include <exec/nodes.h>
#include <exec/lists.h>
#include <exec/ports.h>
#include <exec/memory.h>
#include <devices/input.h>
#include <intuition/intuition.h>
#include <intuition/intuitionbase.h>
#include <intuition/gadgetclass.h>
#include <graphics/gfx.h>
#include <graphics/gfxmacros.h>
#include <libraries/gadtools.h>
#include <libraries/gtdrag.h>
#include <libraries/asl.h>
#include <dos/dos.h>

#include <clib/alib_protos.h>
#include <clib/alib_stdio_protos.h>
#include <clib/exec_protos.h>
#include <clib/gadtools_protos.h>
#include <clib/intuition_protos.h>
#include <clib/graphics_protos.h>
#include <clib/layers_protos.h>
#include <clib/utility_protos.h>
#include <clib/dos_protos.h>

#include <pragmas/exec_pragmas.h>
#include <pragmas/gadtools_pragmas.h>
#include <pragmas/intuition_pragmas.h>
#include <pragmas/graphics_pragmas.h>
#include <pragmas/layers_pragmas.h>
#include <pragmas/utility_pragmas.h>
#include <pragmas/dos_pragmas.h>

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define foreach(l,v) for(v = (APTR)((struct List *)l)->lh_Head;((struct Node *)v)->ln_Succ;v = (APTR)((struct Node *)v)->ln_Succ)
#define words(a,b) ((ULONG)((a) << 16L) | (WORD)(b))

#define PUBLIC __asm __saveds
#define PRIVATE __regargs
#define reg(x) register __ ## x

void kprintf(STRPTR,...);
#define bug kprintf
#ifdef DEBUG
#define D(x) x
#else
#define D(x) ;
#endif

/********************* DragWindow *********************/

struct DragWindow
{
  struct MinNode dw_Node;
  struct Window *dw_Window;
  struct Task *dw_Task;
  ULONG  dw_AcceptMask;
  BOOL   __asm (*dw_AcceptFunc)(reg (a0) struct Window *,reg (a1) struct Gadget *,reg (a2) struct ObjectDescription *);
};


/********************* DragGadget *********************/

struct DragGadget
{
  struct MinNode dg_Node;
  struct Gadget *dg_Gadget;
  struct Window *dg_Window;
  struct Task *dg_Task;       /* pointer to the owner task */
  struct List *dg_List;       /* listviews only */
  ULONG  dg_Type;
  ULONG  dg_AcceptMask;       /* accept mask for internal types */
  struct Image *dg_Image;     /* image to render */
  struct Hook *dg_RenderHook; /* render hook for the object */
  WORD   dg_ItemHeight;       /* listviews only */
  WORD   dg_Width,dg_Height;
  UWORD  dg_Flags;
  BOOL   __asm (*dg_AcceptFunc)(reg (a0) struct Window *,reg (a1) struct Gadget *,reg (a2) struct ObjectDescription *);
  void   __asm (*dg_ObjectFunc)(reg (a0) struct Window *,reg (a1) struct Gadget *,reg (a2) struct ObjectDescription *,reg (d0) LONG pos);
  struct ObjectDescription dg_Object;
  APTR   dg_CurrentObject;
  ULONG  dg_SourceEntry;
  ULONG  dg_Selected;
};

#define DGF_IMAGES 1        /* Images only, if possible */
#define DGF_NODRAG 2        /* can't be the source of a drag */
#define DGF_SAME 4          /* icon can be dragged over the same gadget */
#define DGF_NOPOS 8         /* no positioning, listview only */
#define DGF_NOSCROLL 16     /* listview cannot be scrolled */
#define DGF_DROPOVER 32     /* item drops over not between other items */
#define DGF_SUPPORTGTD 64   /* flag for boopsi gadgets */
#define DGF_LIKECURRENT 128 /* dg_CurrentObject would be accepted */
#define DGF_TREEVIEW 256    /* treeview specials activated */
#define DGF_ONTHEFLY 512    /* boopsi-gadget are not really registered */
#define DGF_USERENDERING 1024 /* boopsi-gadget highlights itself */
#define DGF_FINAL 2048        /* do not call GM_OBJECTDRAG again */
#define DGF_INTERNALONLY 4096 /* gadget will not accept external objects */
#define DGF_DROPBETWEEN 8192  /* DGF_DROPOVER is only a light version */


/********************* DragApp *********************/

struct DragApp
{
  struct MinNode da_Node;
  struct Task *da_Task;
  STRPTR da_Name;
  UWORD  da_Flags;
  BOOL   da_GTMsg;
};

#define DAF_INTERN 1       /* drag&drop only inside the application */


/********************* DragObj *********************/

struct DragObj
{
  struct DragGadget *do_DragGadget;
  struct Screen *do_Screen;
  int do_DeltaX,do_DeltaY;
  int do_X,do_Y,do_Width,do_Height;
  int do_SX,do_SY;
  int do_PX,do_PY,do_PWidth,do_PHeight;
  struct RastPort *do_ScrRPort;
  struct RastPort do_RPort;
  struct RastPort do_RefreshRPort;
  struct BitMap *do_BitMap;
  struct BitMap *do_SaveBack;
  struct BitMap *do_RefreshMap;
  UWORD *do_Mask;
  UWORD *do_FullShadow,*do_HalfShadow;
};

#define LVDRAGPIXEL 10
#define DRAGPIXEL 3


/********************* global variables *********************/

extern struct ExecBase *SysBase;
extern struct IntuitionBase *IntuitionBase;
extern struct Library  *DOSBase;
extern struct GfxBase  *GfxBase;
extern struct Library  *GadToolsBase;
extern struct Library  *LayersBase;
extern struct Library  *UtilityBase;
extern struct Library  *CyberGfxBase;

extern struct MinList applist;
extern struct MinList gadlist;
extern struct MinList winlist;
extern struct DragObj *gdo;
extern struct DragGadget *dg,*hdg,*adg;
extern struct DropMessage dm;
extern struct BitMap *hbm;
extern struct Gadget *boopsigad;
extern struct RastPort hrp,hsrp;
extern int    mx,my,hx,hy,hw,hh;
extern BOOL   isdragged,fakemsg,noreport;
extern struct MsgPort *dmport;
extern struct SignalSemaphore ListSemaphore;
extern struct Hook iffstreamHook,renderHook,treeHook;


/********************* private functions *********************/

// gtdrag.c
extern int PRIVATE GTD_Init(void);
extern void PRIVATE GTD_Exit(void);
extern int PRIVATE CountNodes(struct List *l);
extern struct Node * PRIVATE FindListNumber(struct MinList *l,long num);
extern void PRIVATE FakeInputEvent(void);

// GTD_Apps.c
extern void PRIVATE SetObjectOwner(struct DragApp *da,struct Task *t,struct ObjectDescription *od);
extern struct DragApp * PRIVATE GetDragApp(struct Task *);

// GTD_Highlight.c
extern BOOL PRIVATE UpdateHighlighting(ULONG class,WORD mousex,WORD mousey,struct DragGadget *sdg);
extern BOOL PRIVATE HighlightLVDragGadget(struct DragGadget *,long,short);
extern void PRIVATE HighlightDragGadget(struct DragGadget *dg,WORD x,WORD y);

// GTD_DragObjs.c
extern void PRIVATE FreeDragObj(struct DragObj *gdo);
extern struct DragObj * PRIVATE CreateDragObj(struct DragGadget *dg,int x,int y);
extern void PRIVATE UpdateDragObj(struct DragObj *gdo,int x, int y);

// GTD_Gadget.c
extern BOOL PRIVATE DragGadgetAcceptsObject(struct DragGadget *adg,WORD x,WORD y);
extern struct DragGadget * PRIVATE GetAcceptorDragGadget(int mx,int my);
extern void PRIVATE FreeDragGadget(struct DragGadget *dg);
extern struct DragGadget * PRIVATE WhichDragGadget(APTR layer,int mx,int my);
extern struct DragGadget * PRIVATE AddDragGadget(struct Gadget *gad,struct Window *win,ULONG type);
extern BOOL PRIVATE PointInDragGadget(struct DragGadget *dg,int x,int y,BOOL lheight);
extern struct DragGadget * PRIVATE FindDragGadget(struct Gadget *gad);

// GTD_Windows.c
extern void PRIVATE SetWindowAttrs(struct Window *win,struct TagItem *tags);

// GTD_Boopsi.c
extern ULONG PRIVATE DoCustomMethod(struct Gadget *gad,ULONG method,...);
extern ULONG PRIVATE DoRenderMethod(struct DragGadget *dg,WORD x,WORD y,ULONG mode);

// GTD_Hook.c
extern void PRIVATE DrawRect(struct RastPort *rp,long x, long y, long w, long h);
extern void PRIVATE GhostRect(struct RastPort *rp,UWORD pen,UWORD x0,UWORD y0,UWORD x1,UWORD y1);
extern long PRIVATE WriteHookText(struct RastPort *rp,struct Rectangle *bounds,STRPTR name,ULONG bpen);

// GTD_DropMsgs.c
extern void PRIVATE FreeDropMessage(struct IntuiMessage *msg);
extern void PRIVATE MakeDropMessage(struct DragApp *da,ULONG qual,WORD mousex,WORD mousey);

// GTD_Drag.c
extern void PRIVATE EndDrag(void);
extern void PRIVATE PrepareDrag(BOOL boopsi);
extern void PRIVATE MouseMove(WORD mousex,WORD mousey);
extern void PRIVATE IntuiTick(WORD mousex,WORD mousey);

/********************* public functions *********************/

// GTD_Apps.c
extern int PUBLIC GTD_AddAppA(reg (a0) STRPTR t,reg (a1) struct TagItem *tag);
extern void PUBLIC GTD_RemoveApp(void);

// GTD_Gadgets.c
extern BOOL PUBLIC GTD_GetAttr(reg (a0) APTR gad,reg (d0) ULONG tag,reg (a1) ULONG *storage);
extern void PUBLIC GTD_SetAttrsA(reg (a0) APTR gad,reg (a1) struct TagItem *tags);
extern void PUBLIC GTD_AddGadgetA(reg (d0) ULONG type,reg (a0) struct Gadget *gad,reg (a1) struct Window *win,reg (a2) struct TagItem *tag1);
extern void PUBLIC GTD_RemoveGadget(reg (a0) struct Gadget *);
extern void PUBLIC GTD_RemoveGadgets(reg (a0) struct Window *);

// GTD_Windows.c
extern void PUBLIC GTD_AddWindowA(reg (a0) struct Window *win,reg (a1) struct TagItem *tag);
extern void PUBLIC GTD_RemoveWindow(reg (a0) struct Window *win);

// GTD_Boopsi.c
extern ULONG PUBLIC GTD_HandleInput(reg (a0) struct Gadget *gad,reg (a1) struct gpInput *gpi);
extern BOOL PUBLIC GTD_PrepareDrag(reg (a0) struct Gadget *gad,reg (a1) struct gpInput *gpi);
extern BOOL PUBLIC GTD_BeginDrag(reg (a0) struct Gadget *gad,reg (a1) struct gpInput *gpi);
extern void PUBLIC GTD_StopDrag(reg (a0) struct Gadget *gad);

// GTD_DropMsgs.c
extern STRPTR PUBLIC GTD_GetString(reg (a0) struct ObjectDescription *od,reg (a1) STRPTR buf,reg (d0) LONG len);

// GTD_IMsgs.c
extern void PUBLIC GTD_ReplyIMsg(reg (a0) struct IntuiMessage *msg);
extern struct IntuiMessage * PUBLIC GTD_GetIMsg(reg (a0) struct MsgPort *mp);
extern struct IntuiMessage * PUBLIC GTD_FilterIMsg(reg (a0) struct IntuiMessage *msg);
extern struct IntuiMessage * PUBLIC GTD_PostFilterIMsg(reg (a0) struct IntuiMessage *msg);

// GTD_Hook.c
extern struct Hook * PUBLIC GTD_GetHook(reg (d0) ULONG type);

// GTD_(IFF|Image|Tree)Hook.c
extern ULONG PUBLIC IFFStreamHook(reg (a0) struct Hook *h,reg (a1) struct IFFStreamCmd *sc,reg (a2) struct IFFHandle *iff);
extern ULONG PUBLIC RenderHook(reg (a1) struct LVDrawMsg *msg,reg (a2) struct ImageNode *in);
extern ULONG PUBLIC TreeHook(reg (a0) struct Hook *h,reg (a1) struct LVDrawMsg *msg,reg (a2) struct TreeNode *tn);

// GTD_Tree.c
extern struct TreeNode * PUBLIC AddTreeNode(reg (a0) APTR pool,reg (a1) struct MinList *tree,reg (a2) STRPTR name,reg (a3) struct Image *im,reg (d0) UWORD flags);
extern void PUBLIC FreeTreeNodes(reg (a0) APTR pool,reg (a1) struct MinList *list);
extern void PUBLIC FreeTreeList(reg (a0) APTR pool,reg (a1) struct TreeList *tl);
extern void PUBLIC CloseTreeNode(reg (a0) struct MinList *main,reg (a1) struct TreeNode *tn);
extern LONG PUBLIC OpenTreeNode(reg (a0) struct MinList *main,reg (a1) struct TreeNode *tn);
extern LONG PUBLIC ToggleTreeNode(reg (a0) struct MinList *main,reg (a1) struct TreeNode *tn);
extern void PUBLIC InitTreeList(reg (a0) struct TreeList *tl);
extern struct TreeNode * PUBLIC GetTreeContainer(reg (a0) struct TreeNode *tn);
extern STRPTR PUBLIC GetTreePath(reg (a0) struct TreeNode *tn,reg (a1) STRPTR buffer,reg (d0) LONG len);
extern struct TreeNode * PUBLIC FindTreePath(reg (a0) struct MinList *tree,reg (a1) STRPTR path);
extern struct TreeNode * PUBLIC FindTreeSpecial(reg (a0) struct MinList *tree,reg (a1) APTR special);
extern struct TreeNode * PUBLIC FindListSpecial(reg (a0) struct MinList *list,reg (a1) APTR special);
extern BOOL PUBLIC ToggleTree(reg (a0) struct Gadget *gad,reg (a1) struct TreeNode *tn,reg (a2) struct IntuiMessage *msg);

#endif
