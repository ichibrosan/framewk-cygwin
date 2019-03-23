// ---------------------------------------------------
// EX.HPP       28-Jan-11 DOSBox-0.74 Version 1.00.00a
// Serial No. 8208-4162-344865    All Rights Reserved.
// Copyright (C) 2010 Douglas Goodall,  United States.
// ---------------------------------------------------

if(0 == strcmp(strupr(g_szOpcode),"EX")) {
	fprintf(g_flog,"...processing EX g_szOpcode...\n");
        g_iLineType = TYPE_Z80;
        g_iErrorNo ^= ERROR_UNKOP;
	if(0 < strlen(g_szParms)) {
		int bDone = FALSE;
		if(0 == strcmp(strupr(g_szParms),"(SP),HL")) {
			g_ucBytes[g_iBytesIndex++] = 0xe3;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"(SP),IX")) {
			g_ucBytes[g_iBytesIndex++] = 0xDD;
			g_ucBytes[g_iBytesIndex++] = 0xe3;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"(SP),IY")) {
			g_ucBytes[g_iBytesIndex++] = 0xfd;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"AF,AF")) {
			g_ucBytes[g_iBytesIndex++] = 0x08;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"DE,HL")) {
			g_ucBytes[g_iBytesIndex++] = 0xeb;
			bDone = TRUE;
		}
		if(FALSE == bDone) {
			g_iErrorNo |= ERROR_NOREG;
		}
	} else {
		g_iErrorNo |= ERROR_NOPARM;
	}

}

//////////////////
// eof - ex.hpp //
//////////////////

