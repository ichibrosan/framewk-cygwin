# ---------------------------------------------------
# mkfiles/inouttst.mak  Ver 11.03.06s  
# Serial No. 2011-1042-654321    All Rights Reserved.
# Copyright (C) 2011 Douglas Goodall,  United States.
# ---------------------------------------------------
# mkfiles/inouttst.mak autogenerated by asmall.cpp 
# Tue Mar  8 07:38:07 PST 2011
# Copyright (c)2011 Douglas Goodall. Rights Reserved.

AS = ../assemble

INCFILES  = assemble.inc banner.inc cpm80.inc incl1.inc incl2.inc incl3.inc 

inouttst.hex:	inouttst.asm $(INCFILES) $(AS) 
	$(AS) inouttst 

clean:
	rm -f *.bin  *.lst *.log *.hex

# eof - mkfiles/inouttst.mak