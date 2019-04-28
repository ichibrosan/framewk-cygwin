# ------------------------------------------------
# Makefile     10-Mar-11 Licensed with the GNU GPL
# S/n 2011-1042-654321  Written by Douglas Goodall
# Copyright(c)2011 Douglas Goodall, United States.
# ------------------------------------------------
# This file is part of 
#   "Vintage Modern Assembler Plus Tools (VMAPT)".
#
# VMAPT is free software:  you can redistribute it
# and / or  modify it  under the terms of  the GNU
# General Public License  as published by the Free
# Software  Foundation,  either  version 3  of the
# License, or (at your option)  any later version.
#
# VMAPT is distributed in the hope that it will be
# useful,  but WITHOUT ANY WARRANTY;  without even
# the  implied  warranty  of   MERCHANTABILITY  or
# FITNESS FOR A PARTICULAR PURPOSE.   See the  GNU
# General Public License for more details.
#
# You  should  have  received  a  copy of  the GNU
# General Public License along with VMAPT. If not,
# see <http://www.gnu.org/licenses/>.
# ------------------------------------------------
 
AS     = tasm
INTEL = -85 
ZILOG = -80 -x 

all:	xmodem48.obj rtc.obj romfrmtn.obj loader-m.obj Format.obj dbgmon48.obj cpm22.obj testz80.obj test85.obj 

xmodem48.obj:	xmodem48.asm Makefile
	$(AS) $(ZILOG) xmodem48.asm

rtc.obj:	rtc.asm Makefile
	$(AS) $(ZILOG) rtc.asm

romfrmtn.obj:	romfrmtn.asm Makefile
	$(AS) $(ZILOG) romfrmtn.asm

loader-m.obj:	loader-m.asm Makefile
	$(AS) $(ZILOG) loader-m.asm

Format.obj:	Format.asm Makefile
	$(AS) $(ZILOG) Format.asm

dbgmon48.obj:	dbgmon48.asm Makefile
	$(AS) $(ZILOG) dbgmon48.asm

cpm22.obj:	cpm22.asm Makefile
	$(AS) $(ZILOG) cpm22.asm

testz80.obj:	testz80.asm Makefile
	$(AS) $(ZILOG) testz80.asm

test85.obj:	test85.asm Makefile
	$(AS) $(INTEL) test85.asm

clean:
	rm -f *.hex
	rm -f *.lst
	rm -f *.obj

