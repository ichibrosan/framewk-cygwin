        title   $Id: testeval.asm,v 1.3 2011/04/03 05:20:36 doug Exp $
        subttl  COPR 2011 Douglas Goodall
;
; $Log: testeval.asm,v $
; Revision 1.3  2011/04/03 05:20:36  doug
; check back in, all is well
;
; Revision 1.2  2011/03/25 09:01:21  doug
; *** empty log message ***
;
; Revision 1.1  2011/03/25 08:26:35  doug
; Initial revision
;
;
        include gplstuff.inc


	include assemble.inc

one	equ	1


two	equ	2


five	equ	5 


sum8	db	one+two+five

	db	'A'

	db	'A','B'

	db	'A','B','C'+2

sum16	dw	one+two+five


sum32	dd	one+two+five


sum64	dq	one+two+five



	end
	
