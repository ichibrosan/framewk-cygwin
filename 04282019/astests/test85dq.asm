
        title   $Id: test85dq.asm,v 1.1 2011/04/03 05:20:36 doug Exp $
        subttl  COPR 2011 Douglas Goodall
;

; $Log: test85dq.asm,v $
; Revision 1.1  2011/04/03 05:20:36  doug
; Initial revision
;
;
        include gplstuff.inc

	dq	1
	dq	1,2
	dq	1,2,3
	dq	1,2,3,4

xyz	equ64	1

	dq	xyz

	end


