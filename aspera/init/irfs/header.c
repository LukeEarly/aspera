#include <init/irfs.h>

int irfs_check_magic(struct irfs_mem mem)
{
	char *magic = (char *) mem.header;
	return mem.length >= IRFS_HEADER_SIZE
		&& magic[0] == 'I'
		&& magic[1] == 'R'
		&& magic[2] == 'F'
		&& magic[3] == 'S';
}
