        title   $Id: allz80.asm,v 1.2 2011/03/25 09:01:21 doug Exp $
        subttl  COPR 2011 Douglas Goodall
;
; $Log: allz80.asm,v $
; Revision 1.2  2011/03/25 09:01:21  doug
; *** empty log message ***
;
; Revision 1.1  2011/03/25 08:26:35  doug
; Initial revision
; 
;
	include	gplstuff.inc

	proc	z80
	radix	hex
	org	100

value8	equ8	0E5

start	nop

	ld	a,a
	ld	a,b
	ld	a,c
	ld	a,d
	ld	a,e
	ld	a,h
	ld	a,i
	ld	a,l
	ld	a,r
	ld	a,(bc)
	ld	a,(de)
	ld	a,(hl)
	ld	b,a
	ld	b,b
	ld	b,c
	ld	b,d
	ld	b,e
	ld	b,h
	ld	b,l
	ld	b,(hl)
	ld	c,a
	ld	c,b
	ld	c,c
	ld	c,d
	ld	c,e
	ld	c,h
	ld	c,l
	ld	c,(hl)
	ld	d,a
	ld	d,b
	ld	d,c
	ld	d,d
	ld	d,e
	ld	d,h
	ld	d,l
	ld	d,(hl)
	ld	e,a
	ld	e,b
	ld	e,c
	ld	e,d
	ld	e,e
	ld	e,h
	ld	e,l
	ld	e,(hl)
	ld	h,a
	ld	h,b
	ld	h,c
	ld	h,d
	ld	h,e
	ld	h,h
	ld	h,l
	ld	h,(hl)
	ld	i,a
	ld	l,a
	ld	l,b
	ld	l,c
	ld	l,d
	ld	l,e
	ld	l,h
	ld	l,l
	ld	l,(hl)
	ld	r,a
	ld	sp,hl
	ld	b,value8
	ld	c,value8
	ld	d,value8
	ld	e,value8
	ld	h,value8
	ld	l,value8
	ld	a,value8
	ld	(hl),b
	ld	(hl),c
	ld	(hl),d
	ld	(hl),e
	ld	(hl),h
	ld	(hl),l
	ld	(hl),a
	
	end	start
 
