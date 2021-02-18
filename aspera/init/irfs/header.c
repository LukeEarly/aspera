#include <init/irfs.h>

int irfs_check_magic(struct irfs_mem mem)
{
	char *magic = (char *) mem.start;
	return mem.length >= IRFS_HEADER_SIZE
		&& magic[0] == 'I'
		&& magic[1] == 'R'
		&& magic[2] == 'F'
		&& magic[3] == 'S';
}

struct irfs_header irfs_parse_header(struct irfs_mem mem)
{
	struct irfs_header header;
	header.magic = mem.start[0];
	header.reserved = mem.start[1];
	header.flags = mem.start[2];
	header.size = mem.start[3];
	header.heap_offset = mem.start[4];
	header.icount = mem.start[5];
	return header;
}
