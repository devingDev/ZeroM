#include "menu.h"
#include "pluginreload.h"
#include "menuitems.h"
#include "navigation.h"
#include "gamemodloader.h"
#include <psp2/kernel/sysmem.h>


#define SWITCH_MODE_DELAY 3000000
#define FPS_TIMER_TICK    1000000
#define NUM_MODES         2
void display_menu(const Menu* menu);
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
void* currentMenu;

Menu* GetMenuPointer(){
	return &menu;
}
Menu* GetActiveMenu(){
	if(currentMenu == NULL){
		return GetMenuPointer();
	}
	else{
		GameMod* gameMod = (GameMod*)currentMenu;
		return(Menu*)gameMod;
	}
}
SceKernelFreeMemorySizeInfo freeMemInfo;
int sceDisplaySetFrameBuf_patched(const SceDisplayFrameBuf *pParam, int sync) {

    //sceCtrlPeekBufferPositive(0, &pad, 1);
	if(activeMenu){
		updateFramebuf(pParam);
		if(pluginReloadLoaded){
			drawStringF(5, 5, "  ZeroM v:%d    PR:%d   made by Bizzy  " , ZEROM_VERSION, GetPluginLoaderVersion());
		}else{
			drawStringF(5, 5, "  ZeroM v:%d    PR:?   made by Bizzy  " , ZEROM_VERSION);
		}

		drawStringF(5, 25, " L+Select: Toggle menu; L/R: switch tabs ");

		sceKernelGetFreeMemorySize(&freeMemInfo);
		//drawStringF(5, 45, "Free Memory : %d", freeMemInfo.size_phycont); // always 0 anyway?
		drawStringF(5, 45, "Mods loaded : %d ", countGameMods);

		display_menu(&menu);
	}
	return TAI_CONTINUE(int, display_ref, pParam, sync);
}


void drawTabs(Tab* tabs, int tab_count, int current_tab){
    int x = 5;
    int y = 75;
	for (int i = 0; i < tab_count; ++i) {
		if(current_tab == i){
			setTextColor(0x0000FFFF);
			setTextImportant();
		}
		drawStringF(x + 128*i, y, " %s ", tabs[i].name);
		if(current_tab == i){
			setTextColor(0x00FFFFFF);
			setTextUnimportant();
		}
	}
}

void drawTabEntries(Tab* tab){
	int x = 5;
	int y = 75;
	for (int j = 0; j < tab->entry_count; ++j) {
		const Entry* entry = &tab->entries[j];
		if(tab->current_selected_entry == j){
			setTextColor(0x0000FFFF);
			setTextImportant();
		}
		drawStringF(x, y+(j+2)*FONT_VERT_DIST, " %s ", entry->name);
		if(tab->current_selected_entry == j){
			setTextColor(0x00FFFFFF);
			setTextUnimportant();
		}
	}
}

void display_menu(const Menu* menu) {

	if(currentMenu == NULL){
		drawTabs(menu->tabs, menu->tab_count, menu->current_shown_tab);
		drawTabEntries(&menu->tabs[menu->current_shown_tab]);
		
		return;
	}

	GameMod* gm = (GameMod*)currentMenu;
	//gm->tabs
	drawTabs(gm->tabs, gm->tab_count, gm->current_shown_tab);
	drawTabEntries(&gm->tabs[gm->current_shown_tab]);

}


// when reloading plugin, it crashes so i removed this for now:
static SceUID sceDisplaySetFrameBuf_30fps_hook;
static tai_hook_ref_t sceDisplaySetFrameBuf_30fps_ref;
int sceDisplaySetFrameBuf_30fps(const SceDisplayFrameBuf *pParam, int sync) {
	int ret = TAI_CONTINUE(int, sceDisplaySetFrameBuf_30fps_ref, pParam, sync);
	sceDisplayWaitVblankStartMulti(2);
	return ret;
}

void changeMenu(void* gameMod){
	currentMenu = gameMod;
	logInfo("changeMenu 0x%08X", gameMod);
}

void execute_entry() {
	Menu* activeMenu = GetActiveMenu();
    Tab* tab = &activeMenu->tabs[activeMenu->current_shown_tab];
    Entry* entry = &tab->entries[tab->current_selected_entry];
    if (entry->func != NULL) {
        entry->func(entry->funcArg);
    }
}

void menu_go_back(){
	changeMenu(NULL);
}
void change_current_tab(int direction) {
	Menu* activeMenu = GetActiveMenu();
    if(direction > 0){
        if(activeMenu->current_shown_tab < activeMenu->tab_count-1){
            activeMenu->current_shown_tab++;
        }
    }else{
        if(activeMenu->current_shown_tab > 0){
            activeMenu->current_shown_tab--;
        }
    }
    
}
void change_current_entry(int direction) {
	Menu* activeMenu = GetActiveMenu();

    if(direction > 0){
        if(activeMenu->tabs[activeMenu->current_shown_tab].current_selected_entry < activeMenu->tabs[activeMenu->current_shown_tab].entry_count-1){
            activeMenu->tabs[activeMenu->current_shown_tab].current_selected_entry++;
        }
    }else{
        if(activeMenu->tabs[activeMenu->current_shown_tab].current_selected_entry > 0){
            activeMenu->tabs[activeMenu->current_shown_tab].current_selected_entry--;
        }
    }
    
}

void add_mod_entry_to_mods_tab(Menu* menu, GameMod* gameMod){
	logInfo("Adding mod tab for : %08X , %s", gameMod, gameMod->gameModInfo->modName);
    for (int i = 0; i < menu->tab_count; ++i) {
        Tab* tab = &menu->tabs[i];
        if (sceClibStrcmp(tab->name, MOD_TAB_NAME) == 0) {
            if (tab->entry_count < MAX_ENTRIES_PER_TAB) {
                tab->entries = (Entry*)realloc((void*)tab->entries, sizeof(Entry) * (tab->entry_count+1));
                

                Entry* entry = &tab->entries[tab->entry_count];
                entry->enabled = false;

                //SceSize entry_length = sceClibStrnlen(gameMod->gameModInfo->modName, MAX_NAME_LENGTH);
                //entry->name = (char*)malloc((entry_length+1)* sizeof(char));
                //sceClibStrncpy(entry->name, gameMod->gameModInfo->modName, entry_length);
                //entry->name[entry_length] = '\0'; 
                entry->name = gameMod->gameModInfo->modName;
                entry->enabled = false;
                entry->func = changeMenu;
				entry->funcArg = (void*)gameMod;
                entry->isModEntry = true;
                tab->entry_count++;
            }
            return;
        }
    }
}
void setup_menu(Menu* m){
	currentMenu = NULL;
    m->tabs = NULL;
	m->tab_count = 0;
	m->current_shown_tab = 0;

    create_memspace(); // todo move elsewhere?

    add_tab(m, "Info");
    add_tab(m, MOD_TAB_NAME);
    add_tab(m, "Settings");

    add_entry_to_tab(m, "Info", "Info1");
    add_entry_to_tab(m, "Info", "Info2");
    add_entry_to_tab_with_function(m, "Settings", "Rainbow Mode", toggleRGBMode);
    add_entry_to_tab_with_function(m, "Settings", "Rainbow Mode", toggleRGBMode);
    
}

void destroy_menu(Menu* m){
    logInfo("Destroying menu");
    for(int i = 0; i < m->tab_count; i++){
        Tab* t = &m->tabs[i];
        if(t != NULL){
            for(int j = 0; j < t->entry_count; j++){
                Entry* e = &t->entries[j];
                if(e != NULL && !e->isModEntry){
                    free(e->name);
                }
            }
            free(t->name);
            free(t->entries);
        }
    }
    free(m->tabs);

    destroy_memspace();
}


void menu_draw_hooks(){
	logInfo("Menu hooks!");
	setup_menu(GetMenuPointer());
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

void menu_end(){
	destroy_menu(GetMenuPointer());
}




void add_mod_entry(GameMod* gameMod){
	add_mod_entry_to_mods_tab(GetMenuPointer(), gameMod);
}


