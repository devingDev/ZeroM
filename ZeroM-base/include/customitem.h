#ifndef CUSTOMITEM_H
#define CUSTOMITEM_H

#include "item.h"


typedef struct{

}TextureAtlasVTable;
typedef struct{
    TextureAtlasVTable* vtbl;
} TextureAtlas;



void addCustomItemsTest();
void addHooksCustomItem();



#endif