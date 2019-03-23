        title   Salota 8C 2K at 0000-07FF
        subttl  COPR 2011 Douglas Goodall
	include	assemble.inc
	binary	true
	proc	8085
	radix	hex

	org	0
start	db	31		; ld sp,3FFDH
	dw	stktop
	jmp	main

	org	8
rst08	nop
	ret

	org	10
rst10	nop
	ret

	org	18
rst18	nop
	ret

	org	20
rst20	nop
	ret

	org	28
rst28	nop
	ret

	org	30
rst30	nop
	ret

	org	38
intvec	nop


	org	100
main	nop
	
	org	0700
	rb	0FD
stktop	db	0E5

	end

