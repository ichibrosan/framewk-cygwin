// $Log: dsa.hpp,v $
// Revision 1.2  2011/03/25 21:47:31  doug
// *** empty log message ***
//
// Revision 1.1  2011/03/25 07:19:17  doug
// Initial revision
//

char dir_dsa[] = "$Id: dsa.hpp,v 1.2 2011/03/25 21:47:31 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.
	
	if(0 == strcmp(strupr(g_szOpcode),"DSA")) {
		fprintf(g_flog,"Processing DSA directive\n");
		value = resolvep16(g_szParms);
		g_ucBytes[g_iBytesIndex++] = value & 0x00ff;
		g_ucBytes[g_iBytesIndex++] = value >> 8;
		g_iLineType = TYPE_DIR;
		g_iErrorNo ^= ERROR_UNKOP;
	}
