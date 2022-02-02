/*
CAREERS

Routines for menu functions, part 3

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

#pragma code-name ("OVERLAY9");
#pragma rodata-name ("OVERLAY9");

// Menu functions part 3

// Cards menu
void cards_useexperience()
{
    unsigned char fields;

    menumakeborder(40,8,9,35);
    cputsxy(42,10,"Use experience cards");
    cputsxy(42,12,"How many fields forward?");
    do
    {
        fields = input_number(42,13,0,4);
    } while (fields != 0 && !player[playerturn].cards[14+fields]);
    if(fields)
    {
        dice_total = fields;
        player[playerturn].cards[14+fields]--;
    }
    else
    {
        gameendflag = 0;
    }

    presskeyprompt(42,15);
    windowrestore();    
}

void cards_useopportunity()
{
    unsigned char cards_number = 0;
    unsigned char card_select = 1;
    unsigned char career_select = 1;
    unsigned char xpos=42;
    unsigned char x,height,ypos,key;
    unsigned char card_map[15];

    for(x=0;x<15;x++)
    {
        if(player[playerturn].cards[x])
        {
            card_map[cards_number]=x;
            cards_number++;
        }
    }

    height=cards_number+5;
    ypos=12-(height/2);
    menumakeborder(40,ypos,height,35);
    ypos+=2;
    cputsxy(42,ypos,"Which card you want to use?");

    ypos++;
    VDC_Plot(ypos,xpos,C_LOWRIGHT,VDC_LRED);
    VDC_HChar(ypos,xpos+1,C_LOWLINE,31,VDC_LRED);
    VDC_Plot(ypos,xpos+32,C_LOWLEFT,VDC_LRED);
    for(x=0;x<cards_number+1;x++)
    {
        if(x<cards_number)
        {
            sprintf(buffer," %-20s (%s) ",cards_actiontext(card_map[x]),opportunitycard[card_map[x]].conditionfree==0?"Normal":"Free  ");
        }
        else
        {
            sprintf(buffer," %-20s          ","None");
        }
        VDC_Plot(ypos+x+1,xpos,C_RIGHTLINE,VDC_LRED);
        VDC_PrintAt(ypos+x+1,xpos+1,buffer,VDC_LCYAN+VDC_A_REVERSE);
        VDC_Plot(ypos+x+1,xpos+32,C_LEFTLINE,VDC_LRED);        
    }
    VDC_Plot(ypos+cards_number+2,xpos,C_UPRIGHT,VDC_LRED);
    VDC_HChar(ypos+cards_number+2,xpos+1,C_UPLINE,31,VDC_LRED);
    VDC_Plot(ypos+cards_number+2,xpos+32,C_UPLEFT,VDC_LRED);

    do
    {
        if(card_select<cards_number+1)
        {
            sprintf(buffer," %-20s (%s) ",cards_actiontext(card_map[card_select-1]),opportunitycard[card_map[card_select-1]].conditionfree==0?"Normal":"Free  ");
        }
        else
        {
            sprintf(buffer," %-20s          ","None");
        }
        VDC_PrintAt(ypos+card_select,xpos+1,buffer,VDC_LYELLOW+VDC_A_REVERSE);

        key = getkey(updownenter,joyinterface);
        switch (key)
        {
        case C_DOWN:
        case C_UP:
            VDC_PrintAt(ypos+card_select,xpos+1,buffer,VDC_LCYAN+VDC_A_REVERSE);
            if(key==C_UP)
            {
                card_select--;
                if(card_select<1)
                {
                    card_select=cards_number;
                }
            }
            else
            {
                card_select++;
                if(card_select>cards_number+1)
                {
                    card_select = 1;
                }
            }
            break;

        default:
            break;
        }
    } while (key!=C_ENTER);
    
    windowrestore();

    if(card_select==cards_number+1)
    {
        gameendflag=0;
    }
    else
    {
        card_select=card_map[card_select-1];
        if(opportunitycard[card_select].careernumber==9)
        {
            menumakeborder(40,8,13,35);
            cputsxy(42,10,"Which career do you want to start?");

            xpos=42;
            ypos=12;

            VDC_Plot(ypos,xpos,C_LOWRIGHT,VDC_LRED);
            VDC_HChar(ypos,xpos+1,C_LOWLINE,22,VDC_LRED);
            VDC_Plot(ypos,xpos+23,C_LOWLEFT,VDC_LRED);
            for(x=0;x<8;x++)
            {
                    sprintf(buffer," %-20s ",career[x].name);
                    VDC_Plot(ypos+x+1,xpos,C_RIGHTLINE,VDC_LRED);
                    VDC_PrintAt(ypos+x+1,xpos+1,buffer,VDC_LCYAN+VDC_A_REVERSE);
                    VDC_Plot(ypos+x+1,xpos+23,C_LEFTLINE,VDC_LRED);        
            }
            VDC_Plot(ypos+9,xpos,C_UPRIGHT,VDC_LRED);
            VDC_HChar(ypos+9,xpos+1,C_UPLINE,22,VDC_LRED);
            VDC_Plot(ypos+9,xpos+23,C_UPLEFT,VDC_LRED);

            do
            {
                sprintf(buffer," %-20s ",career[career_select-1].name);
                VDC_PrintAt(ypos+career_select,xpos+1,buffer,VDC_LYELLOW+VDC_A_REVERSE);

                key = getkey(updownenter,joyinterface);
                switch (key)
                {
                case C_DOWN:
                case C_UP:
                    VDC_PrintAt(ypos+career_select,xpos+1,buffer,VDC_LCYAN+VDC_A_REVERSE);
                    if(key==C_UP)
                    {
                        career_select--;
                        if(career_select<1)
                        {
                            career_select=8;
                        }
                    }
                    else
                    {
                        career_select++;
                        if(career_select>8)
                        {
                            career_select = 1;
                        }
                    }
                    break;

                default:
                    break;
                }
            } while (key!=C_ENTER);
            windowrestore();
        }
        else
        {
            career_select=opportunitycard[card_select].careernumber;
        }
        pawn_erase(playerturn);
        player[playerturn].career=0;
        player[playerturn].cards[card_select]--;
        opportunitycard[card_select].available++;
        player[playerturn].position=(career_select==0)?25:career[career_select-1].startfield;
        pawn_place(playerturn);
        if(career_select!=0 && opportunitycard[card_select].conditionfree)
        {
            if(career_select==1)
            {
                player[playerturn].experience[4]++;
            }
            else
            {
                player[playerturn].experience[career_select+2]++;
            }
        }
    }
}

unsigned char computer_playexperiencecards()
{
    /* Decide on playing cards for computer */

    unsigned char x,helpcar,helppos,helpoutc,scoremax,cardselect;
    unsigned char presentcar = player[playerturn].career;
    unsigned char presentpos = player[playerturn].position;

    if(gameendflag==10) { return 1; }

    // Reset variable for choosing cards
    for(x=0;x<20;x++) { whichcard[x]=0; }

    // Decide best experience card to use if any
    for(x=0;x<4;x++)
    {
        if(player[playerturn].cards[x+15])
        {
            // Calculate new position if this card would be used
            helppos=presentpos+x+1;
            helpcar=presentcar;
            if(!presentcar)
            {
                if(helppos >32) { helppos -= 32; }
            }
            else
            {
                if(helppos > career[helpcar-1].length)
                {
                    helppos = helppos - career[helpcar-1].length + career[helpcar-1].returnfield-1;
                    if(helppos >32) { helppos -= 32; }
                    helpcar = 0;
                }
            }

            // Check for possible bumps
            if(checkforbump_check(helpcar,helppos)) { whichcard[x+15]+=50; }

            if(helpcar)
            {
                // Check within career paths
                helpoutc=careerfield[helpcar-1][helppos-1].outcome;

                // If hearts to be received
                if(helpoutc==1||helpoutc==4)
                {
                    if(player[playerturn].happiness<20) { whichcard[x+15]+=10;}
                }
                // If money to be received
                if(helpoutc==3 || helpoutc==5 || helpoutc==14)
                {
                    if(player[playerturn].money<20000) { whichcard[x+15]+=10;}
                }
                // If fame to be received
                if(helpoutc==4 || helpoutc==8 || helpoutc==14)
                {
                    if(player[playerturn].fame<20) { whichcard[x+15]+=10;}
                }
                // If salary to be received
                if(helpoutc==10 || helpoutc==17)
                {
                    if(player[playerturn].money<20000) { whichcard[x+15]+=5;}
                }
            }
            else
            {
                // Check for landing on start
                if(helppos==1) { whichcard[x+15]+=10; }
            }
        }
    }

    // Use highest score experience card if any
    scoremax=0;
    cardselect=0;
    for(x=0;x<4;x++)
    {
        if(whichcard[x+15]>scoremax)
        {
            scoremax=whichcard[x+15];
            cardselect=x;
        }
    }
    if(cardselect)
    {
        gameendflag=9;
        dice_total=cardselect+1;
        player[playerturn].cards[cardselect+15]--;
        menumakeborder(35,8,7,40);
        cputsxy(37,10,"Computer uses experience card to move");
        gotoxy(37,11);
        cprintf("%u fields.",cardselect+1);
        presskeyprompt(37,13);
        windowrestore();
        return 1;
    }

    return 0;
   
}