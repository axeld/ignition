/* :ts=4
 *  $VER: OpenTreeNode.c $Revision$ (20-Sep-2013)
 *
 *  This file is part of gtdrag.
 *
 * Copyright ©1999-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the MIT License.
 *
 * $Id$
 *
 * $Log$
 *
 *
 */


#include <exec/exec.h>
#include <proto/exec.h>
#include <dos/dos.h>
#include <exec/types.h>
#include <libraries/gtdrag.h>
#include <proto/gtdrag.h>
#include <stdarg.h>

/****** gtdrag/main/OpenTreeNode ******************************************
*
*   NAME
*      OpenTreeNode -- Description
*
*   SYNOPSIS
*      LONG OpenTreeNode(struct MinList * main, struct TreeNode * treenode);
*
*   FUNCTION
*
*   INPUTS
*       main - 
*       treenode - 
*
*   RESULT
*       The result ...
*
*   EXAMPLE
*
*   NOTES
*
*   BUGS
*
*   SEE ALSO
*
*****************************************************************************
*
*/

LONG _Gtdrag_OpenTreeNode(struct GtdragIFace *Self, struct MinList * main, struct TreeNode * treenode)
{
    /* Write me. Really, I dare you! */
    ((struct ExecIFace *)((*(struct ExecBase **)4)->MainInterface))->DebugPrintF("Function gtdrag::OpenTreeNode not implemented\n");  
    return (LONG)0;

}

