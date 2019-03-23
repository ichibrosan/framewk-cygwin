; ------------------------------------------------
; printhex.inc 13-Apr-11 Licensed with the GNU GPL
; S/n 2011-1042-654321  Written by Douglas Goodall
; Copyright(c)2011 Douglas Goodall, United States.
; ------------------------------------------------
; This file is part of 
;   "Vintage Modern Assembler Plus Tools (VMAPT)".
;
; VMAPT is free software:  you can redistribute it
; and / or  modify it  under the terms of  the GNU
; General Public License  as published by the Free
; Software  Foundation,  either  version 3  of the
; License, or (at your option)  any later version.
;
; VMAPT is distributed in the hope that it will be
; useful,  but WITHOUT ANY WARRANTY;  without even
; the  implied  warranty  of   MERCHANTABILITY  or
; FITNESS FOR A PARTICULAR PURPOSE.   See the  GNU
; General Public License for more details.
;
; You  should  have  received  a  copy of  the GNU
; General Public License along with VMAPT. If not,
; see <http://www.gnu.org/licenses/>.
; ------------------------------------------------

	public16 prnyb
prnyb	push	psw
	push	b
	push	d
	ani	0F
	lxi	h,hexref
	mvi	d,0
	mov	e,a
	dad	d
	mov	e,m
	mvi	c,conout
	call	bdos
	pop	d
	pop	b
	pop	psw
	ret

hexref	dstr	0123456789ABCDEF

	public16 prbyte
prbyte	push	psw
	rrc
	rrc
	rrc
	rrc
	call	prnyb
	pop	psw
	call	prnyb
	ret

;;;;;;;;;;;;;;;;;;;
; eof - prnyb.inc ;
;;;;;;;;;;;;;;;;;;;
