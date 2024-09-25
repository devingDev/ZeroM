#ifndef MEMORY_H
#define MEMORY_H
#include <psp2/kernel/sysmem.h> 
#include <psp2/kernel/clib.h> 

#define ALIGN(x, a)          (((x) + ((a)-1)) & ~((a)-1))
// type SCE_KERNEL_MEMBLOCK_TYPE_USER_RW
void *vita_mem_alloc(unsigned int type, unsigned int size, unsigned int alignment, SceUID *uid);
void vita_mem_free(SceUID mem);

extern void* memblock;
void create_memspace();
void destroy_memspace();
void* malloc(SceSize size);
void* calloc(SceSize num, SceSize size);
void* realloc(void* oldMemPtr, SceSize size);
void free(void* memPtr);
char* realpath(const char *restrict file_name, char *restrict resolved_name);
int *__errno (void);
#endif