#include <string.h>

void *memcpy(void *dest, const void *src, size_t size)
{
	unsigned char *dest_buf = (unsigned char *) dest;
	const unsigned char *src_buf = (const unsigned char *) src;
	for (size_t i = 0; i < size; i++) {
		dest_buf[i] = src_buf[i];
	}
	return dest_buf;
}
