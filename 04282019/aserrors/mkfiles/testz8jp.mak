# ---------------------------------------------------
# mkfiles/testz8jp.mak  Ver 11.03.24c  
# Serial No. 2011-1042-654321    All Rights Reserved.
# Copyright (C) 2011 Douglas Goodall,  United States.
# ---------------------------------------------------
# mkfiles/testz8jp.mak autogenerated by asmall.cpp 
# Thu Mar 24 02:23:40 PDT 2011
# Copyright (c)2011 Douglas Goodall. Rights Reserved.

AS = ../assemble

INCFILES  = assemble.inc banner.inc cpm80.inc incl1.inc incl2.inc incl3.inc 

testz8jp.hex:	testz8jp.asm $(INCFILES) $(AS) 
	$(AS) testz8jp 

clean:
	rm -f *.bin  *.lst *.log *.hex

# eof - mkfiles/testz8jp.mak
