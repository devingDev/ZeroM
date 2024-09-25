#ifndef MENU_H
#define MENU_H
#include <psp2/kernel/modulemgr.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/display.h>
#include <psp2/ctrl.h>
#include <psp2/power.h>
#include <taihen.h>
#include <string.h>
#include "renderer.h"
#include "log.h"
#include "structures/menuitems.h"
#include "gamemod.h"


extern bool pluginReloadLoaded;
extern SceCtrlData current_pad;

void menu_draw_hooks();
void menu_draw_release_hooks();
void menu_end();
void add_mod_entry_to_mods_tab(Menu* menu, GameMod* gameMod);
void add_mod_entry(GameMod* gameMod);
void execute_entry(); // :)
void menu_go_back();
void change_current_tab(int direction);
void change_current_entry(int direction);

Menu* GetMenuPointer();

#endif