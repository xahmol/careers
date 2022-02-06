# Careers
Careers board game for 8 bit computers.

![Careers title screen](https://raw.githubusercontent.com/xahmol/careers/main/screenshots/careers-banner.png)

## Contents

[Version history and download](#version-history-and-download)

[Introduction](#introduction)

[Credits](#credits)

## Version history and download
([Back to contents](#contents))

## Introduction
([Back to contents](#contents))

This game is a computer recreation of the classic boardgame of Careers. See for details about the original boardgame at is description at [BoardGameGeeks](https://boardgamegeek.com/boardgame/1475/careers).

When I was a kid we used to play this game frequently with our family. I made my original computer adaptation for the C128 in BASIC7.0 in 1992. This original version in Dutch is available here as well ([D64 image](https://github.com/xahmol/careers/raw/main/C128/BASIC/D64/Carriere%20C128.d64)) ([BASIC7.0 source](https://github.com/xahmol/careers/tree/main/C128/BASIC/Source)).

The BASIC original has been made from the Dutch game board with rules we used to play with in our family. Exactly 30 years later, I have converted this to a new version in C with more advanced game board using a scrollable board. To translate this properly I have used the [US 1958 version of the gameboard](https://github.com/xahmol/careers/blob/main/careers_1958board.jpg?raw=true) and the [US 1979 rule book](https://github.com/xahmol/careers/raw/main/careers_us_1979_rules.pdf).
As the rules and board did change over time, rules and gameboard in the computer adaptation might differ a bit from official version. However, the above linked rule book can be used as good starting point as to the rules implemented.

## Starting the game


## Credits
([Back to contents](#contents))

Written in 1992, 2022 by Xander Mol

[https://github.com/xahmol/careers](https://github.com/xahmol/careers)

[https://www.idreamtin8bits.com/](https://www.idreamtin8bits.com/)


### Credits for the C128 version:

Originally written in 1992 in Commodore BASIC 7.0 for the Commodore 128. Rewritten for C128 in C using CC65 in 2022

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

-   Tooling to transfer original Commodore software code: "
    VICE by VICE authors
    DirMaster by The Wiz/Elwix
    CharPad Free by Subchrist software
    UltimateII+ cartridge by Gideon Zweijtzer
    
-   Tested using real hardware (C128D and C128DCR) plus VICE.

Music credits:
-   Made in Elx - Adam Hay (Sack) 2010 Cosine

    https://csdb.dk/release/?id=94679

    https://deepsid.chordian.net/?file=%2FMUSICIANS%2FS%2FSack%2FMade_in_Elx.sid

-   Jupiler Dance - Hans Jürgen Ehrentraut (HJE) 2017 Genesis Project

    https://csdb.dk/release/?id=153508

    https://deepsid.chordian.net/?file=%2FMUSICIANS%2FH%2FHJE%2FJupiler_Dance.sid

-   What's Your Game? - Richard Bayliss (RCB) 2004 Civitas

    https://csdb.dk/release/?id=13027

    https://deepsid.chordian.net/?file=/MUSICIANS/B/Bayliss_Richard/Whats_Your_Game.sid

The code can be used freely as long as you retain
a notice describing original source and author.

THE PROGRAMS ARE DISTRIBUTED IN THE HOPE THAT THEY WILL BE USEFUL,
BUT WITHOUT ANY WARRANTY. USE THEM AT YOUR OWN RISK!
*/


([Back to contents](#contents))
