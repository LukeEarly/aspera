#ifndef __IRFS_H_
#define __IRFS_H_

#include <stdint.h>

/**
 * Minimum version of IRFS required.
 */
#define IRFS_MIN_VERSION 0
/**
 * Size of header.
 */
#define IRFS_HEADER_SIZE 24

/**
 * A chunk of memory that stores the IRFS.
 */
struct irfs_mem {
	uint32_t *start; /**< pointer to the start of the image */
	uintptr_t length; /**< length in bytes */
};

/**
 * First 24 bytes of IRFS file.
 */
struct irfs_header {
	uint32_t magic; /**< 'I' 'R' 'F' 'S' - no null */
	uint32_t reserved; /**< 0 for now */
	uint32_t flags; /**< 0 for now */
	uint32_t size; /**< size of image in words */
	uint32_t heap_offset; /**< size of header + ilist in words */
	uint32_t icount; /**< number of inodes */
};

/**
 * An entry in the ilist.
 */
struct irfs_inode {
	uint32_t mode; /**< permissions and type */
	uint32_t size; /**< size of entire file, in words */
	uint32_t meta_size; /**< size of metadata, in words */
	uint32_t offset; /**< offset of metadata from start of heap, in words */
};

/**
 * Entry in directory table
 */
struct irfs_dirent {
	uint32_t namelen; /**< length of name, in words */
	uint32_t nameptr; /**< offset of name from start of heap, in words */
	uint32_t inode; /**< inode number */
};

/**
 * Loads and gets address of irfs.
 * @return memory chunk.
 */
struct irfs_mem irfs_addr();
/**
 * Checks the magic string "IRFS" (no null byte).
 * @param mem memory location and size of image.
 * @return 1 if matches, 0 if not
 */
int irfs_check_magic(struct irfs_mem mem);
/**
 * Populates the struct with the values of the header.
 * @param mem memory location and size of image.
 * @return a struct of the header values
 */
struct irfs_header irfs_parse_header(struct irfs_mem mem);

#endif // __IRFS_H_
