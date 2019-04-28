// $Log: dstr4.hpp,v $
// Revision 1.2  2011/03/25 21:47:31  doug
// *** empty log message ***
//
// Revision 1.1  2011/03/25 07:19:17  doug
// Initial revision
//

char dir_dstr4[] = "$Id: dstr4.hpp,v 1.2 2011/03/25 21:47:31 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

	if(0 == strcmp(strupr(g_szOpcode),"DSTR4")) {
		char szDSTR4temp[DEFAULT_STRSIZE];
		memset(szDSTR4temp,0,sizeof(szDSTR4temp));
		fprintf(g_flog,"Processing DSTR4 directive\n");
		for(int o=0;o<strlen(g_szParms);o++) {
			g_ucBytes[g_iBytesIndex++] = g_szParms[o];
			szDSTR4temp[o] = g_szParms[o];
		}
		g_ucBytes[g_iBytesIndex-1] |= 0x80;
		szDSTR4temp[g_iBytesIndex-1] |= 0x80;
		g_iLineType = TYPE_DIR;
		g_iErrorNo ^= ERROR_UNKOP;
		g_pCSymbols->add(g_szLabel,TYPE_STRING,szDSTR4temp);
	}
