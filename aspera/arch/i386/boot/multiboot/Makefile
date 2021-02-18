LDSCRIPT=$(BOOTDIR)/linker.ld
BOOT_CFLAGS=
BOOT_CPPFLAGS=
BOOT_LDFLAGS=
BOOT_LIBS=
BOOT_KOBJS=\
$(BOOTDIR)/header.o \
$(BOOTDIR)/boot.o \
$(BOOTDIR)/check.o \
$(BOOTDIR)/irfs_addr.o \

.PHONY: install-multiboot

install-multiboot: install-kernel $(BOOTDIR)/grub.cfg
	grub-file --is-x86-multiboot $(SYSROOT)$(SYSBOOTDIR)/aspera
	mkdir -p $(SYSROOT)$(SYSBOOTDIR)/grub
	cp $(BOOTDIR)/grub.cfg $(SYSROOT)$(SYSBOOTDIR)/grub/
