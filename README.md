# Careers
Careers board game for 8 bit computers.

![Careers title screen](https://raw.githubusercontent.com/xahmol/careers/main/screenshots/careers-banner.png)

## Contents

[Version history and download](#version-history-and-download)

[Introduction](#introduction)

[Installing the game](#installing-the-game)

[Starting the game](#starting-the-game)

[Game instructions](#game-instructions)

[Credits](#credits)

## Version history and download
([Back to contents](#contents))

[Download latest build](https://github.com/xahmol/careers/raw/main/C128/CC65/careers-v090-20220206-1546.zip)

Version v090-20220206-1546:
- First released version

## Introduction
([Back to contents](#contents))

This game is a computer recreation of the classic boardgame of Careers. See for details about the original boardgame at is description at [BoardGameGeeks](https://boardgamegeek.com/boardgame/1475/careers).

When I was a kid we used to play this game frequently with our family. I made my original computer adaptation for the C128 in BASIC7.0 in 1992. This original version in Dutch is available here as well ([D64 image](https://github.com/xahmol/careers/raw/main/C128/BASIC/D64/Carriere%20C128.d64)) ([BASIC7.0 source](https://github.com/xahmol/careers/tree/main/C128/BASIC/Source)).

The BASIC original has been made from the Dutch game board with rules we used to play with in our family. Exactly 30 years later, I have converted this to a new version in C with more advanced game board using a scrollable board. To translate this properly I have used the [US 1958 version of the gameboard](https://github.com/xahmol/careers/blob/main/careers_1958board.jpg?raw=true) and the [US 1979 rule book](https://github.com/xahmol/careers/raw/main/careers_us_1979_rules.pdf).
As the rules and board did change over time, rules and gameboard in the computer adaptation might differ a bit from official version. However, the above linked rule book can be used as good starting point as to the rules implemented.

## Installing the game
([Back to contents](#contents))
- Download the latest distributable ZIP file (download link under [Version history and download](#version-history-and-download) )
- Unzip the file on your PC
- Transfer the desired Dxx image to your storage method. D81 loads faster than D71 than D64 (all image types are provided if your solution does not supoort D81 or D64 files)
- Alternatively, transfer all the .prg files to your storage location if your storage device support SD2IEC type disc access.

## Starting the game
([Back to contents](#contents))
- Mount the image (see your storage method manual)
- The image is bootable, so to start, either boot with image mounted or enter BOOT U8 (or BOOT U(enter device id) if you want to boot from another device ID than 8)
- If you use the seperate .PRG files instead of a disk image, select the proper directory using the instructions for your storage method. Than start the game by entering RUN"CAREERS",U(device ID).

## Game instructions
([Back to contents](#contents))

### Aim of the game
To be the first to "succeed" by winning 60 points. You win points by earning Fame, Money and Happiness in a number of different occupations.

As in real life, you first decide what your own "Success Formula" will be. Your Success Formula is the combination of Fame, Money and Happiness that you choose to earn in order to win. Your total must equal 60 points and may be divided in any way among Fame, Money (1 point per $1.000) and Happiness.

Computer players always choose the default of 20 Fame, $20.000 Money and 20 Happiness.

The first player to reach or exceed **each** part of his or her Success Formula is the winner.

See for full rules the [rule book](https://github.com/xahmol/careers/raw/main/careers_us_1979_rules.pdf).

### Game start
Wait until loading of the game is finished and this screen appears:
![Careers title screen](https://github.com/xahmol/careers/blob/main/screenshots/careers_titlescreen.png?raw=true)

Options at this screen:

|Key|Description
|---|---|
|**C**|Toggle controls between Joystick (default), SNES pad or Keyboard only.In all options the game can be controlled via keyboard. The option joystick allows the game to be also controlled by a joystick in port 2, while the option SNES pad enables control using a SNES gamepad via the Petscii Robots userport adapter.
|**M**|Toggle music. This stops the music or restarts the music
|**ENTER** or **FIRE**|Starts the game.

After pressing ENTER or FIRE a menu appears to ask if you want to load a previous game. Select No to proceed without loading, or select Yes and than select the desired game slot to load from to load a saved game.

### General controls
The game is mostly menu driven. Menus can be controlled via keyboard by the cursor keys to move around the options and ENTER to select the highlighted option.
Using a joystick or a SNES pad, moving between the options is done by moving the joystick in the desired direction or pressing the corresponding direction button on the SNES pad. Selection is done by fire on the joystick, or A or B key on the SNES pad.
Text input is done with the full keyboard alphanumerical keys, number selection is done by lowering or highering the number via cursor keys/joystick/SNES pad and pressing ENTER or FIRE to confirm.

### Menu options on human player turn

*Game menu*

![Game menu](https://github.com/xahmol/careers/blob/main/screenshots/careers_gamemenu.png?raw=true)

- Throw dice proceeds the turn with throwing the dice
- Restart restarts the game after asking for confirmation
- Stop stops the game after asking for confirmation

*Disc menu*

![Disc menu](https://github.com/xahmol/careers/blob/main/screenshots/careers_discmenu.png?raw=true)

- Save game lets you save the present game in one of four gameslots. Select desired slot and enter name to recognise the save
- Load game loads a saved game from the selected game slot (after asking confirmation)
- Autosave off/on toggles the autosave function. By default the function is enabled and saves before any human player turn to slot 1 called Autosave. Disabling speeds the game up somewhat and prevents music to be hampered caused by disk IO.

*Cards menu*

![Cards menu](https://github.com/xahmol/careers/blob/main/screenshots/careers_cardsmenu.png?raw=true)

- Show cards shows all present cards you own
- Play opportunity lets you select an opportunity card to be played
- Play experience lets you select an experience card to be played

*Infomration menu*

![Information menu](https://github.com/xahmol/careers/blob/main/screenshots/careers_informationmenu.png?raw=true)

- Field info shows information about a field a selected number of steps away from your present location
- Game score shows your present game score and experience, next to your selected winning formula
- Color legend shows an overview of the meaning of the colors used in the game board
- Explore board lets you scroll around the game board with the cursor keys, joystick or SNES pad. ENTER or FIRE to leave
- Credits shows the version number of the game build

### Game board explanation

The game board fields are coded with text and colouring:

![Game board](https://github.com/xahmol/careers/blob/main/screenshots/careers_gamescreen.png?raw=true)

Meaning of the colour coding:

![Color legend](https://github.com/xahmol/careers/blob/main/screenshots/careers_legend.png?raw=true)

Meaning of the text coding in the career path fields, where the number gives indication of the amount to receive:

|Text|Description
|---|---|
|![Fame](https://github.com/xahmol/careers/blob/main/screenshots/careers_getfame.png?raw=true)|Receive Fame
|![Money](https://github.com/xahmol/careers/blob/main/screenshots/careers_getmoney.png?raw=true)|Receive Money or Salary increase
|![Happiness](https://github.com/xahmol/careers/blob/main/screenshots/careers_gethearts.png?raw=true)|Receive Happiness
|![Event](https://github.com/xahmol/careers/blob/main/screenshots/careers_event.png?raw=true)|Event (often negative)
|![Experience](https://github.com/xahmol/careers/blob/main/screenshots/careers_getexp.png?raw=true)|Receive experience cards
|![Opportunity](https://github.com/xahmol/careers/blob/main/screenshots/careers_getopp.png?raw=true)|Receive opportunity cards

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

-   Routines for supporting the Petscii Robots userport SNES adapter
    https://texelec.com/product/snes-adapter-commodore/ :

    Based on code from:
    -   The 8-Bit Guy / David Murray
        https://www.the8bitguy.com/wp-content/uploads/2021/03/snestest.zip
    -   Chris Garrett:
        https://retrogamecoders.com/trse-snes-controller/

-   Scott Robison for boot sector creating method

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
