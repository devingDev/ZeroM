#ifndef HOOKS_H
#define HOOKS_H
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
#include <stdlib.h>
#include "structures/player.h"
#include "log.h"
#include "testhooks.h"

#define TAI_NEXT(this_func, hook, ...) ({ \
  (((struct _tai_hook_user *)hook)->next) != 0 ? \
    ((__typeof__(&this_func))((struct _tai_hook_user *)((struct _tai_hook_user *)hook)->next)->func)(__VA_ARGS__) \
  : \
    ((__typeof__(&this_func))((struct _tai_hook_user *)hook)->old)(__VA_ARGS__) \
  ; \
})




#define TOTAL_HOOKS 32
extern tai_hook_ref_t hook_refs[TOTAL_HOOKS];
extern SceUID hooks[TOTAL_HOOKS];
extern int currentHooks;
extern tai_module_info_t info;
extern int activeMenu;


void prepareHooking();
void setupHooks();
void unhook();
tai_hook_ref_t* add_taiHookFunctionOffsetThumb(uint32_t offset, const void * hook_func, int thumb);
tai_hook_ref_t* add_taiHookFunctionOffset(uint32_t offset, const void * hook_func);



int module_get_offset(int uid, int seg, uint32_t in_off, void *out_off);
uint64_t GetTick();
uint32_t swap(uint32_t in);

extern int* playerAdd;
extern Player* player;
extern Player* playerCaught;

void Player_Tick_patched(Player *playerF);
void Livingent_Tick_patched(int *param_1);
int  CreateServerPlayer_patched(Player* playerAllocated, int a2, int *a3, int a4, int a5);






#endif