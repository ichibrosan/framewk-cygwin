// $Log: dotend.hpp,v $
// Revision 1.2  2011/03/25 21:47:31  doug
// *** empty log message ***
//
// Revision 1.1  2011/03/25 07:19:17  doug
// Initial revision
//

char dir_dotend[] = "$Id: dotend.hpp,v 1.2 2011/03/25 21:47:31 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.
	
	if(0 == strcmp(strupr(g_szOpcode),".END")) {
		fprintf(g_flog,"Processing .END directive\n");
		unsigned int result = resolvep16(g_szParms);
		g_ucBytes[g_iBytesIndex++] = result & 255;
		g_ucBytes[g_iBytesIndex++] = result >> 8;
		g_iLineType = TYPE_DIR;
		g_bEndFound = TRUE;

		// this line causes a pagebreak before 
		// the symbols table dump
                g_iPageline = g_iPageLength - 1;
		g_iErrorNo ^= ERROR_UNKOP;

	}
