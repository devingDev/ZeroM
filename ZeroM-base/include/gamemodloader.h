#ifndef GAMEMODLOADER_H
#define GAMEMODLOADER_H
#include "player.h"
void loadGameMods();
void unloadGameMods();
void setPlayer(Player* player);
extern int countGameMods;
#endif