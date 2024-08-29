#include "hooks.h"


tai_hook_ref_t hook_refs[TOTAL_HOOKS];
SceUID hooks[TOTAL_HOOKS];

SceUID add_taiHookFunctionOffset	(tai_hook_ref_t* p_hook, SceUID modid, int segidx, uint32_t offset, int thumb, const void * hook_func){


    return 0;
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

	if(playerF != player){
		if(playerCaught == NULL){
			playerAdd = (int*)playerF;
			playerCaught = playerF;
			sceClibPrintf("Player_Tick_patched playerCaught: %08X\n", (int)playerAdd);
		}
	}

	TAI_NEXT(Player_Tick_patched, hook_refs[0], playerF);
	
	//sceClibPrintf("Player_Tick_patched: %08X\n", param_1);
	
	//sceClibPrintf("B:%.2f|%.2f|%.2f\r\n", *(float*)&param_1[0x100], *(float*)&param_1[0x101], *(float*)&param_1[0x102]);
}

void Livingent_Tick_patched(int *param_1) {
	TAI_NEXT(Livingent_Tick_patched, hook_refs[1], param_1);
	
	
}

int  CreateServerPlayer_patched(Player* playerAllocated, int a2, int *a3, int a4, int a5){
	player = playerAllocated;
	sceClibPrintf("%llu sub_8183458C %08X\n", GetTick(), (int)(int*)playerAllocated);
	int result = TAI_NEXT(CreateServerPlayer_patched, hook_refs[19],playerAllocated,a2,a3,a4,a5);

	//print_bytes(playerAllocated->extraData, 0xA8C);
	sceClibPrintf("%llu sub_8183458C %08X\n", GetTick(), (int)(int*)playerAllocated);

	return result;
}