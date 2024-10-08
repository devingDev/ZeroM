#ifndef LOG_H
#define LOG_H
#include <string.h>
#include <stdbool.h>
#include <psp2/kernel/clib.h> 
#include <vitasdk.h>
#include "version.h"


#define LOG_BUFFER_SIZE 1024

#define logInfo(X,...) sceClibPrintf("ZeroM[INFO] "X"\n", ##__VA_ARGS__)

typedef enum{
    INFO,
    DEBUG,
    ERROR,
    CRITICAL
} LogLevel_t;


void logger(const char* logString, LogLevel_t logLevel, ...);

void logInfoA(const char* logString, ...);

void logRaw(const char* logString, ...);


void print_bytes(const unsigned char* data, size_t size);

void hex_dump(const char *name, int *addr, int length);

//size_t wcslen_custom(const wchar_t* wstr);
//char* wchar_to_char(const wchar_t* wstr);


#endif