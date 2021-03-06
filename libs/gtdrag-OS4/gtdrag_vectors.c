
/* This file was generated by idltool 53.1. Do not edit */

#ifndef EXEC_TYPES_H
#include <exec/types.h>

#endif
#ifndef EXEC_EXEC_H
#include <exec/exec.h>
#endif
#ifndef EXEC_INTERFACES_H
#include <exec/interfaces.h>
#endif

#ifndef LIBRARIES_GTDRAG_H
#include <libraries/gtdrag.h>
#endif

extern ULONG                VARARGS68K _Gtdrag_Obtain(struct GtdragIFace *);
extern ULONG                VARARGS68K _Gtdrag_Release(struct GtdragIFace *);
extern struct IntuiMessage * VARARGS68K _Gtdrag_GTD_GetIMsg(struct GtdragIFace *, struct MsgPort * iport);
extern void                 VARARGS68K _Gtdrag_GTD_ReplyIMsg(struct GtdragIFace *, struct IntuiMessage * msg);
extern struct IntuiMessage * VARARGS68K _Gtdrag_GTD_FilterIMsg(struct GtdragIFace *, struct IntuiMessage * msg);
extern struct IntuiMessage * VARARGS68K _Gtdrag_GTD_PostFilterIMsg(struct GtdragIFace *, struct IntuiMessage * msg);
extern int                  VARARGS68K _Gtdrag_GTD_AddAppA(struct GtdragIFace *, STRPTR name, struct TagItem * tagList);
extern int                  VARARGS68K _Gtdrag_GTD_AddApp(struct GtdragIFace *, STRPTR name, ...);
extern void                 VARARGS68K _Gtdrag_GTD_RemoveApp(struct GtdragIFace *);
extern void                 VARARGS68K _Gtdrag_GTD_AddWindowA(struct GtdragIFace *, struct Window * win, struct TagItem * tagList);
extern void                 VARARGS68K _Gtdrag_GTD_AddWindow(struct GtdragIFace *, struct Window * win, ...);
extern void                 VARARGS68K _Gtdrag_GTD_RemoveWindow(struct GtdragIFace *, struct Window * win);
extern void                 VARARGS68K _Gtdrag_GTD_AddGadgetA(struct GtdragIFace *, ULONG type, struct Gadget * gad, struct Window * win, struct TagItem * tagList);
extern void                 VARARGS68K _Gtdrag_GTD_AddGadget(struct GtdragIFace *, ULONG type, struct Gadget * gad, struct Window * win, ...);
extern void                 VARARGS68K _Gtdrag_GTD_RemoveGadget(struct GtdragIFace *, struct Gadget * gad);
extern void                 VARARGS68K _Gtdrag_GTD_RemoveGadgets(struct GtdragIFace *, struct Window * gad);
extern void                 VARARGS68K _Gtdrag_GTD_SetAttrsA(struct GtdragIFace *, APTR gad, struct TagItem * tags);
extern void                 VARARGS68K _Gtdrag_GTD_SetAttrs(struct GtdragIFace *, APTR gad, ...);
extern BOOL                 VARARGS68K _Gtdrag_GTD_GetAttr(struct GtdragIFace *, APTR gad, ULONG d0arg, ULONG * storage);
extern struct Hook *        VARARGS68K _Gtdrag_GTD_GetHook(struct GtdragIFace *, ULONG num);
extern STRPTR               VARARGS68K _Gtdrag_GTD_GetString(struct GtdragIFace *, struct ObjectDescription * od, STRPTR buf, LONG len);
extern BOOL                 VARARGS68K _Gtdrag_GTD_PrepareDrag(struct GtdragIFace *, struct Gadget * gad, struct gpInput * gpi);
extern BOOL                 VARARGS68K _Gtdrag_GTD_BeginDrag(struct GtdragIFace *, struct Gadget * gad, struct gpInput * gpi);
extern ULONG                VARARGS68K _Gtdrag_GTD_HandleInput(struct GtdragIFace *, struct Gadget * gad, struct gpInput * gpi);
extern void                 VARARGS68K _Gtdrag_GTD_StopDrag(struct GtdragIFace *, struct Gadget * gad);
extern void                 VARARGS68K _Gtdrag_FreeTreeList(struct GtdragIFace *, APTR pool, struct TreeList * treelist);
extern void                 VARARGS68K _Gtdrag_InitTreeList(struct GtdragIFace *, struct TreeList * treelist);
extern void                 VARARGS68K _Gtdrag_FreeTreeNodes(struct GtdragIFace *, APTR pool, struct MinList * list);
extern struct TreeNode *    VARARGS68K _Gtdrag_AddTreeNode(struct GtdragIFace *, APTR pool, struct MinList * tree, STRPTR name, struct Image * image, UWORD flags);
extern void                 VARARGS68K _Gtdrag_CloseTreeNode(struct GtdragIFace *, struct MinList * main, struct TreeNode * treenode);
extern LONG                 VARARGS68K _Gtdrag_OpenTreeNode(struct GtdragIFace *, struct MinList * main, struct TreeNode * treenode);
extern LONG                 VARARGS68K _Gtdrag_ToggleTreeNode(struct GtdragIFace *, struct MinList * main, struct TreeNode * treenode);
extern struct TreeNode *    VARARGS68K _Gtdrag_GetTreeContainer(struct GtdragIFace *, struct TreeNode * treenode);
extern STRPTR               VARARGS68K _Gtdrag_GetTreePath(struct GtdragIFace *, struct TreeNode * treenode, STRPTR buffer, LONG len);
extern struct TreeNode *    VARARGS68K _Gtdrag_FindTreePath(struct GtdragIFace *, struct MinList * tree, STRPTR path);
extern struct TreeNode *    VARARGS68K _Gtdrag_FindTreeSpecial(struct GtdragIFace *, struct MinList * tree, APTR special);
extern struct TreeNode *    VARARGS68K _Gtdrag_FindListSpecial(struct GtdragIFace *, struct MinList * list, APTR special);
extern BOOL                 VARARGS68K _Gtdrag_ToggleTree(struct GtdragIFace *, struct Gadget * gad, struct TreeNode * treenode, struct IntuiMessage * msg);


STATIC CONST APTR main_vectors[] =
{
    _Gtdrag_Obtain,
    _Gtdrag_Release,
    NULL,
    NULL,
    _Gtdrag_GTD_GetIMsg,
    _Gtdrag_GTD_ReplyIMsg,
    _Gtdrag_GTD_FilterIMsg,
    _Gtdrag_GTD_PostFilterIMsg,
    NULL,
    NULL,
    _Gtdrag_GTD_AddAppA,
    _Gtdrag_GTD_AddApp,
    _Gtdrag_GTD_RemoveApp,
    _Gtdrag_GTD_AddWindowA,
    _Gtdrag_GTD_AddWindow,
    _Gtdrag_GTD_RemoveWindow,
    _Gtdrag_GTD_AddGadgetA,
    _Gtdrag_GTD_AddGadget,
    _Gtdrag_GTD_RemoveGadget,
    _Gtdrag_GTD_RemoveGadgets,
    _Gtdrag_GTD_SetAttrsA,
    _Gtdrag_GTD_SetAttrs,
    _Gtdrag_GTD_GetAttr,
    _Gtdrag_GTD_GetHook,
    _Gtdrag_GTD_GetString,
    _Gtdrag_GTD_PrepareDrag,
    _Gtdrag_GTD_BeginDrag,
    _Gtdrag_GTD_HandleInput,
    _Gtdrag_GTD_StopDrag,
    _Gtdrag_FreeTreeList,
    _Gtdrag_InitTreeList,
    _Gtdrag_FreeTreeNodes,
    _Gtdrag_AddTreeNode,
    _Gtdrag_CloseTreeNode,
    _Gtdrag_OpenTreeNode,
    _Gtdrag_ToggleTreeNode,
    _Gtdrag_GetTreeContainer,
    _Gtdrag_GetTreePath,
    _Gtdrag_FindTreePath,
    _Gtdrag_FindTreeSpecial,
    _Gtdrag_FindListSpecial,
    _Gtdrag_ToggleTree,
    (APTR)-1
};

