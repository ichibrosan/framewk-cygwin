// $Log: copr.hpp,v $
// Revision 1.2  2011/03/25 21:47:31  doug
// *** empty log message ***
//
// Revision 1.1  2011/03/25 07:19:17  doug
// Initial revision
//

char dir_copr[] = "$Id: copr.hpp,v 1.2 2011/03/25 21:47:31 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.
	
	if(0 == strcmp(strupr(g_szOpcode),"COPR")) {
		fprintf(g_flog,"Processing COPR directive\n");
		for(int o=0;o<strlen(g_szCopr);o++) {
			g_ucBytes[g_iBytesIndex++] = g_szCopr[o];
		}
		g_iLineType = TYPE_DIR;
		g_iErrorNo ^= ERROR_UNKOP;
	}
