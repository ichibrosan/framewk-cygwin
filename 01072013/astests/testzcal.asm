        title   $Id: testzcal.asm,v 1.2 2011/03/25 09:01:21 doug Exp $
        subttl  COPR 2011 Douglas Goodall
;
; $Log: testzcal.asm,v $
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

	call	z,start
	call	c,start
	call	p,start
	call	m,start
	call	nz,start
	call	nc,start
	call	po,start
	call	pe,start
	call	start
 
	end

