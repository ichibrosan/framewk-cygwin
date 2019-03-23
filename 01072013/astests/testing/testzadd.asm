        title   $Id: testzadd.asm,v 1.2 2011/03/25 09:01:21 doug Exp $
        subttl  COPR 2011 Douglas Goodall
;
; $Log: testzadd.asm,v $
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
 
; add (hl)
	add	(hl)

; add ix,pp
	add	ix,bc
	add	ix,de
	add	ix,ix
	add	ix,sp

; add iy,rr
	add	iy,bc
	add	iy,de
	add	iy,iy
	add	iy,sp

; add hl,ss
	add	hl,bc
	add	hl,de
	add	hl,hl
	add	hl,sp

backwd	nop
	nop
	nop
	nop

; add (ix+d)
	add	(ix+backwd)
	add	(ix+forewd)

; add (iy+d)
	add	(iy+backwd)
	add	(iy+forewd)

	nop
	nop
	nop
	nop

forewd	nop

; add r
	add	b
	add	c
	add	d
	add	e
	add	h
	add	l
	add	a

; add n
	add	0E5

	end	start

