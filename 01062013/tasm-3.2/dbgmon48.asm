;****************************************************************
;*	Z80 Test Prototype                                      *
;*	THIRD BOOT Program (RAM LOADABLE MONITOR EXPERIMENT)    *
;*	Andrew Lynch                                            *
;*	lynchaj@yahoo.com                                       *
;*	13 Feb 2007 with mods J Moxham 4th October 2008         *
;****************************************************************

;********************* PROGRAM OBJECTIVES *********************************

; OBJECTIVE OF FIRST BOOT PROGRAM is to verify CPU, ROM, RAM, memory decode, and
; IO decode logic function

; Simple output are LEDs attached to chipselect logic at IO port and memory
; chipselect lines.  Chip Select lines are active when grounded and result
; in LEDs slightly dimming

; Simple input is the RESET key and the INTERRUPT key.  The RESET key starts
; and restarts the program dimming the LEDs in a cycle.  Pressing the INTERRUPT
; key halts the CPU and stops the program.  Pressing RESET again restarts.

; OBJECTIVE OF SECOND BOOT PROGRAM is to expand on FIRST BOOT program and 
; verify correct operation of PIO and UART circuits

; OBJECTIVE OF THIRD BOOT PROGRAM is to add basic ROM monitor functions


;********************* REFERENCES *****************************************

; Thomas Scherrer basic hardware test assembler sources from the Z80 info page
; including original schematic concept

; http://z80.info/z80sourc.txt

; Code samples from Bruce Jones public domain ROM monitor for the SBC-200C 

; http://www.retrotechnology.com/herbs_stuff/sd_bruce_code.zip

; Inspiration from Joel Owens "Z-80 Space-Time Productions Single Board Computer"

; http://www.joelowens.org/z80/z80index.html

; Great help and technical advice from Allison at ALPACA_DESIGNERS

; http://groups.yahoo.com/group/alpaca_designers

; INTEL SDK-85 ROM Debug Monitor

;********************* HARDWARE IO ADR ************************************

; IO ADDRESS DECODE PORT BASES
; TEST PROTOTYPE ACCEPTS FOUR SETS OF IO ADDRESSES STARTING AT THE FOLLOWING
; BASE ADDRESSES.  THESE CORRESPOND TO THE CHIP SELECT LINES OUTPUT FROM THE
; 74LS139 DEMULTIPLEXER

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


;*******************************************************************
;*	MAIN PROGRAM
;*******************************************************************

	.ORG	MONSTARTCOLD
	CALL	INITIALIZE
MONSTARTWARM:			; CALL HERE FOR MONITOR WARM START

	XOR	A		;ZERO OUT ACCUMULATOR (added)
	PUSH	HL		;protect HL from overwrite     
	LD	HL,TXT_READY	;POINT AT TEXT
	CALL	MSG		;SHOW WE'RE HERE
	POP	HL		;protect HL from overwrite


;**************** MONITOR COMMANDS *****************

;not done ; A BOOT FV II DRIVE 0
;not done ; B BOOT FV II DRIVE 1
;not done ; 1 BOOT FV II DRIVE 0 FROM ROM
;not done ; 2 BOOT FV II DRIVE 1 FROM ROM
;done ; A Print out all commands
;done ; C BOOT CP/M FROM ROM DRIVE
;done ; D XXXXH YYYYH  DUMP MEMORY FROM XXXX TO YYYY
;done ; E XXXXH EXAMINE MEMORY LOC XXXX
;done ; F XXXXH YYYYH ZZH FILL MEMORY FROM XXXX TO YYYY WITH ZZ
;done ; H LOAD INTEL HEX FORMAT DATA
;done ; I INPUT FROM PORT AND SHOW HEX DATA
;done ; K ECHO KEYBOARD INPUT
;done ; M XXXXH YYYYH ZZZZH MOVE MEMORY BLOCK XXXX TO YYYY TO ZZZZ
;done ; O OUTPUT TO PORT HEX DATA
;done ; P PROGRAM RAM STARTING FROM CURRENT LOCATION
;done ; R RUN A PROGRAM FROM CURRENT LOCATION
;done ; 'ESCAPE' STOP CURRENT MODE AND WAIT FOR NEW COMMAND


;*******************************************************
;*	COMMAND CHECK ROUTINE
;*	READ THE KEYBOARD & EXECUTE VALID COMMANDS
;*******************************************************

CHEK:

; edited Oct 15 2008 J Moxham - jump straight to CPM

	LD	SP,RAMTOP	;RESET ON ESCAPE

	JP GOCPM		; ***** jump straight to CPM - delete this if want to use monitor

	CALL	CRLFA		;CR,LF,>
	CALL	KIN		;GET KEYBOARD DATA
	CP	'E'		;IS IT "E" (y/n)
	JR	Z,EXAM		;IF YES GO EXAMINE ROUTINE
	CP	'O'		;IS IT AN "O" (y/n)
	JP	Z,POUT		;PORT OUTPUT
	CP	'H'		;IS IT A "H" (y/n)
	JP	Z,HXLOAD	;INTEL HEX FORMAT LOAD DATA
	CP	'I'		;IS IT AN "I" (y/n)
	JP	Z,PIN		;PORT INPUT
	CP	'D'		;IS IT A "D" (y/n)
	JP	Z,DUMP		;DUMP MEMORY
	CP	'K'
	JR	Z,KLOP		;LOOP ON KEYBOARD
	CP	'M'		;IS IT A "M" (y/n)
	JP	Z,MOVE		;MOVE MEMORY COMMAND
	CP	'F'		;IS IT A "F" (y/n)
	JP	Z,FILL		;FILL MEMORY COMMAND
	CP	'C'		;IS IT A "C" (y/n)
	JP	Z,GOCPM		;BOOT CP/M FROM ROM DRIVE COMMAND
	CP	'A'		; is it an A
	JP 	Z,PRINTHELP	; print all commands out
	CP	'T'
	JP 	z,FORMATRAM	;FORMAT the ram disk drive B
; got here, no match so print unknown command
	PUSH	HL		;protect HL from overwrite
	LD	HL,TXT_COMMAND	;POINT AT TEXT
	CALL	MSG		;print command label
	CALL	COUT            ;print received command
	POP	HL		;protect HL from overwrite
	JR	CHEK


; *******************************************************
;* Help - print out all commands 
;********************************************************
PRINTHELP:
	PUSH	HL		;protect HL from overwrite
	LD	HL,TXT_HELP	;POINT AT TEXT
	CALL	MSG		;print command label
	POP	HL		;protect HL from overwrite
	JP 	CHEK


;********************************************************
;*	READ THE KEYBOARD, & ECHO IT BACK TO SCREEN
;********************************************************

KLOP:
	CALL	KIN
	JR	KLOP

;********************************************************
;*	READ THE KEYBOARD, & MAKE UPPER-CASE
;********************************************************

KIN:

KIN1:


GETCHR:

RX_BUSYLP:
	IN	A,(UART5)		; READ Line Status Register
	BIT	0,A			; TEST IF DATA IN RECEIVE BUFFER
	JP	Z,RX_BUSYLP		; LOOP UNTIL DATA IS READY
	IN	A,(UART0)		; THEN READ THE CHAR FROM THE UART
	AND	7FH		;STRIP HI BIT
	CP	ESC		;IS IT "ESCAPE" (y/n)
	JR	Z,CHEK		;IF SO GO BACK

;NOW PRINT K.B. DATA ON SCREEN

	CALL	COUT
UPCASE:
	CP	'a'		;KEEP NUMBERS, CONTROLS
	RET	C		;AND UPPER CASE
	CP	7BH		;SEE IF NOT LOWER CASE
	RET	NC
	AND	5FH		;MAKE UPPER CASE
	RET

COUT:

TX_BUSY:
	PUSH   AF
TX_BUSYLP:
	IN	A,(UART5)		; READ Line Status Register
	BIT	5,A			; TEST IF UART IS READY TO SEND
	JP	Z,TX_BUSYLP		; IF NOT REPEAT
	POP	AF
	OUT	(UART0),A		; THEN WRITE THE CHAR TO UART
TX_END_CHAR:
	RET			;DONE


;*********************************************************
;*	PRINT CARRIAGE RETURN & LINE FEED
;*********************************************************

CRLF:
	PUSH	HL		; protect HL from overwrite
	LD	HL,PROMPT
	CALL	MSG
	POP	HL		; protect HL from overwrite
	RET


;********************************************************
;*	ROUTINE TO DISPLAY MEMORY IN EXAMINE MODE
;********************************************************

EXAM:
	CALL	CRLF		;SHOW EXAMINE READY
	CALL	LDHL		;LOAD IN HL REGS.
EXAM1:
	CALL	CRLF		;SHOW READY
DHLD:
	CALL	PHLD		;PRINT HL & DATA
ECK:
	CALL	KIN		;CHECK THE K.B.
	INC	HL		;READY FOR NEXT LOCATION
	CP	' '		;A SPACE (y/n)
	JR	Z,EXAM1
	DEC	HL		;RESET IF NOT NEXT
	CP	'R'
	JR	NZ,SEEP
	JP	(HL)

SEEP:
	CP	'P'		;IS IT A "P" (y/n)
	JR	NZ,ECK		;IF YES GO PROGRAM


;****************************************************
;*	'PROGRAM' THE MEMORY LOCATION
;*	& INCREMENT TO THE NEXT ONE
;****************************************************

PROG:
	CALL	CRLF		;SHOW READY
	CALL	PHL		;GO PRINT ADDRESS
	CALL	SPACE
	CALL	HEXIN		;GET K.B. DATA
	LD	(HL),A		;STORE IT
	CALL	PDAT		;GET DATA FROM RAM & PRINT IT
	INC	HL		;POINT NEXT
	JR	PROG		;AND REPEAT IT


;*****************************************************
;*	GET TWO BYTES OF HEX DATA FROM K.B.
;*	& RETURN WITH THEM IN HL REGS
;*****************************************************

LDHL:
	CALL	HEXIN		;GET K.B. AND MAKE HEX
	LD	H,A		;THATS THE HI BYTE
	CALL	HEXIN		;DO HEX AGAIN
	LD	L,A		;THATS THE LOW BYTE
	RET			;GO BACK WITH ADDRESS  


;*****************************************************
;*	GET K.B. DATA & MAKE IT 'HEX'
;*****************************************************

HEXIN:
	PUSH	BC		;SAVE BC REGS.
	CALL	NIBL		;DO A NIBBLE
	RLC	A		;MOVE FIRST BYTE UPPER NIBBLE  
	RLC	A
	RLC	A
	RLC	A
	LD	B,A		;SAVE ROTATED BYTE
	CALL	NIBL		;DO NEXT NIBBLE
	ADD	A,B		;COMBINE NIBBLES IN ACC.
	POP	BC		;RESTORE BC
	RET			;DONE  
NIBL:
	CALL	KIN		;GET K.B. DATA
	CP	40H		;TEST FOR ALPHA
	JR	NC,ALPH
	AND	0FH		;GET THE BITS
	RET
ALPH:
	AND	0FH		;GET THE BITS
	ADD	A,09H		;MAKE IT HEX A-F
	RET


;**************************************************
;*	PRINT THE HL REGS & THE DATA AT
;*	THE LOCATION POINTED TO BY SAME
;**************************************************

PHLD:
	CALL	PHL		;GO PRINT HL
PDAT:
	CALL	SPACE		;PRINT A SPACE
	LD	A,(HL)		;GET THE DATA


;**************************************************
;*	PRINT THE ACCUMULATOR CONTENTS AS
;*	HEX DATA ON THE SCREEN
;**************************************************

HXOUT:
	PUSH	BC		;SAVE BC
	LD	B,A
	RLC	A		;DO HIGH NIBBLE FIRST  
	RLC	A
	RLC	A
	RLC	A
	AND	0FH		;ONLY THIS NOW
	ADD	A,30H		;TRY A NUMBER
	CP	3AH		;TEST IT
	JR	C,OUT1		;IF CY SET PRINT 'NUMBER'
	ADD	A,07H		;MAKE IT AN ALPHA

OUT1:
	CALL	COUT		;SCREEN IT
	LD	A,B		;NEXT NIBBLE
	AND	0FH		;JUST THIS
	ADD	A,30H		;TRY A NUMBER
	CP	3AH		;TEST IT
	JR	C,OUT2		;PRINT 'NUMBER'
	ADD	A,07H		;MAKE IT ALPHA

OUT2:
	CALL	COUT		;SCREEN IT
	POP	BC		;RESTORE BC
	RET


;***************************************************
;*	PRINT A SPACE CHARACTER ON THE SCREEN
;***************************************************

SPACE:
	PUSH	AF
	LD	A,20H		;LOAD A "SPACE"
	CALL	COUT		;SCREEN IT
	POP	AF
	RET			;DONE


;**************************************************
;*	PRINT THE HL REGS ON THE SCREEN
;**************************************************

PHL:
	LD	A,H		;GET HI BYTE
	CALL	HXOUT		;DO HEX OUT ROUTINE
	LD	A,L		;GET LOW BYTE
	CALL	HXOUT		;HEX IT
	CALL	SPACE
	RET			;DONE  


;**************************************************
;*	WRITE A BYTE TO SPECIFIED PORT
;**************************************************

POUT:
POUT1:
	CALL	CRLF
	CALL	HEXIN		;GET PORT
	LD	C,A		;SAVE PORT POINTER
	CALL	SPACE
	CALL	HEXIN		;GET DATA
OUTIT:
	OUT	(C),A
	JP	CHEK


;**************************************************
;*	GET DATA FROM SPECIFIED PORT AND
;*	DISPLAY IT ON THE SCREEN
;**************************************************

PIN:
	CALL	CRLF
	CALL	HEXIN		;GET PORT
	LD	C,A		;SAVE PORT POINTER
	CALL	SPACE
	IN	A,(C)		;GET DATA
	CALL	HXOUT		;SHOW IT
	JP	CHEK		


;******************************************************
;*	PRINT CARRIAGE RETURN, LINE FEED & >
;******************************************************

CRLFA:
	PUSH	HL		; protect HL from overwrite
	LD	HL,PROMPTA
	 CALL	MSG
	POP	HL		; protect HL from overwrite
	RET			;DONE


;*******************************************************
;*	MESSAGE PRINT ROUTINE
;*******************************************************

MSG:

TX_SERLP:
	LD	A,(HL)			; GET CHARACTER TO A
	CP	END			; TEST FOR END BYTE
	JP	Z,TX_END		; JUMP IF END BYTE IS FOUND
	PUSH   AF
TX_BUSYLP_MSG:
	IN	A,(UART5)		; READ Line Status Register
	BIT	5,A			; TEST IF UART IS READY TO SEND
	JP	Z,TX_BUSYLP_MSG		; IF NOT REPEAT
	POP	AF
	OUT	(UART0),A		; THEN WRITE THE CHAR TO UART
	INC	HL			; INC POINTER, TO NEXT CHAR
	JP	TX_SERLP		; TRANSMIT LOOP
TX_END:
	RET				;ELSE DONE

;****************************************************
;	DUMP MEMORY ROUTINE
;****************************************************

DUMP:
	LD	SP,RAMTOP
	CALL	CRLF		;SHOW READY
	CALL	LDHL		;GET START ADDRESS
	PUSH	HL		;SAVE START
	CALL	SPACE
	CALL	LDHL		;GET END ADDRESS
	INC	HL		;ADD ONE MORE FOR LATER COMPARE
	EX	DE,HL		;PUT END ADDRESS IN DE
	POP	HL		;GET BACK START

GDATA:	
	CALL	CRLF	

BLKRD:
	CALL	PHL		;PRINT START LOCATION
	LD	C,16		;SET FOR 16 LOCS
	PUSH	HL		;SAVE STARTING HL
NXTONE:
	EXX
	LD	C,E
	IN	A,(C)
	EXX
	AND	7FH
	CP	ESC
	JP	Z,CHEK
	CP	19
	JR	Z,NXTONE
	LD 	A,(HL)		;GET BYTE
	CALL	HXOUT		;PRINT IT
	CALL	SPACE

UPDH:	
	INC	HL		;POINT NEXT
	DEC	C		;DEC. LOC COUNT
	JR	NZ,NXTONE	;IF LINE NOT DONE

;NOW PRINT 'DECODED' DATA TO RIGHT OF DUMP

PCRLF:
	CALL	SPACE		;SPACE IT
	LD	C,16		;SET FOR 16 CHARS
	POP	HL		;GET BACK START

PCRLF0:
	LD	A,(HL)		;GET BYTE
	AND	060H		;SEE IF A 'DOT'
	LD	A,(HL)		;O.K. TO GET
	JR	NZ,PDOT
DOT:
	LD	A,2EH		;LOAD A DOT	
PDOT:
	CALL	COUT		;PRINT IT
	INC	HL
	LD	A,D
	CP	H
	JR	NZ,UPDH1
	LD	A,E
	CP	L
	JP	Z,CHEK

;IF BLOCK NOT DUMPED, DO NEXT CHARACTER OR LINE
	
UPDH1:
	DEC	C		;DEC. CHAR COUNT
	JR	NZ,PCRLF0	;DO NEXT
CONTD:
	CALL	CRLF
	JP	BLKRD


;****************************************************
;	INTEL HEX FORMAT LOAD ROUTINE
;****************************************************

;-------------------------------------------------------------------------------------
; LOAD INTEL HEX FORMAT FILE FROM THE CONSOLE.
; [INTEL HEX FORMAT IS:
; 1) COLON (FRAME 0)
; 2) RECORD LENGTH FIELD (FRAMES 1 AND 2)
; 3) LOAD ADDRESS FIELD (FRAMES 3,4,5,6)
; 4) RECORD TYPE FIELD (FRAMES 7 AND 8)
; 5) DATA FIELD (FRAMES 9 TO 9+2*(RECORD LENGTH)-1
; 6) CHECKSUM FIELD - SUM OF ALL BYTE VALUES FROM RECORD LENGTH TO AND 
;   INCLUDING CHECKSUM FIELD = 0 ]
;------------------------------------------------------------------------------	
;EXAMPLE OF INTEL HEX FORMAT FILE
;EACH LINE CONTAINS A CARRIAGE RETURN AS THE LAST CHARACTER
;:18F900002048454C4C4F20574F524C4420FF0D0AFF0D0A3EFF0D0A54BF
;:18F918006573742050726F746F7479706520524F4D204D6F6E69746FF1
;:18F9300072205265616479200D0AFF0D0A434F4D4D414E4420524543F2
;:18F948004549564544203AFF0D0A434845434B53554D204552524F52CD
;:16F96000FF0A0D20202D454E442D4F462D46494C452D20200A0DA4
;:00000001FF


HXLOAD:
	CALL	CRLF		; SHOW READY

HXLOAD0:
	CALL	KIN		; GET THE FIRST CHARACTER, EXPECTING A ':'

HXLOAD1:
	CP	$3A		; IS IT COLON ':'? START OF LINE OF INTEL HEX FILE
	JR	NZ,HXLOADERR	; IF NOT, MUST BE ERROR, ABORT ROUTINE

	LD	E,0		; FIRST TWO CHARACTERS IS THE RECORD LENGTH FIELD

	CALL	HEXIN		; GET US TWO CHARACTERS INTO BC, CONVERT IT TO A BYTE <A>
	CALL	HXCHKSUM	; UPDATE HEX CHECK SUM

	LD	D,A		; LOAD RECORD LENGTH COUNT INTO D

	CALL	HEXIN		; GET NEXT TWO CHARACTERS, MEMORY LOAD ADDRESS <H>
	CALL	HXCHKSUM	; UPDATE HEX CHECK SUM

	LD	H,A		; PUT VALUE IN H REGISTER.

	CALL	HEXIN		; GET NEXT TWO CHARACTERS, MEMORY LOAD ADDRESS <L>
	CALL	HXCHKSUM	; UPDATE HEX CHECK SUM

	LD	L,A		; PUT VALUE IN L REGISTER.

	CALL	HEXIN		; GET NEXT TWO CHARACTERS, RECORD FIELD TYPE
	CALL	HXCHKSUM	; UPDATE HEX CHECK SUM

	CP	$01		; RECORD FIELD TYPE 00 IS DATA, 01 IS END OF FILE
	JR	NZ,HXLOAD2	; MUST BE THE END OF THAT FILE

	CALL	HEXIN		; GET NEXT TWO CHARACTERS, ASSEMBLE INTO BYTE
	CALL	HXCHKSUM	; UPDATE HEX CHECK SUM

	LD	A,E		; RECALL THE CHECKSUM BYTE
	AND	A		; IS IT ZERO?
        JP      Z,HXLOADEXIT	; MUST BE O.K., GO BACK FOR SOME MORE, ELSE
	JR	HXLOADERR	; CHECKSUMS DON'T ADD UP, ERROR OUT
		
HXLOAD2:
	LD	A,D		; RETRIEVE LINE CHARACTER COUNTER	
	AND	A		; ARE WE DONE WITH THIS LINE?
	JR	Z,HXLOAD3	; GET TWO MORE ASCII CHARACTERS, BUILD A BYTE AND CHECKSUM
	CALL	HEXIN		; GET NEXT TWO CHARS, CONVERT TO BYTE IN A, CHECKSUM IT
	CALL	HXCHKSUM	; UPDATE HEX CHECK SUM
	LD	(HL),A		; CHECKSUM OK, MOVE CONVERTED BYTE IN A TO MEMORY LOCATION
	INC	HL		; INCREMENT POINTER TO NEXT MEMORY LOCATION	
	DEC	D		; DECREMENT LINE CHARACTER COUNTER
	JR	HXLOAD2		; AND KEEP LOADING INTO MEMORY UNTIL LINE IS COMPLETE
		
HXLOAD3:
	CALL	HEXIN		; GET TWO CHARS, BUILD BYTE AND CHECKSUM
	CALL	HXCHKSUM	; UPDATE HEX CHECK SUM
	LD	A,E		; CHECK THE CHECKSUM VALUE
	AND	A		; IS IT ZERO?
	JR	Z,HXLOADAGAIN	; IF THE CHECKSUM IS STILL OK, CONTINUE ON, ELSE


HXLOADERR:
	LD	HL,TXT_CKSUMERR	; GET "CHECKSUM ERROR" MESSAGE
	CALL	MSG		; PRINT MESSAGE FROM (HL) AND TERMINATE THE LOAD
	JP	HXLOADEXIT	; RETURN TO PROMPT

HXCHKSUM:
	LD	C,A		; BUILD THE CHECKSUM
	LD	A,E
	SUB	C		; THE CHECKSUM SHOULD ALWAYS EQUAL ZERO WHEN CHECKED
	LD	E,A		; SAVE THE CHECKSUM BACK WHERE IT CAME FROM
	LD	A,C		; RETRIEVE THE BYTE AND GO BACK
	RET			; BACK TO CALLER

HXLOADAGAIN:
	CALL	KIN		; CATCH THE TRAILING CARRIAGE RETURN
	JP	HXLOAD0		; LOAD ANOTHER LINE OF DATA

HXLOADEXIT:
	CALL	KIN		; CATCH ANY STRAY TRAILING CHARACTERS
	JP	CHEK		; RETURN TO PROMPT


;****************************************************
;	MOVE MEMORY ROUTINE
;****************************************************

	;
	; MOVE COMMAND
	; MOVE MEMORY- MXXXX,YYYY,ZZZZ
	; MOVE MEMORY STARTING FROM XXXX TO YYYY TO LOCATION
	;	STARTING AT ZZZZ

MOVE:
	LD	C,03


; start GETNM replacement

				; get source starting memory location
	CALL	CRLF		;SHOW EXAMINE READY
	CALL	LDHL		;LOAD IN HL REGS.
	PUSH	HL		; push memory address on stack
	CALL	SPACE		; print space separator
			; get source ending memory location
	CALL	LDHL		;LOAD IN HL REGS.
	PUSH	HL		; push memory address on stack
	CALL	SPACE		; print space separator
				; get target starting memory location
	CALL	LDHL		;LOAD IN HL REGS.
	PUSH	HL		; push memory address on stack

; end GETNM replacement
	POP	DE	; DEST
	POP	BC	; SOURCE END
	POP	HL	; SOURCE
	PUSH    HL
	LD	A,L
	CPL
	LD	L,A
	LD	A,H
	CPL
	LD	H,A
	INC	HL
	ADD	HL,BC
	LD	C,L
	LD	B,H
	POP     HL        
	CALL    MOVE_LOOP
	JP	CHEK	; EXIT MOVE COMMAND ROUTINE
        ;
MOVE_LOOP:
	LD	A,(HL)	; FETCH
	LD	(DE),A	; DEPOSIT
	INC     HL	; BUMP  SOURCE
	INC     DE	; BUMP DEST
	DEC     BC	; DEC COUNT
	LD	A,C
	OR	B       
	JP	NZ,MOVE_LOOP	; TIL COUNT=0
	RET
               
;****************************************************
;	FILL MEMORY ROUTINE
;****************************************************


	;	FILL COMMAND
	;	FILL RAM WITH PATTERN- FXXXX,YYYY,DD
	;


FILL:
	LD	C,03

; start GETNM replacement

				; get fill starting memory location
	CALL	CRLF		;SHOW EXAMINE READY
	CALL	LDHL		;LOAD IN HL REGS.
	PUSH	HL		; push memory address on stack

	CALL	SPACE		; print space separator

				; get fill ending memory location
	CALL	LDHL		;LOAD IN HL REGS.
	PUSH	HL		; push memory address on stack

	CALL	SPACE		; print space separator

				; get target starting memory location
	CALL	HEXIN		;GET K.B. AND MAKE HEX
	LD	C,A		; put fill value in F so it is saved for later
	PUSH	BC		; push fill value byte on stack

; end GETNM replacement

	POP	BC	; BYTE
	POP	DE	; END
	POP	HL	; START
	LD	(HL),C
FILL_LOOP:
	LD	(HL),C
	INC     HL
	LD	A,E
	SUB     L
	LD	B,A
	LD	A,D
	SUB     H
	OR	B
	JP	NZ,FILL_LOOP
	JP	CHEK

;****************************************************
;	BOOT CP/M FROM ROM DRIVE ROUTINE
;****************************************************

	;
	;	BOOT CP/M FROM ROM DRIVE COMMAND
	;	C
	;


GOCPM:

	LD	HL,TXT_CPM		;point at text to say 'LOADING cpm
	CALL	MSG
	JP	$EA00		; CP/M COLD BOOT ENTRY POINT
;	JP	CHEK




;*******************************************************
;*	FLOPPY DISK BOOT FOLLOWS
;*******************************************************
;*	BOOTA BOOTS FROM DRIVE A, 8"
;*******************************************************
;*	BOOTB IS USED TO BOOT FROM DRIVE B
;*******************************************************

;BOOTB:
;	MVI	A,7DH
;	JMP	BOOTE
;BOOTA:
;	MVI	A,7EH
;BOOTE:
;	OUT	DCMD		;WRITE TO DRIVE CONTROL PORT

;RELOCATE BOOTSTRAP TO MAIN RAM
;AND JUMP TO IT

;	LXI	H,BOOTS
;	LXI	D,BSLOC
;	LXI	B,BSLEN
;	LDIR
;	JMP	BSLOC
	
;BOOTS:
;SHUT OFF SBC-200 RAM/ROM
	
;	MVI	A,2
;	OUT	7FH

;RETRY:
;..HOME:
;	MVI	A,0BH		;RESTORE THE DISC DRIVE
;	OUT	WCMD		;SEND TO CONTROLLER

;	MVI	B,200		;DELAY TILL VALID STATUS
;..WAIT:	DJNZ	..WAIT

;..NB:	IN	WSTAT		;GET STATUS
;	BIT	0,A		;BUSY (y/n)
;	JRNZ	..NB		;YES,KEEP WAITING

; NOW READ BOOT SECTOR

;	MVI	A,1		;START WITH SECTOR 1
;	OUT	WSECT		;SET SECTOR REG
;SECTOR:
;	LXI	H,BOOT		;WHERE SECTOR STARTS
;	MVI	A,88H		;ISSUE READ SECTOR COMMAND 
;	OUT	WCMD
;	LXI	B,0067H		;SET UP BC FOR PIO READ NEXT
;	INIR			;DO PIO SECTOR READ
;	INIR

;	MVI	B,200		;DELAY TILL VALID STATUS
;..WAIT:	DJNZ	..WAIT

;..NB:	IN	WSTAT		;GET STATUS
;	BIT	0,A		;BUSY (y/n)
;	JRNZ	..NB		;YES,KEEP WAITING
;	ANI	9DH		;WAS READ SUCCESSFUL(y/n)
;	JZ	BOOT		;GET SYSTEM
;	JMPR	RETRY

;	BSLEN	==	.-BOOTS



; BOOT FROM WITHIN ROM
; CPM MUST FIT BELOW ONBOARD RAM/ROM

;BOOTR2:
;	MVI	A,7DH
;	JMP	BOOTRE
;BOOTR1:
;	MVI	A,7EH
;BOOTRE:
;	OUT  	DCMD		;WRITE TO DRIVE CONTROL PORT
;	JMP	RETRY


;NEND:	.LOC	.


;	.RADIX	10


;	.IF1,[
;	.DEFINE LEFMEM[XX]=[


;	.PRNTX	/XX BYTES OF ROM LEFT/

;	]

;	LEFMEM	\(BEGIN+1024)-NEND

;	]



;	.END


;******************************************************************
;*	INIT_UART
;*	Function	: Init serial port  8250, 16C450, OR 16C550
;*			9600 Baud, 8 bit, 1 stopbit, 0 parity
;*	Output		: none
;*	call		: PAUSE
;*	tested		: 2 Feb 2007
;******************************************************************

INIT_UART:
	LD	A,$AA
	OUT	(UART7),A
	IN	A,(UART7)
	CP	$AA	; TEST IF YOU COULD STORE AA
	JP	NZ,INITUART_FAIL	; IF NOT, THE UART CAN'T BE FOUND
	LD	A,$55
	OUT	(UART7),A		; 
	IN	A,(UART7)
	CP	$55			; 
	JP	NZ,INITUART_FAIL
	LD	A,$01
	LD	(SER_ON),A
	JP	UART_OK

INITUART_FAIL:				; Handle if initialize UART fails
	LD	A,1
	LD	(UART_FAIL),A
	HALT


UART_OK:
	LD	A,0
	LD	(UART_FAIL),A		; UART OK FOUND
	LD	A,(SER_BAUD)
	CP	1
	JP	Z,UART1200
	CP	2
	JP	Z,UART2400
	CP	3
	JP	Z,UART4800
	CP	4
	JP	Z,UART9600
	CP	5
	JP	Z,UART19K2
	CP	6
	JP	Z,UART38K4
	CP	7
	JP	Z,UART57K6
	CP	8
	JP	Z,UART115K2
					; IF NOTHING IS DEFINED 1200 WILL BE USED..


UART1200:
	LD	A,80H
	OUT	(UART3),A		; SET DLAB FLAG
	LD	A,96			;  = 1,843,200 / ( 16 x 1200 )
	OUT	(UART0),A		;
	LD	A,00H
	OUT	(UART1),A		;
	LD	A,03H
	OUT	(UART3),A		; Set 8 bit data, 1 stopbit

;	LD	A,03H
;	OUT	(UART4),A		; Force DTR and RTS

	JP	INITRET			; 0 parity, reset DLAP FLAG
UART2400:
	LD	A,80H
	OUT	(UART3),A		; SET DLAB FLAG
	LD	A,48			; = 1,843,200 / ( 16 x 2400 )
	OUT	(UART0),A		;
	LD	A,00H
	OUT	(UART1),A		;
	LD	A,03H
	OUT	(UART3),A		; Set 8 bit data, 1 stopbit
	JP	INITRET			; 0 parity, reset DLAP FLAG
UART4800:
	LD	A,80H
	OUT	(UART3),A		; SET DLAB FLAG
	LD	A,24			; = 1,843,200 / ( 16 x 4800 )
	OUT	(UART0),A		;
	LD	A,00H
	OUT	(UART1),A		;
	LD	A,03H
	OUT	(UART3),A		; Set 8 bit data, 1 stopbit
	JP	INITRET			; 0 parity, reset DLAP FLAG
UART9600:	LD	A,80H
	OUT	(UART3),A		; SET DLAB FLAG
	LD	A,12			; = 1,843,200 / ( 16 x 9600 )
	OUT	(UART0),A		; Set BAUD rate til 9600
	LD	A,00H
	OUT	(UART1),A		; Set BAUD rate til 9600
	LD	A,03H
	OUT	(UART3),A		; Set 8 bit data, 1 stopbit
	JP	INITRET			; 0 parity, reset DLAP FLAG
UART19K2:	LD	A,80H
	OUT	(UART3),A		; SET DLAB FLAG
	LD	A,06			; = 1,843,200 / ( 16 x 19,200 )
	OUT	(UART0),A		;
	LD	A,0
	OUT	(UART1),A		;
	LD	A,3
	OUT	(UART3),A		; Set 8 bit data, 1 stopbit
	JP	INITRET			; 0 parity, reset DLAP FLAG
UART38K4:	LD	A,80H
	OUT	(UART3),A		; SET DLAB FLAG
	LD	A,03
	OUT	(UART0),A		; = 1,843,200 / ( 16 x 38,400 )
	LD	A,00H
	OUT	(UART1),A		;
	LD	A,03H
	OUT	(UART3),A		; Set 8 bit data, 1 stopbit
	JP	INITRET			; 0 parity, reset DLAP FLAG
UART57K6:	LD	A,80H
	OUT	(UART3),A		; SET DLAB FLAG
	LD	A,02
	OUT	(UART0),A		; = 1,843,200 / ( 16 x 57,600 )
	LD	A,00H
	OUT	(UART1),A		;
	LD	A,03H
	OUT	(UART3),A		; Set 8 bit data, 1 stopbit
	JP	INITRET			; 0 parity, reset DLAP FLAG
UART115K2:	LD	A,80H
	OUT	(UART3),A		; SET DLAB FLAG
	LD	A,01
	OUT	(UART0),A		; = 1,843,200 / ( 16 x 115,200 )
	LD	A,00H
	OUT	(UART1),A		;
	LD	A,03H
	OUT	(UART3),A		; Set 8 bit data, 1 stopbit
					; 0 parity, reset DLAP FLAG
INITRET:
	RET


;******************************************************************
;*	INIT_PIO
;*	Function	: Init parallel port >82C55<
;******************************************************************

INIT_PIO:
	LD	A,10011001B		; A= IN, B= OUT C= IN
	OUT	(PIO1CONT),A
	RET


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





;******************************************************************
;*	FILL_MEM
;*	Function	: fill memory with a value
;*      Input		: HL = start address block
;*			: BC = length of block
;			: A = value to fill with
;*	Uses		: DE, BC
;*	Output		:
;*	calls		: 
;*	tested		: 13 Feb 2007
;******************************************************************


FILL_MEM:

; This code snippet will show one method to fill a block
; of memory with a single data byte using Z80 assembly
; language.

;;--------------------------------------------------
; 	fills with value in A
					;; HL = start address of block
					;; DE = HL + 1
	ld	e,l
	ld	d,h
	inc	de
					;; initialise first byte of block
					;; with data byte (&00)
					;; with data byte in A
	ld	(hl),A
	
					;; BC = length of block in bytes
					;; HL+BC-1 = end address of block
					;; fill memory
	ldir
	RET				;; return to caller

;;--------------------------------------------------



;; For each iteration of the LDIR command:
;;
;; 1. This command will copy the byte from the memory 
;; address pointed to by HL to the memory address pointed to by DE.
;; i.e. (DE) = (HL).
;; 2. Then HL and DE will be incremented. BC will be decremented.
;;
;;
;; For the first byte:
;; 
;; HL = start
;; DE = start+1
;; BC = length
;; (HL)=0
;; 
;; For the second byte:
;; 
;; HL = start + 1 (initialised to 0 by the previous iteration)
;; DE = start + 2
;; BC = length - 1
;;
;; For the third byte:
;;
;; HL = start + 2 (initialised to 0 by the previous iteration)
;; DE = start + 3
;; BC = length - 2
;;
;; etc....


;******************************************************************
;*	INITIALIZE
;*	Function	: Master Initialize Function
;******************************************************************


INITIALIZE:

; initialize UART related functions and variables

	LD	A,0
	LD	(SER_ON),A	; Initialize "Serial On" flag
				; assume it is off until UART
				; is autodetected
	LD	A,1
	LD	(UART_FAIL),A	; Initialize "UART FAIL" flag
				; assume it has failed until UART
				; is autodetected as working
				; INIT AND TEST OF UART
				; ONLY CALL THIS IF YOU
				; HAVE THE UART MOUNTED..
	LD	A,$01		; specify baud rate 1200 bps (1200,8,None,1)
	LD	A,$04		; specify baud rate 9600 bps (9600,8,None,1)
	LD	A,$02		; specify baud rate 2400 bps 2400,8,none,1
	LD	A,$03		; specify baud rate 4800,8,none, 1
	LD	(SER_BAUD),A	; 
	CALL	INIT_UART	; WITH NO FLOW CONTROL on terminal!!

; turn on interrupts
	EI			; Start INT COUNTER

; initialize PIO and do LED RESET "Wake Up" routine
	CALL	INIT_PIO	; initialize the PIO 
	LD	A,0
	OUT	(PIO1B),A	; Turn ALL BITS OFF on PIO
	LD	BC,100		; 10ms pause
	CALL	PAUSE
	LD	A,255
	OUT	(PIO1B),A	; ALL BITS ON FOR 1 SEC..
	LD	BC,100		; 10ms pause
	CALL	PAUSE
	LD	A,0
	OUT	(PIO1B),A	; ALL BITS OFF
	LD	A,%00000000
	OUT	(MPCL_RAM),A		; reset RAM memory pager configuration latch to default
	LD	A,%00000000
	OUT	(MPCL_ROM),A		; reset ROM memory pager configuration latch to default
	LD	A,%10000000
	OUT	(MPCL_ROM),A		; ensure ROM is switched out
	LD	A,%00000000		; start RAM page counter in A at zero
	OUT	(MPCL_RAM),A		
	RET


FORMATRAM:
	LD	HL,TXT_FORMAT		;point at text to say ' formatting...
	CALL	MSG			;print command label
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
	CALL	FILL_MEM		; call memory fill subroutine
	INC	A			; select next memory page and change fill value
	CP	$0F			; have you filled $0E pages yet?
	JP	NZ,FORM_MEM_LOOP	; no, go initialize the next page
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
	CALL	FILL_MEM		; write the data block to TRACK 1, sectors $00-$40
; RESET MPCL latch to default CP/M with 64K setting
	LD	A,%00000000
	OUT	(MPCL_RAM),A		; reset memory pager configuration latch to default
					; default configuration is full 64K RAM and 32K ROM
					; switched out
	LD	A,%10000000
	OUT	(MPCL_ROM),A		; reset memory pager configuration latch to default
					; default configuration is full 64K RAM and 32K ROM
					; switched out
	JP	CHEK			; Jump back to beginning





;********************* RAM VARIABLES ************************************

INT_COUNTER:	.DS	1	; Interrupt-counter
COUNTER		.DS	1	; Cycle counter main loop
SER_ON:		.DS	1	; serial on/off
UART_FAIL:	.DS	1	; UART has failed detection flag
SER_BAUD:	.DS	1	; specify desired UART com rate in bps


;********************* TEXT STRINGS *************************************

TXT_HELLO:
	.BYTE " HELLO WORLD ",END

PROMPT:
	.BYTE	CR,LF,END

PROMPTA:
	.BYTE	CR,LF,'>',END

TXT_READY:
	.BYTE CR,LF
	.BYTE "N8VEM Single Board Computer "
	.BYTE "32K-1M EPROM & Permanent RAM",CR,LF
	.BYTE "CP/M drives are A and B",CR,LF
	.BYTE "B>FORMAT formats drive A ",CR,LF
	.BYTE "B>XMODEM R MYFILE.COM "
	.BYTE "to download files to A",CR,LF
	.BYTE "Add SUPERSUB.COM and "
	.BYTE "AUTOEXEC.SUB for auto run"
	.BYTE CR,LF,END

TXT_COMMAND:
	.BYTE CR,LF
	.BYTE "Unknown command"
	.BYTE END

TXT_CKSUMERR:
	.BYTE CR,LF
	.BYTE "Checksum error"
	.BYTE END

TXT_HELP:
	.BYTE CR,LF
	.BYTE "D XXXXH YYYYH Dump memory"
	.BYTE " from XXXX to YYYY",CR,LF
	.BYTE "E XXXXH Examine memory "
	.BYTE "location XXXX",CR,LF
	.BYTE "F XXXXH YYYYH ZZH Fill memory"
	.BYTE " from XXXX to YYYY with ZZ",CR,LF
	.BYTE "H Load intel hex format data",CR,LF
	.BYTE "I Input from port and "
	.BYTE "show hex data",CR,LF
	.BYTE "K echo keyboard input",CR,LF
	.BYTE "M XXXXH YYYYH ZZZZH move memory"
	.BYTE " block XXXX to YYYY to ZZZZ",CR,LF
	.BYTE "O Output to port hex data",CR,LF
	.BYTE "P Program ram starting from"
	.BYTE " current location",CR,LF
	.BYTE "R Run a program from "
	.BYTE "current location",CR,LF
	.BYTE "T Format RAM disk B "
	.BYTE " (format before first use)",CR,LF
	.BYTE "'ESCAPE' Stop current mode"
	.BYTE " and wait for new command",CR,LF
	.BYTE "C Boot CP/M from ROM drive",CR,LF
	.BYTE END

TXT_FORMAT:
	.BYTE CR,LF
	.BYTE "Formatting..."
	.BYTE END
TXT_CPM:
	.BYTE CR,LF
	.BYTE "Loading CPM..."
	.BYTE END

;********************* END OF PROGRAM ***********************************

;	.include ctxt001.asm		; YOU CAN INCLUDE OTHER ASM FILES AND USE-
					; THE SUB ROUTINES FROM THEM.
.text "\n\r  -END-OF-FILE-  \n\r"

.ORG	$FFFF
.BYTE	$FF
.END
