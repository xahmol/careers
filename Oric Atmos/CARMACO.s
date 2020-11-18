	.zero

	*=$50
_GameBoardZP		.dsb 2		    ; Gameboard address zero page
_ScreenZP	    	.dsb 2		    ; Screen address zero page

	.text

    *=$6500 

#define BoarddataStart  $9800       ; Game board data base address
#define Screenstart     $bcc0       ; Screen position X=0 and Y=7

StartCopygameboard
; Obtain game board copy adress via Y and X registers
    clc                             ; Clear carry
    lda YpointersLowbyte,y          ; Obtain low byte of vertical index
    adc Xpointers,x                 ; Add x index
    sta _GameBoardZP                ; Store low byte in zero page
    lda YpointersHighbyte,y         ; Obtain high byte of vertical index
    adc #0                          ; Add zero to add carry if needed
    sta _GameBoardZP+1              ; Store high byte in zero page

; Load screen base address at X=1 and Y=7
    lda #<Screenstart               ; Load low byte of screen base address
    sta _ScreenZP                   ; Store low byte in zero page
    lda #>Screenstart               ; Load high byte of screen base address
    sta _ScreenZP+1                 ; Store low byte in zero page

; Main routine
    ldx #20                         ; Counter for 20 lines
loop_x
    ldy #0                          ; Reset at char 0 of line
    lda #0                          ; Value for black ink
    sta (_ScreenZP),y               ; Store black ink at start of each line

; Loop for copying a single line
loop_y
    lda (_GameBoardZP),y            ; Load char at x index
    iny                             ; Increase y
    sta (_ScreenZP),y               ; Store char at x index
    cpy #39                         ; Did we reach char 39?
    bne loop_y                      ; Continue loop if not equal
 
 ; Add 89 to source address pointer
    clc                             ; Clear carry
    lda _GameBoardZP                ; Load low byte
    adc #89                         ; Add 89
    sta _GameBoardZP                ; Store updated address
    lda _GameBoardZP+1              ; Load high byte
    adc #0                          ; Add zero to add carry if needed
    sta _GameBoardZP+1              ; Store high byte

 ; Add 40 to screen address pointer
    clc                             ; Clear carry
    lda _ScreenZP                   ; Load low byte
    adc #40                         ; Add 40
    sta _ScreenZP                   ; Store updated address
    lda _ScreenZP+1                 ; Load high byte
    adc #0                          ; Add zero to add carry if needed
    sta _ScreenZP+1                 ; Store high byte

; Next line
    dex                             ; Decrease x
    bne loop_x                      ; Continue loop if not zero                 

    rts                             ; Finished and return

; Pointers for the start adresses of the half tile lines

YpointersHighbyte
    .byt >BoarddataStart
    .byt >BoarddataStart+356
    .byt >BoarddataStart+712
    .byt >BoarddataStart+1068
    .byt >BoarddataStart+1424
    .byt >BoarddataStart+1780
    .byt >BoarddataStart+2136
    .byt >BoarddataStart+2492
    .byt >BoarddataStart+2848
    .byt >BoarddataStart+3204
    .byt >BoarddataStart+3560
    .byt >BoarddataStart+3916
    .byt >BoarddataStart+4272
    .byt >BoarddataStart+4539

YpointersLowbyte
    .byt <BoarddataStart
    .byt <BoarddataStart+356
    .byt <BoarddataStart+712
    .byt <BoarddataStart+1068
    .byt <BoarddataStart+1424
    .byt <BoarddataStart+1780
    .byt <BoarddataStart+2136
    .byt <BoarddataStart+2492
    .byt <BoarddataStart+2848
    .byt <BoarddataStart+3204
    .byt <BoarddataStart+3560
    .byt <BoarddataStart+3916
    .byt <BoarddataStart+4272
    .byt <BoarddataStart+4539

; Horizontal offsett per tile

Xpointers
    .byt 0
    .byt 10
    .byt 20
    .byt 30
    .byt 40
    .byt 50
    .byt 60