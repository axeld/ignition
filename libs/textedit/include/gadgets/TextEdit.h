#ifndef GADGETS_TEXTEDIT_H
#define GADGETS_TEXTEDIT_H 1
/*
**  $VER: TextEdit.h 0.2 (23.9.2000)
**  Includes Release 0.1
**
**  Text Edit field
**
**  Copyright ©2000 pinc Software.
**  All rights Reserved.
*/

#include <exec/nodes.h>
#include <exec/lists.h>
#include <utility/hooks.h>
#include <graphics/rastport.h>

/* attributes */

#define EGA_Text           TAG_USER+52
#define EGA_FrameType      TAG_USER+53
#define EGA_Justification  TAG_USER+54
#define EGA_MaxSpaces      TAG_USER+55
#define EGA_Spacing        TAG_USER+56
#define EGA_TabSpaces      TAG_USER+57
#define EGA_ShowControls   TAG_USER+58
#define EGA_NoClips        TAG_USER+59  /* not yet implemented (no marks) */
#define EGA_Scroller       TAG_USER+60
#define EGA_AutoIndent     TAG_USER+61


struct EditGData
{
  APTR   ed_Pool;
  STRPTR ed_Text;
  long   ed_Size,ed_Pos,ed_MarkPos,ed_TextLines;
  struct MinList ed_List;
  struct MinNode *ed_Top;
  UWORD  ed_LineHeight,ed_Spacing,ed_MinSpace,ed_MaxSpace,ed_CharWidth;
  UWORD  ed_Width,ed_Lines,ed_MaxSpaces,ed_TabSpaces,ed_GadWidth;
  UBYTE  ed_APen,ed_BPen,ed_BorderH,ed_BorderV;
  UWORD  ed_Flags;
  long   ed_FrameType;
  struct Gadget *ed_Scroller;
  UBYTE  ed_ClipUnit;
};

#endif   // GADGETS_TEXTEDIT_H
