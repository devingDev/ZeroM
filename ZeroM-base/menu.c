#include "menu.h"
#include "../common/pluginreload.h"


#define SWITCH_MODE_DELAY 3000000
#define FPS_TIMER_TICK    1000000
#define NUM_MODES         2

enum {
	INTEGER_FPS,
	NO_FPS
};

static SceUID display_hook;
static tai_hook_ref_t display_ref;
uint64_t tick = 0;
uint64_t switch_tick = 0;
int frames = 0;
int fps = 0;
int mode = INTEGER_FPS;
uint64_t t_tick;


SceCtrlData current_pad;
SceCtrlData emptyPad;
int sceDisplaySetFrameBuf_patched(const SceDisplayFrameBuf *pParam, int sync) {

    //sceCtrlPeekBufferPositive(0, &pad, 1);
	if(activeMenu){
		updateFramebuf(pParam);
		if(pluginReloadLoaded){
			drawStringF(5, 5, "ZeroM v:%d    PR: %d" , ZEROM_VERSION, GetPluginLoaderVersion());
		}else{
			drawStringF(5, 5, "ZeroM v:%d    PR:?" , ZEROM_VERSION);
		}
	}
	return TAI_CONTINUE(int, display_ref, pParam, sync);
}


// when reloading plugin, it crashes so i removed this for now:
static SceUID sceDisplaySetFrameBuf_30fps_hook;
static tai_hook_ref_t sceDisplaySetFrameBuf_30fps_ref;
int sceDisplaySetFrameBuf_30fps(const SceDisplayFrameBuf *pParam, int sync) {
	int ret = TAI_CONTINUE(int, sceDisplaySetFrameBuf_30fps_ref, pParam, sync);
	sceDisplayWaitVblankStartMulti(2);
	return ret;
}

static SceUID ctrlPeek1_hook;
static tai_hook_ref_t ctrlPeek1_ref;
int ctrlPeek1_patched(int port, SceCtrlData *pad_data, int count) {
	int ret = TAI_CONTINUE(int, ctrlPeek1_ref, port, pad_data, count);
	memcpy(&current_pad, pad_data, sizeof(SceCtrlData));
	if(activeMenu){
		memcpy(pad_data, &emptyPad, sizeof(SceCtrlData));
	}
	return ret;
}

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

void SetupEmptyPad(){
	emptyPad.lx = 127;
	emptyPad.ly = 127;
	emptyPad.rx = 127;
	emptyPad.ry = 127;
}

void menu_draw_hook(){
	logInfo("Menu hooks!");
	SetupEmptyPad();
	display_hook = taiHookFunctionImport(&display_ref, TAI_MAIN_MODULE, TAI_ANY_LIBRARY, 0x7A410B64, sceDisplaySetFrameBuf_patched);
	ctrlPeek1_hook = taiHookFunctionImport(&ctrlPeek1_ref, TAI_MAIN_MODULE, TAI_ANY_LIBRARY, 0xA9C3CED6, ctrlPeek1_patched);
	//ctrlPeek2_hook = taiHookFunctionImport(&ctrlPeek2_ref, TAI_MAIN_MODULE, TAI_ANY_LIBRARY, 0x15F81E8C, ctrlPeek2_patched);
	//sceDisplaySetFrameBuf_30fps_hook = taiHookFunctionImport(&sceDisplaySetFrameBuf_30fps_ref, TAI_MAIN_MODULE, TAI_ANY_LIBRARY, 0x7A410B64, sceDisplaySetFrameBuf_30fps);
	logInfo("Menu hooks done!");
}
void menu_draw_release_hook(){
	logInfo("Removing menu hooks!");
	taiHookRelease(display_hook, display_ref);
	taiHookRelease(ctrlPeek1_hook, ctrlPeek1_ref);
	//taiHookRelease(ctrlPeek2_hook, ctrlPeek2_patched);
	//taiHookRelease(sceDisplaySetFrameBuf_30fps_hook, sceDisplaySetFrameBuf_30fps_ref);
	logInfo("Removed menu hooks!");
}