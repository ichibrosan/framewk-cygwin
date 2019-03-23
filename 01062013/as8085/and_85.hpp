// $Log: and_85.hpp,v $
// Revision 1.2  2011/03/25 22:47:07  doug
// add log and trim gpl stuff
////

char and_85[] = "$Id: and_85.hpp,v 1.2 2011/03/25 22:47:07 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

if(0 == strcmp(strupr(g_szOpcode),"AND")) {
	fprintf(g_flog,"...processing AND g_szOpcode...\n");
	g_iLineType = TYPE_8085;
	g_iErrorNo ^= ERROR_UNKOP;
	if(0 < strlen(g_szParms)) {
		int bDone = FALSE;
		if(0 == strcmp(strupr(g_szParms),"A")) {
			g_ucBytes[g_iBytesIndex++] = 0xa7;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"B")) {
			g_ucBytes[g_iBytesIndex++] = 0xa0;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"C")) {
			g_ucBytes[g_iBytesIndex++] = 0xa1;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"D")) {
			g_ucBytes[g_iBytesIndex++] = 0xa2;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"E")) {
			g_ucBytes[g_iBytesIndex++] = 0xa3;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"H")) {
			g_ucBytes[g_iBytesIndex++] = 0xa4;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"L")) {
			g_ucBytes[g_iBytesIndex++] = 0xa5;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"(HL)")) {
			g_ucBytes[g_iBytesIndex++] = 0xa6;
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
// eof - and.hpp //
///////////////////

