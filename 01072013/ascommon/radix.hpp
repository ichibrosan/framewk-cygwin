// $Log: radix.hpp,v $
// Revision 1.2  2011/03/25 21:47:31  doug
// *** empty log message ***
//
// Revision 1.1  2011/03/25 07:19:17  doug
// Initial revision
//

char dir_radix[] = "$Id: radix.hpp,v 1.2 2011/03/25 21:47:31 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

if(0 == strcmp(strupr(g_szOpcode),"RADIX")) {
	g_iLineType = TYPE_DIR;
	fprintf(g_flog,"Processing RADIX directive\n");
	if(0 != strlen(g_szParms)) {
		if(0 == strcmp(strupr(g_szParms),"DECIMAL")) {
			strcpy(g_szRadixFormat8,  g_szRadixFormat8Decimal);
			strcpy(g_szRadixFormat16,g_szRadixFormat16Decimal);
			strcpy(g_szRadixFormat32,g_szRadixFormat32Decimal);
			strcpy(g_szRadixFormat64,g_szRadixFormat64Decimal);
                        g_iErrorNo ^= ERROR_UNKOP;
		}		
		if(0 == strcmp(strupr(g_szParms),"HEX")) {
			strcpy(g_szRadixFormat8, g_szRadixFormat8Hex);
			strcpy(g_szRadixFormat16,g_szRadixFormat16Hex);
			strcpy(g_szRadixFormat32,g_szRadixFormat32Hex);
			strcpy(g_szRadixFormat64,g_szRadixFormat64Hex);
                        g_iErrorNo ^= ERROR_UNKOP;
		}		
		if(0 == strcmp(strupr(g_szParms),"HEXADECIMAL")) {
			strcpy(g_szRadixFormat8, g_szRadixFormat8Hex);
			strcpy(g_szRadixFormat16,g_szRadixFormat16Hex);
                        strcpy(g_szRadixFormat32,g_szRadixFormat32Hex);
			strcpy(g_szRadixFormat64,g_szRadixFormat64Hex);
                        g_iErrorNo ^= ERROR_UNKOP;
		}		
	}
}
