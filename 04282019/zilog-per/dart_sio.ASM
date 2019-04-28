; 10.01.2009 HR
; Assembler ASIDE 1.14
; c't 8504
; dart_sio_ct8504
; Testprogramm für die I/O-Karte in Z80-Mnemonics
;
BASE:	.EQU	000H		; 4 DIL-SCHALTER

CTC:	.EQU	BASE+00H	;
CTC0:	.EQU    BASE+0		; ZAEHLER 0
CTC1:	.EQU    BASE+1		; ZAEHLER 1
CTC2:	.EQU    BASE+2		; ZAEHLER 2
CTC3:	.EQU    BASE+3		; ZAEHLER 3

SIO:	.EQU    BASE+4H		;
SIOAD:	.EQU    SIO+0		; KANAL A DATEN
SIOBD:	.EQU    SIO+1		; KANAL B DATEN
SIOAC:	.EQU    SIO+2		; KANAL A CONT.
SIOBC:	.EQU    SIO+3		; KANAL B CONT.

PIO1:	.EQU    BASE+08H	;
PIO1A:	.EQU    PIO1+0		; PIO 1 A DATEN
PIO1B:	.EQU    PIO1+1		; PIO 1 B DATEN
PIO1AC:	.EQU    PIO1+2		; PIO 1 A CONT.
PIO1BC:	.EQU    PIO1+3		; PIO 1 B CONT.

PIO2:	.EQU    BASE+0CH	;
PIO2A:	.EQU    PIO2+0		; PIO 2 A DATEN
PIO2B:	.EQU    PIO2+1		; PIO 2 B DATEN
PIO2AC:	.EQU    PIO2+2		; PIO 2 A CONT.
PIO2BC:	.EQU    PIO2+3		; PIO 2 B CONT.

             .ORG 0100H         ; PROGRAMM FUER CP/M 80

START:

          LD     HL,(0000)
          INC    HL
          INC    HL
          INC    HL
          LD     DE,CONST
          LD     BC,00009
          LDIR

          JR     XXXX


UART		.EQU	$68		; BASE IO ADDRESS OF UART

CONST:	;CONSOLE STATUS, RETURN 0FFH IF CHARACTER READY, 00H IF NOT
	IN	A,(UART + $05)		; READ LINE STATUS REGISTER (UART5 = $68 + $05)
	AND	$01			; TEST IF DATA IN RECEIVE BUFFER
					; IS THERE A CHAR READY? 0=NO, 1=YES
	JP	Z,NOT_READY
	LD	A,$FF			; YES, PUT $FF IN A AND RETURN
NOT_READY:				; NO, LEAVE $00 IN A AND RETURN
	RET
;

CONIN:	;CONSOLE CHARACTER INTO REGISTER A

	CALL	CONST			; IS A CHAR READY TO BE READ FROM UART?
	CP	$00			;
	JP	Z,CONIN			; NO?  TRY AGAIN   
	IN	A,(UART)		; YES? READ THE CHAR FROM THE UART (UART0 = $68 + $00)
					; REGISTER AND PASS BACK TO USER
;	ANI	7FH			;STRIP PARITY BIT
	RET
;

CONOUT: ;CONSOLE CHARACTER OUTPUT FROM REGISTER C

CONOUT1:
	IN	A,(UART + $05)		; READ LINE STATUS REGISTER
	AND	$20			; TEST IF UART IS READY TO SEND
	JP	Z,CONOUT1		; IF NOT REPEAT

	LD	A,C			;GET TO ACCUMULATOR
	OUT	(UART),A		; THEN WRITE THE CHAR TO UART (UART0 = $68 + $00)
	RET

XXXX:
          CALL   INIT
;          EI

LOOP:
          IN     A,(PIO2B)    ; 7 AUSGABE PIO 2 B
          INC    A            ; ERZEUGE RECHTECKE
          AND    07FH         ; IM BINAER-CODE
          OUT    (PIO2B),A

          CALL   SIOIN        ; CHAR. VON SIO ?
          JR     Z,LOOP1      ; NEIN

          LD     C,A          ; CHAR. VON SIO AUF SCHIRM
          DI
          CALL   CONOUT       ;
          EI

LOOP1:
          CALL   CONST        ; CHAR. AUF KEYBOARD ?

          OR     A            ;
          JR     Z,LOOP       ; NEIN

          CALL   CONIN        ;
          CP     '.'          ; ABBRUCH ?
          JR     NZ,LOOP2     ; NEIN

          DI
          NOP
          NOP
          JP     0000

LOOP2:
          LD     C,A          ;
          CALL   SIOOUT       ; CHAR. VON KEYBOARD ZUM SIO
          JR     LOOP

SIOOUT:
          IN     A,(SIOBC)    ; STATUS LESEN
          BIT    2,A          ; TX SENDEPUFFER LEER ?
          JR     Z,SIOOUT     ; NEIN
          LD     A,A          ; CHAR.
          OUT    (SIOBD),A    ; SENDEN
          RET

SIOIN:
          IN     A,(SIOBC)    ; STATUS LESEN
          AND    00000001B    ; RX CHAR. VORHANDEN ?
          RET    Z            ; KEIN CHAR.
          IN     A,(SIOBD)    ;
          AND    01111111B    ; BIT 7 = 0
          RET

;==========================================================================


INIT:

          LD     HL,CTCIT     ; CTC 0 INITITALISIEREN
          CALL   INITX

          LD     HL,SIOIT     ; SIO INITITALISIEREN
          CALL   INITX

          LD     HL,PIO1T     ; PIO1 INITITALISIEREN
          CALL   INITX

          LD     HL,PIO2T     ; PIO2 INITITALISIEREN
          CALL   INITX

;          LD     A,HIGH INTV0 ; CPU INITITALISIEREN
;          LD     HL,INTV0
;          LD     A,H


          LD     A,INTV0/256
          LD     I,A
          IM     2

          EI                  ; ENABLE INTERRUPTS
          RETI                ; GGF PORT-BAUSTEINE AUS INTER. HOLEN

INITX:
          LD                  A,(HL)               ; BYTE-ANZAHL
          OR                  A
          RET                 Z
          LD                  B,A
          INC                 HL
          LD                  C,(HL)
          INC                 HL
          OTIR
          JR                  INITX

CTCIT:
          .DB                03,CTC0              ; 3 BYTE ZUM CTC0
          .DB                INTV8 & 0FFH         ; INT-VEKTOR
          .DB                10100111B            ; INT-ENABLE
                                                   ; RESET
                                                   ; ZEITGEBER / 256
                                                   ; ZEIT-KONST. FOLGT
          .DB                255                  ; ZEIT-KONST. 255

          .DB                02,CTC1              ; 2 BYTE ZUM CTC1
          .DB                00100111B            ; INT-DISABLE
                                                   ; RESET
                                                   ; ZEITGEBER / 256
                                                   ; ZEIT-KONST. FOLGT
          .DB                255                  ; ZEIT-KONST. 255

          .DB                0                    ; ENDE CTC-TABELLE

SIOIT:

          .DB                12,SIOAC             ; 11 BYTE ZUM SIO A
          .DB                00011000B            ; RESET
          .DB                12h,00000000B          ; REG2: INT.VEC. LEER and reset ext/stat
          .DB                04h,11000100B          ; REG4: TRANSMITTER X64 CLOCK
                                                   ; 1 STOPBIT NO PARITY
          .DB                11h,00000000B          ; REG1: ALLE INT. DISABLE and reset ext/stat
          .DB                03h,11000001B          ; REG3: 8 BIT/CHAR RX ENABLE
          .DB                05h,01101010B          ; REG5; RECIVER DTR=0 8 BIT/CHAR
                                                  ; TX ENABLE RTS=1
          .DB                10h                  ;RESET ext/stat int's AGAIN

          .DB                12,SIOBC             ; 11 BYTE ZUM SIO B
          .DB                00011000B            ; RESET
          .DB                12h,00000000B          ; REG2: INT.VECTER and reset ext/stat
          .DB                04h,11000100B          ; REG4: TRANSMITTER X64 CLOCK
                                                   ; 1 STOPBIT NO PARITY
          .DB                11h,00000000B          ; REG1: ALLE INT. DISABLE and reset ext/stat
          .DB                03h,11000001B          ; REG3: 8 BIT/CHAR RX ENABLE
          .DB                05h,01101010B          ; REG5; RECIVER DTR=0 8 BIT/CHAR
                                                  ; TX ENABLE RTS=1
          .DB                10h                  ;RESET ext/stat int's AGAIN


          .DB                0                     ; ENDE SIO-TABELLE

PIO1T:
          .DB               05,PIO1AC             ; 5 BYTE ZUM PIO 1 A CONTROL
          .DB               00000011B             ; DIS-INT
          .DB               01001111B             ; BETR.ART BYTE EINGABE
          .DB               01001111B             ; BETR.ART BYTE EINGABE
          .DB               11001111B             ; BETR.ART BIT EIN/AUSG.
          .DB               00000000B             ; ALLES AUSG.

          .DB               01,PIO1A              ; 1 BYTE ZUM PIO 1 B DATEN
          .DB               00000000B             ; DATEN "LOW"
          
          .DB               0                     ; ENDE PIO-1-TABELLE
          
PIO2T:
          .DB               05,PIO2AC             ; 5 BYTE ZUM PIO 2 CONTROL
          .DB               00000011B             ; DIS-INT
          .DB               01001111B             ; BETR.ART BYTE EINGABE
          .DB               01001111B             ; BETR.ART BYTE EINGABE
          .DB               11001111B             ; BETR.ART BIT EIN/AUSG.
          .DB               00000000B             ; ALLES AUSG.

          .DB               01,PIO2A              ; 1 BYTE ZUM PIO 2 A DATEN
          .DB               00000000B             ; DATEN "LOW"

          .DB               09,PIO2AC             ; 7 BYTE ZUM PIO 2 B CONTROL
          .DB               00000011B             ; DIS-INT
          .DB               INTVF & 0FFH          ; INT.-VECTOR
          .DB               01001111B             ; BETR.ART BYTE EINGABE
          .DB               01001111B             ; BETR.ART BYTE EINGABE
          .DB               11001111B             ; BETR.ART EIN/AUSG.
          .DB               10000000B             ; 1 EINGANG SONST ALLES AUSG.
          .DB               00110111B             ; DIS-INT / AND HIGH / INT-MASKE
          .DB               01111111B             ; BIT 7 MACHT INTERRUPT
          .DB               10000011B             ; INT-ENABLE

          .DB               01,PIO2B              ; 1 BYTE ZUM PIO 2 B DATEN
          .DB               00000000B             ; DATEN "LOW"

          .DB               0                     ; ENDE PIO-2-TABELLE

;==========================================================================

          .ORG                300H                  ; VECTOR-TAB. ADR.LOW: XXXX XXX0

INTV0:	
          .DW               RETIN                 ; SIO
INTV1:
          .DW               RETIN
INTV2:
          .DW               RETIN
INTV3:
          .DW               RETIN
INTV4:
          .DW               RETIN
INTV5:
          .DW               RETIN
INTV6:
          .DW               RETIN
INTV7:
          .DW               RETIN

                    
INTV8:
          .DW               FLAG0                 ; CTC
INTV9:
          .DW               FLAG1
INTVA:
          .DW               FLAG2
INTVB:
          .DW               FLAG3



INTVC:
          .DW               RETIN                 ; PIO 1
INTVD:
          .DW               RETIN


INTVE:
          .DW               RETIN                 ; PIO 2
INTVF:
          .DW               FLAG4


;==========================================================================

FLAG0:
          PUSH     AF
          PUSH     BC
          LD       C,'0'
          CALL     CONOUT
          POP      BC
          POP      AF
RETIN:
          EI
          RETI

FLAG1:
          PUSH     AF
          PUSH     BC
          LD       C,'1'
          CALL     CONOUT
          POP      BC
          POP      AF
          EI
          RETI

FLAG2:
          PUSH     AF
          PUSH     BC
          LD       C,'2'
          CALL     CONOUT
          POP      BC
          POP      AF
          EI
          RETI


FLAG3:
          PUSH     AF
          PUSH     BC
          LD       C,'3'
          CALL     CONOUT
          POP      BC
          POP      AF
          EI
          RETI


FLAG4:
          PUSH     AF
          PUSH     BC
          LD       C,'4'
          CALL     CONOUT
          POP      BC
          POP      AF
          EI
          RETI


          .END
