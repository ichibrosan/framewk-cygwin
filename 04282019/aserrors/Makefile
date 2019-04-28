# ---------------------------------------------------
# Makefile     Ver 11.03.24c  x86_64-apple-darwin10.0
# Serial No. 2011-1042-654321    All Rights Reserved.
# Copyright (C) 2011 Douglas Goodall,  United States.
# ---------------------------------------------------
# Created by asmall.cpp  Fri Mar 25 02:10:07 PDT 2011


AS = ../assemble

HEXFILES = banner.hex test68k.hex 

INCFILES = assemble.inc banner.inc cpm80.inc gplstuff.inc incl1.inc incl2.inc incl3.inc 

all:	$(HEXFILES)


banner.hex:	banner.asm $(AS) Makefile $(INCFILES) 
	$(AS) banner 

test68k.hex:	test68k.asm $(AS) Makefile $(INCFILES) 
	$(AS) test68k 

clean:
	rm -f *.bin editthem *.lst *.log *.hex 
	rm -r -f banner test68k  *.sym

# eof - Makefile
