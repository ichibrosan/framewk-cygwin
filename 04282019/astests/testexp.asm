        title   $Id:$
        subttl  COPR 2011 Douglas Goodall
;
        include gplstuff.inc

	proc	8085
	radix	hex

	org	100

start	nop

	org	0D000
jcld	jmp	cold
jwrm	jmp	warm
jcout	jmp	conout

	org	0E000
cold	nop
	orgplus	10
warm	nop
	orgplus	10
conout	nop

	export	jcld	
	export	jwrm
	export	jcout
	export	cold
	export	warm
	export	conout

	end	start

