// ---------------------------------------------------
// IM.HPP       28-Jan-11 DOSBox-0.74 Version 1.00.00a
// Serial No. 8208-4162-344865    All Rights Reserved.
// Copyright (C) 2010 Douglas Goodall,  United States.
// ---------------------------------------------------

if(0 == strcmp(strupr(g_szOpcode),"IM")) {
	fprintf(g_flog,"...processing IM g_szOpcode...\n");
	g_iErrorNo ^= ERROR_UNKOP;
	g_iLineType = TYPE_Z80;
	if(0 < strlen(g_szParms)) {
		switch(g_szParms[0]) {
			case '0':	
				g_ucBytes[g_iBytesIndex++] = 0xed;
				g_ucBytes[g_iBytesIndex++] = 0x46;
				break;
			case '1':
				g_ucBytes[g_iBytesIndex++] = 0xed;
				g_ucBytes[g_iBytesIndex++] = 0x56;
				break;
			case '2':
				g_ucBytes[g_iBytesIndex++] = 0xed;
				g_ucBytes[g_iBytesIndex++] = 0x5e;
				break;
			default:
				g_iErrorNo |= ERROR_NOMODE;
				break;
		}
	} else {
		g_iErrorNo |= ERROR_NOPARM;
	}
}

//////////////////
// eof - im.hpp //
//////////////////

