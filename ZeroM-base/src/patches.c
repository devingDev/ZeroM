#include "patches.h"


void custom_function(){
/*     asm volatile (
        "MOV R0, %[func]\n"  // Load the function pointer into R0
        "BX R0\n"            // Branch to the address in R0
        :
        : [func] "r" (func_ptr)
        : "r0"
    ); */
}
void (*func_ptr)() = custom_function;  // Function pointer to your target function


unsigned char thumb_code[] = {
    0x40, 0xF2, 0x00, 0x00,   // MOVW R0, #0x5678
    0xC0, 0xF2, 0x00, 0x00,   // MOVT R0, #0x1234
    0x70, 0x47                // BX LR
}; //10

void extract_digits(int hex_value) {
    char hex_str[20];  // Buffer to hold the hexadecimal string representation
    //char trimmed_str[20]; // Buffer to hold the trimmed string
    int i = 0;

    // Convert the integer to a hexadecimal string
    sceClibSnprintf(hex_str, sizeof(hex_str), "%X", hex_value);  // %X for uppercase hex

/*     // Trim trailing zeros from the hexadecimal string
    for (i = sceClibStrnlen(hex_str,16) - 1; i >= 0; i--) {
        if (hex_str[i] != '0') {
            break;
        }
    } */
    hex_str[i + 1] = '\0';  // Null-terminate the trimmed string

    // Print each digit from the trimmed string
    sceClibPrintf("Digits in the hexadecimal number:\n");

// 0x504BE4AE
// MOVW            R0, #0xE4AE    4EF2AE40
// MOVT            R0, #0x504B    C5F24B00

//                        4567
// MOVW            R0, #0xE4AE    4EF2AE40
    int num = -1;
    unsigned char shifted = -1;
    int hexI = 4;

    // MOVW
    hexI = 4;
    if(isdigit(hex_str[hexI])){
        num = hex_str[hexI] - '0';
    }else{
        num = hex_str[hexI] - 'A' + 10;
    }
    thumb_code[0] += num;

    hexI = 5;
    if(isdigit(hex_str[hexI])){
        num = hex_str[hexI] - '0';
    }else{
        num = hex_str[hexI] - 'A' + 10;
    }
    if(num <= 7){
        shifted = num << 4;
        thumb_code[3] += shifted;
    }else{
        thumb_code[1] += 0x4;
        num -= 8;
        shifted = num << 4;
        thumb_code[3] += shifted;
    }

    hexI = 6;
    if(isdigit(hex_str[hexI])){
        num = hex_str[hexI] - '0';
    }else{
        num = hex_str[hexI] - 'A' + 10;
    }
    shifted = num << 4;
    thumb_code[2] += num;

    hexI = 7;
    if(isdigit(hex_str[hexI])){
        num = hex_str[hexI] - '0';
    }else{
        num = hex_str[hexI] - 'A' + 10;
    }
    thumb_code[2] += num;

    // MOVT
    hexI = 0;
    if(isdigit(hex_str[hexI])){
        num = hex_str[hexI] - '0';
    }else{
        num = hex_str[hexI] - 'A' + 10;
    }
    thumb_code[0+4] += num;

    hexI = 1;
    if(isdigit(hex_str[hexI])){
        num = hex_str[hexI] - '0';
    }else{
        num = hex_str[hexI] - 'A' + 10;
    }
    if(num <= 7){
        shifted = num << 4;
        thumb_code[3+4] += shifted;
    }else{
        thumb_code[1+4] += 0x4;
        num -= 8;
        shifted = num << 4;
        thumb_code[3+4] += shifted;
    }

    hexI = 2;
    if(isdigit(hex_str[hexI])){
        num = hex_str[hexI] - '0';
    }else{
        num = hex_str[hexI] - 'A' + 10;
    }
    shifted = num << 4;
    thumb_code[2+4] += num;

    hexI = 3;
    if(isdigit(hex_str[hexI])){
        num = hex_str[hexI] - '0';
    }else{
        num = hex_str[hexI] - 'A' + 10;
    }
    thumb_code[2+4] += num;



    sceClibPrintf("%02X %02X %02X %02X\n%02X %02X %02X %02X\n%02X %02X\n", thumb_code[0], thumb_code[1], thumb_code[2], thumb_code[3]
    , thumb_code[4], thumb_code[5], thumb_code[6], thumb_code[7]
    , thumb_code[8], thumb_code[9]);
}


void doPatches(){
/* 		int value = 0x3b;
		taiInjectData(info.modid, 0, 0x248840, &value, 2);

		// change extension from jpg to png
		const char *path = "ur0:temp/screenshot/capture.png";
		taiInjectData(info.modid, 0, 0x5148b8, path, strlen(path) + 1); */


        uintptr_t function_address = (uintptr_t)(void *)custom_function;

        sceClibPrintf("custom_function address: %08X ", function_address);

        extract_digits(function_address);


        // Convert the address to little-endian
        /*thumb_code[2] = ((uintptr_t)function_address >> 0)  & 0xFF;
        addr_bytes[3] = ((uintptr_t)function_address >> 8)  & 0xFF;
        addr_bytes[6] = ((uintptr_t)function_address >> 16) & 0xFF;
        addr_bytes[7] = ((uintptr_t)function_address >> 24) & 0xFF; */

        //taiInjectData(info.modid, 0, 0x0C68D0, &thumb_code, 10);
        //0x810C68D0  4E F2 F8 31 C8 F2 C8 11

}



