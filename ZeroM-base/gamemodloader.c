#include "gamemodloader.h"
#include "gamemod.h"
#include "menu.h"
#include "mem.h"
#include <dlfcn.h>
#include <psp2/io/dirent.h>
#include <psp2/io/fcntl.h>
#include <stdio.h>
#include <string.h>


int ends_with(const char *str, const char *suffix) {
    if (!str || !suffix)
        return 0;
    
    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);
    
    if (suffix_len > str_len){
        return 0;
    }

    return strncmp(str + str_len - suffix_len, suffix, suffix_len) == 0;
}

ZeroMData zeroMData;

typedef struct {
    void* handle;
    GameMod* (*getGameMod)(void);
} LoadedGameMod;

LoadedGameMod* loadedGameMods;
int countGameMods = 0;

void try_load_gamemod(const char* path){
    logInfo("Trying to open lib %s", path);
    void* gameModHandle = dlopen(path, 0);
	logInfo("loaded lib: 0x%08x", gameModHandle);
	if(gameModHandle == NULL){
		return;
	}
    
	GameMod* (*getGameMod)(void) = dlsym(gameModHandle, "getGameMod");
	logInfo("got getGameMod function: 0x%08x\n", getGameMod);
	if(getGameMod == NULL){
        dlclose(gameModHandle);
		return;
	}
    loadedGameMods = realloc((void*)loadedGameMods, sizeof(LoadedGameMod)* (countGameMods+1));

    loadedGameMods[countGameMods].handle = gameModHandle;
    loadedGameMods[countGameMods].getGameMod = getGameMod;
    countGameMods++;

	GameMod* loadedMod = getGameMod();
	logInfo("called getGameMod: 0x%08x\n", loadedMod);
	loadedMod->startFunction(&zeroMData);
	logInfo("called start function: 0x%08x\n", getGameMod()->startFunction);
    add_mod_entry(loadedMod);
}

void loadGameMods(){
    countGameMods = 0;
    loadedGameMods = NULL;
    SceUID dir;
    SceIoDirent dir_entry;
    char full_path[256];
    memset(&dir_entry, 0, sizeof(SceIoDirent));
    const char* path = "ux0:/zerom";
    dir = sceIoDopen(path);
    if (dir < 0) {
        logInfo("Error opening directory %s", path);
        return;
    }
    while (sceIoDread(dir, &dir_entry) > 0) {
        logInfo("%s", dir_entry.d_name);
        if (ends_with(dir_entry.d_name, ".suprx")){
            logInfo("Found gamemod: %s", dir_entry.d_name);
            sceClibSnprintf(full_path, sizeof(full_path), "%s/%s", path, dir_entry.d_name);
            try_load_gamemod(full_path);
        }
        memset(&dir_entry, 0, sizeof(SceIoDirent));
    }
    sceIoDclose(dir);


	
}
void unloadGameMods(){
    for(int i = 0; i < countGameMods; i++){
        dlclose(loadedGameMods[i].handle);
    }
    free((void*)loadedGameMods);
}
