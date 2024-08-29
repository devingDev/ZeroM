#include "log.h"

void print_bytes(const unsigned char *data, size_t size){
	sceClibPrintf("\n\n");
	sceClibPrintf("Offset   00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
	sceClibPrintf("\n");
    for (size_t i = 0; i < size; i+=16) {
        //sceClibPrintf("%04X  |  %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X \n", i,
		//				data[i], data[i+1], data[i+2], data[i+3], data[i+4], data[i+5], data[i+6], data[i+7],
		//				data[i+8], data[i+9], data[i+10], data[i+11], data[i+12], data[i+13], data[i+14], data[i+15]);
        sceClibPrintf("%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X \n",
						data[i], data[i+1], data[i+2], data[i+3], data[i+4], data[i+5], data[i+6], data[i+7],
						data[i+8], data[i+9], data[i+10], data[i+11], data[i+12], data[i+13], data[i+14], data[i+15]);
    }
	sceClibPrintf("\n\n");
}

