#include <aspera/tty.h>
#include <init/init.h>
#include <stdlib.h>

void kernel_entry(void)
{
	terminal_puts("aspera\nan operating system\n");
	//init_mm();
	//init_irfs();
	abort();
}
