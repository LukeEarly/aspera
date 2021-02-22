#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <init/irfs.h>
#include "multiboot.h"

struct irfs_mem irfs_addr() {
	uint32_t flags = *(uint32_t *) multiboot_info;
	assert(flags & (1 << 3));
	uint32_t count = *(uint32_t *) (multiboot_info + 20);
	uint32_t *modarr = (uint32_t *) (*(uint32_t *) (multiboot_info + 24));
	for (size_t i = 0; i < count; i++) {
		uint32_t *modstruct = modarr + 16*i;
		uint32_t start = modstruct[0];
		struct irfs_header *header = (struct irfs_header *) start;
		uint32_t end = modstruct[1];
		struct irfs_mem mem = (struct irfs_mem) {
			.length = (uintptr_t) (end - start),
			.header = header,
			.ilist = (struct irfs_node *) (header + 1),
			.heap = ((uint32_t *) header + header->heap_offset)
		};
		if (mem.length > 12 && irfs_check_magic(mem)) {
			return mem;
		}
	}
	abort();
}
