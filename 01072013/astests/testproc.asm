        title   $Id: testproc.asm,v 1.1 2011/04/13 19:53:46 doug Exp $
        subttl  COPR 2011 Douglas Goodall
;
; $Log: testproc.asm,v $
; Revision 1.1  2011/04/13 19:53:46  doug
; Initial revision
;
;
        include gplstuff.inc
	include	assemble.inc
	include	cpm80.inc

	radix	hex
	org	100

start	mvi	c,destbuf-srcbufr
	lxi	d,destbuf
	lxi	h,srcbufr
	proc	z80
	ldir
	proc	8085

	mvi	c,prt
	lxi	d,donemsg
	call	bdos

	mvi	c,TERM
	jmp	bdos

srcbufr	dstr	Hello World!!
destbuf	rb	destbuf-srcbufr
donemsg	dstr	Done with mem copy$

	end	start

	nop

	end

