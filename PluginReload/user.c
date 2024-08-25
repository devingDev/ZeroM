#include <psp2/kernel/clib.h>
#include <psp2common/kernel/modulemgr.h> 
#include <psp2/kernel/threadmgr/thread.h> 
#include <psp2/kernel/modulemgr.h>
#include <psp2/io/dirent.h> 
#include <psp2/io/fcntl.h>
#include <psp2/io/stat.h>
#include <psp2/registrymgr.h>
#include <psp2/system_param.h>
#include <psp2/power.h>
#include <psp2/ctrl.h>
#include <string.h>
#include <taihen.h>
#include <stdbool.h>

const int PLUGINLOADER_VERSION = 3;

void load_ZeroM();
void unload_ZeroM();

SceUID thid = -1;
int PluginLoader_thread(unsigned int args, void* argp)
{
	sceClibPrintf("PluginLoader_thread started \n");
	load_ZeroM();
	
	
	SceCtrlData ctrlData;
	sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG_WIDE);
	sceCtrlPeekBufferPositive(0, &ctrlData, 1);
	
	while (1)
	{
		sceCtrlPeekBufferPositive(0, &ctrlData, 1);
		if(ctrlData.buttons & SCE_CTRL_RTRIGGER){
			if(ctrlData.buttons & SCE_CTRL_LTRIGGER ){
				unload_ZeroM();
				sceKernelDelayThread(100*1000); // 1000*1000 = 1 second
				load_ZeroM();
				sceKernelDelayThread(3*500*1000);
			}
		}
		sceKernelDelayThread(12*1000);
	}
	return 0;
}

SceUID zeroMModuleId = -1;
void load_ZeroM(){
	sceClibPrintf("Loading ZeroM \n");
	int status;
	zeroMModuleId = sceKernelLoadStartModule("ur0:/tai/ZeroM.suprx", 0, 0, 0, NULL, &status); 
	sceClibPrintf("Loaded module response: %08x STATUS %08x \n", zeroMModuleId, status);
}

void unload_ZeroM(){
	sceClibPrintf("Unloading ZeroM \n");
	int status;
	int ret = sceKernelStopUnloadModule(zeroMModuleId, 0, 0, 0, NULL, &status); 
	sceClibPrintf("Unloaded module response: %08x STATUS %08x \n", ret, status);
}

void list_files(const char *path) {
    SceUID dir = sceIoDopen(path);
    if (dir < 0) {
        sceClibPrintf("Failed to open directory: %08x\n", dir);
        return;
    }

    SceIoDirent entry;
    while (sceIoDread(dir, &entry) > 0) {
        sceClibPrintf("%s\n", entry.d_name);
    }

    sceIoDclose(dir);
}

void _start() __attribute__((weak, alias("module_start")));
int module_start(SceSize argc, const void *args) {
	sceClibPrintf("PluginLoader says hello! V: %d\n", PLUGINLOADER_VERSION);
	
	sceClibPrintf("Creating and starting PluginLoader thread\n");
	thid = sceKernelCreateThread("PluginLoader_thread", PluginLoader_thread, 0x40, 0x10000, 0, 0, NULL);
	sceKernelStartThread(thid, 0, NULL);
	
	
	return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args) 
{
	sceClibPrintf("Stopping PluginLoader!\n");
	sceKernelWaitThreadEnd(thid, NULL, NULL);
	return SCE_KERNEL_STOP_SUCCESS;
}
