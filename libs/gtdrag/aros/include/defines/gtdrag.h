#ifndef DEFINES_GTDRAG_H
#define DEFINES_GTDRAG_H

/*
    *** Automatically generated from '/home/mazze/projects/AROS/local/ignition/libs/gtdrag/gtdrag.conf'. Edits will be lost. ***
    Copyright © 1995-2009, The AROS Development Team. All rights reserved.
*/

/*
    Desc: Defines for gtdrag
*/

#include <aros/libcall.h>
#include <exec/types.h>
#include <aros/preprocessor/variadic/cast2iptr.hpp>


#define __GTD_GetIMsg_WB(__GTDragBase, __arg1) \
        AROS_LC1(struct IntuiMessage *, GTD_GetIMsg, \
                  AROS_LCA(struct MsgPort *,(__arg1),A0), \
        struct Library *, (__GTDragBase), 5, Gtdrag)

#define GTD_GetIMsg(arg1) \
    __GTD_GetIMsg_WB(GTDragBase, (arg1))

#define __GTD_ReplyIMsg_WB(__GTDragBase, __arg1) \
        AROS_LC1NR(void, GTD_ReplyIMsg, \
                  AROS_LCA(struct IntuiMessage *,(__arg1),A0), \
        struct Library *, (__GTDragBase), 6, Gtdrag)

#define GTD_ReplyIMsg(arg1) \
    __GTD_ReplyIMsg_WB(GTDragBase, (arg1))

#define __GTD_FilterIMsg_WB(__GTDragBase, __arg1) \
        AROS_LC1(struct IntuiMessage *, GTD_FilterIMsg, \
                  AROS_LCA(struct IntuiMessage *,(__arg1),A0), \
        struct Library *, (__GTDragBase), 7, Gtdrag)

#define GTD_FilterIMsg(arg1) \
    __GTD_FilterIMsg_WB(GTDragBase, (arg1))

#define __GTD_PostFilterIMsg_WB(__GTDragBase, __arg1) \
        AROS_LC1(struct IntuiMessage *, GTD_PostFilterIMsg, \
                  AROS_LCA(struct IntuiMessage *,(__arg1),A0), \
        struct Library *, (__GTDragBase), 8, Gtdrag)

#define GTD_PostFilterIMsg(arg1) \
    __GTD_PostFilterIMsg_WB(GTDragBase, (arg1))

#define __GTD_AddAppA_WB(__GTDragBase, __arg1, __arg2) \
        AROS_LC2(int, GTD_AddAppA, \
                  AROS_LCA(STRPTR,(__arg1),A0), \
                  AROS_LCA(struct TagItem *,(__arg2),A1), \
        struct Library *, (__GTDragBase), 11, Gtdrag)

#define GTD_AddAppA(arg1, arg2) \
    __GTD_AddAppA_WB(GTDragBase, (arg1), (arg2))

#if !defined(NO_INLINE_STDARG) && !defined(GTDRAG_NO_INLINE_STDARG)
#define GTD_AddApp(arg1, ...) \
({ \
    IPTR __args[] = { AROS_PP_VARIADIC_CAST2IPTR(__VA_ARGS__) }; \
    GTD_AddAppA((arg1), (struct TagItem *)__args); \
})
#endif /* !NO_INLINE_STDARG */

#define __GTD_RemoveApp_WB(__GTDragBase) \
        AROS_LC0NR(void, GTD_RemoveApp, \
        struct Library *, (__GTDragBase), 12, Gtdrag)

#define GTD_RemoveApp() \
    __GTD_RemoveApp_WB(GTDragBase)

#define __GTD_AddWindowA_WB(__GTDragBase, __arg1, __arg2) \
        AROS_LC2NR(void, GTD_AddWindowA, \
                  AROS_LCA(struct Window *,(__arg1),A0), \
                  AROS_LCA(struct TagItem *,(__arg2),A1), \
        struct Library *, (__GTDragBase), 13, Gtdrag)

#define GTD_AddWindowA(arg1, arg2) \
    __GTD_AddWindowA_WB(GTDragBase, (arg1), (arg2))

#if !defined(NO_INLINE_STDARG) && !defined(GTDRAG_NO_INLINE_STDARG)
#define GTD_AddWindow(arg1, ...) \
({ \
    IPTR __args[] = { AROS_PP_VARIADIC_CAST2IPTR(__VA_ARGS__) }; \
    GTD_AddWindowA((arg1), (struct TagItem *)__args); \
})
#endif /* !NO_INLINE_STDARG */

#define __GTD_RemoveWindow_WB(__GTDragBase, __arg1) \
        AROS_LC1NR(void, GTD_RemoveWindow, \
                  AROS_LCA(struct Window *,(__arg1),A0), \
        struct Library *, (__GTDragBase), 14, Gtdrag)

#define GTD_RemoveWindow(arg1) \
    __GTD_RemoveWindow_WB(GTDragBase, (arg1))

#define __GTD_AddGadgetA_WB(__GTDragBase, __arg1, __arg2, __arg3, __arg4) \
        AROS_LC4NR(void, GTD_AddGadgetA, \
                  AROS_LCA(ULONG,(__arg1),D0), \
                  AROS_LCA(struct Gadget *,(__arg2),A0), \
                  AROS_LCA(struct Window *,(__arg3),A1), \
                  AROS_LCA(struct TagItem *,(__arg4),A2), \
        struct Library *, (__GTDragBase), 15, Gtdrag)

#define GTD_AddGadgetA(arg1, arg2, arg3, arg4) \
    __GTD_AddGadgetA_WB(GTDragBase, (arg1), (arg2), (arg3), (arg4))

#if !defined(NO_INLINE_STDARG) && !defined(GTDRAG_NO_INLINE_STDARG)
#define GTD_AddGadget(arg1, arg2, arg3, ...) \
({ \
    IPTR __args[] = { AROS_PP_VARIADIC_CAST2IPTR(__VA_ARGS__) }; \
    GTD_AddGadgetA((arg1), (arg2), (arg3), (struct TagItem *)__args); \
})
#endif /* !NO_INLINE_STDARG */

#define __GTD_RemoveGadget_WB(__GTDragBase, __arg1) \
        AROS_LC1NR(void, GTD_RemoveGadget, \
                  AROS_LCA(struct Gadget *,(__arg1),A0), \
        struct Library *, (__GTDragBase), 16, Gtdrag)

#define GTD_RemoveGadget(arg1) \
    __GTD_RemoveGadget_WB(GTDragBase, (arg1))

#define __GTD_RemoveGadgets_WB(__GTDragBase, __arg1) \
        AROS_LC1NR(void, GTD_RemoveGadgets, \
                  AROS_LCA(struct Window *,(__arg1),A0), \
        struct Library *, (__GTDragBase), 17, Gtdrag)

#define GTD_RemoveGadgets(arg1) \
    __GTD_RemoveGadgets_WB(GTDragBase, (arg1))

#define __GTD_SetAttrsA_WB(__GTDragBase, __arg1, __arg2) \
        AROS_LC2NR(void, GTD_SetAttrsA, \
                  AROS_LCA(APTR,(__arg1),A0), \
                  AROS_LCA(struct TagItem *,(__arg2),A1), \
        struct Library *, (__GTDragBase), 18, Gtdrag)

#define GTD_SetAttrsA(arg1, arg2) \
    __GTD_SetAttrsA_WB(GTDragBase, (arg1), (arg2))

#if !defined(NO_INLINE_STDARG) && !defined(GTDRAG_NO_INLINE_STDARG)
#define GTD_SetAttrs(arg1, ...) \
({ \
    IPTR __args[] = { AROS_PP_VARIADIC_CAST2IPTR(__VA_ARGS__) }; \
    GTD_SetAttrsA((arg1), (struct TagItem *)__args); \
})
#endif /* !NO_INLINE_STDARG */

#define __GTD_GetAttr_WB(__GTDragBase, __arg1, __arg2, __arg3) \
        AROS_LC3(BOOL, GTD_GetAttr, \
                  AROS_LCA(APTR,(__arg1),A0), \
                  AROS_LCA(ULONG,(__arg2),D0), \
                  AROS_LCA(ULONG *,(__arg3),A1), \
        struct Library *, (__GTDragBase), 19, Gtdrag)

#define GTD_GetAttr(arg1, arg2, arg3) \
    __GTD_GetAttr_WB(GTDragBase, (arg1), (arg2), (arg3))

#define __GTD_GetHook_WB(__GTDragBase, __arg1) \
        AROS_LC1(struct Hook *, GTD_GetHook, \
                  AROS_LCA(ULONG,(__arg1),D0), \
        struct Library *, (__GTDragBase), 20, Gtdrag)

#define GTD_GetHook(arg1) \
    __GTD_GetHook_WB(GTDragBase, (arg1))

#define __GTD_GetString_WB(__GTDragBase, __arg1, __arg2, __arg3) \
        AROS_LC3(STRPTR, GTD_GetString, \
                  AROS_LCA(struct ObjectDescription *,(__arg1),A0), \
                  AROS_LCA(STRPTR,(__arg2),D1), \
                  AROS_LCA(LONG,(__arg3),D0), \
        struct Library *, (__GTDragBase), 21, Gtdrag)

#define GTD_GetString(arg1, arg2, arg3) \
    __GTD_GetString_WB(GTDragBase, (arg1), (arg2), (arg3))

#define __GTD_PrepareDrag_WB(__GTDragBase, __arg1, __arg2) \
        AROS_LC2(BOOL, GTD_PrepareDrag, \
                  AROS_LCA(struct Gadget *,(__arg1),A0), \
                  AROS_LCA(struct gpInput *,(__arg2),A1), \
        struct Library *, (__GTDragBase), 22, Gtdrag)

#define GTD_PrepareDrag(arg1, arg2) \
    __GTD_PrepareDrag_WB(GTDragBase, (arg1), (arg2))

#define __GTD_BeginDrag_WB(__GTDragBase, __arg1, __arg2) \
        AROS_LC2(BOOL, GTD_BeginDrag, \
                  AROS_LCA(struct Gadget *,(__arg1),A0), \
                  AROS_LCA(struct gpInput *,(__arg2),A1), \
        struct Library *, (__GTDragBase), 23, Gtdrag)

#define GTD_BeginDrag(arg1, arg2) \
    __GTD_BeginDrag_WB(GTDragBase, (arg1), (arg2))

#define __GTD_HandleInput_WB(__GTDragBase, __arg1, __arg2) \
        AROS_LC2(ULONG, GTD_HandleInput, \
                  AROS_LCA(struct Gadget *,(__arg1),A0), \
                  AROS_LCA(struct gpInput *,(__arg2),A1), \
        struct Library *, (__GTDragBase), 24, Gtdrag)

#define GTD_HandleInput(arg1, arg2) \
    __GTD_HandleInput_WB(GTDragBase, (arg1), (arg2))

#define __GTD_StopDrag_WB(__GTDragBase, __arg1) \
        AROS_LC1NR(void, GTD_StopDrag, \
                  AROS_LCA(struct Gadget *,(__arg1),A0), \
        struct Library *, (__GTDragBase), 25, Gtdrag)

#define GTD_StopDrag(arg1) \
    __GTD_StopDrag_WB(GTDragBase, (arg1))

#define __FreeTreeList_WB(__GTDragBase, __arg1, __arg2) \
        AROS_LC2NR(void, FreeTreeList, \
                  AROS_LCA(APTR,(__arg1),A0), \
                  AROS_LCA(struct TreeList *,(__arg2),A1), \
        struct Library *, (__GTDragBase), 26, Gtdrag)

#define FreeTreeList(arg1, arg2) \
    __FreeTreeList_WB(GTDragBase, (arg1), (arg2))

#define __InitTreeList_WB(__GTDragBase, __arg1) \
        AROS_LC1NR(void, InitTreeList, \
                  AROS_LCA(struct TreeList *,(__arg1),A0), \
        struct Library *, (__GTDragBase), 27, Gtdrag)

#define InitTreeList(arg1) \
    __InitTreeList_WB(GTDragBase, (arg1))

#define __FreeTreeNodes_WB(__GTDragBase, __arg1, __arg2) \
        AROS_LC2NR(void, FreeTreeNodes, \
                  AROS_LCA(APTR,(__arg1),A0), \
                  AROS_LCA(struct MinList *,(__arg2),A1), \
        struct Library *, (__GTDragBase), 28, Gtdrag)

#define FreeTreeNodes(arg1, arg2) \
    __FreeTreeNodes_WB(GTDragBase, (arg1), (arg2))

#define __AddTreeNode_WB(__GTDragBase, __arg1, __arg2, __arg3, __arg4, __arg5) \
        AROS_LC5(struct TreeNode *, AddTreeNode, \
                  AROS_LCA(APTR,(__arg1),A0), \
                  AROS_LCA(struct MinList *,(__arg2),A1), \
                  AROS_LCA(STRPTR,(__arg3),A2), \
                  AROS_LCA(struct Image *,(__arg4),A3), \
                  AROS_LCA(UWORD,(__arg5),D0), \
        struct Library *, (__GTDragBase), 29, Gtdrag)

#define AddTreeNode(arg1, arg2, arg3, arg4, arg5) \
    __AddTreeNode_WB(GTDragBase, (arg1), (arg2), (arg3), (arg4), (arg5))

#define __CloseTreeNode_WB(__GTDragBase, __arg1, __arg2) \
        AROS_LC2NR(void, CloseTreeNode, \
                  AROS_LCA(struct MinList *,(__arg1),A0), \
                  AROS_LCA(struct TreeNode *,(__arg2),A1), \
        struct Library *, (__GTDragBase), 30, Gtdrag)

#define CloseTreeNode(arg1, arg2) \
    __CloseTreeNode_WB(GTDragBase, (arg1), (arg2))

#define __OpenTreeNode_WB(__GTDragBase, __arg1, __arg2) \
        AROS_LC2(LONG, OpenTreeNode, \
                  AROS_LCA(struct MinList *,(__arg1),A0), \
                  AROS_LCA(struct TreeNode *,(__arg2),A1), \
        struct Library *, (__GTDragBase), 31, Gtdrag)

#define OpenTreeNode(arg1, arg2) \
    __OpenTreeNode_WB(GTDragBase, (arg1), (arg2))

#define __ToggleTreeNode_WB(__GTDragBase, __arg1, __arg2) \
        AROS_LC2(LONG, ToggleTreeNode, \
                  AROS_LCA(struct MinList *,(__arg1),A0), \
                  AROS_LCA(struct TreeNode *,(__arg2),A1), \
        struct Library *, (__GTDragBase), 32, Gtdrag)

#define ToggleTreeNode(arg1, arg2) \
    __ToggleTreeNode_WB(GTDragBase, (arg1), (arg2))

#define __GetTreeContainer_WB(__GTDragBase, __arg1) \
        AROS_LC1(struct TreeNode *, GetTreeContainer, \
                  AROS_LCA(struct TreeNode *,(__arg1),A0), \
        struct Library *, (__GTDragBase), 33, Gtdrag)

#define GetTreeContainer(arg1) \
    __GetTreeContainer_WB(GTDragBase, (arg1))

#define __GetTreePath_WB(__GTDragBase, __arg1, __arg2, __arg3) \
        AROS_LC3(STRPTR, GetTreePath, \
                  AROS_LCA(struct TreeNode *,(__arg1),A0), \
                  AROS_LCA(STRPTR,(__arg2),A1), \
                  AROS_LCA(LONG,(__arg3),D0), \
        struct Library *, (__GTDragBase), 34, Gtdrag)

#define GetTreePath(arg1, arg2, arg3) \
    __GetTreePath_WB(GTDragBase, (arg1), (arg2), (arg3))

#define __FindTreePath_WB(__GTDragBase, __arg1, __arg2) \
        AROS_LC2(struct TreeNode *, FindTreePath, \
                  AROS_LCA(struct MinList *,(__arg1),A0), \
                  AROS_LCA(STRPTR,(__arg2),A1), \
        struct Library *, (__GTDragBase), 35, Gtdrag)

#define FindTreePath(arg1, arg2) \
    __FindTreePath_WB(GTDragBase, (arg1), (arg2))

#define __FindTreeSpecial_WB(__GTDragBase, __arg1, __arg2) \
        AROS_LC2(struct TreeNode *, FindTreeSpecial, \
                  AROS_LCA(struct MinList *,(__arg1),A0), \
                  AROS_LCA(APTR,(__arg2),A1), \
        struct Library *, (__GTDragBase), 36, Gtdrag)

#define FindTreeSpecial(arg1, arg2) \
    __FindTreeSpecial_WB(GTDragBase, (arg1), (arg2))

#define __FindListSpecial_WB(__GTDragBase, __arg1, __arg2) \
        AROS_LC2(struct TreeNode *, FindListSpecial, \
                  AROS_LCA(struct MinList *,(__arg1),A0), \
                  AROS_LCA(APTR,(__arg2),A1), \
        struct Library *, (__GTDragBase), 37, Gtdrag)

#define FindListSpecial(arg1, arg2) \
    __FindListSpecial_WB(GTDragBase, (arg1), (arg2))

#define __ToggleTree_WB(__GTDragBase, __arg1, __arg2, __arg3) \
        AROS_LC3(BOOL, ToggleTree, \
                  AROS_LCA(struct Gadget *,(__arg1),A0), \
                  AROS_LCA(struct TreeNode *,(__arg2),A1), \
                  AROS_LCA(struct IntuiMessage *,(__arg3),A2), \
        struct Library *, (__GTDragBase), 38, Gtdrag)

#define ToggleTree(arg1, arg2, arg3) \
    __ToggleTree_WB(GTDragBase, (arg1), (arg2), (arg3))

#endif /* DEFINES_GTDRAG_H*/
