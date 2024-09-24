#ifndef MENUTITEMS_H
#define MENUTITEMS_H
#include <psp2/kernel/clib.h> 
#include "renderer.h"
#include "log.h"

#define FONT_VERT_DIST 20

#define MAX_ENTRIES_PER_TAB 10
#define MAX_TABS 5
#define MAX_NAME_LENGTH 128

typedef void (*EntryFunction)(void);

typedef struct {
    char name[MAX_NAME_LENGTH];
    EntryFunction func;
    bool enabled;
} Entry;

typedef struct {
    char name[MAX_NAME_LENGTH];
    Entry entries[MAX_ENTRIES_PER_TAB];
    int entry_count; 
    int current_selected_entry;
} Tab;

typedef struct {
    Tab tabs[MAX_TABS];
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
        Tab* tab = &menu->tabs[menu->tab_count++];
        sceClibStrncpy(tab->name, tab_name, sceClibStrnlen(tab_name,MAX_NAME_LENGTH));
        tab->entry_count = 0;
        tab->current_selected_entry = 0;
    } else {
        
    }
}

static void add_entry_to_tab(Menu* menu, const char* tab_name, const char* entry_name) {
    for (int i = 0; i < menu->tab_count; ++i) {
        Tab* tab = &menu->tabs[i];
        if (sceClibStrcmp(tab->name, tab_name) == 0) {
            if (tab->entry_count < MAX_ENTRIES_PER_TAB) {
                Entry* entry = &tab->entries[tab->entry_count++];

                size_t entry_length = sceClibStrnlen(entry_name, MAX_NAME_LENGTH);
                if (entry_length < MAX_NAME_LENGTH) {
                    sceClibStrncpy(entry->name, entry_name, entry_length);
                    entry->name[entry_length] = '\0'; 
                } else {
                    sceClibStrncpy(entry->name, entry_name, MAX_NAME_LENGTH - 1);
                    entry->name[MAX_NAME_LENGTH - 1] = '\0'; 
                }
                entry->enabled = false;
            } else {
            }
            return;
        }
    }
}

static void add_entry_to_tab_with_function(Menu* menu, const char* tab_name, const char* entry_name, EntryFunction func) {
    for (int i = 0; i < menu->tab_count; ++i) {
        Tab* tab = &menu->tabs[i];
        if (sceClibStrcmp(tab->name, tab_name) == 0) {
            if (tab->entry_count < MAX_ENTRIES_PER_TAB) {
                Entry* entry = &tab->entries[tab->entry_count++];

                size_t entry_length = sceClibStrnlen(entry_name, MAX_NAME_LENGTH);
                if (entry_length < MAX_NAME_LENGTH) {
                    sceClibStrncpy(entry->name, entry_name, entry_length);
                    entry->name[entry_length] = '\0'; 
                } else {
                    sceClibStrncpy(entry->name, entry_name, MAX_NAME_LENGTH - 1);
                    entry->name[MAX_NAME_LENGTH - 1] = '\0'; 
                }
                entry->func = func;
                entry->enabled = false;
            } else {
            }
            return;
        }
    }
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

#endif