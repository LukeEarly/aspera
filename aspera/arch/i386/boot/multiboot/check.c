#include <stdint.h>
#include <assert.h>
#include <aspera/tty.h>
#include "multiboot.h"

uint8_t multiboot_info[116];

#ifdef __debug

struct mmap_entry_ptrs {
	uint32_t *size;
	uint64_t *addr;
	uint64_t *len;
	uint32_t *type;
};

inline struct mmap_entry_ptrs get_entry_ptrs(void *ptr) {
	return (struct mmap_entry_ptrs){
		.size = (uint32_t *) ptr,
		.addr = (uint64_t *) (ptr + 4),
		.len = (uint64_t *) (ptr + 12),
		.type = (uint32_t *) (ptr + 20),
	};
}

static char* const FLAG_STRINGS[] = {"Memory Range",
				     "Boot Device",
				     "Command Line",
				     "Modules Table",
				     "Symbols-4",
				     "Symbols-5",
				     "Memory Table",
				     "Drives Table",
				     "Config Table",
				     "Bootloader",
				     "APM Table",
				     "VBE Table",
				     "Framebuffer Table"};

void print_flags(uint32_t flags)
{
	for (size_t i = 0; i < 13; i++) {
		if (flags & (1 << i)) {
			terminal_printf("%s ", FLAG_STRINGS[i]);
		}
	}
    terminal_putchar('\n');
}

void map_mem(uint32_t len, void *addr)
{
	size_t offset = 0;
	uint64_t free = 0;
	while (offset < len) {
		struct mmap_entry_ptrs mmap = get_entry_ptrs(addr + offset);
		uint64_t end = *mmap.addr + *mmap.len;
		terminal_printf("size: %X; addr: %X,%X; len: %X,%X; end: %X,%X; type: %X\n",
						*mmap.size,
						(uint32_t) (*mmap.addr >> 32), (uint32_t) *mmap.addr,
						(uint32_t) (*mmap.len >> 32), (uint32_t) *mmap.len,
						(uint32_t) (end >> 32), (uint32_t) end,
						*mmap.type);
		if (*mmap.type == 1) {
			free += *mmap.len;
		}
		offset += 4 + *mmap.size;
	}
	terminal_printf("total free memory: %X bytes\n", (uint32_t) free);
}

#endif // __debug

void boot_check(uint32_t magic, uint32_t *info)
{
	terminal_init();
	assert(magic == 0x2BADB002);
	uint8_t *info8 = (uint8_t *) info;
	for (size_t i = 0; i < 116; i++) {
		multiboot_info[i] = info8[i];
	}
	#ifdef __debug
	terminal_printf("magic: %X\n", magic);
	print_flags(info[0]);
	terminal_printf("flags: %X\nmem_lower: %X\nmem_upper: %X\nboot_device: %X\ncmdline: %s\nmmap_length: %X\nmmap_addr: %X\nbootloader: %s\n",
					info[0], info[1], info[2], info[3], info[4], info[11], info[12], info[16]);
	map_mem(info[11], (void *) info[12]);
	#endif // __debug
}
