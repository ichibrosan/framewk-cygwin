;***********************************
;*	Z80 Test Prototype
;*	LOAD MONITOR FROM ROM INTO RAM AND EXECUTE Program
;*	Andrew Lynch
;*	lynchaj@yahoo.com
;*	15 Feb 2007
;***********************************


;********************* CONSTANTS ****************************************

RAMTOP:		.EQU	$FFFF	; HIGHEST ADDRESSABLE MEMORY LOCATION
MONSTART:	.EQU	$F800	; START OF 6116 SRAM 2KB x 8 RAM F800H-FFFFH
RAMBOTTOM:	.EQU	$8000	; Beginning of Upper 32K RAM page
END:		.EQU	$FF	; Mark END OF TEXT
CR:		.EQU	0DH	; ASCII carriage return character
LF:		.EQU	0AH	; ASCII line feed character
ESC:		.EQU	1BH	; ASCII escape character

ROMSTART_MON:	.EQU	$0100	; Where the Monitor is stored in ROM
RAMTARG_MON:	.EQU	$F800	; Where the Monitor starts in RAM (entry point)
MOVSIZ_MON:	.EQU	$0800	; Monitor is 2KB in length

ROMSTART_CPM:	.EQU	$0900	; Where the CCP+BDOS+BIOS is stored in ROM
RAMTARG_CPM:	.EQU	$D400	; Where the CCP+BDOS+BIOS starts in RAM (entry point)
MOVSIZ_CPM:	.EQU	$2100	; CCP, BDOS, + BIOS is 6-7KB in length $1EFF

Monitor_Entry	.EQU	$F860	; Monitor Entry Point (May change)
IO_Y3:		.EQU	$78


MPCL_ROM:	.EQU	$IO_Y3+$04	; ROM CONTROL PORT, SHOULD ONLY BE CHANGED WHILE
					; IN UPPER MEMORY PAGE $8000-$FFFF OR LIKELY
					; LOSS OF CPU MEMORY CONTEXT.


;*******************************************************************
;*	START AFTER RESET
;*	Function	: ready system, load monitor into RAM and start
;*******************************************************************

	.ORG	$0000

	DI			; Disable interrupt
	LD	SP,RAMTOP	; Set stack pointer to top off ram
	IM	1		; Set interrupt mode 1

	LD	HL,ROMSTART_MON	; where in rom Monitor is stored (first byte)
        LD	DE,RAMTARG_MON	; where in ram to move Monitor to (first byte)
	LD	BC,MOVSIZ_MON	; number of bytes to move from ROM to RAM
	LDIR			; Perform Block Copy of Monitor to Upper RAM page

	LD	HL,ROMSTART_CPM	; where in rom CP/M is stored (first byte)
        LD	DE,RAMTARG_CPM	; where in ram to move Monitor to (first byte)
	LD	BC,MOVSIZ_CPM	; number of bytes to move from ROM to RAM
	LDIR			; Perform Block Copy of CP/M to Upper RAM page

	EI			; enable interrupts (access to Monitor while CP/M running)

	JP	$MONSTART	; jump to Start of Monitor


;************************************************************************
;*	MASKABLE INTERRUPT-PROGRAM
;*	Function	:
;*	Input		:
;*	Output		: 
;*	uses		: 
;*	calls		: none
;*	info		:
;*	tested		: 2 Feb 2007
;************************************************************************

	.ORG	$0038		; Int mode 1
;	DI			; disable
TESTLOOP:	
	OUT	($68),A
	JP	TESTLOOP

;	JP	$Monitor_Entry	; Go to Monitor
;	EI			; enable again
	RETI			; return from interrupt


;************************************************************************
;*	NONMASKABLE INTERRUPT-PROGRAM
;*	Function	:
;*	Input		:
;*	Output		: none
;*	uses		: 
;*	calls		: none
;*	info		:
;*	tested		: 2 Feb 2007
;************************************************************************

	.ORG	$0066		; HERE IS THE NMI ROUTINE
	RETI

;******************************************************************
;*	SUB-ROUTINE	: PAUSE
;*	Function	: Pause in 100uS. times value in BC
;*	Input		: BC reg
;*	Output		: none
;*	call		: NONE
;*	Info		: KEA. 
;*	tested		: 2 Feb 2007
;******************************************************************

PAUSE:
	PUSH	AF
	INC	B
	INC	C			; ADJUST THE LOOP
PAUSELOOP1:	LD	A,13H		; ADJUST THE TIME 13h IS FOR 4 MHZ
PAUSELOOP2:	DEC	A		; DEC COUNTER. 4 T-states = 1 uS.
	JP	NZ,PAUSELOOP2		; JUMP TO PAUSELOOP2 IF A <> 0.
	DEC	C			; DEC COUNTER
	JP	NZ,PAUSELOOP1		; JUMP TO PAUSELOOP1 IF C <> 0.

	DJNZ	PAUSELOOP1		; JUMP TO PAUSELOOP1 IF B <> 0.
PAUSE_END:	POP	AF
	RET


	.ORG	$00FF
FLAG	.db	$FF		; Fills with zeros up to FF and next program then fits in correct place

.END
