#ifndef STRUCTURES_H
#define STRUCTURES_H
#include "helperfunctions.h"

typedef struct Player Player, *PPlayer;

typedef struct Player_vtbl Player_vtbl, *PPlayer_vtbl;
typedef struct Player2 Player2, *PPlayer2;

struct Player {
    struct Player_vtbl *__vftable;
    char pad00[0xC4];
    double posx1;
    double posy1;
    double posz1;
    float angleA;
    float angleB;
    char pad01[0x18];
    double posx2;
    double posy2;
    double posz2;
    double posx3;
    double posy3;
    double posz3;
    char pad02[0x18];
    float angle1;
    float angle2;
    float angle3;
    float angle4;
    float angle5;
    float angle6;

    //unsigned char extraData[0xA8C];
};
struct Player2 {
    unsigned char extraData[0xA90];
    //struct Player_vtbl *__vftable;
    //unsigned char extraData[0xA8C];
};

struct Player_vtbl { /* vtable of Player */
    int field_0;
    int field1_0x4;
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

    logInfo("0: %08X", swap(playerAdd[0x52]));


    logInfo("A: %.2f|%.2f|%.2f", *(float*)&playerAdd[0x52], *(float*)&playerAdd[0x53], *(float*)&playerAdd[0x54]);
    logInfo("B: %.2f|%.2f|%.2f", *(float*)&playerAdd[0x100], *(float*)&playerAdd[0x101], *(float*)&playerAdd[0x102]);
}

#endif