/*
CAREERS

Routines for career fields, part 1

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

#pragma code-name ("OVERLAY5");
#pragma rodata-name ("OVERLAY5");

// Career fields part 1

void career_generic(unsigned char careernr, unsigned char position)
{
    unsigned int address = careerfield[careernr][position].textaddress;

    // Career generic
    menumakeborder(30,8,12,45);
    cputsxy(32,10,"Career: ");
    textcolor(COLOR_CYAN);
    cprintf("%s",career[careernr].name);
    textcolor(COLOR_YELLOW);
    gotoxy(32,12);
    do
    {
        cputc(PEEKB(address++,1));
    } while (PEEKB(address,1)!=0);
}

void career_waitforkey()
{
    presskeyprompt(32,19);
    windowrestore();
}

void career_gethappiness(unsigned char careernr, unsigned char position)
{
    gotoxy(32,14);
    cprintf("Receive:   %u",careerfield[careernr][position].amount1);
    VDC_Plot(14,41,C_HEART,VDC_LRED);
    if(!fieldinformation)
    {
        player[playerturn].happiness += careerfield[careernr][position].amount1;
    }
}

void career_getexperiencecard(unsigned char careernr, unsigned char position)
{
    unsigned char cards = careerfield[careernr][position].amount1;
    unsigned char x,fields;

    gotoxy(32,14);
    cprintf("Receive: %u experience card%s.",cards,(cards==1)?"":"s");

    if(!fieldinformation)
    {
        for(x=0;x<cards;x++)
        {
            fields = rand()%4+1;
            gotoxy(32,16+x);
            cprintf("With card %u you can move forward %u fields.",x+1,fields);
            player[playerturn].cards[14+fields]++;
        }
    }
}

void career_getmoneytimesdie(unsigned char careernr, unsigned char position)
{
    unsigned long money = careerfield[careernr][position].amount1*1000;

    gotoxy(32,14);
    cprintf("Receive:   %lu times throw of one die.",money);
    VDC_Plot(14,41,C_DOLLAR,VDC_LGREEN);
    if(!fieldinformation)
    {
        dice_throw(1);
        cputsxy(32,16,"Received: ");
        textcolor(COLOR_CYAN);
        cprintf("%lu",money*dice_total);
        textcolor(COLOR_YELLOW);
        player[playerturn].money += money*dice_total;
    }
}

void career_gethappinessandfame(unsigned char careernr, unsigned char position)
{
    gotoxy(32,14);
    cprintf("Receive:   %u and",careerfield[careernr][position].amount1);
    VDC_Plot(14,41,C_STAR,VDC_LYELLOW);
    gotoxy(43,15);
    cprintf("%u",careerfield[careernr][position].amount2);
    VDC_Plot(15,41,C_HEART,VDC_LRED);
    if(!fieldinformation)
    {
        player[playerturn].fame += careerfield[careernr][position].amount1;
        player[playerturn].happiness += careerfield[careernr][position].amount2;
    }
}

void career_gotoparkbench()
{
    cputsxy(32,14,"Go to park bench.");
    if(!fieldinformation)
    {
        career_waitforkey();
        waitkeyflag = 1;
        pawn_erase(playerturn);
        player[playerturn].career=0;
        player[playerturn].position=17;
        pawn_place(playerturn);
    }
}

void career_gotohospital()
{
    cputsxy(32,14,"Go to hospital.");
    if(!fieldinformation)
    {
        career_waitforkey();
        waitkeyflag = 1;
        pawn_erase(playerturn);
        player[playerturn].career=0;
        player[playerturn].position=9;
        pawn_place(playerturn);
    }
}

void career_loosemoneyorparkbench(unsigned char careernr, unsigned char position)
{
    unsigned long money = careerfield[careernr][position].amount1*1000;
    unsigned char choice = 2;

    gotoxy(32,14);
    cprintf("Lose   :   %lu",money);
    VDC_Plot(14,41,C_DOLLAR,VDC_LGREEN);
    cputsxy(32,15,"or go to park bench.");
    if(!fieldinformation)
    {
        if(player[playerturn].money<money)
        {
            cputsxy(32,17,"Not enough money to pay.");
        }
        else
        {
            cputsxy(32,17,"Do you want to pay?");
            choice = menupulldown(69,16,6);
        }
        if(choice==1)
        {
            player[playerturn].money -= money;
        }
        else
        {
            career_waitforkey();
            waitkeyflag = 1;
            pawn_erase(playerturn);
            player[playerturn].career=0;
            player[playerturn].position=17;
            pawn_place(playerturn);
        }
    }
}

void career_getfamebuthospital(unsigned char careernr, unsigned char position)
{
    gotoxy(32,14);
    cprintf("Receive:   %u",careerfield[careernr][position].amount1);
    cputsxy(32,15,"but go to hospital.");
    VDC_Plot(14,41,C_STAR,VDC_LYELLOW);
    if(!fieldinformation)
    {
        player[playerturn].fame += careerfield[careernr][position].amount1;
        career_waitforkey();
        waitkeyflag = 1;
        pawn_erase(playerturn);
        player[playerturn].career=0;
        player[playerturn].position=9;
        pawn_place(playerturn);
    }
}

void career_endofcareer()
{
    // End of career routine'

    unsigned char card_select, degree_select;
    if(player[playerturn].career!=2)
    {
        menumakeborder(40,8,7,35);
        cputsxy(42,10,"You receive an experience card.");
        card_select=rand()%4+1;
        cputsxy(42,11,"With this card you can move");
        gotoxy(42,12);
        cprintf("%u fields.",card_select);
        player[playerturn].cards[14+card_select]++;
        if(player[playerturn].career==1)
        {
            player[playerturn].experience[4]++;
        }
        else
        {
            player[playerturn].experience[player[playerturn].career+2]++;
        }
        presskeyprompt(42,14);
    }
    else
    {
        menumakeborder(30,5,12,45);
        cputsxy(32,7,"Your salary is raised with   2000");
        VDC_Plot(7,59,C_DOLLAR,VDC_LGREEN);
        cputsxy(32,9,"You also can choose one of these degrees:");
        cputsxy(33,11,"Law              (Business, Politics)");
        cputsxy(33,12,"Medicine         (Business, Hospital)");
        cputsxy(33,13,"Science          (Business, Moon)");
        cputsxy(33,14,"Engineering      (Business, Uranium)");
        cputsxy(32,16,"Make your choice.");
        if(player[playerturn].computer)
        {
            degree_select=3;
        }
        else
        {
            degree_select=menupulldown(32,10,10);
        }
        textcolor(COLOR_CYAN);
        cputsxy(33,10+degree_select,pulldownmenutitles[9][degree_select-1]);
        textcolor(COLOR_YELLOW);
        player[playerturn].experience[degree_select-1]=1;
        player[playerturn].salary+=2000;
        player[playerturn].cards[11]=0;
        cputsxy(31,16,"                  ");
        presskeyprompt(32,16);
    }
    windowrestore();
}

unsigned char computer_hospitalparkbench()
{
    // Computer at hospital and park bench
    
    unsigned char numberofdoctors = 0;
    unsigned long totalpaid = 0;
    unsigned char x;
    unsigned char presentcar = player[playerturn].career;
    unsigned char presentpos = player[playerturn].position;

    paidforleave=0;    

    // Check if computer is in the hospital and, if yes, decide on payment
    if(presentcar==0 && presentpos==9)
    {
        for(x=0;x<4;x++)
        {
            if(player[x].experience[1]) { numberofdoctors++; }
        }
        if(numberofdoctors)
        {
            totalpaid = (player[playerturn].salary/2)*numberofdoctors;
        }
        else
        {
            totalpaid = player[playerturn].salary/2;
        }
        if(!((player[playerturn].money*80)/100 < totalpaid))
        {
            menumakeborder(40,8,7,35);
            paidforleave=1;
            gotoxy(42,10);
            cprintf("Computer pays   %lu to leave.",totalpaid);
            VDC_Plot(10,56,C_DOLLAR,VDC_LGREEN);
            player[playerturn].money -= totalpaid;
            for(x=0;x<4;x++)
            {
                if(player[x].experience[1])
                {
                    player[x].money += player[playerturn].salary/2;
                }
            }
            presskeyprompt(42,12);
            windowrestore();
        }
        else
        {
            return 1;
        }
    }

    // Check if computer is on the park bench and, if yes, decide on payment
    if(presentcar==0 && presentpos==17)
    {
        totalpaid = player[playerturn].money/2;
        if(!((player[playerturn].money*90)/100 < totalpaid))
        {
            menumakeborder(40,8,7,35);
            paidforleave=1;
            gotoxy(42,10);
            cprintf("Computer pays   %lu to leave.",totalpaid);
            VDC_Plot(10,56,C_DOLLAR,VDC_LGREEN);
            player[playerturn].money -= totalpaid;
            presskeyprompt(42,12);
            windowrestore();
        }
        else
        {
            return 1;
        }
    }

    return 0;
}