#include "testhooks.h"

#define undefined4 unsigned int
#define undefined unsigned char


tai_hook_ref_t* ServerAllocator_REF;
undefined4 ServerAllocator(undefined4 *server){
    logInfo("ServerAllocator begin: %p",server);
    undefined4 result = TAI_NEXT(ServerAllocator, *ServerAllocator_REF, server);

    return result;
}

tai_hook_ref_t* ServerDeconstructor_REF;
undefined4 * ServerDeconstructor(undefined4 *server){
    logInfo("ServerDeconstructor: %p",server);
    undefined4* result = TAI_NEXT(ServerDeconstructor, *ServerDeconstructor_REF, server);

    return result;
}
tai_hook_ref_t* ServerStarter_REF;
undefined4 * ServerStarter(undefined4 *a1){
    logInfo("ServerStarter: %p",a1);
    undefined4* result = TAI_NEXT(ServerStarter, *ServerStarter_REF, a1);
    
    return result;
}

tai_hook_ref_t* ServerVTBLConstructor_REF;
undefined4* ServerVTBLConstructor(undefined4 *server){
    logInfo("ServerVTBLConstructor begin: %p",server);
    undefined4* result = TAI_NEXT(ServerVTBLConstructor, *ServerVTBLConstructor_REF, server);
    //logInfo("ServerVTBLConstructor done: %08X",server);
    //print_bytes((void*)server, 0x120 );

    return result;
}

tai_hook_ref_t* sub_81972508_REF;
int sub_81972508(int param_1,wchar_t *param_2){
    //logInfo("sub_81972508 begin: %08X %08X",param_1, param_2);
    int result = TAI_NEXT(sub_81972508, *sub_81972508_REF, param_1, param_2);
    //logInfo("sub_81972508 done: %08X %08X",param_1, param_2);
    //print_bytes((void*)param_2, 0x10);

    return result;
}

tai_hook_ref_t* TNT_SomethingSetupSides_REF;
void TNT_SomethingSetupSides(int param_1,int *param_2){
    logInfo("TNT_SomethingSetupSides begin: %08X %p %08X",param_1, (void*)param_2, *param_2);
    print_bytes((void*)param_2, 0x40);
    TAI_NEXT(TNT_SomethingSetupSides, *TNT_SomethingSetupSides_REF, param_1, param_2);
    logInfo("TNT_SomethingSetupSides done: %08X %p %08X",param_1, (void*)param_2, *param_2);
    print_bytes((void*)param_2, 0x40);
}

tai_hook_ref_t* FUN_810c65b4_REF;
void FUN_810c65b4(){
    logInfo("FUN_810c65b4 begin %08X %08X %08X");
    TAI_NEXT(FUN_810c65b4, *FUN_810c65b4_REF);
    //logInfo("FUN_810c65b4 end %08X %08X %08X",x,y,z);
}

bool done = true;
tai_hook_ref_t* FUN_81972508_REF;
int FUN_81972508(int a1, wchar_t* a2){
    bool doing = false;
    if(!done){
        done = true;
        doing = true;
    }
    if(doing){
        logInfo("a2  %ls\n", a2); 
        logInfo("hook_func1(0x%08X, 0x%08X)\n", a1, a2); 
        
        hex_dump("hook_func1 a a1", (int*)a1, 0x50);
        hex_dump("hook_func1 a a2", a2, 0x50);
    }

    if(a2 > 0x81000000 || a2 < 0x83FFFFFF){
        //logInfo("a2  %ls\n", a2); 
    }
    int result = TAI_NEXT(FUN_81972508, *FUN_81972508_REF, a1, a2);

    if(a2 > 0x81000000 || a2 < 0x83FFFFFF){
        //logInfo("a2  %ls  %08X\n", a2, ***(char ***)a1); 
        //logInfo("a2  %ls\n", a2); 
    }

    if(doing){

        hex_dump("hook_func1 b a1", (int*)a1, 0x50);
        hex_dump("hook_func1 b a2", a2, 0x50);
        
        logInfo("hook_func1(0x%08X, 0x%08X): 0x%08X\n", a1, a2, result); 
        logInfo("a2  %ls\n", a2); 
        return result;
    }
}

tai_hook_ref_t* FUN_8189a58a_REF;
int* FUN_8189a58a(int* r1, int r2, int r3, int r4, int r5, char r6)
{
    logInfo("FUN_8189a58a(0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X)\n", r1,r2,r3,r4,r5,r6); 
/*     hex_dump("FUN_8189a58a a r1", r1, 0x50);
    hex_dump("FUN_8189a58a a r2", r2, 0x50);
    hex_dump("FUN_8189a58a a r3", r3, 0x50);
    hex_dump("FUN_8189a58a a r4", r4, 0x50);
    hex_dump("FUN_8189a58a a r5", r5, 0x50);
    hex_dump("FUN_8189a58a a r6", r6, 0x50); */
	int result = TAI_NEXT(FUN_8189a58a, *FUN_8189a58a_REF, r1, r2, r3, r4, r5, r6);
/*     hex_dump("FUN_8189a58a b r1", r1, 0x50);
    hex_dump("FUN_8189a58a b r2", r2, 0x50);
    hex_dump("FUN_8189a58a b r3", r3, 0x50);
    hex_dump("FUN_8189a58a b r4", r4, 0x50);
    hex_dump("FUN_8189a58a b r5", r5, 0x50);
    hex_dump("FUN_8189a58a b r6", r6, 0x50);
    hex_dump("FUN_8189a58a b result", result, 0x50); */
    logInfo("FUN_8189a58a(0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X): 0x%08X\n", r1,r2,r3,r4,r5,r6, result); 



    return result;
}


tai_hook_ref_t* LocalPlayer__tick_REF;
void LocalPlayer__tick(int *param_1){
	TAI_NEXT(LocalPlayer__tick, *LocalPlayer__tick_REF, param_1);
    //logInfo("LocalPlayer__tick begin %08X", param_1);
}

tai_hook_ref_t* MinecraftServer__tick_REF;
void MinecraftServer__tick(int *param_1){
	TAI_NEXT(MinecraftServer__tick, *MinecraftServer__tick_REF, param_1);
    //logInfo("MinecraftServer__tick begin %08X", param_1);
    //hex_dump("MinecraftServer__tick param_1", param_1, 0x50);
}

void doTestHooks(){
    ServerAllocator_REF = add_taiHookFunctionOffset(0x5bfde6, ServerAllocator);
    ServerDeconstructor_REF = add_taiHookFunctionOffset(0x807d22, ServerDeconstructor);
    //ServerStarter_REF = add_taiHookFunctionOffset(0x5bfde6, ServerStarter);
    ServerVTBLConstructor_REF = add_taiHookFunctionOffset(0x807b5c, ServerVTBLConstructor);
    //sub_81972508_REF = add_taiHookFunctionOffset(0x972508, sub_81972508);
    //TNT_SomethingSetupSides_REF = add_taiHookFunctionOffset(0x43dd80, TNT_SomethingSetupSides);
    FUN_810c65b4_REF = add_taiHookFunctionOffset(0x0c65b4, FUN_810c65b4);
    FUN_81972508_REF = add_taiHookFunctionOffset(0x972508, FUN_81972508);

    FUN_8189a58a_REF = add_taiHookFunctionOffset(0x89a58a, FUN_8189a58a);

    LocalPlayer__tick_REF = add_taiHookFunctionOffset(0x7edcca, LocalPlayer__tick);
    MinecraftServer__tick_REF = add_taiHookFunctionOffset(0x80a11e, MinecraftServer__tick);
    
   //taiHookFunctionOffset(&FUN_8189a58a_REF, info.modid, 0, 0x89a58a, 1, FUN_8189a58a);

}


