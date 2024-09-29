#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H
#include <psp2/kernel/threadmgr.h> 

inline uint64_t GetTick(){ return sceKernelGetSystemTimeWide(); }
inline uint32_t swap(uint32_t in){ return __builtin_bswap32(in); }

#endif