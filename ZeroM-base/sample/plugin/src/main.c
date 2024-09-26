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
void setPos(void* arg) {
    sceClibPrintf("Set Pos\n");
    if(!CheckPlayer()){ return; }


    double posx = zeroMData->Player->posx1+5;
    double posy = zeroMData->Player->posy1+2;
    double posz = zeroMData->Player->posz1+15;
    zeroMData->Player->__vftable->teleportTo(zeroMData->Player, posx, posy, posz);
}
void kill(void* arg) {
    sceClibPrintf("Set Pos\n");
    if(!CheckPlayer()){ return; }
    zeroMData->Player->__vftable->kill(zeroMData->Player);
}

void fillMenu(){
    // propagate with the necessary stuff
    tabs[0].name = "Super Fun";
    tabs[0].entries = &entriesTab1;
    tabs[0].entries[0].name = "Set Angle";
    tabs[0].entries[0].func = setAngle;
    tabs[0].entries[1].name = "Teleport";
    tabs[0].entries[1].func = setPos;
    tabs[0].entries[2].name = "Kill";
    tabs[0].entries[2].func = kill;
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
