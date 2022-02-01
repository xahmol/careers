// SNES support lib
// Routines for supporting the Petscii Robots userport SNES adapter
// https://texelec.com/product/snes-adapter-commodore/
//
// Based on code from:
// - The 8-Bit Guy / David Murray
//   https://www.the8bitguy.com/wp-content/uploads/2021/03/snestest.zip
// - Chris Garrett:
//   https://retrogamecoders.com/trse-snes-controller/

//Includes
#include <peekpoke.h>
#include "snes.h"

#pragma code-name ("MACO");
#pragma rodata-name ("MACO");

//Variables
struct SNES_Struct SNES;

void snes_init()
{
    // Initialize the SNES pad

    // Initialise GPIO pins
    // Set pins 3 and 5 as output

    POKE(PORTB_DIR, 0x28);          // %00101000
}

unsigned char snes_readdata()
{
    // Read data from the SNES pad

    // READ pin 6
    unsigned char pin_value;

    // Check the pin value then ping the clock
    pin_value = ((PEEK(USER_PORT) & 0x40) == 0x40)? 0:1;  // %01000000

    // Pulse the clock on pin 3
    POKE(USER_PORT, 0x08);          // %00001000
    POKE(USER_PORT, 0x00);          // %00000000

    return pin_value;
}

void snes_read()
{
    // Read buttons pressed on SNES pad

    // Test buttons pressed with testing SNES.first and SNES.second with
    // if(SNES.<<first or second>> & <<predefined mask for button )

    // Masks for SNES.first:
    // - SNES_B      
    // - SNES_Y      
    // - SNES_SELECT 
    // - SNES_START  
    // - SNES_UP    
    // - SNES_DOWN   
    // - SNES_LEFT   
    // - SNES_RIGHT
    // Masks for SNES.second:
    // - SNES_A      
    // - SNES_X      
    // - SNES_BACK_L 
    // - SNES_BACK_R 

    // Get the 12 value of the buttons on the SNES pad

    // Pulse GPIO pin 5
    POKE(USER_PORT, 0x20);          // %00100000
    POKE(USER_PORT, 0x00);          // %00000000

    // Read from the serialized data
    SNES.first   = snes_readdata()    ;  // B on bit 0 of byte 1
    SNES.first  += snes_readdata()*  2;  // Y on bit 1 of byte 1
    SNES.first  += snes_readdata()*  4;  // SELECT on bit 2 of byte 1
    SNES.first  += snes_readdata()*  8;  // START on bit 3 of byte 1
    SNES.first  += snes_readdata()* 16;  // UP on bit 4 of byte 1
    SNES.first  += snes_readdata()* 32;  // DOWN on bit 5 of byte 1
    SNES.first  += snes_readdata()* 64;  // LEFT on bit 6 of byte 1
    SNES.first  += snes_readdata()*128;  // RIGHT on bit 7 of byte 1
    SNES.second  = snes_readdata()    ;  // A on bit 0 of byte 2
    SNES.second += snes_readdata()*  2;  // X on bit 1 of byte 2
    SNES.second += snes_readdata()*  4;  // BACK_L on bit 2 of byte 2
    SNES.second += snes_readdata()*  8;  // BACK_R on bit 3 of byte 2
}