#include "menu.h"
#include "../common/pluginreload.h"
#include "structures/menuitems.h"
#include "navigation.h"


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
Menu menu;

Menu* GetMenuPointer(){
	return &menu;
}

int sceDisplaySetFrameBuf_patched(const SceDisplayFrameBuf *pParam, int sync) {

    //sceCtrlPeekBufferPositive(0, &pad, 1);
	if(activeMenu){
		updateFramebuf(pParam);
		if(pluginReloadLoaded){
			drawStringF(5, 5, "  ZeroM v:%d    PR:%d   made by Bizzy  " , ZEROM_VERSION, GetPluginLoaderVersion());
		}else{
			drawStringF(5, 5, "  ZeroM v:%d    PR:?   made by Bizzy  " , ZEROM_VERSION);
		}

		drawString(5, 25, " L+Select: Toggle menu; L/R: switch tabs ");

		display_menu(&menu);
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




void SetupMenu(Menu* m){
	m->tab_count = 0;
	m->current_shown_tab = 0;

    add_tab(m, "Info");
    add_tab(m, "Mods");
    add_tab(m, "Settings");
    add_tab(m, "Credits");

    add_entry_to_tab(m, "Info", "CPU\0");
    add_entry_to_tab(m, "Info", "GPU");
    add_entry_to_tab(m, "Info", "SSD");
    add_entry_to_tab(m, "Info", "MACADDRESS");
    add_entry_to_tab(m, "Mods", "nudestealer");
    add_entry_to_tab(m, "Mods", "INSTALL HARRYPOTTER.VPK");
    add_entry_to_tab_with_function(m, "Settings", "Rainbow Mode", toggleRGBMode);
    add_entry_to_tab(m, "Settings", "Exit");

    add_entry_to_tab(m, "Credits", "Many thanks to everyone who helped!");
    add_entry_to_tab(m, "Credits", "Cat(isage)");
    add_entry_to_tab(m, "Credits", "CreepNT");
    add_entry_to_tab(m, "Credits", "Kuria");
    add_entry_to_tab(m, "Credits", "PrincessOfSleeping");
    add_entry_to_tab(m, "Credits", "everyone in the community!");
    add_entry_to_tab(m, "Credits", "MPVolta coming 2025 Spring");
}




void menu_draw_hooks(){
	logInfo("Menu hooks!");
	SetupMenu(GetMenuPointer());
	display_hook = taiHookFunctionImport(&display_ref, TAI_MAIN_MODULE, TAI_ANY_LIBRARY, 0x7A410B64, sceDisplaySetFrameBuf_patched);
	//ctrlPeek2_hook = taiHookFunctionImport(&ctrlPeek2_ref, TAI_MAIN_MODULE, TAI_ANY_LIBRARY, 0x15F81E8C, ctrlPeek2_patched);
	//sceDisplaySetFrameBuf_30fps_hook = taiHookFunctionImport(&sceDisplaySetFrameBuf_30fps_ref, TAI_MAIN_MODULE, TAI_ANY_LIBRARY, 0x7A410B64, sceDisplaySetFrameBuf_30fps);
	logInfo("Menu hooks done!");
}
void menu_draw_release_hooks(){
	logInfo("Removing menu hooks!");
	taiHookRelease(display_hook, display_ref);
	//taiHookRelease(ctrlPeek2_hook, ctrlPeek2_patched);
	//taiHookRelease(sceDisplaySetFrameBuf_30fps_hook, sceDisplaySetFrameBuf_30fps_ref);
	logInfo("Removed menu hooks!");
}