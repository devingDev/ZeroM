#include "testhooks.h"

#define undefined4 int


tai_hook_ref_t* ServerAllocator_REF;
undefined4 ServerAllocator(undefined4 *server){
    logInfo("ServerAllocator: %08X",server);
    TAI_NEXT(ServerAllocator, *ServerAllocator_REF, server);
}

tai_hook_ref_t* ServerDeconstructor_REF;
undefined4 * ServerDeconstructor(undefined4 *server){
    logInfo("ServerDeconstructor: %08X",server);
    TAI_NEXT(ServerDeconstructor, *ServerDeconstructor_REF, server);
}
tai_hook_ref_t* ServerStarter_REF;
undefined4 * ServerStarter(undefined4 *a1){
    logInfo("ServerStarter: %08X",a1);
    TAI_NEXT(ServerStarter, *ServerStarter_REF, a1);
}

void doTestHooks(){
    ServerAllocator_REF = add_taiHookFunctionOffset(0x5bfde6, ServerAllocator);
    ServerDeconstructor_REF = add_taiHookFunctionOffset(0x807d22, ServerDeconstructor);
    ServerStarter_REF = add_taiHookFunctionOffset(0x5bfde6, ServerStarter);

}


