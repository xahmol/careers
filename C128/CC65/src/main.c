/*
CAREERS
Written in 1992, 2022 by Xander Mol

# https://github.com/xahmol/careers
# https://www.idreamtin8bits.com/

Originally written in 1992 in Commodore BASIC 7.0 for the Commodore 128
Rewritten for C128 in C using CC65 in 2022

Code and resources from others used:

-   CC65 cross compiler:
    https://cc65.github.io/

-   C128 Programmers Reference Guide: For the basic VDC register routines and VDC code inspiration
    http://www.zimmers.net/anonftp/pub/cbm/manuals/c128/C128_Programmers_Reference_Guide.pdf

-   Scott Hutter - VDC Core functions inspiration:
    https://github.com/Commodore64128/vdc_gui/blob/master/src/vdc_core.c
    (used as starting point, but channged to inline assembler for core functions, added VDC wait statements and expanded)

-   Francesco Sblendorio - Screen Utility: used for inspiration:
    https://github.com/xlar54/ultimateii-dos-lib/blob/master/src/samples/screen_utility.c

-   DevDef: Commodore 128 Assembly - Part 3: The 80-column (8563) chip
    https://devdef.blogspot.com/2018/03/commodore-128-assembly-part-3-80-column.html

-   6502.org: Practical Memory Move Routines: Starting point for memory move routines
    http://6502.org/source/general/memory_move.html

-   Anthony Beaucamp - 8Bit Unity: Starting point for SID play routines
    https://github.com/8bit-Dude/8bit-Unity/blob/main/unity/targets/c64/SID.s

-   Bart van Leeuwen: For inspiration and advice while coding.
    Also for providing the excellent Device Manager ROM to make testing on real hardware very easy

-   Original windowing system code on Commodore 128 by unknown author.

-   Music credits:

    
-   Tooling to transfer original Commodore software code: "
    VICE by VICE authors
    DirMaster by The Wiz/Elwix
    CharPad Free by Subchrist software
    UltimateII+ cartridge by Gideon Zweijtzer
    
-   Tested using real hardware (C128D and C128DCR) plus VICE.

The code can be used freely as long as you retain
a notice describing original source and author.

THE PROGRAMS ARE DISTRIBUTED IN THE HOPE THAT THEY WILL BE USEFUL,
BUT WITHOUT ANY WARRANTY. USE THEM AT YOUR OWN RISK!
*/

//Includes
#include <stdio.h>
#include <string.h>
#include <peekpoke.h>
#include <cbm.h>
#include <conio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <device.h>
#include <accelerator.h>
#include <c128.h>
#include <time.h>
#include <joystick.h>
#include "vdc_core.h"
#include "sidplay.h"
#include "snes.h"
#include "defines.h"
#include "ring1.h"
#include "ring2.h"
#include "ring3.h"
#include "ring4.h"
#include "career1.h"
#include "career2.h"
#include "menu1.h"
#include "menu2.h"
#include "menu3.h"

// Overlay data
struct OverlayStruct overlaydata[9];
unsigned char overlay_active = 0;

//Window data
struct WindowStruct Window[9];

unsigned int windowaddress = WINDOWBASEADDRESS;
unsigned char windownumber = 0;

//Menu data
unsigned char menubaroptions = 5;
unsigned char pulldownmenunumber = 9;
char menubartitles[5][12] = {"Game","Disc","Music","Cards","Information"};
unsigned char menubarcoords[5] = {1,6,11,17,23};
unsigned char pulldownmenuoptions[11] = {3,3,3,3,5,2,2,4,4,4,5};
char pulldownmenutitles[11][5][17] = {
    {"Throw dice",
     "Restart   ",
     "Stop      "},
    {"Save game   ",
     "Load game   ",
     "Autosave off"},
    {"Next   ",
     "Stop   ",
     "Restart"},
    {"Show cards      ",
     "Play opportunity",
     "Play experience "},
    {"Field info   ",
     "Game score   ",
     "Color legend ",
     "Explore board",
     "Credits      "},
    {"Yes",
     "No "},
    {"Continue",
     "Stop    "},
    {"  2.000",
     "  8.000",
     " 16.000",
     "Nothing"},
    {"  4.000",
     "  8.000",
     " 12.000",
     "Nothing"},
    {"Law        ",
     "Medicine   ",
     "Science    ",
     "Engineering"},
    {"Autosave       ",
     "Slot 1: Empty  ",
     "Slot 2: Empty  ",
     "Slot 3: Empty  ",
     "Slot 4: Empty  "}
};

// Global variables
unsigned char bootdevice;
char DOSstatus[40];
char buffer[81];
char version[22];

char updownenter[4] = {C_DOWN,C_UP,C_ENTER,0};
char leftright[3] = {C_LEFT,C_RIGHT,0};
char alldirections[6] = {C_DOWN,C_UP,C_ENTER,C_LEFT,C_RIGHT,0};

unsigned char musicnumber = 1;
unsigned char joyinterface = 0;
unsigned char autosavetoggle = 1;

// Game variables

// Board, cards and careers data
struct RingStruct ring[32] =
{
    {99,51,VDC_LCYAN  , 1},{87,51,VDC_DYELLOW, 2},{75,51,VDC_LPURPLE, 3},
    {63,51,VDC_DYELLOW, 2},{51,51,VDC_WHITE  , 4},{39,51,VDC_DYELLOW, 2},
    {27,51,VDC_LPURPLE, 5},{15,51,VDC_WHITE  , 6},{ 3,51,VDC_LCYAN  , 7},
    { 3,45,VDC_DYELLOW, 2},{ 3,39,VDC_LPURPLE, 8},{ 3,33,VDC_WHITE  , 9},
    { 3,27,VDC_DYELLOW, 2},{ 3,21,VDC_LPURPLE,10},{ 3,15,VDC_WHITE  ,11},
    { 3, 9,VDC_DYELLOW, 2},{ 3, 3,VDC_LCYAN  ,12},{15, 3,VDC_DYELLOW, 2},
    {27, 3,VDC_LPURPLE,13},{39, 3,VDC_WHITE  ,14},{51, 3,VDC_DYELLOW, 2},
    {63, 3,VDC_LPURPLE,15},{75, 3,VDC_WHITE  ,16},{87, 3,VDC_DYELLOW, 2},
    {99, 3,VDC_LCYAN  ,17},{99, 9,VDC_DYELLOW, 2},{99,15,VDC_LPURPLE,18},
    {99,21,VDC_WHITE  ,19},{99,27,VDC_DYELLOW, 2},{99,33,VDC_LPURPLE,20},
    {99,39,VDC_WHITE  ,21},{99,45,VDC_LPURPLE,22} 
};

struct CareerStruct career[8] =
{
    { 9, 6,"Farming"            , 5},
    { 7,11,"College"            , 8},
    {11,13,"Business"           ,12},
    { 9,18,"Going to sea"       ,15},
    {11,21,"Politics"           ,20},
    { 9,26,"Hollywood"          ,23},
    {11,29,"Uranium prospecting",28},
    {13, 2,"Moon expedition"    ,31},
};

struct CareerfieldStruct careerfield[8][14] =
{
    {
        {49,47,VDC_LRED   ,0, 1, 2, 0},
        {49,44,VDC_WHITE  ,0, 2, 1, 0},
        {49,41,VDC_LRED   ,0, 1, 2, 0},
        {49,38,VDC_LGREEN ,0, 3, 1, 0},
        {43,38,VDC_LYELLOW,0, 4, 2, 4},
        {37,38,VDC_LRED   ,0, 1, 6, 0},
        {37,41,VDC_LGREEN ,0, 5, 5, 0},
        {37,44,VDC_LRED   ,0, 1, 2, 0},
        {37,47,VDC_WHITE  ,0, 6, 0, 0}
    },  
    {  
        {19,47,VDC_LRED   ,0, 1, 4, 0},
        {19,44,VDC_WHITE  ,0, 7, 0, 0},
        {25,44,VDC_LRED   ,0, 1, 2, 0},
        {25,41,VDC_LRED   ,0, 1, 2, 0},
        {25,38,VDC_WHITE  ,0, 9, 2, 0},
        {19,38,VDC_LYELLOW,0, 8, 6, 0},
        {13,38,VDC_WHITE  ,0, 9, 2, 0}
    }, 
    { 
        {13,32,VDC_WHITE  ,0, 2, 1, 0},
        {19,32,VDC_WHITE  ,0, 9, 1, 0},
        {25,32,VDC_LGREEN ,0,10, 1, 0},
        {31,32,VDC_WHITE  ,0, 7, 0, 0},
        {31,29,VDC_LGREEN ,0, 5, 2, 0},
        {31,26,VDC_LGREEN ,0,10, 2, 0},
        {31,23,VDC_WHITE  ,0, 2, 1, 0},
        {25,23,VDC_LRED   ,0, 1, 4, 0},
        {19,23,VDC_WHITE  ,0,11, 0, 0},
        {19,26,VDC_WHITE  ,0,12, 0, 0},
        {13,26,VDC_LGREEN ,0,10, 3, 0}
    },
    {
        {13,17,VDC_WHITE  ,0,13, 0, 0},
        {19,17,VDC_LRED   ,0, 1, 2, 0},
        {25,17,VDC_WHITE  ,0, 9, 2, 0},
        {31,17,VDC_WHITE  ,0, 2, 1, 0},
        {31,14,VDC_LGREEN ,0, 3, 1, 0},
        {31,11,VDC_LRED   ,0, 1, 4, 0},
        {25,11,VDC_LRED   ,0, 1, 6, 0},
        {19,11,VDC_WHITE  ,0, 7, 0, 0},
        {19, 8,VDC_LRED   ,0, 1, 8, 0}
    },
    {
        {43, 8,VDC_WHITE  ,0,11, 0, 0},
        {43,11,VDC_WHITE  ,0, 9, 2, 0},
        {43,14,VDC_LYELLOW,0, 8, 4, 0},
        {43,17,VDC_LRED   ,0, 1, 2, 0},
        {49,17,VDC_WHITE  ,0, 2, 2, 0},
        {55,17,VDC_LYELLOW,0, 8, 6, 0},
        {61,17,VDC_LYELLOW,0, 4, 2, 4},
        {61,14,VDC_LYELLOW,0, 8, 8, 0},
        {61,11,VDC_LYELLOW,0,14, 4, 5},
        {55,11,VDC_WHITE  ,0,15, 0, 0},
        {55, 8,VDC_LYELLOW,0, 8,12, 0}
    },
    {
        {73, 8,VDC_LYELLOW,0, 8, 2, 0},
        {73,11,VDC_WHITE  ,0, 2, 1, 0},
        {73,14,VDC_WHITE  ,0, 9, 2, 0},
        {73,17,VDC_LYELLOW,0, 4, 6, 2},
        {79,17,VDC_LGREEN ,0,10, 1, 0},
        {85,17,VDC_WHITE  ,0,12, 0, 0},
        {85,14,VDC_LYELLOW,0,16,10, 0},
        {85,11,VDC_LGREEN ,0,17, 1, 0},
        {91,11,VDC_LYELLOW,0, 8,12, 0}
    },
    {
        {91,23,VDC_LRED   ,0, 1, 2, 0},
        {85,23,VDC_WHITE  ,0,18, 0, 0},
        {79,23,VDC_WHITE  ,0,19, 2, 0},
        {73,23,VDC_LRED   ,0, 1, 2, 0},
        {73,26,VDC_WHITE  ,0, 2, 2, 0},
        {73,29,VDC_LRED   ,0, 1, 4, 0},
        {73,32,VDC_WHITE  ,0,13, 0, 0},
        {79,32,VDC_LGREEN ,0, 5,10, 0},
        {85,32,VDC_LYELLOW,0, 4, 2, 4},
        {85,29,VDC_LRED   ,0, 1, 6, 0},
        {91,29,VDC_LGREEN ,0, 5,20, 0}
    },
    {
        {91,38,VDC_LRED   ,0, 1, 2, 0},
        {85,38,VDC_LYELLOW,0, 8, 6, 0},
        {79,38,VDC_WHITE  ,0,21, 0, 0},
        {73,38,VDC_WHITE  ,0,20, 0, 0},
        {67,38,VDC_LYELLOW,0, 4, 2, 4},
        {61,38,VDC_LGREEN ,0,10, 2, 0},
        {61,41,VDC_WHITE  ,0, 2, 2, 0},
        {61,44,VDC_LYELLOW,0, 8,16, 0},
        {67,44,VDC_LRED   ,0, 1,10, 0},
        {73,44,VDC_LGREEN ,0, 5,10, 0},
        {79,44,VDC_LYELLOW,0,22,10, 0},
        {85,44,VDC_LYELLOW,0, 4, 6, 4},
        {85,47,VDC_LGREEN, 0, 5, 5, 0}
    }
};

struct OpportunitycardStruct opportunitycard[15] =
{
    { 0, 8, 2},{ 0, 4, 2},{ 0, 7, 2},{ 0, 3, 3},{ 0, 6, 2},{ 0, 0, 2},
    { 0, 9, 2},{ 0, 1, 3},{ 0, 5, 2},{ 1, 5, 1},{ 1, 7, 1},{ 0, 2, 3},
    { 1, 6, 1},{ 1, 4, 1},{ 1, 8, 1}
};

//Pawn, field and dice graphics string data
char dicegraphics[6][3][4] = {
    {{0xA0,0xA0,0xA0,0x61} , {0xA0,0xFC,0xA0,0x61} , {0xE2,0xE2,0xE2,0x7E}},
    {{0xEC,0xA0,0xA0,0x61} , {0xA0,0xA0,0xEC,0x61} , {0xE2,0xE2,0xE2,0x7E}},
    {{0xEC,0xA0,0xA0,0x61} , {0xA0,0xFC,0xEC,0x61} , {0xE2,0xE2,0xE2,0x7E}},
    {{0xEC,0xA0,0xEC,0x61} , {0xEC,0xA0,0xEC,0x61} , {0xE2,0xE2,0xE2,0x7E}},
    {{0xEC,0xA0,0xEC,0x61} , {0xEC,0xFC,0xEC,0x61} , {0xE2,0xE2,0xE2,0x7E}},
    {{0xEC,0xEC,0xEC,0x61} , {0xEC,0xEC,0xEC,0x61} , {0xE2,0xE2,0xE2,0x7E}}
};

char pawngraphics[3][3] = {
    {0x85,0x86,0x87} , {0x88,0xA0,0x89} , {0x8A,0x8B,0x8C}
};

// Player and game data
struct PlayerdataStruct player[4];

unsigned char whichcard[19];         //wc(x)
unsigned char cardreset[15] = {2,2,2,3,2,2,2,3,2,1,1,3,1,1,1};
unsigned char fieldinformation = 0;  //ai
unsigned char gameendflag;           // es
unsigned char anotherturn;           // ne
unsigned char playerturn;            // bs
unsigned char waitkeyflag;
unsigned char paidforleave;
unsigned char resetflag =0;
unsigned char dice_double;           // dd
unsigned char dice_total;            // dg

unsigned char choice;
unsigned char xoffset = 28;
unsigned char yoffset = 31;

/* General functions */
unsigned char dosCommand(const unsigned char lfn, const unsigned char drive, const unsigned char sec_addr, const char *cmd)
{
    // Send DOS command
    // based on version DraCopy 1.0e, then modified.
    // Created 2009 by Sascha Bader.

    int res;
    if (cbm_open(lfn, drive, sec_addr, cmd) != 0)
    {
        return _oserror;
    }

    if (lfn != 15)
    {
        if (cbm_open(15, drive, 15, "") != 0)
        {
            cbm_close(lfn);
            return _oserror;
        }
    }

    DOSstatus[0] = 0;
    res = cbm_read(15, DOSstatus, sizeof(DOSstatus));

    if(lfn != 15)
    {
      cbm_close(15);
    }
    cbm_close(lfn);

    if (res < 1)
    {
        return _oserror;
    }

    return (DOSstatus[0] - 48) * 10 + DOSstatus[1] - 48;
}

unsigned int cmd(const unsigned char device, const char *cmd)
{
    // Prepare DOS command
    // based on version DraCopy 1.0e, then modified.
    // Created 2009 by Sascha Bader.
    
    return dosCommand(15, device, 15, cmd);
}

void initoverlay()
{
    unsigned char x;
    unsigned int address=OVERLAYBANK0;
    unsigned char destbank=3;

    for(x=0;x<OVERLAYNUMBER;x++)
    {
        // Compose filename
        sprintf(buffer,"careers.ovl%u",x+1);

        // Load overlay file, exit if not found
        if (cbm_load (buffer, bootdevice, NULL) == 0)
        {
            printf("\nLoading overlay file failed\n");
            exit(1);
        }

        // Copy to overlay storage memory location
        overlaydata[x].bank=destbank;

        gotoxy(0,x);
        cprintf("Overlay %u: Bank %u Adress: %4X",x+1,destbank-3,address);

        if(destbank)
        {
            BankMemCopy(OVERLAYLOAD,2,address,destbank-1,OVERLAYSIZE);
            overlaydata[x].address=address;
            address+=OVERLAYSIZE;
            if(destbank==3)
            {
                if(address<OVERLAYBANK0 || address>0xEFFF)
                {
                    address=LOADSAVEBUFFER;
                    destbank=4;
                }
            }
            else
            {
                if(address<LOADSAVEBUFFER || address>0xEFFF)
                {
                    destbank=0;
                }
            }
        }

        cprintf(" Succes Bank %u Adress: %4X",overlaydata[x].bank-3,overlaydata[x].address);
    }
}

void loadoverlay(unsigned char overlay_select)
{
    // Load memory overlay with given number

    // Returns if overlay allready active
    if(overlay_select != overlay_active)
    {
        if(overlaydata[overlay_select-1].bank)
        {
            BankMemCopy(overlaydata[overlay_select-1].address,overlaydata[overlay_select-1].bank-1,OVERLAYLOAD,2,OVERLAYSIZE);
        }
        else
        {
            // Compose filename
            sprintf(buffer,"careers.ovl%u",overlay_select);

            // Load overlay file, exit if not found
            if (cbm_load (buffer, bootdevice, NULL) == 0)
            {
                printf("\nLoading overlay file failed\n");
                exit(1);
            }
        }
        overlay_active = overlay_select;
    }   
}

void wait(clock_t wait_cycles)
 {
    /* Function to wait for the specified number of cycles
       Input: wait_cycles = numnber of cycles to wait       */

    clock_t starttime = clock();
    while (clock() - starttime < wait_cycles);
}

/* General screen functions */
void cspaces(unsigned char number)
{
    /* Function to print specified number of spaces, cursor set by conio.h functions */

    unsigned char x;

    for(x=0;x<number;x++) { cputc(C_SPACE); }
}

void printcentered(char* text, unsigned char xpos, unsigned char ypos, unsigned char width)
{
    /* Function to print a text centered
       Input:
       - Text:  Text to be printed
       - Color: Color for text to be printed
       - Width: Width of window to align to    */

    gotoxy(xpos,ypos);

    if(strlen(text)<width)
    {
        cspaces((width-strlen(text))/2-1);
    }
    cputs(text);
}

/* Generic input routines */

unsigned char getkey(char* allowedkeys, unsigned char joyallowed)
{
    /* Function to wait on valid key or joystick press/move
       Input: allowedkeys = String with valid key press options
                            Empty string means any key allowed
       Output: key value (or joystick converted to key value)
       Global joyinterface variable needs to be set:
       0 = none, 1 = port 2 joystick, 2 = SNES pad via user port */

    unsigned char key, joy;

    do
    {
        key = 0;

        //Joystick in port 2
        if(joyinterface==1 && joyallowed)
        {
            joy = joy_read(JOY_2);
            if(joy&JOY_BTN_1_MASK) { key = C_ENTER; }
            if(joy&JOY_RIGHT_MASK) { key = C_RIGHT; }
            if(joy&JOY_LEFT_MASK) { key = C_LEFT; }
            if(joy&JOY_DOWN_MASK) { key = C_DOWN; }
            if(joy&JOY_UP_MASK) { key = C_UP; }
            if(key){
                do
                {
                    wait(10);
                    joy = joy_read(JOY_2);
                } while (joy);
            }
        }

        // SNES pad via user port
        if(joyinterface==2 && joyallowed)
        {
            snes_read();
            if(SNES.first&SNES_SELECT || SNES.first&SNES_B ) { key = C_ENTER; }
            if(SNES.first&SNES_RIGHT) { key = C_RIGHT; }
            if(SNES.first&SNES_LEFT) { key = C_LEFT; }
            if(SNES.first&SNES_DOWN) { key = C_DOWN; }
            if(SNES.first&SNES_UP) { key = C_UP; }
            if(key){
                do
                {
                    wait(10);
                    snes_read();
                } while (SNES.first);
            }
        }

        // Default to checking keyboard if nothing detected yet
        if(key == 0)
        {
            if(kbhit())
            {
                key = cgetc();
                if(strlen(allowedkeys)==0) { key = C_ENTER; }
            }
        }
    } while ( (strchr(allowedkeys, key)==0 && key != C_ENTER) || key == 0);
    POKE(208,0);    // Clear keyboard buffer
    return key;
}

int input(unsigned char xpos, unsigned char ypos, char *str, unsigned char size)
{
    /**
    * input/modify a string.
    * based on version DraCopy 1.0e, then modified.
    * Created 2009 by Sascha Bader.
    * @param[in] xpos screen x where input starts.
    * @param[in] ypos screen y where input starts.
    * @param[in,out] str string that is edited, it can have content and must have at   least @p size + 1 bytes. Maximum size if 255 bytes.
    * @param[in] size maximum length of @p str in bytes.
    * @return -1 if input was aborted.
    * @return >= 0 length of edited string @p str.
    */

    unsigned char idx = strlen(str);
    unsigned char c, x, b, flag;
      
    VDC_HChar(ypos,xpos,C_SPACE,size,VDC_WHITE+VDC_A_UNDERLINE+VDC_A_ALTCHAR);
    VDC_PrintAt(ypos,xpos,str,VDC_WHITE+VDC_A_UNDERLINE+VDC_A_ALTCHAR);
    VDC_Plot(ypos,xpos+idx,C_SPACE,VDC_WHITE+VDC_A_REVERSE+VDC_A_ALTCHAR);
  
    while(1)
    {
        c = cgetc();
        switch (c)
        {
            case C_ENTER:
                idx = strlen(str);
                str[idx] = 0;
                VDC_HChar(ypos,xpos,C_SPACE,size,VDC_LYELLOW+VDC_A_ALTCHAR);
                VDC_PrintAt(ypos,xpos,str,VDC_LYELLOW+VDC_A_ALTCHAR);
                return idx;
  
            case C_DELETE:
                if (idx)
                {
                    --idx;
                    VDC_Plot(ypos,xpos+idx,C_SPACE,VDC_WHITE+VDC_A_UNDERLINE+VDC_A_ALTCHAR);
                    for(x = idx; 1; ++x)
                    {
                        b = str[x+1];
                        str[x] = b;
                        VDC_Plot(ypos,xpos+x, b ? VDC_PetsciiToScreenCode(b) : C_LOWLINE,VDC_WHITE+VDC_A_UNDERLINE+VDC_A_ALTCHAR);
                        if (b == 0) { break; }
                    }
                    VDC_Plot(ypos,xpos+idx,str[idx] ? VDC_PetsciiToScreenCode(str[idx]) : C_SPACE,VDC_WHITE+VDC_A_REVERSE+VDC_A_ALTCHAR);
                    VDC_Plot(ypos,xpos+idx+1,str[idx+1] ? VDC_PetsciiToScreenCode(str[idx+1]) : C_SPACE,VDC_WHITE+VDC_A_UNDERLINE+VDC_A_ALTCHAR);
                }
                break;

            case C_INSERT:
                c = strlen(str);
                if (c < size && c > 0 && idx < c)
                {
                    ++c;
                    while(c >= idx)
                    {
                        str[c+1] = str[c];
                        if (c == 0) { break; }
                        --c;
                    }
                    str[idx] = ' ';
                    VDC_PrintAt(ypos,xpos,str,VDC_WHITE+VDC_A_UNDERLINE+VDC_A_ALTCHAR);
                    VDC_Plot(ypos,xpos+idx,C_SPACE,VDC_WHITE+VDC_A_REVERSE+VDC_A_ALTCHAR);
                }
                break;
  
            case C_LEFT:
                if (idx)
                {
                    --idx;
                    VDC_Plot(ypos,xpos+idx,str[idx] ? VDC_PetsciiToScreenCode(str[idx]) : C_SPACE,VDC_WHITE+VDC_A_REVERSE+VDC_A_ALTCHAR);
                    VDC_Plot(ypos,xpos+idx+1,str[idx+1] ? VDC_PetsciiToScreenCode(str[idx+1]) : C_SPACE,VDC_WHITE+VDC_A_UNDERLINE+VDC_A_ALTCHAR);
                }
                break;

            case C_RIGHT:
                if (idx < strlen(str) && idx < size)
                {
                    ++idx;
                    VDC_Plot(ypos,xpos+idx-1,VDC_PetsciiToScreenCode(str[idx-1]),VDC_WHITE+VDC_A_UNDERLINE+VDC_A_ALTCHAR);
                    VDC_Plot(ypos,xpos+idx,str[idx] ? VDC_PetsciiToScreenCode(str[idx]) : C_SPACE,VDC_WHITE+VDC_A_REVERSE+VDC_A_ALTCHAR);
                }
                break;
  
            default:
                if (isprint(c) && idx < size)
                {
                    flag = (str[idx] == 0);
                    str[idx] = c;
                    VDC_Plot(ypos,xpos+idx,VDC_PetsciiToScreenCode(c),VDC_WHITE+VDC_A_UNDERLINE+VDC_A_ALTCHAR);
                    VDC_Plot(ypos,xpos+idx+1,C_SPACE,VDC_WHITE+VDC_A_REVERSE+VDC_A_ALTCHAR);
                    ++idx;
                    if (flag) { str[idx+1] = 0; }
                }
                break;
        }
    }
    return 0;
}

unsigned char input_number(unsigned char xpos, unsigned char ypos, unsigned char minvalue, unsigned char maxvalue)
{
    // Function to input a number using the cursor keys (or joystick/pad)

    unsigned char answer = minvalue;
    unsigned char key;

    textcolor(COLOR_WHITE);

    do
    {
        gotoxy(xpos,ypos);
        cprintf("%u  ",answer);
        key = getkey(alldirections,1);
        switch (key)
        {
        case C_DOWN:
        case C_LEFT:
            if(answer>minvalue) { answer--; } else { answer=maxvalue; }
            break;

        case C_UP:
        case C_RIGHT:
            if(answer<maxvalue) { answer++; } else { answer=minvalue; }
            break;
        
        default:
            break;
        }

    } while (key != C_ENTER);

    textcolor(COLOR_CYAN);
    gotoxy(xpos,ypos);
    cprintf("%u  ",answer);
    textcolor(COLOR_YELLOW);
    return answer;
}

void presskeyprompt(unsigned char xpos, unsigned char ypos)
{
    cputsxy(xpos,ypos,"Press key.");
    getkey("",1);
}

/* Functions for windowing and menu system */

void windowsave(unsigned char ypos, unsigned char height)
{
    /* Function to save a window
       Input:
       - ypos: startline of window
       - height: height of window    */
    
    Window[windownumber].address = windowaddress;
    Window[windownumber].ypos = ypos;
    Window[windownumber].height = height;

    // Copy characters
    VDC_CopyVDCToMem(ypos*80,windowaddress,1,height*80);
    windowaddress += height*80;

    // Copy attributes
    VDC_CopyVDCToMem(0x0800+ypos*80,windowaddress,1,height*80);
    windowaddress += height*80;

    windownumber++;
}

void windowrestore()
{
    /* Function to restore a window */
    windowaddress = Window[--windownumber].address;

    // Restore characters
    VDC_CopyMemToVDC(Window[windownumber].ypos*80,windowaddress,1,Window[windownumber].height*80);

    // Restore attributes
    VDC_CopyMemToVDC(0x0800+(Window[windownumber].ypos*80),windowaddress+(Window[windownumber].height*80),1,Window[windownumber].height*80);
}

void menumakeborder(unsigned char xpos, unsigned char ypos, unsigned char height, unsigned char width)
{
    /* Function to make menu border
       Input:
       - xpos: x-coordinate of left upper corner
       - ypos: y-coordinate of right upper corner
       - height: number of rows in window
       - width: window width in characters        */
 
    windowsave(ypos, height+4);

    VDC_FillArea(ypos+1,xpos+1,C_SPACE,width,height,VDC_LYELLOW);
    VDC_Plot(ypos,xpos,C_LOWRIGHT,VDC_LRED);
    VDC_HChar(ypos,xpos+1,C_LOWLINE,width,VDC_LRED);
    VDC_Plot(ypos,xpos+width+1,C_LOWLEFT,VDC_LRED);
    VDC_VChar(ypos+1,xpos,C_RIGHTLINE,height,VDC_LRED);
    VDC_VChar(ypos+1,xpos+width+1,C_LEFTLINE,height,VDC_LRED);
    VDC_Plot(ypos+height+1,xpos,C_UPRIGHT,VDC_LRED);
    VDC_HChar(ypos+height+1,xpos+1,C_UPLINE,width,VDC_LRED);
    VDC_Plot(ypos+height+1,xpos+width+1,C_UPLEFT,VDC_LRED);
}

void menuplacebar()
{
    /* Function to print menu bar */

    unsigned char x;

    VDC_HChar(0,0,C_SPACE,80,VDC_LGREEN+VDC_A_REVERSE);
    VDC_HChar(1,0,C_SPACE,80,VDC_DGREEN+VDC_A_REVERSE);

    VDC_PrintAt(0,1,"C A R E E R S",VDC_LGREEN+VDC_A_REVERSE);
    VDC_PrintAt(0,59,"Written by Xander Mol",VDC_LGREEN+VDC_A_REVERSE);

    for(x=0;x<menubaroptions;x++)
    {
        VDC_PrintAt(1,menubarcoords[x],menubartitles[x],VDC_DGREEN+VDC_A_REVERSE);
    }
}

unsigned char menupulldown(unsigned char xpos, unsigned char ypos, unsigned char menunumber)
{
    /* Function for pull down menu
       Input:
       - xpos = x-coordinate of upper left corner
       - ypos = y-coordinate of upper left corner
       - menunumber = 
         number of the menu as defined in pulldownmenuoptions array */

    unsigned char x;
    char validkeys[6];
    unsigned char key;
    unsigned char exit = 0;
    unsigned char menuchoice = 1;

    windowsave(ypos, pulldownmenuoptions[menunumber-1]+4);
    if(menunumber>menubaroptions)
    {
        VDC_Plot(ypos,xpos,C_LOWRIGHT,VDC_LRED);
        VDC_HChar(ypos,xpos+1,C_LOWLINE,strlen(pulldownmenutitles[menunumber-1][0])+2,VDC_LRED);
        VDC_Plot(ypos,xpos+strlen(pulldownmenutitles[menunumber-1][0])+3,C_LOWLEFT,VDC_LRED);
    }
    for(x=0;x<pulldownmenuoptions[menunumber-1];x++)
    {
        VDC_Plot(ypos+x+1,xpos,C_RIGHTLINE,VDC_LRED);
        VDC_Plot(ypos+x+1,xpos+1,C_SPACE,VDC_LCYAN+VDC_A_REVERSE);
        VDC_PrintAt(ypos+x+1,xpos+2,pulldownmenutitles[menunumber-1][x],VDC_LCYAN+VDC_A_REVERSE);
        VDC_Plot(ypos+x+1,xpos+strlen(pulldownmenutitles[menunumber-1][x])+2,C_SPACE,VDC_LCYAN+VDC_A_REVERSE);
        VDC_Plot(ypos+x+1,xpos+strlen(pulldownmenutitles[menunumber-1][x])+3,C_LEFTLINE,VDC_LRED);
    }
    VDC_Plot(ypos+pulldownmenuoptions[menunumber-1]+1,xpos,C_UPRIGHT,VDC_LRED);
    VDC_HChar(ypos+pulldownmenuoptions[menunumber-1]+1,xpos+1,C_UPLINE,strlen(pulldownmenutitles[menunumber-1][0])+2,VDC_LRED);
    VDC_Plot(ypos+pulldownmenuoptions[menunumber-1]+1,xpos+strlen(pulldownmenutitles[menunumber-1][0])+3,C_UPLEFT,VDC_LRED);

    strcpy(validkeys, updownenter);
    if(menunumber<=menubaroptions)
    {
        strcat(validkeys, leftright);
    }
    
    do
    {
        VDC_Plot(ypos+menuchoice,xpos+1,C_SPACE,VDC_LYELLOW+VDC_A_REVERSE);
        VDC_PrintAt(ypos+menuchoice,xpos+2,pulldownmenutitles[menunumber-1][menuchoice-1],VDC_LYELLOW+VDC_A_REVERSE);
        VDC_Plot(ypos+menuchoice,xpos+strlen(pulldownmenutitles[menunumber-1][menuchoice-1])+2,C_SPACE,VDC_LYELLOW+VDC_A_REVERSE);

        key = getkey(validkeys,joyinterface);
        switch (key)
        {
        case C_ENTER:
            exit = 1;
            break;
        
        case C_LEFT:
            exit = 1;
            menuchoice = 18;
            break;
        
        case C_RIGHT:
            exit = 1;
            menuchoice = 19;
            break;

        case C_DOWN:
        case C_UP:
            VDC_Plot(ypos+menuchoice,xpos+1,C_SPACE,VDC_LCYAN+VDC_A_REVERSE);
            VDC_PrintAt(ypos+menuchoice,xpos+2,pulldownmenutitles[menunumber-1][menuchoice-1],VDC_LCYAN+VDC_A_REVERSE);
            VDC_Plot(ypos+menuchoice,xpos+strlen(pulldownmenutitles[menunumber-1][menuchoice-1])+2,C_SPACE,VDC_LCYAN+VDC_A_REVERSE);
            if(key==C_UP)
            {
                menuchoice--;
                if(menuchoice<1)
                {
                    menuchoice=pulldownmenuoptions[menunumber-1];
                }
            }
            else
            {
                menuchoice++;
                if(menuchoice>pulldownmenuoptions[menunumber-1])
                {
                    menuchoice = 1;
                }
            }
            break;

        default:
            break;
        }
    } while (exit==0);
    windowrestore();    
    return menuchoice;
}

unsigned char menumain()
{
    /* Function for main menu selection */

    unsigned char menubarchoice = 1;
    unsigned char menuoptionchoice = 0;
    unsigned char key;
    char validkeys[4] = {C_LEFT,C_RIGHT,C_ENTER,0};
    unsigned char xpos;

    do
    {
        do
        {
            VDC_Plot(1,menubarcoords[menubarchoice-1]-1,C_SPACE,VDC_WHITE+VDC_A_REVERSE+VDC_A_ALTCHAR);
            VDC_PrintAt(1,menubarcoords[menubarchoice-1],menubartitles[menubarchoice-1],VDC_WHITE+VDC_A_REVERSE+VDC_A_ALTCHAR);
            VDC_Plot(1,menubarcoords[menubarchoice-1]+strlen(menubartitles[menubarchoice-1]),C_SPACE,VDC_WHITE+VDC_A_REVERSE+VDC_A_ALTCHAR);

            key = getkey(validkeys,joyinterface);

            VDC_Plot(1,menubarcoords[menubarchoice-1]-1,C_SPACE,VDC_DGREEN+VDC_A_REVERSE+VDC_A_ALTCHAR);
            VDC_PrintAt(1,menubarcoords[menubarchoice-1],menubartitles[menubarchoice-1],VDC_DGREEN+VDC_A_REVERSE+VDC_A_ALTCHAR);
            VDC_Plot(1,menubarcoords[menubarchoice-1]+strlen(menubartitles[menubarchoice-1]),C_SPACE,VDC_DGREEN+VDC_A_REVERSE+VDC_A_ALTCHAR);
            
            if(key==C_LEFT)
            {
                menubarchoice--;
                if(menubarchoice<1)
                {
                    menubarchoice = menubaroptions;
                }
            }
            else if (key==C_RIGHT)
            {
                menubarchoice++;
                if(menubarchoice>menubaroptions)
                {
                    menubarchoice = 1;
                }
            }
        } while (key!=C_ENTER);
        xpos=menubarcoords[menubarchoice-1]-1;
        if(xpos+strlen(pulldownmenutitles[menubarchoice-1][0])>38)
        {
            xpos=menubarcoords[menubarchoice-1]+strlen(menubartitles[menubarchoice-1])-strlen(pulldownmenutitles[menubarchoice-1][0]);
        }
        menuoptionchoice = menupulldown(xpos,1,menubarchoice);
        if(menuoptionchoice==18)
        {
            menuoptionchoice=0;
            menubarchoice--;
            if(menubarchoice<1)
            {
                    menubarchoice = menubaroptions;
            }
        }
        if(menuoptionchoice==19)
        {
            menuoptionchoice=0;
            menubarchoice++;
            if(menubarchoice>menubaroptions)
            {
                menubarchoice = 1;
            }
        }
    } while (menuoptionchoice==0);
    return menubarchoice*10+menuoptionchoice;    
}

unsigned char areyousure()
{
    /* Pull down menu to verify if player is sure */

    unsigned char choice;

    menumakeborder(8,8,6,30);
    cputsxy(10,10,"Are you sure?");
    choice = menupulldown(25,11,6);
    windowrestore();
    return choice;
}

void fileerrormessage(unsigned char error)
{
    /* Show message for file error encountered */

    menumakeborder(8,8,6,30);
    cputsxy(10,10,"File error!");
    if(error<255)
    {
        gotoxy(10,12);
        cprintf("Error nr.: %2X",error);
    }
    presskeyprompt(10,12);
    windowrestore();    
}

/* Config file and save functions */

void saveconfigfile()
{
    // Function to save config file

    char filename[] = "career.cfg";
    unsigned char error;

    // Remove old file
    remove(filename);

    // Set device ID
	cbm_k_setlfs(0, getcurrentdevice(), 0);

    // Set filename
	cbm_k_setnam(filename);

    // Set bank to 0
    SetLoadSaveBank(0);

    // Save saveslots memory
	error = cbm_k_save(SAVESLOTS, SAVESLOTS+85);

    if (error) { fileerrormessage(error); }
}

void loadconfigfile()
{
    // Load configuration file or create one if not present

    char filename[] = "career.cfg";
    unsigned int address;
    unsigned char x,y;

    // Set device ID
	cbm_k_setlfs(0, getcurrentdevice(), 0);

	// Set filename
	cbm_k_setnam(filename);

	// Set bank to 0
	SetLoadSaveBank(0);
	
	// Load config from file to memory
	address = cbm_k_load(0,SAVESLOTS);

    if (address>SAVESLOTS) {
        address=SAVESLOTS+5;
        for(y=0;y<5;y++)
        {
            for(x=0;x<16;x++)
            {
                pulldownmenutitles[10][y][x]=PEEK(address++);
            }
        }
    }
    else
    {
        memset((char*)SAVESLOTS,0,85);
        address=SAVESLOTS+5;
        for(y=0;y<5;y++)
        {
            for(x=0;x<16;x++)
            {
                POKE(address++,pulldownmenutitles[10][y][x]);
            }
        }
        saveconfigfile();
    }
}

// Board display and movement routines

void board_reposition(unsigned char row, unsigned char col)
{
    /* Centers board on given row and col.
       Input: row and column on gameboard to center on     */

    if(col>40) { xoffset = col-40; } else { xoffset = 0; }
    if(xoffset>48) { xoffset=48; }
    if(row>12) { yoffset = row-12; } else { yoffset = 0; }
    if(yoffset>31) { yoffset=31; }
    VDC_CopyViewPortToVDC(SCREENMAPADDRESS,1,BOARD_WIDTH,BOARD_HEIGHT,xoffset,yoffset,0,2,60,23);
}

void board_print(unsigned char row, unsigned char col, unsigned char screencode, unsigned char attribute)
{
    /* Print on game board.
       Input: row, column, screencode and attribute */

    unsigned int printaddress = SCREENMAPADDRESS + row*BOARD_WIDTH + col;
    POKEB(printaddress,1,screencode);
    POKEB(printaddress+(BOARD_HEIGHT*BOARD_WIDTH)+BOARD_ATTRPADDING,1,attribute);    
}

// Pawn placement routines

void pawn_place(unsigned char playernumber)
{
    /* Place pawn on board. Input: player number */

    unsigned char row,col,help,x,y;

    if (player[playernumber].career==0 || player[playernumber].position==0)
    {
        help = 255;
        if (player[playernumber].position==0)
        {
            help = 0;
            player[playernumber].position=career[player[playernumber].career-1].startfield;
        }
        row=ring[player[playernumber].position-1].ycoord;
        col=ring[player[playernumber].position-1].xcoord;
        for(y=0;y<3;y++)
        {
            for(x=0;x<3;x++)
            {
                board_print(row+y,col+x,pawngraphics[y][x],ring[player[playernumber].position-1].color+VDC_A_REVERSE);
            }
        }
        board_print(row+1,col+1,0x31+playernumber,VDC_WHITE);
        if (help == 0) { player[playernumber].position = 0; }
    }
    else
    {
        row=careerfield[player[playernumber].career-1][player[playernumber].position-1].ycoord;
        col=careerfield[player[playernumber].career-1][player[playernumber].position-1].xcoord;
        board_print(row,col,0xF0+playernumber,VDC_WHITE);
    }

    board_reposition(row,col);
}

unsigned char pawn_other(unsigned char playernumber)
{
    /* Checks if other pawns are present on location of player's pawn.
       Input: player number */

    unsigned char otherpawnflag = 0;
    unsigned char x;

    if(resetflag) { return 0; }

    for(x=0;x<4;x++)
    {
        if(player[playernumber].career==player[x].career && player[playernumber].position==player[x].position && x!=playernumber)
        { otherpawnflag = x; }
    }

    if (otherpawnflag>0) { pawn_place(otherpawnflag); }

    return otherpawnflag;
}

void pawn_erase(unsigned char playernumber)
{
    /* Erase pawn on board. Input: player number */

    unsigned char help,x,y;

    if(pawn_other(playernumber)==0)
    {
        if (player[playernumber].career==0 || player[playernumber].position==0)
        {
            help = 255;
            if (player[playernumber].position==0)
            {
                help = 0;
                player[playernumber].position=career[player[playernumber].career-1].startfield;
            }
            for(y=0;y<3;y++)
            {
                for(x=0;x<3;x++)
                {
                    board_print(ring[player[playernumber].position-1].ycoord+y,ring[player[playernumber].position-1].xcoord+x,y==2?C_BLOCKUNDER:C_SPACE,ring[player[playernumber].position-1].color+VDC_A_REVERSE);
                }
            }
            if (help == 0) { player[playernumber].position = 0; }
        }
        else
        {
            board_print(careerfield[player[playernumber].career-1][player[playernumber].position-1].ycoord,careerfield[player[playernumber].career-1][player[playernumber].position-1].xcoord,C_BLOCKUNDER,careerfield[player[playernumber].career-1][player[playernumber].position-1].color+VDC_A_REVERSE);
        }
    }
}

void board_reset()
{
    /* Clears game board for new game */

    unsigned char x;

    xoffset = 48;
    yoffset = 31;

    resetflag=1;
    for(x=0;x<4;x++) { pawn_erase(x); }
    resetflag=0;
}

/* Game loop routines */

void game_reset()
{
    /* Reset all game variables for new game */

    unsigned char x,y;

    for(x=0;x<15;x++)
    {
        opportunitycard[x].available = cardreset[x];
    }
    for(x=0;x<4;x++)
    {
        player[x].career = 0;
        player[x].position = 1;
        player[x].salary = 2000;
        player[x].money = 2000;
        player[x].fame = 0;
        player[x].happiness = 0;
        player[x].winmoney = 20;
        player[x].winfame = 20;
        player[x].winhappiness = 20;
        player[x].skipturn = 0;
        for(y=0;y<11;y++) { player[x].experience[y]=0; }
    }
    fieldinformation=0;
    anotherturn=0;
    playerturn=0;
    board_reset();
}

void inputofnames()
{
    /* Enter player nanes */

    unsigned char x,choice,selected;
    char allowedkeys[8];

    strcpy(allowedkeys,alldirections);
    strcat(allowedkeys,"+-");
    menumakeborder(30,8,6,45);
    for(x=0;x<4;x++)
    {
        gotoxy(32,10);
        cputs("Computer plays player ");
        textcolor(COLOR_CYAN);
        cprintf("%d",x+1);
        textcolor(COLOR_YELLOW);
        cputs("?");
        player[x].computer=menupulldown(69,11,6)==1?1:0;
        gotoxy(32,10);
        cprintf("Input name player ");
        textcolor(COLOR_CYAN);
        cprintf("%d",x+1);
        textcolor(COLOR_YELLOW);
        cputs(":    ");
        input(32,12,player[x].name,19);
        if(player[x].computer==0)
        {
            selected = 0;
            VDC_FillArea(10,32,C_SPACE,43,4,VDC_LYELLOW+VDC_A_ALTCHAR);
            cputsxy(32,10,player[x].name);
            cputsxy(32,11,"Select Success Formula (total must be 60):");
            do
            {
                do
                {
                    VDC_Plot(12,32,C_HEART,VDC_LRED);
                    sprintf(buffer," %2u ",player[x].winhappiness);
                    VDC_PrintAt(12,33,buffer,selected==0?VDC_WHITE+VDC_A_REVERSE+VDC_A_ALTCHAR:VDC_LYELLOW);
                    VDC_PrintAt(12,37," + ",VDC_LYELLOW);

                    VDC_Plot(12,40,C_STAR,VDC_LYELLOW);
                    sprintf(buffer," %2u ",player[x].winfame);
                    VDC_PrintAt(12,41,buffer,selected==1?VDC_WHITE+VDC_A_REVERSE+VDC_A_ALTCHAR:VDC_LYELLOW);
                    VDC_PrintAt(12,45," + ",VDC_LYELLOW);

                    VDC_Plot(12,48,C_DOLLAR,VDC_LGREEN);
                    sprintf(buffer," %2u ",player[x].winmoney);
                    VDC_PrintAt(12,49,buffer,selected==2?VDC_WHITE+VDC_A_REVERSE+VDC_A_ALTCHAR:VDC_LYELLOW);
                    sprintf(buffer," =%3u",player[x].winhappiness+player[x].winfame+player[x].winmoney);
                    VDC_PrintAt(12,53,buffer,VDC_LYELLOW);

                    choice = getkey(allowedkeys,1);

                    switch (choice)
                    {
                    case C_LEFT:
                        if(selected>0) { selected--; } else { selected = 2; }
                        break;

                    case C_RIGHT:
                        if(selected<2) { selected++; } else { selected = 0; }
                        break;

                    case C_UP:
                    case '+':
                        if(selected==0 && player[x].winhappiness<60) { player[x].winhappiness++; }
                        if(selected==1 && player[x].winfame<60) { player[x].winfame++; }
                        if(selected==2 && player[x].winmoney<60) { player[x].winmoney++; }
                        break;

                    case C_DOWN:
                    case '-':
                        if(selected==0 && player[x].winhappiness>0) { player[x].winhappiness--; }
                        if(selected==1 && player[x].winfame>0) { player[x].winfame--; }
                        if(selected==2 && player[x].winmoney>0) { player[x].winmoney--; }
                        break;

                    default:
                        break;
                    }

                } while (choice != C_ENTER);

                if(player[x].winhappiness+player[x].winfame+player[x].winmoney != 60)
                {
                    cputsxy(32,13,"Total is not 60, please correct.");
                }

            } while (player[x].winhappiness+player[x].winfame+player[x].winmoney != 60);
            
            VDC_FillArea(10,32,C_SPACE,43,4,VDC_LYELLOW+VDC_A_ALTCHAR);                 
        }
    }
    windowrestore();
}

void dice_throw(unsigned char dicenumber)
{
    /* Throw the dice(s).
       Input: number of dice to throw (1 or 2)
       Output: places total thrown in global variable dice_total
               Sets flag if both dice are the same in global variable dice_double */

    unsigned char dice1, dice2, x;

    menumakeborder(60,10,7,11);
    for(x=0;x<10;x++)
    {
        dice1 = rand()%6+1;
        dice2 = rand()%6+1;
        VDC_PlotString(12,62,dicegraphics[dice1-1][0],4,VDC_WHITE+VDC_A_ALTCHAR);
        VDC_PlotString(13,62,dicegraphics[dice1-1][1],4,VDC_WHITE+VDC_A_ALTCHAR);
        VDC_PlotString(14,62,dicegraphics[dice1-1][2],4,VDC_WHITE+VDC_A_ALTCHAR);
        if(dicenumber==2)
        {
            VDC_PlotString(12,67,dicegraphics[dice2-1][0],4,VDC_WHITE+VDC_A_ALTCHAR);
            VDC_PlotString(13,67,dicegraphics[dice2-1][1],4,VDC_WHITE+VDC_A_ALTCHAR);
            VDC_PlotString(14,67,dicegraphics[dice2-1][2],4,VDC_WHITE+VDC_A_ALTCHAR);
        }
        wait(5);
    }
    dice_total = dicenumber==2?dice1+dice2:dice1;
    dice_double = dice1==dice2?1:0;
    presskeyprompt(62,16);
    windowrestore();
}

unsigned char player_collegeexperience()
{
    /* Routine to check if player went to college before.
       Output is 1 for yes, 0 for no */

    if(player[playerturn].experience[0] || player[playerturn].experience[1] || player[playerturn].experience[2] || player[playerturn].experience[3])
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

unsigned char card_selectopportunity()
{
    /* Selects an opportunity card randomly, returns card number */

    unsigned char card_count = 0;
    unsigned char card_select = 0;
    unsigned char x,y,counter;

    for(x=0;x<15;x++)
    {
        card_count += opportunitycard[x].available;
    }
    if(card_count==0) { return 255; }
    do
    {
        card_select = rand()%card_count;
        counter=0;
        for(x=0;x<15;x++)
        {
            if(opportunitycard[x].available)
            {
                for(y=0;y<opportunitycard[x].available;y++)
                {
                    if(counter==card_select)
                    {
                        card_select = x;
                        x=16;
                        break;
                    }
                    else
                    {
                        counter++;
                    }
                }
            }
        }
    } while (card_select == 11 && player_collegeexperience() && card_count > 1);
    if(card_select==11 && player_collegeexperience() ) { return 255; }
    opportunitycard[card_select].available--;
    return card_select;
}

char* cards_actiontext(unsigned char cardnumber)
{
    /* Return text for the action of an opportunity card.
       Input: card number */

    if(opportunitycard[cardnumber].careernumber==0) { return "Florida vacation"; }
    if(opportunitycard[cardnumber].careernumber==9) { return "Free choice"; }
    return career[opportunitycard[cardnumber].careernumber -1].name;
}

// Go to correct field action

void board_gotofieldaction()
{
    unsigned char careernr = player[playerturn].career;
    unsigned char position = player[playerturn].position;

    if (position==0)
    {
        position=career[careernr-1].startfield;
        careernr=0;
    }

    if(!careernr)
    {
        // Outer ring field selection
        switch (position)
        {
        case 1:
            loadoverlay(1);
            ring_payday();
            break;
        
        case 2:
        case 4:
        case 6:
        case 10:
        case 13:
        case 16:
        case 18:
        case 21:
        case 24:
        case 26:
        case 29:
            loadoverlay(1);
            ring_opportunity();
            break;

        case 3:
            loadoverlay(1);
            ring_paytaxes();
            break;
        
        case 5:
            loadoverlay(1);
            ring_farming();
            break;

        case 7:
            loadoverlay(1);
            ring_automobileshow();
            break;
        
        case 8:
            loadoverlay(1);
            ring_college();
            break;

        case 9:
            loadoverlay(1);
            ring_hospital();
            break;

        case 11:
            loadoverlay(2);
            ring_payfoodbills();
            break;

        case 12:
            loadoverlay(2);
            ring_business();
            break;

        case 14:
            loadoverlay(2);
            ring_artgallery();
            break;

        case 15:
            loadoverlay(2);
            ring_sea();
            break;

        case 17:
            loadoverlay(2);
            ring_parkbench();
            break;

        case 19:
            loadoverlay(3);
            ring_payrent();
            break;

        case 20:
            loadoverlay(3);
            ring_politics();
            break;
        
        case 22:
            loadoverlay(3);
            ring_shoppingspree();
            break;
        
        case 23:
            loadoverlay(3);
            ring_hollywood();
            break;

        case 25:
            loadoverlay(3);
            ring_floridavacation();
            break;
        
        case 27:
            loadoverlay(4);
            ring_stockmarket();
            break;
        
        case 28:
            loadoverlay(4);
            ring_uranium();
            break;
        
        case 30:
            loadoverlay(4);
            ring_yachtharbor();
            break;

        case 31:
            loadoverlay(4);
            ring_moon();
            break;

        case 32:
            loadoverlay(4);
            ring_statueinthepark();
            break;
        
        default:
            break;
        }
    }
    else
    {
        waitkeyflag = 0;
        loadoverlay(5);
        career_generic(careernr-1,position-1);
        switch (careerfield[careernr-1][position-1].outcome)
        {
        case 1:
            career_gethappiness(careernr-1,position-1);
            break;
        
        case 2:
            career_getexperiencecard(careernr-1,position-1);
            break;
        
        case 3:
            career_getmoneytimesdie(careernr-1,position-1);
            break;

        case 4:
            career_gethappinessandfame(careernr-1,position-1);
            break;

        case 5:
            loadoverlay(6);
            career_getmoney(careernr-1,position-1);
            break;

        case 6:
            loadoverlay(6);
            career_loosehalfmoney();
            break;

        case 7:
            loadoverlay(6);
            career_skipturn();
            break;
        
        case 8:
            loadoverlay(6);
            career_getfame(careernr-1,position-1);
            break;

        case 9:
            loadoverlay(6);
            career_getopportunitycard(careernr-1,position-1);
            break;

        case 10:
            loadoverlay(6);
            career_getsalary(careernr-1,position-1);
            break;

        case 11:
            career_gotoparkbench();
            break;

        case 12:
            loadoverlay(6);
            career_loosehalfsalary();
            break;
        
        case 13:
            career_gotohospital();
            break;

        case 14:
            loadoverlay(6);
            career_getmoneyandfame(careernr-1,position-1);
            break;
        
        case 15:
            loadoverlay(6);
            career_loosehalffame();
            break;

        case 16:
            loadoverlay(6);
            career_getfamenohappiness(careernr-1,position-1);
            break;
        
        case 17:
            loadoverlay(6);
            career_getsalarytimesdie(careernr-1,position-1);
            break;

        case 18:
            loadoverlay(6);
            career_throwagain();
            break;

        case 19:
            career_loosemoneyorparkbench(careernr-1,position-1);
            break;

        case 20:
            loadoverlay(6);
            career_looaseallcash();
            break;

        case 21:
            loadoverlay(6);
            career_looseallfame();
            break;

        case 22:
            career_getfamebuthospital(careernr-1,position-1);
            break;

        default:
            break;
        }
        loadoverlay(5);
        if(!waitkeyflag)
        {
            career_waitforkey();
        }
        else
        {
            board_gotofieldaction();
        }
    }
}

// Player choices routines

// Information submenu functions
void information_fieldinfo()
{
    // Information submenu: show information on a field

    unsigned char help_pos = player[playerturn].position;
    unsigned char help_car = player[playerturn].career;
    unsigned char answer;

    menumakeborder(40,8,5,37);
    cputsxy(42,10,"For how much fields further do you");
    cputsxy(42,11,"want to view the field information?");
    answer = input_number(67,12,1,12);
    windowrestore();

    fieldinformation = 1;
    player[playerturn].position += answer;

    if(!player[playerturn].career)
    {
        if(player[playerturn].position >32) { player[playerturn].position -= 32; }
    }
    else
    {
        if(player[playerturn].position > career[player[playerturn].career-1].length)
        {
            player[playerturn].position = player[playerturn].position - career[player[playerturn].career-1].length + career[player[playerturn].career-1].returnfield-1;
            if(player[playerturn].position >32) { player[playerturn].position -= 32; }
            player[playerturn].career = 0;
        }
    }

    board_gotofieldaction();

    fieldinformation = 0;
    player[playerturn].position = help_pos;
    player[playerturn].career = help_car;
}

// Player turn functions

void turnhuman()
{
    /* Turn for the human players */

    unsigned char choice, yesno;
    unsigned char leavemenu=0;

    do
    {
        choice = menumain();
        switch (choice)
        {
        case 11:
            leavemenu=1;
            break;

        case 12:
            yesno = areyousure();
            if(yesno==1) { leavemenu=1; gameendflag=6; game_reset(); }
            break;

        case 13:
            yesno = areyousure();
            if(yesno==1) { leavemenu=1; gameendflag=5; }
            break;

        case 21:
            loadoverlay(8);
            savegame(0);
            break;

        case 22:
            yesno = areyousure();
            if(yesno==1)
            {
                leavemenu=1;
                gameendflag=7;
                loadoverlay(8);
                loadgame();
            }
            break;

        case 23:
                if(autosavetoggle==1)
                {
                    autosavetoggle=0;
                    strcpy(pulldownmenutitles[1][2],"Autosave on ");
                }
                else
                {
                    autosavetoggle=1;
                    strcpy(pulldownmenutitles[1][2],"Autosave off");
                }
                break;

        case 31:
            loadoverlay(7);
            musicnext();
            break;

        case 32:
            StopMusic();
            musicnumber=0;
            break;
        case 33:
            if(musicnumber)
            { 
                StopMusic();
            }
            else
            {
                musicnumber=1;
            }
            PlayMusic();
            break;      

        case 41:
            loadoverlay(7);
            cards_show();
            break;
        
        case 42:
            if(!player[playerturn].skipturn && !(player[playerturn].career==0 && player[playerturn].position==9) && !(player[playerturn].career==0 && player[playerturn].position==17))
            {
                leavemenu=1;
                gameendflag=8;
                loadoverlay(9);
                cards_useopportunity();
            }
            break;
        
        case 43:
            if(!player[playerturn].skipturn && !(player[playerturn].career==0 && player[playerturn].position==9) && !(player[playerturn].career==0 && player[playerturn].position==17))
            {
                leavemenu=1;
                gameendflag=9;
                loadoverlay(9);
                cards_useexperience();
            }
            break;

        case 51:
            information_fieldinfo();
            break;

        case 52:
            loadoverlay(7);
            information_gamescore();
            break;
        
        case 53:
            loadoverlay(7);
            information_colorlegend();
            break;

        case 54:
            loadoverlay(8);
            board_scroll();
            break;
        
        case 55:
            loadoverlay(7);
            information_credits();
            break;

        default:
            break;
        }
    } while (!leavemenu);
}

void turncomputer()
{
    // Check if computer has to skip a turn
    if(player[playerturn].skipturn) { return; }

    // Check for hospital and park bench
    loadoverlay(5);
    if(computer_hospitalparkbench()) { return; }

    // Check for playing experience cards
    loadoverlay(9);
    if(computer_playexperiencecards()) { return; }

    // Check for playing opportunity cards
    loadoverlay(3);
    computer_playopportunitycards();
}

// Generic game logic functions

void checkwincondition()
{
    // Check for players that met their success formula

    unsigned char win = 255;
    unsigned char x;

    for(x=0;x<3;x++)
    {
        if( player[x].happiness > player[x].winhappiness-1 &&
            player[x].fame > player[x].winfame-1 &&
            player[x].money/1000 > player[x].winmoney-1)
        {
            win=x;
            x=4;
        }
    }
    if(win!=255)
    {
        menumakeborder(30,8,8,45);
        gotoxy(32,10);
        textcolor(COLOR_GREEN);
        cprintf("%s ",player[win].name);
        textcolor(COLOR_YELLOW);
        cputs("has won!");
        cputsxy(32,12,"Another game?");
        gameendflag = (menupulldown(69,13,6)==1)?6:5;
        windowrestore();
    }
}

unsigned char checkforbump_check(unsigned char car, unsigned char pos)
{
    // Function of the actual bump check
    // Input:  Career and position to check for
    // Output: Player number that can be bumped, 0 if none

    unsigned char x;
    unsigned char bump=0;
    unsigned char helpcar, helppos;

    // Return if hospital or park bench
    if(car==0)
    {
        if(pos==9 || pos==17)
        {
            return(0);
        }
    }

    // Adjust if player is at career startfield
    if(pos==0)
    {
        pos=career[car-1].startfield;
        car=0;
    }

    // Check for another pawn at same position
    for(x=0;x<3;x++)
    {
        if(playerturn!=x)
        {
            helpcar=player[x].career;
            helppos=player[x].position;
            if(helppos==0)
            {
                helppos=career[helpcar-1].startfield;
                helpcar=0;
            }
            if(car==helpcar && pos==helppos)
            {
                bump=x+1;
            }
        }
    }
    return bump;
}

void checkforbump()
{
    // Check if pawn already present that will be bumped
    // Dialogue only

    unsigned char bump=0;

    bump=checkforbump_check(player[playerturn].career,player[playerturn].position);

    // Dialogue of bump
    if(bump)
    {
        pawn_erase(bump-1);
        player[bump-1].career=0;
        player[bump-1].position=17;
        pawn_place(bump-1);
        menumakeborder(40,8,7,35);
        cputsxy(42,10,"Player ");
        textcolor(COLOR_CYAN);
        cprintf("%u (%s)",bump,player[bump-1].name);
        textcolor(COLOR_YELLOW);
        cputsxy(42,11,"is bumped to the PARK BENCH.");
        presskeyprompt(42,13);
        windowrestore();
    }
}

/* Graphics and screen initialisation functions */

void graphicsinit()
{
    // Initialize VDC screen and load charsets
    VDC_Init();
    printcentered("Loading...",0,10,80);
    VDC_LoadCharset("careers.chrs",bootdevice,LOADSAVEBUFFER,1,1);
    VDC_LoadCharset("careers.chra",bootdevice,LOADSAVEBUFFER,1,2);
}

void loadintro()
{
    /* Game start up: loading data and title screen */
    
    unsigned char error,x,y;
    unsigned int address = CTEXTADDRESS;

    /* Game intro */
    char joys[10];
    char music[4];
    char validkeys[6] = {'c','C','m', 'M', C_ENTER, 0 };
    unsigned char key;

    /* Title screen */
    //VDC_LoadScreen("ludo.tscr",LOADSAVEBUFFER,1,1);

    /* Load and read game config file */
    loadconfigfile();

    // Load game board screen map to memory
    VDC_LoadScreen("careers.scrn",bootdevice,SCREENMAPADDRESS,1);

    // Load career texts and sets string pointers
	cbm_k_setlfs(0,bootdevice, 0);
	cbm_k_setnam("careers.ctxt");
	SetLoadSaveBank(1);
	cbm_k_load(0,CTEXTADDRESS);
	SetLoadSaveBank(0);

    // Set career text address pointers
    for(x=0;x<8;x++)
    {
        y=0;
        do
        {
            careerfield[x][y].textaddress = address++;
            while (PEEKB(address++,1) !=0);
            y++;
        } while (PEEKB(address,1) !=0);
        address++;
    }

    // Imstall joystick driver
    error = joy_install(&joy_static_stddrv);
    if(error == JOY_ERR_OK)
    {
        joyinterface = 1;
    }
    else
    {
        cputsxy(0,24,"Joystick driver unavailable.");
    }

    // Initialise SNES pad
    snes_init();

    // Init overlays
    initoverlay();

    /* Load and start first music file */
    LoadMusic("careers.mus1");

    /* Wait for ENTER of FIRE while player can toggle music */ 
    printcentered("Press ENTER or FIRE to start game.",0,22,80);
    printcentered("C=toggle controls, M=toggle music.",0,23,80);

    do
    {
        switch (joyinterface)
        {
        case 0:
            strcpy(joys,"Keys only");
            break;

        case 1:
            strcpy(joys,"Joystick ");
            break;

        case 2:
            strcpy(joys,"SNES pad ");
            break;
        
        default:
            break;
        }
        if(musicnumber) { strcpy(music,"Yes"); } else { strcpy(music,"No "); }
        sprintf(buffer,"Controls: %s  Music: %s", joys,music);
        printcentered(buffer,0,20,80);
        key = getkey(validkeys,1);
        switch (key)
        {
        case 'c':
        case 'C':
            joyinterface++;
            if(error != JOY_ERR_OK && joyinterface==1) { joyinterface = 2; }
            if(joyinterface>2) { joyinterface=0; }
            break;

        case 'm':
        case 'M':
            if(musicnumber)
            {
                StopMusic();
                musicnumber = 0;
            }
            else{
                musicnumber = 1;
                PlayMusic();
            }
            break;
        
        default:
            break;
        }
    } while (key != C_ENTER);
}

// Main gane loop

void main()
{
    //unsigned char x,y;

    // Obtain device number the application was started from
    bootdevice = getcurrentdevice();

    // Set version number in string variable
    sprintf(version,
            "v%2i.%2i - %c%c%c%c%c%c%c%c-%c%c%c%c",
            VERSION_MAJOR, VERSION_MINOR,
            BUILD_YEAR_CH0, BUILD_YEAR_CH1, BUILD_YEAR_CH2, BUILD_YEAR_CH3, BUILD_MONTH_CH0, BUILD_MONTH_CH1, BUILD_DAY_CH0, BUILD_DAY_CH1,BUILD_HOUR_CH0, BUILD_HOUR_CH1, BUILD_MIN_CH0, BUILD_MIN_CH1);

    //Game intro
    graphicsinit();

    loadintro();

    //Show game interface
    clrscr(); 
    menuplacebar();
    game_reset();

    //Ask for loading save game
    menumakeborder(40,8,6,35);
    cputsxy(42,10,"Load old game?");
    choice = menupulldown(69,11,6);
    windowrestore();
    if(choice==1) { loadoverlay(8); gameendflag=7; loadgame(); }

    srand(clock());

    //Main game loop
    do
    {
        if(gameendflag!=7) { inputofnames(); }
        do
        {
            VDC_FillArea(3,60,C_SPACE,20,10,VDC_LYELLOW);
            gotoxy(61,3);
            cputs("Player ");
            textcolor(COLOR_CYAN);
            cprintf("%u", playerturn+1);
            textcolor(COLOR_YELLOW);
            cputs(":");
            textcolor(COLOR_GREEN);
            cputsxy(61,4,player[playerturn].name);
            textcolor(COLOR_YELLOW);

            gameendflag=0;
            pawn_erase(playerturn);
            pawn_place(playerturn);

            //// Testing fields
            //fieldinformation=1;
            //for(x=0;x<32;x++)
            //{
            //    pawn_erase(playerturn);
            //    player[playerturn].career=0;
            //    player[playerturn].position=x+1;
            //    pawn_place(playerturn);
            //    board_gotofieldaction();
            //}
            //// Testing careers
            //for(y=0;y<8;y++)
            //{
            //    for(x=0;x<career[y].length+1;x++)
            //    {
            //        pawn_erase(playerturn);
            //        player[playerturn].career=y+1;
            //        player[playerturn].position=x;
            //        pawn_place(playerturn);
            //        board_gotofieldaction();
            //    }
            //}
            //exit(1);

            if(player[playerturn].computer==0)
            {
                turnhuman();
                if(player[playerturn].career==0 && player[playerturn].position == 9)
                {
                    loadoverlay(2);
                    ring_leavehospital();
                }
                if(player[playerturn].career==0 && player[playerturn].position == 17)
                {
                    loadoverlay(2);
                    ring_leaveparkbench();
                }
            }
            else
            {
                cputsxy(61,6,"Computer plays.");
                turncomputer();
            }

            if(gameendflag!=5 && gameendflag!=6 && gameendflag!=7)
            {
                if(player[playerturn].skipturn)
                {
                    gameendflag=10;
                    player[playerturn].skipturn=0;
                    cputsxy(61,6,"Skip turn.");
                    presskeyprompt(61,8);
                }
    
                if(gameendflag==0)
                {
                    dice_throw(player[playerturn].career==0?2:1);
                }
    
                if(player[playerturn].career==0 && player[playerturn].position == 25 && dice_total<8 && gameendflag!=8 )
                {
                    loadoverlay(2);
                    ring_leavefloridavacation();
                }
    
                if(player[playerturn].career==0 && player[playerturn].position == 9 && dice_total>5 && !paidforleave )
                {
                    gameendflag=10;
                }
    
                if(player[playerturn].career==0 && player[playerturn].position == 17 && dice_total!=7 && dice_total!=11 && !dice_double && !paidforleave )
                {
                    gameendflag=10;
                }
    
                if(gameendflag!=10)
                {
                    pawn_erase(playerturn);
                    if(gameendflag==0 || gameendflag==9)
                    {
                        player[playerturn].position+=dice_total;
                        if(player[playerturn].career)
                        {
                            if(player[playerturn].position>career[player[playerturn].career-1].length)
                            {
                                player[playerturn].position = player[playerturn].position - career[player[playerturn].career-1].length + career[player[playerturn].career-1].returnfield-1;
                                loadoverlay(5);
                                career_endofcareer();
                                if(player[playerturn].position >32)
                                {
                                    player[playerturn].position -= 32;
                                    if(player[playerturn].position!=1)
                                    {
                                        loadoverlay(2);
                                        receive_salary();
                                    }
                                }
                                player[playerturn].career = 0;
                            }
                        }
                        else
                        {
                            if(player[playerturn].position>32)
                            {
                                player[playerturn].position-=32;
                                if(player[playerturn].position!=1)
                                {
                                    loadoverlay(2);
                                    receive_salary();
                                }
                            }
                        }
                    }
                    checkforbump();
                    pawn_place(playerturn);
                    board_gotofieldaction();
                }
                checkwincondition();
                if(anotherturn!=0)
                {
                    anotherturn=0;
                }
                else
                {
                    playerturn++;
                    if(playerturn>3) { playerturn=0; }
                }
                if(!player[playerturn].computer && autosavetoggle)
                {
                    loadoverlay(8);
                    savegame(1);
                }
            }        
        
        } while (gameendflag!=5 && gameendflag!=6);

    } while (gameendflag!=5);

    //if(musicnumber) { StopMusic(); }

    VDC_Exit();
    joy_uninstall();
    cputsxy(0,0,"Thanks for playing, goodbye.");
}