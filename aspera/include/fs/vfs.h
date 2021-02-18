#ifndef __VFS_H_
#define __VFS_H_

#include <stddef.h>

typedef struct FILE FILE;
struct fs;
struct fs {
	void (*open)(FILE *stream);
	void (*close)(FILE *stream);
	size_t (*write)(void *buf, size_t size, size_t count, FILE *stream);
	size_t (*read)(void *buf, size_t size, size_t count, FILE *stream);
	int (*exec)(int argc, void **argv, FILE *file);
};
ruct fperm {
	int l : 1;
	int r : 1;
	int w : 1;
	int x : 1;
};
FILE *file_req(const char *path, struct fperm perm);
int file_open_req(FILE *file);
int file_open_reqs(int filec, FILE **filev);
int file_close(FILE *node);
int fs_reg(struct fs* fs, const char *path);

#endif // __VFS_H_
