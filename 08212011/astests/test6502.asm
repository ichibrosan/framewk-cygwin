        title   $Id: test6502.asm,v 1.2 2011/03/25 09:01:21 doug Exp $
        subttl  COPR 2011 Douglas Goodall
;
; $Log: test6502.asm,v $
; Revision 1.2  2011/03/25 09:01:21  doug
; *** empty log message ***
;
; Revision 1.1  2011/03/25 08:26:35  doug
; Initial revision
;
;
        include gplstuff.inc


; The purpose of this test is to verify 
; that the calculation of forward and 
; backward displacements are correct.

; When calculating branches a forward 
; branch of 6 skips the following 6 
; bytes so, effectively the program 
; counter points to the address that 
; is 8 bytes beyond the address of 
; the branch opcode; and a backward
; branch of $FA (256-6) goes to an 
; address 7 bytes before the branch 
; instruction

	proc	6502

	radix	hex
	org	100

	page

; test BPL instruction
backwd1	nop	; -7
	nop	; -6
	nop	; -5
	nop	; -4
	nop	; -3
	nop	; -2
	nop	; -1
;	bpl	backwd1
;	bpl	forewd1
	nop	; +1
	nop	; +2
	nop	; +3
	nop	; +4
	nop	; +5
	nop	; +6
forewd1	nop	; +7

	page

; test BMI instruction
backwd2	nop	; -7
        nop	; -6
        nop	; -5
        nop	; -4
        nop	; -3
        nop	; -2
        nop	; -1
        bmi     backwd2
        bmi     forewd2
        nop	; +1
        nop	; +2
        nop	; +3
        nop	; +4
        nop	; +5
	nop	; +6
forewd2	nop	; +7
	
	page

; test BVC instruction
backwd3 nop	; -7
        nop	; -6
        nop	; -5
        nop	; -4
        nop	; -3
        nop	; -2
        nop	; -1
        bvc     backwd3
        bvc     forewd3
        nop	; +1
        nop	; +2
        nop	; +3
        nop	; +4
        nop	; +5
	nop	; +6
forewd3 nop	; +7

	page

; test BVS instruction
backwd4 nop	; -7
        nop	; -6
        nop	; -5
        nop	; -4
        nop	; -3
        nop	; -2
        nop	; -1
	bvs	backwd4
	bvs	forewd4
        nop	; +1
        nop	; +2
        nop	; +3
        nop	; +4
        nop	; +5
	nop	; +6
forewd4	nop	; +7

	page

; test BCC instruction
backwd5 nop	; -7
        nop	; -6
        nop	; -5
        nop	; -4
        nop	; -3
        nop	; -2
        nop	; -1
        bcc     backwd5
        bcc     forewd5
        nop	; +1
        nop	; +2
        nop	; +3
        nop	; +4
        nop	; +5
	nop	; +6
forewd5 nop	; +7

	page

; test BCS instruction
backwd6 nop	; -7
        nop	; -6
        nop	; -5
        nop	; -4
        nop	; -3
        nop	; -2
        nop	; -1
        bcs     backwd6
        bcs     forewd6
        nop	; +1
        nop	; +2
        nop	; +3
        nop	; +4
        nop	; +5
	nop	; +6
forewd6 nop	; +7

	page

; test BNE instructon
backwd7 nop	; -7
        nop	; -6
        nop	; -5
        nop	; -4
        nop	; -3
        nop	; -2
        nop	; -1
        bne     backwd7
        bne     forewd7
        nop	; +1
        nop	; +2
        nop	; +3
        nop	; +4
        nop	; +5
	nop	; +6
forewd7 nop	; +7

	page

; test BEQ instruction
backwd8 nop	; -7
        nop	; -6
        nop	; -5
        nop	; -4
        nop	; -3
        nop	; -2
        nop	; -1
        beq     backwd8
        beq     forewd8
        nop	; +1
        nop	; +2
        nop	; +3
        nop	; +4
        nop	; +5
	nop	; +6
forewd8 nop	; +7

	end
 
