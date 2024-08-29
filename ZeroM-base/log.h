#ifndef LOG_H
#define LOG_H
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <psp2/kernel/clib.h> 
#include <vitasdk.h>

#define MODULE_STRING "ZeroM"
#define LOG_BUFFER_SIZE 1024

typedef enum{
    INFO,
    DEBUG,
    ERROR,
    CRITICAL
} LogLevel_t;


void logger(const char* logString, LogLevel_t logLevel, ...);

void logInfo(const char* logString, ...);

void logRaw(const char* logString, ...);


void print_bytes(const unsigned char* data, size_t size);


#endif