        title   $Id: testzsub.asm,v 1.2 2011/03/25 09:01:21 doug Exp $
        subttl  COPR 2011 Douglas Goodall
;
; $Log: testzsub.asm,v $
; Revision 1.2  2011/03/25 09:01:21  doug
; *** empty log message ***
;
; Revision 1.1  2011/03/25 08:26:35  doug
; Initial revision
;
;
        include gplstuff.inc


	proc	z80
	radix	hex
	org	100

start	nop
 
; sub (hl)
	sub	(hl)

backwd	nop
	nop
	nop
	nop

; sub (ix+d)
	sub	(ix+backwd)
	sub	(ix+forewd)

; sub (iy+d)
	sub	(iy+backwd)
	sub	(iy+forewd)

	nop
	nop
	nop
	nop

forewd	nop

; sub r
	sub	b
	sub	c
	sub	d
	sub	e
	sub	h
	sub	l	
	sub	a

; sub n
	sub	0E5

	end	start

