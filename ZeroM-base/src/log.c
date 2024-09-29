#include "log.h"

void logger(const char* logString, LogLevel_t logLevel, ...){
    char buffer[LOG_BUFFER_SIZE];

    const char* levelString = NULL;
    switch(logLevel) {
        case INFO:     levelString = "[INFO]"; break;
        case DEBUG:    levelString = "[DEBUG]"; break;
        case ERROR:    levelString = "[ERROR]"; break;
        case CRITICAL: levelString = "[CRITICAL]"; break;
        default:       levelString = "[DEFAULT]";
    }

    int offset = sceClibSnprintf(buffer, LOG_BUFFER_SIZE, "%s %s ", MODULE_STRING, levelString);

    va_list args;
    va_start(args, logLevel);
    sceClibVsnprintf(buffer + offset, LOG_BUFFER_SIZE - offset, logString, args);
    va_end(args);

    sceClibPrintf("%s\n", buffer);
}

void logInfoA(const char* logString, ...){
    va_list args;
    va_start(args, logString);
    logger(logString, INFO, args);
    va_end(args);
}

void logRaw(const char* logString, ...){
    va_list args;
    va_start(args, logString);
    sceClibVprintf(logString, args);
    va_end(args);
}


void print_bytes(const unsigned char *data, size_t size){
	logInfo("Offset   00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
    for (size_t i = 0; i < size; i+=16) {
        logInfo("%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X \n",
						data[i], data[i+1], data[i+2], data[i+3], data[i+4], data[i+5], data[i+6], data[i+7],
						data[i+8], data[i+9], data[i+10], data[i+11], data[i+12], data[i+13], data[i+14], data[i+15]);
    }
}

void hex_dump(const char *name, int *addr, int length) {
	if(addr < 0x81000000 || addr > 0x85FFFFFF)
    {
        return;
    }
    int BUFFER_SIZE = LOG_BUFFER_SIZE * (1+(length/0x50));
    char buffer[BUFFER_SIZE];
    char *ptr = buffer;
    ptr += sceClibSnprintf(ptr, BUFFER_SIZE - (ptr - buffer), "%s:\n", name);
    for (int i = 0; i < length; i++) {
        ptr += sceClibSnprintf(ptr, BUFFER_SIZE - (ptr - buffer), "%08X ", addr[i]);
    }
    sceClibSnprintf(ptr, BUFFER_SIZE - (ptr - buffer), "\n\n");
    sceClibPrintf("%s", buffer);
}



size_t wcslen_custom(const wchar_t* wstr) {
    const wchar_t* s = wstr;
    while (*s && *(s+1)) s+=2;
    return s - wstr;
}

char* wchar_to_char(const wchar_t* wstrA) {
    static char str[256];  
    // todo add the code.
    
    return str;
}


