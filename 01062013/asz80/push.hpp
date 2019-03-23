// ---------------------------------------------------
// PUSH.HPP     28-Jan-11 DOSBox-0.74 Version 1.00.00a
// Serial No. 8208-4162-344865    All Rights Reserved.
// Copyright (C) 2010 Douglas Goodall,  United States.
// ---------------------------------------------------
	
if(0 == strcmp(strupr(g_szOpcode),"PUSH")) {
	g_iErrorNo ^= ERROR_UNKOP;
	fprintf(g_flog,"...processing PUSH g_szOpcode...\n");
	if(0 < strlen(g_szParms)) {
		int bDone = FALSE;
		if(0 == strcmp(strupr(g_szParms),"B")) {
			g_ucBytes[g_iBytesIndex++] = 0xC5;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"D")) {
			g_ucBytes[g_iBytesIndex++] = 0xD5;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"H")) {
			g_ucBytes[g_iBytesIndex++] = 0xE5;
			bDone = TRUE;
		} 
                if(0 == strcmp(strupr(g_szParms),"AF")) {
                        g_ucBytes[g_iBytesIndex++] = 0xF5;
			bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"BC")) {
                        g_ucBytes[g_iBytesIndex++] = 0xC5;
			bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"DE")) {
                        g_ucBytes[g_iBytesIndex++] = 0xD5;
			bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"HL")) {
                        g_ucBytes[g_iBytesIndex++] = 0xE5;
			bDone = TRUE;
                }
		if(0 == strcmp(strupr(g_szParms),"PSW")) {
			g_ucBytes[g_iBytesIndex++] = 0xF5;
			bDone = TRUE;
		}
		if(FALSE == bDone) {
			g_iErrorNo = ERROR_NOREG;
		}
	} else {
		g_iErrorNo |= ERROR_NOPARM;
	}
}

