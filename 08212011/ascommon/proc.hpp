// $Log: proc.hpp,v $
// Revision 1.2  2011/03/25 21:47:31  doug
// *** empty log message ***
//
// Revision 1.1  2011/03/25 07:19:17  doug
// Initial revision
//

char dir_proc[] = "$Id: proc.hpp,v 1.2 2011/03/25 21:47:31 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

if(0 == strcmp(strupr(g_szOpcode),"PROC")) {
	fprintf(g_flog,"Processing PROC directive\n");
	g_iErrorNo ^= ERROR_UNKOP;
	g_iLineType = TYPE_DIR;
	if(0 < strlen(g_szParms)) {
		char bDone = FALSE;
		if(0 == strcmp(strupr(g_szParms),"8080")) {
			g_iProc = PROC_8085;
			strcpy(g_szListRadix,g_szListRadixHex);
			bDone = TRUE;
		}		
                if(0 == strcmp(strupr(g_szParms),"Z80")) {
                        g_iProc = PROC_Z80;
                        strcpy(g_szListRadix,g_szListRadixHex);
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"8085")) {
                        g_iProc = PROC_8085; 
                        strcpy(g_szListRadix,g_szListRadixHex);
			bDone = TRUE;
                }
		if(0 == strcmp(strupr(g_szParms),"6502")) {
			g_iProc = PROC_6502;
                        strcpy(g_szListRadix,g_szListRadixHex);
			bDone = TRUE;
		}		
                if(0 == strcmp(strupr(g_szParms),"68000")) {
                        g_iProc = PROC_68000; 
                        strcpy(g_szListRadix,g_szListRadixHex);
			bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"1620")) {
                        g_iProc = PROC_1620;
                        strcpy(g_szListRadix,g_szListRadixDec);
                        bDone = TRUE;
                }
		if(FALSE == bDone) {
                	g_iErrorNo |= ERROR_NOCPU;
		}
	} else {
		g_iErrorNo |= ERROR_NOPARM;
	}
}
