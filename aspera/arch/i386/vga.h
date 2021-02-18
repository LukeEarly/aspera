#ifndef __VGA_H_
#define __VGA_H_

#include <stdint.h>
#include <stddef.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEM 0xb8000

struct vga_color {
	enum {
		VGA_BLACK = 0,
		VGA_BLUE = 1,
		VGA_GREEN = 2,
		VGA_CYAN = 3,
		VGA_RED = 4,
		VGA_MAGENTA = 5,
		VGA_YELLOW = 6,
		VGA_WHITE = 7
	} color;
	unsigned int bright : 1;
};

static inline uint8_t vga_color_byte(struct vga_color fg, struct vga_color bg)
{
	return fg.color | fg.bright << 3 | bg.color << 4 | bg.bright << 7;
}
static inline uint16_t vga_char(unsigned char c, uint8_t color)
{
	return (uint16_t) c | (uint16_t) color << 8;
}
static inline size_t vga_index(size_t x, size_t y)
{
	return x + VGA_WIDTH * y;
}

#endif // __VGA_H_
