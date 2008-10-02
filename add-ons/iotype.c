/* ignition I/O-Module-Linkfile
 *
 * Copyright �1996-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the MIT License.
 */


#include <exec/types.h>
#include <exec/lists.h>
#include <exec/nodes.h>
#include <exec/memory.h>
#include <dos/dos.h>

#include <clib/exec_protos.h>
#include <clib/dos_protos.h>
#include <pragmas/exec_pragmas.h>
#include <pragmas/dos_pragmas.h>

#include <string.h>
#include <math.h>
/*#include <mieeedoub.h>*/

#define reg(x) register __ ## x
#define PUBLIC __saveds __asm

#ifdef DEBUG
  extern kprintf(STRPTR,...);
# define bug kprintf
#endif


// Must always be in sync with the definition in io.h !!!

struct IOType {
  struct Node io_Node;
  struct MinList io_Descr;
  STRPTR io_Filename;
  STRPTR io_Pattern;
  ULONG  io_BytesUsed;
  char   io_Bytes[32];
  STRPTR io_OriginalBytes;
  UBYTE  io_Flags;
  BPTR   io_Segment;
  long   __asm (*io_Load)(reg (d0) BPTR,reg (a0) struct Mappe *);
  long   __asm (*io_Save)(reg (d0) BPTR,reg (a0) struct Mappe *);
  long   __asm (*io_SetPrefs)(reg (a0) STRPTR);
  STRPTR __asm (*io_GetPrefs)(void);
  void   __asm (*io_OpenPrefsGUI)(reg (a0) struct Screen *);
  void   __asm (*io_ClosePrefsGUI)(void);
  STRPTR io_Short;
  STRPTR io_Prefs;
  STRPTR io_Suffix;
  UBYTE  io_ReadOver;
};

#define IOF_WRITEABLE 1
#define IOF_READABLE 2
#define IOF_ASCII 4
#define IOF_FORCEABLE 8
#define IOF_SUBSET 16
#define IOF_NODEFAULT 32


struct ExecBase *SysBase;
struct Library *DOSBase;
struct Library *MathIeeeDoubBasBase, *MathIeeeDoubTransBase;
struct Library *UtilityBase, *LocaleBase;
APTR   pool, ioBase;

/* Modul-Funktionen*/

extern LONG PUBLIC load(reg (d0) BPTR dat,reg (a0) struct Mappe *mp);
extern LONG PUBLIC save(reg (d0) BPTR dat,reg (a0) struct Mappe *mp);
extern LONG PUBLIC setPrefs(reg (a0) STRPTR);
extern STRPTR PUBLIC getPrefs(void);
extern UBYTE PUBLIC hasPrefsGUI(void);
extern void PUBLIC openPrefsGUI(reg (a0) struct Screen *scr);
extern void PUBLIC closePrefsGUI(void);

#define MAKE_ID(a,b,c,d) ((a << 24) | (b << 16) | (c << 8) | d)


BOOL PUBLIC
InitModule(reg (a6) struct ExecBase *execBase,reg (a0) struct IOType *io,reg (a1) APTR table,reg (a2) APTR mainpool,
	reg (a3) APTR dosBase, reg (d0) APTR mathBase,reg (d1) APTR mathtransBase, reg (d2) long magic,
	reg (d3) APTR utilityBase, reg (d4) APTR localeBase)
{
#ifdef IGNITION_LITE_EDITION
	if (magic != MAKE_ID('I', 'G', 'N', '\0') && magic != MAKE_ID('I', 'G', 'L', '\0'))
		return FALSE;
#else
	if (magic != MAKE_ID('I', 'G', 'N', '\0'))
		return FALSE;
#endif

	SysBase = execBase;
	DOSBase = dosBase;
	UtilityBase = utilityBase;
	MathIeeeDoubBasBase = mathBase;
	MathIeeeDoubTransBase = mathtransBase;
	LocaleBase = localeBase;

	io->io_Load = load;
	io->io_Save = save;
	io->io_SetPrefs = setPrefs;
	io->io_GetPrefs = getPrefs;
	io->io_OpenPrefsGUI = openPrefsGUI;
	io->io_ClosePrefsGUI = closePrefsGUI;

	ioBase = table;
	pool = mainpool;

	setPrefs(io->io_Prefs);

	return TRUE;
}

