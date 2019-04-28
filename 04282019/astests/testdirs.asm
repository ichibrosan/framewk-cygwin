	typesrc	1
	title   $Id: testdirs.asm,v 1.2 2011/04/03 05:25:48 doug Exp $
        subttl  COPR 2011 Douglas Goodall
;
; $Log: testdirs.asm,v $
; Revision 1.2  2011/04/03 05:25:48  doug
; test for multiple parms on db dw dd and dq and typesrc
;
; Revision 1.1  2011/04/03 05:20:36  doug
; Initial revision
;
;
	include	assemble.inc
	listincl FALSE
        include gplstuff.inc
	listincl TRUE
	include cpm80.inc

	; ask for binary file
	binary	 TRUE

	; save symbols
	savesyms TRUE

	; use 8085 opcodes
	proc	8085

	; default to hex for numeric literals
	radix	hex

byte	equ8	12
word	equ16	1234
dword	equ32	12345678
qword	equ64	0123456789ABCDEF

	; test the new support for multiple 
	;   parms in db, dw, dd and dq
	db	byte
	db	byte,byte
	db	byte,byte,byte
	db	byte,byte,byte,byte
	;
	dw	word
	dw	word,word
	dw	word,word,word
	dw	word,word,word,word
	;
	dd	dword
	dd	dword,dword
	dd	dword,dword,dword
	dd	dword,dword,dword,dword
	;
	dq	qword
	dq	qword,qword
	dq	qword,qword,qword
	dq	qword,qword,qword,qword


	end

	
