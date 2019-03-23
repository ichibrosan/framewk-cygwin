        title   $Id: testaci.asm,v 1.2 2011/03/25 09:01:21 doug Exp $
        subttl  COPR 2011 Douglas Goodall
;
; $Log: testaci.asm,v $
; Revision 1.2  2011/03/25 09:01:21  doug
; *** empty log message ***
;
; Revision 1.1  2011/03/25 08:26:35  doug
; Initial revision
;
;
        include gplstuff.inc


	proc	8085

	radix	hex

	org	100

;	aci

	aci	0

	aci	9

;	aci	a
	
	aci	100

	aci	32767

	end
 
