        title   $Id: testz8cp.asm,v 1.2 2011/03/25 09:01:21 doug Exp $
        subttl  COPR 2011 Douglas Goodall
;
; $Log: testz8cp.asm,v $
; Revision 1.2  2011/03/25 09:01:21  doug
; *** empty log message ***
;
; Revision 1.1  2011/03/25 08:26:35  doug
; Initial revision
;
;
        include gplstuff.inc



; The Z80 CP (compare) operation code has three 
; forms. The first is "cp <reg>", where <reg> can
; be A, B, C, D, E, H and L. The second form is
; "cp (hl)". The third form is an immediate mode
; where the parameter can be numeric or sumbolic.
; "cp <parm". This file tests all three forms.

	proc	z80
	radix	hex
value	equ	0E5
	org	100
start	cp	a
	cp	b
	cp	c
	cp	d
	cp	e
	cp	h
	cp	l
	cp	(hl)
	cp	value
	cp	7
	end	start
 
