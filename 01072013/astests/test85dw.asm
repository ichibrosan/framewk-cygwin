
        title   $Id$
        subttl  COPR 2011 Douglas Goodall
;

; $Log$
;
        include gplstuff.inc

	radix	hex

	dw	1
	dw	1,2
	dw	1,2,3
	dw	1,2,3,4

word	equ	1234

	dw	word
	dw	word,word
	dw	word,word,word
	dw	word,word,word,word

	end


