#ifndef MENUTITEMS_H
#define MENUTITEMS_H
#include <psp2/kernel/clib.h> 
#include <stdbool.h>

#define FONT_VERT_DIST 20

#define MAX_ENTRIES_PER_TAB 100
#define MAX_TABS 10
#define MAX_NAME_LENGTH 128
#define MOD_TAB_NAME "Mods"

typedef void (*EntryFunction)(void*);

typedef struct {
    char* name;
    EntryFunction func;
    void* funcArg;
    bool enabled;
    bool isModEntry;
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









static void add_tab(Menu* menu, const char* tab_name) {

    if (menu->tab_count < MAX_TABS) {
        menu->tabs = (Tab*)realloc((void*)menu->tabs, sizeof(Tab) * (menu->tab_count+1));
        
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

static void add_tab_direct(Tab* tab, const char* tab_name) {
    SceSize strLength = sceClibStrnlen(tab_name, MAX_NAME_LENGTH);
    tab->name = (char*)calloc(strLength+1, sizeof(char));
    sceClibStrncpy(tab->name, tab_name, strLength);
    tab->entry_count = 0;
    tab->current_selected_entry = 0;
    tab->entries = NULL;
}
static void add_entry_direct(Entry* entry, const char* entry_name, EntryFunction func) {
    SceSize entry_length = sceClibStrnlen(entry_name, MAX_NAME_LENGTH);
    entry->name = (char*)malloc((entry_length+1)* sizeof(char));
    sceClibStrncpy(entry->name, entry_name, entry_length);
    entry->name[entry_length] = '\0'; 
    entry->enabled = false;
    entry->func = func;
    entry->isModEntry = false;
}

static void add_entry_to_tab_with_function(Menu* menu, const char* tab_name, const char* entry_name, EntryFunction func) {
    for (int i = 0; i < menu->tab_count; ++i) {
        Tab* tab = &menu->tabs[i];
        if (sceClibStrcmp(tab->name, tab_name) == 0) {
            if (tab->entry_count < MAX_ENTRIES_PER_TAB) {
                tab->entries = (Entry*)realloc((void*)tab->entries, sizeof(Entry) * (tab->entry_count+1));
                

                Entry* entry = &tab->entries[tab->entry_count];
                entry->enabled = false;

                SceSize entry_length = sceClibStrnlen(entry_name, MAX_NAME_LENGTH);
                entry->name = (char*)malloc((entry_length+1)* sizeof(char));
                sceClibStrncpy(entry->name, entry_name, entry_length);
                entry->name[entry_length] = '\0'; 
                entry->enabled = false;
                entry->func = func;
                entry->isModEntry = false;
                tab->entry_count++;
            }
            return;
        }
    }
}
static void add_entry_to_tab(Menu* menu, const char* tab_name, const char* entry_name) {
    add_entry_to_tab_with_function(menu, tab_name, entry_name, NULL);
}




#endif