        title   $Id: test.asm,v 1.2 2011/03/25 09:01:21 doug Exp $
        subttl  COPR 2011 Douglas Goodall
;
; $Log: test.asm,v $
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
start	nop
	end	start

The purpose of the test.asm program is to test the
basic setup including page characteristics, radix,
label storage, and end processing. Because this 
test is after the end  statement, the assembler
does not care about what is written here.


