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
#include <psp2/vshbridge.h> 
#include "log.h"
#include "hooks.h"
#include "patches.h"
#include "menu.h"
#include "navigation.h"
#include "structures/player.h"
#include "pluginreload.h"
#include "gamemod.h"
#include <dlfcn.h>


const uint32_t ZEROM_VERSION = 17;

bool pluginReloadLoaded = false;
int run = 1;
SceUID thid = -1;

uint32_t GetVersion(){ return ZEROM_VERSION; }

int ZeroM_thread(unsigned int args, void* argp){
	logInfo("ZeroM_thread started");
	while (run == 1)
	{
		//doNavigation(&menu);

		if(current_pad.buttons & SCE_CTRL_LTRIGGER){
			if(current_pad.buttons & SCE_CTRL_SELECT){
				activeMenu = !activeMenu;
				sceKernelDelayThread(500*1000);
			}
		}
		if(current_pad.buttons & SCE_CTRL_CIRCLE){
			if(current_pad.buttons & SCE_CTRL_UP){
				logPlayerInfo(player, playerAdd);
				
				sceKernelDelayThread(500*1000);
			}

			if(current_pad.buttons & SCE_CTRL_RIGHT){
				logInfo("\n\n=====[DUMP BEGIN]=====");
				print_bytes((void*)player, 0xA90);
				logInfo("\n=====[DUMP END]=====\n\n");

			}

			if(current_pad.buttons & SCE_CTRL_LEFT){
				/*if(activeMenu == 0){
					activeMenu = 1;
				}
				if(activeMenu == 1){
					activeMenu = 0;
				}*/
				sceKernelDelayThread(550);

			}
			
					
			
			if(current_pad.buttons & SCE_CTRL_DOWN){
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

void* gameModHandle;
GameMod* (*getGameMod)(void);
void testLoadGameMod(){
	logInfo("Trying to open lib\n");
	gameModHandle = dlopen("ux0:/zerom/gamemod.suprx",0);
	logInfo("loaded lib: 0x%08x\n", gameModHandle);
	if(gameModHandle == NULL){
		return;
	}
	getGameMod = dlsym(gameModHandle, "getGameMod");
	logInfo("got getGameMod function: 0x%08x\n", getGameMod);
	if(getGameMod == NULL){
		return;
	}
	getGameMod()->startFunction();
	logInfo("called start function: 0x%08x\n", getGameMod()->startFunction);
}
void testUnloadGameMod(){
  dlclose(gameModHandle);
}

void _start() __attribute__((weak, alias("module_start")));
int module_start(SceSize argc, const void *args) {
	logInfo("\n\n\n\n\n\n");
	logInfo("Starting ZeroM! v: %lu", ZEROM_VERSION);
	
	const char src[0x10] = "test 12345";
   	char dest[0x10];
	memcpy(dest, src, strlen(src) + 1);
	logInfo("memcpy : %s\n", dest);

	// search for pluginreload plugin
	tai_module_info_t prinfo;
	prinfo.size = sizeof(tai_module_info_t);
	int res = taiGetModuleInfo("PluginReload", &prinfo);
	pluginReloadLoaded = res == 0;
	if(pluginReloadLoaded){
		logInfo("PluginReload is running! %08X" , res);
		logInfo("PluginReload Version: %d" , GetPluginLoaderVersion());
	}else{
		logInfo("PluginReload not found! %08X" , res);
	}
	
	prepareHooking();
	
	thid = sceKernelCreateThread("ZeroM_thread", ZeroM_thread, 0x40, 0x10000, 0, 0, NULL);
	sceKernelStartThread(thid, 0, NULL);


	setupHooks();
	logInfo("Hooked\n");

	doPatches();
	logInfo("Patched\n");
	
	menu_draw_hooks();
	logInfo("Menu Draw hooked\n");
	sceKernelDelayThread(5000);
	navigation_hooks();
	logInfo("Navigation hooked\n");

	logInfo("testLoadGameMod start\n");
	testLoadGameMod();
	logInfo("testLoadGameMod end\n");
	
	return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args) 
{
	logInfo("Stopping ZeroM!");
	navigation_release_hooks();
	menu_draw_release_hooks();
	
	unhook();
	run = 0;
	sceKernelWaitThreadEnd(thid, NULL, NULL);
	testUnloadGameMod();
	return SCE_KERNEL_STOP_SUCCESS;
}
