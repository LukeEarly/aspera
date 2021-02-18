#include <string.h>

int strcmp(const char *str1, const char *str2)
{
	size_t i = 0;
	while (str1[i]) {
		if (str1[i] > str2[i]) {
			return 1;
		}
		if (str1[i] < str2[i]) {
			return -1;
		}
		i++;
	}
	if (0 > str2[i]) {
		return 1;
	}
	if (0 < str2[i]) {
		return -1;
	}
	return 0;
}
