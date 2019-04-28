// $Log: orgminus.hpp,v $
// Revision 1.2  2011/03/25 21:47:31  doug
// *** empty log message ***
//
// Revision 1.1  2011/03/25 07:19:17  doug
// Initial revision
//

char dir_orgminus[] = "$Id: orgminus.hpp,v 1.2 2011/03/25 21:47:31 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.
	
	// Decrement the program counter
	if(0 == strcmp(strupr(g_szOpcode),"ORGMINUS")) {
		fprintf(g_flog,"Processing ORGMINUS directive\n");
		if(0 != strlen(g_szParms)) {
			g_iPc -= resolvep16(g_szParms);
        	        g_iLineType = TYPE_DIR;
			g_iErrorNo ^= ERROR_UNKOP;
		}
	}