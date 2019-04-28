// ---------------------------------------------------
// DEC.HPP      28-Jan-11 DOSBox-0.74 Version 1.00.00a
// Serial No. 8208-4162-344865    All Rights Reserved.
// Copyright (C) 2010 Douglas Goodall,  United States.
// ---------------------------------------------------

if(0 == strcmp(strupr(g_szOpcode),"DEC")) {
	fprintf(g_flog,"...processing DEC g_szOpcode...\n");
	g_iErrorNo ^= ERROR_UNKOP;
	g_iLineType = TYPE_Z80;
	if(0 < strlen(g_szParms)) {
		int bDone = FALSE;
		if(0 == strcmp(strupr(g_szParms),"A")) {
			g_ucBytes[g_iBytesIndex++] = 0x3d;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"B")) {
			g_ucBytes[g_iBytesIndex++] = 0x05;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"BC")) {
			g_ucBytes[g_iBytesIndex++] = 0x0b;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"C")) {
			g_ucBytes[g_iBytesIndex++] = 0x0d;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"D")) {
			g_ucBytes[g_iBytesIndex++] = 0x15;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"DE")) {
			g_ucBytes[g_iBytesIndex++] = 0x1b;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"E")) {
			g_ucBytes[g_iBytesIndex++] = 0x1d;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"H")) {
			g_ucBytes[g_iBytesIndex++] = 0x25;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"HL")) {
			g_ucBytes[g_iBytesIndex++] = 0x2b;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"IX")) {
			g_ucBytes[g_iBytesIndex++] = 0xdd;
			g_ucBytes[g_iBytesIndex++] = 0x2b;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"IY")) {
			g_ucBytes[g_iBytesIndex++] = 0xfd;
			g_ucBytes[g_iBytesIndex++] = 0x2b;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"L")) {
			g_ucBytes[g_iBytesIndex++] = 0x2b;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"SP")) {
			g_ucBytes[g_iBytesIndex++] = 0x3b;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"(HL)")) {
			g_ucBytes[g_iBytesIndex++] = 0x35;
			bDone = TRUE;
		}
		if(FALSE == bDone) {
			g_iErrorNo |= ERROR_NOREG;
		}
	} else {
		g_iErrorNo |= ERROR_NOPARM;
	}
}

///////////////////
// eof - dec.hpp //
///////////////////

