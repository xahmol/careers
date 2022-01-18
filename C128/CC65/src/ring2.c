/*
CAREERS

Routines for left part of board outer ring

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

#pragma code-name ("OVERLAY2");
#pragma rodata-name ("OVERLAY2");

// Outer ring field part 2: left ring

void ring_payfoodbills()
{
    // Pay food bills

    menumakeborder(40,8,7,35);
    gotoxy(42,10);
    cputs("You have to ");
    textcolor(COLOR_GREEN);
    cputs("PAY FOOD BILLS");
    textcolor(COLOR_YELLOW);
    cputs(".");

    cputsxy(42,12,"Cost:   ");
    cprintf("%lu",player[playerturn].money/4);
    VDC_Plot(12,48,C_DOLLAR,VDC_LGREEN);

    if(!fieldinformation)
    {
        player[playerturn].money -= (player[playerturn].money/4);
    }

    cputsxy(42,14,"Press key.");
    getkey("",1);
    windowrestore();
}

void ring_business()
{
    // Business

    unsigned char free_entry = 0;
    unsigned char start_select = 0;

    menumakeborder(40,8,11,35);
    gotoxy(42,10);
    cputs("You may join ");
    textcolor(COLOR_GREEN);
    cputs("BIG BUSINESS");
    textcolor(COLOR_YELLOW);
    cputs(".");

    if(player[playerturn].experience[5] || player_collegeexperience())
    {
        cputsxy(42,12,"Due to your experience/education");
        cputsxy(42,13,"no costs are involved.");
        free_entry=1;
    }
    else
    {
        cputsxy(42,12,"Pay $500 employment fee.");
    }

    if(!fieldinformation)
    {
        if(player[playerturn].money>499 || free_entry)
        {
            if(player[playerturn].computer)
            {
                start_select=1;
            }
            else
            {
                cputsxy(42,15,"Do you want to start?");
                start_select = menupulldown(69,16,6);
            }
        }
        if(start_select==1)
        {
            player[playerturn].career = 3;
            player[playerturn].position = 0;
            if(!free_entry) { player[playerturn].money -= 500; }
        }
    }

    cputsxy(42,17,"Press key.");
    getkey("",1);
    windowrestore();
}

void ring_artgallery()
{
    // Art gallery

    unsigned char bought = 0;
    unsigned char maxbought = 0;

    menumakeborder(40,5,16,35);
    gotoxy(42,7);
    cputs("You are at the ");
    textcolor(COLOR_GREEN);
    cputs("ART GALLERY");
    textcolor(COLOR_YELLOW);
    cputs(".");

    cputsxy(42,9,"You may buy old masters");
    cputsxy(42,10,"for $3000 each. Throw");
    cputsxy(42,11,"one die and score 1 *");
    cputsxy(42,12,"times the number thrown");
    cputsxy(42,13,"for each picture bought.");
    cputsxy(42,14,"Limit: 2 to a customer.");

    if(!fieldinformation && player[playerturn].money>2999)
    {
        cputsxy(42,16,"How many do you wamt to buy?");
        if(player[playerturn].computer)
        {
            if(player[playerturn].fame<20)
            {
                bought = (player[playerturn].money>5999 && player[playerturn].fame<19)? 2:1;
            }
            gotoxy(42,17);
            textcolor(COLOR_CYAN);
            cprintf("%u",bought);
            textcolor(COLOR_YELLOW);
        }
        else
        {
            maxbought = player[playerturn].money / 3000;
            if(maxbought > 2) { maxbought =2; }
            bought = input_number(42,15,0,maxbought);
        }
        player[playerturn].money -= bought*3000;
        if(bought)
        {
            dice_throw(bought);
            player[playerturn].fame += dice_total;
        }
        gotoxy(42,18);
        cprintf("* %u received.",dice_total);
    }

    cputsxy(42,20,"Press key.");
    getkey("",1);
    windowrestore();
}

void ring_sea()
{
    // Sea

    unsigned char free_entry = 0;
    unsigned char start_select = 0;

    menumakeborder(40,8,11,35);
    gotoxy(42,10);
    cputs("You may go to ");
    textcolor(COLOR_GREEN);
    cputs("SEA");
    textcolor(COLOR_YELLOW);
    cputs(".");

    if(player[playerturn].experience[6])
    {
        cputsxy(42,12,"Due to your experience");
        cputsxy(42,13,"no costs are involved.");
        free_entry=1;
    }
    else
    {
        cputsxy(42,12,"Pay $100 for Union dues.");
    }

    if(!fieldinformation)
    {
        if(player[playerturn].money>99 || free_entry)
        {
            if(player[playerturn].computer)
            {
                start_select = 1;
            }
            else
            {
                cputsxy(42,15,"Do you want this?");
                start_select = menupulldown(69,16,6);
            }
            if(start_select==1)
            {
                player[playerturn].career = 4;
                player[playerturn].position = 0;
                if(!free_entry) { player[playerturn].money -= 100; }
            }
        }
    }

    cputsxy(42,17,"Press key.");
    getkey("",1);
    windowrestore();
}

void ring_parkbench()
{
    // Park bench

    menumakeborder(40,6,14,35);
    gotoxy(42,8);
    cputs("You sit on a ");
    textcolor(COLOR_GREEN);
    cputs("PARK BENCH");
    textcolor(COLOR_YELLOW);
    cputs(".");

    cputsxy(42,10,"You are unemployed and must throw");
    cputsxy(42,11,"7, 11 or double to move on. You");
    cputsxy(42,12,"may not use opportunity or expe-");
    cputsxy(42,13,"rience cards. But you may spend");
    cputsxy(42,14,"half your cash for a new suit of");
    cputsxy(42,15,"clothes before any throw and go");
    cputsxy(42,16,"on that throw.");

    cputsxy(42,18,"Press key.");
    getkey("",1);
    windowrestore();
}