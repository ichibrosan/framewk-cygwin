;
;	XMODEM.ASM V5.0, by Keith Petersen, W8SDZ
;		   (revised 6/8/82)
;
;	REMOTE CP/M - CP/M FILE TRANSFER PROGRAM
;  see below DEFDRV	.EQU	'A'	;DRIVE TO REC TO
;
;Based on MODEM.ASM V2.0, by Ward Christensen.
;This program is intended for use on remote CP/M
;systems where it is important that the initialization
;of the modem not be changed, such as when using
;the PMMIBYE program. The baud rate and number of bits
;remains the same as whatever was set previously.
;There is no disconnect, terminal or echo option.
;
;Updates/fixes (in reverse order to minimize reading time):
;
;6/8/82    Added file transfer logging  feature. Enabled  with
;		 the  equate  variable LOGCAL,  it uses  caller 
;		info   provided  by  the  RCPM  file   LASTCALR 
;		together with transferred file name,  size  and 
;		direction of transfer to append each successful 
;		transfer to new special file LOG.SYS.  The user 
;		area designation for LASTCALR must be specified 
; 		by the variable LASTUSR and file is expected to 
;		reside on the DEFDRV drive. The support library 
;		SEQIO.LIB(vrs >=2.2) and the MAC assembler  are 
;		needed   ONLY if LOGCAL is true.  If logging is 
;		not desired,  or you don't have MAC then LOGCAL 
;		may  be  set false and the ASM  assembler  will 
;		work.  See  SEQIO.LIB for documentation on  the 
;		support  code.  Also made mods to  file  length 
;		printout  to  give  times for  600  baud  (PMMI 
;		only). This is optional with the LSPEED equate. 
;		If  used,  the baud rate of caller must be made 
;		available  thru  location  MSPEED(by  the   BYE 
;		program).		     Jack Riley
;04/18/82 Corrected transfer time calculations. Added optional
;	  equate, VOUT for sector count display to
;	  console output. (Must be CRT type device)
;	  Changed modem data port equates into 2 distinct
;	  booleans to accomodate a wider variety of customized
;	  EXTMOD equated modems.
;	  Changed NOCOMR option on receive to  automatic
;	  renaming of  .COM extents to .OBJ. (Howard Booker)
;
;04/01/82 Added routine to ERASE any file not properly received
;	  (gets rid of all those damn 0K files) - thanks
;	  to Skip Hansen for this one. - BHK
;
;03/28/82 Added cancel facility - if first char received 
;	  when waiting for initial nak is control-X it will
;	  cancel sending (useful for when the time estimate
;	  is longer than you want to wait). - BHK
;
;03/22/82 Added calculation of estimated transmission time
;	  when sending a file - divide # sectors by ~ 8 sectors
;	  per minute transmission speed (at 300 baud) - BHK
;
;03/08/82 Added Bruce Wood's designated user and drive area
;         routines to the original ver. 46 which contained
;         the DCH modem updates which were first included
;         on 10/19/81.  Then renamed to ver. 48A to distinguish
;         from the first ver. 48.  (Bill Aten)
;
;01/06/82 Added code to implement designated user and drive
; 	  area to receive files on.  This was put in to
;	  make it easier to locate new programs and for drives
;	  that are write protected. This change will put the file
;	  being sent into the designated area and when done return
;	  to the orginal area.
;	  SEE SETAREA LABEL IN THE CONDITIONAL SECTION  (Bruce Wood)
;
;10/19/81 Corrected numerous 'IN MODCTL2' errors for the DC
;	  Hayes modem.  Added DC Hayes detection of framing
;	  errors, overrun errors, and parity errors (if
;	  parity is used) for the receive file routine.
;	  (Bill Aten)
;
;10/12/81 Added code to implement Cyclic Redundancy
;	  Checking for both receiving and sending files.
;	  The CRC can only be specified by the operator
;	  on the receive file option as a secondary
;	  option of 'C' (XMODEM RC FN.FT).  When CRC is
;	  in effect, an initial 'C' instead of a NAK will
;	  be sent to the sender to start things off.
;	  The 'C' will be the signal to the sender
;	  (hopefully a version of MODEM that implements
;	  this CRC convention) that CRC is in effect.
;	  CRC will then take the place of the checksum
;	  checking for data validity.  The CRC should
;	  make file transfers as far as data integrity is
;	  concerned better than 99.99% error free.  The
;	  crc macro, CRC120, was used to implement CRC
;	  in this program and its equivalent version of
;	  MODEM.  Acknowledgements and thanks to Paul
;	  Hansknecht who designed and wrote CRC120.
;
;07/01/81 REDID H8/H89 EQUATES TESTED PROGRAM USING BOTH
;	  SYSTEMS AND CHANGED VER TO 4.4    (AL OLANDER)
;
;06/28/81 INSTALL H8/H89 EQUATES AND CHANGE EXTERNAL
;	  MODEM EQUATES TO "EXTMOD". (L. SHIPINSKI)
;
;05/30/81 Added IF PMMI/ENDIF to RCVERR routine to eliminate
;	  'undefined symbol' error when set for DCH modem.
;	  (Dave Hardy)
;
;05/07/81 Changed signon revision number.
;	  Cleaned up file. (KBP)
;
;05/01/81 Added detection of framing errors, overrun
;	  errors, and parity errors (if parity is used)
;	  for the receive file routine.  This feature
;	  is only active for the PMMI modem, since I
;	  do not know what the modem status bits are
;	  for IDS and D.C. Hayes modems.  If there
;	  is one of the above errors, the line will
;	  be purged for that block and a NAK will be
;	  sent to the sender for that block.  This was
;	  added to help catch those transmission errors
;	  that are not always caught by the checksum.
;	  This error checking is in addition to the
;	  checksum routine. (John Mahr)
;
;02/17/81 Added test for "f2" tagged files in OPENOK
;	  for MP/M version 1.1 compatiblity, which
;	  doesn't allow Ctl-C or Ctl-S in "f1" tagged
;	  files. (Tim Nicholas)
;
;02/16/81 Added hex to file size display. Now reports
;	  size in both decimal and (xxxxH) hex. Thanks
;	  to Ben Bronson for the idea. (Tim Nicholas)
;
;02/15/81 Added a software timer to the carrier test
;	  added in SEND and RECV routines. This will
;	  now abort only if carrier is lost for a 
;	  period of 15 seconds. This is only essential
;	  for those using external modems with certain
;	  SIO's, but will provide the PMMI/DCH user
;	  faster recovery in a lost carrier situation
;	  as well. Approx 15 seconds plus 15 seconds
;	  in BYE.COM, compared to 3 minutes at 300
;	  baud with earlier revisions. Thanks to Ben
;	  Bronson for his aid in developing this
;	  revision. (Tim Nicholas)
;
;02/14/81 Corrected error in last update which read
;	  the incorrect port for PMMI in the added
;	  carrier test. (Tim Nicholas)
;	
;01/31/81 Added equates and code for a carrier test.
;	  Test performed in modem I/O routines. This
;	  is required since loss of carrier will go
;	  undetected by BYE.COM, if the loss occurs
;	  after a sucessful XMODEM signon, when using
;	  an external modem and SIO. (Tim Nicholas)
;
;01/17/81 Re-wrote routine to calculate file size so
;         that it works correctly on v2.X systems with
;         extent folding (non-zero extent mask). (BRR)
;
;12/06/80 Re-wrote routine to calculate file size,
;	  added decimal print of file size. (KBP)
;
;12/05/80 Corrected error in use of ext byte that pre-
;	  vented files greater than one extent from 
;	  being sent.     Ron Fowler
;
;12/03/80 Corrected file extent length display. Now
;	  reports correct number of records for files
;	  longer than one extent. Display is now
;	  double precision (xxxxH). Also made some
;	  cosmetic changes by re-arranging the equates.
;	  By Tim Nicholas
;
;10/28/80 Cleaned up file. (KBP)
;
;10/23/80 Expanded conditional assembly of NOCOM routines
;	  into NOCOMS, NOLBS, and NOCOMR equates, to allow
;	  separate conditional assembly of tests for sending
;	  .COM files, sending .??# files, and receiving .COM
;	  files, respectively.	(Dave Hardy)
;
;10/15/80 Added traps for ambiguous file name or
;	  none at all. (KBP)
;
;09/09/80 Added conditional assembly to prevent filetypes
;	  '.COM' or '.??#' from being sent to distant end
;	  and added conditional assembly of test for '.COM'
;	  filetype on receive as well. See 'NOCOM' below.
;	  Any filetype ending in '#' will not be sent by
;	  this program if 'NOCOM' is set to TRUE.  J.SEYMOUR
;29 Oct 2008 
;	Added packet send for wireless links - short delay after
;	30 bytes have been sent.  Search for N8VEM to find changes
;	fastclock disabled as using 3.68Mhz. ERRLIM changed 10 to 4 retries
;	 (either it works or it doesn't, and if it is unreliable then fix it!)
;        J Moxham 
;
;
;NOTE: If you add improvements or otherwise update
;this program, please modem a copy of the new file
;to "TECHNICAL CBBS" in Dearborn, Michigan - phone
;313-846-6127 (110, 300, 450 or 600 baud).  Use the
;filename XMODEM.NEW.	(KBP)
;
FALSE:	.EQU 0
TRUE:	.EQU ~FALSE
;
;-----------------------------------------------------
;	 --- Conditional Assembly Options ---	      ;
;------------------------------------------------------
;
STDCPM:	.EQU TRUE		; TRUE, IS STANDARD CP/M
ALTCPM:	.EQU FALSE		; TRUE, IS TRS-80 OR H8 W/O 0-ORG
;
PMMI:	.EQU FALSE		; TRUE, IS PMMI
DCH:	.EQU FALSE		; TRUE, IS D.C. HAYES
H8:	.EQU FALSE		; TRUE, IS H8/H89 W/INS8250 MODEM CHIP
EXTMOD:	.EQU TRUE		; TRUE, IS NONE OF THE ABOVE!
;
NOCOMS:	.EQU FALSE		; TRUE, NO .COM FILES SENT
NOLBS:	.EQU FALSE		; TRUE, NO .??# FILES SENT
NOCOMR:	.EQU FALSE		; TRUE, CHANGE.COM TO.OBJ ON RECEIVE
;
;FASTCLK .EQU	TRUE	;PUT TRUE HERE FOR 4 MHZ CLOCK
FASTCLK:.EQU FALSE		; false for the 3.68Mhz N8VEM
;
FRNTPNL:.EQU FALSE		; TO DISPLAY STATUS ON FRONT PANEL
PANEL:	.EQU 0FFH		; DEFAULT ADDRESS OF FRONT PANEL
;
SETAREA:.EQU TRUE		; TRUE, IF USING DESIGNATED AREA TO RECEIVE 
RECU:	.EQU 0			; USER AREA TO REC IN (NOT GREATER THAN 9)
DEFDRV:	.EQU 'A'		; DRIVE TO REC TO
;
;	FILE TRANSFER LOGGING OPTIONS	(J. Riley)
LOGCAL:	.EQU FALSE		; IF USING LOGGING OF XMODEM TRANSFERS
LASTUSR:.EQU 15			; USER AREA OF 'LASTCALR' FILE (IF 'LOGCAL' ONLY)
;
LSPEED:	.EQU FALSE		; REPORT DIFFERENCES IN BAUD RATES IN PRINTOUT
MSPEED:	.EQU 3EH		; LOCATION OF CURRENT BAUD RATE FACTOR(set by BYE)
;
VOUT:	.EQU 00000H		; ADR OF VIDEO DRIVER IF OPTIONAL SECTOR
				; COUNT TO CONSOLE, ELSE LEAVE AS 0000H
;
;
;------------------------------------------------------
;	     --- Modem Port Equates --- 	      ;
;------------------------------------------------------
;
	.IF PMMI
MODCTLP:.EQU 0C0H		; PMMI VALUES(base port addr)
MODSNDB:.EQU 1			; BIT TO TEST FOR SEND
MODSNDR:.EQU 1			; VALUE WHEN READY
MODRCVB:.EQU 2			; BIT TO TEST FOR RECEIVE
MODRCVR:.EQU 2			; VALUE WHEN READY
MODDCDB:.EQU 4			; CARRIER DETECT BIT
MODDCDA:.EQU 0			; VALUE WHEN ACTIVE
MODPARE:.EQU 08H		; VALUE FOR PARITY ERROR
MODOVRE:.EQU 10H		; VALUE FOR OVERRUN ERROR
MODFRME:.EQU 20H		; VALUE FOR FRAMING ERROR
MODDATP:.EQU MODCTLP+1		; DATA PORT, RECEIVE
MODDATO:.EQU MODCTLP+1		; DATA PORT, SEND
BAUDRP:	.EQU MODCTLP+2		; BAUD RATE OUTPUT/MODEM STATUS
B600:	.EQU 1AH		; FACTOR FOR B600 BAUD
MODCTL2:.EQU MODCTLP+3		; SECOND CTL PORT
	.ENDIF
;
	.IF H8
MODCTLP:.EQU 0DDH		; H8/H89 VALUES (LSR-LINE STATUS REG.)
MODSNDB:.EQU 20H		; TEST FOR SEND (LSR-THRE)
MODSNDR:.EQU 20H		; VALUE WHEN READY
MODRCVB:.EQU 01H		; TEST FOR RECIEVE (LSR-DR)
MODRCVR:.EQU 01H		; VALUE WHEN READY
MODDCDB:.EQU 20H		; CARRIER DETECT BIT (MSR-CTS)
MODDCDA:.EQU 20H		; VALUE WHEN ACTIVE
MODPARE:.EQU 04H		; VALUE FOR PARITY ERROR (LSR-PE)
MODOVRE:.EQU 02H		; VALUE FOR OVERRUN ERROR (LSR-OR)
MODFRME:.EQU 08H		; VALUE FOR FRAMING ERROE (LSR-FE)
MODDATP:.EQU 0D8H		; DATA PORT, RECIEVE
MODDATO:.EQU 0D8H		; DATA PORT, SEND
BAUDRP:	.EQU 0DDH		; BAUD RATE PORT (DALB IN LCR MUST=1)
MODCTL2:.EQU 0DEH		; MODEM STATUS REGISTER (MSR)
MODCTL1:.EQU 0DBH		; LINE CONTROL REGISTER (LCR)
	.ENDIF
;
	.IF DCH
MODCTLP:.EQU 82H		; D. C. HAYES VALUES
MODSNDB:.EQU 2			; BIT TO TEST FOR SEND
MODSNDR:.EQU 2			; VALUE WHEN READY
MODRCVB:.EQU 1			; BIT TO TEST FOR RECEIVE
MODRCVR:.EQU 1			; VALUE WHEN READY
MODDCDB:.EQU 40H		; CARRIER DETECT BIT
MODDCDA:.EQU 40H		; VALUE WHEN ACTIVE
MODPARE:.EQU 04H		; VALUE FOR PARITY ERROR
MODOVRE:.EQU 10H		; VALUE FOR OVERRUN ERROR
MODFRME:.EQU 08H		; VALUE FOR FRAMING ERROR
MODDATP:.EQU 80H		; DATA PORT IN PORT
MODDATO:.EQU 80H		; DATA OUT PORT
MODCTL2:.EQU 81H		; SECOND CTL PORT
	.ENDIF
;
;If you are using an external modem (not S-100 plug-in)
;change these equates for your modem port requirements
;
	.IF EXTMOD
MODCTLP:.EQU 06DH		; PUT YOUR MODEM STATUS PORT HERE
MODSNDB:.EQU 20H		; YOUR BIT TO TEST FOR SEND
MODSNDR:.EQU 20H		; YOUR VALUE WHEN READY
MODRCVB:.EQU 01H		; YOUR BIT TO TEST FOR RECEIVE
MODRCVR:.EQU 01H		; YOUR VALUE WHEN READY
MODDCDB:.EQU 02H		; CARRIER DETECT BIT		              *** DSR change status bit 
MODDCDA:.EQU 00H		; VALUE WHEN ACTIVE                    *** 0 = no change since 
MODDATP:.EQU 068H		; YOUR MODEM DATA IN PORT
MODDATO:.EQU 068H		; YOUR MODEM DATA OUT PORT
MODCTL2:.EQU 0C1H		; SECOND CONTROL/STATUS PORT.
	.ENDIF			; END OF EXTERNAL MODEM .EQUATES
;
;		--- End of Options ---
;------------------------------------------------------
;
ERRLIM:	.EQU 10			; MAX ALLOWABLE ERRORS (10 STANDARD)
;
;Define ASCII characters used
;
SOH:	.EQU 1			; START OF HEADER
EOT:	.EQU 4			; END OF TRANSMISSION
ACK:	.EQU 6			; ACKNOWLEDGE
NAK:	.EQU 15H		; NEG ACKNOWLEDGE
CRC:	.EQU 'C'		; CRC REQUEST CHARACTER
CAN:	.EQU 18H		; CONTROL-X FOR CANCEL
LF:	.EQU 10			; LINEFEED
CR:	.EQU 13			; CARRIAGE RETURN
; 
	.IF STDCPM
BASE:	.EQU 0			; CP/M BASE ADDRESS
	.ENDIF
;
	.IF ALTCPM
BASE:	.EQU 4200H		; ALTERNATE CP/M BASE ADDRESS
	.ENDIF
;
	.ORG BASE+100H
;
;
;Init private stack
BEGIN:	LD	HL,0		; HL=0
	ADD	HL,SP		; HL=STACK FROM CP/M
	LD	(STACK),HL	; ..SAVE IT
	LD	SP,STACK	; SP=MY STACK
;
	.IF SETAREA
	LD	E,0FFH		; Get the current user area	 a 01/06/82
	LD	C,USER		; A 01/06/82
	CALL	BDOS		; A 01/06/82
	LD	(OLDUSER),A	; Save user number here		 a 01/06/82
	LD	C,CURDRV	; Get the current drive		 a 01/06/82
	CALL	BDOS		; A 01/06/82
	LD	(OLDDRV),A	; Save drive here		 a 01/06/82
	.ENDIF
;
	CALL	ILPRT		; PRINT:
	.DB CR,LF
	.DB "XMODEM48 VER 5.0V"
	.DB " [CRC CAPABLE]",CR,LF,0
;
;GET OPTION
;
	LD	A,(FCB+2)	; SECONDARY OPTION?
	CP	'C'		; CRC CHECKING REQUESTED?
	JP	NZ,CHKOPTN	; NO, GO CHECK PRIMARY
	LD	A,(FCB+1)	; GET PRIMARY OPTION
	CP	'R'		; CRC VALID ONLY FOR RECEIVE
	JP	NZ,OPTNERR	; PRT MSG, ABORT
	XOR	A		; ZERO ACCUM
	LD	(CRCFLG),A	; TURN ON CRC FLAG
;
CHKOPTN:LD	A,(FCB+1)	; GET OPTION (S or R)
	PUSH	AF		; SAVE OPTION
;
;Move the filename from FCB2 to FCB1
;
	CALL	MOVEFCB
;
;Gobble up garbage chars from the line
;prior to receive or send
;
	IN	A,(MODDATP)
	IN	A,(MODDATP)
;
;Jump to appropriate function
;
	POP	AF		; GET OPTION
	.IF LOGCAL
	PUSH	AF		; BUT SAVE IT
	.ENDIF
;
	CP	'S'		; SEND..
	JP	Z,SENDFIL	; ..A FILE?
;
	CP	'R'		; RECEIVE..
	JP	Z,RCVFIL	; ..A FILE?
;
;Invalid option
;
OPTNERR:CALL	ERXIT		; EXIT W/ERROR
	.DB "++INVALID OPTION ON XMODEM "
	.DB "COMMAND++",CR,LF
	.DB "MUST BE S FOR SEND	; R or RC "
	.DB "FOR RECEIVE",CR,LF,'$'

	.IF LOGCAL
	MACLIB SEQIO22

BSIZE:	.EQU 80H
FILERR:	.SET EXIT
BUFFERS:.SET DBUF

;		THE FOLLOWING ALLOCATIONS ARE USED BY THE 'FILE' MACROS
DEFAULT$USER:
	.DB LASTUSR
CUR$USER:
	.DB 0FFH
DEFAULT$DISK:
	.DB DEFDRV-'A'
CUR$DISK:
	.DB 0FFH
PGSIZE:	.DW 0

LOGCALL:FILE INFILE,CALLER,,LASTCALR,,BSIZE,,PUBLIC,TRUE
	LD	A,RECU
	LD	(DEFAULT$USER),A
	FILE APPEND,LOG,,LOG,SYS,BSIZE,,PUBLIC,TRUE

	POP	AF		; GET OPTION
	PUT LOG			; PUT IT OUT TO LOG

	LD	A,(MSPEED)	; GET SPEED FACTOR
	CPL
	ADD	A,7EH		; MAGIC NUMBER FOR PMMI MODEM SO WE CAN
	PUT LOG			; PUT OUT A SINGLE LETTER CODE
	LD	A,(PGSIZE)	; NOW THE PROGRAM SIZE(IN MINUTES TRANSFER TIME)
	CALL	PNDEC
	LD	A,' '		; BLANK
	PUT LOG

;			LOG THE DRIVE AND USER AREA AS A PROMPT
	LD	A,(FCB)
	OR	A
	JP	NZ,WDRV
	LD	C,25
	CALL	@BDOS
	INC	A
WDRV:	ADD	A,'A'-1
	PUT LOG

	LD	C,32		; NOW THE USER AREA(AS DECIMAL NUMBER)
	LD	E,0FFH
	CALL	@BDOS
	CALL	PNDEC
	LD	A,'>'		; MAKE IT LOOK LIKE A PROMPT
	PUT LOG

	LD	HL,FCB+1	; NOW THE NAME OF THE FILE
	LD	B,11
	CALL	PUTSTR

	LD	A,' '		; BLANK
	PUT LOG

CLOOP:	GET CALLER		; AND THE CALLER
	CP	EOF
	JP	Z,QUIT
	PUT LOG
	JP	CLOOP

PNDEC:	CP	10		; TWO COLUMN DECIMAL FORMAT ROUTINE
	JP	C,ONE		; ONE OR TWO DIGITS TO AREA #?
	JP	TWO
ONE:	PUSH	AF
	LD	A,'0'
	PUT LOG
	POP	AF
TWO:	LD	H,0
	LD	L,A
	CALL	DECOT
	RET

DECOT:	PUSH	BC
	PUSH	DE
	PUSH	HL
	LD	BC,-10
	LD	DE,-1
;
DECOT2:	ADD	HL,BC
	INC	DE
	JP	C,DECOT2
	LD	BC,10
	ADD	HL,BC
	EX	DE,HL
	LD	A,H
	OR	L
	CALL	NZ,DECOT
	LD	A,E
	ADD	A,'0'
	PUT LOG
	POP	HL
	POP	DE
	POP	BC
	RET

PUTSTR:	LD	A,(HL)
	PUSH	HL
	PUSH	BC
	PUT LOG
	POP	BC
	POP	HL
	INC	HL
	DEC	B
	JP	NZ,PUTSTR
	RET

QUIT:	FINIS LOG
	JP	EXIT
	.ENDIF			; LOGCAL
;
;* * * * * * * * * * * * * * * * * * * * *
;*					*
;*	SENDFIL: SENDS A CP/M FILE	*
;*					*
;* * * * * * * * * * * * * * * * * * * * *
;
;The CP/M file specified in the XMODEM command
;is transferred over the phone to another
;computer running MODEM with the "R" (receive)
;option.  The data is sent one sector at a
;time with headers and checksums, and re-
;transmission on errors.  
;
SENDFIL:CALL	TRAP		; CHECK FOR NO NAME OR AMBIG. NAME
	CALL	CNREC		; COMPUTE # OF RECORDS.
	CALL	OPENFIL		; OPEN THE FILE
	LD	E,80		; WAIT 80 SEC..
	CALL	WAITNAK		; ..FOR INITIAL NAK
;
SENDLP:	CALL	RDSECT		; READ A SECTOR
	JP	C,SENDEOF	; SEND EOF IF DONE
	CALL	INCRSNO		; BUMP SECTOR #
	XOR	A		; ZERO ERROR..
	LD	(ERRCT),A	; ..COUNT
;
SENDRPT:CALL	SENDHDR		; SEND A HEADER
	CALL	SENDSEC		; SEND DATA SECTOR
	LD	A,(CRCFLG)	; GET CRC FLAG
	OR	A		; CRC IN EFFECT?
	CALL	Z,SENDCRC	; YES, SEND CRC
	CALL	NZ,SENDCKS	; NO, SEND CKSUM
	CALL	GETACK		; GET THE ACK
	JP	C,SENDRPT	; REPEAT IF NO ACK
	JP	SENDLP		; LOOP UNTIL EOF
;
;File sent, send EOT's
;
SENDEOF:LD	A,EOT		; SEND..
	CALL	SEND		; ..AN EOT	
	CALL	GETACK		; GET THE ACK       	
	JP	C,SENDEOF	; LOOP IF NO ACK
	JP	EXITLG		; ALL DONE
;
;* * * * * * * * * * * * * * * * * * * * *
;*					*
;*	RCVFIL: RECEIVE A FILE		*
;*					*
;* * * * * * * * * * * * * * * * * * * * *
;
;Receives a file in block format as sent
;by another person doing "MODEM S FN.FT".
;Can be invoked by 'XMODEM R FN.FT' or
;by 'XMODEM RC FN.FT' if CRC is to be used.
;
RCVFIL:	CALL	TRAP		; CHECK FOR NO NAME OR AMBIG. NAME
;
	.IF NOCOMR
	LD	HL,FCB+9	; POINT TO FILETYPE
	LD	A,'C'		; 1ST LETTER
	CP	(HL)		; IS IT C ?
	JP	NZ,CONTINU	; IF NOT, CONTINUE NORMALLY
	INC	HL		; GET 2ND LETTER
	LD	A,'O'		; 2ND LETTER
	CP	(HL)		; IS IT O ?
	JP	NZ,CONTINU	; IF NOT, CONTINUE NORMALLY
	INC	HL		; GET 3RD LETTER
	LD	A,'M'		; 3RD LETTER
	CP	(HL)		; IS IT M ?
	JP	NZ,CONTINU	; IF NOT, CONTINUE NORMALLY

	CALL	ILPRT		; PRINT RENAMING MESSAGE
	.DB "AUTO RENAMING FILETYPE TO '.OBJ' "
	.DB CR,LF,CR,LF,0
;
	LD	HL,OBJEXT
	LD	DE,FCB+9
	LD	B,3
ALTEXT:	LD	A,(HL)
	LD	(DE),A
	INC	HL
	INC	DE
	DEC	B
	JP	NZ,ALTEXT
	JP	CONTINU

OBJEXT:	.DB "OBJ"
	.ENDIF
;
CONTINU:CALL	CHEKFIL		; SEE IF FILE EXISTS
	CALL	MAKEFIL		; ..THEN MAKE NEW
	CALL	ILPRT		; PRINT:
;
	.IF SETAREA
	.DB "NOTE: FILE WILL BE "
	.DB "RECEIVED ON",CR,LF	; 	     a 01/06/81
	.DB "DRIVE ",DEFDRV," USER ",RECU+30H,CR,LF ; tell this .a 01/06/81
	.ENDIF
;
	.DB "FILE OPEN - READY TO RECEIVE",CR,LF,0
;
RCVLP:	CALL	RCVSECT		; GET A SECTOR
	JP	C,RCVEOT	; GOT EOT
	CALL	WRSECT		; WRITE THE SECTOR
	CALL	INCRSNO		; BUMP SECTOR #
	CALL	SENDACK		; ACK THE SECTOR

				; debug code
	PUSH	AF
	POP	AF
				; debug code

	JP	RCVLP		; LOOP UNTIL EOF
;
;Got EOT on sector - flush buffers, end
;
RCVEOT:	CALL	WRBLOCK		; WRITE THE LAST BLOCK
	CALL	SENDACK		; ACK THE SECTOR
	CALL	CLOSFIL		; CLOSE THE FILE
	JP	EXITLG		; ALL DONE
;
;* * * * * * * * * * * * * * * * * * * * *
;*					*
;*		SUBROUTINES		*
;*					*
;* * * * * * * * * * * * * * * * * * * * *
;
;---->	TRAP: Check for no file name or ambiguous name
;
TRAP:	LD	HL,FCB+1	; POINT TO FILE NAME
	LD	A,(HL)		; GET FIRST CHAR OF FILE NAME
	CP	' '		; ANY THERE?
	JP	NZ,ATRAP	; YES, CHECK FOR AMBIGOUS FILE NAME
	CALL	ERXIT		; PRINT MSG, EXIT
	.DB "++NO FILE NAME SPECIFIED++",CR,LF,'$'
;
ATRAP:	LD	B,11		; 11 CHARS TO CHECK
;
TRLOOP:	LD	A,(HL)		; GET CHAR FROM FCB
	CP	'?'		; AMBIGUOUS?
	JP	Z,TRERR		; YES, EXIT WITH ERROR MSG
	INC	HL		; POINT TO NEXT CHAR
	DEC	B		; ONE LESS TO GO
	JP	NZ,TRLOOP	; NOT DONE, CHECK SOME MORE
	RET			; NO AMBIGUOUS NAME, RETURN
;
TRERR:	CALL	ERXIT		; PRINT MSG, EXIT
	.DB "++CAN''T USE WILD "
	.DB "CARD OPTIONS++",CR,LF,'$'
;
;---->	RCVSECT: Receive a sector
;
;Returns with carry set if EOT received.
;
RCVSECT:XOR	A		; GET 0
	LD	(ERRCT),A	; INIT ERROR COUNT
;
RCVRPT:
	.IF PMMI | H8 | DCH
	XOR	A		; GET 0
	LD	(ERRCDE),A	; CLEAR RECEIVE ERROR CODE
	.ENDIF
;
	LD	B,10		; 10 SEC TIMEOUT
	CALL	RECV		; GET SOH/EOT
	JP	C,RCVSTOT	; TIMEOUT
;
	.IF PMMI | H8 | DCH
	CALL	RCVERR		; TRANS ERROR?
	JP	C,RCVSERR	; CARRY SET IF ERROR
	.ENDIF
;
	CP	SOH		; GET SOH?
	JP	Z,RCVSOH	; ..YES
;
;Earlier versions of MODEM program send some nulls -
;ignore them
;
	OR	A		; 00 FROM SPEED CHECK?
	JP	Z,RCVRPT	; YES, IGNORE IT
	CP	EOT		; END OF TRANSFER?
	SCF			; RETURN WITH CARRY..
	RET	Z		; ..SET IF EOT
;
;Didn't get SOH or EOT - 
;	-or-
;Didn't get valid header - purge the line,
;then send NAK.
;
RCVSERR:LD	B,1		; WAIT FOR 1 SEC..
	CALL	RECV		; ..WITH NO CHARS
	JP	NC,RCVSERR	; LOOP UNTIL SENDER DONE
	LD	A,(CRCFLG)	; GET CRC FLAG
	OR	A		; CRC IN EFFECT?
	LD	A,NAK		; PUT NAK IN ACCUM
	JP	NZ,RCVSER2	; NO, SEND THE NAK
	LD	A,(FIRSTIME)	; GET FIRST TIME SWITCH
	OR	A		; HAS FIRST SOH BEEN RECEIVED?
	LD	A,NAK		; PUT NAK IN ACCUM
	JP	Z,RCVSER2	; YES, THEN SEND NAK
	LD	A,CRC		; TELL SENDER CRC IS IN EFFECT
;
RCVSER2:CALL	SEND		; ..THE NAK or CRC request
	LD	A,(ERRCT)	; ABORT IF..
	INC	A		; ..WE HAVE REACHED..
	LD	(ERRCT),A	; ..THE ERROR..
	CP	ERRLIM		; ..LIMIT?
	JP	C,RCVRPT	; ..NO, TRY AGAIN
;
;10 errors in a row -
;
RCVSABT:CALL	CLOSFIL		; KEEP WHATEVER WE GOT
	CALL	ILPRT
	.DB "++UNABLE TO RECEIVE BLOCK "
	.DB "- ABORTING++",CR,LF,0
	CALL	DELFILE		; DELETE RECEIVED FILE			; v48c smh
	CALL	ILPRT		; PRINT SECOND HALF OF MESSAGE
	.DB "++INCOMPLETELY RECEIVED FILE "
	.DB "DELETED++",CR,LF,0
	JP	EXIT		; GIVE UP
;
;---->	DELFILE: Deletes the received file (used if receive aborts)
;							; v48c smh
DELFILE:LD	DE,FCB		; POINT TO FILE			; (whole routine)
	LD	C,ERASEF	; GET FUNCTION
	CALL	BDOS		; DELETE IT
	INC	A		; DELETE OK?
	RET	NZ		; ..YES, RETURN
	CALL	ERXIT		; ..NO, ABORT
	.DB "++CAN''T DELETE RECEIVED "
	.DB "FILE++",CR,LF,'$',0
;
;Timed out on receive
;
RCVSTOT:JP	RCVSERR		; BUMP ERR CT, ETC.
;
;---->RCVERR: Checks to see if framing error, overrun, or
;		parity error occurred.
;	1. Error code (ERRCDE) was set in recv routine
;	2. ERRCDE=0 for no errors, ERRCDE<>0 for errors
;	3. If there has been an error, this routine sets
;		the carry bit on.
;
	.IF PMMI | H8 | DCH
RCVERR:	PUSH	AF		; SAVE CHAR TRANSMITTED
	LD	A,(ERRCDE)	; GET RECEIVE ERR CODE
	AND	A		; IS IT ZERO?
	JP	Z,RCVERR2	; YES, NO ERROR
	POP	AF		; RESTORE CHAR TRANSMITTED
	SCF			; SET CARRY ON FOR ERROR
	RET
;
RCVERR2:POP	AF		; RESTORE CHAR TRANSMITTED
	OR	A		; CLEAR CARRY BIT
	RET
	.ENDIF
;
;Got SOH - get block #, block # complemented
;
RCVSOH:	XOR	A		; ZERO ACCUM
	LD	(FIRSTIME),A	; INDICATE FIRST SOH RECV'D
	LD	B,1		; TIMEOUT = 1 SEC
	CALL	RECV		; GET SECTOR
	JP	C,RCVSTOT	; GOT TIMEOUT
;
	.IF PMMI | H8 | DCH
	CALL	RCVERR		; TRANS ERROR?
	JP	C,RCVSERR	; CARRY SET IF ERROR
	.ENDIF
;
	LD	D,A		; D=BLK #
	LD	B,1		; TIMEOUT = 1 SEC
	CALL	RECV		; GET CMA'D SECT #
	JP	C,RCVSTOT	; TIMEOUT
;
	.IF PMMI | H8 | DCH
	CALL	RCVERR		; TRANS ERROR?
	JP	C,RCVSERR	; CARRY SET IF ERROR
	.ENDIF
;
	CPL			; CALC COMPLEMENT
	CP	D		; GOOD SECTOR #?
	JP	Z,RCVDATA	; YES, GET DATA
;
;Got bad sector #
;
	JP	RCVSERR		; BUMP ERROR CT.
;
RCVDATA:LD	A,D		; GET SECTOR #
	LD	(RCVSNO),A	; SAVE IT
	LD	C,0		; INIT CKSUM
	CALL	CLRCRC		; CLEAR CRC COUNTER
	LD	HL,BASE+80H	; POINT TO BUFFER
;
RCVCHR:	LD	B,1		; 1 SEC TIMEOUT
	CALL	RECV		; GET CHAR
	JP	C,RCVSTOT	; TIMEOUT
;
	.IF PMMI | H8 | DCH
	CALL	RCVERR		; TRANS ERROR?
	JP	C,RCVSERR	; CARRY SET IF ERROR
	.ENDIF
;
	LD	(HL),A		; STORE CHAR
	INC	L		; DONE?
	JP	NZ,RCVCHR	; NO, LOOP
	LD	A,(CRCFLG)	; GET CRC FLAG
	OR	A		; CRC IN EFFECT?
	JP	Z,RCVCRC	; YES, TO RECEIVE CRC
;
;Verify checksum
;
	LD	D,C		; SAVE CHECKSUM
	LD	B,1		; TIMEOUT LEN.
	CALL	RECV		; GET CHECKSUM
	JP	C,RCVSTOT	; TIMEOUT
;
	.IF PMMI | H8 | DCH
	CALL	RCVERR		; TRANS ERROR?
	JP	C,RCVSERR	; CARRY SET IF ERROR
	.ENDIF
;
	CP	D		; CHECKSUM OK?
	JP	NZ,RCVSERR	; NO, ERROR
;
;Got a sector, it's a duplicate if = previous,
;	or OK if = 1 + previous sector
;
CHKSNUM:LD	A,(RCVSNO)	; GET RECEIVED
	LD	B,A		; SAVE IT
	LD	A,(SECTNO)	; GET PREV
	CP	B		; PREV REPEATED?
	JP	Z,RECVACK	; ACK TO CATCH UP
	INC	A		; CALC NEXT SECTOR #
	CP	B		; MATCH?
	JP	NZ,ABORT	; NO MATCH - STOP SENDER, EXIT
	RET			; CARRY OFF - NO ERRORS
;
;---->	RCVCRC:	Receive the cyclic redundancy check
;		characters (2 bytes), and see if the crc
;		received matches the one calculated.
;		If they match, get next sector, else
;		send a NAK requesting the sector be
;		resent.
;
RCVCRC:	LD	E,2		; NUMBER OF BYTES TO RECEIVE
;
RCVCRC2:LD	B,1		; 1 SEC TIMEOUT
	CALL	RECV		; GET CRC BYTE
	JP	C,RCVSTOT	; TIMEOUT
;
	.IF PMMI | H8 | DCH
	CALL	RCVERR		; TRANSMISSION ERROR?
	JP	C,RCVSERR	; YES, IF CARRY IS ON
	.ENDIF
;
	DEC	E		; DECREMENT NUM OF BYTES
	JP	NZ,RCVCRC2	; GET BOTH BYTES
	CALL	CHKCRC		; CHECK RCVD CRC AGAINST CALC'D CRC
	OR	A		; IS CRC OKAY?
	JP	Z,CHKSNUM	; YES, GO CHECK SECTOR NUMBERS
	JP	RCVSERR		; GO CHECK ERROR LIMIT AND SEND NAK
;
;Previous sector repeated, due to the last ACK
;being garbaged.  ACK it so sender will catch up 
;
RECVACK:CALL	SENDACK		; SEND THE ACK,
	JP	RCVSECT		; GET NEXT BLOCK
;
;Send an ACK for the sector
;
SENDACK:LD	A,ACK		; GET ACK
	CALL	SEND		; ..AND SEND IT
	RET
;
;---->	SENDHDR: Send the sector header
;
;SEND: (SOH) (block #) (complemented block #)
;
SENDHDR:LD	A,SOH		; SEND..
	CALL	SEND		; ..SOH,
	LD	A,(SECTNO)	; THEN SEND..
	CALL	SEND		; ..SECTOR #
	LD	A,(SECTNO)	; THEN SECTOR #
	CPL			; ..COMPLEMENTED..
	CALL	SEND		; ..SECTOR #
	RET			; FROM SENDHDR
;
;---->	SENDSEC: Send the data sector
;
SENDSEC:LD	C,0		; INIT CKSUM
	CALL	CLRCRC		; CLEAR THE CRC COUNTER
	LD	HL,BASE+80H	; POINT TO BUFFER
;
SENDC:	LD	A,(HL)		; GET A CHAR
	CALL	SEND		; SEND IT
	INC	L		; POINT TO NEXT CHAR
	JP	NZ,SENDC	; LOOP IF <100H
	RET			; FROM SENDSEC
;
;---->	SENDCKS: Send the checksum
;
SENDCKS:LD	A,C		; SEND THE..
	CALL	SEND		; ..CHECKSUM
	RET			; FROM SENDCKS
;
;---->	SENDCRC: Send the two Cyclic Redundancy
;		 Check characters.  Call FINCRC
;		 to calc the CRC which will be in
;		 d,e regs upon return.
;
SENDCRC:CALL	FINCRC		; CALC THE CRC FOR THIS SECTOR
	LD	A,D		; PUT FIRST CRC BYTE IN ACCUM
	CALL	SEND		; SEND IT
	LD	A,E		; PUT SECOND CRC BYTE IN ACCUM
	CALL	SEND		; SEND IT
	XOR	A		; SET ZERO RETURN CODE
	RET
;
;---->	GETACK: Get the ACK on the sector
;
;Returns with carry clear if ACK received.
;If an ACK is not received, the error count
;is incremented, and if less than "ERRLIM",
;carry is set and control returns.  If the
;error count is at "ERRLIM", the program
;aborts.
;
GETACK:	LD	B,10		; WAIT 10 SECONDS MAX
	CALL	RECVDG		; RECV W/GARBAGE COLLECT
	JP	C,GETATOT	; TIMED OUT
	CP	ACK		; OK? (CARRY OFF IF =)
	RET	Z		; YES, RET FROM GETACK
;
;Timeout or error on ACK - bump error count
;
ACKERR:	LD	A,(ERRCT)	; GET COUNT
	INC	A		; BUMP IT
	LD	(ERRCT),A	; SAVE BACK
	CP	ERRLIM		; AT LIMIT?
	RET	C		; NOT AT LIMIT
;
;Reached error limit
;
CSABORT:CALL	ERXIT
	.DB "++CAN''T SEND SECTOR "
	.DB "- ABORTING++",CR,LF,'$'
;
;Timeout getting ACK
;
GETATOT:JP	ACKERR		; NO MSG
; 
ABORT:	LD	SP,STACK
;
ABORTL:	LD	B,1		; 1 SEC. W/O CHARS.
	CALL	RECV
	JP	NC,ABORTL	; LOOP UNTIL SENDER DONE
	LD	A,CAN		; CONTROL X
	CALL	SEND		; STOP SENDING END
;
ABORTW:	LD	B,1		; 1 SEC W/O CHARS.
	CALL	RECV
	JP	NC,ABORTW	; LOOP UNTIL SENDER DONE
	LD	A,' '		; GET A SPACE...
	CALL	SEND		; TO CLEAR OUT CONTROL X
	CALL	ERXIT		; EXIT WITH ABORT MSG
	.DB "XMODEM PROGRAM CANCELLED",CR,LF,'$'
;
;---->	INCRSNO: Increment sector #
;
INCRSNO:LD	A,(SECTNO)	; INCR..
	INC	A		; ..SECT..
	LD	(SECTNO),A	; ..NUMBER
	PUSH	HL
	LD	HL,VOUT		; CK FOR OPTIONAL COUNT TO CONSOLE
	LD	A,H
	OR	L
	JP	NZ,CONSEC
	POP	HL
	RET
;
CONSEC:	LD	A,CR
	CALL	VOUT
	LD	HL,(SECCNT)	; UPDATE TOTAL SECTOR COUNT
	INC	HL
	LD	(SECCNT),HL
	CALL	DECOUTX		; DISPLAY COUNT
	POP	HL
	RET
;
DECOUTX:PUSH	BC
	PUSH	DE
	PUSH	HL
	LD	BC,-10
	LD	DE,-1
;
DECOU2X:ADD	HL,BC
	INC	DE
	JP	C,DECOU2X
	LD	BC,10
	ADD	HL,BC
	EX	DE,HL
	LD	A,H
	OR	L
	CALL	NZ,DECOUTX
	LD	A,E
	ADD	A,'0'
	CALL	VOUT
	POP	HL
	POP	DE
	POP	BC
	RET
;
;---->	CHEKFIL: See if file exists
;
;If it exists, say use a different name.
;
CHEKFIL:
	.IF SETAREA
	CALL	RECAREA		; Set the designated area up 	a 01/06/81
	.ENDIF
;
	LD	DE,FCB		; POINT TO CTL BLOCK
	LD	C,SRCHF		; SEE IF IT..
	CALL	BDOS		; ..EXISTS
	INC	A		; FOUND?
	RET	Z		; ..NO, RETURN
	CALL	ERXIT		; EXIT, PRINT ERROR MESSAGE
	.DB "++FILE EXISTS - USE "
	.DB "A DIFFERENT NAME++"
	.DB CR,LF,'$'
;
;---->	MAKEFIL: Makes the file to be received
;
MAKEFIL:XOR	A		; SET EXT & REC # TO 0
	LD	(FCBEXT),A
	LD	(FCBSNO),A
	LD	DE,FCB		; POINT TO FCB
	LD	C,MAKE		; GET BDOS FNC
	CALL	BDOS		; TO THE MAKE
	INC	A		; FF=BAD?
	RET	NZ		; OPEN OK
;Directory full - can't make file
	CALL	ERXIT
	.DB "++ERROR - CAN''T MAKE FILE++",CR,LF
	.DB "DIRECTORY MUST BE FULL",CR,LF,'$'
;
;---->	CNREC: Computes record count, and saves it
;	       until successful file OPEN.
;
;LOOK UP THE FCB IN THE DIRECTORY
CNREC:	LD	A,'?'		; MATCH ALL EXTENTS
	LD	(FCBEXT),A
	LD	A,0FFH
	LD	(MAXEXT),A	; INIT MAX EXT NO.
	LD	C,SRCHF		; GET 'SEARCH FIRST' FNC
	LD	DE,FCB
	CALL	BDOS		; READ FIRST
	INC	A		; WERE THERE ANY?
	JP	NZ,SOME		; GOT SOME
	CALL	ERXIT
	.DB "++FILE NOT FOUND++$"
;
;READ MORE DIRECTORY ENTRIES
MOREDIR:LD	C,SRCHN		; SEARCH NEXT
	LD	DE,FCB
	CALL	BDOS		; READ DIR ENTRY
	INC	A		; CHECK FOR END (0FFH)
	JP	NZ,SOME		; NOT END OF DIR...PROCESS EXTENT
	LD	A,(MAXEXT)	; HIT END...GET HIGHEST EXTENT NO. SEEN
	LD	L,A		; WHICH GIVES EXTENT COUNT - 1
	LD	H,0
	LD	D,H
	LD	A,(RCNT)	; GET RECORD COUNT OF MAX EXTENT SEEN
	LD	E,A		; SAVE IT IN DE
	ADD	HL,HL
	ADD	HL,HL		; MULTIPLY # OF EXTENTS - 1
	ADD	HL,HL		; TIMES 128
	ADD	HL,HL
	ADD	HL,HL
	ADD	HL,HL
	ADD	HL,HL
	ADD	HL,DE		; ADD IN SIZE OF LAST EXTENT
	LD	(RCNT),HL	; SAVE TOTAL RECORD COUNT
	RET			; AND EXIT
;
;POINT TO DIRECTORY ENTRY 
SOME:	DEC	A		; UNDO PREV 'INR A'
	AND	3		; MAKE MODULUS 4
	ADD	A,A		; MULTIPLY...
	ADD	A,A		; ..BY 32 BECAUSE
	ADD	A,A		; ..EACH DIRECTORY
	ADD	A,A		; ..ENTRY IS 32
	ADD	A,A		; ..BYTES LONG
	LD	HL,BASE+80H	; POINT TO BUFFER
	ADD	A,L		; POINT TO ENTRY
	ADD	A,15		; OFFSET TO RECORD COUNT
	LD	L,A		; HL NOW POINTS TO REC COUNT
	LD	B,(HL)		; GET RECORD COUNT
	DEC	HL
	DEC	HL		; BACK DOWN TO EXTENT NUMBER
	DEC	HL
	LD	A,(MAXEXT)	; COMPARE WITH CURRENT MAX.
	OR	A		; IF NO MAX YET
	JP	M,BIGGER	; THEN SAVE RECORD COUNT ANYWAY
	CP	(HL)
	JP	NC,MOREDIR
;
BIGGER:	LD	A,B		; SAVE NEW RECORD COUNT
	LD	(RCNT),A
	LD	A,(HL)		; SAVE NEW MAX. EXTENT NO.
	LD	(MAXEXT),A
	JP	MOREDIR		; GO FIND MORE EXTENTS
;
;---->	OPENFIL: Opens the file to be sent
;
OPENFIL:XOR	A		; SET EXT & REC # TO 0 FOR PROPER OPEN
	LD	(FCBEXT),A
	LD	(FCBSNO),A
	LD	DE,FCB		; POINT TO FILE
	LD	C,OPEN		; GET FUNCTION
	CALL	BDOS		; OPEN IT
	INC	A		; OPEN OK?
	JP	NZ,OPENOK	; ..YES
	CALL	ERXIT		; ..NO, ABORT
	.DB "++OPEN ERROR++",CR,LF,'$'
;
;Check for distribution-protected file
;
OPENOK:	LD	A,(FCB+1)	; FIRST CHAR OF FILE NAME
	AND	80H		; CHECK BIT 7
	JP	NZ,OPENOT	; If on, file can't be sent.
	LD	A,(FCB+2)	; Also check "f2" for tag.
	AND	80H		; Is it set?
	JP	Z,OPENOK2	; If not, ok to send file.
;
OPENOT:	CALL	ERXIT		; EXIT W/MESSAGE
	.DB "++THIS FILE IS NOT FOR "
	.DB "DISTRIBUTION, SORRY++"
	.DB CR,LF,'$'
;
OPENOK2:.EQU $
;
	.IF NOLBS | NOCOMS	; CHECK FOR SEND RESTRICTIONS
	LD	HL,FCB+11
	LD	A,(HL)		; CHECK FOR PROTECT ATTR
	AND	7FH		; REMOVE CP/M 2.x ATTRS
	.ENDIF			; NOLBS OR NOCOMS
;
	.IF NOLBS		; DON'T ALLOW '#' TO BE SENT.
	CP	'#'		; CHK FOR '#' AS LAST FIRST
	JP	Z,OPENOT	; IF '#', CAN'T SEND, SHOW WHY
	.ENDIF			; NOLBS
;
	.IF NOCOMS		; DON'T ALLOW .COM TO BE SENT
	CP	'M'		; IF NOT, CHK FOR '.COM'
	JP	NZ,OPENOK3	; IF NOT, OK TO SEND
	DEC	HL
	LD	A,(HL)		; CHK NEXT CHAR
	AND	7FH		; STRIP ATTRIBUTES
	CP	'O'		; 'O'?
	JP	NZ,OPENOK3	; IF NOT, OK TO SEND
	DEC	HL
	LD	A,(HL)		; NOW CHK FIRST CHAR
	AND	7FH		; STRIP ATTRIBUTES
	CP	'C'		; 'C' AS IN '.COM'?
	JP	NZ,OPENOK3	; IF NOT, CONTINUE
	CALL	ERXIT		; EXIT W/MESSAGE
	.DB "++CAN''T SEND A .COM FILE++"
	.DB CR,LF,'$'
	.ENDIF			; NOCOMS
;
OPENOK3:CALL	ILPRT		; PRINT:
	.DB "FILE OPEN -  ",0	; v48b bhk
	LD	HL,(RCNT)	; Get record count.
	CALL	DECOUT		; PRINT DECIMAL NUMBER OF SECTORS
	CALL	ILPRT
	.DB " (",0
	CALL	DHXOUT		; Now print size in hex.
	CALL	ILPRT
	.DB " HEX) SECTORS",CR,LF ; v48b bhk
	.DB "(APPROXIMATELY ",0	; v48b bhk
	LD	HL,(RCNT)	; get # of sectors		; v48b bhk
	.IF LSPEED
	LD	A,(MSPEED)	; V50  JPR
	CP	B600		;  "
	PUSH	AF		;  "
	JP	NZ,S300		;  "
	XOR	A		; DIVIDE HL BY 2		   "
	LD	A,H		;  "
	RRA			;  "
	LD	H,A		;  "
	LD	A,L		;  "
	RRA			;  "
	LD	L,A		;  "

S300:	
	.ENDIF
	CALL	DIVHL14		; divide HL by 14 (sectors/min)	; v48b bhk
	PUSH	HL
	.IF LOGCAL
	LD	(PGSIZE),HL	; V50  JPR
	.ENDIF
	LD	H,0
	CALL	DECOUT		; print decimal # of minutes	; v48b bhk
	CALL	ILPRT		; v48b bhk
	.DB " MINS, ",0

	POP	HL
	LD	A,H		; REMAINDER X 4 = SECONDS
	RLCA
	RLCA
	LD	L,A
	LD	H,0
	CALL	DECOUT
	.IF LSPEED
	POP	AF		; V50 JPR
	JP	NZ,MS300
	CALL	ILPRT
	.DB " SECS TO SEND AT 600 BAUD).",CR,LF ; v48b bhk
	.DB "[CONTROL-X TO CANCEL.]",CR,LF,0 ; v48c bhk
	RET
MS300:	
	.ENDIF
	CALL	ILPRT
	.DB " SECS TO SEND AT 300 BAUD).",CR,LF ; v48b bhk
	.DB "[CONTROL-X TO CANCEL.]",CR,LF,0 ; v48c bhk
	RET
;
;---->  DIVHL14: Divides HL by 14, 
;	UPON EXIT: L=QUOTIENT,H=REMAINDER
;
DIVHL14:PUSH	BC
	LD	B,8		; SHIFT FACTOR TO B
	LD	C,14		; DIVISOR TO C
DIV2:	XOR	A		; clear carry flag and accumulator
	ADD	HL,HL
	LD	A,H
	SUB	C
	JP	M,DIV3		; DONT BORROW ON NEG RESULTS
	LD	H,A
	LD	A,L
	OR	1		; BORROW 1
	LD	L,A
DIV3:	DEC	B
	JP	NZ,DIV2
	POP	BC
	RET
;
;---->	CLOSFIL: Closes the received file
;
CLOSFIL:LD	DE,FCB		; POINT TO FILE
	LD	C,CLOSE		; GET FUNCTION
	CALL	BDOS		; CLOSE IT
	INC	A		; CLOSE OK?
	RET	NZ		; ..YES, RETURN
	CALL	ERXIT		; ..NO, ABORT
	.DB "++CAN''T CLOSE FILE++",CR,LF,'$'
;
;
;----> DECOUT: Decimal output routine
;
DECOUT:	PUSH	BC
	PUSH	DE
	PUSH	HL
	LD	BC,-10
	LD	DE,-1
;
DECOU2:	ADD	HL,BC
	INC	DE
	JP	C,DECOU2
	LD	BC,10
	ADD	HL,BC
	EX	DE,HL
	LD	A,H
	OR	L
	CALL	NZ,DECOUT
	LD	A,E
	ADD	A,'0'
	CALL	CTYPE
	POP	HL
	POP	DE
	POP	BC
	RET
;
;---->	DHXOUT: - double precision hex output routine.
;	Call with hex value in HL.
;
DHXOUT:	PUSH	HL		; Save H,L
	PUSH	AF		; Save A
	LD	A,H		; Get MS byte.
	CALL	HEXO		; Output hi order byte.
	LD	A,L		; Get LS byte.
	CALL	HEXO		; Output lo order byte.
	POP	AF		; Restore A
	POP	HL		; Restore H,L
	RET			; Return to caller.
;
;
;---->	RDSECT: Reads a sector
;
;For speed, this routine buffers up 16
;sectors at a time.
;
RDSECT:	LD	A,(SECINBF)	; GET # SECT IN BUFF.
	DEC	A		; DECREMENT..
	LD	(SECINBF),A	; ..IT
	JP	M,RDBLOCK	; EXHAUSTED?  NEED MORE.
	LD	HL,(SECPTR)	; GET POINTER
	LD	DE,BASE+80H	; TO DATA
	CALL	MOVE128		; MOVE TO BUFFER
	LD	(SECPTR),HL	; SAVE BUFFER POINTER
	RET			; FROM "READSEC"
;
;Buffer is empty - read in another block of 16
;
RDBLOCK:LD	A,(EOFLG)	; GED EOF FLAG
	CP	1		; IS IT SET?
	SCF			; TO SHOW EOF
	RET	Z		; GOT EOF
	LD	C,0		; SECTORS IN BLOCK
	LD	DE,DBUF		; TO DISK BUFFER
;
RDSECLP:PUSH	BC
	PUSH	DE
	LD	C,STDMA		; SET DMA..
	CALL	BDOS		; ..ADDR
	LD	DE,FCB
	LD	C,READ
	CALL	BDOS
	POP	DE
	POP	BC
	OR	A		; READ OK?
	JP	Z,RDSECOK	; YES
	DEC	A		; EOF?
	JP	Z,REOF		; GOT EOF
;
;Read error
;
	CALL	ERXIT
	.DB "++FILE READ ERROR++",CR,LF,'$'
;
RDSECOK:LD	HL,80H		; ADD LENGTH OF ONE SECTOR...
	ADD	HL,DE		; ...TO NEXT BUFF
	EX	DE,HL		; BUFF TO DE
	INC	C		; MORE SECTORS?
	LD	A,C		; GET COUNT
	CP	16		; DONE?
	JP	Z,RDBFULL	; ..YES, BUFF IS FULL
	JP	RDSECLP		; READ MORE
;
REOF:	LD	A,1
	LD	(EOFLG),A	; SET EOF FLAG
	LD	A,C
;
;Buffer is full, or got EOF
;
RDBFULL:LD	(SECINBF),A	; STORE SECTOR COUNT
	LD	HL,DBUF		; INIT BUFFER..
	LD	(SECPTR),HL	; ..POINTER
	LD	DE,BASE+80H	; RESET..
	LD	C,STDMA		; ..DMA..
	CALL	BDOS		; ..ADDR
	JP	RDSECT		; PASS SECT TO CALLER
;
;---->	WRSECT: Write a sector
;
;Writes the sector into a buffer.  When 16
;have been written, writes the block to disk.
;
;Entry point "WRBLOCK" flushes the buffer at EOF.
;
WRSECT:	LD	HL,(SECPTR)	; GET BUFF ADDR
	EX	DE,HL		; TO DE FOR MOVE
	LD	HL,BASE+80H	; FROM HERE
	CALL	MOVE128		; MOVE TO BUFFER
	EX	DE,HL		; SAVE NEXT..
	LD	(SECPTR),HL	; ..BLOCK POINTER
	LD	A,(SECINBF)	; BUMP THE..
	INC	A		; ..SECTOR #..
	LD	(SECINBF),A	; ..IN THE BUFF
	CP	16		; HAVE WE 16?
	RET	NZ		; NO, RETURN
;
;---->	WRBLOCK: Writes a block to disk
;
WRBLOCK:LD	A,(SECINBF)	; # SECT IN BUFFER
	OR	A		; 0 MEANS END OF FILE
	RET	Z		; NONE TO WRITE
	LD	C,A		; SAVE COUNT
	LD	DE,DBUF		; POINT TO DISK BUFF
;
DKWRLP:	PUSH	HL
	PUSH	DE
	PUSH	BC
	LD	C,STDMA		; SET DMA
	CALL	BDOS		; TO BUFFER
	LD	DE,FCB		; THEN WRITE
	LD	C,WRITE		; ..THE..
	CALL	BDOS		; ..BLOCK
	POP	BC
	POP	DE
	POP	HL
	OR	A
	JP	NZ,WRERR	; OOPS, ERROR
	LD	HL,80H		; LENGTH OF 1 SECT
	ADD	HL,DE		; HL= NEXT BUFF
	EX	DE,HL		; TO DE FOR SETDMA
	DEC	C		; MORE SECTORS?
	JP	NZ,DKWRLP	; ..YES, LOOP
	XOR	A		; GET A ZERO
	LD	(SECINBF),A	; RESET # OF SECTORS
	LD	HL,DBUF		; RESET BUFFER..
	LD	(SECPTR),HL	; ..POINTER
;
RSDMA:	LD	DE,BASE+80H	; RESET..
	LD	C,STDMA		; ..DMA..
	CALL	BDOS		; ..ADDR
	RET
;
WRERR:	CALL	RSDMA		; RESET DMA TO NORM.
	LD	C,CAN		; CANCEL..
	CALL	SEND		; ..SENDER
	CALL	ERXIT		; EXIT W/MSG:
	.DB "++ERROR WRITING FILE++",CR,LF,'$'
;
;---->	RECV: Receive a character
;
;Timeout time is in B, in seconds.  Entry via
;"RECVDG" deletes garbage characters on the
;line.	For example, having just sent a sector,
;calling RECVDG will delete any line-noise-induced
;characters "long" before the ACK/NAK would
;be received.
;
RECVDG:	.EQU $			; RECEIVE W/GARBAGE DELETE
	IN	A,(MODDATP)	; GET A CHAR
	IN	A,(MODDATP)	; ..TOTALLY PURGE UART
;
RECV:	PUSH	DE		; SAVE
;
	.IF FASTCLK		; 4MHZ?
	LD	A,B		; GET TIME REQUEST
	ADD	A,A		; DOUBLE IT
	LD	B,A		; NEW TIME IN B
	.ENDIF
;
MSEC:	LD	DE,50000	; 1 SEC DCR COUNT 
;
	.IF ~DCH
MWTI:	IN	A,(MODCTLP)	; CHECK STATUS
	.ENDIF
;
	.IF DCH
MWTI:	IN	A,(MODCTL2)	; CHECK STATUS
	.ENDIF
;
	.IF PMMI & FRNTPNL
	OUT	(PANEL),A	; DISPLAY STATUS ON PANEL LIGHTS
	.ENDIF
;
	AND	MODRCVB		; ISOLATE BIT
	CP	MODRCVR		; READY?
	JP	Z,MCHAR		; GOT CHAR
	DEC	E		; COUNT..
	JP	NZ,MWTI		; ..DOWN..
	DEC	D		; ..FOR..
	JP	NZ,MWTI		; ..TIMEOUT
	DEC	B		; MORE SECONDS?
	JP	NZ,MSEC		; YES, WAIT
;
;Test for the presence of carrier - if none, go to 
;CARCK and continue testing for 15 seconds. If carrier
;returns, continue. If is doesn't return, exit.
;
	.IF  H8 | DCH		;  was   .IF	EXTMOD | H8 | DCH
	IN	A,(MODCTL2)	; READ MODEM STATUS
	.ENDIF
;
	IN	A,(MODCTLP)	; READ MODEM STATUS       ; 	 read correct port
;
	.IF PMMI
	IN	A,(BAUDRP)	; READ MODEM STATUS
	.ENDIF
;
	.IF PMMI & FRNTPNL
	OUT	(PANEL),A	; DISPLAY STATUS ON PANEL LIGHTS
	.ENDIF
;
	AND	MODDCDB		; CARRIER DETECT MASK
	CP	MODDCDA		; IS IT STILL ON?
	CALL	NZ,CARCK	; IF NOT, TEST FOR 15 SECONDS
;
;Modem timed out receiving - but carrier still on.
;
	POP	DE		; RESTORE D,E
	SCF			; CARRY SHOWS TIMEOUT
	RET
;
;Got character from modem
;
MCHAR:
;Check to see if there was a framing error,
;overrun, or parity error.
;
	.IF PMMI | H8
	IN	A,(MODCTLP)	; GET MODEM STATUS
	.ENDIF
;
	.IF DCH
	IN	A,(MODCTL2)	; GET MODEM STATUS
	.ENDIF
;
	.IF PMMI | H8 | DCH
	LD	D,A		; SAVE STATUS
	AND	MODFRME		; FRAMING ERROR?
	CP	MODFRME
	JP	NZ,MCHAR2	; NO, CHECK FOR OVERRUN
	LD	A,(ERRCDE)	; GET RECV ERR CODE
	OR	MODFRME		; TURN ON RECV ERR CODE
	LD	(ERRCDE),A	; PUT IT BACK
;
MCHAR2:	LD	A,D		; RESTORE MODEM STATUS
	AND	MODOVRE		; OVERRUN?
	CP	MODOVRE
	JP	NZ,MCHAR3	; NO, CHECK FOR PARITY ERROR
	LD	A,(ERRCDE)
	OR	MODOVRE		; TURN ON RECV ERR CODE
	LD	(ERRCDE),A
;
MCHAR3:	LD	A,D		; RESTORE MODEM STATUS
	AND	MODPARE		; PARITY ERROR?
	CP	MODPARE
	JP	NZ,MCHAR4	; NO, GET DATA CHAR
	LD	A,(ERRCDE)
	OR	MODPARE
	LD	(ERRCDE),A
;
MCHAR4:
	.ENDIF			; PMMI OR H8 OR DCH
;
;Get data char
;
	IN	A,(MODDATP)	; READ THE CHAR
	POP	DE		; RESTORE DE
;
;Calc checksum and CRC
;
	PUSH	AF		; SAVE THE CHAR
	CALL	UPDCRC		; CALC CRC
	ADD	A,C		; ADD TO CHECKSUM
	LD	C,A		; SAVE CHECKSUM
	POP	AF		; RESTORE CHAR
	OR	A		; CARRY OFF: NO ERROR
	RET			; FROM "RECV"
;
;CARCK - common 15 second carrier test for RECV and
;SEND. If carrier returns within 15 seconds, normal
;program execution continues. Else, it will abort
;to CP/M via EXIT.
;
CARCK:	LD	E,150		; VALUE FOR 15 SECOND DELAY = 150 
;
CARCK1:	CALL	DELAY		; KILL .1 SECONDS
;
	.IF  H8 | DCH		;  WAS   .IF	EXTMOD | H8 | DCH
	IN	A,(MODCTL2)	; READ MODEM STATUS
	.ENDIF
;
	IN	A,(MODCTLP)	; READ MODEM STATUS       ; 	 read correct port
;
	.IF PMMI
	IN	A,(BAUDRP)	; READ MODEM STATUS
	.ENDIF
;
	.IF PMMI & FRNTPNL
	OUT	(PANEL),A	; DISPLAY STATUS
	.ENDIF
;
	
;
	AND	MODDCDB		; CARRIER DETECT MASK
	CP	MODDCDA		; IS IT STILL ON?
	RET	Z		; RETURN IF CARRIER ON
	DEC	E		; HAS 15 SECONDS EXPIRED?
	JP	NZ,CARCK1	; IF NOT, CONTINUE TESTING
	JP	EXIT		; ELSE, ABORT TO CP/M.
;
;DELAY - 100 millisecond delay.
;
DELAY:	PUSH	BC		; SAVE B,C
;
	.IF FASTCLK		; IF 4MHZ CLOCK
	LD	BC,16667	; VALUE FOR 100MS DELAY
	.ENDIF
;
	.IF ~FASTCLK
	LD	BC,8334		; VALUE FOR 100MS DELAY
	.ENDIF
;
DELAY2:	DEC	BC		; UPDATE COUNT
	LD	A,B		; GET MS BYTE
	OR	C		; COUNT = ZERO?
	JP	NZ,DELAY2	; IF NOT, CONTINUE
	POP	BC		; RESTORE B,C
	RET			; RETURN TO CARCK1.
;
;---->	SEND: Send a character to the modem
;
SEND:	PUSH	AF		; SAVE THE CHARACTER
	CALL	UPDCRC		; Calc the crc
	ADD	A,C		; CALC CKSUM
	LD	C,A		; SAVE CKSUM
;
	.IF ~DCH
SENDW:	IN	A,(MODCTLP)	; GET STATUS
	.ENDIF
;
	.IF DCH
SENDW:	IN	A,(MODCTL2)	; GET STATUS
	.ENDIF
;
	.IF PMMI & FRNTPNL
	OUT	(PANEL),A	; DISPLAY STATUS
	.ENDIF
;
	AND	MODSNDB		; ISOLATE READY BIT
	CP	MODSNDR		; READY?
	JP	Z,SENDR		; ..YES, GO SEND
;
;Xmit status not ready, so test for carrier before
;looping - if lost, go to CARCK and give it up to 15
;seconds to return. If it doesn't return abort via
;EXIT.
;
	PUSH	DE		; Save D,E
;
	.IF  H8 | DCH		;  was   .IF	EXTMOD | H8 | DCH
	IN	A,(MODCTL2)	; READ MODEM STATUS
	.ENDIF
;
	IN	A,(MODCTLP)	; READ MODEM STATUS       ; 	 read correct port
;
	.IF PMMI
	IN	A,(BAUDRP)	; READ MODEM STATUS
	.ENDIF
;
	.IF PMMI & FRNTPNL
	OUT	(PANEL),A	; DISPLAY STATUS
	.ENDIF
;
	AND	MODDCDB		; CARRIER DETECT MASK
	CP	MODDCDA		; IS IT STILL ON?
	CALL	NZ,CARCK	; IF NOT, CONTINUE TESTING IT
	POP	DE		; RESTORE D,E
	JP	SENDW		; ELSE, WAIT FOR XMIT READY.
;
;Xmit status ready, carrier still on - send the data.
;
SENDR:	POP	AF		; GET CHAR
	OUT	(MODDATP),A	; OUTPUT IT
	CALL	PACKET		; N8VEM delay every 30 bytes
	RET			; FROM "SEND"
;
;---->	WAITNAK: Waits for initial NAK
;
;To ensure no data is sent until the receiving
;program is ready, this routine waits for the
;first timeout-NAK or the letter 'C' for CRC
;from the receiver.  If CRC is in effect, then
;Cyclic Redundancy Checks are used instead of
;checksums.
;(E) contains the # of seconds to wait.
;
; If the first character received is a CAN (control-X)
; then the send will be aborted as though it had timed out.
; 04/01/82 BHK 
;
WAITNAK:LD	B,1		; TIMEOUT DELAY
	CALL	RECV		; DID WE GET..
	CP	NAK		; ..A NAK?
	RET	Z		; YES, SEND BLOCK
	CP	CRC		; CRC INDICATED?
	JP	Z,WAITCRC	; YES, GO PUT CRC IN EFFECT
	CP	CAN		; WAS IT A CANCEL (CONTROL-X)?		; v48c bhk
	JP	Z,ABORT		; YES, ABORT				; v48c bhk
	DEC	E		; 80 TRIES?
	JP	Z,ABORT		; YES, ABORT
	JP	WAITNAK		; NO, LOOP
;
;----> WAITCRC: Turn on CRC Flag
;
WAITCRC:XOR	A		; ZERO ACCUM
	LD	(CRCFLG),A	; TURN ON CRC OPT
	RET
;
;---->	MOVEFCB: Moves FCB(2) to FCB
;
;In order to make the XMODEM command 'natural',
;i.e. XMODEM SEND FILENAME (MODEM S FN.FT) rather
;than XMODEM FILENAME SEND (MODEM FN.FT S), this
;routine moves the filename from the second FCB
;to the first.
;
MOVEFCB:LD	HL,FCB+16	; FROM
	LD	DE,FCB		; TO
	LD	B,16		; LEN
	CALL	MOVE		; DO THE MOVE
	XOR	A		; GET 0
	LD	(FCBSNO),A	; ZERO SECTOR #
	LD	(FCBEXT),A	; ..AND EXTENT
	RET
;
CTYPE:	PUSH	BC		; SAVE..
	PUSH	DE		; ..ALL..
	PUSH	HL		; ..REGS
	LD	E,A		; CHAR TO E
	LD	C,WRCON		; GET BDOS FNC
	CALL	BDOS		; PRIN THE CHR
	POP	HL		; RESTORE..
	POP	DE		; ..ALL..
	POP	BC		; ..REGS
	RET			; FROM "CTYPE"
;
HEXO:	PUSH	AF		; SAVE FOR RIGHT DIGIT
	RRA			; RIGHT..
	RRA			; ..JUSTIFY..
	RRA			; ..LEFT..
	RRA			; ..DIGIT..
	CALL	NIBBL		; PRINT LEFT DIGIT
	POP	AF		; RESTORE RIGHT
;
NIBBL:	AND	0FH		; ISOLATE DIGIT
	CP	10		; IS IT <10?
	JP	C,ISNUM		; YES, NOT ALPHA
	ADD	A,7		; ADD ALPHA BIAS
;
ISNUM:	ADD	A,'0'		; MAKE PRINTABLE
	JP	CTYPE		; ..THEN TYPE IT
;
;---->	ILPRT: Inline print of message
;
;The call to ILPRT is followed by a message,
;binary 0 as the end.
;
ILPRT:	EX	(SP),HL		; SAVE HL, GET HL=MSG
;
ILPLP:	LD	A,(HL)		; GET CHAR
	OR	A		; END OF MSG?
	JP	Z,ILPRET	; ..YES, RETURN
	CALL	CTYPE		; TYPE THE MSG
	INC	HL		; TO NEXT CHAR
	JP	ILPLP		; LOOP
;
ILPRET:	EX	(SP),HL		; RESTORE HL
	RET			; PAST MSG
;
EXITLG:				; SPECIAL LOG CALLER EXIT
	.IF LOGCAL
	JP	LOGCALL
	.ENDIF
	JP	EXIT
;
;---->	ERXIT: Exit printing message following call
;
ERXIT:	POP	DE		; GET MESSAGE
	LD	C,PRINT		; GET BDOS FNC
	CALL	BDOS		; PRINT MESSAGE
;
EXIT:	LD	HL,(STACK)	; GET ORIGINAL STACK
	LD	SP,HL		; RESTORE IT
;
	.IF SETAREA
	CALL	RESTU		; restore old area user & drive ..a 01/06/81
	.ENDIF
;
	RET			; --EXIT-- TO CP/M
;
	.IF SETAREA
;
;------> RESTORE THE OLD USER AREA AND DRIVE FROM A RECEIVED FILE
;
RESTU:	LD	A,(OLDDRV)	; RESTORE THE OLD DRIVE		;a 01/06/81
	LD	E,A		; A 01/06/81
	CALL	RECDRX		; A 01/06/81
	LD	A,(OLDUSER)	; RESTORE THE OLD USER NUMBER	;a 01/06/81
	LD	E,A		; A 01/06/81
	JP	RECARE		; A 01/06/81
;
;--------> SET USER AREA TO RECEIVE FILE
RECAREA:CALL	RECDRV		; Ok set the drive to its place	;a 01/06/81
	LD	E,RECU		; Ok now set the user area	;a 01/06/81
RECARE:	LD	C,USER		; Tell bdos what we want to do	;a 01/06/81
	CALL	BDOS		; Do it				;a 01/06/81
	RET
;
RECDRV:	LD	E,DEFDRV-41H	; Make drive cp/m number		;a 01/06/81
RECDRX:	LD	C,SELDRV	; Tell bdos			;a 01/06/81
	CALL	BDOS		; Do it				;a 01/06/81
	RET			; Back				;a 01/06/81
	.ENDIF
;
;Move 128 characters
;
MOVE128:LD	B,128		; SET MOVE COUNT
;
;Move from (HL) to (DE) length in (B)
;
MOVE:	LD	A,(HL)		; GET A CHAR
	LD	(DE),A		; STORE IT
	INC	HL		; TO NEXT "FROM"
	INC	DE		; TO NEXT "TO"
	DEC	B		; MORE?
	JP	NZ,MOVE		; ..YES, LOOP
	RET			; ..NO, RETURN
;
;************************************************************************
;* CRCSUBS (Cyclic Redundancy Code Subroutines) version 1.20		*
;* 8080 Mnemonics							*
;*									*
;*     	These subroutines will compute and check a true 16-bit		*
;*	Cyclic Redundancy Code for a message of arbitrary length.	*
;*									*
;*	The  use  of this scheme will guarantee detection of all	*
;*	single and double bit errors, all  errors  with  an  odd	*
;*	number  of  error bits, all burst errors of length 16 or	*
;*	less, 99.9969% of all 17-bit error bursts, and  99.9984%	*
;*	of  all  possible  longer  error bursts.  (Ref: Computer	*
;*	Networks, Andrew S.  Tanenbaum, Prentiss-Hall, 1981)		*
;*									*
;*									*
;*	There are four entry points, which are used as follows:		*
;*									*
;*	CLRCRC - A call to this entry resets the CRC accumulator.	*
;*		 It must be called at the start of each message.	*
;*									*
;*		 Entry Parameters: None.				*
;*									*
;*		 Exit Conditions:  CRC accumulator cleared.		*
;*				   All registers preserved.		*
;*									*
;*									*
;*	UPDCRC - A call to this entry updates the CRC accumulator.	*
;*		 It must be called once for each byte in the		*
;*		 message for which the CRC is being calculated.		*
;*									*
;*		 Entry Parameters: (A) = a byte to be included		*
;*					 in the CRC calculation.	*
;*									*
;*		 Exit Conditions:  CRC accumulator updated.		*
;*				   All registers preserved.		*
;*									*
;*									*
;*	FINCRC - A call to this entry finishes the CRC calculation	*
;*		 for a message which is to be TRANSMITTED. It must	*
;*		 be called after the last byte of the message has	*
;*		 been passed thru UPDCRC. It returns the calculated	*
;*		 CRC bytes, which must be transmitted as the final	*
;*		 two bytes of the message (first D, then E).		*
;*									*
;*		 Entry Parameters: None.				*
;*									*
;*		 Exit Conditions:  (DE) = calculated CRC bytes.		*
;*				   All other registers preserved.	*
;*									*
;*									*
;*	CHKCRC - A call to this routine checks the CRC bytes of		*
;*		 a RECEIVED message and returns a code to indicate	*
;*		 whether the message was received correctly. It must	*
;*		 be called after the message AND the two CRC bytes	*
;*		 have been received AND passed thru UPDCRC.		*
;*									*
;*		 Entry Parameters: None.				*
;*									*
;*		 Exit Conditions:  (A) =  0 if message ok.		*
;*				   (A) = -1 if message garbled.		*
;*				   All other registers preserved.	*
;*									*
;************************************************************************
;*									*
;*	Designed & coded by Paul Hansknecht, June 13, 1981		*
;*									*
;*									*
;*	Copyright (c) 1981, Carpenter Associates			*
;*			    Box 451					*
;*			    Bloomfield Hills, MI 48013			*
;*			    313/855-3074				*
;*									*
;*	This program may be freely reproduced for non-profit use.	*
;*									*
;************************************************************************
;
;	ENTRY	CLRCRC,UPDCRC,FINCRC,CHKCRC
;
CLRCRC:	.EQU $			; Reset CRC Accumulator for a new message.
	PUSH	HL
	LD	HL,0
	LD	(CRCVAL),HL
	POP	HL
	RET
;
UPDCRC:	.EQU $			; Update CRC Accumulator using byte in (A).
	PUSH	AF
	PUSH	BC
	PUSH	HL
	LD	B,8
	LD	C,A
	LD	HL,(CRCVAL)
UPDLOOP:LD	A,C
	RLCA
	LD	C,A
	LD	A,L
	RLA
	LD	L,A
	LD	A,H
	RLA
	LD	H,A
	JP	NC,SKIPIT
	LD	A,H		; The generator is X^16 + X^12 + X^5 + 1
	XOR	10H		; as recommended by CCITT.
	LD	H,A		; An alternate generator which is often
	LD	A,L		; used in synchronous transmission protocols
	XOR	21H		; is X^16 + X^15 + X^2 + 1. This may be
	LD	L,A		; used by substituting XOR 80H for XOR 10H
SKIPIT:	DEC	B		; and XOR 05H for XOR 21H in the adjacent code.
	JP	NZ,UPDLOOP
	LD	(CRCVAL),HL
	POP	HL
	POP	BC
	POP	AF
	RET
;
FINCRC:	.EQU $			; Finish CRC calc for outbound message.
	PUSH	AF
	XOR	A
	CALL	UPDCRC
	CALL	UPDCRC
	PUSH	HL
	LD	HL,(CRCVAL)
	LD	D,H
	LD	E,L
	POP	HL
	POP	AF
	RET
;
CHKCRC:	.EQU $			; Check CRC bytes of received message.
	PUSH	HL
	LD	HL,(CRCVAL)
	LD	A,H
	OR	L
	POP	HL
	RET	Z
	LD	A,0FFH
	RET
; ***************** N8VEM code added Oct 2008 - add a delay after every 30 byte

PACKET:				; push then pop all registers
	PUSH	HL		; store previous value for HL
	PUSH	DE		; store DE
	PUSH	BC		; store BC
	PUSH	AF		; store AF
	LD	HL,OUTCNT	; count how many times have sent out the data - into HL
	LD	A,(HL)		; put the value in A
	INC	A		; a=a+1
	LD	(HL),A		; put it back
	SUB	30		; subtract 30
	JP	NZ,PACKET1	; if not zero then no delay
	LD	A,0		; reset counter back to 0
	LD	(HL),A		; and store it to memory
	LD	C,50		; delay variable try 50
	CALL	DELAYP
PACKET1:POP	AF		; restore AF
	POP	BC		; restore BC 
	POP	DE		; restore DE
	POP	HL		; restore HL
	RET

DELAYP:				; delay routine, pass value in C
				; now need to add similar packet delay to xmodem					
DELCON1:

	LD	A,255		; 255 small loop
DELCON2:
	SUB	1		; subtract 1
	CP	0		; DECREMENT
	JP	NZ,DELCON2
	LD	A,C		; get the next C
	SUB	1		; subtract 1	
	LD	C,A		; store it back to C
	CP	0		; is it 0?
	JP	NZ,DELCON1
	RET
; ***** end added code ****
;
;
CRCVAL:	.DW 0
;
;
;
;Temporary storage area
;
MAXEXT:	.DB 0			; HIGHEST EXTENT NO. SEEN IN FILE SIZE CALC.
RCNT:	.DW 0			; RECORD COUNT
RCVSNO:	.DB 0			; SECT # RECEIVED
SECTNO:	.DB 0			; CURRENT SECTOR NUMBER 
SECCNT:	.DW 0			; TOTAL SECTOR COUNT
ERRCT:	.DB 0			; ERROR COUNT
OLDUSER:.DB 0			; Save the org user number
OLDDRV:	.DB 0			; Save the org drive number
OUTCNT:	.DB 1			; reserve one byte for counter
;
	.IF PMMI | H8 | DCH
ERRCDE:	.DB 0			; RECEIVE ERROR CODE
	.ENDIF
;
CRCFLG:	.DB 'C'			; SET TO NULL IF CRC USED
FIRSTIME:
	.DB 1			; TURNED OFF AFTER FIRST SOH RECEIVED
;
;Following 3 used by disk buffering routines
EOFLG:	.DB 0			; EOF FLAG (1=TRUE)
SECPTR:	.DW DBUF
SECINBF:.DB 0			; # OF SECTORS IN BUFFER
	.DS 60			; STACK AREA
STACK:	.DS 2			; STACK POINTER
;
;16 sector disk buffer
;
DBUF:	.EQU $			; 16 SECTOR DISK BUFFER
;
;BDOS equates
;
RDCON:	.EQU 1
WRCON:	.EQU 2
PRINT:	.EQU 9
CONST:	.EQU 11			; CONSOLE STAT
SELDRV:	.EQU 14			; SELECT DRIVE
OPEN:	.EQU 15			; 0FFH = NOT FOUND
CLOSE:	.EQU 16			; 	"       "
SRCHF:	.EQU 17			; 	"       "
SRCHN:	.EQU 18			; 	"       "
ERASEF:	.EQU 19			; NO RET CODE
READ:	.EQU 20			; 0=OK, 1=EOF
WRITE:	.EQU 21			; 0=OK, 1=ERR, 2=?, 0FFH=NO DIR SPC
MAKE:	.EQU 22			; 0FFH=BAD
REN:	.EQU 23			; 0FFH=BAD
CURDRV:	.EQU 25			; GET CURRENT DRIVE
STDMA:	.EQU 26			; SET DMA
USER:	.EQU 32			; SET USER AREA TO RECEIVE FILE
BDOS:	.EQU BASE+5
FCB:	.EQU BASE+5CH		; SYSTEM FCB
FCBEXT:	.EQU FCB+12		; FILE EXTENT
FCBSNO:	.EQU FCB+32		; SECTOR #
FCB2:	.EQU BASE+6CH		; SECOND FCB
;

;	.org	$0CFF
;endbyte	.db	$FF

; Oct 15th deleted the above two lines so more compact

	.END
