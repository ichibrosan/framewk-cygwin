        title   $Id $
        subttl  COPR 2011 Douglas Goodall
;
; $Log: testmisc.asm,v $
; Revision 1.1  2011/04/03 05:20:36  doug
; Initial revision
;
;

	savesyms 1
        include gplstuff.inc

	proc	8085
	radix	hex

byte	equ8	12
word	equ16	1234
dword	equ32	12345678
qword	equ64	0123456789ABCDEF

	db	byte
	db	byte,byte
	db	byte,byte,byte
	db	byte,byte,byte,byte

	dw	word
	dw	word,word
	dw	word,word,word
	dw	word,word,word,word

	dd	dword
	dd	dword,dword
	dd	dword,dword,dword
	dd	dword,dword,dword,dword

	dq	qword
	dq	qword,qword
	dq	qword,qword,qword
	dq	qword,qword,qword,qword

	end

	
