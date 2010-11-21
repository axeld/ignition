CC=i386-aros-gcc
CFLAGS=-Wall -Wno-pointer-sign -I../../include -Iinclude
LDFLAGS=-lgraphics -lintuition -lutility -lrom -nostartfiles

EXE = ../pScroller.gadget

OBJS = Scroller_lib.o Scroller.o

.PHONY: all
all : $(EXE)

$(EXE) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

.PHONY: clean
clean :
	rm -f $(OBJS) $(EXE)

.PHONY: distclean
distclean : clean


Scroller_lib.o: Scroller_lib.c Scroller_includes.h \
  ../../include/SDI_compiler.h ../../include/compatibility.h \
  include/gadgets/Scroller.h
Scroller.o: Scroller.c Scroller_includes.h ../../include/SDI_compiler.h \
  ../../include/compatibility.h include/gadgets/Scroller.h
