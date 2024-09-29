#ifndef NAVIGATION_H
#define NAVIGATION_H
#include <psp2common/ctrl.h>
#include <taihen.h>
#include "menu.h"
#include "log.h"

void doNavigation(Menu* menu);

void navigation_hooks();
void navigation_release_hooks();

#endif