/*
CAREERS

Routines for upper part of board outer ring

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

#pragma code-name ("OVERLAY3");
#pragma rodata-name ("OVERLAY3");

// Outer ring field part 3: upper ring

void ring_payrent()
{
    // Pay rent

    unsigned long rent = 0;

    menumakeborder(40,8,7,35);
    gotoxy(42,10);
    cputs("You have to ");
    textcolor(COLOR_GREEN);
    cputs("PAY RENT");
    textcolor(COLOR_YELLOW);
    cputs(".");

    rent = player[playerturn].salary / 2;
    if(rent > player[playerturn].money ) { rent = player[playerturn].money; }

    cputsxy(42,12,"Cost:   ");
    cprintf("%lu",rent);
    VDC_Plot(12,48,C_DOLLAR,VDC_LGREEN);

    if(!fieldinformation)
    {
        player[playerturn].money -= rent;
    }

    presskeyprompt(42,14);
    windowrestore();
}

void ring_politics()
{
    // Politics

    unsigned char free_entry = 0;
    unsigned char start_select = 0;

    menumakeborder(40,8,11,35);
    gotoxy(42,10);
    cputs("You may run for office ");
    textcolor(COLOR_GREEN);
    cputs("(POLITICS)");
    textcolor(COLOR_YELLOW);

    if(player[playerturn].experience[7] || player[playerturn].experience[0])
    {
        cputsxy(42,12,"Due to your experience/education");
        cputsxy(42,13,"no costs are involved.");
        free_entry=1;
    }
    else
    {
        cputsxy(42,12,"Pay $3000 for campaign fund.");
    }

    if(!fieldinformation)
    {
        if(player[playerturn].money>2999 || free_entry)
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
                player[playerturn].career = 5;
                player[playerturn].position = 0;
                if(!free_entry) { player[playerturn].money -= 3000; }
            }
        }
    }

    presskeyprompt(42,17);
    windowrestore();
}

void ring_shoppingspree()
{
    unsigned long spent = 0;
    menumakeborder(40,8,15,35);
    gotoxy(42,10);
    textcolor(COLOR_GREEN);
    cputs("SHOPPING SPREE");
    textcolor(COLOR_YELLOW);

    if(!player[playerturn].money)
    {
        cputsxy(42,12,"Because you do not have money");
        cputsxy(42,13,"nothing has been bought.");
    }
    else
    {
        cputsxy(42,12,"Throw 1 die to find out");
        cputsxy(42,13,"what has been spent on");
        cputsxy(42,14,"a shopping spree.");
        cputsxy(42,15,"Pay number thrown times");
        cputsxy(42,16,"10% of your cash on hand.");

        if(!fieldinformation)
        {
            dice_throw(1);
            spent = (player[playerturn].money/10)*dice_total;
            cputsxy(42,18,"Cost:   ");
            cprintf("%lu",spent);
            VDC_Plot(18,48,C_DOLLAR,VDC_LGREEN);
            player[playerturn].money -= spent;
        }
    }

    presskeyprompt(42,20);
    windowrestore();
}

void ring_hollywood()
{
    // Hollywood

    unsigned char free_entry = 0;
    unsigned char start_select = 0;

    menumakeborder(40,8,11,35);
    gotoxy(42,10);
    cputs("You may enter ");
    textcolor(COLOR_GREEN);
    cputs("HOLLYWOOD");
    textcolor(COLOR_YELLOW);
    cputs(".");

    if(player[playerturn].experience[8])
    {
        cputsxy(42,12,"Due to your experience");
        cputsxy(42,13,"no costs are involved.");
        free_entry=1;
    }
    else
    {
        cputsxy(42,12,"Pay $1000 for new clothes.");
    }

    if(!fieldinformation)
    {
        if(player[playerturn].money>999 || free_entry)
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
                player[playerturn].career = 6;
                player[playerturn].position = 0;
                if(!free_entry) { player[playerturn].money -= 1000; }
            }
        }
    }
    presskeyprompt(42,17);
    windowrestore();
}

void ring_floridavacation()
{
    // Park bench

    menumakeborder(40,6,14,35);
    gotoxy(42,8);
    textcolor(COLOR_GREEN);
    cputs("FLORIDA VACATION");
    textcolor(COLOR_YELLOW);

    cputsxy(42,10,"Score 4   when you land here");
    VDC_Plot(10,50,C_HEART,VDC_LRED);
    cputsxy(42,11,"and   2   each time you stay.");
    VDC_Plot(11,50,C_HEART,VDC_LRED);
    cputsxy(42,12,"You may stay on throws 7 or");
    cputsxy(42,13,"less. But you may leave on");
    cputsxy(42,14,"any throw.");

    if(!fieldinformation) { player[playerturn].happiness += 4; }

    presskeyprompt(42,18);
    windowrestore();
}

void computer_playopportunitycards()
{
    unsigned char x,helpcar,helppos,scoremax,cardselect;
    unsigned char presentcar = player[playerturn].career;
    unsigned char presentpos = player[playerturn].position;

     // Decide best opportunity card to use if any
    if(presentcar) { return; }

    for(x=0;x<15;x++)
    {
        if(player[playerturn].cards[x])
        {
            whichcard[x]=5;
            helpcar=opportunitycard[x].careernumber;
            if(player[playerturn].happiness<20)
            {
                if(helpcar==1 || helpcar==2 || helpcar==4 || helpcar==7)
                {
                    whichcard[x]+=10;
                }
            }
            if(player[playerturn].fame<20)
            {
                if(helpcar==5 || helpcar==6 || helpcar==8)
                {
                    whichcard[x]+=11;
                }
            }
            if(player[playerturn].money<20000)
            {
                if(helpcar==3 || helpcar==7 || helpcar==8)
                {
                    whichcard[x]+=5;
                }
            }
            cardselect=0;
            if(helpcar==1 && player[playerturn].experience[4]) { cardselect=1; }
            if(helpcar==3 && (player_collegeexperience() || player[playerturn].experience[5])) { cardselect=1; }
            if(helpcar==4 && player[playerturn].experience[6]) { cardselect=1; }
            if(helpcar==5 && (player[playerturn].experience[0] || player[playerturn].experience[7])) { cardselect=1; }
            if(helpcar==6 && player[playerturn].experience[8]) { cardselect=1; }
            if(helpcar==7 && (player[playerturn].experience[3] || player[playerturn].experience[9])) { cardselect=1; }
            if(helpcar==8 && (player[playerturn].experience[2] || player[playerturn].experience[10])) { cardselect=1; }
            if(helpcar==9)
            {
                whichcard[x]=(player[playerturn].money>3999)?100:0;
            }
            if(x==9 || x==10 || x>11) { cardselect=1; }
            if(!cardselect)
            {
                if((helpcar==1 || helpcar==6) && player[playerturn].money<1000) { whichcard[x]=0; }
                if((helpcar==2 || helpcar==3) && player[playerturn].money<500) { whichcard[x]=0; }
                if(helpcar==4 && player[playerturn].money<100) { whichcard[x]=0; }
                if(helpcar==5 && player[playerturn].money<3000) { whichcard[x]=0; }
                if(helpcar==7 && player[playerturn].money<4000) { whichcard[x]=0; }
                if(helpcar==8 && player[playerturn].money<5000) { whichcard[x]=0; }
            }
            else
            {
                whichcard[x]+=100;
            }
        }
    }

    // Use highest score opportunity card if any
    cardselect=0;
    scoremax=0;
    for(x=0;x<15;x++)
    {
        if(whichcard[x]>scoremax)
        {
            scoremax=whichcard[x];
            cardselect=x+1;
        }
    }

    if(cardselect)
    {
        gameendflag=8;
        helpcar=opportunitycard[cardselect-1].careernumber;
        helppos=opportunitycard[cardselect-1].conditionfree;
        if(helppos)
        {
            if(helpcar==1)
            {
                player[playerturn].experience[4]++;
            }
            else
            {
                player[playerturn].experience[2+helpcar]++;
            }
        }
        if(cardselect==7)
        {
            helpcar=(player[playerturn].money>4999)?8:7;
        }
        if(cardselect==6)
        {
            helpcar=0;
            helppos=25;
        }
        else
        {
            helppos=0;
        }
        player[playerturn].cards[cardselect-1]--;
        opportunitycard[cardselect-1].available++;
        pawn_erase(playerturn);
        player[playerturn].position=helppos;
        player[playerturn].career=helpcar;
        pawn_place(playerturn);
        menumakeborder(35,8,7,40);
        cputsxy(37,10,"Computer uses opportunity card.");
        gotoxy(37,12);
        cprintf("%s (%s)",cards_actiontext(cardselect-1),opportunitycard[cardselect-1].conditionfree?"Free":"Normal");
        presskeyprompt(37,14);
        windowrestore();
    }
}