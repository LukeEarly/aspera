#include <stdlib.h>
#ifdef __is_libk
#include <aspera/tty.h>
#endif // __is_libk

__attribute__((__noreturn__))
void abort(void)
{
#ifdef __is_libk
	// TODO kernel panic, stack trace
	terminal_setcolors(
		(struct ansi_color){.color=ANSI_RED, .bright=1},
		(struct ansi_color){.color=ANSI_BLACK, .bright=0});
	terminal_puts("kernel panic; abort()");
#else
	// TODO liba abort
#endif // __is_libk
	while (1) {}
	__builtin_unreachable();
}
