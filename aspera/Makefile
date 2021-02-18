# Aspera Kernel

ARCH?=i386

CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lk -lgcc

SYSROOT?=sysroot
SYSLIBDIR=/lib
SYSBOOTDIR=/boot
SYSINCLUDEDIR=/include

ARCHDIR=arch/$(ARCH)
include $(ARCHDIR)/Makefile
# arch provides ARCH_{{C,CPP,LD}FLAGS,LIBS,KOBJS,TRIPLET} LDSCRIPT

CFLAGS:=$(CFLAGS) $(ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(ARCH_LDFLAGS)
LIBS:=$(LIBS) $(ARCH_LIBS)

include init/Makefile
# provides INIT_KOBJS

KOBJS=\
$(ARCH_KOBJS) \
$(INIT_KOBJS) \

OBJS=\
$(ARCHDIR)/crti.o \
$(ARCHDIR)/crtbegin.o \
$(KOBJS) \
$(ARCHDIR)/crtend.o \
$(ARCHDIR)/crtn.o \

# things going to be linked
IUNGENDA=\
$(LDFLAGS) \
$(ARCHDIR)/crti.o \
$(ARCHDIR)/crtbegin.o \
$(KOBJS) \
$(LIBS) \
$(ARCHDIR)/crtend.o \
$(ARCHDIR)/crtn.o \

AR=$(ARCH_TRIPLET)-ar
AS=$(ARCH_TRIPLET)-as
LD=$(ARCH_TRIPLET)-ld
CC=$(ARCH_TRIPLET)-gcc

.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .c .S

all: aspera

aspera: $(OBJS) $(LDSCRIPT)
	$(CC) -T $(LDSCRIPT) -o $@ $(CFLAGS) $(IUNGENDA)

$(ARCHDIR)/crtbegin.o $(ARCHDIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

.S.o:
	$(CC) -MD -c $< -o  $@ $(CFLAGS) $(CPPFLAGS)

clean:
	rm -f aspera
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-kernel

install-headers:
	mkdir -p $(SYSROOT)$(SYSINCLUDEDIR)
	cp -R --preserve=timestamps include/. $(SYSROOT)$(SYSINCLUDEDIR)/.

install-kernel: aspera
	mkdir -p $(SYSROOT)$(SYSBOOTDIR)
	cp aspera $(SYSROOT)$(SYSBOOTDIR)

-include $(OBJS:.o=.d)
# end
