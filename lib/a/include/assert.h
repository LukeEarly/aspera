#ifndef __ASSERT_H_
#define __ASSERT_H_

//#ifdef __is_libk
#include <aspera/tty.h>
#include <stdlib.h>

#define assert(condition)\
	if (!(condition)) {\
		terminal_setcolors(\
			(struct ansi_color){.color=ANSI_RED, .bright=1},\
			(struct ansi_color){.color=ANSI_BLACK, .bright=0});\
		terminal_puts("assertion failed: " #condition "\n");\
		abort();\
	}
//#else
	// TODO liba assert
//#endif // __is_libk

#endif // __ASSERT_H_
