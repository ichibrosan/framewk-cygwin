        title   $Id: testdoll.asm,v 1.2 2011/03/25 09:01:21 doug Exp $
        subttl  COPR 2011 Douglas Goodall
;
; $Log: testdoll.asm,v $
; Revision 1.2  2011/03/25 09:01:21  doug
; *** empty log message ***
;
; Revision 1.1  2011/03/25 08:26:35  doug
; Initial revision
;
;
        include gplstuff.inc


	radix	hex
	org	100

	db	$1
	db	$12

	dw	$1
	dw	$12
	dw	$123
	dw	$1234

	end
 
