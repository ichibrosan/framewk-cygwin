        title   $Id: testmov.asm,v 1.2 2011/03/25 09:01:21 doug Exp $
        subttl  COPR 2011 Douglas Goodall
;
; $Log: testmov.asm,v $
; Revision 1.2  2011/03/25 09:01:21  doug
; *** empty log message ***
;
; Revision 1.1  2011/03/25 08:26:35  doug
; Initial revision
;
;
        include gplstuff.inc


	include	assemble.inc 
	proc	8085

	mov	a,a
	mov	a,b
	mov	a,c
	mov	a,d
	mov	a,e
	mov	a,h
	mov	a,l
	mov	a,m

	mov	b,a
	mov	b,b
	mov	b,c
	mov	b,d
	mov	b,e
	mov	b,h
	mov	b,l
	mov	b,m

	mov	c,a
	mov	c,b
	mov	c,c
	mov	c,d
	mov	c,e
	mov	c,h
	mov	c,l
	mov	c,m

	mov	d,a
	mov	d,b
	mov	d,c
	mov	d,d
	mov	d,e
	mov	d,h
	mov	d,l
	mov	d,m

	mov	e,a
	mov	e,b
	mov	e,c
	mov	e,d
	mov	e,e
	mov	e,h
	mov	e,l
	mov	e,m

	page

	mov	h,a
	mov	h,b
	mov	h,c
	mov	h,d
	mov	h,e
	mov	h,h
	mov	h,l
	mov	h,m

	mov	l,a
	mov	l,b
	mov	l,c
	mov	l,d
	mov	l,e
	mov	l,h
	mov	l,l
	mov	l,m

	mov	m,a
	mov	m,b
	mov	m,c
	mov	m,d
	mov	m,e
	mov	m,h
	mov	m,l
	mov	m,m

	end

