#include <psp2/kernel/clib.h>
#include <psp2/kernel/modulemgr.h>
#include <psp2/io/fcntl.h>
#include <psp2/io/stat.h>
#include <psp2/registrymgr.h>
#include <psp2/system_param.h>
#include <psp2/kernel/rng.h> 
#include <psp2/power.h>
#include <psp2/ctrl.h>
#include <string.h>
#include <taihen.h>
#include <stdbool.h>
#include <stdlib.h>


const int ZEROM_VERSION = 11;

static tai_hook_ref_t player_tick_ref;
SceUID player_tick_hook;
bool done = false;
SceCtrlData ctrlData;

uint32_t swap(uint32_t in)
{
  return __builtin_bswap32(in);
}

void print_bytes(const unsigned char *data, size_t size) {
	sceClibPrintf("\n\n");
	sceClibPrintf("Offset   00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
	sceClibPrintf("\n");
    for (size_t i = 0; i < size; i+=16) {
        sceClibPrintf("%04X  |  %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X \n", i,
						data[i], data[i+1], data[i+2], data[i+3], data[i+4], data[i+5], data[i+6], data[i+7],
						data[i+8], data[i+9], data[i+10], data[i+11], data[i+12], data[i+13], data[i+14], data[i+15]);
    }
	sceClibPrintf("\n\n");
}



void Player_Tick_patched(int *param_1) {
	TAI_CONTINUE(int, player_tick_ref, param_1);
	
	sceCtrlPeekBufferPositive(0, &ctrlData, 1);
	
	if(ctrlData.buttons & SCE_CTRL_CIRCLE){
		if(ctrlData.buttons & SCE_CTRL_UP){
			done = true;
			print_bytes(param_1,0x150);
			sceClibPrintf("0: %08X\n", swap(param_1[0x52]));
		
		
			sceClibPrintf("A: %.2f|%.2f|%.2f\n", *(float*)&param_1[0x52], *(float*)&param_1[0x53], *(float*)&param_1[0x54]);
			sceClibPrintf("B: %.2f|%.2f|%.2f\n", *(float*)&param_1[0x100], *(float*)&param_1[0x101], *(float*)&param_1[0x102]);
		}
		
		
		if(ctrlData.buttons & SCE_CTRL_DOWN){
			//int num = 0;
			//sceKernelGetRandomNumber(&num, 4);
			//float angle = num % 180;
			float angle = 180.0;
			float angle2 = -15.0;
			param_1[0x52]  = *(int*)&angle; // first person viewangle
			param_1[0x53]  = *(int*)&angle2; // first person viewangle
		}
		
		
		
	}
	
	//sceClibPrintf("B:%.2f|%.2f|%.2f\r\n", *(float*)&param_1[0x100], *(float*)&param_1[0x101], *(float*)&param_1[0x102]);
}


void _start() __attribute__((weak, alias("module_start")));
int module_start(SceSize argc, const void *args) {
	sceClibPrintf("Starting ZeroM! v: %d\n", ZEROM_VERSION);
	done = false;
	
	tai_module_info_t info;
	info.size = sizeof(tai_module_info_t);
	taiGetModuleInfo(TAI_MAIN_MODULE, &info);
	
	sceClibPrintf("Hooking\n");
	player_tick_hook = taiHookFunctionOffset(&player_tick_ref, info.modid, 0, 0x32FE14, 1, Player_Tick_patched);
	
	sceClibPrintf("Hooked\n");
	return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args) 
{
	sceClibPrintf("Stopping ZeroM!\n");
	if (player_tick_hook >= 0) taiHookRelease(player_tick_hook, player_tick_ref);
	return SCE_KERNEL_STOP_SUCCESS;
}
