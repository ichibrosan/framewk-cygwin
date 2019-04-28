        title   $Id: testsyml.asm,v 1.2 2011/03/25 09:01:21 doug Exp $
        subttl  COPR 2011 Douglas Goodall
;
; $Log: testsyml.asm,v $
; Revision 1.2  2011/03/25 09:01:21  doug
; *** empty log message ***
;
; Revision 1.1  2011/03/25 08:26:35  doug
; Initial revision
;
;
        include gplstuff.inc


	radix	hex

test_s		dstr	Hello World!!
test_s4		dstr4	Hello World!!
test_sb		dstrb	Hello World!!
test_sz		dstrz	Hello World!!
test_u8		equ8	12
test_u16	equ16	1234
test_u32	equ32	12345678
test_u64	equ64	0123456789ABCDEF

	symlist	STRING
	symlist	U8
	symlist	U16
	symlist	U32
	symlist	U64

;---------------------------------------

	end

