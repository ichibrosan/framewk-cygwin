        title   $Id: testz8dw.asm,v 1.3 2011/03/25 09:01:21 doug Exp $
        subttl  COPR 2011 Douglas Goodall
;
; $Log: testz8dw.asm,v $
; Revision 1.3  2011/03/25 09:01:21  doug
; *** empty log message ***
;
; Revision 1.2  2011/03/25 08:48:52  doug
; *** empty log message ***
;
; Revision 1.1  2011/03/25 08:26:35  doug
; Initial revision
;
;
        include gplstuff.inc



	proc	z80
	include	assemble.inc

;	savesyms	TRUE

figrel	equ	1
figrev	equ	1
usrver	equ	0

	radix	hex
abl	equ	20
acr	equ	0D
adot	equ	2E
bell	equ	07
bsin	equ	7F
bsout	equ	08
dle	equ	10
lf	equ	0A
ff	equ	0C

em	equ	4000
nscr	equ	1
	radix	decimal
kbbuf	equ	128
	radix	hex
us	equ	40
rts	equ	0A0


_co	equ	kbbuf+4

	debug	TRUE
nbuf	equ	nscr*400/kbbuf
	debug	FALSE

buf1	equ	em-_co*nbuf
initr0	equ	buf1-us
inits0	equ	initr0-rts

; this is debug code
	dw	_co
	dw	nbuf
	dw	buf1
	dw	initr0
	dw	inits0
; end of debug code

	end

	page

	org	100
orig	nop
	jmp	cld
	nop
	jmp	wrm

here	equ	@
hereis	dw	here+2

	db	figrel
	db	figrev
	db	usrver
	db	0E
	dw	task-7
	dw	bsin
	dw	inir0

	dw	inits0
	dw	initr0
	dw	inits0
	dw	20
	dw	0
	dw	initdp
	dw	initdp
	xdw	forth+6

	dw	5
	dw	0B320

	page

bip	dw	0
;
tnext	lxi	h,bip
	mov	a,m
	cmp	c
	jnz	tnext1
	inx	h
	mov	a,m
	cmp	b
	jnz	tnext1
break	nop
	nop
	nop
tnext1	ldax	b
	inx	b
	mov	l,a
	jmp	next+3

dpush	push	d
hpush	push	h
next	ldax	b
	inx	b
	mov	l,a
	ldax	b
	inx	b
	mov	h,a
next1	mov	e,m
	inx	h
	mov	d,m
	xchg
	pchl

	page

dp0	db	83
	dstr4	LIT
	dw	0
lit	dw	lit+2
	ldax	b
	inx	b
	mov	l,a
	ldax	b
	inx	b
	mov	h,a
	jmp	hpush
;
	db	87
	dstr4	EXECUTE
	dw	lit-6
exec	dw	exec+2
	pop	h
	jmp	next1
;
	db	86
	dstr4	BRANCH
	dw	exec-0a
bran	dw	bran+2
bran1	mov	h,b
	mov	l,c
	mov	e,m

	page

	inx	h
	mov	d,m
	dcx	h
	dad	d
	mov	c,l
	mov	b,h
	jmp	next
;
	db	87
	dstr	0BRANCH
	dw	bran-9
zbran	dw	zbran+2
	pop	h
	mov	a,l
	ora	h
	jz	bran1
	inx	b
	inx	b
	jmp	next
;
	db	86
	dstr4	(LOOP)
	dw	zbran-0a
xloop	dw	xloop+2
	lxi	d,1
xloo1	lhld	rpp
	mov	a,m
	add	e
	mov	m,a
	mov	e,a
	inx	h
	mov	a,m
	adc	d
	mov	m,a
	inx	h
	inr	d
	dcr	d
	mov	d,a
	jm	xloo2
	mov	a,e
	sub	m
	mov	a,d
	inx	h
	sbb	m
	jmp	xloo3
xloo2	mov	a,m
	sub	e
	inx	h
	mov	a,m
	sbb	d
;
xloo3	jm	bran1
	inx	h
	shld	rpp

	page

	inx	b
	inx	b
	jmp	next
;
	db	87
	dstr4	(+LOOP)
	dw	xloop-9
xploo	dw	xploo+2
	pop	d
	jmp	xloo1
;
	db	84
	dstr4	(DO)
	dw	xploo-0a
xdo	dw	xdo+2
	lhld	rpp
	dcx	h
	dcx	h
	dcx	h
	dcx	h
	shld	rpp
	pop	d
	mov	m,e
	inx	h
	mov	m,d
	pop	d
	inx	h
	mov	m,e
	inx	h
	mov	m,d
	jmp	next
;
	db	81
	dstr4	I
	dw	xdo-7
ido	dw	ido+2
	lhld	rpp
	mov	e,m
	inx	h
	mov	d,m
	push	d
	jmp	next
;
	db	85
	dstr4	DIGIT
	dw	ido-4
digit	dw	digit+2
	pop	h
	pop	d
	mov	a,e
	sui	30
	jm	digi2

	page

	cpi	0a
	jm	digi1
	sui	7
	cpi	0a
	jm	digi2
;
digi1	cmp	l
	jp	digi2
;
	mov	e,a
	lxi	h,1
	jmp	dpush
;
digi2	mov	l,h
	jmp	hpush
;
	db	86
	dstr4	(FIND)
	dw	digit-8
pfind	dw	pfind+2
	pop	d
	push	h
	ldax	d
	xra	m
	ani	3f
	jnz	pfin4
;
pfin2	inx	h
	inx	d
	ldax	d
	xra	m
	add	a
	jnz	pfin3
	jnc	pfin2
	lxi	h,5
	dad	d

	xthl
;
pfin6	dcx	d
	ldax	d
	ora	a
	jp	pfin6
	mov	e,a
	mvi	d,0
	lxi	h,1
	jmp	dpush
;
pfin3	jc	pfin5
pfin4	inx	d
	ldax	d
	ora	a
	jp	pfin4
pfin5	inx	d
	xchg

	page

	mov	e,m
	inx	h
	mov	d,m
	mov	a,d
	ora	e
	jnz	pfin1
;
	pop	h
	lxi	h,0
	jmp	hpush
;
	db	87
	dstr4	ENCLOSE
	dw	pfind-9
encl	dw	encl+2
	pop	d
	pop	h
	push	h
	mov	a,e
	mov	d,a
	mvi	e,0ff	; -1
	dcx	h
;
encl1	inx	h
	inr	e
	cmp	m
	jz	encl1
;
	mvi	d,0
	push	d
	mov	d,a
	mov	a,m
	ana	a
	jnz	encl2
	mvi	d,0
	inr	e
	push	d
	jmp	next
;
encl2	mov	a,d
	inx	h
	inr	e
	cmp	m
	jz	encl4
	mov	a,m
	ana	a
	jnz	encl2
;
encl3	mvi	d,0
	push	d
	push	d
	jmp	next

	page

;
encl4	mvi	d,0
;
	push	d
	inr	E
;
	push	d
	jmp	next
;
	db	84
	dstr4	EMIT
	dw	encl-0A
emit	dw	docol
	dw	pemit
	dw	one
	dw	outt
	dw	pstor
	dw	semis
;
	db	83
	dstr4	KEY
	dw	emit-7
key	dw	key+2
	jmp	pkey
;
	db	89
	dstr4	?TERMINAL
	dw	key-6
qterm	dw	qterm+2
	lxi	h,0
	jmp	pqter
;
	db	82
	dstr4	CR
	xdw	qterm-0C
here	equ	$
cr	dw	here+2
	jmp	pcr
;
	db	85
	dstr4	CMOVE
	xdw	cr-5
here	equ	$
cmove	dw	here+2
	mov	l,c
	mov	h,b
	pop	b
	pop	d
	xthl
;
	jmp	cmov2
cmov1	mov	a,m
	inx	h
	stax	d
	inx	d

	page

	dcx	b
cmov2	mov	a,b
	ora	c
	jnz	cmov1
	pop	b
	jmp	next
;
	db	82
	dstr4	U*
	xdw	cmove-8
here	equ	$
ustar	xdw	here+2
	pop	d
	pop	h
	push	b
	mov     b,h
	mov	a,l
	call	mpyx
;
	push	h
	mov	h,a
	mov	a,b
	mov	b,h
	call	mpyx
;
	pop	d
	mov	c,d

	dad	b
	aci	0
	mov	d,l
	mov	l,h
	mov	h,a
	pop	b
	push	d
	jmp	hpush
;
mpyx	lxi	h,0
	mvi	c,8
mpyx1	dad	h
	ral
	jnc	mpyx2
	dad	d
	aci	0
mpyx2	dcr	c
	jnz	mpyx1
	ret
;
	db	82

	page

	dstr4	U/
	xdw	ustar-5
here	equ	$
uslas	xdw	here+2
	lxi	h,4
	dad	sp
	mov	e,m
	mov	m,c
	inx	h
	mov	d,m
	mov	m,b
	pop	b
	pop	h
	mov	a,l
	sub	c
	mov	a,h
	sbb	b
	jc	uslas1
	lxi	h,0FFFF
	lxi	d,0FFFF
	jmp	uslas7
	radix	decimal
uslas1	mvi	a,16
uslas2	dad	h
	ral
	xchg
	dad	h
	jnc	uslas3
	inx	d
	ana	a
uslas3	xchg
	rar
	push	psw
	jnc	uslas4
	mov	a,l
	sub	c
	mov	l,a
	mov	a,h
	sbb	b
	mov	h,a
	jmp	uslas5
uslas4	mov	a,l
	sub	c
	mov	l,a
	mov	a,h
	sbb	b
	mov	h,a
	jnc	uslas5
	dad	b
	dcx	d
uslas5	inx	d
uslas6	pop	psw
	dcr	a
	jnz	uslas2
uslas7	pop	b
	push	h
	push	d

	page

	radix	hex
	db	83
	dstr4	AND
	xdw	uslas-5
here	equ	$
andd	xdw	here+2
	pop	d
	pop	h
	mov	a,e
	ana	l
	mov	l,a
	mov	a,d
	ana	h
	mov	h,a
	jmp	hpush
;
	db	82
	dstr4	OR
	xdw	andd-6
here	equ	$
orr	xdw	here+2
	pop	d
	pop	h
	mov	a,e
	ora	l
	mov	l,a
	mov	a,d
	ora	h
	mov	h,a
	jmp	hpush
;
	db	83
	dstr4	XOR
	xdw	orr-5
here	equ	$
xorr	xdw	here+2
	pop	d
	pop	h
	mov	a,e
	xra	l
	mov	l,a
	mov	a,d
	xra	h
	mov	h,a
	jmp	hpush
;
	db	83
	dstr4	SP@
	xdw	xorr-6
here	equ	$
spat	xdw	here+2
	lxi	h,0
	dad	sp
	jmp	hpush
;

	page

	db	83
	dstr4	SP!
	xdw	spat-6
here	equ	$
spsto	xdw	here+2
	lhld	up
	lxi	d,6
	dad	d
	mov	e,m
	inx	h
	mov	d,m
	xchg
	sphl
	jmp	next
;
	db	83
	dstr4	RP@
	xdw	spsto-6
here	equ	$
rpat	xdw	here+2
	lhld	rpp
	jmp	hpush
;
	db	83
	dstr4	RP!
	xdw	rpat-6
here	equ	$
rpsto	xdw	here+2
	lhld	up
	lxi	d,8
	dad	d
	mov	e,m
	inx	h
	mov	d,m
	xchg
	shld	rpp
	jmp	next
;
	db	82
	dstr4	;S
	xdw	rpsto-6
here	equ	$
semis	dw	here+2
	lhld	rpp
	mov	c,m
	inx	h
	mov	b,m
	inx	h
	shld	rpp
	jmp	next
;
	db	85
	dstr4	LEAVE
	dw	semis-5
here	equ	$
leave	xdw	here+2

	page

	lhld	rpp
	mov	e,m
	inx	h
	mov	d,m
	inx	h
	mov	m,e
	inx	h
	mov	m,d
	jmp	next
;
	db	82
	dstr4	>R
	xdw	leave-8
here	equ	$
tor	xdw	here+2
	pop	d
	lhld	rpp
	dcx	h
	dcx	h
	shld	rpp
	mov	m,e
	inx	h
	mov	m,d
	jmp	next
;
	db	82
	dstr4	R>
	xdw	tor-5
here	equ	$
fromr	equ	here+2
	lhld	rpp
	mov	e,m
	inx	h
	mov	d,m
	inx	h
	shld	rpp
	push	d
	jmp	next
;
	db	81
	dstr4	R
	
	xdw	fromr-5
here	equ	$
rr	xdw	here+2
;
	db	82
	dstr	0=
	xdw	rr-4
here	equ	$
zequ	xdw	here+2
	pop	h
	mov	a,l
	ora	h
	lxi	h,0
	jnz	zequ1
	inx	h
zequ1	jmp	hpush

	page

;
	db	82
	dstr4	0<
	dw	zequ-5
here	equ	$
zless	xdw	here+2
	pop	h
	dad	d
	lxi	h,0
	jnc	zles1
	inx	h
zles1	jmp	hpush
;
	db	81
	dstr4	+
	xdw	zless-5
here	equ	$
plus	xdw	here+2
	pop	d
	pop	h
	dad	d
	jmp	hpush
;
	db	82
	dstr4	D+
	xdw	plus-4
here	equ	$
dplus	xdw	here+2
	lxi	h,6
	dad	sp
	mov	e,m
	mov	m,c
	inx	h
	mov	d,m
	mov	m,b
	pop	b
	pop	h
	dad	d
	xchg
	pop	h
	mov	a,l
	adc	c
	mov	l,a
	mov	a,h
	adc	b
	mov	h,a
	pop	b
	push	d
	jmp	hpush
;
	db	85
	dstr4	MINUS
	xdw	dplus-5
here	equ	$
minus	xdw	here+2
	pop	h
	mov	a,l

	page

	cma
	mov	l,a
	mov	a,h
	cm
	mov	h,a
	inx	h
	jmp	hpush
;
	db	86
	dstr4	DMINUS
	xdw	minus-8
here	equ	$
dminu	xdw	here+2
	pop	h
	pop	d
	sub	a
	sub	e
	mov	e,a
	mvi	a,0
	sbb	d
	mov	d,a
	mvi	a,0
	sbb	l
	mov	l,a
	sbb	h
	mov	h,a
	push	d
	jmp	hpush
;
	db	84
	dstr4	OVER
	xdw	dminu-9
here	equ	$
over	xdw	here+2
	pop	d
	pop	h
	push	h
	jmp	dpush
;
	db	84
	dstr4	DROP
	xdw	over-7
here	equ	$
drop	xdw	here+2
	pop	h
	jmp	next
;
	db	84
	dstr4	SWAP
	xdw	drop-7
here	equ	$
swap	xdw	here+2
	pop	h
	xthl
	jmp	hpush

	page

	db	83
	dstr4	DUP
	xdw	swap-7
here	equ	$
dup	xdw	here+2
	pop	h
	push	h
	jmp	hpush
;
	db	84
	dstr4	2DUP
	xdw	dup-6
here	equ	$
tdup	xdw	here+2
	pop	h
	pop	d
	push	d
	push	h
	jmp	dpush
;
	db	82
	dstr4	+!
	xdw	tdup-7
here	equ	$
pstor	xdw	here+2
	pop	h
	pop	d
	mov	a,m
	add	e
	mov	m,a
	inx	h
	mov	a,m
	adc	d
	mov	m,a
	jmp	next
;
	db	86
	dstr4	TOGGLE
	xdw	pstor-5
here	equ	$
toggl	xdw	here+2
	pop	d
	pop	h
	mov	a,m
	xra	e
	mov	m,a
	jmp	next
;
	db	81
	dstr4	@
	xdw	toggl-9
here	equ	$
at	xdw	here+2
	pop	h
	mov	e,m
	inx	h

	page

	mov	d,m
	push	d
	jmp	next
;
	db	82
	dstr4	C@
	xdw	at-4
here	equ	$
cat	xdw	here+2
	pop	h
	mov	l,m
	mvi	h,0
	jmp	hpush
;
	db	82
	dstr4	2@
	xdw	cat-5
here	equ	$
tat	xdw	here+2
	pop	h
	lxi	d,2
	dad	d
	mov	e,m
	inx	h
	mov	d,m
	push	d
	mov	e,m
	inx	h
	mov	d,m
	push	d
	jmp	next
;
	db	81
	dstr4	!
	xdw	tat-5
here	equ	$
store	xdw	here+2
	pop	h
	pop	d
	mov	m,e
	inx	h
	mov	m,d
	jmp	next
;
	db	82
	dstr4	C!
	xdw	store-4
here	equ	$
cstor	xdw	here+2
	pop	h
	pop	d
	mov	m,e
	jmp	next
;
	db	82

	page

	dstr4	2!
	xdw	cstor-5
here	equ	$
tstor	xdw	here+2
	pop	h
	pop	d
	mov	m,e
	inx	h
	mov	m,d
	inx	h
	pop	d
	mov	m,e
	inx	h
	mov	m,d
	jmp	next
;
; See old page #21



	end
	
