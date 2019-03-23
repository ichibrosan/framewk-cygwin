;****************************************************************
;	Format N8VEMram disk B - 2008 J Moxham                  *
; modified with JR loops so can be relocated anywhere in ram    *
;                                                               *
;****************************************************************
IO_Y0:		.EQU	$60
IO_Y1:		.EQU	$68
IO_Y2:		.EQU	$70
IO_Y3:		.EQU	$78

; PIO 82C55 I/O IS ATTACHED TO THE FIRST IO BASE ADDRESS

PIO1A:		.EQU	$IO_Y0+0	; (INPUT)  IN 1-8
PIO1B:		.EQU	$IO_Y0+1	; (OUTPUT) OUT TO LEDS
PIO1C:		.EQU	$IO_Y0+2	; (INPUT)  
PIO1CONT:	.EQU	$IO_Y0+3	; CONTROL BYTE PIO 82C55

; UART 16C450 SERIAL IS ATTACHED TO THE SECOND IO BASE ADDRESS

UART0:		.EQU	$IO_Y1+0	; DATA IN/OUT
UART1:		.EQU	$IO_Y1+1	; CHECK RX
UART2:		.EQU	$IO_Y1+2	; INTERRUPTS
UART3:		.EQU	$IO_Y1+3	; LINE CONTROL
UART4:		.EQU	$IO_Y1+4	; MODEM CONTROL
UART5:		.EQU	$IO_Y1+5	; LINE STATUS
UART6:		.EQU	$IO_Y1+6	; MODEM STATUS
UART7:		.EQU	$IO_Y1+7	; SCRATCH REG.

; MEMORY PAGE CONFIGURATION LATCH IS ATTACHED TO FOURTH IO BASE ADDRESS

MPCL_RAM:	.EQU	$IO_Y3		; RAM CONTROL PORT, SHOULD ONLY BE CHANGED WHILE
					; IN UPPER MEMORY PAGE $8000-$FFFF OR LIKELY
					; LOSS OF CPU MEMORY CONTEXT.

MPCL_ROM:	.EQU	$IO_Y3+$04	; ROM CONTROL PORT, SHOULD ONLY BE CHANGED WHILE
					; IN UPPER MEMORY PAGE $8000-$FFFF OR LIKELY
					; LOSS OF CPU MEMORY CONTEXT.

; RAM MEMORY PAGE CONFIGURATION LATCH CONTROL PORT ( IO_Y3 ) INFORMATION

;	7 6 5 4  3 2 1 0      ONLY APPLICABLE TO THE LOWER MEMORY PAGE $0000-$7FFF
;	^ ^ ^ ^  ^ ^ ^ ^
;	: : : :  : : : :--0 = A15 RAM ADDRESS LINE DEFAULT IS 0
;	: : : :  : : :----0 = A16 RAM ADDRESS LINE DEFAULT IS 0
;	: : : :  : :------0 = A17 RAM ADDRESS LINE DEFAULT IS 0
;	: : : :  :--------0 = A18 RAM ADDRESS LINE DEFAULT IS 0
;	: : : :-----------0 = 
;	: : :-------------0 = 
;	: :---------------0 = 
;	:-----------------0 = 

; ROM MEMORY PAGE CONFIGURATION LATCH CONTROL PORT ( IO_Y3+$04 ) INFORMATION

;	7 6 5 4  3 2 1 0      ONLY APPLICABLE TO THE LOWER MEMORY PAGE $0000-$7FFF
;	^ ^ ^ ^  ^ ^ ^ ^
;	: : : :  : : : :--0 = A15 ROM ADDRESS LINE DEFAULT IS 0
;	: : : :  : : :----0 = A16 ROM ADDRESS LINE DEFAULT IS 0
;	: : : :  : :------0 = A17 ROM ADDRESS LINE DEFAULT IS 0
;	: : : :  :--------0 = A18 ROM ADDRESS LINE DEFAULT IS 0
;	: : : :-----------0 = A19 ROM ONLY ADDRESS LINE DEFAULT IS 0
;	: : :-------------0 = 
;	: :---------------0 = 
;	:-----------------0 = ROM SELECT (0=ROM, 1=RAM) DEFAULT IS 0


; NOTE THESE ARE ARTIFACTS FROM THE BRUCE JONES ROM MONITOR PROGRAM
; THE FLOPPY DISK CONTROLLER HARDWARE DOES NOT EXIST IN TEST PROTOTYPE
; AT THIS TIME BUT MAY BE INCLUDED AT SOME FUTURE DATE

; PI/O DISK CONTROLLER DATA

;	DCMD	==	63H	;FDC CONTROL PORT
;	WDC	==	64H	;FDC BASE ADDRESS
;	WCMD	==	WDC+0	;FDC COMMAND REG
;	WSTAT	==	WDC+0	;FDC STATUS REG
;	WTRACK	==	WDC+1
;	WSECT	==	WDC+2	;FDC SECTOR REG
;	WDATA	==	WDC+3	;FDC DATA REG

;179X COMMAND VALUES

;	RES	==	0BH	;RESTORE
;	SEEK	==	1BH	;SEEK NO VERIFY
;	READ	==	8CH	;READ NO SIDE COMPARE
;	WRITE	==	0ACH	;WRITE NO SIDE COMPARE
;	INT	==	0D0H	;FORCE INTERRUPT

;	DENS	==	01111110B ;INITIAL BOOT BYTE
;	HOME	==	0	;HOME TRACK VALUE
;	TRAK	==	0	;DESTINATION TRACK
;	BOOT	==	0	;LOCATION TO JUMP AFTER BOOTSTRAP
;	BCOUNT	==	512	;NUMBER OF BYTES TO READ IN

;PIO DISK CONTROLLER CONTROL PORT ( 63H ) INFORMATION

;	7 6 5 4  3 2 1 0
;	^ ^ ^ ^  ^ ^ ^ ^
;	: : : :  : : : :--0 = DISK 0 SELECTED
;	: : : :  : : :----0 = DISK 1 SELECTED
;	: : : :  : :------0 = DISK 2 SELECTED
;	: : : :  :--------0 = DISK 3 SELECTED
;	: : : :-----------1 = LOWER HEAD
;	: : :-------------0 = 
;	: :---------------0 = 
;	:-----------------0 = WAIT STATE


;********************* CONSTANTS ****************************************

RAMTOP:		.EQU	$FFFF	; HIGHEST ADDRESSABLE MEMORY LOCATION
RAMBOTTOM:	.EQU	$8000	; START OF FIXED UPPER 32K PAGE OF 512KB x 8 RAM 8000H-FFFFH
MONSTARTCOLD:	.EQU	$F800	; COLD START MONITOR IN HIGH RAM
END:		.EQU	$FF	; Mark END OF TEXT
CR:		.EQU	0DH	; ASCII carriage return character
LF:		.EQU	0AH	; ASCII line feed character
ESC:		.EQU	1BH	; ASCII escape character

		.org 	$0100


		ld hl,$0110		; move $80 bytes from location $0110 to $9000
		ld de,$9000
		ld bc,$80
		ldir
		jp $9000		; jump to $9000 ' arbitrary location above $8000 but below CPM

		.org	$0110		; compile at $0110 but all jumps are relative
FORMATRAM:

	LD	A,%00000000
	OUT	(MPCL_RAM),A		; reset RAM memory pager configuration latch to default
	LD	A,%00000000
	OUT	(MPCL_ROM),A		; reset ROM memory pager configuration latch to default
	LD	A,%10000000
	OUT	(MPCL_ROM),A		; ensure ROM is switched out
	LD	A,%00000000		; start RAM page counter in A at zero
FORM_MEM_LOOP:
					; objective is to initialize all SRAM pages
					; fill selected SRAM page with its page number
					; page numbers are $0-$F
					; page $F is reserved so do not overwrite it
					; or you will lose CPU context
	OUT	(MPCL_RAM),A		; switch out ROM and in SRAM page 0
					; indicate to operator what is happening by
					; flashing SRAM page number in the LEDs with
					; the MSB of LEDs lit
;	OUT	(PIO1B),A		; output value to PIO, port B LEDs during initialize
	LD	HL,$0000		; specify beginning of lower 32K page in HL
	LD	BC,$8000		; specify length of lower 32K page in BC
					; specify fill value data in A

	ld	e,l			; fill memory
	ld	d,h
	inc	de
	ld	(hl),A
	ldir
	INC	A			; select next memory page and change fill value
	CP	$0F			; have you filled $0E pages yet?
	JR	NZ,FORM_MEM_LOOP	; no, go initialize the next page
					; yes, go on to start monitor
	LD	A,$00			
;	OUT	(PIO1B),A		; output value to PIO, turn off port B LEDs
	LD	A,%00000001		; switch in first 32K lower page (first track)
	OUT	(MPCL_RAM),A		;
;                   Formatting the ram is simple as clearing the directory area 
;                   to a value of E5h (the first 8k of track 1 or the ramdisk).
	LD	HL,$0000		; starting memory address of track 1, sector 0 in HL
	LD	BC,$1FFF		; 8K of directory sectors reserved (length in BC)
	LD	A,$E5			; initializing value in A 
	ld	e,l			; fill memory
	ld	d,h
	inc	de
	ld	(hl),A
	ldir
; RESET MPCL latch to default CP/M with 64K setting
	LD	A,%00000000
	OUT	(MPCL_RAM),A		; reset memory pager configuration latch to default
					; default configuration is full 64K RAM and 32K ROM
					; switched out
	LD	A,%10000000
	OUT	(MPCL_ROM),A		; reset memory pager configuration latch to default
					; default configuration is full 64K RAM and 32K ROM
					; switched out
	JP	$EA03			; Jump to warm boot CPM
	.byte "End Format"
	.byte "------"
	.ORG	$04ff	; fill up space so RTC and xmodem in the right spot
	.db	$00
.END


