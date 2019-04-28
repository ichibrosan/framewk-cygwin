// $Log: include.hpp,v $
// Revision 1.2  2011/03/25 21:47:31  doug
// *** empty log message ***
//
// Revision 1.1  2011/03/25 07:19:17  doug
// Initial revision
//

char dir_include[] = "$Id: include.hpp,v 1.2 2011/03/25 21:47:31 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

	if(0 == strcmp(strupr(g_szOpcode),"INCLUDE")) {
		fprintf(g_flog,"Processing INCLUDE directive\n");
		if(TRUE == g_bPass1) {
			g_pCSource1->srcopen(g_szParms);
		}
		if(TRUE == g_bPass2) {
			g_pCSource2->srcopen(g_szParms);
		}
		g_iLineType = TYPE_DIR;
		g_iErrorNo ^= ERROR_UNKOP;
	}
