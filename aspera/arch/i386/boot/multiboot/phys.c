#include <mm/phys.h>
#include "multiboot.h";

struct phys_chunks phys_map()
{
	struct phys_chunks chunks;
	uintptr_t offset = 0;
	uint32_t len = ((uint32_t *) multiboot_info)[11]
	void *addr = (void *) ((uint32_t *) multiboot_info)[12];
	while (offset < len) {
		void *ptr = addr + offset;
		if ((*(uint32_t *) (ptr + 20)) == 1) {

			.addr = (uint64_t *) (ptr + 4),
			.len = (uint64_t *) (ptr + 12),
		}
	}

}
