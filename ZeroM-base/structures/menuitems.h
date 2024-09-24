#ifndef MENUTITEMS_H
#define MENUTITEMS_H
#include <psp2/kernel/clib.h> 
#include "renderer.h"
#include "log.h"

#define FONT_VERT_DIST 20

#define MAX_ENTRIES_PER_TAB 10
#define MAX_TABS 5
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    
} Entry;

typedef struct {
    char name[MAX_NAME_LENGTH];
    Entry entries[MAX_ENTRIES_PER_TAB];
    int entry_count; 
} Tab;

typedef struct {
    Tab tabs[MAX_TABS];
    int tab_count;
    int current_shown_tab;
} Menu;

extern Menu menu;

static void change_current_tab(Menu* menu, int direction) {
    if(direction > 0){
        if(menu->current_shown_tab < menu->tab_count){
            menu->current_shown_tab++;
        }
    }else{
        if(menu->current_shown_tab > 0){
            menu->current_shown_tab--;
        }
    }
    
}

static void add_tab(Menu* menu, const char* tab_name) {
    if (menu->tab_count < MAX_TABS) {
        Tab* tab = &menu->tabs[menu->tab_count++];
        sceClibStrncpy(tab->name, tab_name, sceClibStrnlen(tab_name,MAX_NAME_LENGTH));
        tab->entry_count = 0;
    } else {
        
    }
}

static void add_entry_to_tab(Menu* menu, const char* tab_name, const char* entry_name) {
    for (int i = 0; i < menu->tab_count; ++i) {
        Tab* tab = &menu->tabs[i];
        if (sceClibStrcmp(tab->name, tab_name) == 0) {
            if (tab->entry_count < MAX_ENTRIES_PER_TAB) {
                Entry* entry = &tab->entries[tab->entry_count++];
                sceClibStrncpy(entry->name, entry_name, sceClibStrnlen(entry_name,MAX_NAME_LENGTH));
            } else {
                
            }
            return;
        }
    }
    
}

static void display_menu(const Menu* menu) {
    int x = 5;
    int y = 35;
    const Tab* tab = &menu->tabs[menu->current_shown_tab];
    drawStringF(x, y, "%s\n", tab->name);
    for (int j = 0; j < tab->entry_count; ++j) {
        const Entry* entry = &tab->entries[j];
        drawStringF(x, y+(j+1)*FONT_VERT_DIST, "  %s\n", entry->name);
    }
}

#endif