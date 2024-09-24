#include "hooks.h"



tai_hook_ref_t hook_refs[TOTAL_HOOKS];
SceUID hooks[TOTAL_HOOKS];
int currentHooks = 0;
tai_module_info_t info;
SceKernelModuleInfo extrainfo;

void (* EntityTick1)(int *param1) = NULL;

tai_hook_ref_t* playerTickHookRef; 
tai_hook_ref_t* livingEntTickHookRef; 
tai_hook_ref_t* createServerPlayerHookRef; 


void prepareHooking(){
	info.size = sizeof(tai_module_info_t);
	taiGetModuleInfo(TAI_MAIN_MODULE, &info);
	logInfo("module_nid : %08X", info.module_nid);
	logInfo("modid : %08X", info.modid);
	logInfo("exports_start : %08X", info.exports_start);
	logInfo("exports_end : %08X", info.exports_end);
	logInfo("imports_start : %08X", info.imports_start);
	logInfo("imports_end : %08X", info.imports_end);

	extrainfo.size = sizeof(SceKernelModuleInfo);
	sceKernelGetModuleInfo(info.modid, &extrainfo);
	logInfo("segments[0] : %08X %08X", extrainfo.segments[0].vaddr, extrainfo.segments[0].memsz);

    SceUID currentPID = sceKernelGetProcessId();
	logInfo("Process ID : %08X", currentPID);
	//sceKernelGetModuleInfo(uid, &info)
	int ret = module_get_offset(info.modid, 0, 0x16f00e, &EntityTick1);
	if(ret < 0){
		logInfo("ERROR getting function ERRORCODE: %d", ret);
	}else{
		logInfo("module_get_offset: %08X    %d", (int)EntityTick1, ret);
	}
	//int ret = module_get_offset(currentPID, info.modid, 0, 0x16f00e, &EntityTick1);
}



void setupHooks(){
	logInfo("Hooking");

    playerTickHookRef =  add_taiHookFunctionOffset(0x32FE14, Player_Tick_patched);
    livingEntTickHookRef = add_taiHookFunctionOffset(0x289684, Livingent_Tick_patched);
    createServerPlayerHookRef = add_taiHookFunctionOffset(0x83458C, CreateServerPlayer_patched);

    doTestHooks();
}

void unhook(){
	logInfo("Removing hooks...");
	for (int i = 0; i < TOTAL_HOOKS; i++){
		if (hooks[i] >= 0) taiHookRelease(hooks[i], hook_refs[i]);
	}
}

tai_hook_ref_t* add_taiHookFunctionOffsetThumb(uint32_t offset, const void * hook_func, int thumb){
    int segidx = 0;
	hooks[currentHooks] = taiHookFunctionOffset(&hook_refs[currentHooks], info.modid, segidx, offset, thumb, hook_func);
    currentHooks++;
    return &hook_refs[currentHooks-1];
}

tai_hook_ref_t* add_taiHookFunctionOffset(uint32_t offset, const void * hook_func){
    int thumb = 1;
	return add_taiHookFunctionOffsetThumb(offset, hook_func, thumb);
}

int module_get_offset(int uid, int seg, uint32_t in_off, void *out_off) {
	SceKernelModuleInfo info;
	if ((sceKernelGetModuleInfo(uid, &info) < 0) || (in_off > info.segments[seg].memsz))
		return -1;
	*(uint32_t *)out_off = (uint32_t)(info.segments[seg].vaddr + in_off);
	return 0;
}

uint64_t GetTick(){ return sceKernelGetSystemTimeWide(); }
uint32_t swap(uint32_t in){ return __builtin_bswap32(in); }


int* playerAdd;
Player* player = NULL;
Player* playerCaught = NULL;

void Player_Tick_patched(Player *playerF) {
	TAI_NEXT(Player_Tick_patched, *playerTickHookRef, playerF);
}

void Livingent_Tick_patched(int *param_1) {
	TAI_NEXT(Livingent_Tick_patched, *livingEntTickHookRef, param_1);
}


int  CreateServerPlayer_patched(Player* playerAllocated, int a2, int *a3, int a4, int a5){
	player = playerAllocated;
	//logInfo("%llu CreateServerPlayer_patched start %p %p", GetTick(), (int)(int*)playerAllocated, &playerAllocated);
	int result = TAI_NEXT(CreateServerPlayer_patched, *createServerPlayerHookRef,playerAllocated,a2,a3,a4,a5);

	//logInfo("%llu CreateServerPlayer_patched end   %p %p", GetTick(), (int)(int*)playerAllocated, &playerAllocated);

	return result;
}