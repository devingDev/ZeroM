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

const int ZEROM_VERSION = 12;



void (* EntityTick1)(int *param1) = NULL;
int run = 1;
SceUID thid = -1;
SceCtrlData ctrlData;
int ZeroM_thread(unsigned int args, void* argp){
	sceClibPrintf("ZeroM_thread started\n");
	while (run == 1)
	{
		sceCtrlPeekBufferPositive(0, &ctrlData, 1);
		if(ctrlData.buttons & SCE_CTRL_CIRCLE){
			if(ctrlData.buttons & SCE_CTRL_UP){
				sceClibPrintf("%llu\n", GetTick());
				//print_bytes(playerAdd,0x40);

				sceClibPrintf("player: %08X\n", (int)(int*)player);
				sceClibPrintf("playerAdd: %08X\n", (int)playerAdd);

				sceClibPrintf("angle1: %.4f\n", player->angle1);
				sceClibPrintf("angle2: %.4f\n", player->angle2	);
				sceClibPrintf("angle3: %.4f\n", player->angle3	);
				sceClibPrintf("angle4: %.4f\n", player->angle4	);
				sceClibPrintf("angle5: %.4f\n", player->angle5	);
				sceClibPrintf("angle6: %.4f\n", player->angle6	);
				sceClibPrintf("angleA: %.4f\n", player->angleA	);
				sceClibPrintf("angleB: %.4f\n", player->angleB	);

				sceClibPrintf("posx1: %.2f\n", player->posx1);
				sceClibPrintf("posy1: %.2f\n", player->posy1);
				sceClibPrintf("posz1: %.2f\n", player->posz1);

				sceClibPrintf("posx2: %.2f\n", player->posx2);
				sceClibPrintf("posy2: %.2f\n", player->posy2);
				sceClibPrintf("posz2: %.2f\n", player->posz2);

				sceClibPrintf("posx3: %.2f\n", player->posx3);
				sceClibPrintf("posy3: %.2f\n", player->posy3);
				sceClibPrintf("posz3: %.2f\n", player->posz3);

				sceClibPrintf("0: %08X\n", swap(playerAdd[0x52]));
			
			
				sceClibPrintf("A: %.2f|%.2f|%.2f\n", *(float*)&playerAdd[0x52], *(float*)&playerAdd[0x53], *(float*)&playerAdd[0x54]);
				sceClibPrintf("B: %.2f|%.2f|%.2f\n", *(float*)&playerAdd[0x100], *(float*)&playerAdd[0x101], *(float*)&playerAdd[0x102]);
				sceKernelDelayThread(500*1000);
			}

			if(ctrlData.buttons & SCE_CTRL_RIGHT){
				sceClibPrintf("\n\n=====[DUMP BEGIN]=====\n");
				print_bytes((void*)player, 0xA90);
				sceClibPrintf("\n=====[DUMP END]=====\n");

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
	sceClibPrintf("Starting ZeroM! v: %d\n", ZEROM_VERSION);
	
	tai_module_info_t info;
	info.size = sizeof(tai_module_info_t);
	taiGetModuleInfo(TAI_MAIN_MODULE, &info);
	sceClibPrintf("module_nid : %08X\n", info.module_nid);
	sceClibPrintf("modid : %08X\n", info.modid);
	
	SceUID currentPID = sceKernelGetProcessId();
	sceClibPrintf("Process ID : %d\n", currentPID);
	//sceKernelGetModuleInfo(uid, &info)
	int ret = module_get_offset(info.modid, 0, 0x16f00e, &EntityTick1);
	if(ret < 0){
		sceClibPrintf("ERROR getting function ERRORCODE: %d\n", ret);
	}else{
		sceClibPrintf("module_get_offset: %08X    %d\n", (int)EntityTick1, ret);
	}
	//int ret = module_get_offset(currentPID, info.modid, 0, 0x16f00e, &EntityTick1);
	
	thid = sceKernelCreateThread("ZeroM_thread", ZeroM_thread, 0x40, 0x10000, 0, 0, NULL);
	sceKernelStartThread(thid, 0, NULL);
	
	sceClibPrintf("Hooking\n");

	hooks[0] = taiHookFunctionOffset(&hook_refs[0], info.modid, 0, 0x32FE14, 1, Player_Tick_patched);
	hooks[1] = taiHookFunctionOffset(&hook_refs[1], info.modid, 0, 0x289684, 1, Livingent_Tick_patched);
	hooks[19] = taiHookFunctionOffset(&hook_refs[2], info.modid, 0, 0x83458C, 1, CreateServerPlayer_patched);
	sceClibPrintf("Hooked\n");
	
	
	return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args) 
{
	sceClibPrintf("Stopping ZeroM!\n");
	
	for (int i = 0; i < TOTAL_HOOKS; i++){
		if (hooks[i] >= 0) taiHookRelease(hooks[i], hook_refs[i]);
	}
	run = 0;
	sceKernelWaitThreadEnd(thid, NULL, NULL);
		
	return SCE_KERNEL_STOP_SUCCESS;
}
