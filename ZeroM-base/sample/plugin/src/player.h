#ifndef STRUCTURES_H
#define STRUCTURES_H
#include "helperfunctions.h"

typedef struct Player Player, *PPlayer;

typedef struct Player_vtbl Player_vtbl, *PPlayer_vtbl;
typedef struct Player2 Player2, *PPlayer2;

struct Player {
    Player_vtbl *__vftable;
    char pad00[0xC4]; 
    double posx1; //0xC8
    double posy1; //0xD0
    double posz1; //0xD8
    float angleA; //0xE0
    float angleB; //0xE4
    char pad01[0x18]; //0xE8
    double posx2; //0x100
    double posy2; //0x108
    double posz2; //0x110
    double posx3; //0x118
    double posy3; //0x120
    double posz3; //0x128
    char pad02[0x18]; //0x130
    float angle1; //0x148
    float angle2; //0x14C
    float angle3; //0x150
    float angle4; //0x154
    float angle5; //0x158
    float angle6; //0x15C
    char pad03[0x60]; //0x160
    double posx4; //0x1C0
    double posy4; //0x1C8
    double posz4; //0x1D0
    char pad04[0x6F0]; //0x1D8
    double posx5; //0x8C8
    double posy5; //0x8D0
    double posz5; //0x8D8

    //unsigned char extraData[0xA8C];
}; // i think this was around 0xA90 bytes?
struct Player2 {
    unsigned char extraData[0xA90];
    //struct Player_vtbl *__vftable;
    //unsigned char extraData[0xA8C];
};

typedef struct {
    double x;
    double y;
    double z;
} Vec3;

struct Player_vtbl { /* vtable of Player */
    char pad00[0x3C]; // 0x0
    int (*kill)(Player* a1); // 0x3C , not working probably needs to be a server call?
    char pad01[0xC0]; // 0x40
    int (*moveTo)(Player* player, double x, double y, double z, double angle1, double angle2); // 0x100
    char pad02[0xC4]; // 0x104
    Vec3* (*getForward)(Player* player); // 0x1C8
    char pad03[0x138]; // 0x1CC
    int (*teleportTo)(Player* player, double x, double y, double z); // 0x304

};

static void logPlayerInfo(Player* player, int* playerAdd){
    logInfo("%llu", GetTick());
    if(player == NULL){
        logInfo("Player null");
        return;
    }
    //print_bytes(playerAdd,0x40);

    logInfo("player: %08X", (int)(int*)player);
    logInfo("playerAdd: %08X", (int)playerAdd);

    logInfo("angle1: %.4f", player->angle1);
    logInfo("angle2: %.4f", player->angle2	);
    logInfo("angle3: %.4f", player->angle3	);
    logInfo("angle4: %.4f", player->angle4	);
    logInfo("angle5: %.4f", player->angle5	);
    logInfo("angle6: %.4f", player->angle6	);
    logInfo("angleA: %.4f", player->angleA	);
    logInfo("angleB: %.4f", player->angleB	);

    logInfo("posx1: %.2f", player->posx1);
    logInfo("posy1: %.2f", player->posy1);
    logInfo("posz1: %.2f", player->posz1);

    logInfo("posx2: %.2f", player->posx2);
    logInfo("posy2: %.2f", player->posy2);
    logInfo("posz2: %.2f", player->posz2);

    logInfo("posx3: %.2f", player->posx3);
    logInfo("posy3: %.2f", player->posy3);
    logInfo("posz3: %.2f", player->posz3);
    
    logInfo("posx4: %.2f", player->posx4);
    logInfo("posy4: %.2f", player->posy4);
    logInfo("posz4: %.2f", player->posz4);
    
    logInfo("posx5: %.2f", player->posx5);
    logInfo("posy5: %.2f", player->posy5);
    logInfo("posz5: %.2f", player->posz5);

    logInfo("0: %08X", swap(playerAdd[0x52]));


    logInfo("A: %.2f|%.2f|%.2f", *(float*)&playerAdd[0x52], *(float*)&playerAdd[0x53], *(float*)&playerAdd[0x54]);
    logInfo("B: %.2f|%.2f|%.2f", *(float*)&playerAdd[0x100], *(float*)&playerAdd[0x101], *(float*)&playerAdd[0x102]);
}

#endif