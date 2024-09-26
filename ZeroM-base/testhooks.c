#include "testhooks.h"

#define undefined4 unsigned int
#define undefined unsigned char


tai_hook_ref_t* LocalPlayer__tick_REF;
void LocalPlayer__tick(int *param_1){
	//logInfo("LocalPlayer__tick begin %08X", param_1);
	TAI_NEXT(LocalPlayer__tick, *LocalPlayer__tick_REF, param_1);
}

tai_hook_ref_t* MinecraftServer__tick_REF;
void MinecraftServer__tick(int *param_1){
	TAI_NEXT(MinecraftServer__tick, *MinecraftServer__tick_REF, param_1);
}


void doTestHooks(){
	logInfo("Adding test hooks...");

    LocalPlayer__tick_REF = add_taiHookFunctionOffset(0x7edcca, LocalPlayer__tick);
    MinecraftServer__tick_REF = add_taiHookFunctionOffset(0x80a11e, MinecraftServer__tick);


	logInfo("Added test hooks...");
}

void removeTestHooks(){
	logInfo("Removing test hooks...");
    
	logInfo("Removed test hooks...");
}


