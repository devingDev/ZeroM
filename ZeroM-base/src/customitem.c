#include "customitem.h"
#include <taihen.h>
#include "hooks.h"


void addCustomItemsTest(){

}


// add item test
tai_hook_ref_t* MinecraftWorld_RunStaticCtors_ref;
void MinecraftWorld_RunStaticCtors(void){
	TAI_NEXT(MinecraftWorld_RunStaticCtors, *MinecraftWorld_RunStaticCtors_ref);
	logInfo("MinecraftWorld_RunStaticCtors");
}
tai_hook_ref_t* TextureAtlas__loadUVs_ref;
void TextureAtlas__loadUVs(int* atlasAddr){
	TAI_NEXT(TextureAtlas__loadUVs, *TextureAtlas__loadUVs_ref, atlasAddr);
	logInfo("TextureAtlas__loadUVs %08X", atlasAddr);
}

void addHooksCustomItem(){
    
	MinecraftWorld_RunStaticCtors_ref = add_taiHookFunctionOffset(0x2c904a, MinecraftWorld_RunStaticCtors);
	TextureAtlas__loadUVs_ref = add_taiHookFunctionOffset(0x89b47a, TextureAtlas__loadUVs);
}
