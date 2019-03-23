// $Log: listradx.hpp,v $
// Revision 1.2  2011/03/25 21:47:31  doug
// *** empty log message ***
//
// Revision 1.1  2011/03/25 18:30:42  doug
// Initial revision
//
//

// Copyright (C) 2011 Douglas Goodall

char dir_listradix[] = "$Id: listradx.hpp,v 1.2 2011/03/25 21:47:31 doug Exp $";

if(0 == strcmp(strupr(g_szOpcode),"LISTRADIX")) {
	g_iLineType = TYPE_DIR;
	fprintf(g_flog,"Processing LISTRADIX directive\n");
	if(0 != strlen(g_szParms)) {
		if(0 == strcmp(strupr(g_szParms),"DECIMAL")) {
			strcpy(g_szListRadix,g_szListRadixDec);
                        g_iErrorNo ^= ERROR_UNKOP;
		}		
		if(0 == strcmp(strupr(g_szParms),"HEX")) {
			strcpy(g_szListRadix,g_szListRadixHex);
                        g_iErrorNo ^= ERROR_UNKOP;
		}		
		if(0 == strcmp(strupr(g_szParms),"HEXADECIMAL")) {
                        strcpy(g_szListRadix,g_szListRadixHex);
                        g_iErrorNo ^= ERROR_UNKOP;
		}		
	}
}
