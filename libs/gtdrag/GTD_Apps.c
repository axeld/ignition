/*
 * Copyright �1999-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the MIT License.
 */

//!	Application related functions.


#include "gtdrag_includes.h"


void PRIVATE SetObjectOwner(struct DragApp *da,struct Task *t,struct ObjectDescription *od)
{
  if (da->da_Task != t)
    od->od_Owner = da->da_Name;
  else
    od->od_Owner = NULL;
}


struct DragApp * PRIVATE GetDragApp(struct Task *task)
{
  struct DragApp *da;

  if (!task)
    task = FindTask(NULL);

  foreach(&applist,da)
  {
    if (da->da_Task == task)
      return(da);
  }
  return(NULL);
}


void PUBLIC GTD_RemoveApp(void)
{
  struct DragApp *da;
  struct MinNode *n,*s;

  ObtainSemaphore(&ListSemaphore);
  if (da = GetDragApp(NULL))
  {
    for(n = winlist.mlh_Head;n->mln_Succ;n = n->mln_Succ)
    {
      if (((struct DragWindow *)n)->dw_Task == da->da_Task)
      {
        s = n->mln_Pred;
        Remove((struct Node *)n);
        FreeMem(n,sizeof(struct DragWindow));
        n = s;
      }
    }
    for(n = gadlist.mlh_Head;n->mln_Succ;n = n->mln_Succ)
    {
      if (((struct DragGadget *)n)->dg_Task == da->da_Task)
      {
        s = n->mln_Pred;
        Remove((struct Node *)n);
        FreeMem(n,sizeof(struct DragGadget));
        n = s;
      }
    }

    Remove((struct Node *)da);
    FreeMem(da, sizeof(struct DragApp));
  }
  ReleaseSemaphore(&ListSemaphore);
}


int PUBLIC GTD_AddAppA(reg (a0) STRPTR t,reg (a1) struct TagItem *tag1)
{
  struct DragApp *da;

  if (!FindTagItem(GTDA_NewStyle,tag1))
    return(TRUE);
  ObtainSemaphore(&ListSemaphore);

  if (t && !GetDragApp(NULL))
  {
    if (da = AllocMem(sizeof(struct DragApp),MEMF_PUBLIC | MEMF_CLEAR))
    {
      da->da_Name = t;
      da->da_Task = FindTask(NULL);
      da->da_Flags = GetTagData(GTDA_InternalOnly,0,tag1);

      AddTail((struct List *)&applist,(APTR)da);

      ReleaseSemaphore(&ListSemaphore);
      return(TRUE);
    }
  }
  ReleaseSemaphore(&ListSemaphore);
  return(FALSE);
}


