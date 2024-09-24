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

void menu_draw_hook();
void menu_draw_release_hook();
extern bool pluginReloadLoaded;
extern SceCtrlData current_pad;

#endif