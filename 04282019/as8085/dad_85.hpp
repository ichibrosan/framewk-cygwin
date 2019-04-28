// $Log: dad_85.hpp,v $
// Revision 1.2  2011/03/25 22:47:07  doug
// add log and trim gpl stuff
////

char dad_85[] = "$Id: dad_85.hpp,v 1.2 2011/03/25 22:47:07 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

if(0 == strcmp(strupr(g_szOpcode),"DAD")) {
	fprintf(g_flog,"Processing 8085 DAD g_szOpcode\n");
        g_iLineType = TYPE_8085;
        g_iErrorNo ^= ERROR_UNKOP;
	if(0 < strlen(g_szParms)) {
		int bDone = FALSE;
		if(0 == strcmp(strupr(g_szParms),"B")) {
			g_ucBytes[g_iBytesIndex++] = 0x09;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"D")) {
			g_ucBytes[g_iBytesIndex++] = 0x19;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"H")) {
			g_ucBytes[g_iBytesIndex++] = 0x29;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"SP")) {
			g_ucBytes[g_iBytesIndex++] = 0x39;
			bDone = TRUE;
		}
                if(0 == strcmp(strupr(g_szParms),"BC")) {
                        g_ucBytes[g_iBytesIndex++] = 0x09;
			bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"DE")) {
                        g_ucBytes[g_iBytesIndex++] = 0x19;
                	bDone = TRUE;
		}
                if(0 == strcmp(strupr(g_szParms),"HL")) {
                        g_ucBytes[g_iBytesIndex++] = 0x29;
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
// eof - dad.hpp //
///////////////////

