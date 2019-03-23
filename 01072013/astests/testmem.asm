        title   $Id: testmem.asm,v 1.2 2011/03/25 09:01:21 doug Exp $
        subttl  COPR 2011 Douglas Goodall
;
; $Log: testmem.asm,v $
; Revision 1.2  2011/03/25 09:01:21  doug
; *** empty log message ***
;
; Revision 1.1  2011/03/25 08:26:35  doug
; Initial revision
;
;
        include gplstuff.inc


	include assemble.inc
	proc	8085
	radix	hex
	binary	TRUE	; enable output to memory.bin
	org	10

	dstr	ABCDEFGHIJKLMNOPQRSTUVWXYZ

	end

