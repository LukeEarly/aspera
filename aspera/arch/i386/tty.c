#include <stdint.h>
#include <stddef.h>
#include <aspera/tty.h>
#include <stdarg.h>
#include "vga.h"


static uint16_t* const VGA_BUFFER = (uint16_t*) VGA_MEM;
static size_t terminal_x;
static size_t terminal_y;
static uint8_t terminal_color;
static struct ansi_color terminal_fg;
static struct ansi_color terminal_bg;

/* ANSI VGA
 * 0    0
 * 1    4*
 * 2    2
 * 3    6*
 * 4    1*
 * 5    5
 * 6    3*
 * 7    7
 */
static inline struct vga_color ansi2vga(struct ansi_color c)
{
	struct vga_color vc;
	vc.bright = c.bright;
	switch (c.color) {
	case ANSI_RED:
		vc.color = VGA_RED;
		break;
	case ANSI_BLUE:
		vc.color = VGA_BLUE;
		break;
	case ANSI_YELLOW:
		vc.color = VGA_YELLOW;
		break;
	case ANSI_CYAN:
		vc.color = VGA_CYAN;
		break;
	default:
		vc.color = c.color;
	}
	return vc;
}

void terminal_init()
{
	terminal_x = 0;
	terminal_y = 0;
	terminal_setcolors(
		(struct ansi_color){.color=ANSI_GREEN, .bright=0},
		(struct ansi_color){.color=ANSI_BLACK, .bright=0});
	terminal_clear();
	terminal_x = 0;
	terminal_y = 0;
}

void terminal_clear()
{
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		// TODO memcpy
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			terminal_putchar(' ');
		}
	}
}

int terminal_putchar(char c)
{
	if (c >= 32 && c <= 126) // not control key
		VGA_BUFFER[vga_index(terminal_x, terminal_y)] = vga_char(c, terminal_color);
	if (c && (++terminal_x == VGA_WIDTH || c == '\n')) {
		terminal_x = 0;
		if (++terminal_y == VGA_HEIGHT) {
			terminal_scroll(1);
		}
	}
	return c;
}

void terminal_write(const char* ptr, size_t len)
{
	for (size_t i = 0; i < len; i++) {
		terminal_putchar(ptr[i]);
	}
}

void terminal_puts(const char* str)
{
	size_t i = 0;
	while (terminal_putchar(str[i++])) {}
}

void terminal_printf(const char *format, ...)
{
	va_list arg;
	va_start(arg, format);
	while (*format) {
		if (*format == '%') {
			format++;
			int value;
			switch (*format) {
			case '%':
				terminal_putchar('%');
				break;
			case 'X':
				switch(format[1]) {
				case '8':
					//format++;
					//terminal_putchar('0');
					//terminal_putchar('x');
					//format++;
					//value = va_arg(arg, uint64_t);
					//for (int i = 2 * sizeof(uint64_t) - 1; i >= 0; i--) {
						//char digit = ((value >> (4 * i)) & 0xF) + 0x30;
						//if (digit > '9')
							//digit += 7; // skip special characters
						//terminal_putchar(digit);
					//}
					//break;
				case '4':
					format++;
				default:
					terminal_putchar('0');
					terminal_putchar('x');
					format++;
					value = va_arg(arg, uint32_t);
					for (int i = 2 * sizeof(uint32_t) - 1; i >= 0; i--) {
						char digit = ((value >> (4 * i)) & 0xF) + 0x30;
						if (digit > '9')
							digit += 7; // skip special characters
						terminal_putchar(digit);
					}
					break;
				}
				break;
			case 's':
				terminal_puts(va_arg(arg, char *));
				format++;
				break;
			default:
				terminal_puts("not implemented: %");
			}

			//if (*format == '%') {
				//terminal_putchar('%');
			//} else {
				//int left_align;
				//int plus;
				//switch (*format) {
				//case '-':
//
					//break;
				//default:
					//action
				//}
				//int leading_zero = *format == '0';
				//while (*format >= '0' && *format <= '9') {
					//// TODO POSIX parameter extension
				//
				//}
		} else {
			terminal_putchar(*format);
			format++;
		}
	}
}

void terminal_scroll(size_t rows)
{
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		if (y < VGA_HEIGHT - rows) {
			for (size_t x = 0; x < VGA_WIDTH; x++) {
				VGA_BUFFER[vga_index(x, y)] = VGA_BUFFER[vga_index(x, y + rows)];
			}
		} else {
			for (size_t x = 0; x < VGA_WIDTH; x++) {
				VGA_BUFFER[vga_index(x, y)] = vga_char(' ', terminal_color);
			}
		}
	}
	terminal_y -= rows;
}

void terminal_setcolors(struct ansi_color fg, struct ansi_color bg)
{
	terminal_fg = fg;
	terminal_bg = bg;
	terminal_color = vga_color_byte(ansi2vga(fg), ansi2vga(bg));
}
