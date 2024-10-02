#ifndef ITEM_H
#define ITEM_H
#include <stdint.h>
#include <wchar.h>


#define undefRet int
typedef undefRet (*ItemFun)(void* item);
#define undefItemFun ItemFun

typedef struct{
    undefItemFun getDefaultInstance__4ItemFv;
    undefItemFun verifyTagAfterLoad__4ItemFP11CompoundTag;
    undefItemFun GetUseTooltip__4ItemFRC21ItemTooltipDataHolder;
    undefItemFun deleteItemD2;
    undefItemFun deleteItemD0;
    undefItemFun useOn;
    undefItemFun getDestroySpeed;
    undefItemFun TestUse;
    undefItemFun use;
    undefItemFun finishUsingItem;
    undefItemFun getMaxStackSize;
    undefItemFun getLevelDataForAuxValue;
    undefItemFun hurtEnemy;
    undefItemFun mineBlock;
    undefItemFun getAttackDamage;
    undefItemFun canDestroySpecial;
    undefItemFun interactEnemy;
    undefItemFun isHandEquipped;
    undefItemFun isMirroredArt;
    undefItemFun getDescriptionId;
    undefItemFun getDescriptionIdInst;
    undefItemFun getUseDescriptionId;
    undefItemFun getUseDescriptionIdInst;
    undefItemFun shouldOverrideMultiplayerNBT;
    undefItemFun getColor;
    undefItemFun inventoryTick;
    undefItemFun onCraftedBy;
    undefItemFun isComplex;
    undefItemFun getUseAnimation;
    undefItemFun getUseDuration;
    undefItemFun releaseUsing;
    undefItemFun appendHoverText;
    undefItemFun getName;
    undefItemFun isFoil;
    undefItemFun getRarity;
    undefItemFun isEnchantable;
    undefItemFun getEnchantmentValue;
    undefItemFun mayBePlacedInAdventureMode;
    undefItemFun isValidRepairItem;
    undefItemFun getDefaultAttributeModifiers;
    undefItemFun registerIcons;
    undefItemFun hasMultipleSpriteLayers;
    undefItemFun getLayerIcon;
    undefItemFun getIconType;
    undefItemFun getIcon;
    undefItemFun getIconInst;
    undefItemFun GetArmorType;
    undefItemFun GetOverrideCount;
    undefItemFun GetOverrideCountColour;
    undefItemFun GetOverrideCountIcon;

} ItemVtable;

typedef struct{
    ItemVtable* vtbl;
    uint8_t pad[0x4 * 0x13];
    wchar_t* iconName;
    uint32_t field_0x70;

} Item;


#endif