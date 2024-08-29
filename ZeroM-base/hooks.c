#include "hooks.h"



tai_hook_ref_t hook_refs[TOTAL_HOOKS];
SceUID hooks[TOTAL_HOOKS];
int currentHooks = 0;
tai_module_info_t info;
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

    SceUID currentPID = sceKernelGetProcessId();
	logInfo("Process ID : %d", currentPID);
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

tai_hook_ref_t* add_taiHookFunctionOffset(uint32_t offset, const void * hook_func){
    int segidx = 0;
    int thumb = 1;
	hooks[currentHooks] = taiHookFunctionOffset(&hook_refs[currentHooks], info.modid, segidx, offset, thumb, hook_func);
    currentHooks++;
    return &hook_refs[currentHooks-1];
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

	if(playerF != NULL && playerF != player){
		if(playerCaught == NULL){
			playerAdd = (int*)playerF;
			playerCaught = playerF;
			logInfo("Player_Tick_patched playerCaught: %08X %08X", (int)playerAdd, &playerF);
		}
	}

	TAI_NEXT(Player_Tick_patched, *playerTickHookRef, playerF);
	
	//logInfo("Player_Tick_patched: %08X\n", param_1);
	
	//logInfo("B:%.2f|%.2f|%.2f\r\n", *(float*)&param_1[0x100], *(float*)&param_1[0x101], *(float*)&param_1[0x102]);
}

void Livingent_Tick_patched(int *param_1) {
	TAI_NEXT(Livingent_Tick_patched, *livingEntTickHookRef, param_1);
	
	
}


int  CreateServerPlayer_patched(Player* playerAllocated, int a2, int *a3, int a4, int a5){
	player = playerAllocated;
	logInfo("%llu CreateServerPlayer_patched %08X", GetTick(), (int)(int*)playerAllocated);
	int result = TAI_NEXT(CreateServerPlayer_patched, *createServerPlayerHookRef,playerAllocated,a2,a3,a4,a5);

	//print_bytes(playerAllocated->extraData, 0xA8C);
	logInfo("%llu sub_8183458C %08X", GetTick(), (int)(int*)playerAllocated);

	return result;
}