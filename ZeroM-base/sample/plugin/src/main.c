#include <psp2/kernel/clib.h>
#include <psp2/kernel/modulemgr.h>
#include <string.h>
#include <math.h>
#include "gamemod.h"
#include "gamemodvars.h"


// you can decide how many tabs and entries.
// currently you kind of have to hardcode these and fillMenu() :S
Tab tabs[3];
Entry entriesTab1[3];
Entry entriesTab2[2];
Entry entriesTab3[1];


// this function is called after this mod was loaded in ZeroM
// will later probably get better callbacks.
void startFunction(ZeroMData* zmData){
    zeroMData = zmData;
    //gameMod.gameModInfo->modName[9] = 'o';
    sceClibPrintf("Hello world from %s by %s\n", gameMod.gameModInfo->modName, gameMod.gameModInfo->modAuthor);
}


void testFunction(void* arg) {
    sceClibPrintf("Test function\n");
}

bool CheckPlayer(){
    if(zeroMData->Player == NULL){
        sceClibPrintf("player was null :(\n");
        return false;
    }
    return true;
}
void setAngle(void* arg) {
    sceClibPrintf("Set Angle\n");
    if(!CheckPlayer()){ return; }

    float angle = 180.0;
    float angle2 = -15.0;
    zeroMData->Player->angle1 = angle;
    zeroMData->Player->angle2 = angle2;
}
void teleportForward(void* arg) {
    sceClibPrintf("Set Pos\n");
    if(!CheckPlayer()){ return; }

    Vec3* forward = zeroMData->Player->__vftable->getForward(zeroMData->Player);

   // int xDir = forward->x == 0 ? 0 : forward->x > 0.001 ? 1 : -1;
  //  int yDir = forward->y == 0 ? 0 : forward->y > 0.001 ? 1 : -1;
   // int zDir = forward->z == 0 ? 0 : forward->z > 0.001 ? 1 : -1;

    double xDir = (forward->x < 0.001 && forward->x > -0.001) ? 0 : forward->x;
    double yDir = (forward->y < 0.001 && forward->y > -0.001) ? 0 : forward->y;
    double zDir = (forward->z < 0.001 && forward->z > -0.001) ? 0 : forward->z;

    double newposx = zeroMData->Player->posx1 + (xDir * 10);
    double newposy = zeroMData->Player->posy1 + (yDir * 1) + 1;
    double newposz = zeroMData->Player->posz1 + (zDir * 10);
    zeroMData->Player->__vftable->teleportTo(zeroMData->Player, newposx, newposy, newposz);
}

void testFunc(void* arg) {
    sceClibPrintf("Test Func\n");
    if(!CheckPlayer()){ return; }
    Vec3* forward = zeroMData->Player->__vftable->getForward(zeroMData->Player);
    sceClibPrintf("got fwd\n");
    //hex_dump("test", &forward, 64);
    sceClibPrintf("Forward: %f %f %f\n", forward->x, forward->y, forward->z);
    sceClibPrintf("Forward: %08lX %08lX %08lX\n", forward->x, forward->y, forward->z);
}

void fillMenu(){
    // propagate with the necessary stuff
    tabs[0].name = "Super Fun";
    tabs[0].entries = &entriesTab1;
    tabs[0].entries[0].name = "Set Angle";
    tabs[0].entries[0].func = setAngle;
    tabs[0].entries[1].name = "Teleport forward";
    tabs[0].entries[1].func = teleportForward;
    tabs[0].entries[2].name = "TestFunc";
    tabs[0].entries[2].func = testFunc;
    tabs[0].entry_count = 3;

    tabs[1].name = "Extra Settings";
    tabs[1].entries = &entriesTab2;
    tabs[1].entries[0].name = "Nothing";
    tabs[1].entries[0].func = testFunction;
    tabs[1].entries[1].name = "Nothing";
    tabs[1].entry_count = 2;

    tabs[2].name = "Help";
    tabs[2].entries = &entriesTab3;
    tabs[2].entries[0].name = "discord: ki.ne";
    tabs[2].entry_count = 1;
}


// Do NOT touch these if you don't know what you're doing
ZeroMData* zeroMData;
GameMod gameMod;
int module_start() {
    fillMenu();
    gameMod.tabs = &tabs;
    gameMod.tab_count = sizeof(tabs)/sizeof(Tab);
    gameMod.current_shown_tab = 0;
    sceClibPrintf("GameMod tab count %d\n", gameMod.tab_count);
    gameMod.gameModInfo = &gameModInfo; 
    gameMod.startFunction = startFunction;
    return SCE_KERNEL_START_SUCCESS;
}
int module_stop() {
    return SCE_KERNEL_STOP_SUCCESS;
}
void _start() __attribute__ ((weak, alias ("module_start")));
GameMod* getGameMod(){ return &gameMod; }
