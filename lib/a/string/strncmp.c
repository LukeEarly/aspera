#include <string.h>

int strncmp(const char *str1, const char *str2, size_t size)
{
	size_t i = 0;
	while (i < size) {
		if (str1[i] > str2[i]) {
			return 1;
		}
		if (str1[i] < str2[i]) {
			return -1;
		}
		i++;
	}
	return 0;
}
