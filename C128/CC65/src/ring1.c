/*
CAREERS

Routines for lower part of board outer ring

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

#pragma code-name ("OVERLAY1");
#pragma rodata-name ("OVERLAY1");

// Outer ring field part 1: lower ring

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
            player[playerturn].career = 1;
            player[playerturn].position = 0;
            if(!player[playerturn].experience[4])
            {
                player[playerturn].money -= 1000;
            }
        }
    }

    cputsxy(42,15,"Press key.");
    getkey("",1);
    windowrestore();
}

void ring_automobileshow()
{
    // Automobile show

    signed char bought = 0;
    signed char maxbought;
    signed char maxhappiness;

    menumakeborder(40,5,15,35);
    gotoxy(42,7);
    cputs("You are at the ");
    textcolor(COLOR_GREEN);
    cputs("AUTOMOBILE SHOW");
    textcolor(COLOR_YELLOW);
    cputs(".");

    cputsxy(42, 9,"You may spend up to 1 year's");
    cputsxy(42,10,"salary for new car.");
    cputsxy(42,11,"Score 1   for each $1000");
    VDC_Plot(11,50,C_HEART,VDC_LRED);
    cputsxy(42,12,"you spend.");
    if(player[playerturn].happiness)
    {
        cputsxy(42,13,"Lose  1   for just looking.");
        VDC_Plot(13,50,C_HEART,VDC_LRED);
    }
    if(!fieldinformation)
    {
        if(player[playerturn].money>999 && player[playerturn].salary>999)
        {
            cputsxy(42,15,"How many times $1000 do you");
            cputsxy(42,16,"want to spend?");
            if(player[playerturn].computer)
            {
                bought = (player[playerturn].money-2000)/1000;
                if(bought*1000>player[playerturn].salary) { bought = player[playerturn].salary/1000; }
                maxhappiness = 20 - player[playerturn].happiness;
                if(bought>0 && maxhappiness>0)
                {
                    if(bought>maxhappiness) { bought= maxhappiness; }
                }
                else { bought=0; }
                textcolor(COLOR_CYAN);
                gotoxy(42,17);
                cprintf("%u",bought);
                textcolor(COLOR_YELLOW);
            }
            else
            {
                maxbought = player[playerturn].money/1000;
                if(maxbought*1000>player[playerturn].salary) { maxbought = player[playerturn].salary/1000; }
                bought = input_number(42,17,0,maxbought);
            }
            player[playerturn].money -= bought*1000;
            player[playerturn].happiness += bought;
        }
        if(player[playerturn].happiness>0 && bought==0)
        {
            player[playerturn].happiness--;
        }
    }
    cputsxy(42,19,"Press key.");
    getkey("",1);
    windowrestore();
}

void ring_college()
{
    // College

    unsigned char start_select = 0;

    menumakeborder(40,8,10,35);
    gotoxy(42,10);
    cputs("You may enter ");
    textcolor(COLOR_GREEN);
    cputs("COLLEGE");
    textcolor(COLOR_YELLOW);
    cputs(".");

    if(player[playerturn].experience[0] ||
       player[playerturn].experience[1] ||
       player[playerturn].experience[2] ||
       player[playerturn].experience[3])
    {
        cputsxy(42,12,"However, you already did go");
        cputsxy(42,13,"to college and may not enter");
        cputsxy(42,14,"again. Throw again.");
        start_select = 255;
    }
    if(player[playerturn].money<500 && !start_select)
    {
        cputsxy(42,12,"However, you do not have");
        cputsxy(42,13,"money for tuition fee.");
        start_select = 254;
    }
    else
    {
        cputsxy(42,12,"Cost:");
        VDC_Plot(12,48,C_DOLLAR,VDC_LGREEN);
        textcolor(COLOR_CYAN);
        cputsxy(50,12,"500");
        textcolor(COLOR_YELLOW);
    }
    if(!fieldinformation)
    {
        if(!start_select)
        {
            if(player[playerturn].computer)
            {
                start_select=1;
            }
            else
            {
                cputsxy(42,14,"Do you want to enter?");
                start_select=menupulldown(69,15,6);
                cputsxy(42,14,"                     ");
            }
            if(start_select==1)
            {
                player[playerturn].career = 2;
                player[playerturn].position = 0;
                player[playerturn].money -= 500;
            }
        }
        if(start_select==255)
        {
            anotherturn = 1;
        }
    }

    cputsxy(42,16,"Press key.");
    getkey("",1);
    windowrestore();
}

void ring_hospital()
{
    // Hospital

    menumakeborder(40,6,15,35);
    gotoxy(42,8);
    cputs("You are in the ");
    textcolor(COLOR_GREEN);
    cputs("HOSPITAL");
    textcolor(COLOR_YELLOW);
    cputs(".");

    cputsxy(42,10,"You are laid up until you throw");
    cputsxy(42,11,"5 or less. You may not use op-");
    cputsxy(42,12,"portunity or experience cards;");
    cputsxy(42,13,"but you may pay Doctor (if no");
    cputsxy(42,14,"Doctor, pay Bank) half your");
    cputsxy(42,15,"Salary for Special treatment");
    cputsxy(42,16,"before any throw and go on");
    cputsxy(42,17,"that throw.");

    cputsxy(42,19,"Press key.");
    getkey("",1);
    windowrestore();
}