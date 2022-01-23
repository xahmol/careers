/*
CAREERS

Routines for career fields, part 2

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

#pragma code-name ("OVERLAY6");
#pragma rodata-name ("OVERLAY6");

// Career fields part 2
void career_getopportunitycard(unsigned char careernr, unsigned char position)
{
    unsigned char cards = careerfield[careernr][position].amount1;
    unsigned char x, selected;

    gotoxy(32,14);
    cprintf("Receive: %u opportunity card%s.",cards,(cards==1)?"":"s");

    if(!fieldinformation)
    {
        for(x=0;x<cards;x++)
        {
            selected = card_selectopportunity();
            if(selected==255)
            {
                cputsxy(32,16+x,"No opportunitycards left.");
                x=cards;
            }
            else
            {
                player[playerturn].cards[selected]++;
                gotoxy(32,16+x);
                cprintf("Card %u: %s %s",x+1,cards_actiontext(selected),opportunitycard[selected].conditionfree==0?"Normal":"Free");

            }
        }
    }
}

void career_getsalary(unsigned char careernr, unsigned char position)
{
    unsigned long salary = careerfield[careernr][position].amount1*1000;
    gotoxy(32,14);
    cprintf("Receive:   %lu salary increase.",salary);
    VDC_Plot(14,41,C_DOLLAR,VDC_LGREEN);
    if(!fieldinformation)
    {
        player[playerturn].salary += salary;
    }
}

void career_loosehalfsalary()
{
    unsigned long salary = player[playerturn].salary/2;

    gotoxy(32,14);
    cprintf("Lose   :   %lu salary",salary);
    VDC_Plot(14,41,C_DOLLAR,VDC_LGREEN);
    if(!fieldinformation)
    {
        player[playerturn].salary -= salary;
    }
}

void career_getmoneyandfame(unsigned char careernr, unsigned char position)
{
    unsigned long money = careerfield[careernr][position].amount2*1000;

    gotoxy(32,14);
    cprintf("Receive:   %u and",careerfield[careernr][position].amount1);
    VDC_Plot(14,41,C_STAR,VDC_LYELLOW);
    gotoxy(43,15);
    cprintf("%lu",money);
    VDC_Plot(15,41,C_DOLLAR,VDC_LGREEN);
    if(!fieldinformation)
    {
        player[playerturn].fame += careerfield[careernr][position].amount1;
        player[playerturn].money += money;
    }
}

void career_loosehalffame()
{
    unsigned char fame = player[playerturn].fame/2;

    gotoxy(32,14);
    cprintf("Lose   :   %u",fame);
    VDC_Plot(14,41,C_STAR,VDC_LYELLOW);
    if(!fieldinformation)
    {
        player[playerturn].fame -= fame;
    }
}

void career_getfamenohappiness(unsigned char careernr, unsigned char position)
{
    gotoxy(32,14);
    cprintf("Receive:   %u,",careerfield[careernr][position].amount1);
    VDC_Plot(14,41,C_STAR,VDC_LYELLOW);
    cputsxy(32,15,"but you lose all your happiness.");
    if(!fieldinformation)
    {
        player[playerturn].fame += careerfield[careernr][position].amount1;
        player[playerturn].happiness = 0;
    }
}

void career_getsalarytimesdie(unsigned char careernr, unsigned char position)
{
    unsigned long salary = careerfield[careernr][position].amount1*1000;

    gotoxy(32,14);
    cprintf("Receive:   %lu salary * throw of one die.",salary);
    VDC_Plot(14,41,C_DOLLAR,VDC_LGREEN);
    if(!fieldinformation)
    {
        dice_throw(1);
        cputsxy(32,16,"Received: ");
        textcolor(COLOR_CYAN);
        cprintf("%lu salary increase.",salary*dice_total);
        textcolor(COLOR_YELLOW);
        player[playerturn].salary += salary*dice_total;
    }
}

void career_throwagain()
{
    cputsxy(32,14,"Throw again.");
    if(!fieldinformation)
    {
        anotherturn=1;
    }
}

void career_looseallfame()
{
    cputsxy(32,14,"Lose all your fane.");
    if(!fieldinformation)
    {
        player[playerturn].fame = 0;
    }
}

void career_getmoney(unsigned char careernr, unsigned char position)
{
    unsigned long money = careerfield[careernr][position].amount1*1000;
    gotoxy(32,14);
    cprintf("Receive:   %lu",money);
    VDC_Plot(14,41,C_DOLLAR,VDC_LGREEN);
    if(!fieldinformation)
    {
        player[playerturn].money += money;
    }
}

void career_loosehalfmoney()
{
    unsigned long money = player[playerturn].money/2;

    gotoxy(32,14);
    cprintf("Lose   :   %lu",money);
    VDC_Plot(14,41,C_DOLLAR,VDC_LGREEN);
    if(!fieldinformation)
    {
        player[playerturn].money -= money;
    }
}

void career_skipturn()
{
    cputsxy(32,14,"Lose next turn.");
    if(!fieldinformation) { player[playerturn].skipturn=1; }
}

void career_getfame(unsigned char careernr, unsigned char position)
{
    gotoxy(32,14);
    cprintf("Receive:   %u",careerfield[careernr][position].amount1);
    VDC_Plot(14,41,C_STAR,VDC_LYELLOW);
    if(!fieldinformation)
    {
        player[playerturn].fame += careerfield[careernr][position].amount1;
    }
}