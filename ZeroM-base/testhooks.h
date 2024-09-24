#ifndef TESTHOOKS_H
#define TESTHOOKS_H
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
#include <string.h>
#include <taihen.h>
#include <stdbool.h>
#include <locale.h>
#include <stdlib.h>
#include <wchar.h>
#include "structures/player.h"
#include "hooks.h"
#include "log.h"

void doTestHooks();

#endif