#ifndef __PLAYER_H__
#define __PLAYER_H__



struct TPlayer {
    int8 x;
    int8 y;
    int8 w;
    int8 h;
    int8 v;
    int8 energia;
    int8 color;
    int8 sprite;
    int8 plano;
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
#endif