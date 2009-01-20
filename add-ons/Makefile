## ignition-Modules-Makefile
##
## Copyright 1996-2009 pinc Software. All Rights Reserved.
## Licensed under the terms of the GNU General Public License, version 3.

.c.o:
	@echo "compiling $*.c"
	@sc $(OPTIMIZE) $(CFLAGS) $(INCLUDES) $(DEFINES) $(DEBUG) gst=$(GST) cpu=$(CPU) idir=/ $*.c

.c.oo:
	sc $(CFLAGS) $(INCLUDES) $(DEFINES) $(DEBUG) cpu=$(CPU) gst=$(GST) objname=$*.oo $*.c

.c.ooo:
	sc $(OPTIMIZE) $(CFLAGS) $(INCLUDES) $(DEBUG) gst=$(GST) cpu=any objname=$*.ooo $*.c

.asm.o:
	asm -D -DCPU_$(CPU) -u $*.asm

#CFLAGS			= nostkchk afp math=i ign=147
CFLAGS			= nostkchk math=i code=n data=n nostartup ign=147 utillib
#LFLAGS			= sc sd nd noicons
LFLAGS			= sc sd noicons

#OPTIMIZE		= opt opttime
OPTIMIZE		= noopt
CPU				= 68040
#CPU			= 68020
INCLUDES		= idir=/libs/include idir=/libs
#DEFINES		= def=IGNITION_LITE_EDITION
DEFINES			=
DEBUG			= dbg=l def=DEBUG
#DEBUG			= nodbg
LIBS			= lib:scmieee.lib lib:sc.lib lib:amiga.lib lib:debug.lib
GST				= include:all.gst

IOOBJS			= iotype.o
GCOBJS			= gclass.o

all:			ioobjs iotypes gcobjs gclasses

start:			all

clean:
	delete *.o *.gc *.io

lib:
	makelib /*.h gclass_functable.c name=gclass to=t:include fd=gclass.fd protos with=gclass_makelib.with
	copy T:include/clib/gclass_protos.h ""
	copy T:include/pragmas/gclass_pragmas.h ""
	smake -a gcobjs gclasses

ioobjs:			$(IOOBJS) csv.o ascii.o turbocalc.o
iotypes:		csv.io ascii.io turbocalc.io

gcobjs:			$(GCOBJS) \
				button.o checkbox.o frame.o text.o \
				line.o rectangle.o gradient.o \
				area_diagram.o column_diagram.o line_diagram.o circle_diagram.o

gclasses:		button.gc checkbox.gc frame.gc text.gc \
				line.gc rectangle.gc gradient.gc \
				area_diagram.gc column_diagram.gc line_diagram.gc circle_diagram.gc

iotype.c:		iotype.h
gclass.c:		gclass.h

%.io : %.o 			$(IOOBJS) #%.o
	@echo "linking $@..."
	@slink with lib:utillib.with from $(IOOBJS) $*.o to $@ lib $(LIBS) $(LFLAGS)

%.gc : %.o 			$(GCOBJS) #%.o
	@echo "linking $@..."
	@slink with lib:utillib.with \
		from $(GCOBJS) $*.o \
		to $@ \
		lib $(LIBS) \
		$(LFLAGS)
