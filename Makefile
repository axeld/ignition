## ignition-Makefile
##
## Copyright �1996-2008 pinc Software. All Rights Reserved.
## Licensed under the terms of the GNU General Public License, version 3.

#CFLAGS         = nostkchk afp math=i ign=147
CFLAGS          = nostkchk afp math=i code=f data=f ign=79+147 utillib
#LFLAGS         = sc sd nd noicons
LFLAGS          = sc sd noicons

#OPTIMIZE       = opt opttime
OPTIMIZE        = noopt
CPU             = 68020
#CPU            = any
DEFINES	        =
#DEFINES	     = def=IGNITION_DEMO
#DEFINES		 = def=IGNITION_LITE_EDITION
DEBUG           = dbg=l def=DEBUG def=GDEBUG
#DEBUG          = dbg=l def=DEBUG
#DEBUG          = nodbg
LIBS            = lib:scmieee.lib lib:scnb.lib lib:amiga.lib lib:debug.lib lib:clip.o lib/safeclip.o
GST             = include:allnb.gst

all:              ignition addons guides

start:            ignition
	run ignition

addons:
	@cd add-ons; make -f Makefile all

ignition_strings.o ignition_strings.h:	locale/ignition.cd
	CatComp DESCRIPTOR home:source/ignition/locale/ignition.cd CFILE ignition_strings.h OBJFILE ignition_strings.o

help/deutsch/ignition.guide: help/deutsch/ignition.in.guide
	sc help/deutsch/ignition.in.guide $(DEFINES) pponly objname=help/deutsch/ignition.guide
	flush

help/english/ignition.guide: help/english/ignition.in.guide
	sc help/english/ignition.in.guide $(DEFINES) pponly objname=help/english/ignition.guide
	flush

guides:	help/english/ignition.guide help/deutsch/ignition.guide

catalogs:
	@echo "Creating ignition catalogs & flushing memory"
	@CatComp DESCRIPTOR locale/ignition.cd TRANSLATION locale/ignition_english.ct CATALOG LOCALE:Catalogs/english/ignition.catalog >nil:
	@copy LOCALE:Catalogs/english/ignition.catalog distribution/full/locale/english/catalogs/english/
	@copy LOCALE:Catalogs/english/ignition.catalog distribution/lite/locale/english/catalogs/english/
	@flush

clean:
	delete \#?.o

OBJS            = ignition.o prefs.o prefsio.o edit.o table.o cell.o calc.o font.o functions.o \
				  handlewindows.o gadgets.o initwindows.o images.o windows.o objects.o debug.o \
                  rexx.o support.o project.o io.o classes.o handleprefs.o color.o reference.o \
				  prefsgadgets.o graphic.o clip.o undo.o hooks.o database.o pointer.o ignition_strings.o \
				  boopsi.o diagram.o printer.o lock.o cmd.o menu.o popper.o screen.o search.o

windows.o:        windows.c windefs.h version.h
screen.o:         version.h types.h
classes.o:        classes.c classes.h
diagram.o:        diagram.c graphic.h

ignition:         ignition_strings.h $(OBJS)
	@echo "linking..."
	@slink with lib:utillib.with \
		from lib:c.o $(OBJS) \
		to $@ \
		lib $(LIBS) \
		$(LFLAGS)

.c.o:
	@echo "compiling $*.c"
	@sc $(OPTIMIZE) $(CFLAGS) $(DEFINES) $(DEBUG) gst=$(GST) cpu=$(CPU) $*.c

.c.oo:
	sc $(CFLAGS) $(DEBUG) cpu=$(CPU) gst=$(GST) objname=$*.oo $*.c

.c.ooo:
	sc $(OPTIMIZE) $(CFLAGS) $(DEBUG) gst=$(GST) cpu=any objname=$*.ooo $*.c

.asm.o:
	asm -D -DCPU_$(CPU) -u $*.asm

