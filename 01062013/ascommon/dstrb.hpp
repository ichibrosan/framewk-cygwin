// $Log: dstrb.hpp,v $
// Revision 1.2  2011/03/25 21:47:31  doug
// *** empty log message ***
//
// Revision 1.1  2011/03/25 07:19:17  doug
// Initial revision
//

char dir_dstrb[] = "$Id: dstrb.hpp,v 1.2 2011/03/25 21:47:31 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

	if(0 == strcmp(strupr(g_szOpcode),"DSTRB")) {
		fprintf(g_flog,"Processing DSTRB directive\n");
		char szDSTRBtemp[DEFAULT_STRSIZE];
		memset(szDSTRBtemp,0,sizeof(szDSTRBtemp));

		for(int o=0;o<strlen(g_szParms);o++) {
			if(0 ==o) {
				g_ucBytes[g_iBytesIndex++] = g_szParms[o]+0x80;
				szDSTRBtemp[o]      = g_szParms[o]+0x80;
			} else {
                                g_ucBytes[g_iBytesIndex++] = g_szParms[o];
				szDSTRBtemp[o]      = g_szParms[o];
			}
		}
		g_iLineType = TYPE_DIR;
		g_iErrorNo ^= ERROR_UNKOP;
		g_pCSymbols->add(g_szLabel,TYPE_STRING,szDSTRBtemp);
	}
