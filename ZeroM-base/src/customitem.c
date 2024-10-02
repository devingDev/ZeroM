#include "customitem.h"
#include <taihen.h>
#include "hooks.h"
#include "item.h"
#include "resourcelocation.h"


void addCustomItemsTest(){

}


void (*ResourceLocationCreate)(ResourceLocation* loc, wchar_t* str1, wchar_t* str2) = NULL;
void ResourceLocationCreateHelper(ResourceLocation* loc, wchar_t* str1, wchar_t* str2){
	ResourceLocationCreate(loc, str1, str2);
    //code::Func<void, 0x810706, ResourceLocation*, const mstd::wstring&, const mstd::wstring&>()(this, str1, str2);
}

void (*registerItem)(int, const ResourceLocation* loc, Item* Item) = NULL;
static void registerItemHelper(int id, const ResourceLocation* loc, Item* item) {
	registerItem(id, loc, item);
	//code::Func<void, 812244E4, int, const ResourceLocation&, Item*>()(id, loc, item);
}

// add item test
tai_hook_ref_t* MinecraftWorld_RunStaticCtors_ref;
void MinecraftWorld_RunStaticCtors(void){
	logInfo("MinecraftWorld_RunStaticCtors begin");
	TAI_NEXT(MinecraftWorld_RunStaticCtors, *MinecraftWorld_RunStaticCtors_ref);


	ResourceLocation loc;
	ResourceLocationCreate(&loc, L"modded", L"custom_item");
	Item item;
	int ret = module_get_offset(info.modid, 0, (0xD21F00), &item.vtbl);
	logInfo("item vtbl %08X ", item.vtbl);
	item.iconName = L"custom_texture_name";

	registerItemHelper(1, &loc, &item);


    //mc::ResourceLocation loc(L"modded", L"custom_item");
    //mc::TestItem* testItem = new mc::TestItem();
	//testItem->iconName            = L"custom_texture_name"; //sets the custom item's texture to your custom icon
    
    // Set Item Id to 1, so we can get it from the Creative Inventory, see AddCreativeMenuItem.h to use a custom ID
    //mc::Item::registerItem(1, loc, testItem);

	
	logInfo("MinecraftWorld_RunStaticCtors   end");
}



TextureAtlas* AtlasPTRs[2];
int currentAtlas = 0;
//typedef int (*function_t)(TextureAtlas* textureAtlas, uint32_t unknown, uint32_t x, uint32_t y, wchar_t * iconName);
//function_t TextureAtlas__addIcon;

void (* TextureAtlas__addIcon)(TextureAtlas* textureAtlas, uint32_t unknown, uint32_t x, uint32_t y, wchar_t * iconName) = NULL;
void addIconHelper(TextureAtlas* textureAtlas, uint32_t x, uint32_t y, wchar_t * iconName){
	TextureAtlas__addIcon(textureAtlas, 0, x, y, iconName);
}

tai_hook_ref_t* TextureAtlas__loadUVs_ref;
void TextureAtlas__loadUVs(int* atlasAddr){
	logInfo("TextureAtlas__loadUVs begin %08X", atlasAddr);
	TAI_NEXT(TextureAtlas__loadUVs, *TextureAtlas__loadUVs_ref, atlasAddr);


	AtlasPTRs[currentAtlas] = (TextureAtlas*)atlasAddr;
	currentAtlas++;

	if(currentAtlas == 2){
		addIconHelper(AtlasPTRs[1], 6, 16, L"custom_texture_name");
	}

	logInfo("TextureAtlas__loadUVs   end %08X", atlasAddr);
}

void addHooksCustomItem(){
	int ret = module_get_offset(info.modid, 0, (0x89A2F8|1), &TextureAtlas__addIcon);
	ret = module_get_offset(info.modid, 0, (0x810706|1), &ResourceLocationCreate);
	ret = module_get_offset(info.modid, 0, (0x2244E4|1), &registerItem);

	//MinecraftWorld_RunStaticCtors_ref = add_taiHookFunctionOffset(0x2C904A, MinecraftWorld_RunStaticCtors);
	//TextureAtlas__loadUVs_ref = add_taiHookFunctionOffset(0x89B47A, TextureAtlas__loadUVs);
}
