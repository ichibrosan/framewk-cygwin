// ---------------------------------------------------
// RLD.HPP      28-Jan-11 DOSBox-0.74 Version 1.00.00a
// Serial No. 8208-4162-344865    All Rights Reserved.
// Copyright (C) 2010 Douglas Goodall,  United States.
// ---------------------------------------------------
	
	if(0 == strcmp(strupr(g_szOpcode),"RLD")) {
		g_ucBytes[g_iBytesIndex++] = 0xed;
		g_ucBytes[g_iBytesIndex++] = 0x6f;
		g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;

	}
