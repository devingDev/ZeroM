#include "mem.h"
void *vita_mem_alloc(unsigned int type, unsigned int size, unsigned int alignment, SceUID *uid)
{
    void *mem;

    if (type == SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW) {
        size = ALIGN(size, 256 * 1024);
    } else {
        size = ALIGN(size, 4 * 1024);
    }

    *uid = sceKernelAllocMemBlock("zerom_mem", type, size, NULL);

    if (*uid < 0) {
        return NULL;
    }

    if (sceKernelGetMemBlockBase(*uid, &mem) < 0) {
        return NULL;
    }


    return mem;
}


const uint32_t DEFAULT_SIZE = 2 * 1024 * 1024;
void* memblock;
SceClibMspace mspace;
void create_memspace(){
    SceUID memId;
    memblock = vita_mem_alloc(SCE_KERNEL_MEMBLOCK_TYPE_USER_RW, DEFAULT_SIZE, sizeof(void *), &memId);
    mspace = sceClibMspaceCreate(memblock, DEFAULT_SIZE);
}
void destroy_memspace(){
    sceClibMspaceDestroy(mspace);
}

void* malloc(SceSize size){
    return sceClibMspaceMalloc(mspace, size);
}
void* calloc(SceSize num, SceSize size){
    return sceClibMspaceCalloc(mspace, num, size);
}
void* realloc(void* oldMemPtr, SceSize size){
    return sceClibMspaceRealloc(mspace, oldMemPtr, size);
}
void free(void* memPtr){
    sceClibMspaceFree(mspace, memPtr);
}
char* realpath(const char *restrict file_name, char *restrict resolved_name){
    SceSize strlength = sceClibStrnlen(file_name, 512);
    sceClibStrncpy(resolved_name, file_name, strlength);
    resolved_name[strlength] = '\0';
    return resolved_name;
}
int *__errno (void){
    return 0;
}
