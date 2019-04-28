// $Log: pop_85.hpp,v $
// Revision 1.2  2011/03/25 22:47:07  doug
// add log and trim gpl stuff
////

char pop_85[] = "$Id: pop_85.hpp,v 1.2 2011/03/25 22:47:07 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

if(0 == strcmp(strupr(g_szOpcode),"POP")) {
	fprintf(g_flog,"Processing 8085 POP g_szOpcode\n");
        g_iLineType = TYPE_8085;
        g_iErrorNo ^= ERROR_UNKOP;
	if(0 < strlen(g_szParms)) {
		int bDone = FALSE;
		if(0 == strcmp(strupr(g_szParms),"B")) {
			g_ucBytes[g_iBytesIndex++] = 0xC1;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"D")) {
			g_ucBytes[g_iBytesIndex++] = 0xD1;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"H")) {
			g_ucBytes[g_iBytesIndex++] = 0xE1;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"BC")) {
			g_ucBytes[g_iBytesIndex++] = 0xC1;
                        bDone = TRUE;
		}
                if(0 == strcmp(strupr(g_szParms),"DE")) {
                        g_ucBytes[g_iBytesIndex++] = 0xD1;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"HL")) {
                        g_ucBytes[g_iBytesIndex++] = 0xE1;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"PSW")) {
                        g_ucBytes[g_iBytesIndex++] = 0xF1;
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
// eof - pop.hpp //
///////////////////

