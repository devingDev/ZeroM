// Made by Bizzy
#ifndef GAMEMODINFO_H
#define GAMEMODINFO_H
#include <stdint.h>
// you do NOT change this file for your mod!
typedef struct {
    uint32_t version;
    char* modName;
    char* modAuthor;
    void* data;
} GameModInfo;
typedef void (*StartFunction)(void);
typedef struct {
    GameModInfo* gameModInfo;
    StartFunction startFunction;
} GameMod;


extern GameModInfo gameModInfo;
extern GameMod gameMod;


#endif