// Made by Bizzy
#ifndef GAMEMODINFO_H
#define GAMEMODINFO_H
#include <stdint.h>
#include "menuitems.h"

// you do NOT change this file for your mod!
typedef struct {
    void* Player; // Should hold original player struct/class pointer
    void* Server; // same for server
} ZeroMData;
typedef struct {
    uint32_t version;
    char* modName;
    char* modAuthor;
    void* data;
} GameModInfo;
typedef void (*StartFunction)(ZeroMData* zeroMData);
typedef struct {
    Tab* tabs;
    int tab_count;
    int current_shown_tab;
    GameModInfo* gameModInfo;
    StartFunction startFunction;
} GameMod;


extern GameModInfo gameModInfo;
extern GameMod gameMod;


#endif