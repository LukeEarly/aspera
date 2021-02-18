#include <string.h>

void *memmove(void *dest, const void *src, size_t size)
{
	unsigned char *tmp[size];
	memcpy(tmp, src, size);
	memcpy(dest, tmp, size);
	return dest;
}
