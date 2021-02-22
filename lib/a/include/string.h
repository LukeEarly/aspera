#ifndef __STRING_H_
#define __STRING_H_

#include <sys/cdefs.h>

#include <stddef.h> // for size_t

#ifdef __cplusplus
extern "C" {
#endif

// TODO implement
void *memchr(const void *ptr, int c, size_t size);

int memcmp(const void *ptr1, const void *ptr2, size_t size);

void *memcpy(void *dest, const void *src, size_t size);

void *memmove(void *dest, const void *src, size_t size);

// TODO implement
void *memset(void *ptr, int c, size_t size);

// TODO implement
char *strcat(char *dest, const char *src);

// TODO implement
char *strncat(char *dest, const char *src, size_t size);

// TODO implement
char *strchr(const char *str, int c);

int strcmp(const char *str1, const char *str2);

int strncmp(const char *str1, const char *str2, size_t size);

// TODO implement
int strcoll(const char *str1, const char *str2);

// TODO implement
char *strcpy(char *dest, const char *src);

// TODO implement
char *strncpy(char *dest, const char *src, size_t size);

// TODO implement
size_t strcspn(const char *str1, const char *str2);

// TODO implement
char *strerror(int errnum);

size_t strlen(const char *str);

// TODO implement
char *strpbrk(const char *str1, const char *str2);

// TODO implement
char *strrchr(const char *str, int c);

// TODO implement
size_t strspn(const char *str1, const char *str2);

// TODO implement
char *strstr(const char *haystack, const char *needle);

// TODO implement
char *strtok(char *str, const char *delim);

// TODO implement
size_t strxfrm(char *dest, const char *src, size_t n);

#ifdef __cplusplus
}
#endif

#endif // __STRING_H_
