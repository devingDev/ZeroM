#include "hooks.h"
#include "gamemodloader.h"
#include <psp2/display.h>



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

int* playerAdd;
Player* player;
tai_hook_ref_t* Player_new_REF;
void Player_new(int *a, int *b,int *c){
	logInfo("Player_new_REF begin %08X", a);
	player = a;
	playerAdd = a;
	setPlayer(player);
	TAI_NEXT(Player_new, *Player_new_REF, a, b, c);
	logInfo("Player_new_REF end   %08X", a);
}
int* serverplayerAdd;
Player* serverplayer;
tai_hook_ref_t* ServerPlayer_new_REF;
void ServerPlayer_new(int *a, int *b, int *c, int *d, int *e){
	logInfo("ServerPlayer_new_REF begin %08X", a);
	serverplayer = a;
	serverplayerAdd = a;
	TAI_NEXT(ServerPlayer_new, *ServerPlayer_new_REF, a, b, c, d, e);
	logInfo("ServerPlayer_new_REF end   %08X", a);
	return;
}

tai_hook_ref_t* run_middle_REF;
void run_middle(void* param){
	TAI_NEXT(run_middle, *run_middle_REF, param);
	return;
}
tai_hook_ref_t* local_player_tick_ref;
void local_player_tick(void* localplayer){
	//logInfo("local_player_tick begin %08X", localplayer);
	player = localplayer;
	playerAdd = localplayer;
	setPlayer(player);
	TAI_NEXT(local_player_tick, *local_player_tick_ref, player);
	return;
}




// add item test

tai_hook_ref_t* MinecraftWorld_RunStaticCtors_ref;
void MinecraftWorld_RunStaticCtors(void){
	TAI_NEXT(MinecraftWorld_RunStaticCtors, *MinecraftWorld_RunStaticCtors_ref);
	logInfo("MinecraftWorld_RunStaticCtors");
}
tai_hook_ref_t* TextureAtlas__loadUVs_ref;
void TextureAtlas__loadUVs(int* atlasAddr){
	TAI_NEXT(TextureAtlas__loadUVs, *TextureAtlas__loadUVs_ref, atlasAddr);
	logInfo("TextureAtlas__loadUVs %08X", atlasAddr);
}




void setupHooks(){
	logInfo("Hooking");
	Player_new_REF = add_taiHookFunctionOffset(0x32e5a8, Player_new);
	ServerPlayer_new_REF = add_taiHookFunctionOffset(0x83458c, ServerPlayer_new);
	//run_middle_REF = add_taiHookFunctionOffset(0x7d5f70, run_middle);
	local_player_tick_ref = add_taiHookFunctionOffset(0x7edcca, local_player_tick);

	//MinecraftWorld_RunStaticCtors_ref = add_taiHookFunctionOffset(0x2c904a, MinecraftWorld_RunStaticCtors);
	//TextureAtlas__loadUVs_ref = add_taiHookFunctionOffset(0x89b47a, TextureAtlas__loadUVs);
	
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

