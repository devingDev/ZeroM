#include <psp2/kernel/clib.h>
#include <psp2common/kernel/modulemgr.h> 
#include <psp2/kernel/threadmgr/thread.h> 
#include <psp2/kernel/modulemgr.h>
#include <psp2/io/dirent.h> 
#include <psp2/io/fcntl.h>
#include <psp2/io/stat.h>
#include <psp2/registrymgr.h>
#include <psp2/system_param.h>
#include <psp2/kernel/sysmem.h> 
#include <psp2/power.h>
#include <psp2/ctrl.h>
#include <string.h>
#include <taihen.h>
#include <stdbool.h>

const uint32_t PLUGINLOADER_VERSION = 12;
uint32_t GetPluginLoaderVersion(){ return PLUGINLOADER_VERSION; }


bool isZeroMRunning = false;

void load_ZeroM();
void unload_ZeroM();
void dump_ram();

int run = 1;
SceUID thid = -1;
int PluginLoader_thread(unsigned int args, void* argp)
{
	sceClibPrintf("PluginLoader_thread started\n");
	load_ZeroM();
	
	
	SceCtrlData ctrlData;
	sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG_WIDE);
	sceCtrlPeekBufferPositive(0, &ctrlData, 1);
	
	while (run == 1)
	{
		sceCtrlPeekBufferPositive(0, &ctrlData, 1);
		if(ctrlData.buttons & SCE_CTRL_RTRIGGER && ctrlData.buttons & SCE_CTRL_LTRIGGER){
			if(ctrlData.buttons & SCE_CTRL_CIRCLE){
				unload_ZeroM();
				sceKernelDelayThread(1000*1000); // 1000*1000 = 1 second
				load_ZeroM();
				sceKernelDelayThread(3*500*1000);
			}
			if(ctrlData.buttons & SCE_CTRL_TRIANGLE){
				unload_ZeroM();
				sceKernelDelayThread(3*500*1000);
			}if(ctrlData.buttons & SCE_CTRL_SQUARE){
				load_ZeroM();
				sceKernelDelayThread(3*500*1000);
			}
			if(ctrlData.buttons & SCE_CTRL_CROSS && ctrlData.buttons & SCE_CTRL_DOWN){
				dump_ram();
			}
		}
		sceKernelDelayThread(12*1000);
	}
	return 0;
}

SceUID zeroMModuleId = -1;
void load_ZeroM(){
	sceClibPrintf("Loading ZeroM \n");

	tai_module_info_t prinfo;
	prinfo.size = sizeof(tai_module_info_t);
	int res = taiGetModuleInfo("ZeroM", &prinfo);
	isZeroMRunning = res == 0;
	if(isZeroMRunning){
		sceClibPrintf("ZeroM is already running! %08X" , res);
		zeroMModuleId = prinfo.modid;
	}else{
		sceClibPrintf("ZeroM not loaded yet, starting! %08X" , res);
		int status;
		zeroMModuleId = sceKernelLoadStartModule("ur0:/tai/ZeroM.suprx", 0, 0, 0, NULL, &status); 
		sceClibPrintf("Loaded module response: %08x STATUS %08x \n", zeroMModuleId, status);
	}

}

void unload_ZeroM(){
	sceClibPrintf("Unloading ZeroM \n");
	int status;
	int ret = sceKernelStopUnloadModule(zeroMModuleId, 0, 0, 0, NULL, &status); 
	sceClibPrintf("Unloaded module response: %08x STATUS %08x \n", ret, status);
}

#define BUFFER_SIZE 4096
void dump_ram(){

	char filename[256];
	sceClibSnprintf(filename, sizeof(filename), "ux0:/data/ramdump_%llu.bin", sceKernelGetSystemTimeWide());
    int fd = sceIoOpen(filename, SCE_O_WRONLY | SCE_O_CREAT | SCE_O_TRUNC, 0777);
	if (fd < 0) {
        sceClibPrintf("ERROR OPENING FILE TO WRITE: %s\n", filename);
        return;
    }
	sceClibPrintf("DUMPING RAM TO : %s\n", filename);
	SceKernelMemBlockInfo info;
	info.size = sizeof(SceKernelMemBlockInfo);
	int times = 0;
    uintptr_t lastMappedBase = 0;
    size_t lastMappedSize = 0;
	for(uintptr_t i=0x81000000;i<0x84000000;){	
		int ret = sceKernelGetMemBlockInfoByAddr(i, &info);
		if(ret != 0){
            sceClibPrintf("ret not 0 %d %08X   address: %08X , size: %08X\n", ret,ret, (uintptr_t)info.mappedBase, (size_t)info.mappedSize);
			i+=0x1000;
			continue;
		}

		if((uintptr_t)info.mappedBase == 0xFFFFFFFF || info.mappedSize == 0xFFFFFFFF){
			i+=0x1000;
			continue;
		}
		if (info.mappedBase == lastMappedBase && info.mappedSize == lastMappedSize) {
            sceClibPrintf("Skipping duplicated block at address: %08X, size: %08X\n", (uintptr_t)info.mappedBase, (size_t)info.mappedSize);
            i += 0x1000;
            continue;
        }


		size_t totalWritten = 0;
		void* mapBase = ((void*)info.mappedBase);
		size_t size = info.mappedSize;

		while(totalWritten < size){
			size_t to_write = (size - totalWritten > BUFFER_SIZE) ? BUFFER_SIZE : (size - totalWritten);
			int written = sceIoWrite(fd, mapBase + totalWritten, to_write);
			if (written < 0) {
				sceClibPrintf("Failed to write to file %08X %08X\n" , i, written);
				break;
			}
        	totalWritten += written;
		}

        lastMappedBase = (uintptr_t)info.mappedBase;
        lastMappedSize = info.mappedSize;
		
		//i+=info.mappedSize;
		i+=0x1000;
		times++;
	}
	sceIoClose(fd);
	sceClibPrintf("DUMP RAM COMPLETE!  %s   %d\n", filename, times );
}

void dump_ramX()
{
	char filename[256];
	sceClibSnprintf(filename, sizeof(filename), "ux0:/data/ramdump_%llu.bin", sceKernelGetSystemTimeWide());
    int fd = sceIoOpen(filename, SCE_O_WRONLY | SCE_O_CREAT | SCE_O_TRUNC, 0777);
	if (fd < 0) {
        sceClibPrintf("ERROR OPENING FILE TO WRITE: %s\n", filename);
        return;
    }
	sceClibPrintf("DUMPING RAM TO : %s\n", filename);

	uint32_t addr = 0x80000000U;
    while (addr < 0xA0000000U) {
        SceUID heap_memblock = sceKernelFindMemBlockByAddr((const void*)addr, 0);
        if (heap_memblock >= 0) {
            void* heap_addr;
            int ret = sceKernelGetMemBlockBase(heap_memblock, &heap_addr);
            if (ret >= 0) {
                SceKernelMemBlockInfo heap_info;
                heap_info.size = sizeof(SceKernelMemBlockInfo);
                ret = sceKernelGetMemBlockInfoByAddr(heap_addr, &heap_info);
                if (ret == 0) {
                    addr = (uint32_t)heap_info.mappedBase + heap_info.mappedSize;
                    if ((heap_info.type == SCE_KERNEL_MEMBLOCK_TYPE_USER_RW || heap_info.type == SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE) && (heap_info.access & 4) == 4) {
                        void *base = heap_info.mappedBase;
                        uint32_t size = heap_info.mappedSize;
                        //sceClibSnprintf(infostr, 256, "Heap %X (%s): %08X.bin, offset 0x%08X, size %04X\r\n", heap_memblock, heap_info.type == SCE_KERNEL_MEMBLOCK_TYPE_USER_RW ? "SCE_KERNEL_MEMBLOCK_TYPE_USER_RW" : "SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE", base, base, size);
                        //sceIoWrite(fdlist, infostr, sceClibStrnlen(infostr, 256));
                        //sceClibSnprintf(filename, 128, "%s/%08X.bin", path, base);
                        //int f = sceIoOpen(filename, SCE_O_WRONLY | SCE_O_CREAT | SCE_O_TRUNC, 0644);
                        sceIoWrite(fd, base, size);
                    }
                    continue;
                }
            }
        }
        addr += 0x4000;
    }
    sceIoClose(fd);
	sceClibPrintf("DUMP RAM COMPLETE!  %s \n", filename );
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
	run = 0;
	sceKernelWaitThreadEnd(thid, NULL, NULL);
	return SCE_KERNEL_STOP_SUCCESS;
}
