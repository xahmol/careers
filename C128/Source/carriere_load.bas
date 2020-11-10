 10000 rem "---------------------------------------------------------------------
 10010 rem "-                       C A R R I E R E lader                       -
 10020 rem "-              Geschreven door Xander Arend Herman Mol              -
 10030 rem "-                     (C) 1992 by XAMA Software                     -
 10040 rem "---------------------------------------------------------------------
 10050 :
 10060 rem "--- Hoofdprogramma ---
 10070 :
 10080 color6,1:fast:window0,0,79,24,1:printchr$(14)chr$(27)"m{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{wht}"
 10090 fd$="Even geduld S.V.P.":gosub11150
 10100 poke247,128:poke0,peek(0)or64:poke1,peek(1)and191:poke47,0:poke48,164:clr
 10110 trap11490
 10120 graphic1,1:graphic5,0
 10130 bload"carriere.maco
 10140 bload"carriere.chr1
 10150 bload"carriere.chr2
 10160 sysdec("0bc0"),1,0,0
 10170 sysdec("0bc0"),2,1,0
 10180 graphicclr
 10190 bload"carriere.mdat",onb1
 10200 boot"carriere.mirq
 10210 fd$="XAMA Software presenteert":gosub11040
 10220 fd$="Een programma geschreven door Xander Arend Herman Mol":gosub11040
 10230 fd$="C a r r i {CBM-*} r e":gosub11040
 10240 fd$="@ 1992 by XAMA Software":gosub11040
 10250 fd$="Made in The Netherlands":gosub11040
 10260 do
 10270 printchr$(142)
 10280 scnclr
 10290 : printtab(9)"{rvon}{red}KLM{rght}{rght}{rght}{rght}{rght}{yel}NO{CBM-I}{CBM-I}LM{red}{rght}{rght}{rght}{rght}{rght}{rght}{rght}DC{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}DC{rght}{rght}DC{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}DC"
 10300 : printtab(9)"{rvon}{red}{rght}{rght}KLM{rght}{yel}ROP{rght}{rght}{rght}{rght}KLM{red}{rght}{rght}{rght}{rght}DBAC{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}DBACDBAC{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}DBAC"
 10310 : printtab(9)"{rvon}{red}{rght}{rght}{rght}{rght}KLM{yel}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}KL{rvof}{CBM-I}{rvon}G{red}DB{yel}IJ{red}AC{yel}H{rvof}{CBM-I}{CBM-I}{CBM-I}{CBM-I}{rvon}G{red}DB{yel}IJ{red}AB{yel}IJ{red}AC{yel}H{rvof}{CBM-I}{CBM-I}{CBM-I}{CBM-I}{rvon}G{red}DB{yel}IJ{red}AC{yel}H{rvof}{CBM-I}{CBM-I}{CBM-I}{CBM-I}{CBM-I}{CBM-I}{CBM-I}{CBM-I}"
 10320 : printtab(9)"{rvon}{yel}{rght}{rght}NOQ{red}{rght}KLM{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}DB{rght}{rght}{rght}{rght}AC{rght}{rght}{rght}{rght}DB{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}AC{rght}{rght}{rght}{rght}DB{rght}{rght}{rght}{rght}AC"
 10330 : printtab(9)"{rvon}{yel}NOP{red}{rght}{rght}{rght}{rght}{rght}KL{rvof}{CBM-I}{CBM-I}{CBM-I}{CBM-I}{CBM-I}{CBM-I}{CBM-I}{rvon}FB{rght}{rght}{rght}{rght}{rght}{rght}AE{rvof}{CBM-I}{CBM-I}{rvon}FB{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}AE{rvof}{CBM-I}{CBM-I}{rvon}FB{rght}{rght}{rght}{rght}{rght}{rght}AE{rvof}{CBM-I}{CBM-I}{CBM-I}{CBM-I}{CBM-I}{CBM-I}{CBM-I}{down}{down}{wht}"
 10340 : fd$="S o f t w a r e   p r e s e n t e e r t   :":gosub11150
 10350 : printtab(50)"{down}{rvon}{blu}KLM{down}"
 10360 : printtab(9)"{rvon}S    T{rght}{rght}S    T{rght}{rght}S    T{rght}{rght}S    T{rght}{rght}S    T{rght}{rght}S    T{rght}{rght}S    T{rght}{rght}S    T"
 10370 : printtab(9)"{lblu}{rvon} U{rght}{rght}{rght}V{rght}{rght} U{rght}{rght}V {rght}{rght} U{rght}{rght}V {rght}{rght} U{rght}{rght}V {rght}{rght}Y    Z{rght}{rght} U{rght}{rght}{rght}V{rght}{rght} U{rght}{rght}V {rght}{rght} U{rght}{rght}{rght}V"
 10380 : printtab(9)"{gry1}{rvon} {rght}{rght}{rght}{rght}{rght}{rght}{rght} W{rght}{rght}X {rght}{rght} W{rght}{rght}XZ{rght}{rght} W{rght}{rght}XZ{rght}{rght}{rght}V  U{rght}{rght}{rght}YW{rght}{rght}{rght}{rght}{rght}{rght} W{rght}{rght}XZ{rght}{rght}YW"
 10390 : printtab(9)"{cyn}{rvon} {rght}{rght}{rght}{rght}{rght}{rght}{rght}      {rght}{rght}     T{rght}{rght}     T{rght}{rght}{rght}X  W{rght}{rght}{rght}SU{rght}{rght}{rght}{rght}{rght}{rght}     T{rght}{rght}SU"
 10400 : printtab(9)"{lgrn}{rvon} W{rght}{rght}{rght}X{rght}{rght} U{rght}{rght}V {rght}{rght} U{rght}{rght}V {rght}{rght} U{rght}{rght}V {rght}{rght}S    T{rght}{rght} W{rght}{rght}{rght}X{rght}{rght} U{rght}{rght}V {rght}{rght} W{rght}{rght}{rght}X"
 10410 : printtab(9)"{grn}{rvon}Y    Z{rght}{rght} {rght}{rght}{rght}{rght} {rght}{rght} {rght}{rght}{rght}{rght} {rght}{rght} {rght}{rght}{rght}{rght} {rght}{rght}Y    Z{rght}{rght}Y    Z{rght}{rght} {rght}{rght}{rght}{rght} {rght}{rght}Y    Z{down}{down}{wht}"
 10420 : fd$="Geschreven door Xander{$a0}Arend Herman Mol":gosub11150
 10430 : print
 10440 : fd$="@ 1992 by XAMA Software":gosub11150
 10450 : printchr$(14)
 10460 : color5,8:gosub11200
 10470 : ifaw$=" "orjw>=128thenexit
 10480 : gosub10570
 10490 loop
 10500 sysdec("13a0")
 10510 print"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{wht}";
 10520 fd$="Even geduld S.V.P.":gosub11150:print"{home}"chr$(27)"l"
 10530 run"carriere.mprg
 10540 :
 10550 rem "--- Instructies ---
 10560 :
 10570 printchr$(142)"{clr}{red}{rvon}a{rvof}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{rvon}b{rvof}{gry2}";
 10580 print"{red}{CBM-G}"tab(50)"{rvon}{blu}KLM"tab(79)"{red}{rvof}{CBM-N}";
 10590 print"{red}{CBM-G}"tab(79)"{CBM-N}";
 10600 print"{red}{CBM-G}"tab(9)"{rvon}{blu}S    T{rght}{rght}S    T{rght}{rght}S    T{rght}{rght}S    T{rght}{rght}S    T{rght}{rght}S    T{rght}{rght}S    T{rght}{rght}S    T"tab(79)"{red}{rvof}{CBM-N}";
 10610 print"{red}{CBM-G}"tab(9)"{lblu}{rvon} U{rght}{rght}{rght}V{rght}{rght} U{rght}{rght}V {rght}{rght} U{rght}{rght}V {rght}{rght} U{rght}{rght}V {rght}{rght}Y    Z{rght}{rght} U{rght}{rght}{rght}V{rght}{rght} U{rght}{rght}V {rght}{rght} U{rght}{rght}{rght}V"tab(79)"{red}{rvof}{CBM-N}";
 10620 print"{red}{CBM-G}"tab(9)"{gry1}{rvon} {rght}{rght}{rght}{rght}{rght}{rght}{rght} W{rght}{rght}X {rght}{rght} W{rght}{rght}XZ{rght}{rght} W{rght}{rght}XZ{rght}{rght}{rght}V  U{rght}{rght}{rght}YW{rght}{rght}{rght}{rght}{rght}{rght} W{rght}{rght}XZ{rght}{rght}YW"tab(79)"{red}{rvof}{CBM-N}";
 10630 print"{red}{CBM-G}"tab(9)"{cyn}{rvon} {rght}{rght}{rght}{rght}{rght}{rght}{rght}      {rght}{rght}     T{rght}{rght}     T{rght}{rght}{rght}X  W{rght}{rght}{rght}SU{rght}{rght}{rght}{rght}{rght}{rght}     T{rght}{rght}SU"tab(79)"{red}{rvof}{CBM-N}";
 10640 print"{red}{CBM-G}"tab(9)"{lgrn}{rvon} W{rght}{rght}{rght}X{rght}{rght} U{rght}{rght}V {rght}{rght} U{rght}{rght}V {rght}{rght} U{rght}{rght}V {rght}{rght}S    T{rght}{rght} W{rght}{rght}{rght}X{rght}{rght} U{rght}{rght}V {rght}{rght} W{rght}{rght}{rght}X"tab(79)"{red}{rvof}{CBM-N}";
 10650 print"{red}{CBM-G}"tab(9)"{grn}{rvon}Y    Z{rght}{rght} {rght}{rght}{rght}{rght} {rght}{rght} {rght}{rght}{rght}{rght} {rght}{rght} {rght}{rght}{rght}{rght} {rght}{rght}Y    Z{rght}{rght}Y    Z{rght}{rght} {rght}{rght}{rght}{rght} {rght}{rght}Y    Z"tab(79)"{red}{rvof}{CBM-N}";
 10660 print"{red}{rvon}c{rvof}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{rvon}d{rvof}{down}";
 10670 print"{red}{rvon}a{rvof}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{rvon}b{rvof}";
 10680 forn=1to11
 10690 : print"{CBM-G}"tab(79)"{CBM-N}";
 10700 nextn
 10710 print"{rvon}c{rvof}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{rvon}d{rvof}";
 10720 window2,12,77,22
 10730 printchr$(14);
 10740 print"{yel}Carri{CBM-*}re is een, compleet menugestuurd bordspel voor vier spelers (of, als U"
 10750 print"dat wilt, computers), waar elke speler moet proberen dusdanig carri{CBM-*}re te"
 10760 print"maken dat hij of zij zowel gelukkig, als rijk en beroemd wordt."
 10770 print"{down}Elke speler moet proberen zo snel mogelijk 20 {lred}{CBM-+}{yel} (gelukspunten), 20 * "
 10780 print"(beroemdheid), en Fl. 200.000,- te verzamelen. Degene die het eerst hierin"
 10790 print"slaagt is winnaar van het spel."
 10800 print"U kunt over het spelbord reizen door het gooien van 1 (binnen een carri{CBM-*}re)"
 10810 print"of 2 dobbelstenen. Op elk vak wacht U een bepaalde gebeurtenis."
 10820 gosub11390
 10830 print"{yel}Geluk, beroemdheid en geld kunt U vooral verzamelen in een carri{CBM-*}re."
 10840 print"Carri{CBM-*}res kunt U starten door op de witte velden in de bordrand te komen, of"
 10850 print"door gebruik te maken van een kanskaart. Om een carri{CBM-*}re te beginnen moet U"
 10860 print"enige kosten betalen, tenzij U ervaring met deze carri{CBM-*}re heeft, U een bij-"
 10870 print"behorende Universitaire opleiding bezit (die U kunt krijgen doormiddel van"
 10880 print"de carri{CBM-*}re Universiteit), of een kanskaart waarmee U gratis mag beginnen."
 10890 print"{down}Verder zijn in het spel de kans- en ervaringskaarten belangrijk. Deze kaar-"
 10900 print"en krijgt U op verschillende momenten tijdens het spel."
 10910 gosub11390
 10920 print"{yel}Met ervaringskaarten kunt U het aantal vakken vooruit dat op de kaart staat."
 10930 print"Door een kanskaart te gebruiken kunt U een carri{CBM-*}re starten. Dit kan zijn"
 10940 print"onder normale voorwaarden, of misschien zelfs gratis."
 10950 print"{down}Het spel wordt bestuurt door middel van menu's die U bestuurt met de cursor-"
 10960 print"toetsen of de joystick. Alleen als er een lichtblauwe cursor verschijnt"
 10970 print"wordt er van U invoer via het toetsenbord verwacht."
 10980 print"{down}Veel plezier !"
 10990 gosub11390:window0,0,79,24
 11000 return
 11010 :
 11020 rem "--- Fade ---
 11030 :
 11040 restore11570
 11050 forn=1to8
 11060 : readc,d
 11070 : color5,c:print"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}";
 11080 : gosub11150
 11090 : forw=1tod:nextw
 11100 nextn
 11110 return
 11120 :
 11130 rem "--- Centreren ---
 11140 :
 11150 printusing"=################################################################################";fd$
 11160 return
 11170 :
 11180 rem "--- Scrolltext ---
 11190 :
 11200 window0,24,79,24:restore11590
 11210 ss$="                                                                                ":sc$=ss$
 11220 do
 11230 : iflen(sc$)<85thenbegin
 11240 :   readtx$
 11250 :   iftx$="Einde"thenrestore11590:sc$=sc$+ss$:readtx$
 11260 :   sc$=sc$+tx$
 11270 : bend
 11280 : printleft$(sc$,80)
 11290 : sc$=right$(sc$,len(sc$)-1)
 11300 : getaw$:jw=joy(2)
 11310 : ifaw$=" "oraw$="i"oraw$="I"orjw>=128thenexit
 11320 : forw=1to50:nextw
 11330 loop
 11340 window0,0,79,24
 11350 return
 11360 :
 11370 rem "--- Toets of knop joystick ---
 11380 :
 11390 print"{down}{lgrn}Toets.";
 11400 do
 11410 : getaw$
 11420 : jw=joy(2)
 11430 loopwhileaw$=""andjw<128
 11440 scnclr
 11450 return
 11460 :
 11470 rem "--- Foutenonderscheproutine ---
 11480 :
 11490 ifer=30thenresume
 11500 window0,0,79,24,1
 11510 print"{cyn}"err$(er)"{yel} error in regel{cyn}"el;chr$(27)"l"
 11520 help
 11530 end
 11540 :
 11550 rem "--- Data ---
 11560 :
 11570 data1,30,13,30,16,30,2,2000
 11580 data2,30,16,30,13,30,1,1000
 11590 data"XAMA Software presenteert: C a r r i {CBM-*} r e ! ! !    "
 11600 data"Een programma van Xander Arend Herman Mol.    @ 1992 by XAMA Software.    Carri{CBM-*}re.  Een boeiend bordspel voor vier personen.    "
 11610 data"De speler die het eerste zijn levensdoel verwezenlijkt heeft gewonnen !      Spelen tegen de computer is natuurlijk ook mogelijk !   "
 11620 data"Druk op 'SPATIE' om het hoofdprogramma te starten, en op 'I' voor instructies bij het programma.    "
 11630 data"De groeten zou ik willen doen aan de volgende personen:   Rinco, Jeroen, Edwin, DJ, Duncan, Suzanne, Erwin, Martine, Martijn, Bas, Masson, Timo, "
 11640 data"Wouter, Emille, Jeannet, Liesette, Carla, Thirza, Marc, Yuri, alle leden der Societas Studiosorum Reformatorum Roterodamensis, alle leden van Het "
 11650 data"Belgisch Dispuut Sidonia, alle leden van D66, alle leden van de Jonge Democraten, alle studenten economie aan de Erasmus Universiteit Rotterdam, "
 11660 data"en verder iedereen die ik vergeten ben.          Voor informatie over XAMA Software: XAMA Software, p.a. X.A.H. Mol, Goudse Rijweg 575-1, 3031 CG "
 11670 data"Rotterdam, Telefoon: 010 - 4047275.          XAMA{$a0}Software. For people who know what progress means !"
 11680 data"Einde"
 11690 :
 11700 rem "---------------------------------------------------------------------
 11710 rem "-                          Einde programma                          -
 11720 rem "---------------------------------------------------------------------
