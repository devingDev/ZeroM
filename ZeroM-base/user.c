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

#include "eboot.bin.elf.h"

#define TAI_NEXT(this_func, hook, ...) ({ \
  (((struct _tai_hook_user *)hook)->next) != 0 ? \
    ((__typeof__(&this_func))((struct _tai_hook_user *)((struct _tai_hook_user *)hook)->next)->func)(__VA_ARGS__) \
  : \
    ((__typeof__(&this_func))((struct _tai_hook_user *)hook)->old)(__VA_ARGS__) \
  ; \
})

const int ZEROM_VERSION = 11;


#define TOTAL_HOOKS 99
static tai_hook_ref_t hook_refs[TOTAL_HOOKS];
SceUID hooks[TOTAL_HOOKS];

uint64_t GetTick(){
	return sceKernelGetSystemTimeWide();
}



bool done = false;
SceCtrlData ctrlData;

int* playerAdd;
Player* player = NULL;
Player* playerCaught = NULL;

uint32_t swap(uint32_t in)
{
  return __builtin_bswap32(in);
}

void print_bytes(const unsigned char *data, size_t size) {
	sceClibPrintf("\n\n");
	sceClibPrintf("Offset   00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
	sceClibPrintf("\n");
    for (size_t i = 0; i < size; i+=16) {
        //sceClibPrintf("%04X  |  %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X \n", i,
		//				data[i], data[i+1], data[i+2], data[i+3], data[i+4], data[i+5], data[i+6], data[i+7],
		//				data[i+8], data[i+9], data[i+10], data[i+11], data[i+12], data[i+13], data[i+14], data[i+15]);
        sceClibPrintf("%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X \n",
						data[i], data[i+1], data[i+2], data[i+3], data[i+4], data[i+5], data[i+6], data[i+7],
						data[i+8], data[i+9], data[i+10], data[i+11], data[i+12], data[i+13], data[i+14], data[i+15]);
    }
	sceClibPrintf("\n\n");
}

void (* EntityTick1)(int *param1) = NULL;


void Player_Tick_patched(Player *playerF) {

	if(playerF != player){
		if(playerCaught == NULL){
			playerAdd = (int*)playerF;
			playerCaught = playerF;
			sceClibPrintf("Player_Tick_patched playerCaught: %08X\n", playerAdd);
		}
	}

	TAI_NEXT(Player_Tick_patched, hook_refs[0], playerF);
	
	//sceClibPrintf("Player_Tick_patched: %08X\n", param_1);
	
	//sceClibPrintf("B:%.2f|%.2f|%.2f\r\n", *(float*)&param_1[0x100], *(float*)&param_1[0x101], *(float*)&param_1[0x102]);
}

void Livingent_Tick_patched(int *param_1) {
	TAI_NEXT(Livingent_Tick_patched, hook_refs[1], param_1);
	
	
}


void FUN_817e2746(int *param_1){
	TAI_CONTINUE(void, hook_refs[2]);
	//sceClibPrintf("|FUN_817e2746 %08X", param_1);
}

void FUN_8182f080(int param_1){
	TAI_CONTINUE(void, hook_refs[3]);
	//sceClibPrintf("|FUN_8182f080 %08X", param_1);
}



void FUN_8116f00e(int* param_1){
	//sceClibPrintf("FUN_8116f00e %08X\n", param_1);
	//(*(void (__fastcall **)(int *))(*param_1 + 88))(param_1);
	
	//(**(code **)(*param_1 + 0x58))(param_1);
	
	TAI_CONTINUE(void, hook_refs[4], param_1);
}
void FUN_8189a2f8(int param_1,char param_2,int param_3,int param_4,int param_5){
	//sceClibPrintf("FUN_8189a2f8 %08X %c %d %d %08X\n", param_1, param_2,param_3,param_4,param_5);
	TAI_CONTINUE(void, hook_refs[5], param_1, param_2, param_3, param_4, param_5);
}
void FUN_81aeaec0(int param_1,int param_2){
	//sceClibPrintf("FUN_81aeaec0 %08X %08X\n", param_1, param_2);
	TAI_CONTINUE(void, hook_refs[6], param_1, param_2);
}
int sub_817C894C(int param_1,int param_2,int param_3){
	sceClibPrintf("sub_817C894C %08X %08X %08X\n", param_1, param_2, param_3);
	return TAI_CONTINUE(int, hook_refs[7], param_1, param_2, param_3);
}
int * FUN_817e1a7e(int *param_1){
	sceClibPrintf("FUN_817e1a7e %08X\n", param_1);
	return TAI_CONTINUE(int*, hook_refs[8], param_1);
}
int * sub_817EDC4E(int *param_1){
	sceClibPrintf("sub_817EDC4E %08X\n", param_1);
	return TAI_CONTINUE(int*, hook_refs[9], param_1);
}
int * sub_817EDC7A(int *param_1){
	sceClibPrintf("sub_817EDC7A %08X\n", param_1);
	return TAI_CONTINUE(int*, hook_refs[10], param_1);
}
int * sub_817E1B12(int *param_1){
	sceClibPrintf("sub_817E1B12 %08X\n", param_1);
	return TAI_CONTINUE(int*, hook_refs[11], param_1);
}
int * sub_817E1B02(int *param_1){
	sceClibPrintf("sub_817E1B02 %08X\n", param_1);
	return TAI_CONTINUE(int*, hook_refs[12], param_1);
}
short * sub_81834D4E(int *a1,int *a2,int a3,int a4,int a5,int a6,int a7,int a8,int a9,int a10,int a11,int a12,int a13,int a14,int a15,int a16,int a17,int a18){
	sceClibPrintf("%llu sub_81834D4E %08X %08X\n", GetTick(), a1, a2 );
	return TAI_NEXT(sub_81834D4E, hook_refs[14],  a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18);
}
void FUN_818a5a10(void* a1, int a2, int a3, float a4, float a5, float a6, float a7, float a8, float a9){
	//sceClibPrintf("FUN_818a5a10 %08X %08X %08X %08X %08X %08X %08X %08X %08X\n", a1, a2, a3, a4, a5, a6, a7, a8, a9);
	TAI_NEXT(FUN_818a5a10, hook_refs[16], a1, a2, a3, a4, a5, a6, a7, a8, a9);
}


void * FUN_81688938(){
	sceClibPrintf("FUN_81688938\n");
	return TAI_NEXT(FUN_81688938, hook_refs[17]);
}
void FUN_817d91da(){
	sceClibPrintf("%llu FUN_817d91da\n", GetTick());
	return TAI_NEXT(FUN_817d91da, hook_refs[18]);
}


int  sub_8183458C(Player* playerAllocated, int a2, int *a3, int a4, int a5){
	player = playerAllocated;
	sceClibPrintf("%llu sub_8183458C %08X\n", GetTick(), (int*)playerAllocated);
	int result = TAI_NEXT(sub_8183458C, hook_refs[19],playerAllocated,a2,a3,a4,a5);

	//print_bytes(playerAllocated->extraData, 0xA8C);
	sceClibPrintf("%llu sub_8183458C %08X\n", GetTick(), (int*)playerAllocated);

	return result;
}

short * sub_818359C2(int *a1, int *a2, int *a3, int a4, unsigned char a5){
	sceClibPrintf("sub_818359C2\n");
	return TAI_NEXT(sub_818359C2, hook_refs[20],a1,a2,a3,a4,a5);
}

short * sub_81834D4C(int *a1,int *a2,int a3,int a4,int a5,int a6,int a7,int a8,int a9,int a10,int a11,int a12,int a13,int a14,int a15,int a16,int a17,int a18){
	sceClibPrintf("sub_81834D4C\n");
	return TAI_NEXT(sub_81834D4C, hook_refs[21],a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18);

}

short * sub_817C8586(int a1, int a2, int a3, int a4, int a5){
	sceClibPrintf("%llu sub_817C8586\n", GetTick());
	return TAI_NEXT(sub_817C8586, hook_refs[22],a1,a2,a3,a4,a5);

}


int module_get_offset(int uid, int seg, uint32_t in_off, void *out_off) {
	SceKernelModuleInfo info;
	if ((sceKernelGetModuleInfo(uid, &info) < 0) || (in_off > info.segments[seg].memsz))
		return -1;
	*(uint32_t *)out_off = (uint32_t)(info.segments[seg].vaddr + in_off);
	return 0;
}



int run = 1;
SceUID thid = -1;
int ZeroM_thread(unsigned int args, void* argp){
	sceClibPrintf("ZeroM_thread started\n");
	while (run == 1)
	{
		sceCtrlPeekBufferPositive(0, &ctrlData, 1);
		if(ctrlData.buttons & SCE_CTRL_CIRCLE){
			if(ctrlData.buttons & SCE_CTRL_UP){
				sceClibPrintf("%llu\n", GetTick());
				//print_bytes(playerAdd,0x40);

				sceClibPrintf("player: %08X\n", (int*)player);
				sceClibPrintf("playerAdd: %08X\n", playerAdd);

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
				print_bytes(player, 0xA90);
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
	done = false;
	
	tai_module_info_t info;
	info.size = sizeof(tai_module_info_t);
	taiGetModuleInfo(TAI_MAIN_MODULE, &info);
	
	SceUID currentPID = sceKernelGetProcessId();
	sceClibPrintf("Process ID : %d\n", currentPID);
	//sceKernelGetModuleInfo(uid, &info)
	int ret = module_get_offset(info.modid, 0, 0x16f00e, &EntityTick1);
	if(ret < 0){
		sceClibPrintf("ERROR getting function ERRORCODE: %d\n", ret);
	}else{
		sceClibPrintf("module_get_offset: %08X    %d\n", EntityTick1, ret);
	}
	//int ret = module_get_offset(currentPID, info.modid, 0, 0x16f00e, &EntityTick1);
	
	thid = sceKernelCreateThread("ZeroM_thread", ZeroM_thread, 0x40, 0x10000, 0, 0, NULL);
	sceKernelStartThread(thid, 0, NULL);
	
	sceClibPrintf("Hooking\n");

	hooks[0] = taiHookFunctionOffset(&hook_refs[0], info.modid, 0, 0x32FE14, 1, Player_Tick_patched);
	hooks[1] = taiHookFunctionOffset(&hook_refs[1], info.modid, 0, 0x289684, 1, Livingent_Tick_patched);
	//hooks[2] = taiHookFunctionOffset(&hook_refs[2], info.modid, 0, 0x7e2746, 1, FUN_817e2746);
	//hooks[3] = taiHookFunctionOffset(&hook_refs[3], info.modid, 0, 0x82f080, 1, FUN_8182f080);
	//hooks[4] = taiHookFunctionOffset(&hook_refs[4], info.modid, 0, 0x16f00e, 1, FUN_8116f00e);
	//hooks[5] = taiHookFunctionOffset(&hook_refs[5], info.modid, 0, 0x89a2f8, 1, FUN_8189a2f8);
	//hooks[6] = taiHookFunctionOffset(&hook_refs[6], info.modid, 0, 0xaeaec0, 1, FUN_81aeaec0);
	//hooks[7] = taiHookFunctionOffset(&hook_refs[7], info.modid, 0, 0x7C894C, 1, sub_817C894C);
	//hooks[8] = taiHookFunctionOffset(&hook_refs[8], info.modid, 0, 0x7e1a7e, 1, FUN_817e1a7e);
	//hooks[9] = taiHookFunctionOffset(&hook_refs[9], info.modid, 0, 0x7EDC4E, 1, sub_817EDC4E);
	//hooks[10] = taiHookFunctionOffset(&hook_refs[10], info.modid, 0, 0x7EDC7A, 1, sub_817EDC7A);
	//hooks[11] = taiHookFunctionOffset(&hook_refs[11], info.modid, 0, 0x7E1B12, 1, sub_817E1B12);
	//hooks[12] = taiHookFunctionOffset(&hook_refs[12], info.modid, 0, 0x7E1B02, 1, sub_817E1B02);
	////hooks[13] = taiHookFunctionOffset(&hook_refs[13], info.modid, 0, 0x83458C, 1, sub_8183458C);
	hooks[14] = taiHookFunctionOffset(&hook_refs[14], info.modid, 0, 0x834D4E, 1, sub_81834D4E);
	hooks[16] = taiHookFunctionOffset(&hook_refs[16], info.modid, 0, 0x8a5a10, 1, FUN_818a5a10);
	hooks[17] = taiHookFunctionOffset(&hook_refs[17], info.modid, 0, 0x688938, 1, FUN_81688938);
	hooks[18] = taiHookFunctionOffset(&hook_refs[18], info.modid, 0, 0x7d91da, 1, FUN_817d91da);
	hooks[19] = taiHookFunctionOffset(&hook_refs[19], info.modid, 0, 0x83458C, 1, sub_8183458C);
	hooks[20] = taiHookFunctionOffset(&hook_refs[20], info.modid, 0, 0x8359C2, 1, sub_818359C2);
	////hooks[21] = taiHookFunctionOffset(&hook_refs[21], info.modid, 0, 0x834D4C, 1, sub_81834D4C);
	hooks[22] = taiHookFunctionOffset(&hook_refs[22], info.modid, 0, 0x7C8586, 1, sub_817C8586);
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
