        title   $Id: testz8jr.asm,v 1.2 2011/03/25 09:01:21 doug Exp $
        subttl  COPR 2011 Douglas Goodall
;
; $Log: testz8jr.asm,v $
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

backwd	nop

	nop
	nop
	nop
	nop

	jr	z,forewd
	jr	c,forewd
	jr	nz,forewd
	jr	nc,forewd

        jr      z,backwd
        jr      c,backwd
        jr      nz,backwd
        jr      nc,backwd

	jr	start

	nop
	nop
	nop
	nop

forewd	nop
 
	end

