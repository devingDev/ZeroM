#ifndef HASH_H
#define HASH_H
#include <stdint.h>

typedef struct SceSblDmac5HashTransformParam {
   void* src;
   void* dst;
   uint32_t size;
   uint32_t unk_C;
   uint32_t unk_10;
   void* iv;
} SceSblDmac5HashTransformParam;
int sceSblDmac5HashTransform(SceSblDmac5HashTransformParam *param, uint32_t command, uint32_t extra);	

#endif