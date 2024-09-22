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

const int ZEROM_VERSION = 14;



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
				logInfo("%llu", GetTick());
				//print_bytes(playerAdd,0x40);

				logInfo("player: %08X", (int)(int*)player);
				logInfo("playerAdd: %08X", (int)playerAdd);

				logInfo("angle1: %.4f", player->angle1);
				logInfo("angle2: %.4f", player->angle2	);
				logInfo("angle3: %.4f", player->angle3	);
				logInfo("angle4: %.4f", player->angle4	);
				logInfo("angle5: %.4f", player->angle5	);
				logInfo("angle6: %.4f", player->angle6	);
				logInfo("angleA: %.4f", player->angleA	);
				logInfo("angleB: %.4f", player->angleB	);

				logInfo("posx1: %.2f", player->posx1);
				logInfo("posy1: %.2f", player->posy1);
				logInfo("posz1: %.2f", player->posz1);

				logInfo("posx2: %.2f", player->posx2);
				logInfo("posy2: %.2f", player->posy2);
				logInfo("posz2: %.2f", player->posz2);

				logInfo("posx3: %.2f", player->posx3);
				logInfo("posy3: %.2f", player->posy3);
				logInfo("posz3: %.2f", player->posz3);

				logInfo("0: %08X", swap(playerAdd[0x52]));
			
			
				logInfo("A: %.2f|%.2f|%.2f", *(float*)&playerAdd[0x52], *(float*)&playerAdd[0x53], *(float*)&playerAdd[0x54]);
				logInfo("B: %.2f|%.2f|%.2f", *(float*)&playerAdd[0x100], *(float*)&playerAdd[0x101], *(float*)&playerAdd[0x102]);
				sceKernelDelayThread(500*1000);
			}

			if(ctrlData.buttons & SCE_CTRL_RIGHT){
				logInfo("\n\n=====[DUMP BEGIN]=====");
				print_bytes((void*)player, 0xA90);
				logInfo("\n=====[DUMP END]=====\n\n");

			}
			
					
			
			if(ctrlData.buttons & SCE_CTRL_DOWN){
				//int num = 0;
				//sceKernelGetRandomNumber(&num, 4);
				//float angle = num % 180;
				float angle = 180.0;
				float angle2 = -15.0;
				//playerAdd[0x52]  = *(int*)&angle; // first person viewangle
				//playerAdd[0x53]  = *(int*)&angle2; // first person viewangle

				// kinda broken :(
				playerCaught->angle1 = angle;
				playerCaught->angle2 = angle2;
				double pos = 150.0;
				playerCaught->posy1 = pos;
				playerCaught->posz1 = pos;
				playerCaught->posy2 = pos;
				playerCaught->posz2 = pos;
				playerCaught->posy3 = pos;
				playerCaught->posz3 = pos;
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
	
	sceKernelDelayThread(1000);
	prepareHooking();
	
	thid = sceKernelCreateThread("ZeroM_thread", ZeroM_thread, 0x40, 0x10000, 0, 0, NULL);
	sceKernelStartThread(thid, 0, NULL);
	

	setupHooks();
	logInfo("Hooked\n");

	doPatches();
	logInfo("Patched\n");
	
	
	return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args) 
{
	logInfo("Stopping ZeroM!");
	
	unhook();

	run = 0;
	sceKernelWaitThreadEnd(thid, NULL, NULL);
		
	return SCE_KERNEL_STOP_SUCCESS;
}
