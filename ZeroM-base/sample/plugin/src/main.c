#include <psp2/kernel/clib.h>
#include <psp2/kernel/modulemgr.h>
#include <string.h>
#include <math.h>
#include "gamemod.h"





// this function is called after this mod was loaded in ZeroM
// will later probably get better callbacks.
void startFunction(){
    sceClibPrintf("Hello world from %s by %s\n", gameMod.gameModInfo->modName, gameMod.gameModInfo->modAuthor);
}





// Do NOT touch these if you don't know what you're doing
GameMod gameMod;
int module_start() {
    gameMod.gameModInfo = &gameModInfo; gameMod.startFunction = startFunction;
    return SCE_KERNEL_START_SUCCESS;
}
int module_stop() {
    return SCE_KERNEL_STOP_SUCCESS;
}
void _start() __attribute__ ((weak, alias ("module_start")));
GameMod* getGameMod(){ return &gameMod; }
