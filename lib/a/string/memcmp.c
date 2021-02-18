#include <string.h>

int memcmp(const void *ptr1, const void *ptr2, size_t size)
{
	const unsigned char *buf1 = (const unsigned char *) ptr1;
	const unsigned char *buf2 = (const unsigned char *) ptr2;
	for (size_t i = 0; i < size; i++) {
		if (buf1[i] > buf2[i]) {
			return 1;
		}
		if (buf1[i] < buf2[i]) {
			return -1;
		}
	}
	return 0;
}
