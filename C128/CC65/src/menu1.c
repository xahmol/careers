/*
CAREERS

Routines for menu functions, part 1

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
#include "main.h"

#pragma code-name ("OVERLAY7");
#pragma rodata-name ("OVERLAY7");

// Menu functions part 1

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
            cprintf("%2u     %u",player[playerturn].cards[x+15],x+1);
        }
    }

    if(y==ycoord)
    {
        cputsxy(42,ycoord,"No experience cards owned");
    }

    textcolor(COLOR_YELLOW);
    presskeyprompt(3,ycoord+height-7);
    windowrestore();
}

// Information submenu functions
void information_gamescore()
{
    /* Information submenu: Show game score */

    unsigned char x,ycoord, count;
    unsigned char height = 14;

    for(x=0;x<11;x++)
    {
        height += player[playerturn].experience[x]?1:0;
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
        if(player[playerturn].experience[4+x])
        {
            gotoxy(42,++ycoord);
            cprintf("%s",career[x==0?x:x+1].name);
        }
    }
    if(count==ycoord) { cputsxy(42,++ycoord,"None"); }

    ycoord++;

    textcolor(COLOR_YELLOW);
    presskeyprompt(42,++ycoord);
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
    presskeyprompt(47,20);
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
    printcentered("C A R E E R S",7,7,68);
    textcolor(COLOR_WHITE);
    printcentered(version,7,8,68);
    textcolor(COLOR_YELLOW);
    printcentered("Written in 2022 by Xander Mol",7,10,68);
    printcentered("Converted to C from the C128 original written in BASIC in 1992",7,11,68);
    printcentered("See source code on Github for full code credits.",7,13,68);
    textcolor(COLOR_GREEN);
    printcentered("Press a key.",7,15,68);
    textcolor(COLOR_YELLOW);
    getkey("",1);
    windowrestore();
}

void musicnext()
{
    /* Funtion to load and start next music track */

    char fname[25]="careers.mus";
    unsigned char len = strlen(fname);

    StopMusic();
    if(++musicnumber>3) { musicnumber = 1;}
    fname[len]=48+musicnumber;
    fname[len+1]=0;
    LoadMusic(fname);
}
