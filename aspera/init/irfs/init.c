#include <init/init.h>
#include <init/irfs.h>
#include <aspera/tty.h>

int init_irfs()
{
	terminal_printf("INITRAMFS\n=========\n");
	struct irfs_mem mem = irfs_addr();
	terminal_printf("irfs at %X\nstring: %s\nlength: %X\n", mem.start, mem.start, mem.length);
	struct irfs_header header = irfs_parse_header(mem);
	terminal_printf("res: %X\flags: %X\nsize: %X\nheap_offset: %X\nicount: %X\n",
			header.reserved,
			header.flags,
			header.size,
			header.heap_offset,
			header.icount
		);
	return 1;
}
