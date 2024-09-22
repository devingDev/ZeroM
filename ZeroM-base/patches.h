#ifndef PATCHES_H
#define PATCHES_H
#include <psp2/kernel/clib.h>
#include <psp2/kernel/modulemgr.h>
#include <psp2common/kernel/threadmgr.h> 
#include <psp2/kernel/threadmgr.h> 
#include <psp2/io/fcntl.h>
#include <psp2/io/stat.h>
#include <psp2/registrymgr.h>
#include <psp2/system_param.h>
#include <psp2/kernel/rng.h> 
#include <psp2/power.h>
#include <psp2/ctrl.h>
#include <psp2kern/kernel/sysclib.h> 
#include <string.h>
#include <taihen.h>
#include <stdbool.h>
#include <stdlib.h>
#include "structures.h"
#include "log.h"
#include "testhooks.h"
#include "hooks.h"

void doPatches();

#endif