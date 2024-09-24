#include "navigation.h"



SceCtrlData current_pad;
SceCtrlData emptyPad;

int confirmButtonAssign = -1;
SceCtrlButtons btnConfirm;
SceCtrlButtons btnAbort;

bool pressedR = false;
bool pressedL = false;
bool pressedUp = false;
bool pressedDown = false;
bool pressedConfirm = false;
bool pressedAbort = false;


static SceUID ctrlPeek1_hook;
static tai_hook_ref_t ctrlPeek1_ref;
int ctrlPeek1_patched(int port, SceCtrlData *pad_data, int count) {
	int ret = TAI_CONTINUE(int, ctrlPeek1_ref, port, pad_data, count);
	memcpy(&current_pad, pad_data, sizeof(SceCtrlData));
	if(activeMenu){
		memcpy(pad_data, &emptyPad, sizeof(SceCtrlData));
        doNavigation(GetMenuPointer());
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
            change_current_tab(menu, -1);
        }
    }else{
        pressedL = false;
    }
    if(current_pad.buttons & SCE_CTRL_RTRIGGER){
        if(!pressedR){
            pressedR = true;
            change_current_tab(menu, 1);
        }
    }else{
        pressedR = false;
    }
    if(current_pad.buttons & SCE_CTRL_UP){
        if(!pressedUp){
            pressedUp = true;
            change_current_entry(menu, -1);
        }
    }else{
        pressedUp = false;
    }
    if(current_pad.buttons & SCE_CTRL_DOWN){
        if(!pressedDown){
            pressedDown = true;
            change_current_entry(menu, 1);
        }
    }else{
        pressedDown = false;
    }
    if(current_pad.buttons & btnConfirm){
        if(!pressedConfirm){
            pressedConfirm = true;
            logInfo("confirm");
            execute_entry(menu);
        }
    }else{
        pressedConfirm = false;
    }
    if(current_pad.buttons & btnAbort){
        if(!pressedAbort){
            pressedAbort = true;
            logInfo("abort");
        }
    }else{
        pressedAbort = false;
    }
}

int CheckButtonAssign(){
	int ret = 0;
	
	if(confirmButtonAssign!=-1)
		return confirmButtonAssign;
	ret = sceRegMgrGetKeyInt("/CONFIG/SYSTEM", "button_assign", &confirmButtonAssign);
	if (ret < 0) {
		return ret;
	}else{
		return confirmButtonAssign;
	}
}

void SetupEmptyPad(){
	emptyPad.lx = 127;
	emptyPad.ly = 127;
	emptyPad.rx = 127;
	emptyPad.ry = 127;
}

bool runNavThread = true;
SceUID navthid = -1;
int ZeroM_NAV_thread(unsigned int args, void* argp){
    while(runNavThread){
        sceKernelDelayThread(50);
    }
}

void navigation_hooks(){
	SetupEmptyPad();
	confirmButtonAssign = CheckButtonAssign();
    if(!confirmButtonAssign){
        btnConfirm = SCE_CTRL_CIRCLE;
        btnAbort = SCE_CTRL_CROSS;
    }else{
        btnConfirm = SCE_CTRL_CROSS;
        btnAbort = SCE_CTRL_CIRCLE;
    }
	ctrlPeek1_hook = taiHookFunctionImport(&ctrlPeek1_ref, TAI_MAIN_MODULE, TAI_ANY_LIBRARY, 0xA9C3CED6, ctrlPeek1_patched);

	//navthid = sceKernelCreateThread("ZeroM_NAV_thread", ZeroM_NAV_thread, 0x40, 0x10000, 0, 0, NULL);
	//sceKernelStartThread(navthid, 0, NULL);
}

void navigation_release_hooks(){
	taiHookRelease(ctrlPeek1_hook, ctrlPeek1_ref);
	runNavThread = false;
	//sceKernelWaitThreadEnd(navthid, NULL, NULL);
}