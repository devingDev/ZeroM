#ifndef MENUTITEMS_H
#define MENUTITEMS_H
#include <psp2/kernel/clib.h> 
#include "renderer.h"
#include "log.h"
#include "mem.h"

#define FONT_VERT_DIST 20

#define MAX_ENTRIES_PER_TAB 100
#define MAX_TABS 10
#define MAX_NAME_LENGTH 128

typedef void (*EntryFunction)(void);

typedef struct {
    char* name;
    EntryFunction func;
    bool enabled;
} Entry;

typedef struct {
    char* name;
    Entry* entries;
    int entry_count; 
    int current_selected_entry;
} Tab;

typedef struct {
    Tab* tabs;
    int tab_count;
    int current_shown_tab;
} Menu;


static void execute_entry(Menu* menu) {
    Tab* tab = &menu->tabs[menu->current_shown_tab];
    Entry* entry = &tab->entries[tab->current_selected_entry];
    if (entry->func != NULL) {
        entry->func();
    }
}


static void change_current_tab(Menu* menu, int direction) {
    if(direction > 0){
        if(menu->current_shown_tab < menu->tab_count-1){
            menu->current_shown_tab++;
        }
    }else{
        if(menu->current_shown_tab > 0){
            menu->current_shown_tab--;
        }
    }
    
}

static void change_current_entry(Menu* menu, int direction) {
    if(direction > 0){
        if(menu->tabs[menu->current_shown_tab].current_selected_entry < menu->tabs[menu->current_shown_tab].entry_count-1){
            menu->tabs[menu->current_shown_tab].current_selected_entry++;
        }
    }else{
        if(menu->tabs[menu->current_shown_tab].current_selected_entry > 0){
            menu->tabs[menu->current_shown_tab].current_selected_entry--;
        }
    }
    
}

static void add_tab(Menu* menu, const char* tab_name) {

    if (menu->tab_count < MAX_TABS) {
        if(menu->tabs == NULL){
            menu->tabs = (Tab*)calloc(1, sizeof(Tab));
        }else{
            menu->tabs = (Tab*)realloc((void*)menu->tabs, sizeof(Tab) * (menu->tab_count+1));
        }
        
        Tab* tab = &menu->tabs[menu->tab_count];
        SceSize strLength = sceClibStrnlen(tab_name, MAX_NAME_LENGTH);
        tab->name = (char*)calloc(strLength+1, sizeof(char));
        sceClibStrncpy(tab->name, tab_name, strLength);
        tab->entry_count = 0;
        tab->current_selected_entry = 0;
        tab->entries = NULL;
        menu->tab_count++;
    }
}


static void add_entry_to_tab_with_function(Menu* menu, const char* tab_name, const char* entry_name, EntryFunction func) {
    for (int i = 0; i < menu->tab_count; ++i) {
        Tab* tab = &menu->tabs[i];
        if (sceClibStrcmp(tab->name, tab_name) == 0) {
            if (tab->entry_count < MAX_ENTRIES_PER_TAB) {
                if(tab->entries == NULL){
                    tab->entries = (Entry*)calloc(1, sizeof(Entry));
                }else{
                    tab->entries = (Entry*)realloc((void*)tab->entries, sizeof(Entry) * (tab->entry_count+1));
                }
                

                Entry* entry = &tab->entries[tab->entry_count];
                entry->enabled = false;

                SceSize entry_length = sceClibStrnlen(entry_name, MAX_NAME_LENGTH);
                entry->name = (char*)malloc((entry_length+1)* sizeof(char));
                sceClibStrncpy(entry->name, entry_name, entry_length);
                entry->name[entry_length] = '\0'; 
                entry->enabled = false;
                entry->func = func;
                tab->entry_count++;
            }
            return;
        }
    }
}
static void add_entry_to_tab(Menu* menu, const char* tab_name, const char* entry_name) {
    add_entry_to_tab_with_function(menu, tab_name, entry_name, NULL);
}

static void display_menu(const Menu* menu) {

    int x = 5;
    int y = 55;
    for (int i = 0; i < menu->tab_count; ++i) {
        if(menu->current_shown_tab == i){
            setTextColor(0x0000FFFF);
            setTextImportant();
        }
        drawStringF(x + 128*i, y, " %s ", menu->tabs[i].name);
        if(menu->current_shown_tab == i){
            setTextColor(0x00FFFFFF);
            setTextUnimportant();
        }
    }
    const Tab* tab = &menu->tabs[menu->current_shown_tab];
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



static void setup_menu(Menu* m){
    m->tabs = NULL;
	m->tab_count = 0;
	m->current_shown_tab = 0;

    create_memspace(); // todo move elsewhere?

    add_tab(m, "Info");
    add_tab(m, "Mods");
    add_tab(m, "Settings");

    add_entry_to_tab(m, "Info", "Info1");
    add_entry_to_tab(m, "Info", "Info2");
    add_entry_to_tab(m, "Mods", "Test1");
    add_entry_to_tab(m, "Mods", "Test2");
    add_entry_to_tab(m, "Mods", "Test3");
    add_entry_to_tab(m, "Mods", "Test4");
    add_entry_to_tab_with_function(m, "Settings", "Rainbow Mode", toggleRGBMode);
    add_entry_to_tab_with_function(m, "Settings", "Rainbow Mode", toggleRGBMode);
    
}

static void destroy_menu(Menu* m){
    logInfo("Destroying menu");
    for(int i = 0; i < m->tab_count; i++){
        Tab* t = &m->tabs[i];
        if(t != NULL){
            for(int j = 0; j < t->entry_count; j++){
                Entry* e = &t->entries[j];
                if(e != NULL){
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

#endif