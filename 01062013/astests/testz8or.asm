        title   $Id: testz8or.asm,v 1.2 2011/03/25 09:01:21 doug Exp $
        subttl  COPR 2011 Douglas Goodall
;
; $Log: testz8or.asm,v $
; Revision 1.2  2011/03/25 09:01:21  doug
; *** empty log message ***
;
; Revision 1.1  2011/03/25 08:26:35  doug
; Initial revision
;
;
        include gplstuff.inc


	include assemble.inc
	proc	z80
	radix	hex
	org	100

start	nop
 
; or (hl)
	or	(hl)

backwd	nop
	nop
	nop
	nop

; or (ix+d)
	or	(ix+backwd)
	or	(ix+forewd)

; or (iy+d)
	or	(iy+backwd)
	or	(iy+forewd)

	nop
	nop
	nop
	nop

forewd	nop

; or r
	or	b
	or	c
	or	d
	or	e
	or	h
	or	l	
	or	a

; or n
	or	0E5

	end	start

