#ifndef __PHYS_H_
#define __PHYS_H_

#include <stdint.h>

struct phys_chunk {
	uintptr_t start;
	uintptr_t len;
};

struct phys_chunks {
	uint32_t count;
	struct phys_chunk chunks[];
};

struct phys_chunks phys_map();

#endif // __PHYS_H_
