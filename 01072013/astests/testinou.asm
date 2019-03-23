        title   $Id: testinou.asm,v 1.2 2011/03/25 09:01:21 doug Exp $
        subttl  COPR 2011 Douglas Goodall
;
; $Log: testinou.asm,v $
; Revision 1.2  2011/03/25 09:01:21  doug
; *** empty log message ***
;
; Revision 1.1  2011/03/25 08:26:35  doug
; Initial revision
;
;
        include gplstuff.inc

 
; opcode binaries verified 2/12/2011 dwg - 

	radix	decimal

status	equ	16
control	equ	17

	in	status

	out	control
	
	end

