#ifndef __TTY_H_
#define __TTY_H_
#include <stddef.h>

struct ansi_color {
	enum {
		ANSI_BLACK = 0,
		ANSI_RED = 1,
		ANSI_GREEN = 2,
		ANSI_YELLOW = 3,
		ANSI_BLUE = 4,
		ANSI_MAGENTA = 5,
		ANSI_CYAN = 6,
		ANSI_WHITE = 7
	} color;
	unsigned int bright : 1;
};

void terminal_init();
int terminal_putchar(char c);
void terminal_write(const char* ptr, size_t len);
void terminal_printf(const char *format, ...);
void terminal_puts(const char* str);
void terminal_scroll(size_t rows);
void terminal_clear();
void terminal_setcolors(struct ansi_color fg, struct ansi_color bg);

#endif // __TTY_H_
