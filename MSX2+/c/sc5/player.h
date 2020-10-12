#ifndef __PLAYER_H__
#define __PLAYER_H__



struct TPlayer {
    int x;
    int y;
    int w;
    int h;
    int v;
    int energia;
    int color;
    int sprite;
    int plano;
};

struct TPlayer player ={
    100,
    160,
    16,
    16,
    4,
    100,
    3,
    0,
    0
};

unsigned char coche_derecha[]={
    0x00,0x00,0x00,0x00,0x00,0xFF,0x8F,0x89,
    0xFF,0x81,0xC1,0xC1,0xC1,0xFF,0x38,0x38,
    0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0x40,
    0xFE,0x01,0x01,0x01,0x01,0xFE,0x38,0x38
};
unsigned char coche_izquierda[]={
    0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x02,
    0x7F,0x80,0x80,0x80,0x80,0x7F,0x1C,0x1C,
    0x00,0x00,0x00,0x00,0x00,0xFF,0xF1,0x91,
    0xFF,0x81,0x83,0x83,0x83,0xFF,0x1C,0x1C
};


// colores
/*
unsigned char color_coche_derecha[]={
}
unsigned char color_coche_izquierda[]={
}
*/
#endif