// SNES support lib
// Routines for supporting the Petscii Robots userport SNES adapter
// https://texelec.com/product/snes-adapter-commodore/
//
// Based on code from:
// - The 8-Bit Guy / David Murray
//   https://www.the8bitguy.com/wp-content/uploads/2021/03/snestest.zip
// - Chris Garrett:
//   https://retrogamecoders.com/trse-snes-controller/

#ifndef __SNES_H_
#define __SNES_H_

#define USER_PORT   0xDD01
#define PORTB_DIR   0xDD03

#define SNES_B      1
#define SNES_Y      2
#define SNES_SELECT 4
#define SNES_START  8
#define SNES_UP     16
#define SNES_DOWN   32
#define SNES_LEFT   64
#define SNES_RIGHT  128
#define SNES_A      1
#define SNES_X      2
#define SNES_BACK_L 4
#define SNES_BACK_R 8

struct SNES_Struct
{
    unsigned char first;   // B,Y,SELECT,START,UP,DOWN,LEFT,RIGHT bits
    unsigned char second;  // A,X,BACK_L,BACK_R bits
};
extern struct SNES_Struct SNES;

extern void snes_init();
extern void snes_read();

#endif // __SNES_H_