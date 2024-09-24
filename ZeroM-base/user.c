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
#include "log.h"
#include "hooks.h"
#include "patches.h"

const int ZEROM_VERSION = 15;



int run = 1;
SceUID thid = -1;
SceCtrlData ctrlData;
int ZeroM_thread(unsigned int args, void* argp){
	logInfo("ZeroM_thread started");
	while (run == 1)
	{
		sceCtrlPeekBufferPositive(0, &ctrlData, 1);
		if(ctrlData.buttons & SCE_CTRL_CIRCLE){
			if(ctrlData.buttons & SCE_CTRL_UP){
				logPlayerInfo(player, playerAdd);
				
				sceKernelDelayThread(500*1000);
			}

			if(ctrlData.buttons & SCE_CTRL_RIGHT){
				logInfo("\n\n=====[DUMP BEGIN]=====");
				print_bytes((void*)player, 0xA90);
				logInfo("\n=====[DUMP END]=====\n\n");

			}

			if(ctrlData.buttons & SCE_CTRL_LEFT){
				/*if(activeMenu == 0){
					activeMenu = 1;
				}
				if(activeMenu == 1){
					activeMenu = 0;
				}*/
				sceKernelDelayThread(550);

			}
			
					
			
			if(ctrlData.buttons & SCE_CTRL_DOWN){
				//int num = 0;
				//sceKernelGetRandomNumber(&num, 4);
				//float angle = num % 180;
				float angle = 180.0;
				float angle2 = -15.0;
				//playerAdd[0x52]  = *(int*)&angle; // first person viewangle
				//playerAdd[0x53]  = *(int*)&angle2; // first person viewangle

				// kinda broken? :(
				playerCaught->angle1 = angle;
				playerCaught->angle2 = angle2;
			}
		
		}
		
		sceKernelDelayThread(50);
	}
	return 0;
}


void _start() __attribute__((weak, alias("module_start")));
int module_start(SceSize argc, const void *args) {
	logInfo("\n\n\n\n\n\n");
	logInfo("Starting ZeroM! v: %lu", ZEROM_VERSION);
	
	const char src[0x10] = "test 12345";
   	char dest[0x10];
	memcpy(dest, src, strlen(src) + 1);
	logInfo("memcpy : %s\n", dest);

	sceKernelDelayThread(1000);
	prepareHooking();
	
	thid = sceKernelCreateThread("ZeroM_thread", ZeroM_thread, 0x40, 0x10000, 0, 0, NULL);
	sceKernelStartThread(thid, 0, NULL);


	setupHooks();
	logInfo("Hooked\n");

	doPatches();
	logInfo("Patched\n");
	
	menu_draw_hook();

	
	return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args) 
{
	logInfo("Stopping ZeroM!");
	
	unhook();
	menu_draw_release_hook();
	run = 0;
	sceKernelWaitThreadEnd(thid, NULL, NULL);
	
	return SCE_KERNEL_STOP_SUCCESS;
}
