#include "navigation.h"



SceCtrlData current_pad;
SceCtrlData emptyPad;

bool pressedR = false;
bool pressedL = false;


static SceUID ctrlPeek1_hook;
static tai_hook_ref_t ctrlPeek1_ref;
int ctrlPeek1_patched(int port, SceCtrlData *pad_data, int count) {
	int ret = TAI_CONTINUE(int, ctrlPeek1_ref, port, pad_data, count);
	memcpy(&current_pad, pad_data, sizeof(SceCtrlData));
	if(activeMenu){
		memcpy(pad_data, &emptyPad, sizeof(SceCtrlData));
        doNavigation(&menu);
	}
	return ret;
}
/*
static SceUID ctrlPeek2_hook;
static tai_hook_ref_t ctrlPeek2_ref;
int ctrlPeek2_patched(int port, SceCtrlData *pad_data, int count) {
	int ret = TAI_CONTINUE(int, ctrlPeek2_ref, port, pad_data, count);
	memcpy(&current_pad, pad_data, sizeof(SceCtrlData));
	if(activeMenu){
		memcpy(pad_data, &emptyPad, sizeof(SceCtrlData));

	}
	return ret;
}
*/


void doNavigation(Menu* menu){
    if(current_pad.buttons & SCE_CTRL_LTRIGGER){
        if(!pressedL){
            pressedL = true;
            change_current_tab(&menu, -1);
        }
    }else{
        pressedL = false;
    }
    if(current_pad.buttons & SCE_CTRL_RTRIGGER){
        if(!pressedR){
            pressedR = true;
            change_current_tab(&menu, 1);
        }
    }else{
        pressedR = false;
    }
}

void SetupEmptyPad(){
	emptyPad.lx = 127;
	emptyPad.ly = 127;
	emptyPad.rx = 127;
	emptyPad.ry = 127;
}

void navigation_hooks(){
	SetupEmptyPad();
	ctrlPeek1_hook = taiHookFunctionImport(&ctrlPeek1_ref, TAI_MAIN_MODULE, TAI_ANY_LIBRARY, 0xA9C3CED6, ctrlPeek1_patched);
}

void navigation_release_hooks(){
	taiHookRelease(ctrlPeek1_hook, ctrlPeek1_ref);
}