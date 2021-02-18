#include <string.h>

void *memset(void *ptr, int c, size_t size)
{
	unsigned char *buf = (unsigned char *) ptr;
	for (size_t i = 0; i < size; i++) {
		buf[i] = c;
	}
	return ptr;
}
