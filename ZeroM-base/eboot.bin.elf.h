
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

