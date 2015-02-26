/* ignition CSV-I/O-Module
 *
 * Copyright 1996-2009 pinc Software. All Rights Reserved.
 * Licensed under the terms of the GNU General Public License, version 3.
 */

#ifdef __amigaos4__
	#include <exec/exec.h>
	#include <proto/exec.h>
	#include <proto/dos.h>
	#include <proto/utility.h>

	#include <string.h>
#else
	#include <stdlib.h>
#endif

#include "iotype.h"


const STRPTR __version = "$VER: csv.io 0.7 (4.3.2001)";


#define PREFS_GUESS -1L
#define PREFS_ASK -2L

char *separator = ";,\t ";
short loadprefs = PREFS_GUESS;
short saveprefs = '\t';

#ifdef __amigaos4__
	STRPTR Strchr(STRPTR t, char c)
	{
		int i;
	
		for(i = 0; t[i] != '\0'; i++)
			if(t[i] == c)
				return &t[i];
		return NULL;
	}
	#undef  strlen
	#undef  stricmp
	#undef  strnicmp
	#undef  strchr
	#define strlen   Strlen
	#define stricmp  Stricmp
	#define strnicmp Strnicmp
	#define strchr   Strchr
#endif

void PUBLIC
closePrefsGUI(void)
{
}


void PUBLIC
openPrefsGUI(REG(a0, struct Screen *src))
{
}


void
setPrefsString(short prefs,STRPTR t)
{
  if (prefs == PREFS_GUESS)
    strcpy(t,"guess");
  else if (prefs == PREFS_ASK)
    strcpy(t,"ask");
  else
  {
    strcpy(t,"sep=");
    t[4] = prefs;
    t[5] = 0;
  }
}


STRPTR PUBLIC
getPrefs(void)
{
  static char t[32];

  setPrefsString(loadprefs,t);
#ifdef __amigaos4__
  Strlcat(t,"&", 32);
#else
  strcat(t,"&");
#endif
  setPrefsString(saveprefs,t+strlen(t));

  return t;
}


long PUBLIC
setPrefs(REG(a0, STRPTR t))
{
  UBYTE  ok = TRUE;
  STRPTR s;

  if (!t)
    return(TRUE);

  if ((s = strchr(t,'&')) != 0)
  {
    if (*(s+1) == '&')  // überschreiben eines Strings der uns nicht gehört
      s++;
    *s = 0;

    if (!stricmp("ask",s+1))
      saveprefs = PREFS_ASK;
    else if (!strnicmp("sep=",s+1,4))
      saveprefs = *(s+5);
    else
      ok = FALSE;
  }
  if (ok)
  {
    if (!stricmp("guess",t))
      loadprefs = PREFS_GUESS;
    else if (!stricmp("ask",t))
      loadprefs = PREFS_ASK;
    else if (!strnicmp("sep=",t,4))
      loadprefs = *(t+4);
    else
      ok = FALSE;
  }
  if (s)  // alten String wiederherstellen
    *s = '&';

  if (!ok)
    ReportError("Fehlerhafte Voreinstellungen.");

  return(TRUE);
}


long PUBLIC load(REG(d0, BPTR file), REG(a0, struct Mappe *mp))
{
  char   *buffer = NULL,*s,sep;
  struct Page *page;
  struct Cell *c;
  long   size = 0;

  {
    struct FileInfoBlock *fib;

    if (!(fib = AllocDosObject(DOS_FIB,TAG_END)))
      return(RETURN_FAIL);

    if (ExamineFH(file,fib))
      buffer = AllocPooled(pool,1+(size = fib->fib_Size));   /* succeeding NULL-byte */

    FreeDosObject(DOS_FIB,fib);
    if (!buffer)
      return(RETURN_FAIL);
  }
  if (FRead(file,buffer,1,size) != size)
    ReportError("Fehler beim Lesen der Datei.");

  if (loadprefs == PREFS_GUESS)
  {
    int  count[4],i,j,k;
    char *a;

    for(i = 0;i < 4;i++)
      count[i] = 0;

    for(s = buffer;*s;s++)
    {
      for(i = 0,a = separator;*a != *s && *a;a++,i++);
      if (i < 4)
        count[i]++;
    }
    j = count[0] > count[1] ? 0 : 1;
    k = count[2] > count[3] ? 2 : 3;
    sep = count[j] > count[k] ? separator[j] : separator[k];
    //ReportError("Trenner: %d.",count[j] > count);
  }
  else if (loadprefs == PREFS_ASK)
  {
    ReportError("Not yet implemented.");
  }
  else
    sep = loadprefs;

  if ((page = NewPage(mp)) != 0)
  {
    long col = 1,row = 1,i;
    char *a;

    for(s = buffer;*s;s++)
    {
      if (*s == '\n' || *s == 13 && *(s+1) == 10)
      {
        row++;  col = 1;
        if (*s == 13)
          s++;
        continue;
      }
      if (*s == sep)
      {
        col++;
        continue;
      }
      if ((c = NewCell(page, col, row)) != 0)
      {
        a = s;
        if (*s == '"')   // cell contains special characters
        {
          char *b;

          s++;  a++;
          for(i = 0;!(*s == '"' && *(s+1) != '"');s++,i++)
            if (*s == '"')
              s++;
          if ((c->c_Text = b = AllocPooled(pool, i+1)) != 0)
          {
            s = a;
            for(;!(*s == '"' && *(s+1) != '"');)
            {
              if (*s == '"')
                s++;
              *b++ = *s++;
            }
            *b = 0;
          }
        }
        else             // cell data can simply be copied
        {
          for(i = 0;*s && *s != sep && *s != '\n' && *s != 13;s++,i++);
          s--;
          c->c_Text = AllocStringLength(a,i);
        }
        UpdateCellText(page,c);
      }
    }
  }
  FreePooled(pool,buffer,size+1);

  return(RETURN_OK);
}


long PUBLIC save(REG(d0, BPTR dat), REG(a0, struct Mappe *mp))
{
  struct Page *page;
  struct Cell *c;
  ULONG  lastrow = 1,lastcol = 1;
  UBYTE  sep = '\t';

  if (saveprefs > 0)
    sep = saveprefs;

  foreach(&mp->mp_Pages,page)
  {
    foreach(&page->pg_Table,c)
    {
      if (c->c_Text)
      {
        STRPTR t;

        while(lastrow < c->c_Row)
        {
          FPutC(dat,'\n');
          lastrow++;  lastcol = 1;
        }
        while(lastcol < c->c_Col)
        {
          FPutC(dat,sep);
          lastcol++;
        }
        for(t = c->c_Text;*t;t++)
          if (*t == sep || *t == '"')
            break;
        if (*t)
        {
          FPutC(dat,'"');
          for(t = c->c_Text;*t;t++)
          {
            if (*t == '"')
              FPutC(dat,'"');
            FPutC(dat,*t);
          }
          FPutC(dat,'"');
        }
        else
          FPuts(dat,c->c_Text);
      }
    }
  }
  return(RETURN_OK);
}


#if defined(__SASC)
void STDARGS _XCEXIT(long a)
{
}
#endif
