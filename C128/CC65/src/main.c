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

//Window data
struct WindowStruct
{
    unsigned int address;
    unsigned char ypos;
    unsigned char height;
};
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
    {"\x1C  2.000",
     "\x1C  8.000",
     "\x1C 16.000",
     "Nothing "},
    {"\x1C  4.000",
     "\x1C  8.000",
     "\x1C 12.000",
     "Nothing "},
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
struct RingStruct
{
    unsigned char xcoord;
    unsigned char ycoord;
    unsigned char color;
    unsigned char outcome;
};
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

struct CareerStruct
{
    unsigned char length;
    unsigned char returnfield;
    char name[20];
    unsigned char startfield;
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

struct CareerfieldStruct
{
    unsigned char xcoord;
    unsigned char ycoord;
    unsigned char color;
    char text[27];
    unsigned char outcome;
    unsigned char amount1;
    unsigned char amount2;
};
struct CareerfieldStruct careerfield[8][14] =
{
    {
        {49,47,VDC_LRED   ,"Beautiful Spring weather"  , 1, 2, 0},
        {49,44,VDC_WHITE  ,"Work on threshing crew"    , 2, 1, 0},
        {49,41,VDC_LRED   ,"Good fishing"              , 1, 2, 0},
        {49,38,VDC_LGREEN ,"Gamble in corn"            , 3, 1, 0},
        {43,38,VDC_LYELLOW,"Raise prize steer"         , 4, 2, 4},
        {37,38,VDC_LRED   ,"Mare has twin colts"       , 1, 6, 0},
        {37,41,VDC_LGREEN ,"Bumper crop"               , 5, 5, 0},
        {37,44,VDC_LRED   ,"Splendid Autumn colors"    , 1, 2, 0},
        {37,47,VDC_WHITE  ,"Hailstorm"                 , 6, 0, 0}
    },  
    {  
        {19,47,VDC_LRED   ,"Fall in love"              , 1, 4, 0},
        {19,44,VDC_WHITE  ,"Grades not high enough"    , 7, 0, 0},
        {25,44,VDC_LRED   ,"Elected to honor society"  , 1, 2, 0},
        {25,41,VDC_LRED   ,"Lead junior prom"          , 1, 2, 0},
        {25,38,VDC_WHITE  ,"Sweetheart has rich uncle" , 9, 2, 0},
        {19,38,VDC_LYELLOW,"All-American athlete"      , 8, 6, 0},
        {13,38,VDC_WHITE  ,"Honor graduate"            , 9, 2, 0}
    }, 
    { 
        {13,32,VDC_WHITE  ,"Learning business"         , 2, 1, 0},
        {19,32,VDC_WHITE  ,"Lunch with boss"           , 9, 1, 0},
        {25,32,VDC_LGREEN ,"Boss likes you"            ,10, 1, 0},
        {31,32,VDC_WHITE  ,"Argue with boss"           , 7, 0, 0},
        {31,29,VDC_LGREEN ,"Invent new production plan", 5, 2, 0},
        {31,26,VDC_LGREEN ,"Promotion to front office" ,10, 2, 0},
        {31,23,VDC_WHITE  ,"Swing big deal"            , 2, 1, 0},
        {25,23,VDC_LRED   ,"Gorgeous secretary"        , 1, 4, 0},
        {19,23,VDC_WHITE  ,"Too ambitious"             ,11, 0, 0},
        {19,26,VDC_WHITE  ,"Business slump"            ,12, 0, 0},
        {13,26,VDC_LGREEN ,"Elected to Board"          ,10, 3, 0}
    },
    {
        {13,17,VDC_WHITE  ,"Sea-sick"                  ,13, 0, 0},
        {19,17,VDC_LRED   ,"See sights of Buenos Aires", 1, 2, 0},
        {25,17,VDC_WHITE  ,"Meet famous traveller"     , 9, 2, 0},
        {31,17,VDC_WHITE  ,"Bad storm"                 , 2, 1, 0},
        {31,14,VDC_LGREEN ,"Find buried treasure"      , 3, 1, 0},
        {31,11,VDC_LRED   ,"Land at Tahiti"            , 1, 4, 0},
        {25,11,VDC_LRED   ,"Swim in tropical lagoon"   , 1, 6, 0},
        {19,11,VDC_WHITE  ,"Go beach-combing"          , 7, 0, 0},
        {19, 8,VDC_LRED   ,"Terrific shore-leave"      , 1, 8, 0}
    },
    {
        {43, 8,VDC_WHITE  ,"Lose in primaries"         ,11, 0, 0},
        {43,11,VDC_WHITE  ,"Lunch with royalty"        , 9, 2, 0},
        {43,14,VDC_LYELLOW,"Oppose crime"              , 8, 4, 0},
        {43,17,VDC_LRED   ,"Judge beauty contest"      , 1, 2, 0},
        {49,17,VDC_WHITE  ,"Ring 1000 doorbells"       , 2, 2, 0},
        {55,17,VDC_LYELLOW,"Sign six treaties"         , 8, 6, 0},
        {61,17,VDC_LYELLOW,"Appointed supreme court"   , 4, 2, 4},
        {61,14,VDC_LYELLOW,"Conduct investigation"     , 8, 8, 0},
        {61,11,VDC_LYELLOW,"Sell life story"           ,14, 4, 5},
        {55,11,VDC_WHITE  ,"Caught with mink"          ,15, 0, 0},
        {55, 8,VDC_LYELLOW,"Win by a landslide"        , 8,12, 0}
    },
    {
        {73, 8,VDC_LYELLOW,"Pose for calendar"         , 8, 2, 0},
        {73,11,VDC_WHITE  ,"Date with star"            , 2, 1, 0},
        {73,14,VDC_WHITE  ,"Director likes you"        , 9, 2, 0},
        {73,17,VDC_LYELLOW,"Marry foreign prince(ss)"  , 4, 6, 2},
        {79,17,VDC_LGREEN ,"TV contract"               ,10, 1, 0},
        {85,17,VDC_WHITE  ,"Fanmail drops off slightly",12, 0, 0},
        {85,14,VDC_LYELLOW,"Scandal"                   ,16,10, 0},
        {85,11,VDC_LGREEN ,"Reach stardom"             ,17, 1, 0},
        {91,11,VDC_LYELLOW,"Win Oscar"                 , 8,12, 0}
    },
    {
        {91,23,VDC_LRED   ,"Scenery is beautiful"      , 1, 2, 0},
        {85,23,VDC_WHITE  ,"Fast burro"                ,18, 0, 0},
        {79,23,VDC_WHITE  ,"Lose half your gear"       ,19, 2, 0},
        {73,23,VDC_LRED   ,"See rare butterfly"        , 1, 2, 0},
        {73,26,VDC_WHITE  ,"Pick & Shovel work"        , 2, 2, 0},
        {73,29,VDC_LRED   ,"Breathless view of Andes"  , 1, 4, 0},
        {73,32,VDC_WHITE  ,"Fall off cliff"            ,13, 0, 0},
        {79,32,VDC_LGREEN ,"Find small lode of gems"   , 5,10, 0},
        {85,32,VDC_LYELLOW,"Find Inca ruins"           , 4, 2, 4},
        {85,29,VDC_LRED   ,"Climb famous peak"         , 1, 6, 0},
        {91,29,VDC_LGREEN ,"Find rich uranium ore"     , 5,20, 0}
    },
    {
        {91,38,VDC_LRED   ,"Ship is beautiful"         , 1, 2, 0},
        {85,38,VDC_LYELLOW,"Successful take-off"       , 8, 6, 0},
        {79,38,VDC_WHITE  ,"Lose your nerve"           ,21, 0, 0},
        {73,38,VDC_WHITE  ,"Ship explodes"             ,20, 0, 0},
        {67,38,VDC_LYELLOW,"Rescue stewardess"         , 4, 2, 4},
        {61,38,VDC_LGREEN ,"Promotion for bravery"     ,10, 2, 0},
        {61,41,VDC_WHITE  ,"Crash landing"             , 2, 2, 0},
        {61,44,VDC_LYELLOW,"Your are 1st human on moon", 8,16, 0},
        {67,44,VDC_LYELLOW,"Learn secret of moonshine" , 1,10, 0},
        {73,44,VDC_LGREEN ,"Find gold in moon crater"  , 5,10, 0},
        {79,44,VDC_LYELLOW,"Jump over mountain"        ,22,10, 0},
        {85,44,VDC_LYELLOW,"Successful landing"        , 4, 6, 4},
        {85,47,VDC_LGREEN, "Sell moon-relic to museum" , 5, 5, 0}
    }
};

struct OpportunitycardStruct
{
    unsigned char conditionfree;
    unsigned char careernumber;
    unsigned char available;                         // ka(x)
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
struct PlayerdataStruct
{
    char name[20];           // sp$(x,0)
    char experience[11];     // sp$(x,1)
    unsigned char career;    // sp(x,0)
    unsigned char position;  // sp(x,1)
    unsigned long salary;    // sp(x,2)
    unsigned long money;     // sp(x,3)
    unsigned char happiness; // sp(x,4)
    unsigned char fame;      // sp(x,5)
    unsigned char winmoney;
    unsigned char winhappiness;
    unsigned char winfame;
    unsigned char computer;  // sp(x,6)
    unsigned char skipturn;  // sp(x,7)
    unsigned char cards[19]; // ks(x,y)
};
struct PlayerdataStruct player[4];

unsigned char whichcard[20];         //wc(x)
unsigned char cardreset[15] = {2,2,2,3,2,2,2,3,2,1,1,3,1,1,1};
unsigned char fieldinformation = 0;  //ai
unsigned char gameendflag;           // es
unsigned char anotherturn;           // ne
unsigned char playerturn;            // bs
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
    cputsxy(10,12,"Press key.");
    getkey("",1);
    windowrestore();    
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

void board_scroll()
{
    /* Explore board by scrolling board around with cursor keys */

    unsigned char choice;

    do
    {
        choice = getkey(alldirections,1);

        switch (choice)
        {
        case C_LEFT:
            if(xoffset>0)
            {
                VDC_ScrollCopy(SCREENMAPADDRESS,1,BOARD_WIDTH,BOARD_HEIGHT,xoffset,yoffset,0,2,60,23,2);
                xoffset--;
            }
            break;

        case C_RIGHT:
            if(xoffset<48)
            {
                VDC_ScrollCopy(SCREENMAPADDRESS,1,BOARD_WIDTH,BOARD_HEIGHT,xoffset,yoffset,0,2,60,23,1);
                xoffset++;
            }
            break;

        case C_UP:
            if(yoffset>0)
            {
                VDC_ScrollCopy(SCREENMAPADDRESS,1,BOARD_WIDTH,BOARD_HEIGHT,xoffset,yoffset,0,2,60,23,4);
                yoffset--;
            }
            break;

        case C_DOWN:
            if(yoffset<31)
            {
                VDC_ScrollCopy(SCREENMAPADDRESS,1,BOARD_WIDTH,BOARD_HEIGHT,xoffset,yoffset,0,2,60,23,8);
                yoffset++;
            }
            break;
        
        default:
            break;
        }

    } while (choice != C_ENTER);

    board_reposition(ring[player[playerturn].position-1].ycoord,ring[player[playerturn].position-1].xcoord);
}

// Pawn placement routines

void pawn_place(unsigned char playernumber)
{
    /* Place pawn on board. Input: player number */

    unsigned char row,col,help,x,y;

    if (player[playernumber].career==0 || player[playernumber].position==0)
    {
        row=ring[player[playernumber].position-1].ycoord;
        col=ring[player[playernumber].position-1].xcoord;
        help = 255;
        if (player[playernumber].position==0)
        {
            help = 0;
            player[playernumber].position==career[player[playernumber].career-1].startfield;
        }
        for(y=0;y<3;y++)
        {
            for(x=0;x<3;x++)
            {
                board_print(row+y,col+x,pawngraphics[y][x],ring[player[playernumber].position-1].color+VDC_A_REVERSE);
            }
        }
        board_print(row+1,col+1,0x31+playernumber,VDC_WHITE);
        if (help == 0) { player[playernumber].position == 0; }
    }
    else
    {
        row=careerfield[player[playernumber].career-1][player[playernumber].position-1].ycoord;
        col=careerfield[player[playernumber].career-1][player[playernumber].position-1].xcoord;
        board_print(row,col,0xF0+playernumber,careerfield[player[playernumber].career-1][player[playernumber].position-1].color);
    }

    board_reposition(row,col);
}

unsigned char pawn_other(unsigned char playernumber)
{
    /* Checks if other pawns are present on location of player's pawn.
       Input: player number */

    unsigned char otherpawnflag = 0;
    unsigned char x;

    for(x=0;x<4;x++)
    {
        if(player[playernumber].career==player[x].career && player[playernumber].position==player[x].position && x!=playernumber)
        { otherpawnflag == x; }
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
                player[playernumber].position==career[player[playernumber].career-1].startfield;
            }
            for(y=0;y<3;y++)
            {
                for(x=0;x<3;x++)
                {
                    board_print(ring[player[playernumber].position-1].ycoord+y,ring[player[playernumber].position-1].xcoord+x,y==2?C_BLOCKUNDER:C_SPACE,ring[player[playernumber].position-1].color+VDC_A_REVERSE);
                }
            }
            if (help == 0) { player[playernumber].position == 0; }
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

    for(x=0;x<4;x++) { pawn_erase(x); }
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
    gameendflag=0;
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
    cputsxy(62,16,"Press key.");
    getkey("",1);
    windowrestore();;
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
            for(y=0;y<opportunitycard[x].available;y++)
            {
                if(counter==card_select)
                {
                    card_select = y;
                    y = opportunitycard[x].available;
                    x=15;
                }
                else
                {
                    counter++;
                }
            }
        }
    } while (card_select == 11 && player_collegeexperience() && card_count > 1);
    if(card_select=11 && player_collegeexperience() ) { return 255; }
    opportunitycard[card_select].available--;
    return card_select;
}

char* cards_actiontext(unsigned char cardnumber)
{
    /* Return text for the action of an opportunity card.
       Input: card number */

    if(cardnumber==0) { return "Florida vacation"; }
    if(cardnumber==9) { return "Free choice"; }
    return career[opportunitycard[cardnumber].careernumber -1].name;
}

// Board field action routines

void ring_payday()
{
    // Payday

    menumakeborder(40,8,8,35);
    gotoxy(42,10);
    cputs("You landed on ");
    textcolor(COLOR_GREEN);
    cputs("START");
    textcolor(COLOR_YELLOW);
    cputs(".");
    gotoxy(42,12);
    cputs("Collect double salary:");
    VDC_Plot(13,42,C_DOLLAR,VDC_LGREEN);
    gotoxy(44,13);
    textcolor(COLOR_CYAN);
    cprintf("%6lu",player[playerturn].salary*2);
    textcolor(COLOR_YELLOW);
    cputsxy(42,15,"Press key.");
    if(!fieldinformation)
    {
        player[playerturn].money += player[playerturn].salary*2;
    }
    getkey("",1);
    windowrestore();
}

void ring_opportunity()
{
    // Opportunity knocks

    unsigned char card_select;

    menumakeborder(40,8,8,35);
    gotoxy(42,10);
    cputs("You receive an ");
    textcolor(COLOR_GREEN);
    cputs("OPPORTUNITY");
    textcolor(COLOR_YELLOW);
    cputs(" card.");
    if(!fieldinformation)
    {
        card_select = card_selectopportunity();
        if(card_select != 255)
        {
            player[playerturn].cards[card_select]++;
            gotoxy(42,12);
            cprintf("Activity:   %s",cards_actiontext(card_select));
            gotoxy(42,13);
            cprintf("Condition:  %s",opportunitycard[card_select].conditionfree==0?"Normal":"Free");
        }
        else
        {
            cputsxy(42,12,"No opportunitycards left.");
        }
    }
    cputsxy(42,15,"Press key.");
    getkey("",1);
    windowrestore();
}

void ring_paytaxes()
{
    // Pay taxes

    unsigned long tax_amount = 0;

    menumakeborder(40,8,7,35);
    gotoxy(42,10);
    cputs("You landed on ");
    textcolor(COLOR_GREEN);
    cputs("PAY TAXES");
    textcolor(COLOR_YELLOW);
    cputs(".");

    if(player[playerturn].salary<3001) { tax_amount = player[playerturn].salary / 10; }
    if(player[playerturn].salary>3000 && player[playerturn].salary<10000) { tax_amount = player[playerturn].salary / 2; }
    if(player[playerturn].salary>9999) { tax_amount = (player[playerturn].salary / 100)*90; }
    if(tax_amount > player[playerturn].money) { tax_amount = player[playerturn].money; }

    gotoxy(42,12);
    cputs("Pay: ");
    VDC_Plot(12,47,C_DOLLAR,VDC_LGREEN);
    gotoxy(49,12);
    textcolor(COLOR_CYAN);
    cprintf("%6lu",tax_amount);
    textcolor(COLOR_YELLOW);
    cputsxy(42,14,"Press key.");

    if(!fieldinformation)
    {
        player[playerturn].money -= tax_amount;
    }
    getkey("",1);
    windowrestore();
}

void ring_farming()
{
    // Farming

    unsigned char start_select = 0;

    menumakeborder(40,8,11,35);
    gotoxy(42,10);
    cputs("You may start ");
    textcolor(COLOR_GREEN);
    cputs("FARMING");
    textcolor(COLOR_YELLOW);
    cputs(".");

    if(player[playerturn].experience[4])
    {
        cputsxy(42,12,"Due to your farming experience");
        cputsxy(42,13,"no costs are involved.");
    }
    else
    {
        cputsxy(42,12,"Pay $1000 for seed and");
        cputsxy(42,13,"supplies.");
    }

    if(!fieldinformation && (player[playerturn].money>1000 || player[playerturn].experience[4]))
    {
        if(player[playerturn].computer) { start_select = 1; }
        else
        {
            cputsxy(42,15,"Do you want to start?");
            start_select = menupulldown(69,16,6);
        }
        if(start_select)
        {
            player[playerturn].career == 1;
            player[playerturn].position == 0;
            if(!player[playerturn].experience[4])
            {
                player[playerturn].money -= 1000;
            }
        }
    }

    getkey("",1);
    windowrestore();
}

// Player choices routines

// Cards submenu functions
void cards_show()
{
    /* Cards submenu: show cards */

    unsigned char opportunity_count = 0;
    unsigned char experience_count = 0;
    unsigned char height = 9;
    unsigned char x, y, ycoord;

    for(x=0;x<19;x++)
    {
        if(player[playerturn].cards[x])
        {
            if(x<15) { opportunity_count++; } else { experience_count++; }
        }
    }

    if(opportunity_count > experience_count)
    {
        height += opportunity_count;
    }
    else
    {
        height += experience_count;
    }

    ycoord = 11-(height/2);
    menumakeborder(1,ycoord,height,75);

    ycoord+=2;

    gotoxy(3,ycoord++);
    textcolor(COLOR_GREEN);
    cprintf("Player %u: ",playerturn+1);
    textcolor(COLOR_CYAN);
    cputs(player[playerturn].name);

    textcolor(COLOR_YELLOW);
    cputsxy(3,++ycoord,"Opportunity cards");
    cputsxy(42,ycoord,"Experience cards");
    cputsxy(3,++ycoord,"Count: Action:             Condition:");
    cputsxy(42,ycoord,"Count: Number of fields:");

    y = ++ycoord;

    textcolor(COLOR_CYAN);

    for(x=0;x<15;x++)
    {
        if(player[playerturn].cards[x])
        {
            gotoxy(3,y);
            cprintf("%2u     %s",player[playerturn].cards[x],cards_actiontext(x));
            cputsxy(30,y++,opportunitycard[x].conditionfree==0?"Normal":"Free");
        }
    }

    if(y==ycoord)
    {
        cputsxy(3,ycoord,"No opportunity cards owned");
    }

    y = ycoord;

    for(x=0;x<4;x++)
    {
        if(player[playerturn].cards[x+15])
        {
            gotoxy(42,y++);
            cprintf("%2u     %u",player[playerturn].cards[x],x+1);
        }
    }

    if(y==ycoord)
    {
        cputsxy(42,ycoord,"No experience cards owned");
    }

    textcolor(COLOR_YELLOW);
    cputsxy(3,ycoord+height-7,"Press key.");
    getkey("",1);

    windowrestore();
}

// Information submenu functions
void information_gamescore()
{
    /* Information submeny: Show game score */

    unsigned char x,ycoord, count;
    unsigned char height = 14;

    for(x=0;x<11;x++)
    {
        height += player[playerturn].experience[x];
    }
    ycoord = 11 - (height/2);

    menumakeborder(40,ycoord,height,34);

    ycoord+=2;

    gotoxy(42,ycoord);
    textcolor(COLOR_GREEN);
    cprintf("Player %u: ",playerturn+1);
    textcolor(COLOR_CYAN);
    cputs(player[playerturn].name);

    gotoxy(42,++ycoord);
    textcolor(COLOR_YELLOW);
    cprintf("Success Formula:  %2u+ %2u+ %2u=60",player[playerturn].winhappiness,player[playerturn].winfame,player[playerturn].winmoney);
    VDC_Plot(ycoord,59,C_HEART,VDC_LRED);
    VDC_Plot(ycoord,63,C_STAR,VDC_LYELLOW);
    VDC_Plot(ycoord,67,C_DOLLAR,VDC_LGREEN);
    
    cputsxy(42,++ycoord,"Happiness      :   ");
    textcolor(COLOR_CYAN);
    cprintf("%3u",player[playerturn].happiness);
    textcolor(COLOR_YELLOW);
    VDC_Plot(ycoord,59,C_HEART,VDC_LRED);

    cputsxy(42,++ycoord,"Fame           :   ");
    textcolor(COLOR_CYAN);
    cprintf("%3u",player[playerturn].fame);
    textcolor(COLOR_YELLOW);
    VDC_Plot(ycoord,59,C_STAR,VDC_LYELLOW);

    cputsxy(42,++ycoord,"Money          :   ");
    textcolor(COLOR_CYAN);
    cprintf("%6lu",player[playerturn].money);
    textcolor(COLOR_YELLOW);
    VDC_Plot(ycoord,59,C_DOLLAR,VDC_LGREEN);

    cputsxy(42,++ycoord,"Salary         :   ");
    textcolor(COLOR_CYAN);
    cprintf("%6lu",player[playerturn].salary);
    textcolor(COLOR_YELLOW);
    VDC_Plot(ycoord,59,C_DOLLAR,VDC_LGREEN);

    cputsxy(42,++ycoord,"College education:");

    count = ycoord;
    textcolor(COLOR_CYAN);

    for(x=0;x<4;x++)
    {
        if(player[playerturn].experience[x]) { cputsxy(42,++ycoord,pulldownmenutitles[9][x]); }
    }
    if(count==ycoord) { cputsxy(42,++ycoord,"None"); }

    textcolor(COLOR_YELLOW);
    cputsxy(42,++ycoord,"Occupation record:");

    textcolor(COLOR_CYAN);

    count = ycoord;

    for(x=0;x<7;x++)
    {
        if(player[playerturn].experience[4+x]) { cputsxy(42,++ycoord,career[x==0?x:x+1].name); }
    }
    if(count==ycoord) { cputsxy(42,++ycoord,"None"); }

    ycoord++;

    textcolor(COLOR_YELLOW);
    cputsxy(42,++ycoord,"Press key.");
    getkey("",1);
    windowrestore();
}

void information_colorlegend()
{
    char colorblock[2] = { C_BLOCKUNDER,C_BLOCKUNDER };

    menumakeborder(45,2,20,32);
    textcolor(COLOR_GREEN);
    cputsxy(47,4,"Legend of colors used");
    textcolor(COLOR_YELLOW);
    cputsxy(47,6,"Colors of board outer ring:");
    VDC_PlotString(7,47,colorblock,2,VDC_LCYAN+VDC_A_REVERSE);
    cputsxy(50,7,"Cornerfield activities");
    VDC_PlotString(8,47,colorblock,2,VDC_DYELLOW+VDC_A_REVERSE);
    cputsxy(50,8,"Receive opportunity card");
    VDC_PlotString(9,47,colorblock,2,VDC_WHITE+VDC_A_REVERSE);
    cputsxy(50,9,"Begin career");
    VDC_PlotString(10,47,colorblock,2,VDC_LPURPLE+VDC_A_REVERSE);
    cputsxy(50,10,"Various activities");

    cputsxy(47,12,"Colors of career track fields:");
    VDC_PlotString(13,47,colorblock,2,VDC_WHITE+VDC_A_REVERSE);
    cputsxy(50,13,"Various");
    VDC_PlotString(14,47,colorblock,2,VDC_LRED+VDC_A_REVERSE);
    cputsxy(50,14,"Receive happiness    ( )");
    VDC_Plot(14,72,C_HEART,VDC_LRED);
    VDC_PlotString(15,47,colorblock,2,VDC_LYELLOW+VDC_A_REVERSE);
    cputsxy(50,15,"Receive fame         (*)");
    VDC_PlotString(16,47,colorblock,2,VDC_LGREEN+VDC_A_REVERSE);
    cputsxy(50,16,"Receive money/salary ( )");
    VDC_Plot(16,72,C_DOLLAR,VDC_LGREEN);
    VDC_Plot(17,47,C_BLOCKUNDER,VDC_LYELLOW+VDC_A_REVERSE);
    VDC_Plot(17,48,C_BLOCKUNDER,VDC_LRED+VDC_A_REVERSE);
    cputsxy(50,17,"Combination happiness/fame");
    VDC_Plot(18,47,C_BLOCKUNDER,VDC_LYELLOW+VDC_A_REVERSE);
    VDC_Plot(18,48,C_BLOCKUNDER,VDC_LGREEN+VDC_A_REVERSE);
    cputsxy(50,18,"Combination happiness/money");
    cputsxy(47,20,"Press key.");
    getkey("",1);
    windowrestore();
}

void information_credits()
{
    /* Print version information and credits */

    char version[30];
    sprintf(version,
            "Version: v%i%i - %c%c%c%c%c%c%c%c-%c%c%c%c",
            VERSION_MAJOR, VERSION_MINOR,
            BUILD_YEAR_CH0, BUILD_YEAR_CH1, BUILD_YEAR_CH2, BUILD_YEAR_CH3, BUILD_MONTH_CH0, BUILD_MONTH_CH1, BUILD_DAY_CH0, BUILD_DAY_CH1,BUILD_HOUR_CH0, BUILD_HOUR_CH1, BUILD_MIN_CH0, BUILD_MIN_CH1);
    menumakeborder(5,5,11,70);
    textcolor(COLOR_CYAN);
    printcentered("C A R E E R S",7,7,70);
    textcolor(COLOR_WHITE);
    printcentered(version,7,8,70);
    textcolor(COLOR_YELLOW);
    printcentered("Written in 2022 by Xander Mol",7,10,70);
    printcentered("Converted to C from the C128 original written in BASIC in 1992",7,11,70);
    printcentered("See source code on Github for full code credits.",7,13,70);
    textcolor(COLOR_GREEN);
    printcentered("Press a key.",7,15,70);
    textcolor(COLOR_YELLOW);
    getkey("",1);
    windowrestore();
}

// Player turn functions

void turnhuman()
{
    /* Turn for the human players */

    unsigned char choice, yesno;

    do
    {
        choice = menumain();
        switch (choice)
        {
        case 12:
            yesno = areyousure();
            if(yesno==1) { gameendflag=6; board_reset(); }
            break;

        case 13:
            yesno = areyousure();
            if(yesno==1) { gameendflag=5; }
            break;

        case 41:
            cards_show();
            break;

        case 52:
            information_gamescore();
            break;
        
        case 53:
            information_colorlegend();
            break;

        case 54:
            menumakeborder(60,10,6,18);
            cputsxy(62,12,"Move board around");
            cputsxy(62,13,"with cursor keys");
            cputsxy(62,14,"or joystick.");
            cputsxy(62,15,"RETURN/fire=end.");
            board_scroll();
            windowrestore();
            break;
        
        case 55:
            information_credits();
            break;

        default:
            break;
        }
    } while (choice!=11 && choice!=12 && choice!=13 && choice!=22);
}

void turncomputer()
{
    /* Turn for the computer players */

    cputsxy(61,8,"Press key.");
    getkey("",1);
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
    
    unsigned char error;

    /* Game intro */
    char joys[10];
    char music[4];
    char validkeys[6] = {'c','C','m', 'M', C_ENTER, 0 };
    unsigned char key;

    /* Title screen */
    //VDC_LoadScreen("ludo.tscr",LOADSAVEBUFFER,1,1);

    /* Load and read game config file */
    //loadconfigfile();

    // Load game board screen map to memory
    VDC_LoadScreen("careers.scrn",bootdevice,SCREENMAPADDRESS,1);

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

    /* Load and start first music file */
    //LoadMusic("careers.mus1");

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
    menuplacebar();
    VDC_CopyViewPortToVDC(SCREENMAPADDRESS,1,BOARD_WIDTH,BOARD_HEIGHT,xoffset,yoffset,0,2,60,23);

    //Ask for loading save game
    menumakeborder(40,8,6,35);
    cputsxy(42,10,"Load old game?");
    choice = menupulldown(69,11,6);
    windowrestore();
    //if(choice==1) { gameendflag=7; loadgame(); }

    srand(clock());

    //Main game loop
    do
    {
        if(gameendflag!=7) { game_reset(); inputofnames(); }
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
            if(player[playerturn].computer==0)
            {
                turnhuman();
            }
            else
            {
                cputsxy(61,6,"Computer plays.");
                turncomputer();
            }

            if(gameendflag==0)
            {
                dice_throw(player[playerturn].career==0?2:1);
            }

            if(anotherturn!=0)
            {
                anotherturn=0;
            }
            else
            {
                playerturn++;
                if(playerturn>3) { playerturn=0; }
            }
        
        } while (gameendflag!=5 && gameendflag!=6);

    } while (gameendflag!=5);

    //if(musicnumber) { StopMusic(); }

    VDC_Exit();
    joy_uninstall();
    cputsxy(0,0,"Thanks for playing, goodbye.");
}