#ifndef CLIB_GTDRAG_PROTOS_H
#define CLIB_GTDRAG_PROTOS_H

/*
    *** Automatically generated from '/home/mazze/projects/AROS/local/ignition/libs/gtdrag/gtdrag.conf'. Edits will be lost. ***
    Copyright © 1995-2009, The AROS Development Team. All rights reserved.
*/

#include <aros/libcall.h>
#include <exec/exec.h>
#include <utility/utility.h>
#include <intuition/intuition.h>
#include <intuition/gadgetclass.h>
#include <libraries/gtdrag.h>
AROS_LP1(struct IntuiMessage *, GTD_GetIMsg,
         AROS_LPA(struct MsgPort *, mp, A0),
         LIBBASETYPEPTR, GTDragBase, 5, Gtdrag
);
AROS_LP1(void, GTD_ReplyIMsg,
         AROS_LPA(struct IntuiMessage *, msg, A0),
         LIBBASETYPEPTR, GTDragBase, 6, Gtdrag
);
AROS_LP1(struct IntuiMessage *, GTD_FilterIMsg,
         AROS_LPA(struct IntuiMessage *, msg, A0),
         LIBBASETYPEPTR, GTDragBase, 7, Gtdrag
);
AROS_LP1(struct IntuiMessage *, GTD_PostFilterIMsg,
         AROS_LPA(struct IntuiMessage *, msg, A0),
         LIBBASETYPEPTR, GTDragBase, 8, Gtdrag
);
AROS_LP2(int, GTD_AddAppA,
         AROS_LPA(STRPTR, t, A0),
         AROS_LPA(struct TagItem *, tag, A1),
         LIBBASETYPEPTR, GTDragBase, 11, Gtdrag
);
AROS_LP0(void, GTD_RemoveApp,
         LIBBASETYPEPTR, GTDragBase, 12, Gtdrag
);
AROS_LP2(void, GTD_AddWindowA,
         AROS_LPA(struct Window *, win, A0),
         AROS_LPA(struct TagItem *, tag, A1),
         LIBBASETYPEPTR, GTDragBase, 13, Gtdrag
);
AROS_LP1(void, GTD_RemoveWindow,
         AROS_LPA(struct Window *, win, A0),
         LIBBASETYPEPTR, GTDragBase, 14, Gtdrag
);
AROS_LP4(void, GTD_AddGadgetA,
         AROS_LPA(ULONG, type, D0),
         AROS_LPA(struct Gadget *, gad, A0),
         AROS_LPA(struct Window *, win, A1),
         AROS_LPA(struct TagItem *, tag, A2),
         LIBBASETYPEPTR, GTDragBase, 15, Gtdrag
);
AROS_LP1(void, GTD_RemoveGadget,
         AROS_LPA(struct Gadget *, gad, A0),
         LIBBASETYPEPTR, GTDragBase, 16, Gtdrag
);
AROS_LP1(void, GTD_RemoveGadgets,
         AROS_LPA(struct Window *, win, A0),
         LIBBASETYPEPTR, GTDragBase, 17, Gtdrag
);
AROS_LP2(void, GTD_SetAttrsA,
         AROS_LPA(APTR, gad, A0),
         AROS_LPA(struct TagItem *, tags, A1),
         LIBBASETYPEPTR, GTDragBase, 18, Gtdrag
);
AROS_LP3(BOOL, GTD_GetAttr,
         AROS_LPA(APTR, gad, A0),
         AROS_LPA(ULONG, tag, D0),
         AROS_LPA(ULONG *, storage, A1),
         LIBBASETYPEPTR, GTDragBase, 19, Gtdrag
);
AROS_LP1(struct Hook *, GTD_GetHook,
         AROS_LPA(ULONG, type, D0),
         LIBBASETYPEPTR, GTDragBase, 20, Gtdrag
);
AROS_LP3(STRPTR, GTD_GetString,
         AROS_LPA(struct ObjectDescription *, od, A0),
         AROS_LPA(STRPTR, buf, D1),
         AROS_LPA(LONG, len, D0),
         LIBBASETYPEPTR, GTDragBase, 21, Gtdrag
);
AROS_LP2(BOOL, GTD_PrepareDrag,
         AROS_LPA(struct Gadget *, gad, A0),
         AROS_LPA(struct gpInput *, gpi, A1),
         LIBBASETYPEPTR, GTDragBase, 22, Gtdrag
);
AROS_LP2(BOOL, GTD_BeginDrag,
         AROS_LPA(struct Gadget *, gad, A0),
         AROS_LPA(struct gpInput *, gpi, A1),
         LIBBASETYPEPTR, GTDragBase, 23, Gtdrag
);
AROS_LP2(ULONG, GTD_HandleInput,
         AROS_LPA(struct Gadget *, gad, A0),
         AROS_LPA(struct gpInput *, gpi, A1),
         LIBBASETYPEPTR, GTDragBase, 24, Gtdrag
);
AROS_LP1(void, GTD_StopDrag,
         AROS_LPA(struct Gadget *, gad, A0),
         LIBBASETYPEPTR, GTDragBase, 25, Gtdrag
);
AROS_LP2(void, FreeTreeList,
         AROS_LPA(APTR, pool, A0),
         AROS_LPA(struct TreeList *, tl, A1),
         LIBBASETYPEPTR, GTDragBase, 26, Gtdrag
);
AROS_LP1(void, InitTreeList,
         AROS_LPA(struct TreeList *, tl, A0),
         LIBBASETYPEPTR, GTDragBase, 27, Gtdrag
);
AROS_LP2(void, FreeTreeNodes,
         AROS_LPA(APTR, pool, A0),
         AROS_LPA(struct MinList *, list, A1),
         LIBBASETYPEPTR, GTDragBase, 28, Gtdrag
);
AROS_LP5(struct TreeNode *, AddTreeNode,
         AROS_LPA(APTR, pool, A0),
         AROS_LPA(struct MinList *, tree, A1),
         AROS_LPA(STRPTR, name, A2),
         AROS_LPA(struct Image *, im, A3),
         AROS_LPA(UWORD, flags, D0),
         LIBBASETYPEPTR, GTDragBase, 29, Gtdrag
);
AROS_LP2(void, CloseTreeNode,
         AROS_LPA(struct MinList *, main, A0),
         AROS_LPA(struct TreeNode *, tn, A1),
         LIBBASETYPEPTR, GTDragBase, 30, Gtdrag
);
AROS_LP2(LONG, OpenTreeNode,
         AROS_LPA(struct MinList *, main, A0),
         AROS_LPA(struct TreeNode *, tn, A1),
         LIBBASETYPEPTR, GTDragBase, 31, Gtdrag
);
AROS_LP2(LONG, ToggleTreeNode,
         AROS_LPA(struct MinList *, main, A0),
         AROS_LPA(struct TreeNode *, tn, A1),
         LIBBASETYPEPTR, GTDragBase, 32, Gtdrag
);
AROS_LP1(struct TreeNode *, GetTreeContainer,
         AROS_LPA(struct TreeNode *, tn, A0),
         LIBBASETYPEPTR, GTDragBase, 33, Gtdrag
);
AROS_LP3(STRPTR, GetTreePath,
         AROS_LPA(struct TreeNode *, tn, A0),
         AROS_LPA(STRPTR, buffer, A1),
         AROS_LPA(LONG, len, D0),
         LIBBASETYPEPTR, GTDragBase, 34, Gtdrag
);
AROS_LP2(struct TreeNode *, FindTreePath,
         AROS_LPA(struct MinList *, tree, A0),
         AROS_LPA(STRPTR, path, A1),
         LIBBASETYPEPTR, GTDragBase, 35, Gtdrag
);
AROS_LP2(struct TreeNode *, FindTreeSpecial,
         AROS_LPA(struct MinList *, tree, A0),
         AROS_LPA(APTR, special, A1),
         LIBBASETYPEPTR, GTDragBase, 36, Gtdrag
);
AROS_LP2(struct TreeNode *, FindListSpecial,
         AROS_LPA(struct MinList *, list, A0),
         AROS_LPA(APTR, special, A1),
         LIBBASETYPEPTR, GTDragBase, 37, Gtdrag
);
AROS_LP3(BOOL, ToggleTree,
         AROS_LPA(struct Gadget *, gad, A0),
         AROS_LPA(struct TreeNode *, tn, A1),
         AROS_LPA(struct IntuiMessage *, msg, A2),
         LIBBASETYPEPTR, GTDragBase, 38, Gtdrag
);

#endif /* CLIB_GTDRAG_PROTOS_H */
