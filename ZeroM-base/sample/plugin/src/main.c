#include <psp2/kernel/clib.h>
#include <psp2/kernel/modulemgr.h>
#include <string.h>
#include <math.h>
#include "gamemod.h"


// you can decide how many tabs and entries.
// currently you kind of have to hardcode these and fillMenu() :S
Tab tabs[3];
Entry entriesTab1[2];
Entry entriesTab2[2];
Entry entriesTab3[1];


// this function is called after this mod was loaded in ZeroM
// will later probably get better callbacks.
void startFunction(ZeroMData* zeroMData){
    //gameMod.gameModInfo->modName[9] = 'o';
    sceClibPrintf("Hello world from %s by %s\n", gameMod.gameModInfo->modName, gameMod.gameModInfo->modAuthor);
}


void testFunction(void* arg) {
    sceClibPrintf("Test function");
}

void fillMenu(){
    // propagate with the necessary stuff
    tabs[0].name = "Super Fun";
    tabs[0].entries = &entriesTab1;
    tabs[0].entries[0].name = "Enable X";
    tabs[0].entries[0].func = testFunction;
    tabs[0].entries[1].name = "Enable A";
    tabs[0].entry_count = 2;

    tabs[1].name = "Extra Settings";
    tabs[1].entries = &entriesTab2;
    tabs[1].entries[0].name = "Toggle";
    tabs[1].entries[0].func = testFunction;
    tabs[1].entries[1].name = "Remove";
    tabs[1].entry_count = 2;

    tabs[2].name = "Help";
    tabs[2].entries = &entriesTab3;
    tabs[2].entries[0].name = "discord: ki.ne";
    tabs[2].entry_count = 1;
}


// Do NOT touch these if you don't know what you're doing
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
