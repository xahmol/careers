 10000 rem "---------------------------------------------------------------------
 10010 rem "-                  C A R R I E R E  hoofdprogramma                  -
 10020 rem "-              Geschreven door Xander Arend Herman Mol              -
 10030 rem "-                     (C) 1992 by XAMA Software                     -
 10040 rem "---------------------------------------------------------------------
 10050 :
 10060 trap26370:print"{home}{home}"chr$(14)
 10070 b$="{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}"
 10080 o$="{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}"
 10090 ci$="0123456789"
 10100 lc$="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"+ci$
 10110 al$=lc$+" !#$%&'()"+chr$(34)+"+-@*^:[;]=,<.>/?_"
 10120 pudef" .,"
 10130 s$="                                                                                "
 10140 ad=4
 10150 gosub24830
 10160 gosub11600
 10170 xc=40:yc=8:b=35:h=6:gosub26270
 10180 window42,10,79,24:print"{yel}Wilt U een oud spel laden ?"
 10190 xc=69:yc=11:mn=5:gosub25300
 10200 gosub25260
 10210 ifm=1thenes=7:gosub22940
 10220 do
 10230 : gosub10840
 10240 : ifes<>7thengosub19920:gosub11870
 10250 : do
 10260 :   print"{home}{home}":window45,5,79,24:print"{yel}Nu aan de beurt:"
 10270 :   print"Speler{cyn}";
 10280 :   printbs+1"{yel}:{lgrn} "sp$(bs,0):es=0
 10290 :   sn=bs:gosub20250:gosub20120
 10300 :   ifsp(bs,6)=0thenbegin
 10310 :     do
 10320 :       gosub25690
 10330 :       ifmn=1andm=1thenexit
 10340 :       ifmn=1andm=2thengosub12390:ifm=1thenes=6:exit
 10350 :       ifmn=1andm=3thengosub12390:ifm=1thenes=5:exit
 10360 :       ifmn=2andm=1thengosub22470
 10370 :       ifmn=2andm=2thengosub12390:ifm=1thenes=7:gosub22940:exit
 10380 :       ifmn=3andm=1thengosub12470
 10390 :       ifmn=3andm=2andsp(bs,7)=0andnot(sp(bs,0)=0andsp(bs,1)=9)andnot(sp(bs,0)=0andsp(bs,1)=17)thenes=8:exit
 10400 :       ifmn=3andm=3andsp(bs,7)=0andnot(sp(bs,0)=0andsp(bs,1)=9)andnot(sp(bs,0)=0andsp(bs,1)=17)thenes=9:exit
 10410 :       ifmn=4thenonmgosub20430,12040,11210,11090
 10420 :     loop
 10430 :     ifes>0andes<8thenexit
 10440 :     ifes=8thengosub21850
 10450 :     ifes=9thengosub21720
 10460 :     ifsp(bs,0)=0andsp(bs,1)=9thengosub21150
 10470 :     ifsp(bs,0)=0andsp(bs,1)=17thengosub21430
 10480 :   bend:elsegosub23400
 10490 :   ifsp(bs,7)=1thenes=10:sp(bs,7)=0
 10500 :   ifes=0thenbegin
 10510 :     ifsp(bs,0)=0thenda=2:elseda=1
 10520 :     gosub11430
 10530 :   bend
 10540 :   ifsp(bs,0)=0andsp(bs,1)=25anddg<8andes<>8thenbegin
 10550 :     ifsp(bs,6)=0thengosub21610:elsegosub24540
 10560 :   bend
 10570 :   ifsp(bs,0)=0andsp(bs,1)=9anddg>5andbt=0thenes=10
 10580 :   ifsp(bs,0)=0andsp(bs,1)=17anddg<>7anddg<>11anddd<>1andbt=0thenes=10
 10590 :   ifes<>10thengosub20250
 10600 :   ifes=0ores=9thenbegin
 10610 :     ifsp(bs,0)=0thenbegin
 10620 :       sp(bs,1)=sp(bs,1)+dg
 10630 :       ifsp(bs,1)>32thensp(bs,1)=sp(bs,1)-32:ifsp(bs,1)<>1thengosub20640
 10640 :     bend:elsebegin
 10650 :       sp(bs,1)=sp(bs,1)+dg
 10660 :       ifsp(bs,1)>cc(sp(bs,0),0,0)thenbegin
 10670 :         sp(bs,1)=sp(bs,1)-cc(sp(bs,0),0,0)+cc(sp(bs,0),0,1)-1
 10680 :         gosub20750
 10690 :         ifsp(bs,1)>32thensp(bs,1)=sp(bs,1)-32:ifsp(bs,1)<>1thengosub20640
 10700 :         sp(bs,0)=0
 10710 :       bend
 10720 :     bend
 10730 :   bend
 10740 :   ifes<>10thenbegin
 10750 :     gosub20120:gosub21050
 10760 :   bend
 10770 :   gosub22310:ifes=5ores=6thenexit
 10780 :   ifne<>0thenne=0:elsebs=bs+1:ifbs>3thenbs=0
 10790 :   window45,5,79,24,1:window0,0,79,24
 10800 : loop
 10810 : ifes=5thenexit
 10820 loop
 10830 goto26430
 10840 scnclr
 10850 print"{lgrn}{rvon} C a r r i {CBM-*} r e                        Geschreven door Xander Arend Herman Mol "
 10860 gosub25130
 10870 print"{down}{down}{down}{rvon}{grn}   {CBM-N}{brn}   {CBM-N}{pur}   {CBM-N}{wht}   {CBM-N}{brn}   {CBM-N}{pur}   {CBM-N}{wht}   {CBM-N}{brn}   {CBM-N}{grn}   {CBM-N}"
 10880 print"{rvon}{grn}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}{brn}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}{pur}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}{wht}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}{brn}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}{pur}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}{wht}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}{brn}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}{grn}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}"
 10890 print"{rvon}{brn}   {CBM-N}{rvof}  {rvon}{lred}{CBM-@}{CBM-POUND}{rvof}      {rvon}{wht}{CBM-@}{CBM-POUND}{rvof}  {rvon}{yel}{CBM-@}{CBM-POUND}{rvof}    {rvon}{yel}{CBM-@}{CBM-POUND}{rvof}      {rvon}{brn}   {CBM-N}"
 10900 print"{rvon}{brn}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}{rvof}  {rvon}{wht}{CBM-@}{CBM-POUND}{lred}{CBM-@}{CBM-POUND}{CBM-@}{CBM-POUND}{rvof}  {rvon}{wht}{CBM-@}{CBM-POUND}{rvof}  {rvon}{wht}{CBM-@}{CBM-POUND}{rvon}{yel}{CBM-@}{lgrn}{CBM-POUND}{rvof}  {rvon}{wht}{CBM-@}{CBM-POUND}{rvof}  {rvon}{lgrn}{CBM-@}{CBM-POUND}{yel}{CBM-@}{CBM-POUND}{brn}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}"
 10910 print"{rvon}{wht}   {CBM-N}{rvof}      {rvon}{lgrn}{CBM-@}{CBM-POUND}{rvof}  {rvon}{yel}{CBM-@}{CBM-POUND}{rvof}    {rvon}{yel}{CBM-@}{CBM-POUND}{rvof}  {rvon}{wht}{CBM-@}{CBM-POUND}{rvof}  {rvon}{yel}{CBM-@}{CBM-POUND}{rvof}  {rvon}{pur}   {CBM-N}"
 10920 print"{rvon}{wht}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}{CBM-@}{CBM-POUND}{lred}{CBM-@}{CBM-POUND}{wht}{CBM-@}{CBM-POUND}{CBM-@}{CBM-POUND}{rvof}  {rvon}{lred}{CBM-@}{CBM-POUND}{wht}{CBM-@}{CBM-POUND}{yel}{CBM-@}{CBM-POUND}{CBM-@}{lred}{CBM-POUND}{rvof}  {rvon}{yel}{CBM-@}{lred}{CBM-POUND}{lgrn}{CBM-@}{CBM-POUND}{wht}{CBM-@}{CBM-POUND}{rvof}  {rvon}{pur}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}"
 10930 print"{rvon}{pur}   {CBM-N}{rvof}                            {rvon}{wht}   {CBM-N}"
 10940 print"{rvon}{pur}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}{rvof}  {rvon}{wht}{CBM-@}{CBM-POUND}{lred}{CBM-@}{CBM-POUND}{wht}{CBM-@}{CBM-POUND}{rvof}{yel}  Carri{CBM-*}re  {rvon}{lred}{CBM-@}{CBM-POUND}{wht}{CBM-@}{CBM-POUND}{CBM-@}{CBM-POUND}{lred}{CBM-@}{CBM-POUND}{wht}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}"
 10950 print"{rvon}{brn}   {CBM-M}{lgrn}{CBM-@}{CBM-POUND}{wht}{CBM-@}{CBM-POUND}{rvof}  {rvon}{lgrn}{CBM-@}{CBM-POUND}{rvof}{wht}   @ 1992   {rvon}{wht}{CBM-@}{CBM-POUND}{rvof}      {rvon}{brn}   {CBM-N}"
 10960 print"{rvon}{brn}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}{rvof}      {rvon}{lgrn}{CBM-@}{CBM-POUND}{rvof}{lred}    XAMA    {rvon}{lred}{CBM-@}{CBM-POUND}{rvof}  {rvon}{CBM-@}{CBM-POUND}{lgrn}{CBM-@}{CBM-POUND}{brn}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}"
 10970 print"{rvon}{wht}   {CBM-N}{CBM-@}{CBM-POUND}{CBM-@}{CBM-POUND}{lgrn}{CBM-@}{CBM-POUND}{wht}{CBM-@}{CBM-POUND}{rvof}{lblu}  Software  {rvon}{wht}{CBM-@}{CBM-POUND}{lgrn}{CBM-@}{CBM-POUND}{yel}{CBM-@}{lred}{CBM-POUND}{rvof}  {rvon}{pur}   {CBM-N}"
 10980 print"{rvon}{wht}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}{rvof}                            {rvon}{pur}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}"
 10990 print"{rvon}{pur}   {CBM-N}{wht}{CBM-@}{CBM-POUND}{yel}{CBM-@}{CBM-POUND}{wht}{CBM-@}{CBM-POUND}{rvof}  {rvon}{lred}{CBM-@}{CBM-POUND}{yel}{CBM-@}{lred}{CBM-POUND}{lgrn}{CBM-@}{CBM-POUND}{rvof}  {rvon}{lgrn}{CBM-@}{CBM-POUND}{yel}{CBM-@}{lred}{CBM-POUND}{yel}{CBM-@}{CBM-POUND}{wht}{CBM-@}{CBM-POUND}{CBM-@}{CBM-POUND}{lred}{CBM-@}{CBM-POUND}{wht}   {CBM-N}"
 11000 print"{rvon}{pur}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}{rvof}    {rvon}{lred}{CBM-@}{CBM-POUND}{rvof}  {rvon}{lgrn}{CBM-@}{CBM-POUND}{rvof}  {rvon}{wht}{CBM-@}{CBM-POUND}{rvof}  {rvon}{wht}{CBM-@}{CBM-POUND}{rvof}          {rvon}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}"
 11010 print"{rvon}{brn}   {CBM-N}{rvof}  {rvon}{wht}{CBM-@}{CBM-POUND}{lred}{CBM-@}{CBM-POUND}{rvof}  {rvon}{lred}{CBM-@}{CBM-POUND}{rvof}  {rvon}{CBM-@}{CBM-POUND}{rvof}  {rvon}{yel}{CBM-@}{CBM-POUND}{CBM-@}{CBM-POUND}{lgrn}{CBM-@}{CBM-POUND}{yel}{CBM-@}{CBM-POUND}{CBM-@}{lred}{CBM-POUND}{rvof}  {rvon}{pur}   {CBM-N}"
 11020 print"{rvon}{brn}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}{rvof}  {rvon}{lred}{CBM-@}{CBM-POUND}{rvof}    {rvon}{wht}{CBM-@}{CBM-POUND}{rvof}  {rvon}{lred}{CBM-@}{CBM-POUND}{rvof}          {rvon}{lgrn}{CBM-@}{CBM-POUND}{rvof}  {rvon}{pur}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}"
 11030 print"{rvon}{grn}   {CBM-N}{wht}   {CBM-N}{pur}   {CBM-N}{brn}   {CBM-N}{wht}   {CBM-N}{brn}   {CBM-N}{pur}   {CBM-N}{brn}   {CBM-N}{grn}   {CBM-N}"
 11040 print"{rvon}{grn}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}{wht}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}{pur}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}{brn}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}{wht}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}{brn}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}{pur}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}{brn}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}{grn}{CBM-@}{CBM-@}{CBM-@}{CBM-POUND}{rvof}"
 11050 return
 11060 :
 11070 rem "--- Spelinformatie ---
 11080 :
 11090 xc=20:yc=8:b=55:h=11:gosub26270
 11100 window0,10,79,24:printtab(41)"{lgrn}C A R R I E R E"
 11110 printtab(22)"{yel}{down}Een programma geschreven door Xander Arend Herman Mol"
 11120 printtab(36)"{wht}{down}(C) 1992 by XAMA Software"
 11130 printtab(28)"{cyn}{down}For people who know what progress means !"
 11140 printtab(31)"{lred}{down}Druk op een toets om verder te gaan"
 11150 gosub26490
 11160 gosub25260
 11170 return
 11180 :
 11190 rem "--- Kleurlegenda ---
 11200 :
 11210 xc=45:yc=2:b=32:h=21:gosub26270
 11220 window48,4,79,24:print"{lgrn}Legenda kleurgebruik"
 11230 print"{lred}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}"
 11240 print"{cyn}Velden rand bord:"
 11250 print"{down}{rvon}{grn}{CBM-@}{CBM-@}{rvof}{yel} Diverse aktiviteiten"
 11260 print"{rvon}{pur}{CBM-@}{CBM-@}{rvof}{yel} Speciale aktiviteiten"
 11270 print"{rvon}{brn}{CBM-@}{CBM-@}{rvof}{yel} Ontvang kanskaart"
 11280 print"{rvon}{wht}{CBM-@}{CBM-@}{rvof}{yel} Begin carri{CBM-*}re"
 11290 print"{cyn}{down}Velden in carri{CBM-*}re:"
 11300 print"{down}{rvon}{wht}{CBM-@}{CBM-@}{rvof}{yel} Diversen"
 11310 print"{rvon}{lred}{CBM-@}{CBM-@}{rvof}{yel} Ontvang gelukspunten ({lred}{CBM-+}{yel})"
 11320 print"{rvon}{yel}{CBM-@}{CBM-@}{rvof} Ontvang beroemdheid  (*)"
 11330 print"{rvon}{lgrn}{CBM-@}{CBM-@}{rvof}{yel} Ontvang geld"
 11340 print"{rvon}{yel}{CBM-@}{lred}{CBM-@}{rvof}{yel} Combinatie geluk/beroemd"
 11350 print"{rvon}{yel}{CBM-@}{lgrn}{CBM-@}{rvof}{yel} Combinatie geluk/geld"
 11360 print"{cyn}{down}Druk op een toets S.V.P.";
 11370 gosub26490
 11380 gosub25260
 11390 return
 11400 :
 11410 rem "--- Dobbelen ---
 11420 :
 11430 dd=0:xc=50:yc=10:b=11:h=7:gosub26270
 11440 forn=1to50
 11450 : print"{home}{home}":window52,12,79,24:print"{wht}";
 11460 : d1=int(rnd(1)*6):d2=int(rnd(1)*6)
 11470 : printdn$(d1);
 11480 : ifda=2thenprintdn$(d2)
 11490 : forw=1to20:nextw
 11500 nextn
 11510 dg=d1+1
 11520 ifda=2thendg=dg+d2+1:ifd1=d2thendd=1
 11530 print"{home}{home}":window52,16,79,24:print"{lgrn}Toets."
 11540 gosub26490
 11550 gosub25260
 11560 return
 11570 :
 11580 rem "--- Initialisatie ---
 11590 :
 11600 dimcv(32,1),cc(8,13,1),vk(32,1),ca(8,13,4),ca$(8,13),ks(3,19)
 11610 dimka(15),kk$(15,1),dn$(5),sp(3,7),sp$(3,1),cb(8),kb(15,1),wc(19)
 11620 restore26690
 11630 forn=1to32:readcv(n,0),cv(n,1):nextn
 11640 forn=1to8
 11650 : an=0
 11660 : do
 11670 :   readd1,d2
 11680 :   ifd2=-1thencc(n,0,1)=d1:cc(n,0,0)=an:exit
 11690 :   an=an+1
 11700 :   cc(n,an,0)=d1:cc(n,an,1)=d2
 11710 : loop
 11720 nextn
 11730 forn=1to32:readvk(n,0),vk(n,1):nextn
 11740 forn=1to8
 11750 : form=1tocc(n,0,0)
 11760 :   readca(n,m,0),ca(n,m,1),ca$(n,m),ca(n,m,2),ca(n,m,3),ca(n,m,4)
 11770 : nextm
 11780 nextn
 11790 forn=1to15:readkk$(n,0),kk$(n,1),kb(n,0),kb(n,1):nextn
 11800 forn=0to5:readdn$(n):nextn
 11810 forn=1to8:readca$(n,0):nextn
 11820 forn=1to8:readcb(n):nextn
 11830 return
 11840 :
 11850 rem "--- Ingave spelernamen ---
 11860 :
 11870 xc=35:yc=8:b=41:h=7:gosub26270
 11880 forsp=0to3
 11890 : window37,10,79,24:print"{yel}Moet de computer voor speler"sp+1"spelen ?"
 11900 : xc=69:yc=12:mn=5:gosub25300
 11910 : ifm=1thensp(sp,6)=1
 11920 : window37,10,79,24:printleft$(s$,39)
 11930 : window37,10,79,24:print"{yel}Geef naam speler"sp+1"in :"
 11940 : xc=37:yc=12:ml=20:tt$=al$:gosub25910
 11950 : sp$(sp,0)=an$
 11960 : window37,10,79,24:printleft$(s$,39)
 11970 : window37,12,79,24:printleft$(s$,20)
 11980 nextsp
 11990 gosub25260
 12000 return
 12010 :
 12020 rem "--- Informatie spelstand ---
 12030 :
 12040 ea=0
 12050 forn=1tolen(sp$(bs,1))
 12060 : ifmid$(sp$(bs,1),n,1)="1"thenea=ea+1
 12070 nextn
 12080 xc=40:b=34:h=14+ea:yc=11-int(h/2):gosub26270
 12090 window42,yc+2,79,24:print"{lgrn}Speler"bs+1":{cyn} "sp$(bs,0)
 12100 print"{lred}"left$(o$,len(sp$(bs,0))+10)
 12110 print"{yel}Geluk        ({lred}{CBM-+}{yel}) :     {cyn}";:printusing"#,###,###";sp(bs,4)
 12120 print"{yel}Beroemdheid  (*) :     {cyn}";:printusing"#,###,###";sp(bs,5)
 12130 print"{yel}Geld             : Fl. {cyn}";:printusing"#,###,###";sp(bs,3)
 12140 print"{yel}Salaris          : Fl. {cyn}";:printusing"#,###,###";sp(bs,2)
 12150 print"{yel}{down}Academische graad:"
 12160 print"{cyn}";
 12170 ifleft$(sp$(bs,1),4)="0000"thenprint"Geen"
 12180 ifmid$(sp$(bs,1),1,1)="1"thenprint"Rechten"
 12190 ifmid$(sp$(bs,1),2,1)="1"thenprint"Medicijnen"
 12200 ifmid$(sp$(bs,1),3,1)="1"thenprint"Wis- en natuurkunde"
 12210 ifmid$(sp$(bs,1),4,1)="1"thenprint"Werktuigkunde"
 12220 ifright$(sp$(bs,1),7)<>"0000000"thenbegin
 12230 : print"{yel}{down}Ervaring:{cyn}"
 12240 : ifmid$(sp$(bs,1),5,1)="1"thenprint"Landbouw"
 12250 : ifmid$(sp$(bs,1),6,1)="1"thenprint"Handel"
 12260 : ifmid$(sp$(bs,1),7,1)="1"thenprint"Zeevaart"
 12270 : ifmid$(sp$(bs,1),8,1)="1"thenprint"Politiek"
 12280 : ifmid$(sp$(bs,1),9,1)="1"thenprint"Hollywood"
 12290 : ifmid$(sp$(bs,1),10,1)="1"thenprint"Uranium"
 12300 : ifmid$(sp$(bs,1),11,1)="1"thenprint"Mars"
 12310 bend:elseprint"{yel}Geen ervaring."
 12320 window42,yc+h-1,79,24:print"{lgrn}Toets."
 12330 gosub26490
 12340 gosub25260
 12350 return
 12360 :
 12370 rem "--- Weet U het zeker ? ---
 12380 :
 12390 xc=55:yc=8:b=20:h=7:gosub26270
 12400 window57,10,79,24:print"{yel}Weet U het zeker ?"
 12410 xc=68:yc=12:mn=5:gosub25300
 12420 gosub25260
 12430 return
 12440 :
 12450 rem "--- Toon kaartenbezit ---
 12460 :
 12470 ka=0:ea=0
 12480 forn=1to15
 12490 : ifks(bs,n)thenka=ka+1
 12500 nextn
 12510 forn=16to19
 12520 : ifks(bs,n)thenea=ea+1
 12530 nextn
 12540 h=9
 12550 ifea>kathenh=h+ea-1
 12560 ifka>eathenh=h+ka-1
 12570 ifka=eathenh=h+ea-1
 12580 xc=1:yc=11-int(h/2):b=75:gosub26270
 12590 window3,yc+2,79,24:print"{lgrn}Speler"bs+1"{left}: {cyn}"sp$(bs,0)
 12600 print"{lred}"left$(o$,len(sp$(bs,0))+10)
 12610 print"{cyn}Kanskaarten                                Ervaringskaarten"
 12620 print"{wht}{down}Aantal:  Wat kunt U doen:  Voorwaarde:     Aantal:  Aantal vakken:"
 12630 y=yc+7
 12640 forn=1to15
 12650 : ifks(bs,n)thenbegin
 12660 :   window4,y,79,24:print"{cyn}";:printusing"##";ks(bs,n)
 12670 :   window12,y,79,24:printkk$(n,0)
 12680 :   window30,y,79,24:printkk$(n,1)
 12690 :   y=y+1
 12700 : bend
 12710 nextn
 12720 y=yc+7
 12730 forn=1to4
 12740 : ifks(bs,n+15)>0thenbegin
 12750 :   window47,y,79,24:print"{cyn}";:printusing"##";ks(bs,n+15)
 12760 :   window56,y,79,24:printusing"##";n
 12770 :   y=y+1
 12780 : bend
 12790 nextn
 12800 ifka=0thenwindow3,yc+6,79,24:print"{wht}U heeft geen kanskaarten.             "
 12810 ifea=0thenwindow46,yc+6,79,24:print"{wht}U heeft geen ervaringskaarten."
 12820 window3,yc+h-1,79,24:print"{lgrn}Toets."
 12830 gosub26490
 12840 gosub25260
 12850 return
 12860 :
 12870 rem "--- Verschillende velden ---
 12880 :
 12890 rem "- Start -
 12900 xc=40:yc=8:b=35:h=8:gosub26270
 12910 window42,10,79,24:print"{yel}U bent op {lgrn}START{yel} terecht gekomen."
 12920 print"{down}{yel}U ontvangt dubbel salaris, nml."
 12930 print"Fl. {cyn}";
 12940 printusing"#,###,###";sp(bs,2)*2
 12950 print"{down}{lgrn}Toets."
 12960 ifai=0thensp(bs,3)=sp(bs,3)+sp(bs,2)*2
 12970 gosub26490
 12980 gosub25260
 12990 return
 13000 rem "- Kans -
 13010 xc=40:yc=8:b=35:h=8:gosub26270
 13020 window42,10,79,24:print"{yel}U krijgt een {brn}KANS{yel}-kaart."
 13030 ifai=0thenbegin
 13040 : gosub24590
 13050 : ifkg<>-1thenbegin
 13060 :   ks(bs,kg)=ks(bs,kg)+1
 13070 :   print"{yel}{down}Activiteit : {cyn}"kk$(kg,0)
 13080 :   print"{yel}Voorwaarde : {cyn}"kk$(kg,1)
 13090 : bend:elseprint"{yel}{down}Kanskaarten zijn op."
 13100 bend
 13110 window42,15,79,24:print"{lgrn}Toets."
 13120 gosub26490
 13130 gosub25260
 13140 return
 13150 rem "- Inkomsten belasting -
 13160 xc=40:yc=8:b=35:h=7:gosub26270
 13170 window42,10,79,24:print"{yel}U komt op {orng}INKOMSTENBELASTING{yel}."
 13180 ifsp(bs,2)<=30000thentb=.1*sp(bs,2)
 13190 ifsp(bs,2)>30000andsp(bs,2)<100000thentb=.5*sp(bs,2)
 13200 ifsp(bs,2)>=100000thentb=.9*sp(bs,2)
 13210 iftb>sp(bs,3)thentb=sp(bs,3)
 13220 print"{down}Te betalen : Fl. {cyn}";
 13230 printusing"#,###,###";tb
 13240 ifai=0thensp(bs,3)=sp(bs,3)-tb
 13250 print"{down}{lgrn}Toets."
 13260 gosub26490
 13270 gosub25260
 13280 return
 13290 rem "- Landbouw -
 13300 xc=40:yc=8:b=35:h=11:gosub26270
 13310 window42,10,79,24:print"{yel}U kunt in de {wht}LANDBOUW{yel}."
 13320 ifmid$(sp$(bs,1),5,1)="0"thenbegin
 13330 : print"{down}Kosten voor zaden en landbouwwerk-"
 13340 : print"tuigen : Fl. {cyn}10.000"
 13350 bend:elsebegin
 13360 : print"{down}Vanwege Uw landbouwervaring zijn"
 13370 : print"er geen kosten."
 13380 bend
 13390 ifai=0and(sp(bs,3)>=10000ormid$(sp$(bs,1),5,1)="1")thenbegin
 13400 : ifsp(bs,6)=1thenm=1:elsebegin
 13410 :   print"{down}{yel}Wilt U hieraan beginnen ?"
 13420 :   xc=69:yc=16:mn=5:gosub25300
 13430 : bend
 13440 : ifm=1thenbegin
 13450 :   sp(bs,0)=1:sp(bs,1)=0
 13460 :   ifmid$(sp$(bs,1),5,1)="0"thensp(bs,3)=sp(bs,3)-10000
 13470 : bend
 13480 bend
 13490 print"{home}{home}":window42,15,79,24:print"{lgrn}Toets.                    "
 13500 gosub26490
 13510 gosub25260
 13520 return
 13530 rem "- Autoshow -
 13540 xc=40:yc=5:b=35:h=15:gosub26270
 13550 window42,7,79,24:print"{yel}U bent op de {orng}AUTO-SHOW{yel}."
 13560 print"{down}U kunt maximaal een jaarsalaris"
 13570 print"besteden aan een nieuwe auto."
 13580 print"Voor elke bestede Fl. 10.000"
 13590 print"ontvangt U {lred}1 {CBM-+}{yel}."
 13600 ifsp(bs,4)>0thenbegin
 13610 : print"Niets uitgeven kost u {lred}1 {CBM-+}{yel}."
 13620 bend
 13630 an$="0"
 13640 ifai=0andsp(bs,3)>=10000thenbegin
 13650 : window42,15,79,24:print"Hoeveel keer wilt U Fl. 10000"
 13660 : print"uitgeven ?"
 13670 : ifsp(bs,6)=1thenbegin
 13680 :   gm=int((sp(bs,3)-200000)/10000):hm=20-sp(bs,4)
 13690 :   ifgm>0andhm>0thenbegin
 13700 :     ifgm>hmthengm=hm
 13710 :   bend:elsegm=0
 13720 :   an$=str$(gm):window41,17,79,24:print"{cyn}"an$
 13730 : bend:elsebegin
 13740 :   do
 13750 :     xc=42:yc=17:ml=4:tt$=ci$:gosub25910
 13760 :   loopwhileval(an$)*10000>sp(bs,3)
 13770 : bend
 13780 : sp(bs,3)=sp(bs,3)-val(an$)*10000
 13790 : sp(bs,4)=sp(bs,4)+val(an$)
 13800 bend
 13810 ifsp(bs,4)>0andan$="0"andai=0thensp(bs,4)=sp(bs,4)-1
 13820 window42,19,79,24:print"{lgrn}Toets."
 13830 gosub26490
 13840 gosub25260
 13850 return
 13860 rem "- Universiteit -
 13870 xc=40:yc=8:b=35:h=10:gu=0:gosub26270
 13880 window42,10,79,24:print"{yel}U kunt naar de {wht}UNIVERSITEIT{yel}."
 13890 ifinstr(left$(sp$(bs,1),4),"1")>0thenbegin
 13900 : print"{down}U heeft echter al gestudeerd, en"
 13910 : print"heeft U maximale inschrijvings-"
 13920 : print"tijd al verbruikt."
 13930 : gu=1
 13940 bend
 13950 ifsp(bs,3)<5000andgu=0thenbegin
 13960 : print"{down}U heeft echter geen geld genoeg"
 13970 : print"om te kunnen studeren."
 13980 : gu=1
 13990 bend
 14000 ifgu=0thenbegin
 14010 : print"{down}Kosten: Fl. {cyn}5.000"
 14020 bend
 14030 ifai=0andgu=0thenbegin
 14040 : ifsp(bs,6)=1thenm=1:elsebegin
 14050 :   window42,14,79,24:print"{yel}Wilt U gaan ?"
 14060 :   xc=69:yc=15:mn=5:gosub25300
 14070 : bend
 14080 : ifm=1thenbegin
 14090 :   sp(bs,0)=2:sp(bs,1)=0:sp(bs,3)=sp(bs,3)-5000
 14100 : bend
 14110 : window42,14,79,24:print"             "
 14120 bend
 14130 window42,16,79,24:print"{lgrn}Toets."
 14140 gosub26490
 14150 gosub25260
 14160 return
 14170 rem "- Ziekenhuis -
 14180 xc=40:yc=5:b=35:h=16:gosub26270
 14190 window42,7,79,24:print"{yel}U bent in het {grn}ZIEKENHUIS{yel} beland."
 14200 print"{down}U moet in bed blijven tot U 5 of"
 14210 print"minder gooit. U mag geen kans- of"
 14220 print"ervaringskaarten gebruiken, maar"
 14230 print"U mag voor U gooit alle personen"
 14240 print"met een medische graad, of als"
 14250 print"deze er niet zijn de bank, de"
 14260 print"helft van Uw salaris voor spe-"
 14270 print"ciale behandeling betalen, en"
 14280 print"daarna gewoon het aantal ogen van"
 14290 print"Uw worp verder gaan."
 14300 print"{lgrn}{down}Toets."
 14310 gosub26490
 14320 gosub25260
 14330 return
 14340 rem "- Betaal rekeningen -
 14350 xc=40:yc=8:b=35:h=7:gosub26270
 14360 window42,10,79,24:print"{yel}U moet Uw {orng}REKENINGEN{$a0}BETALEN{yel}."
 14370 print"{down}Kosten : Fl. {cyn}";
 14380 printusing"#,###,###";.25*sp(bs,3)
 14390 ifai=0thensp(bs,3)=.75*sp(bs,3)
 14400 print"{lgrn}{down}Toets."
 14410 gosub26490
 14420 gosub25260
 14430 return
 14440 rem "- Handel -
 14450 xc=40:yc=8:b=35:h=11:gu=0:gosub26270
 14460 window42,10,79,24:print"{yel}U kunt in de {wht}HANDEL{yel}."
 14470 ifinstr(left$(sp$(bs,1),4),"1")>0ormid$(sp$(bs,1),6,1)="1"thenbegin
 14480 : print"{yel}{down}Vanwege Uw ervaring of opleiding"
 14490 : print"hoeft U niets te betalen.":gu=1
 14500 bend:elsebegin
 14510 : print"{yel}{down}Kosten vanwege handelsopleiding:"
 14520 : print"Fl. {cyn}5.000"
 14530 bend
 14540 ifai=0and(sp(bs,3)>=5000orgu=1)thenbegin
 14550 : ifsp(bs,6)=1thenm=1:elsebegin
 14560 :   print"{down}{yel}Wilt U dit ?"
 14570 :   xc=69:yc=16:mn=5:gosub25300
 14580 : bend
 14590 : ifm=1thenbegin
 14600 :   sp(bs,0)=3:sp(bs,1)=0:ifgu=0thensp(bs,3)=sp(bs,3)-5000
 14610 : bend
 14620 bend
 14630 window42,15,79,24:print"{lgrn}Toets.       "
 14640 gosub26490
 14650 gosub25260
 14660 return
 14670 rem "- Antiquair -
 14680 xc=40:yc=5:b=35:h=16:gosub26270
 14690 window42,7,79,24:print"{yel}U bent bij de {orng}ANTIQUAIR{yel}."
 14700 print"{down}Koop oude meesters voor"
 14710 print"Fl. 30.000 per stuk."
 14720 print"Gooi met een dobbelsteen voor"
 14730 print"elk gekocht schilderij, en"
 14740 print"ontvang 1 * maal het aantal"
 14750 print"ogen van de worp."
 14760 print"Maximaal 2 schilderijen per"
 14770 print"klant."
 14780 ifai=0andsp(bs,3)>=30000thenbegin
 14790 : print"{down}Hoeveel wilt U er kopen ? {rvon}{cyn} {rvof}{yel}";
 14800 : ifsp(bs,6)=1thenbegin
 14810 :   ifsp(bs,5)<20thenaw$="1":ifsp(bs,3)>=60000thenaw$="2"
 14820 : bend:elsebegin
 14830 :   do
 14840 :     tt$="012":gosub25550
 14850 :   loopwhileval(aw$)*30000>sp(bs,3)
 14860 : bend
 14870 : print"{left}{cyn}";aw$
 14880 : sp(bs,3)=sp(bs,3)-val(aw$)*30000
 14890 : ifval(aw$)>0thenda=val(aw$):gosub11430:sp(bs,5)=sp(bs,5)+dg
 14900 bend
 14910 window42,20,79,24:print"{lgrn}Toets."
 14920 gosub26490
 14930 gosub25260
 14940 return
 14950 rem "- Zeevaart -
 14960 xc=40:yc=8:b=35:h=11:gosub26270
 14970 window42,10,79,24:print"{yel}U kunt naar {wht}ZEE{yel}."
 14980 ifmid$(sp$(bs,1),7,1)="1"thenbegin
 14990 : print"{down}Vanwege Uw ervaring hoeft U"
 15000 : print"niets te betalen."
 15010 bend:elsebegin
 15020 : print"{down}Kosten opleiding tot stuurman:"
 15030 : print"Fl. {cyn}1.000{yel}"
 15040 bend
 15050 ifai=0and(sp(bs,3)>=1000ormid$(sp$(bs,1),7,1)="1")thenbegin
 15060 : ifsp(bs,6)=1thenm=1:elsebegin
 15070 :   print"{down}Wilt U dit ?"
 15080 :   xc=69:yc=16:mn=5:gosub25300
 15090 : bend
 15100 : ifm=1thenbegin
 15110 :   sp(bs,0)=4:sp(bs,1)=0
 15120 :   ifmid$(sp$(bs,1),7,1)="0"thensp(bs,3)=sp(bs,3)-1000
 15130 : bend
 15140 bend
 15150 window42,15,79,24:print"{lgrn}Toets.       "
 15160 gosub26490
 15170 gosub25260
 15180 return
 15190 rem "- Arbeidsbureau -
 15200 xc=40:yc=5:b=35:h=14:gosub26270
 15210 window42,7,79,24:print"{yel}U bent in het {grn}ARBEIDSBUREAU{yel}."
 15220 print"{down}U bent zonder werk en moet 7, 11"
 15230 print"of dubbel gooien om verder te"
 15240 print"gaan. U mag geen kans- of er-"
 15250 print"varingskaarten gebruiken, maar"
 15260 print"U mag voor U gooit de helft van"
 15270 print"Uw geld aan nieuwe kleding be-"
 15280 print"steden, en daarna het aantal"
 15290 print"ogen van Uw worp verder gaan."
 15300 print"{down}{lgrn}Toets."
 15310 gosub26490
 15320 gosub25260
 15330 return
 15340 rem "- Betaal huur -
 15350 xc=40:yc=8:b=35:h=7:gosub26270
 15360 window42,10,79,24:print"{yel}U moet Uw {orng}HUUR BETALEN{yel}."
 15370 tb=.5*sp(bs,2)
 15380 iftb>sp(bs,3)thentb=sp(bs,3)
 15390 print"{down}Kosten : Fl. {cyn}";
 15400 printusing"#,###,###";tb
 15410 ifai=0thensp(bs,3)=sp(bs,3)-tb
 15420 print"{down}{lgrn}Toets."
 15430 gosub26490
 15440 gosub25260
 15450 return
 15460 rem "- Politiek -
 15470 gu=0:xc=40:yc=8:b=35:h=11:gosub26270
 15480 window42,10,79,24:print"{yel}U kunt in de {wht}POLITIEK{yel}."
 15490 ifmid$(sp$(bs,1),1,1)="1"ormid$(sp$(bs,1),8,1)="1"thenbegin
 15500 : gu=1
 15510 : print"{down}Door Uw ervaring of opleiding"
 15520 : print"hoeft U niet te betalen."
 15530 bend:elsebegin
 15540 : print"{down}Kosten storting partijfonds:"
 15550 : print"Fl. {cyn}30.000{yel}"
 15560 bend
 15570 ifai=0and(sp(bs,3)>=30000orgu=1)thenbegin
 15580 : ifsp(bs,6)=1thenm=1:elsebegin
 15590 :   print"{down}Wilt U dit ?"
 15600 :   xc=69:yc=16:mn=5:gosub25300
 15610 : bend
 15620 : ifm=1thenbegin
 15630 :   sp(bs,0)=5:sp(bs,1)=0:ifgu=0thensp(bs,3)=sp(bs,3)-30000
 15640 : bend
 15650 bend
 15660 window42,15,79,24:print"{lgrn}Toets.       "
 15670 gosub26490
 15680 gosub25260
 15690 return
 15700 rem "- Winkelen -
 15710 xc=40:yc=8:b=35:h=13:gosub26270
 15720 window42,10,79,24:print"{yel}U bent gaan {orng}WINKELEN{yel}."
 15730 ifsp(bs,3)=0thenbegin
 15740 : print"{down}U heeft echter niets gekocht"
 15750 : print"omdat U geen geld heeft."
 15760 bend:elsebegin
 15770 : print"{down}Gooi met 1 dobbelsteen om te"
 15780 : print"bepalen wat met winkelen is"
 15790 : print"uitgegeven. Betaal 10% van Uw"
 15800 : print"geld maal het aantal gegooide"
 15810 : print"ogen."
 15820 bend
 15830 ifai=0andsp(bs,3)>0thenbegin
 15840 : da=1:gosub11430
 15850 : window42,18,79,24:print"{yel}Kosten: Fl. {cyn}";
 15860 : printusing"#,###,###";.1*dg*sp(bs,3)
 15870 : sp(bs,3)=sp(bs,3)-.1*dg*sp(bs,3)
 15880 bend
 15890 window42,20,79,24:print"{lgrn}Toets."
 15900 gosub26490
 15910 gosub25260
 15920 return
 15930 rem "- Hollywood -
 15940 xc=40:yc=8:b=35:h=11:gosub26270
 15950 window42,10,79,24:print"{yel}U kunt naar {wht}HOLLYWOOD{yel}."
 15960 ifmid$(sp$(bs,1),9,1)="1"thenbegin
 15970 : print"{down}Vanwege Uw ervaring hoeft U"
 15980 : print"niets te betalen."
 15990 bend:elsebegin
 16000 : print"{down}Kosten nieuwe kleren:"
 16010 : print"Fl. {cyn}10.000{yel}"
 16020 bend
 16030 ifai=0and(sp(bs,3)>=10000ormid$(sp$(bs,1),9,1)="1")thenbegin
 16040 : ifsp(bs,6)=1thenm=1:elsebegin
 16050 :   print"{down}Wilt U dit ?"
 16060 :   xc=69:yc=16:mn=5:gosub25300
 16070 : bend
 16080 : ifm=1thenbegin
 16090 :   sp(bs,0)=6:sp(bs,1)=0
 16100 :   ifmid$(sp$(bs,1),9,1)="0"thensp(bs,3)=sp(bs,3)-10000
 16110 : bend
 16120 bend
 16130 window42,15,79,24:print"{lgrn}Toets.       "
 16140 gosub26490
 16150 gosub25260
 16160 return
 16170 rem "- Riviera -
 16180 xc=40:yc=8:b=35:h=12:gosub26270
 16190 window42,10,79,24:print"{yel}U bent {grn}IN{$a0}DE{$a0}RIVIERA OP{$a0}VAKANTIE{yel}."
 16200 print"{down}Ontvang {lred}4 {CBM-+}{yel} indien U hier terecht"
 16210 print"komt, en {lred}2 {CBM-+}{yel} voor elke keer dat U"
 16220 print"hier blijft staan. U mag blij-"
 16230 print"ven indien U 7 of minder gooit,"
 16240 print"maar U mag ook bij elke worp"
 16250 print"verder gaan."
 16260 ifai=0thensp(bs,4)=sp(bs,4)+4
 16270 print"{down}{lgrn}Toets."
 16280 gosub26490
 16290 gosub25260
 16300 return
 16310 rem "- Effectenbeurs -
 16320 xc=40:yc=5:b=35:h=16:gosub26270
 16330 window42,7,79,24:print"{yel}U bent op de {orng}EFFECTENBEURS{yel}."
 16340 print"{down}Koop pakketten aandelen voor"
 16350 print"Fl. 30.000 per stuk. Gooi met"
 16360 print"een dobbelsteen en verkoop"
 16370 print"het pakket aan de bank voor"
 16380 print"Fl. 10.000 maal het aantal"
 16390 print"ogen van de worp. Voor ieder"
 16400 print"gekocht pakket een keer gooi-"
 16410 print"en. Geen aankoopbeperking."
 16420 ifai=0andsp(bs,3)>=30000thenbegin
 16430 : print"{down}Hoeveel pakketten koopt U ?"
 16440 : ifsp(bs,6)=1thenbegin
 16450 :   an$=str$(int(sp(bs,3))/30000):print"{cyn}"an$
 16460 : bend:elsebegin
 16470 :   do
 16480 :     xc=42:yc=19:ml=3:tt$=ci$:gosub25910
 16490 :   loopwhileval(an$)*30000>sp(bs,3)
 16500 : bend
 16510 : window42,18,73,19,1:window0,0,79,24
 16520 : wi=-30000*val(an$)
 16530 : ifval(an$)>0thenbegin
 16540 :   ford=1toval(an$)
 16550 :     da=1:gosub11430:wi=wi+10000*dg
 16560 :   nextd
 16570 : bend
 16580 : window42,18,79,24:ifwi<0thenprint"{yel}Verlies : Fl. {cyn}";:elseprint"{yel}Winst : Fl. {cyn}";
 16590 : printusing"#,###,###";abs(wi)
 16600 : sp(bs,3)=sp(bs,3)+wi
 16610 bend
 16620 window42,20,79,24:print"{lgrn}Toets."
 16630 gosub26490
 16640 gosub25260
 16650 return
 16660 rem "- Uranium -
 16670 gu=0:xc=40:yc=8:b=35:h=11:gosub26270
 16680 window42,10,79,24:print"{yel}U kunt {wht}URANIUM{yel} gaan zoeken."
 16690 ifmid$(sp$(bs,1),4,1)="1"ormid$(sp$(bs,1),10,1)="1"thenbegin
 16700 : gu=1
 16710 : print"{down}Vanwege Uw ervaring of opleiding"
 16720 : print"hoeft U niet te betalen."
 16730 bend:elsebegin
 16740 : print"{down}Kosten uitrusting:"
 16750 : print"Fl. {cyn}40.000{yel}"
 16760 bend
 16770 ifai=0and(sp(bs,3)>=40000orgu=1)thenbegin
 16780 : ifsp(bs,6)=1thenm=1:elsebegin
 16790 :   print"{down}Wilt U dit ?"
 16800 :   xc=69:yc=16:mn=5:gosub25300
 16810 : bend
 16820 : ifm=1thenbegin
 16830 :   sp(bs,0)=7:sp(bs,1)=0:ifgu=0thensp(bs,3)=sp(bs,3)-40000
 16840 : bend
 16850 bend
 16860 window42,15,79,24:print"{lgrn}Toets.       "
 16870 gosub26490
 16880 gosub25260
 16890 return
 16900 rem "- Jachthaven -
 16910 xc=40:yc=5:b=35:h=17:gosub26270
 16920 window42,7,79,24:print"{yel}U bent in de {orng}JACHTHAVEN{yel}."
 16930 print"{down}Zeilboten te koop."
 16940 print"{down}Ontvang bij betaling van:"
 16950 print"{yel}Fl.  20.000     {lred}4 {CBM-+}"
 16960 print"{yel}Fl.  80.000     {lred}8 {CBM-+}"
 16970 print"{yel}Fl. 160.000    {lred}12 {CBM-+}"
 16980 ifai=0andsp(bs,3)>=20000thenbegin
 16990 : print"{down}{yel}Hoeveel wilt U uitgeven ?"
 17000 : ifsp(bs,6)=1thenbegin
 17010 :   mh=20-sp(bs,4):mg=sp(bs,3)-200000:an$="0     "
 17020 :   ifmg>20000andmh>0thenm=1:an$="20.000"
 17030 :   ifmg>80000andmh>7thenm=2:an$="80.000"
 17040 :   ifmg>160000andmh>11thenm=3:an$="160.000"
 17050 :   window42,16,79,24:print"Uitgegeven : {cyn}"an$"      "
 17060 :   print"{home}{home}":window42,18,79,24:print"{lgrn}Toets."
 17070 : bend:elsebegin
 17080 :   do
 17090 :     gu=sp(bs,3)
 17100 :     xc=60:yc=17:mn=7:gosub25300
 17110 :     gu=gu+20000*(m=1)+80000*(m=2)+160000*(m=3)
 17120 :   loopwhilegu<0
 17130 : bend
 17140 : ifm=1thensp(bs,3)=sp(bs,3)-20000:sp(bs,4)=sp(bs,4)+4
 17150 : ifm=2thensp(bs,3)=sp(bs,3)-80000:sp(bs,4)=sp(bs,4)+8
 17160 : ifm=3thensp(bs,3)=sp(bs,3)-160000:sp(bs,4)=sp(bs,4)+12
 17170 bend
 17180 ifsp(bs,6)=0orsp(bs,3)<20000thenwindow42,16,79,24:print"{lgrn}Toets.                     "
 17190 gosub26490
 17200 gosub25260
 17210 return
 17220 rem "- Mars -
 17230 gu=0:xc=40:yc=8:b=35:h=11:gosub26270
 17240 window42,10,79,24:print"{yel}U kunt naar {wht}MARS{yel} gaan."
 17250 ifmid$(sp$(bs,1),3,1)="1"ormid$(sp$(bs,1),11,1)="1"thenbegin
 17260 : gu=1
 17270 : print"{down}Vanwege Uw opleiding of ervaring"
 17280 : print"hoeft U niet te betalen."
 17290 bend:elsebegin
 17300 : print"{down}Kosten bijdrage onderzoek:"
 17310 : print"Fl. {cyn}50.000{yel}"
 17320 bend
 17330 ifai=0and(sp(bs,3)>=50000orgu=1)thenbegin
 17340 : ifsp(bs,6)=1thenm=1:elsebegin
 17350 :   print"{down}Wilt U dit ?"
 17360 :   xc=69:yc=16:mn=5:gosub25300
 17370 : bend
 17380 : ifm=1thenbegin
 17390 :   sp(bs,0)=8:sp(bs,1)=0:ifgu=0thensp(bs,3)=sp(bs,3)-50000
 17400 : bend
 17410 bend
 17420 window42,15,79,24:print"{lgrn}Toets.       "
 17430 gosub26490
 17440 gosub25260
 17450 return
 17460 rem "- Schenking -
 17470 xc=40:yc=5:b=35:h=17:gosub26270
 17480 window42,7,79,24:print"{yel}U kunt de {orng}GEMEENTE SCHENKEN{yel}:"
 17490 print"{down}Clubhuis,  betaal Fl.  {cyn}40.000{yel}"
 17500 print"           ontvang  4 *"
 17510 print"Speeltuin, betaal Fl.  {cyn}80.000{yel}"
 17520 print"           ontvang 10 *"
 17530 print"Zwembad,   betaal Fl. {cyn}120.000{yel}"
 17540 print"           ontvang 16 *"
 17550 ifai=0andsp(bs,3)>=40000thenbegin
 17560 : print"{down}Wat wilt U schenken ?"
 17570 : ifsp(bs,6)=1thenbegin
 17580 :   sm=20-sp(bs,5):gm=sp(bs,3)-200000:an$="Niets  "
 17590 :   ifgm>40000andsm>0thenm=1:an$="Clubhuis"
 17600 :   ifgm>80000andsm>9thenm=2:an$="Speeltuin"
 17610 :   ifgm>120000andsm>15thenm=3:an$="Zwembad"
 17620 :   window42,16,79,24:print"Schenking : {cyn}"an$"  "
 17630 :   print"{down}{lgrn}Toets."
 17640 : bend:elsebegin
 17650 :   do
 17660 :     gu=sp(bs,3)
 17670 :     xc=63:yc=17:mn=8:gosub25300
 17680 :     gu=gu+40000*(m=1)+80000*(m=2)+120000*(m=3)
 17690 :   loopwhilegu<0
 17700 : bend
 17710 : sp(bs,3)=gu
 17720 : sp(bs,5)=sp(bs,5)-4*(m=1)-10*(m=2)-16*(m=3)
 17730 bend
 17740 ifsp(bs,1)=0thenwindow42,16,79,24:print"{lgrn}Toets.                "
 17750 gosub26490
 17760 gosub25260
 17770 return
 17780 rem "--- Carriere algemeen ---
 17790 xc=30:yc=8:b=45:h=12:gosub26270
 17800 window32,10,79,24:print"{yel}Carri{CBM-*}re : {cyn}"ca$(sp(bs,0),0)
 17810 print"{down}{yel}"ca$(sp(bs,0),sp(bs,1))
 17820 return
 17830 rem "- Ontvang geluk -
 17840 gosub17790
 17850 print"{down}{yel}Ontvang {lred}"ca(sp(bs,0),sp(bs,1),3)"{CBM-+}{yel}"
 17860 ifai=0thensp(bs,4)=sp(bs,4)+ca(sp(bs,0),sp(bs,1),3)
 17870 gosub17900
 17880 return
 17890 rem "- Toets -
 17900 window32,19,79,24:print"{lgrn}Toets."
 17910 gosub26490
 17920 gosub25260
 17930 return
 17940 rem "- Ervaringskaart -
 17950 gosub17790
 17960 print"{down}{yel}Ontvang {cyn}"ca(sp(bs,0),sp(bs,1),3)"{yel}ervaringskaart(en)."
 17970 ifai=0thenbegin
 17980 : forea=1toca(sp(bs,0),sp(bs,1),3)
 17990 :   gu=int(rnd(1)*4)+1
 18000 :   window32,15+ea,79,24
 18010 :   print"{yel}Met kaart{cyn}"ea"{yel}kunt U{cyn}"gu"{yel}vak(ken) vooruit."
 18020 :   ks(bs,15+gu)=ks(bs,15+gu)+1
 18030 : nextea
 18040 bend
 18050 gosub17900
 18060 return
 18070 rem "- Fl. maal ogen -
 18080 gosub17790
 18090 print"{yel}{down}Ontvang Fl.{cyn}"ca(sp(bs,0),sp(bs,1),3)"{yel}maal aantal ogen worp."
 18100 ifai=0thenbegin
 18110 : da=1:gosub11430
 18120 : window32,16,79,24:print"{yel}Winst : Fl. {cyn}";
 18130 : printusing"#,###,###";ca(sp(bs,0),sp(bs,1),3)*dg
 18140 : sp(bs,3)=sp(bs,3)+ca(sp(bs,0),sp(bs,1),3)*dg
 18150 bend
 18160 gosub17900
 18170 return
 18180 rem "- Ster en Hart -
 18190 gosub17790
 18200 print"{yel}{down}Ontvang{lred}";
 18210 printca(sp(bs,0),sp(bs,1),3)"{CBM-+}{yel} en"ca(sp(bs,0),sp(bs,1),4)"*"
 18220 ifai=0thensp(bs,4)=sp(bs,4)+ca(sp(bs,0),sp(bs,1),3):sp(bs,5)=sp(bs,5)+ca(sp(bs,0),sp(bs,1),4)
 18230 gosub17900
 18240 return
 18250 rem "- Ontvang geld -
 18260 gosub17790
 18270 print"{yel}{down}Ontvang Fl. {cyn}";
 18280 printusing"#,###,###";ca(sp(bs,0),sp(bs,1),3)
 18290 ifai=0thensp(bs,3)=sp(bs,3)+ca(sp(bs,0),sp(bs,1),3)
 18300 gosub17900
 18310 return
 18320 rem "- Weg helft geld -
 18330 gosub17790
 18340 print"{yel}{down}Verlies Fl. {cyn}";
 18350 printusing"#,###,###";.5*sp(bs,3)
 18360 ifai=0thensp(bs,3)=.5*sp(bs,3)
 18370 gosub17900
 18380 return
 18390 rem "- Sla beurt over -
 18400 gosub17790
 18410 print"{yel}{down}U moet een beurt overslaan."
 18420 ifai=0thensp(bs,7)=1
 18430 gosub17900
 18440 return
 18450 rem "- Geluk ontvangen -
 18460 gosub17790
 18470 print"{down}{yel}Ontvang";
 18480 printca(sp(bs,0),sp(bs,1),3)"*"
 18490 ifai=0thensp(bs,5)=sp(bs,5)+ca(sp(bs,0),sp(bs,1),3)
 18500 gosub17900
 18510 return
 18520 rem "- Kanskaart -
 18530 gosub17790
 18540 print"{yel}{down}U ontvangt{cyn}";
 18550 printca(sp(bs,0),sp(bs,1),3)"{yel}kanskaart(en)."
 18560 ifai=0thenbegin
 18570 : forn=1toca(sp(bs,0),sp(bs,1),3)
 18580 :   gosub24590
 18590 :   ifkg=-1thenbegin
 18600 :     window32,15+n,79,24:print"{yel}Kanskaarten zijn op."
 18610 :     ka=ca(sp(bs,0),sp(bs,1),3)
 18620 :   bend:elsebegin
 18630 :     window32,15+n,79,24:print"{yel}Kanskaart{cyn}";
 18640 :     printn"{yel}: "kk$(kg,0)" "kk$(kg,1)
 18650 :     ks(bs,kg)=ks(bs,kg)+1
 18660 :   bend
 18670 : nextn
 18680 bend
 18690 gosub17900
 18700 return
 18710 rem "- Hoger salaris -
 18720 gosub17790
 18730 print"{yel}{down}Uw salaris wordt met Fl. {cyn}";
 18740 printusing"#,###,###";ca(sp(bs,0),sp(bs,1),3);
 18750 print"{yel} verhoogd."
 18760 ifai=0thensp(bs,2)=sp(bs,2)+ca(sp(bs,0),sp(bs,1),3)
 18770 gosub17900
 18780 return
 18790 rem "- Naar arbeidbureau -
 18800 gosub17790
 18810 gosub17790
 18820 print"{yel}{down}Ga naar het arbeidsbureau."
 18830 gosub17900
 18840 ifai=0thenbegin
 18850 : gosub20250
 18860 : sp(bs,0)=0:sp(bs,1)=17
 18870 : gosub20120
 18880 : gosub15200
 18890 bend
 18900 return
 18910 rem "- Weg helft salaris -
 18920 gosub17790
 18930 print"{yel}{down}Uw salaris wordt met Fl. {cyn}";
 18940 printusing"#,###,###";.5*sp(bs,2)
 18950 print"{yel}vermindert."
 18960 ifai=0thensp(bs,2)=.5*sp(bs,2)
 18970 gosub17900
 18980 return
 18990 rem "- Naar ziekenhuis -
 19000 gosub17790
 19010 print"{yel}{down}Ga naar het ziekenhuis."
 19020 gosub17900
 19030 ifai=0thenbegin
 19040 : gosub20250
 19050 : sp(bs,0)=0:sp(bs,1)=9
 19060 : gosub20120
 19070 : gosub14180
 19080 bend
 19090 return
 19100 rem "- Ontvang geluk en geld -
 19110 gosub17790
 19120 print"{yel}{down}U ontvangt";
 19130 printca(sp(bs,0),sp(bs,1),3);"* en Fl. {cyn}";
 19140 printusing"#,###,###";ca(sp(bs,0),sp(bs,1),4)
 19150 ifai=0thensp(bs,3)=sp(bs,3)+ca(sp(bs,0),sp(bs,1),4):sp(bs,5)=sp(bs,5)+ca(sp(bs,0),sp(bs,1),3)
 19160 gosub17900
 19170 return
 19180 rem "- Weg helft sterren -
 19190 gosub17790
 19200 print"{yel}{down}U verliest";
 19210 printint(.5*sp(bs,5));"*"
 19220 ifai=0thensp(bs,5)=int(.5*sp(bs,5))
 19230 gosub17900
 19240 return
 19250 rem "- Ontvang sterren, weg hartjes -
 19260 gosub17790
 19270 print"{yel}{down}U ontvangt";
 19280 printca(sp(bs,0),sp(bs,1),3)"* ,"
 19290 print"maar U verliest al Uw {lred}";
 19300 print"{CBM-+}"
 19310 ifai=0thensp(bs,4)=0:sp(bs,5)=sp(bs,5)+ca(sp(bs,0),sp(bs,1),3)
 19320 gosub17900
 19330 return
 19340 rem "- Salaris verhogen via worp -
 19350 gosub17790
 19360 print"{yel}{down}Je salaris wordt verhoogd met Fl.{cyn}";
 19370 printca(sp(bs,0),sp(bs,1),3)
 19380 print"{yel}maal het aantal ogen van een worp."
 19390 ifai=0thenbegin
 19400 : da=1:gosub11430
 19410 : window32,17,79,24:print"{yel}Verhoging : Fl. {cyn}";
 19420 : printusing"#,###,###";ca(sp(bs,0),sp(bs,1),3)*dg
 19430 : sp(bs,2)=sp(bs,2)+ca(sp(bs,0),sp(bs,1),3)*dg
 19440 bend
 19450 gosub17900
 19460 return
 19470 rem "- Nog eens gooien -
 19480 gosub17790
 19490 print"{yel}{down}U mag nog eens gooien."
 19500 ifai=0thenne=1
 19510 gosub17900
 19520 return
 19530 rem "- Betalen of arbeidsbureau -
 19540 gosub17790
 19550 print"{yel}{down}Betaal Fl.{cyn}";
 19560 printca(sp(bs,0),sp(bs,1),3)"{yel} of ga naar arbeidsbureau."
 19570 ifai=0andsp(bs,3)>=ca(sp(bs,0),sp(bs,1),3)thenbegin
 19580 : ifsp(bs,6)=1thenm=1:elsebegin
 19590 :   window32,16,79,24:print"{yel}Betaalt U ?"
 19600 :   xc=69:yc=17:mn=5:gosub25300
 19610 : bend
 19620 : ifm=1thensp(bs,3)=sp(bs,3)-ca(sp(bs,0),sp(bs,1),3)
 19630 : window32,16,79,24:print"            "
 19640 bend
 19650 gosub17900
 19660 ifm=2thengosub18840
 19670 return
 19680 rem "- Alle geld weg -
 19690 gosub17790
 19700 print"{yel}{down}U verliest al Uw geld."
 19710 ifai=0thensp(bs,3)=0
 19720 gosub17900
 19730 return
 19740 rem "- Verlies alle sterren -
 19750 gosub17790
 19760 print"{yel}{down}U verliest al Uw beroemdheid (*)."
 19770 ifai=0thensp(bs,5)=0
 19780 gosub17900
 19790 return
 19800 rem "- Ontvang sterren, maar ziekenhuis -
 19810 gosub17790
 19820 print"{yel}{down}U ontvangt";
 19830 printca(sp(bs,0),sp(bs,1),3)"* ,"
 19840 print"maar U moet wel naar het ziekenhuis."
 19850 ifai=0thensp(bs,5)=sp(bs,5)+ca(sp(bs,0),sp(bs,1),3)
 19860 gosub17900
 19870 ifai=0thengosub19030
 19880 return
 19890 :
 19900 rem "--- Reset spelstand ---
 19910 :
 19920 restore27880
 19930 forn=1to15:readka(n):nextn
 19940 forn=0to3
 19950 : sp(n,0)=0:sp(n,1)=1:sp(n,2)=20000:sp(n,3)=20000:sp(n,4)=0
 19960 : sp(n,5)=0:sp(n,7)=0:sp$(n,1)="00000000000"
 19970 nextn
 19980 ai=0:es=0:ne=0:bs=0
 19990 return
 20000 :
 20010 rem "--- Andere pion ? ---
 20020 :
 20030 sn=0
 20040 forn=0to3
 20050 : ifsp(bs,0)=sp(n,0)andsp(bs,1)=sp(n,1)andn<>bsthensn=n
 20060 nextn
 20070 ifsn<>0thengosub20120
 20080 return
 20090 :
 20100 rem "--- Pion zetten ---
 20110 :
 20120 ifsp(sn,0)=0orsp(sn,1)=0thenbegin
 20130 : h1=-1:ifsp(sn,1)=0thenh1=sp(sn,1):sp(sn,1)=cb(sp(sn,0))
 20140 : color5,vk(sp(sn,1),0)
 20150 : windowcv(sp(sn,1),0),cv(sp(sn,1),1),79,24:print"{rvon}"right$(str$(sn+1),1)"{rvof}"
 20160 : ifh1=0thensp(sn,1)=h1
 20170 bend:elsebegin
 20180 : color5,ca(sp(sn,0),sp(sn,1),0)
 20190 : windowcc(sp(sn,0),sp(sn,1),0),cc(sp(sn,0),sp(sn,1),1),79,24:print"{rvon}"chr$(176+sn)"{rvof}"
 20200 bend
 20210 return
 20220 :
 20230 rem "--- Pion wissen ---
 20240 :
 20250 sh=sn
 20260 gosub20010
 20270 ifsn=0thenbegin
 20280 : ifsp(sh,0)=0orsp(sh,1)=0thenbegin
 20290 :   h1=-1:ifsp(sh,1)=0thenh1=sp(sh,1):sp(sh,1)=cb(sp(sh,0))
 20300 :   color5,vk(sp(sh,1),0)
 20310 :   windowcv(sp(sh,1),0),cv(sp(sh,1),1),79,24:print"{rvon} {rvof}"
 20320 :   ifh1=0thensp(sh,1)=h1
 20330 : bend:elsebegin
 20340 :   color5,ca(sp(sh,0),sp(sh,1),0)
 20350 :   windowcc(sp(sh,0),sp(sh,1),0),cc(sp(sh,0),sp(sh,1),1),79,24:print"{rvon}{CBM-@}{rvof}"
 20360 : bend
 20370 bend
 20380 sn=sh
 20390 return
 20400 :
 20410 rem "--- Info veld ---
 20420 :
 20430 h1=sp(bs,0):h2=sp(bs,1)
 20440 xc=40:yc=8:b=35:h=5:gosub26270
 20450 window42,10,79,24:print"{yel}U wilt informatie over een veld."
 20460 print"{down}Hoeveel velden vooruit ?"
 20470 xc=67:yc=12:mg=12:gosub26530
 20480 gosub25260
 20490 ifh1=0thenbegin
 20500 : sp(bs,1)=sp(bs,1)+aw
 20510 : ifsp(bs,1)>32thensp(bs,1)=sp(bs,1)-32
 20520 bend:elsebegin
 20530 : sp(bs,1)=sp(bs,1)+aw
 20540 : ifsp(bs,1)>cc(h1,0,0)thensp(bs,1)=sp(bs,1)-cc(h1,0,0)+cc(h1,0,1)-1:sp(bs,0)=0:ifsp(bs,1)>32thensp(bs,1)=sp(bs,1)-32
 20550 bend
 20560 ai=1
 20570 gosub21050
 20580 ai=0
 20590 sp(bs,0)=h1:sp(bs,1)=h2
 20600 return
 20610 :
 20620 rem "--- Ontvang salaris ---
 20630 :
 20640 xc=40:yc=8:b=35:h=7:gosub26270
 20650 window42,10,79,24:print"{yel}U ontvangt Uw salaris."
 20660 print"{down}Fl. {cyn}";
 20670 printusing"#,###,###";sp(bs,2)
 20680 sp(bs,3)=sp(bs,3)+sp(bs,2)
 20690 print"{lgrn}{down}Toets."
 20700 gosub26490:gosub25260
 20710 return
 20720 :
 20730 rem "--- Einde carriere ---
 20740 :
 20750 ifsp(bs,0)<>2thenbegin
 20760 : xc=40:yc=8:b=35:h=7:gosub26270
 20770 : window42,10,79,24:print"{yel}U krijgt een ervaringskaart."
 20780 : ks=int(rnd(ti)*4)+1
 20790 : ks(bs,15+ks)=ks(bs,15+ks)+1
 20800 : print"{down}U kunt hiermee{cyn}"ks"{yel}vak(ken) vooruit."
 20810 : ifsp(bs,0)=1thenmid$(sp$(bs,1),5,1)="1":elsemid$(sp$(bs,1),sp(bs,0)+3,1)="1"
 20820 : print"{lgrn}{down}Toets.":gosub26490:gosub25260
 20830 bend:elsebegin
 20840 : xc=30:yc=5:b=45:h=12:gosub26270
 20850 : window32,7,79,24:print"{yel}Uw salaris wordt met Fl. {cyn}20.000{yel} verhoogd."
 20860 : print"{yel}{down}Ook kunt U kiezen uit deze titels :"
 20870 : print"{down}{lgrn} Rechten                {yel}(Handel,politiek)"
 20880 : print"{lgrn} Medicijnen             {yel}(Handel,ziekenhuis)"
 20890 : print"{lgrn} Wis- en natuurkunde    {yel}(Handel,Mars)"
 20900 : print"{lgrn} Werktuigkunde          {yel}(Handel,Uranium)"
 20910 : print"{yel}{down}Maak S.V.P. Uw keuze."
 20920 : ifsp(bs,6)=1thenm=3:mn=9:elsebegin
 20930 :   xc=32:yc=10:mn=9:gosub25300
 20940 :   mid$(sp$(bs,1),m,1)="1"
 20950 : bend
 20960 : window33,10+m,79,24:print"{cyn}"mn$(mn,m)
 20970 : sp(bs,2)=sp(bs,2)+20000
 20980 : window32,16,79,24:print"{lgrn}Toets.               ":gosub26490:gosub25260
 20990 : ks(bs,12)=0
 21000 bend
 21010 return
 21020 :
 21030 rem "--- Naar goede veld ---
 21040 :
 21050 ifsp(bs,0)=0thenbegin
 21060 : onvk(sp(bs,1),1)gosub12900,13010,13160,13300,13540,13870,14180,14350,14450,14680,14960,15200,15350,15470,15710,15940,16180,16320,16670,16910,17230,17470
 21070 bend:elsebegin
 21080 : gu=ca(sp(bs,0),sp(bs,1),2)
 21090 : ongugosub17840,17950,18080,18190,18260,18330,18400,18460,18530,18720,18810,18920,19000,19110,19190,19260,19350,19480,19540,19690,19750,19810
 21100 bend
 21110 return
 21120 :
 21130 rem "--- Ziekenhuis ---
 21140 :
 21150 am=0:bt=0
 21160 forn=0to3
 21170 : ifmid$(sp$(n,1),2,1)="1"thenam=am+1
 21180 nextn
 21190 ab=am:ifab=0thenab=1
 21200 xc=40:yc=8:b=35:h=9:gosub26270
 21210 window42,10,79,24:print"{yel}U bent nog in het {grn}ZIEKENHUIS{yel}."
 21220 ifsp(bs,3)<.5*sp(bs,2)*abthenbegin
 21230 : print"{down}Om weg te kunnen moet U 5 of"
 21240 : print"minder gooien."
 21250 bend:elsebegin
 21260 : print"{down}Betaald U Fl. {cyn}";
 21270 : printusing"#,###,###";.5*sp(bs,2)*ab
 21280 : print"{yel}om direct weg te gaan ?"
 21290 : xc=69:yc=14:mn=5:gosub25300
 21300 : ifm=1thenbt=1:sp(bs,3)=sp(bs,3)-.5*sp(bs,2)*ab
 21310 : ifam>0thenbegin
 21320 :   forn=0to3
 21330 :     ifmid$(sp$(n,1),2,1)="1"thensp(n,3)=sp(n,3)+.5*sp(bs,2)
 21340 :   nextn
 21350 : bend
 21360 : window42,12,74,13,1:window0,0,79,24
 21370 bend
 21380 print"{home}{home}":window42,15,79,24:print"{lgrn}Toets.":gosub26490:gosub25260
 21390 return
 21400 :
 21410 rem "--- Arbeidbureau ---
 21420 :
 21430 bt=0:xc=40:yc=8:b=35:h=9:gosub26270
 21440 window42,10,79,24:print"{yel}U bent in het {grn}ARBEIDSBUREAU{yel}."
 21450 ifsp(bs,3)<sp(bs,2)*.5thenbegin
 21460 : print"{down}Om weg te kunnen moet U 7, 11 of"
 21470 : print"dubbel gooien."
 21480 bend:elsebegin
 21490 : print"{down}Betaald U Fl. {cyn}";
 21500 : printusing"#,###,###";.5*sp(bs,2)
 21510 : print"{yel}om direct weg te gaan ?"
 21520 : xc=69:yc=14:mn=5:gosub25300
 21530 : ifm=1thenbt=1:sp(bs,3)=sp(bs,3)-.5*sp(bs,2)
 21540 : window42,12,74,13,1:window0,0,79,24
 21550 bend
 21560 print"{home}{home}":window42,15,79,24:print"{lgrn}Toets.":gosub26490:gosub25260
 21570 return
 21580 :
 21590 rem "--- Riviera ---
 21600 :
 21610 xc=40:yc=8:b=35:h=9:gosub26270
 21620 window42,10,79,24:print"{yel}U bent in de {grn}RIVIERA{yel}."
 21630 print"{down}Wilt U voor {lred}2 {CBM-+}{yel} nog een beurt"
 21640 print"vakantie vieren ?"
 21650 xc=69:yc=14:mn=5:gosub25300
 21660 ifm=1thensp(bs,4)=sp(bs,4)+2:es=10
 21670 gosub25260
 21680 return
 21690 :
 21700 rem "--- Gebruik ervaringskaart ---
 21710 :
 21720 xc=40:yc=8:b=35:h=9:gosub26270
 21730 window42,10,79,24:print"{lgrn}Ervaringskaart gebruiken"
 21740 print"{lred}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}"
 21750 print"{yel}Hoeveel vakken wilt U vooruit ?"
 21760 do
 21770 : xc=74:yc=12:mg=4:gosub26530
 21780 loopwhileaw<>0andks(bs,15+aw)=0
 21790 ifaw=0thenes=0:elsedg=aw:ks(bs,15+aw)=ks(bs,15+aw)-1
 21800 gosub25260
 21810 return
 21820 :
 21830 rem "--- Kanskaarten gebruiken ---
 21840 :
 21850 ka=0:forn=1to15
 21860 : ifks(bs,n)>0thenka=ka+1
 21870 nextn
 21880 h=ka+5:xc=40:yc=12-int(h/2):b=35:gosub26270
 21890 window42,yc+2,79,24:print"{yel}Welke kanskaart wilt U gebruiken ?"
 21900 ml=0:tl=0:forn=1to15
 21910 : ifks(bs,n)>0thentl=tl+1:mn$(10,tl)=kk$(n,0)+" "+kk$(n,1):iflen(mn$(10,tl))>mlthenml=len(mn$(10,tl))
 21920 nextn
 21930 mn(10)=ka+1
 21940 mn$(10,ka+1)="Geen een"
 21950 forn=1toka+1
 21960 : iflen(mn$(10,n))<mlthenmn$(10,n)=mn$(10,n)+left$(s$,ml-len(mn$(10,n)))
 21970 nextn
 21980 y=yc:xc=42:yc=y+3:mn=10:gosub25300:gosub25260
 21990 ifm=ka+1thenes=0:elsebegin
 22000 : kn=0
 22010 : forn=1to15
 22020 :   ifks(bs,n)>0thenkn=kn+1
 22030 :   ifkn=mthenkn=n:n=15
 22040 : nextn
 22050 : kb=kb(kn,0):kv=kb(kn,1)
 22060 : ifkb=-1thenbegin
 22070 :   xc=40:yc=8:b=35:h=13:gosub26270
 22080 :   window42,10,79,24:print"{yel}Welke carri{CBM-*}re kiest U ?"
 22090 :   ml=0
 22100 :   forn=1to8
 22110 :     mn$(11,n)=ca$(n,0)
 22120 :     iflen(mn$(11,n))>mlthenml=len(mn$(11,n))
 22130 :   nextn
 22140 :   mn(11)=8
 22150 :   forn=1to8
 22160 :     iflen(mn$(11,n))<mlthenmn$(11,n)=mn$(11,n)+left$(s$,ml-len(mn$(11,n)))
 22170 :   nextn
 22180 :   xc=42:yc=11:mn=11:gosub25300:gosub25260
 22190 :   kb=cb(m):kv=m
 22200 : bend
 22210 : gosub20250:ks(bs,kn)=ks(bs,kn)-1:ka(kn)=ka(kn)+1
 22220 : sp(bs,0)=0:sp(bs,1)=kb
 22230 : ifkv<>0andkk$(kn,1)="Gratis"thenbegin
 22240 :   ifkv=1thenmid$(sp$(bs,1),5,1)="1":elsemid$(sp$(bs,1),kv+3)="1"
 22250 : bend
 22260 bend
 22270 return
 22280 :
 22290 rem "--- Iemand gewonnen ? ---
 22300 :
 22310 gw=-1
 22320 forn=0to3
 22330 : ifsp(n,3)>=200000andsp(n,4)>=20andsp(n,5)>=20thengw=n:n=3
 22340 nextn
 22350 ifgw<>-1thenbegin
 22360 : xc=30:yc=8:h=8:b=45:gosub26270
 22370 : window32,10,79,24:print"{lgrn}"sp$(gw,0)"{yel} heeft gewonnen !"
 22380 : print"{down}Nog een spel ?"
 22390 : xc=69:yc=13:mn=5:gosub25300
 22400 : ifm=1thenes=6:elsees=5
 22410 : gosub25260
 22420 bend
 22430 return
 22440 :
 22450 rem "--- Saven spel ---
 22460 :
 22470 xc=40:yc=8:b=35:h=6:gosub26270
 22480 window42,10,79,24:print"{lgrn}Saven spel"
 22490 print"{lred}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}"
 22500 print"{yel}Bestandsnaam :"
 22510 xc=57:yc=12:ml=12:tt$=al$:gosub25910
 22520 gosub25260
 22530 ifan$=""thenreturn:elsean$=an$+left$(s$,12-len(an$))+".car"
 22540 dopen#1,(an$),w
 22550 dclose#1
 22560 aw$=ds$
 22570 ifds<>0andds<>63thengosub24770:return
 22580 ifds=63thenbegin
 22590 : xc=40:yc=8:b=35:h=8:gosub26270
 22600 : window42,10,79,24:print"{yel}Bestand bestaat al."
 22610 : print"{down}Wilt U dit bestand vervangen ?"
 22620 : xc=69:yc=13:mn=5:gosub25300
 22630 : ifm=2thengosub25260:return
 22640 : gosub25260
 22650 bend
 22660 scratch(an$)
 22670 dopen#1,(an$),w
 22680 : print#1,bs
 22690 : print#1,ne
 22700 : forn=1to15
 22710 :   print#1,ka(n)
 22720 : nextn
 22730 : forn=0to3
 22740 :   form=0to7
 22750 :     print#1,sp(n,m)
 22760 :   nextm
 22770 : nextn
 22780 : forn=0to3
 22790 :   form=0to1
 22800 :     print#1,sp$(n,m)
 22810 :   nextm
 22820 : nextn
 22830 : forn=0to3
 22840 :   form=1to19
 22850 :     print#1,ks(n,m)
 22860 :   nextm
 22870 : nextn
 22880 dclose#1
 22890 gosub24770
 22900 return
 22910 :
 22920 rem "--- Laden spel ---
 22930 :
 22940 xc=40:yc=8:b=35:h=8:gosub26270
 22950 window42,10,79,24:print"{lgrn}Laden spel"
 22960 print"{lred}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}"
 22970 print"{yel}Wilt U de directory zien ?"
 22980 xc=69:yc=13:mn=5:gosub25300
 22990 window42,12,74,16,1:window0,0,79,24
 23000 ifm=1thenbegin
 23010 : xc=40:yc=5:b=35:h=16:gosub26270:window42,7,74,18
 23020 : color5,4:catalog"????????????.car
 23030 : window42,20,79,24:print"{lgrn}Toets.":gosub26490:gosub25260
 23040 bend
 23050 print"{home}{home}":window42,12,79,24:print"{yel}Bestandsnaam (zonder .car) :"
 23060 xc=42:yc=13:ml=12:tt$=al$:gosub25910
 23070 gosub25260
 23080 ifan$=""thenes=0:return:elsean$=an$+left$(s$,12-len(an$))+".car"
 23090 dopen#1,(an$)
 23100 dclose#1
 23110 aw$=ds$
 23120 ifds<>0thengosub24770:return
 23130 dopen#1,(an$)
 23140 : input#1,bs
 23150 : input#1,ne
 23160 : forn=1to15
 23170 :   input#1,ka(n)
 23180 : nextn
 23190 : forn=0to3
 23200 :   form=0to7
 23210 :     input#1,sp(n,m)
 23220 :   nextm
 23230 : nextn
 23240 : forn=0to3
 23250 :   form=0to1
 23260 :     input#1,sp$(n,m)
 23270 :   nextm
 23280 : nextn
 23290 : forn=0to3
 23300 :   form=1to19
 23310 :     input#1,ks(n,m)
 23320 :   nextm
 23330 : nextn
 23340 dclose#1
 23350 gosub24770
 23360 return
 23370 :
 23380 rem "--- Denken Computer ---
 23390 :
 23400 bt=0
 23410 window45,8,79,24:print"{yel}De computer speelt nu."
 23420 ifsp(bs,7)>0thenreturn
 23430 ifsp(bs,0)=0andsp(bs,1)=9thenbegin
 23440 : am=0
 23450 : forn=0to3
 23460 :   ifmid$(sp$(n,1),2,1)="1"thenam=am+1
 23470 : nextn
 23480 : ab=am:ifab=0thenab=1
 23490 : ifab*.5*sp(bs,2)<=.8*sp(bs,3)thenbegin
 23500 :   xc=40:yc=8:b=35:h=7:gosub26270:bt=1
 23510 :   window42,10,79,24:print"{yel}De computer betaald Fl. {cyn}";
 23520 :   printusing"#,###,###";.5*sp(bs,2)*ab
 23530 :   sp(bs,3)=sp(bs,3)-ab*.5*sp(bs,2)
 23540 :   print"{yel}om weg te mogen.":print"{down}{lgrn}Toets."
 23550 :   forn=0to3
 23560 :     ifmid$(sp$(n,1),2,1)="1"thensp(n,3)=sp(n,3)+.5*sp(bs,2)
 23570 :   nextn
 23580 :   gosub26490:gosub25260
 23590 : bend:elsereturn
 23600 bend
 23610 ifsp(bs,0)=0andsp(bs,1)=17thenbegin
 23620 : if.5*sp(bs,2)<=.9*sp(bs,3)thenbegin
 23630 :   xc=40:yc=8:b=35:h=7:gosub26270:bt=1
 23640 :   window42,10,79,24:print"{yel}De computer betaald Fl. {cyn}";
 23650 :   printusing"#,###,###";.5*sp(bs,2)
 23660 :   print"{yel}om weg te kunnen.":print"{down}{lgrn}Toets."
 23670 :   sp(bs,3)=sp(bs,3)-.5*sp(bs,2)
 23680 :   gosub26490:gosub25260
 23690 : bend:elsereturn
 23700 bend
 23710 ifes=10thenreturn
 23720 forn=1to19:wc(n)=0:nextn
 23730 forn=1to4
 23740 : ifks(bs,15+n)>0thenbegin
 23750 :   ifsp(bs,0)=0andsp(bs,1)+n=33thenwc(15+n)=1000
 23760 :   ifsp(bs,0)<>0thenbegin
 23770 :     cd=sp(bs,1)+n
 23780 :     ifcd<=cc(sp(bs,0),0,0)thenbegin
 23790 :       ifca(sp(bs,0),cd,2)=1andsp(bs,4)<20thenwc(15+n)=1000
 23800 :       ifca(sp(bs,0),cd,2)=3thenwc(15+n)=1500
 23810 :       ifca(sp(bs,0),cd,2)=4and(sp(bs,4)<20orsp(bs,5)<20)thenwc(15+n)=2000
 23820 :       ifca(sp(bs,0),cd,2)=5thenwc(15+n)=2100
 23830 :       ifca(sp(bs,0),cd,2)=8thenwc(15+n)=1600
 23840 :       ifca(sp(bs,0),cd,2)=10thenwc(15+n)=500
 23850 :       ifca(sp(bs,0),cd,2)=14thenwc(15+n)=2200
 23860 :       ifca(sp(bs,0),cd,2)=17thenwc(15+n)=600
 23870 :     bend
 23880 :   bend
 23890 : bend
 23900 nextn
 23910 cd=0:mw=0
 23920 forn=1to4
 23930 : ifwc(15+n)>mwthenmw=wc(15+n):cd=n
 23940 nextn
 23950 ifcd>0thenbegin
 23960 : es=9:dg=cd:ks(bs,15+cd)=ks(bs,15+cd)-1
 23970 : xc=35:yc=8:b=40:h=7:gosub26270
 23980 : window37,10,79,24:print"{yel}De computer gebruikt een ervaringskaart"
 23990 : print"van{cyn}"cd"{yel}vak(ken)."
 24000 : print"{down}{lgrn}Toets."
 24010 : gosub26490:gosub25260:return
 24020 bend
 24030 ifsp(bs,0)>0thenreturn
 24040 forn=1to15
 24050 : ifks(bs,n)>0thenbegin
 24060 :   wc(n)=500:c=kb(n,1)
 24070 :   ifsp(bs,4)<20and(c=1orc=2orc=4orc=7)thenwc(n)=wc(n)+1000
 24080 :   ifsp(bs,5)<20and(c=5orc=6orc=8)thenwc(n)=wc(n)+1100
 24090 :   ifsp(bs,3)<200000and(c=3orc=7orc=8)thenwc(n)=wc(n)+500
 24100 :   cd=0
 24110 :   ifn=1and(mid$(sp$(bs,1),3,1)="1"ormid$(sp$(bs,1),11,1)="1")thencd=1
 24120 :   ifn=2andmid$(sp$(bs,1),7,1)="1"thencd=1
 24130 :   ifn=3and(mid$(sp$(bs,1),4,1)="1"ormid$(sp$(bs,1),10,1)="1")thencd=1
 24140 :   ifn=4and(instr(left$(sp$(bs,1),4),"1")<>0ormid$(sp$(bs,1),6,1)="1")thencd=1
 24150 :   ifn=5andmid$(sp$(bs,1),9,1)="1"thencd=1
 24160 :   ifn=7thenifsp(bs,3)>=40000thenwc(7)=10000:elsewc(7)=0
 24170 :   ifn=8andmid$(sp$(bs,1),5,1)="1"thencd=1
 24180 :   ifn=9and(mid$(sp$(bs,1),1,1)="1"ormid$(sp$(bs,1),8,1)="1")thencd=1
 24190 :   ifn=10orn=11orn>12thencd=1
 24200 :   ifcd=0thenbegin
 24210 :     if(c=1orc=6)andsp(bs,3)<10000thenwc(n)=0
 24220 :     if(c=2orc=3)andsp(bs,3)<5000thenwc(n)=0
 24230 :     ifc=4andsp(bs,3)<1000thenwc(n)=0
 24240 :     ifc=5andsp(bs,3)<30000thenwc(n)=0
 24250 :     ifc=7andsp(bs,3)<40000thenwc(n)=0
 24260 :     ifc=8andsp(bs,3)<50000thenwc(n)=0
 24270 :   bend:elsewc(n)=wc(n)+1000
 24280 : bend
 24290 nextn
 24300 cd=0:mw=0
 24310 forn=1to15
 24320 : ifwc(n)>mwthenmw=wc(n):cd=n
 24330 nextn
 24340 ifcd<>0thenbegin
 24350 : es=8:kb=kb(cd,1):kc=kb(cd,0)
 24360 : ifkk$(cd,1)="Gratis"thenbegin
 24370 :   ifkb=1thenmid$(sp$(bs,1),5,1)="1":elsemid$(sp$(bs,1),3+kb,1)="1"
 24380 : bend
 24390 : ifcd=7thenbegin
 24400 :   ifsp(bs,3)>=50000thenkb=8:kc=31:elsekb=7:kc=28
 24410 : bend
 24420 : ks(bs,cd)=ks(bs,cd)-1:gosub20250:ka(cd)=ka(cd)+1
 24430 : sp(bs,0)=0:sp(bs,1)=kc
 24440 : xc=35:yc=8:b=40:h=7:gosub26270
 24450 : window37,10,79,24:print"{yel}De computer gebruikt een kanskaart."
 24460 : print"{cyn}{down}"kk$(cd,0)" "kk$(cd,1)
 24470 : print"{lgrn}{down}Toets."
 24480 : gosub26490:gosub25260
 24490 bend
 24500 return
 24510 :
 24520 rem "--- Riviera computer ---
 24530 :
 24540 ifsp(bs,4)<=20thensp(bs,4)=sp(bs,4)+2:es=10
 24550 return
 24560 :
 24570 rem "--- Selecteer kanskaart ---
 24580 :
 24590 ka=0
 24600 forkk=1to15
 24610 : ka=ka+ka(kk)
 24620 nextkk
 24630 ifka=0thenkg=-1:return
 24640 do
 24650 : kg=int(rnd(ti)*ka)+1:kn=1
 24660 : forkk=1to15
 24670 :   forka=1toka(kk)
 24680 :     ifkn=kgthenkg=kk:ka=ka(kk):kk=15:elsekn=kn+1
 24690 :   nextka
 24700 : nextkk
 24710 loopwhilekg=12andinstr(left$(sp$(bs,1),4),"1")<>0andka<>1
 24720 ifkg=12andinstr(left$(sp$(bs,1),4),"1")<>0thenkg=-1:return
 24730 ka(kg)=ka(kg)-1
 24740 return
 24750 :
 24760 rem "--- Discfout ---
 24770 xc=5:yc=8:b=70:h=5:gosub26270
 24780 window7,10,79,24:print"{cyn}"ds$
 24790 print"{lgrn}{down}Toets.":gosub26490:gosub25260:return
 24800 :
 24810 rem "--- Lezen menudata ---
 24820 :
 24830 restore27920
 24840 readmn,dn
 24850 dimmn$(mn+dn+2,16),mn(mn+dn+2),mc(mn,1)
 24860 mc=1:mn(0)=mn
 24870 forn=1tomn(0)
 24880 : readmn$(n,0)
 24890 : readmn(n)
 24900 : mc(n,0)=mc:mc(n,1)=mc+len(mn$(n,0)):mc=mc(n,1)+1:ml=0
 24910 : form=1tomn(n)
 24920 :   readmn$(n,m)
 24930 :   iflen(mn$(n,m))>mlthenml=len(mn$(n,m))
 24940 : nextm
 24950 : form=1tomn(n)
 24960 :   mn$(n,m)=mn$(n,m)+left$(s$,ml-len(mn$(n,m)))
 24970 : nextm
 24980 nextn
 24990 forn=1todn
 25000 : readmn(mn(0)+n):ml=0
 25010 : form=1tomn(mn(0)+n)
 25020 :   readmn$(mn(0)+n,m)
 25030 :   iflen(mn$(mn(0)+n,m))>mlthenml=len(mn$(mn(0)+n,m))
 25040 : nextm
 25050 : form=1tomn(mn(0)+n)
 25060 :   mn$(mn(0)+n,m)=mn$(mn(0)+n,m)+left$(s$,ml-len(mn$(mn(0)+n,m)))
 25070 : nextm
 25080 nextn
 25090 return
 25100 :
 25110 rem "--- Menuregel ---
 25120 :
 25130 color5,6:window0,1,79,24:print"{rvon} ";
 25140 forn=1tomn(0)
 25150 : print"{rvon}"mn$(n,0)" {rvof}";
 25160 nextn
 25170 print"{rvon}"left$(s$,79-mc(mn(0),1))
 25180 return
 25190 :
 25200 rem "--- Beeld opslaan ---
 25210 :
 25220 sysdec("0b33"),0,ad:ad=ad+16:print"{home}{home}":return
 25230 :
 25240 rem "--- Beeld terughalen ---
 25250 :
 25260 ad=ad-16:sysdec("0c6a"),16,ad:sysdec("0b7a"),16,0:print"{home}{home}":return
 25270 :
 25280 rem "--- Menu ---
 25290 :
 25300 gosub25220
 25310 ifmn>mn(0)thenwindowxc,yc,79,24:print"{lred}{SHIFT-POUND}"left$(b$,2+len(mn$(mn,1)))"{CBM-Q}"
 25320 forn=1tomn(mn)
 25330 : windowxc,yc+n,79,24:print"{lred}{CBM-N}{rvon}{cyn} "mn$(mn,n)" {rvof}{lred}{CBM-H}"
 25340 nextn
 25350 windowxc,yc+n,79,24:print"{lred}{CBM-Z}"left$(o$,2+len(mn$(mn,1)))"{CBM-S}"
 25360 m=1:tt$="{up}{down}"+chr$(13):tj$="11011101"
 25370 ifmn<=mn(0)thentt$=tt$+"{left}{rght}":tj$="11111111"
 25380 do
 25390 : windowxc+1,yc+m,79,24:print"{rvon}{yel} "mn$(mn,m)" {rvof}"
 25400 : jm=1:gosub25550:jm=0
 25410 : ifaw$=chr$(13)orjw>=128thenexit
 25420 : ifaw$="{left}"orjw=7thenm=0:poke208,1:poke842,asc("{left}"):exit
 25430 : ifaw$="{rght}"orjw=3thenm=0:poke208,1:poke842,asc("{rght}"):exit
 25440 : windowxc+1,yc+m,79,24:print"{rvon}{cyn} "mn$(mn,m)" {rvof}"
 25450 : ifaw$="{up}"orjw=1orjw=2orjw=8thenm=m-1
 25460 : ifaw$="{down}"orjw=4orjw=5orjw=6thenm=m+1
 25470 : ifm>mn(mn)thenm=1
 25480 : ifm<1thenm=mn(mn)
 25490 loop
 25500 gosub25260
 25510 return
 25520 :
 25530 rem "--- Vraag toets ---
 25540 :
 25550 do
 25560 : getaw$
 25570 : ifjm=1thenbegin
 25580 :   jw=joy(2)
 25590 :   ifjw<>0thenbegin
 25600 :     ifjw<128thenifmid$(tj$,jw,1)="1"thenexit
 25610 :     ifjw>=128thenexit
 25620 :   bend
 25630 : bend
 25640 loopwhileinstr(tt$,aw$)=0
 25650 return
 25660 :
 25670 rem "--- Hoofdmenu ---
 25680 :
 25690 mn=1:m=0
 25700 do
 25710 : do
 25720 :   windowmc(mn,0),1,79,24:print"{rvon}{wht}"mn$(mn,0)"{rvof}"
 25730 :   tt$="{left}{rght}"+chr$(13):tj$="01110111"
 25740 :   jm=1:gosub25550:jm=0
 25750 :   ifaw$=chr$(13)orjw>=128thenexit
 25760 :   windowmc(mn,0),1,79,24:print"{rvon}{grn}"mn$(mn,0)"{rvof}"
 25770 :   ifaw$="{left}"orjw=6orjw=7orjw=8thenmn=mn-1
 25780 :   ifaw$="{rght}"orjw=2orjw=3orjw=4thenmn=mn+1
 25790 :   ifmn<1thenmn=mn(0)
 25800 :   ifmn>mn(0)thenmn=1
 25810 : loop
 25820 : xc=mc(mn,0)-1:yc=1
 25830 : ifxc+len(mn$(mn,1))>79thenxc=mc(mn,1)-len(mn$(mn,1))
 25840 : gosub25300
 25850 loopuntilm
 25860 windowmc(mn,0),1,79,24:print"{rvon}{grn}"mn$(mn,0)"{rvof}"
 25870 return
 25880 :
 25890 rem "--- Input ---
 25900 :
 25910 an$="":kn=1
 25920 tt$=tt$+chr$(13)+chr$(20)+chr$(148)+"{left}{rght}"
 25930 do
 25940 : ifkn<=len(an$)thenbegin
 25950 :   windowxc,yc,79,24:print"{cyn}"left$(an$,kn-1)"{rvon}"mid$(an$,kn,1)"{rvof}"right$(an$,len(an$)-kn)"{grn}"left$(b$,ml-len(an$))
 25960 : bend:elsebegin
 25970 :   windowxc,yc,79,24:print"{cyn}"an$"{rvon} {rvof}{grn}"left$(b$,ml-len(an$)-1)
 25980 : bend
 25990 : gosub25550
 26000 : ifaw$=chr$(13)thenexit
 26010 : ifinstr(chr$(20)+chr$(148)+"{left}{rght}",aw$)=0thenbegin
 26020 :   ifkn<=len(an$)thenbegin
 26030 :     an$=left$(an$,kn-1)+aw$+right$(an$,len(an$)-kn)
 26040 :   bend:elsebegin
 26050 :     an$=an$+aw$
 26060 :   bend
 26070 :   kn=kn+1
 26080 : bend:elsebegin
 26090 :   ifaw$=chr$(20)andlen(an$)>0andkn<=len(an$)thenbegin
 26100 :     an$=left$(an$,kn-2)+right$(an$,len(an$)-kn+1):kn=kn-1
 26110 :   bend
 26120 :   ifaw$=chr$(20)andlen(an$)>0andkn>len(an$)thenbegin
 26130 :     an$=left$(an$,len(an$)-1):kn=kn-1
 26140 :   bend
 26150 :   ifaw$="{left}"andkn>1thenkn=kn-1
 26160 :   ifaw$="{rght}"andkn<len(an$)+1thenkn=kn+1
 26170 :   ifaw$=chr$(148)andkn<=len(an$)andlen(an$)<mlthenbegin
 26180 :     an$=left$(an$,kn-1)+" "+right$(an$,len(an$)-kn+1)
 26190 :   bend
 26200 : bend
 26210 loopuntil(len(an$)=mlandkn=len(an$)+1)
 26220 windowxc,yc,79,24:print"{cyn}"an$left$(s$,ml-len(an$))
 26230 return
 26240 :
 26250 rem "--- Maak kader ---
 26260 :
 26270 color5,11:gosub25220
 26280 windowxc,yc,79,24:print"{SHIFT-POUND}"left$(b$,b)"{CBM-Q}"
 26290 forn=1toh
 26300 : windowxc,yc+n,79,24:print"{CBM-N}"left$(s$,b)"{CBM-H}"
 26310 nextn
 26320 windowxc,yc+h+1,79,24:print"{CBM-Z}"left$(o$,b)"{CBM-S}{yel}";
 26330 return
 26340 :
 26350 rem "--- Foutenonderscheproutine ---
 26360 :
 26370 xc=4:yc=8:b=68:h=9:gosub26270
 26380 window6,10,79,24:print"{cyn}"err$(er)"{yel} error in regel{cyn}"el
 26390 print"{yel}{down}Wat wilt U ?"
 26400 xc=61:yc=14:mn=6:gosub25300
 26410 gosub25260
 26420 ifm=1thenrun
 26430 window0,2,79,24,1:window0,0,79,24
 26440 print"{yel}{down}{down}{down}{down}{down}Tot ziens."
 26450 poke208,0:end
 26460 :
 26470 rem "--- Toets of knop joy ---
 26480 :
 26490 poke208,0:tt$=al$:tj$="00000000":jm=1:gosub25550:jm=0:return
 26500 :
 26510 rem "--- Getalinput ---
 26520 :
 26530 aw=0
 26540 do
 26550 : windowxc,yc,79,24:print"{lgrn}"right$(str$(aw),len(str$(aw))-1)" "
 26560 : tt$="{left}{rght}"+chr$(13):tj$="11101110"
 26570 : jm=1:gosub25550:jm=0
 26580 : ifaw$=chr$(13)orjw>=128thenexit
 26590 : if(aw$="{rght}"orjw=1orjw=2orjw=3)thenaw=aw+1
 26600 : if(aw$="{left}"orjw=5orjw=6orjw=7)thenaw=aw-1
 26610 : ifaw<0thenaw=mg
 26620 : ifaw>mgthenaw=0
 26630 loop
 26640 windowxc,yc,79,24:print"{rvof}{cyn}"right$(str$(aw),len(str$(aw))-1)" "
 26650 return
 26660 :
 26670 rem "--- Data voor spel ---
 26680 :
 26690 data33,21,29,21,25,21,21,21,17,21,13,21,9,21,5,21,1,21
 26700 data1,19,1,17,1,15,1,13,1,11,1,9,1,7,1,5
 26710 data5,5,9,5,13,5,17,5,21,5,25,5,29,5,33,5
 26720 data33,7,33,9,33,11,33,13,33,15,33,17,33,19
 26730 data16,20,16,19,16,18,16,17,14,17,12,17,12,18,12,19,12,20,6,-1
 26740 data6,20,6,19,8,19,8,18,8,17,6,17,4,17,11,-1
 26750 data4,15,6,15,8,15,10,15,10,14,10,13,10,12,8,12,6,12,6,13,4,13,13,-1
 26760 data4,10,6,10,8,10,10,10,10,9,10,8,8,8,6,8,6,7,18,-1
 26770 data14,7,14,8,14,9,14,10,16,10,18,10,20,10,20,9,20,8,18,8,18,7,21,-1
 26780 data24,7,24,8,24,9,24,10,26,10,28,10,28,9,28,8,30,8,26,-1
 26790 data30,12,28,12,26,12,24,12,24,13,24,14,24,15,26,15,28,15,28,14,30,14,29,-1
 26800 data30,17,28,17,26,17,24,17,22,17,20,17,20,18,20,19,22,19,24,19,26,19,28,19,28,20,2,-1
 26810 data6,1,10,2,5,3,10,2,2,4,10,2,5,5,2,6,6,7,10,2,5,8,2,9,10,2,5,10,2,11
 26820 data10,2,6,12,10,2,5,13,2,14,10,2,5,15,2,16,10,2,6,17,10,2,5,18,2,19
 26830 data10,2,5,20,2,21,5,22
 26840 data11,11,"Prachtig voorjaar.",1,2,0
 26850 data11,11,"Je vindt eerste kievitsei.",1,2,0
 26860 data2,2,"Help met dorsen.",2,1,0
 26870 data14,14,"Je speculeert in graan.",3,10000,0
 26880 data8,11,"Fok stamboekvee.",4,2,4
 26890 data11,11,"Merrie krijgt 2 veulens.",1,6,0
 26900 data14,14,"Een zeer goede oogst.",5,50000,0
 26910 data11,11,"Prachtige herfstkleuren.",1,2,0
 26920 data2,2,"Hagelstorm.",6,0,0
 26930 data11,11,"Je wordt verliefd.",1,4,0
 26940 data2,2,"Je zakt voor examen.",7,0,0
 26950 data11,11,"Gekozen tot voorzitter van het corps.",1,2,0
 26960 data11,11,"Aanvoerder van het eerste team.",1,2,0
 26970 data2,2,"Je krijgt studiebeurs.",9,2,0
 26980 data8,8,"Uitgekozen voor Olympische spelen.",8,6,0
 26990 data2,2,"Je slaagt cum laude.",9,2,0
 27000 data2,2,"Zakenopleiding.",2,1,0
 27010 data2,2,"Lunch met directeur.",9,1,0
 27020 data14,14,"Chef vindt je geschikt.",10,10000,0
 27030 data2,2,"Verschil van mening met directeur.",7,0,0
 27040 data14,14,"Je bedenkt nieuw produktieplan.",5,20000,0
 27050 data14,14,"Je wordt benoemd tot onderdirecteur.",10,20000,0
 27060 data2,2,"Je boekt prachtorder.",2,1,0
 27070 data11,11,"Knappe secretaresse.",1,4,0
 27080 data2,2,"Je wordt ontslagen.",11,0,0
 27090 data2,2,"Beurscrisis.",12,0,0
 27100 data14,14,"Gekozen in Raad van commissarissen.",10,30000,0
 27110 data2,2,"Je bent zeeziek",13,0,0
 27120 data11,11,"Prachtig uitzicht op Buenos Aires.",1,2,0
 27130 data2,2,"Je ontmoet ontdekkingsreiziger.",9,2,0
 27140 data2,2,"Zwaar stormweer.",2,1,0
 27150 data14,14,"Je vindt verborgen schat.",3,10000,0
 27160 data11,11,"Je landt op Tahiti.",1,4,0
 27170 data11,11,"Avondje uit op Broadway.",1,6,0
 27180 data2,2,"Ga strandjutten.",7,0,0
 27190 data11,11,"Romantisch avontuur op Hawaii.",1,8,0
 27200 data2,2,"Je wordt van kandidatenlijst geschrapt.",11,0,0
 27210 data2,2,"Lunch met buitenlandse president.",9,2,0
 27220 data8,8,"Bevorder wegenbouw.",8,4,0
 27230 data11,11,"Open tentoonstelling beeldende kunst.",1,2,0
 27240 data2,2,"Ontwerp verkiezingscampa>ne.",2,2,0
 27250 data8,8,"Opzienbarende verkiezingstoespraak.",8,6,0
 27260 data8,11,"Leid officiele buitenlandse missie.",4,2,4
 27270 data8,8,"Ministriele benoeming.",8,8,0
 27280 data8,14,"Je schrijft boek op politiek gebied.",14,4,50000
 27290 data2,2,"Politiek schandaaltje.",15,0,0
 27300 data8,8,"Winst door politieke verschuiving.",8,12,0
 27310 data8,8,"Begin als foto-model.",8,2,0
 27320 data2,2,"Afspraakje met filmster.",2,1,0
 27330 data2,2,"Je staat in de gunst bij regisseur.",9,2,0
 27340 data8,11,"Trouw met prins(es).",4,6,2
 27350 data14,14,"Teken televisiecontract.",10,10000,0
 27360 data2,2,"Fainmail vermindert.",12,0,0
 27370 data8,8,"Betrokken in schandaal.",16,10,0
 27380 data14,14,"Je krijgt een hoofdrol.",17,10000,0
 27390 data8,8,"Je wint een oscar.",8,12,0
 27400 data11,11,"Prachtig landschap.",1,2,0
 27410 data2,2,"Makkelijk terrein. Snelle vordering.",18,0,0
 27420 data2,2,"Je verliest helft van je uitrusting.",19,20000,0
 27430 data11,11,"Je ziet zeldzame vogel.",1,2,0
 27440 data2,2,"Moeilijk opgravingswerk.",2,2,0
 27450 data11,11,"Adembenemend gezicht op de Andes.",1,4,0
 27460 data2,2,"Je valt van rots.",13,0,0
 27470 data14,14,"Je vindt ader met waardevolle stenen.",5,100000,0
 27480 data8,11,"Je vindt Inca ruine.",4,2,4
 27490 data11,11,"Beklim bekende bergtop.",1,6,0
 27500 data14,14,"Je vindt rijk uranium erts.",5,200000,0
 27510 data11,11,"Prachtig ruimteschip.",1,2,0
 27520 data2,2,"Mislukte start.",20,0,0
 27530 data2,2,"Je durft niet verder te gaan.",21,0,0
 27540 data8,8,"Goede start.",8,6,0
 27550 data8,11,"Je verhelpt defect aan zuurstofinstallatie.",4,2,4
 27560 data14,14,"Promotie voor moed.",10,20000,0
 27570 data2,2,"Noodlanding.",2,2,0
 27580 data8,8,"Je landt als eerste mens op Mars.",8,16,0
 27590 data8,8,"Je ondekt leven op Mars.",8,10,0
 27600 data14,14,"Vindt goud in krater.",5,100000,0
 27610 data8,8,"Spring over een berg.",22,10,0
 27620 data8,11,"Behouden landing.",4,6,4
 27630 data14,14,"Verkoop Mars-stenen aan museum.",5,50000,0
 27640 data"Marsexpeditie","Normaal",31,8
 27650 data"Zeevaart","Normaal",15,4
 27660 data"Uranium zoeken","Normaal",28,7
 27670 data"Handel","Normaal",12,3
 27680 data"Hollywood","Normaal",23,6
 27690 data"Riviera","Normaal",25,0
 27700 data"Vrije keus","Normaal",-1,-1
 27710 data"Landbouw","Normaal",5,1
 27720 data"Politiek","Normaal",20,5
 27730 data"Politiek","Gratis",20,5
 27740 data"Uranium","Gratis",28,7
 27750 data"Universiteit","Normaal",8,2
 27760 data"Hollywood","Gratis",23,6
 27770 data"Zeevaart","Gratis",15,4
 27780 data"Marsexpeditie","Gratis",31,8
 27790 data"{rvon}   {rvof}{CBM-K}{down}{left}{left}{left}{left}{rvon} {SHIFT-@} {rvof}{CBM-K}{down}{left}{left}{left}{left}{rvon}{CBM-I}{CBM-I}{CBM-I}{rvof}~{up}{up} "
 27800 data"{rvon}{CBM-D}  {rvof}{CBM-K}{down}{left}{left}{left}{left}{rvon}  {CBM-D}{rvof}{CBM-K}{down}{left}{left}{left}{left}{rvon}{CBM-I}{CBM-I}{CBM-I}{rvof}~{up}{up} "
 27810 data"{rvon}{CBM-D}  {rvof}{CBM-K}{down}{left}{left}{left}{left}{rvon} {SHIFT-@}{CBM-D}{rvof}{CBM-K}{down}{left}{left}{left}{left}{rvon}{CBM-I}{CBM-I}{CBM-I}{rvof}~{up}{up} "
 27820 data"{rvon}{CBM-D} {CBM-D}{rvof}{CBM-K}{down}{left}{left}{left}{left}{rvon}{CBM-D} {CBM-D}{rvof}{CBM-K}{down}{left}{left}{left}{left}{rvon}{CBM-I}{CBM-I}{CBM-I}{rvof}~{up}{up} "
 27830 data"{rvon}{CBM-D} {CBM-D}{rvof}{CBM-K}{down}{left}{left}{left}{left}{rvon}{CBM-D}{SHIFT-@}{CBM-D}{rvof}{CBM-K}{down}{left}{left}{left}{left}{rvon}{CBM-I}{CBM-I}{CBM-I}{rvof}~{up}{up} "
 27840 data"{rvon}{CBM-D}{CBM-D}{CBM-D}{rvof}{CBM-K}{down}{left}{left}{left}{left}{rvon}{CBM-D}{CBM-D}{CBM-D}{rvof}{CBM-K}{down}{left}{left}{left}{left}{rvon}{CBM-I}{CBM-I}{CBM-I}{rvof}~{up}{up} "
 27850 data"Landbouw","Universiteit","Handel","Zeevaart","Politiek"
 27860 data"Hollywood","Uranium zoeken","Mars-expeditie"
 27870 data5,8,12,15,20,23,28,31
 27880 data2,2,2,3,2,2,2,3,2,1,1,3,1,1,1
 27890 :
 27900 rem "--- Menudata ---
 27910 :
 27920 data4,5
 27930 data"Spel",3,"Dobbelen","Opnieuw beginnen","Stoppen"
 27940 data"Disc",2,"Saven Spel","Oud spel laden"
 27950 data"Kaarten",3,"Laat kaarten zien","Gebruik kanskaart","Gebruik ervaringskaart"
 27960 data"Informatie",4,"Over veld","Over spelstand","Legenda kleuren","Over spel"
 27970 data2,"Ja","Nee"
 27980 data2,"Verder","Stoppen"
 27990 data4,"Fl.  20.000","Fl.  80.000","Fl. 160.000","Niets"
 28000 data4,"Clubhuis","Speeltuin","Zwembad","Niets"
 28010 data4,"Rechten","Medicijnen","Wis- en natuurkunde","Werktuigkunde"
 28020 :
 28030 rem "---------------------------------------------------------------------
 28040 rem "-                           Einde programma                         -
 28050 rem "---------------------------------------------------------------------
