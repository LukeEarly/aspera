#include <fs/vfs.h>
#include <string.h>

struct path {
	char *name;
	struct path *parent;
};

struct FILE {
	char *name;
	struct file *parent;
	struct fperm perm;
	struct fs *fs;
	fpos_t cursor;
};

struct mnt {
	struct path path;
	struct fs fs;
};

FILE *file_req(const char *path, struct fperm perm)
{
	//TODO malloc
}

struct path parse(char *p)
{
	size_t last_slash = strlen(p);
	for (size_t i = strlen(p) - 1; i >= 1; i--) {
		if (p[i] == '/') {
			last_slash = i;
			// TODO malloc
		}
	}
}
