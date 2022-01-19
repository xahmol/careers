/*
CAREERS

Routines for right part of board outer ring

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

#pragma code-name ("OVERLAY4");
#pragma rodata-name ("OVERLAY4");

// Outer ring field part 4: right ring

void ring_stockmarket()
{
    unsigned char bought = 0;
    unsigned char maxbought = 0;
    unsigned long salestotal = 0;
    unsigned char x;

    menumakeborder(40,5,16,35);
    gotoxy(42,7);
    textcolor(COLOR_GREEN);
    cputs("STOCK MARKET");
    textcolor(COLOR_YELLOW);

    cputsxy(42, 9,"You may buy blocks of stock");
    cputsxy(42,10,"for $3000 each. Throw 1 die");
    cputsxy(42,11,"and sell out for $1000 times");
    cputsxy(42,12,"the number thrown. Throw");
    cputsxy(42,13,"once for each block bought.");
    cputsxy(42,14,"No limit on purchases.");

    if(!fieldinformation && player[playerturn].money>2999)
    {
        cputsxy(42,16,"How many blocks you want to buy?");
        maxbought = player[playerturn].money/3000;
        if(player[playerturn].computer)
        {
            bought = maxbought;
            gotoxy(42,17);
            textcolor(COLOR_CYAN);
            cprintf("%lu",bought);
            textcolor(COLOR_YELLOW);
        }
        else
        {
            bought = input_number(42,17,0,maxbought);
        }
        for(x=0;x<bought;x++)
        {
            dice_throw(1);
            salestotal += dice_total * 1000;
        }
        cputsxy(42,18,(salestotal>(bought*3000))?"Profit: $":"Loss: $");
        textcolor(COLOR_CYAN);
        cprintf("%lu",(salestotal>bought*3000)?salestotal-(bought*3000):(bought*3000)-salestotal);
        textcolor(COLOR_YELLOW);
        player[playerturn].money += salestotal;
        player[playerturn].money -= bought*3000;
    }

    cputsxy(42,20,"Press key.");
    getkey("",1);
    windowrestore();
}

void ring_uranium()
{
    // Uranium prospecting

    unsigned char free_entry = 0;
    unsigned char start_select = 0;

    menumakeborder(40,8,11,35);
    gotoxy(42,10);
    cputs("You may go ");
    textcolor(COLOR_GREEN);
    cputs("URANIUM PROSPECTING");
    textcolor(COLOR_YELLOW);
    cputs(".");

    if(player[playerturn].experience[9] || player[playerturn].experience[3])
    {
        cputsxy(42,12,"Due to your experience/education");
        cputsxy(42,13,"no costs are involved.");
        free_entry=1;
    }
    else
    {
        cputsxy(42,12,"Pay $4000 for equipment.");
    }

    if(!fieldinformation)
    {
        if(player[playerturn].money>3999 || free_entry)
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
                player[playerturn].career = 7;
                player[playerturn].position = 0;
                if(!free_entry) { player[playerturn].money -= 4000; }
            }
        }
    }

    cputsxy(42,17,"Press key.");
    getkey("",1);
    windowrestore();
}

void ring_yachtharbor()
{
    unsigned char bought = 4;
    unsigned char maxhappiness = 0;
    unsigned long maxmoney = 0;
    unsigned long spent = 0;

    menumakeborder(40,5,17,35);
    gotoxy(42,7);
    textcolor(COLOR_GREEN);
    cputs("YACHT HARBOR");
    textcolor(COLOR_YELLOW);

    cputsxy(42, 9,"Yachts for sale.");
    cputsxy(42,10,"Score happiness as follows:");
    cputsxy(42,11,"Pay:      Score:");
    cputsxy(42,12,"   2000    4");
    VDC_Plot(12,42,C_DOLLAR,VDC_LGREEN);
    VDC_Plot(12,55,C_HEART,VDC_LRED);
    cputsxy(42,13,"   8000    8");
    VDC_Plot(13,42,C_DOLLAR,VDC_LGREEN);
    VDC_Plot(13,55,C_HEART,VDC_LRED);
    cputsxy(42,14,"  16000   12");
    VDC_Plot(14,42,C_DOLLAR,VDC_LGREEN);
    VDC_Plot(14,55,C_HEART,VDC_LRED);

    if(!fieldinformation && player[playerturn].money>1999)
    {
        cputsxy(42,16,"How much do you want to spend?");
        if(player[playerturn].computer)
        {
            if(player[playerturn].money>19999)
            {
                maxmoney = player[playerturn].money-20000;
            }
            else
            {
                maxmoney = 0;
            }
            if(player[playerturn].happiness<20)
            {
                maxhappiness = 20 - player[playerturn].happiness;
            }
            if(maxmoney>2000 && maxhappiness>0) { bought = 1; }
            if(maxmoney>8000 && maxhappiness>7) { bought = 2; }
            if(maxmoney>16000 && maxhappiness>11) { bought = 3; }
        }
        else
        {
            do
            {
                bought = menupulldown(60,17,8);
                if(bought==2 && player[playerturn].money<7999) { bought=0; }
                if(bought==3 && player[playerturn].money<15999) { bought=0; }
            } while (!bought);            
        }
        switch (bought)
        {
        case 1:
            spent = 2000;
            maxhappiness = 4;
            break;

        case 2:
            spent = 8000;
            maxhappiness = 8;
            break;
        
        case 3:
            spent = 16000;
            maxhappiness = 12;
            break;
        
        case 4:
            spent = 0;
            maxhappiness = 0;
            break;
        
        default:
            break;
        }

        cputsxy(42,18,"Cost: ");
        textcolor(COLOR_CYAN);
        cprintf("%lu",spent);
        textcolor(COLOR_YELLOW);
        player[playerturn].money -= spent;
        player[playerturn].happiness-= maxhappiness;
    }

    cputsxy(42,20,"Press key.");
    getkey("",1);
    windowrestore();
}

void ring_moon()
{
    // Expedition to the moon

    unsigned char free_entry = 0;
    unsigned char start_select = 0;

    menumakeborder(40,8,11,35);
    gotoxy(42,10);
    cputs("May join ");
    textcolor(COLOR_GREEN);
    cputs("EXPEDITION TO THE MOON");
    textcolor(COLOR_YELLOW);
    cputs(".");

    if(player[playerturn].experience[10] || player[playerturn].experience[2])
    {
        cputsxy(42,12,"Due to your experience/education");
        cputsxy(42,13,"no costs are involved.");
        free_entry=1;
    }
    else
    {
        cputsxy(42,12,"Pay $5000 for research.");
    }

    if(!fieldinformation)
    {
        if(player[playerturn].money>4999 || free_entry)
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
                player[playerturn].career = 8;
                player[playerturn].position = 0;
                if(!free_entry) { player[playerturn].money -= 5000; }
            }
        }
    }

    cputsxy(42,17,"Press key.");
    getkey("",1);
    windowrestore();
}