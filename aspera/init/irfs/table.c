#include <init/irfs.h>
#include <string.h>

struct irfs_inode *irfs_getdirent(struct irfs_mem mem, struct irfs_inode *dir, char *name)
{
	struct irfs_dtable *dtable = (struct irfs_dtable *) (mem.heap + dir->offset + dir->meta_size);

	if (strcmp(name, ".") == 0) {
		return &mem.ilist[dtable->self];
	}

	if (strcmp(name, "..") == 0) {
		return &mem.ilist[dtable->parent];
	}

	struct irfs_dirent *low, *high;
	low = (struct irfs_dirent *) (mem.heap + dir->offset + dir->meta_size);
	high = (struct irfs_dirent *) (mem.heap + dir->offset + dir->size - sizeof(struct irfs_dirent));

	while (high >= low) {
		struct irfs_dirent *mid = low + (high - low) / 2;
		char *n = (char *) (mem.heap + mid->nameptr);
		int a = strncmp(name, n, mid->namelen * 4);

		if (a < 0)
			high = mid - 1;
		else if (a > 0)
			low = mid + 1;
		else
			return &mem.ilist[mid->inode];
	}
	return 0;
}
