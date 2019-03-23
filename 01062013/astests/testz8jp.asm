        title   $Id: testz8jp.asm,v 1.2 2011/03/25 09:01:21 doug Exp $
        subttl  COPR 2011 Douglas Goodall
;
; $Log: testz8jp.asm,v $
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

	jp	(hl)
	jp	(ix)
	jp	(iy)
	jp	z,start
	jp	c,start
	jp	p,start
	jp	m,start
	jp	nz,start
	jp	nc,start
	jp	po,start
	jp	pe,start
	jp	start
 
	end

