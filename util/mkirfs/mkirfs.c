#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define IRFS_HEADER_BYTES 24
#define IRFS_HEADER_WORDS 6
#define IRFS_DENTRY_BYTES 12
#define IRFS_DENTRY_WORDS 3
#define IRFS_INODE_BYTES 16
#define IRFS_INODE_WORDS 4
#define IRFS_TYPE_NULL 0
#define IRFS_TYPE_DIR 1
#define IRFS_TYPE_REG 2
#define IRFS_TYPE_SYM 3

struct irfs_header {
	uint32_t magic;
	uint32_t reserved;
	uint32_t flags;
	uint32_t size;
	uint32_t heap_offset;
	uint32_t icount;
} header;

struct irfs_inode {
	uint32_t mode;
	uint32_t size;
	uint32_t meta_size;
	uint32_t offset;
};

struct irfs_dentry {
	uint32_t namelen;
	uint32_t nameoff;
	uint32_t inode;
};

struct chunk {
	char *start;
	uint32_t wsize;
} ilist, heap;

uint32_t expand(struct chunk *dest, uint32_t wsize);
uint32_t countfiles(char *dpath);
void append_dirent(uint32_t *offset, uint32_t *wsize, uint32_t inode, char *base);
uint32_t append_inode(uint8_t type, uint8_t exec, uint32_t size, uint32_t meta_size, uint32_t offset);
uint32_t addfile(char *path, struct stat st);
uint32_t recurse(char *dpath, uint32_t parenti);
struct chunk headerchunk();

int main(int argc, char **argv)
{
	char *root;
	char *outfile;
	if (argc == 3) {
		root = argv[1];
		outfile = argv[2];
	}
	else {
		root = ".";
		outfile = "irfs";
	}

	header = (struct irfs_header){
		.magic=0x53465249,
		.reserved=0,
		.flags=0,
		.size=0,
		.heap_offset=0,
		.icount=0
	};
	ilist = (struct chunk){.start=0, .wsize=0};
	heap = (struct chunk){.start=0, .wsize=0};
	printf("%s\n", root);
	recurse(root, 0); // magic
	header.heap_offset = IRFS_HEADER_WORDS + ilist.wsize;
	header.size = header.heap_offset + heap.wsize;
	struct chunk h_chunk = headerchunk();
	FILE *f = fopen(outfile, "w+b");
	fwrite(h_chunk.start, 4, IRFS_HEADER_WORDS, f);
	fwrite(ilist.start, 4, ilist.wsize, f);
	fwrite(heap.start, 4, heap.wsize, f);
	fclose(f);
	puts("done\n");
}

struct chunk headerchunk()
{
	struct chunk h_chunk = (struct chunk){.start=0, .wsize=0};
	expand(&h_chunk, IRFS_HEADER_WORDS);
	memcpy(h_chunk.start, &(header.magic), 4);
	memcpy(h_chunk.start + 4, &(header.reserved), 4);
	memcpy(h_chunk.start + 8, &(header.flags), 4);
	memcpy(h_chunk.start + 12, &(header.size), 4);
	memcpy(h_chunk.start + 16, &(header.heap_offset), 4);
	memcpy(h_chunk.start + 20, &(header.icount), 4);
	return h_chunk;
}

uint32_t expand(struct chunk *dest, uint32_t wsize)
{
	char *new;
	if (!(new = reallocarray(dest->start, dest->wsize + wsize, 4))) {
		fprintf(stderr, "bad reallocarray call");
		exit(1);
	}
	uint32_t offset = dest->wsize;
	memset(new + (offset * 4), 0, wsize * 4);
	dest->start = new;
	dest->wsize += wsize;
	return offset;
}

uint32_t countfiles(char *dpath)
{
	DIR *dir = opendir(dpath);
	if (!dir) {
		printf("failed to open %s", dpath);
		return 0;
	}
	uint32_t count = 0;
	struct dirent *entry;
	while (entry = readdir(dir)) {
		char path[1024];
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;
		snprintf(path, sizeof(path), "%s/%s", dpath, entry->d_name);
		printf("%s\n", path);
		struct stat st;
		stat(path, &st);
		if (S_ISREG(st.st_mode)) {
			count++;
		} else if (S_ISDIR(st.st_mode)) {
			count++;
		} else {
			continue;
		}
	}
	return count;
}

void append_dirent(uint32_t *doffset, uint32_t *wsize, uint32_t inode, char *base)
{
	if (*wsize < 3) exit(2);
	uint32_t slen = strlen(base);
	uint32_t len = slen/4 + !!(slen%4);
	uint32_t offset = expand(&heap, len);
	memcpy(heap.start+(offset*4), base, slen);
	uint32_t *dentry = (uint32_t *) (heap.start + *doffset * 4);
	dentry[0] = len;
	dentry[1] = offset;
	dentry[2] = inode;
	*doffset += IRFS_DENTRY_WORDS;
	*wsize -= IRFS_DENTRY_WORDS;
}

uint32_t append_inode(uint8_t type, uint8_t exec, uint32_t size, uint32_t meta_size, uint32_t offset)
{
	expand(&ilist, IRFS_INODE_WORDS);
	uint32_t i = header.icount;
	uint32_t *inode = (uint32_t *) (((char *)ilist.start)+(i * IRFS_INODE_BYTES));
	uint8_t *mode = (uint8_t *) inode;
	mode[0] = type;
	mode[1] = exec;
	inode[1] = size;
	inode[2] = meta_size;
	inode[3] = offset;
	header.icount++;
	return i;
}

uint32_t addfile(char *path, struct stat st)
{
	FILE *f = fopen(path, "rb");
	fseek(f, 0, SEEK_END);
	uint32_t bytes = ftell(f);
	rewind(f);
	uint32_t wsize = bytes / 4 + !!(bytes % 4);
	uint8_t exec = !!(st.st_mode & S_IXUSR);
	uint32_t offset = expand(&heap, wsize);
	char *ptr = heap.start + (offset * 4);
	fread(ptr, 1, bytes, f);
	fclose(f);
	uint32_t i = append_inode(IRFS_TYPE_REG, exec, wsize, 0, offset);
	return i;
}

uint32_t recurse(char *dpath, uint32_t parenti)
{
	uint32_t count = countfiles(dpath);
	uint32_t words = count * IRFS_DENTRY_WORDS + 2;
	uint32_t offset = expand(&heap, words);
	uint32_t i = append_inode(IRFS_TYPE_DIR, 1, words, 0, offset);
	uint32_t *arr = (uint32_t *) (heap.start + offset * 4);
	arr[0] = i;
	arr[1] = parenti;
	offset += 2;
	words -= 2;
	DIR *dir = opendir(dpath);
	if (!dir) {
		printf("failed to open %s", dpath);
		return 0;
	}
	struct dirent *entry;
	while (entry = readdir(dir)) {
		char path[1024];
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;
		snprintf(path, sizeof(path), "%s/%s", dpath, entry->d_name);
		printf("%s\n", path);
		struct stat st;
		stat(path, &st);
		uint32_t newi;
		if (S_ISREG(st.st_mode)) {
			newi = addfile(path, st);
		} else if (S_ISDIR(st.st_mode)) {
			newi = recurse(path, i);
		} else {
			continue;
		}
		append_dirent(&offset, &words, newi, entry->d_name);
	}
	return i;
}
