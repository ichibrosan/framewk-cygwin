// $Log: dstr.hpp,v $
// Revision 1.2  2011/03/25 21:47:31  doug
// *** empty log message ***
//
// Revision 1.1  2011/03/25 07:19:17  doug
// Initial revision
//

char dir_dstr[] = "$Id: dstr.hpp,v 1.2 2011/03/25 21:47:31 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

	if(0 == strcmp(strupr(g_szOpcode),"DSTR")) {
		fprintf(g_flog,"Processing DSTR directive\n");
                g_iLineType = TYPE_DIR;
                g_iErrorNo ^= ERROR_UNKOP;
		for(int o=0;o<strlen(g_szParms);o++) {
			g_ucBytes[g_iBytesIndex++] = g_szParms[o];
		}
		g_pCSymbols->add(g_szLabel,TYPE_STRING,g_szParms);
	}
