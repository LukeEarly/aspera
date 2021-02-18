# Aspera liba/libk

ARCH?=i386

SYSROOT?=sysroot
SYSINCLUDEDIR=/include
SYSLIBDIR=/lib

CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

LC_CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
LC_CPPFLAGS:=$(CPPFLAGS) -D__is_liba -Iinclude
LK_CFLAGS:=$(CFLAGS)
LK_CPPFLAGS:=$(CPPFLAGS) -D__is_libk -Iinclude

ARCHDIR=arch/$(ARCH)
include $(ARCHDIR)/Makefile
# arch provides ARCH_{L{C,K}_{C{,PP}FLAGS,OBJS},TRIPLET}

LC_CFLAGS:=$(LC_CFLAGS) $(ARCH_LC_CFLAGS)
LC_CPPFLAGS:=$(LC_CPPFLAGS) $(ARCH_LC_CPPFLAGS)
LK_CFLAGS:=$(LK_CFLAGS) $(ARCH_LK_CFLAGS)
LK_CPPFLAGS:=$(LK_CPPFLAGS) $(ARCH_LK_CPPFLAGS)

LK_PLAIN_OBJS=\
$(ARCH_LK_OBJS) \
stdlib/abort.o \
string/memcmp.o \
string/strcmp.o \
string/memcpy.o \
string/memmove.o \
string/memset.o \
string/strlen.o \

LC_OBJS=\
$(ARCH_LC_OBJS) \
$(LK_PLAIN_OBJS) \

LK_OBJS=$(LK_PLAIN_OBJS:.o=.libk.o)

AR=$(ARCH_TRIPLET)-ar
AS=$(ARCH_TRIPLET)-as
LD=$(ARCH_TRIPLET)-ld
CC=$(ARCH_TRIPLET)-gcc

.PHONY: all clean liba libk install install-headers install-libs

.SUFFIXES: .o .libk.o .c .S

all: libk.a # liba.a coming soon

liba.a: $(LC_OBJS)
	$(AR) rcs $@ $(LC_OBJS)

libk.a: $(LK_OBJS)
	$(AR) rcs $@ $(LK_OBJS)

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(LC_CFLAGS) $(LC_CPPFLAGS)

.S.o:
	$(CC) -MD -c $< -o $@ $(LC_CFLAGS) $(LC_CPPFLAGS)

.c.libk.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(LK_CFLAGS) $(LK_CPPFLAGS)

.S.libk.o:
	$(CC) -MD -c $< -o $@ $(LK_CFLAGS) $(LK_CPPFLAGS)

clean:
	rm -f *.a
	rm -f $(LC_OBJS) $(LK_OBJS) *.o */*.o */*/*.o
	rm -f $(LC_OBJS:.o=.d) $(LK_OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-libs

install-headers:
	mkdir -p $(SYSROOT)$(SYSINCLUDEDIR)
	cp -R --preserve=timestamps include/. $(SYSROOT)$(SYSINCLUDEDIR)/.

install-libs: libk.a #liba.a coming soon
	mkdir -p $(SYSROOT)$(SYSLIBDIR)
	cp libk.a $(SYSROOT)$(SYSLIBDIR)

-include $(LC_OBJS:.o=.d)
-include $(LK_OBJS:.o=.d)
# end
