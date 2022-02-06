# Careers:
# Boardgame for the C128 80 column mode
# Written in 2021 by Xander Mol
# https://github.com/xahmol/careers
# https://www.idreamtin8bits.com/

# See src/main.c for full credits

# Prerequisites for building:
# - CC65 compiled and included in path with sudo make avail
# - ZIP packages installed: sudo apt-get install zip
# - wput command installed: sudo apt-get install wput

SOURCESMAIN = src/main.c src/ring1.c src/ring2.c src/ring3.c src/ring4.c src/career1.c src/career2.c src/menu1.c src/menu2.c src/menu3.c src/vdc_core.c src/sidplay.c src/snes.c
SOURCESLIB = src/vdc_core_assembly.s src/sidplay_assembly.s src/careertext.s src/bootsect.s
OBJECTS = bootsect.bin careers.maco.prg careers.chrs.prg careers.chra.prg careers.tscr.prg careers.scrn.prg careers.ctxt.prg careers.mus1.prg careers.mus2.prg careers.mus3.prg careers.ovl1.prg careers.ovl2.prg careers.ovl3.prg careers.ovl4.prg careers.ovl5.prg careers.ovl6.prg careers.ovl7.prg careers.ovl8.prg careers.ovl9.prg

ZIP = careers-v010-$(shell date "+%Y%m%d-%H%M").zip
D64 = careers.d64
D71 = careers.d71
D81 = careers.d81
README = README.pdf

# Hostname of Ultimate II+ target for deployment. Edit for proper IP and usb number
ULTHOST = ftp://192.168.1.19/usb1/dev/
ULTHOST2 = ftp://192.168.1.31/usb1/dev/

MAIN = careers.prg

CC65_TARGET = c128
CC = cl65
CFLAGS  = -t $(CC65_TARGET) --create-dep $(<:.c=.d) -Os -I include
LDFLAGSMAIN = -t $(CC65_TARGET) -C careers-cc65config.cfg -m $(MAIN).map

########################################

.SUFFIXES:
.PHONY: all clean deploy vice
all: $(MAIN) $(D64) $(D71) $(D81) $(ZIP)

ifneq ($(MAKECMDGOALS),clean)
-include $(SOURCESMAIN:.c=.d)
endif

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<
  
$(MAIN): $(SOURCESLIB) $(SOURCESMAIN:.c=.o)
	$(CC) $(LDFLAGSMAIN) -o $@ $^

$(D64):	$(MAIN) $(OBJECTS)
	c1541 -format "careers,xm" d64 $(D64)
	c1541 $(D64) -bwrite bootsect.bin 1 0
	c1541 $(D64) -bpoke 18 0 4 $14 %11111110
	c1541 $(D64) -bam 1 1
	c1541 -attach $(D64) -write careers.prg careers
	c1541 -attach $(D64) -write careers.maco.prg careers.maco
	c1541 -attach $(D64) -write careers.chrs.prg careers.chrs
	c1541 -attach $(D64) -write careers.chra.prg careers.chra
	c1541 -attach $(D64) -write careers.tscr.prg careers.tscr
	c1541 -attach $(D64) -write careers.scrn.prg careers.scrn
	c1541 -attach $(D64) -write careers.ovl1.prg careers.ovl1
	c1541 -attach $(D64) -write careers.ovl2.prg careers.ovl2
	c1541 -attach $(D64) -write careers.ovl3.prg careers.ovl3
	c1541 -attach $(D64) -write careers.ovl4.prg careers.ovl4
	c1541 -attach $(D64) -write careers.ovl5.prg careers.ovl5
	c1541 -attach $(D64) -write careers.ovl6.prg careers.ovl6
	c1541 -attach $(D64) -write careers.ovl7.prg careers.ovl7
	c1541 -attach $(D64) -write careers.ovl8.prg careers.ovl8
	c1541 -attach $(D64) -write careers.ovl9.prg careers.ovl9
	c1541 -attach $(D64) -write careers.ctxt.prg careers.ctxt
	c1541 -attach $(D64) -write careers.mus1.prg careers.mus1
	c1541 -attach $(D64) -write careers.mus2.prg careers.mus2
	c1541 -attach $(D64) -write careers.mus3.prg careers.mus3

$(D71):	$(MAIN) $(OBJECTS)
	c1541 -format "careers,xm" d71 $(D71)
	c1541 $(D71) -bwrite bootsect.bin 1 0
	c1541 $(D71) -bpoke 18 0 4 $14 %11111110
	c1541 $(D71) -bam 1 1
	c1541 -attach $(D71) -write careers.prg careers
	c1541 -attach $(D71) -write careers.maco.prg careers.maco
	c1541 -attach $(D71) -write careers.chrs.prg careers.chrs
	c1541 -attach $(D71) -write careers.chra.prg careers.chra
	c1541 -attach $(D71) -write careers.tscr.prg careers.tscr
	c1541 -attach $(D71) -write careers.scrn.prg careers.scrn
	c1541 -attach $(D71) -write careers.ovl1.prg careers.ovl1
	c1541 -attach $(D71) -write careers.ovl2.prg careers.ovl2
	c1541 -attach $(D71) -write careers.ovl3.prg careers.ovl3
	c1541 -attach $(D71) -write careers.ovl4.prg careers.ovl4
	c1541 -attach $(D71) -write careers.ovl5.prg careers.ovl5
	c1541 -attach $(D71) -write careers.ovl6.prg careers.ovl6
	c1541 -attach $(D71) -write careers.ovl7.prg careers.ovl7
	c1541 -attach $(D71) -write careers.ovl8.prg careers.ovl8
	c1541 -attach $(D71) -write careers.ovl9.prg careers.ovl9
	c1541 -attach $(D71) -write careers.ctxt.prg careers.ctxt
	c1541 -attach $(D71) -write careers.mus1.prg careers.mus1
	c1541 -attach $(D71) -write careers.mus2.prg careers.mus2
	c1541 -attach $(D71) -write careers.mus3.prg careers.mus3

$(D81):	$(MAIN) $(OBJECTS)
	c1541 -format "careers,xm" d81 $(D81)
	c1541 $(D81) -bwrite bootsect.bin 1 0
	c1541 $(D81) -bpoke 40 1 16 $27 %11111110
	c1541 $(D81) -bam 1 1
	c1541 -attach $(D81) -write careers.prg careers
	c1541 -attach $(D81) -write careers.maco.prg careers.maco
	c1541 -attach $(D81) -write careers.chrs.prg careers.chrs
	c1541 -attach $(D81) -write careers.chra.prg careers.chra
	c1541 -attach $(D81) -write careers.tscr.prg careers.tscr
	c1541 -attach $(D81) -write careers.scrn.prg careers.scrn
	c1541 -attach $(D81) -write careers.ovl1.prg careers.ovl1
	c1541 -attach $(D81) -write careers.ovl2.prg careers.ovl2
	c1541 -attach $(D81) -write careers.ovl3.prg careers.ovl3
	c1541 -attach $(D81) -write careers.ovl4.prg careers.ovl4
	c1541 -attach $(D81) -write careers.ovl5.prg careers.ovl5
	c1541 -attach $(D81) -write careers.ovl6.prg careers.ovl6
	c1541 -attach $(D81) -write careers.ovl7.prg careers.ovl7
	c1541 -attach $(D81) -write careers.ovl8.prg careers.ovl8
	c1541 -attach $(D81) -write careers.ovl9.prg careers.ovl9
	c1541 -attach $(D81) -write careers.ctxt.prg careers.ctxt
	c1541 -attach $(D81) -write careers.mus1.prg careers.mus1
	c1541 -attach $(D81) -write careers.mus2.prg careers.mus2
	c1541 -attach $(D81) -write careers.mus3.prg careers.mus3

$(ZIP): $(MAIN) $(OBJECTS) $(D64) $(D71) $(D81) $(README)
	zip $@ $^

clean:
	$(RM) $(SOURCESMAIN:.c=.o) $(SOURCESMAIN:.c=.d) $(MAIN) $(MAIN).map
	
# To deploy software to UII+ enter make deploy. Obviously C128 needs to powered on with UII+ and USB drive connected.
deploy: $(MAIN)
	wput -u $(MAIN) $(OBJECTS) $(D64) $(D71) $(D81) $(ULTHOST)
	wput -u $(MAIN) $(OBJECTS) $(D64) $(D71) $(D81) $(ULTHOST2)

# To run software in VICE
vice: $(D64)
	x128 -autostart $(D81)
