#include <init/init.h>
#include <init/irfs.h>
#include <aspera/tty.h>

int init_irfs()
{
	terminal_printf("INITRAMFS\n=========\n");
	struct irfs_mem mem = irfs_addr();
	terminal_printf("irfs at %X\nstring: %s\nlength: %X\n", mem.header, mem.header, mem.length);
	terminal_printf("res: %X\nflags: %X\nsize: %X\nheap_offset: %X\nicount: %X\n",
			mem.header->reserved,
			mem.header->flags,
			mem.header->size,
			mem.header->heap_offset,
			mem.header->icount
		);
	terminal_printf("header: %X\nilist: %X\nheap: %X\n",
			mem.header,
			mem.ilist,
			mem.heap
		);
	struct irfs_inode *root = &mem.ilist[0];
	//struct irfs_inode *entry = irfs_getdirent(mem, root, "entry");
	struct irfs_inode *entry = &mem.ilist[1];
	if (entry) {
		char *text = (char *) (mem.heap + entry->offset);
		size_t size = entry->size * 4;
		for (size_t i = 0; i < size; i++) {
			terminal_putchar(text[i]);
		}
	}
	return 1;
}
