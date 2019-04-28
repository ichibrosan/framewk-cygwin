        title   $Id: hello85.asm,v 1.3 2011/04/14 15:18:43 doug Exp $
        subttl  COPR 2011 Douglas Goodall
;
; $Log: hello85.asm,v $
; Revision 1.3  2011/04/14 15:18:43  doug
; added E5 byte to check end of .com conversion
;
; Revision 1.2  2011/03/25 09:01:21  doug
; *** empty log message ***
;
; Revision 1.1  2011/03/25 08:26:35  doug
; Initial revision
;
;
        include gplstuff.inc

	proc	8085
	radix	decimal
	include	assemble.inc
	include	cpm80.inc

	binary	TRUE
	radix	hex

	org	100
	segment	code
start	lxi	sp,stktop
	mvi	c,prt
	lxi	d,msg
	call	bdos
	mvi	c,term
	jmp	bdos

	segment	data
msg	dstr	Hello World!!$

	segment	stack
	rw	64
stktop	db	0E5
	end	start

