// $Log: dstrz.hpp,v $
// Revision 1.2  2011/03/25 21:47:31  doug
// *** empty log message ***
//
// Revision 1.1  2011/03/25 07:19:17  doug
// Initial revision
//

char dir_dstrz[] = "$Id: dstrz.hpp,v 1.2 2011/03/25 21:47:31 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

if(0 == strcmp(strupr(g_szOpcode),"DSTRZ")) {
	fprintf(g_flog,"Processing DSTRZ directive\n");
	char szDSTRZtemp[DEFAULT_STRSIZE];
	memset(szDSTRZtemp,0,sizeof(szDSTRZtemp));
	for(int o=0;o<strlen(g_szParms);o++) {
		g_ucBytes[g_iBytesIndex++] = g_szParms[o];
		szDSTRZtemp[o] = g_szParms[o];
	}
	g_ucBytes[g_iBytesIndex++] = 0;
	//szDSTRZtemp[strlen(szDSTRZtemp)] = 0;
	g_iLineType = TYPE_DIR;
	g_iErrorNo ^= ERROR_UNKOP;
	g_pCSymbols->add(g_szLabel,TYPE_STRING,szDSTRZtemp);
}

