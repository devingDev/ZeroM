#ifndef MEMORY_H
#define MEMORY_H
#include <psp2/kernel/sysmem.h> 
#include <psp2/kernel/clib.h> 

#define ALIGN(x, a)          (((x) + ((a)-1)) & ~((a)-1))
// type SCE_KERNEL_MEMBLOCK_TYPE_USER_RW
void *vita_mem_alloc(unsigned int type, unsigned int size, unsigned int alignment, SceUID *uid);


extern void* memblock;
void create_memspace();
void destroy_memspace();
void* mem_malloc(SceSize size);
void* mem_calloc(SceSize num, SceSize size);
void* mem_realloc(void* oldMemPtr, SceSize size);
void mem_free(void* memPtr);

#endif