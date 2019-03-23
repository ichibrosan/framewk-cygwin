        title   $Id: testzout.asm,v 1.2 2011/03/25 09:01:21 doug Exp $
        subttl  COPR 2011 Douglas Goodall
;
; $Log: testzout.asm,v $
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

port	equ8	0E5

start	nop

	out	(port),a

	out	(c),a
	out	(c),b
	out	(c),c
	out	(c),d
	out	(c),e
	out	(c),h
	out	(c),l

	end	start
	 
