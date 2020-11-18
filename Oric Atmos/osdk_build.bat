@ECHO OFF


::
:: Initial check.
:: Verify if the SDK is correctly configurated
::
IF "%OSDK%"=="" GOTO ErCfg

::
:: Launch the compilation of files
::
SET OSDKNAME=CAREERS
SET OSDKFILE=CAREERS
CALL %OSDK%\bin\make.bat CAREERS

SET OSDKNAME=CARMAIN
SET OSDKFILE=CARMAIN
CALL %OSDK%\bin\make.bat CARMAIN

::
:: Assemble machine code
::
ECHO Assembling machine code
%osdk%\bin\xa CARMACO.s -o build\CARMACO.o
%OSDK%\bin\header -h1 -a0 build\CARMACO.o build\CARMACO.tap $6500

::
:: Assemble the board game data
::
ECHO Assembling board game data
%osdk%\bin\xa carboard.s -o build\carboard.o
%OSDK%\bin\header -h1 -a0 build\carboard.o build\carboard.tap $9800

::
:: Convert musics
:: ym1.mym -> 8699 bytes
:: ym2.mym -> 7293 bytes
:: ym3.mym -> 7956 bytes
::
:: HIRES last usable memory area is $9800 / 38912
:: - 8657 -> $762f / 30255
:: Round to -> $7600 / 30208 this gives us $2200 / 8704 bytes for the music
::
:: TEXT last usable memory area is $B400 / 46080
:: $B400-$7600  gives us $3E00 / 15872 bytes for the music
::
:: So we make each music load in $7600
::
:: The depacking buffer for the music requires 256 bytes per register, so 256*14 bytes = $e00 / 3584 bytes
:: If we place the buffer just before the music file, it will start at the location $7600-$e00 = $6800 / 26624
::
:: And just before that we put the music player binary file, which will start by two JMP:
:: - (+0) JMP StartMusic
:: - (+3) JMP StopMusic
::
:: The music player itself is less than 512 bytes without counting the IRQ installation and what nots so could start in $6600, say $6500 for security
::
:: echo %osdk%

:: SET YM2MYM=%osdk%\Bin\ym2mym.exe -h1 -m15872

:: %YM2MYM% "Music\R-Type  2 - level 1.ym" build\R-Type.tap                $7600 "Music1"
:: %YM2MYM% "Music\Axel F.ym" build\AxelF.tap                              $7600 "Music2"
:: %YM2MYM% "Music\Wizball 1.ym" build\Wizzball.tap                        $7600 "Music3"

::
:: Rename files so they have friendly names on the disk
::
%OSDK%\bin\taptap ren build\carboard.tap "CARBOARD" 0
:: %OSDK%\bin\taptap ren build\CARTITL.tap "CARTITL" 0
%OSDK%\bin\taptap ren build\CARMACO.tap "CARMACO" 0

ECHO Building DSK file
%OSDK%\bin\tap2dsk -iCLS:CAREERS -c20:3 -nCAREERS CARCHRS.tap build\CARMACO.tap build\CAREERS.tap build\CARMAIN.tap build\carboard.tap build\CAREERS.dsk
%OSDK%\bin\old2mfm build\CAREERS.dsk

GOTO End

::
:: Outputs an error message
::
:ErCfg
ECHO == ERROR ==
ECHO The Oric SDK was not configured properly
ECHO You should have a OSDK environment variable setted to the location of the SDK
IF "%OSDKBRIEF%"=="" PAUSE
GOTO End


:End
pause