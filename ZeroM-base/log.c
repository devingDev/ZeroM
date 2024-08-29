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

void logInfo(const char* logString, ...){
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
        //sceClibPrintf("%04X  |  %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X \n", i,
		//				data[i], data[i+1], data[i+2], data[i+3], data[i+4], data[i+5], data[i+6], data[i+7],
		//				data[i+8], data[i+9], data[i+10], data[i+11], data[i+12], data[i+13], data[i+14], data[i+15]);
        logRaw("%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X \n",
						data[i], data[i+1], data[i+2], data[i+3], data[i+4], data[i+5], data[i+6], data[i+7],
						data[i+8], data[i+9], data[i+10], data[i+11], data[i+12], data[i+13], data[i+14], data[i+15]);
    }
}

