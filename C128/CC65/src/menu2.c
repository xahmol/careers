/*
CAREERS

Routines for menu functions, part 2

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

#pragma code-name ("OVERLAY8");
#pragma rodata-name ("OVERLAY8");

// Menu functions part 2

// Load and save functions

void savegame(unsigned char autosave)
{
    /* Save game to a gameslot
       Input: autosave is 1 for autosave, else 0 */

    char fname[25] = "career.sav";
    unsigned char slot = 0;
    unsigned char x, y, len, ferr;
    unsigned char yesno = 1;
    unsigned int address;

    len = strlen(fname);

    if(autosave==1)
    {
        fname[len]=48;
        fname[len+1]=0;
    }
    else
    {
        menumakeborder(5,5,12,30);
        cputsxy(7,7,"Save game.");
        cputsxy(7,8,"Choose slot:");
        do
        {
            slot = menupulldown(14,10,11) - 1;
        } while (slot<1);
        if(PEEK(SAVESLOTS+slot)==1)
        {
            cputsxy(7,8,"Slot not empty. Sure?");
            yesno = menupulldown(18,10,6);
        }
        if(yesno==1)
        {
            cputsxy(7,8,"Choose name of save. ");
            if(PEEK(SAVESLOTS+slot)==0) { memset(pulldownmenutitles[10][slot],0,15); }
            input(7,9,pulldownmenutitles[10][slot],15);
            for(x=strlen(pulldownmenutitles[10][slot]);x<15;x++)
            {
                pulldownmenutitles[10][slot][x] = C_SPACE;
            }
            pulldownmenutitles[10][slot][15] = 0;
            fname[len]=48+slot;
            fname[len+1]=0;
            address=SAVESLOTS+(slot*16)+5;
            for(x=0;x<16;x++)
            {
                POKE(address++,pulldownmenutitles[10][slot][x]);
            }
        }
        windowrestore();
    }
    if(yesno==1)
    {
        POKE(SAVESLOTS+slot,1);
        saveconfigfile();
        address=SAVEGAMEMEM;
        POKE(address++,playerturn);
        POKE(address++,anotherturn);
        for(x=0;x<15;x++)
        {
            POKE(address++,opportunitycard[x].available);
        }
        for(x=0;x<4;x++)
        {
            for(y=0;y<20;y++)
            {
                POKE(address++,player[x].name[y]);
            }
            for(y=0;y<11;y++)
            {
                POKE(address++,player[x].experience[y]);
            }
            for(y=0;y<19;y++)
            {
                POKE(address++,player[x].cards[y]);
            }
            POKE(address++,player[x].career);
            POKE(address++,player[x].position);
            POKE(address++,(player[x].salary & 0xFF000000) >> 24);
            POKE(address++,(player[x].salary & 0xFF0000) >> 16);
            POKE(address++,(player[x].salary & 0xFF00) >> 8);
            POKE(address++, player[x].salary & 0xFF);
            POKE(address++,(player[x].money & 0xFF000000) >> 24);
            POKE(address++,(player[x].money & 0xFF0000) >> 16);
            POKE(address++,(player[x].money & 0xFF00) >> 8);
            POKE(address++, player[x].money & 0xFF);
            POKE(address++,player[x].happiness);
            POKE(address++,player[x].fame);
            POKE(address++,player[x].winmoney);
            POKE(address++,player[x].winhappiness);
            POKE(address++,player[x].winfame);
            POKE(address++,player[x].computer);
            POKE(address++,player[x].skipturn);
        }

         // Remove old file
        remove(fname);

        // Set device ID
	    cbm_k_setlfs(0, getcurrentdevice(), 0);

        // Set filename
	    cbm_k_setnam(fname);

        // Set bank to 0
        SetLoadSaveBank(0);

        // Save saveslots
	    ferr = cbm_k_save(SAVEGAMEMEM, SAVEGAMEMEM+285);

        if (ferr) { fileerrormessage(ferr); }
    }
}

void loadgame()
{
     /* Load game from a gameslot */
    
    char fname[25] = "career.sav";
    unsigned char slot, x, y, len;
    unsigned char yesno = 1;
    unsigned int address;
    
    len = strlen(fname);
    
    menumakeborder(5,5,12,30);
    cputsxy(7,7,"Load game.");
    cputsxy(7,9,"Choose slot:");
    slot = menupulldown(14,10,11) - 1;
    if(PEEK(SAVESLOTS+slot)==0)
    {
        cputsxy(7,9,"Slot empty. ");
        cputsxy(7,10,"Press key.");
        getkey("",1);
        gameendflag=0;
    }
    windowrestore();
    if(PEEK(SAVESLOTS+slot)==1)
    {
        fname[len]=48+slot;
        fname[len+1]=0;

        // Set device ID
	    cbm_k_setlfs(0, getcurrentdevice(), 0);

	    // Set filename
	    cbm_k_setnam(fname);

	    // Set bank to 0
	    SetLoadSaveBank(0);
	
	    // Load config from file to memory
	    address = cbm_k_load(0,SAVEGAMEMEM);

        if (address <= SAVEGAMEMEM) { fileerrormessage(255); return; }

        board_reset();
        address=SAVEGAMEMEM;
        playerturn=PEEK(address++);
        anotherturn=PEEK(address++);
        for(x=0;x<15;x++)
        {
            opportunitycard[x].available=PEEK(address++);
        }
        for(x=0;x<4;x++)
        {
            for(y=0;y<20;y++)
            {
                player[x].name[y]=PEEK(address++);
            }
            for(y=0;y<11;y++)
            {
                player[x].experience[y]=PEEK(address++);
            }
            for(y=0;y<19;y++)
            {
                player[x].cards[y]=PEEK(address++);
            }
            player[x].career=PEEK(address++);
            player[x].position=PEEK(address++);
            player[x].salary = (((unsigned long)PEEK(address++))<<24) |
                               (((unsigned long)PEEK(address++))<<16) |
                               (((unsigned long)PEEK(address++))<< 8) |
                                ((unsigned long)PEEK(address++));
            player[x].salary = (((unsigned long)PEEK(address++))<<24) |
                               (((unsigned long)PEEK(address++))<<16) |
                               (((unsigned long)PEEK(address++))<< 8) |
                                ((unsigned long)PEEK(address++));
            player[x].happiness=PEEK(address++);
            player[x].fame=PEEK(address++);
            player[x].winmoney=PEEK(address++);
            player[x].winhappiness=PEEK(address++);
            player[x].winfame=PEEK(address++);
            player[x].computer=PEEK(address++);
            player[x].skipturn=PEEK(address++);
            pawn_place(x);
        }
        pawn_place(playerturn);
    }
}

// Board functions

void board_scroll()
{
    /* Explore board by scrolling board around with cursor keys */

    unsigned char choice;

    menumakeborder(60,10,6,18);
    cputsxy(62,12,"Move board around");
    cputsxy(62,13,"with cursor keys");
    cputsxy(62,14,"or joystick.");
    cputsxy(62,15,"RETURN/fire=end.");

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
    windowrestore();
}