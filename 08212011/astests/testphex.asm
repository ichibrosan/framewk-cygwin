
        title   $Id: testphex.asm,v 1.2 2011/04/13 23:47:17 doug Exp $
        subttl  COPR 2011 Douglas Goodall
;
; $Log: testphex.asm,v $
; Revision 1.2  2011/04/13 23:47:17  doug
; working test of printhex functions
;
; Revision 1.1  2011/04/13 20:44:22  doug
; Initial revision
;
;
        include gplstuff.inc
	include	assemble.inc
	include	cpm80.inc

	radix	hex
	org	100

start	mvi	a,12
	call	prbyte

	mvi	c,conout
	mvi	e,0d
	call	bdos

	mvi	c,conout
	mvi	e,0a
	call	bdos

	mvi	c,term
	jmp	bdos

	include	printhex.inc

	end	start

