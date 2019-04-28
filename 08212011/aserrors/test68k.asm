        title $Id: test68k.asm,v 1.1 2011/03/25 09:08:03 doug Exp $
        subttl  COPR 2011 Douglas Goodall
;
; $Log: test68k.asm,v $
; Revision 1.1  2011/03/25 09:08:03  doug
; Initial revision
;
;
        include gplstuff.inc

 
	proc	68000
	radix	hex
	org	1000

dd1	dd	12345678

dq1	dq	0123456789ABCDEF

dw1	dw	1234

extl1	ext.l   0
        ext.l   1
        ext.l   2
        ext.l   3
        ext.l   4
        ext.l   5
        ext.l   6
        ext.l   7

extw1	ext.w	0
	ext.w	1
	ext.w	2
	ext.w	3
	ext.w	4
	ext.w	5
	ext.w	6
	ext.w	7

ill1	illegal

link1	link	0
        link	1
        link	2
        link	3
        link	4
        link	5
        link	6
        link	7

nop1	nop
reset1	reset
rte1	rte
rtr1	rtr
rts1	rts
stop1	stop
trapv1	trapv

unlk1	unlk	0
        unlk	1
        unlk	2
        unlk	3
        unlk	4
        unlk	5
        unlk	6
        unlk	7

end1	end

