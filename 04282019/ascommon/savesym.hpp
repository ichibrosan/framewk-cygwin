// $Log: savesym.hpp,v $
// Revision 1.3  2011/03/25 21:47:31  doug
// *** empty log message ***
//
// Revision 1.2  2011/03/25 07:26:41  doug
// *** empty log message ***
//
// Revision 1.1  2011/03/25 07:19:17  doug
// Initial revision
//

char dir_savesym[] = "$Id: savesym.hpp,v 1.3 2011/03/25 21:47:31 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.
	
	if(0 == strcmp(strupr(g_szOpcode),"SAVESYMS")) {
		fprintf(g_flog,"Processing SAVESYMS directive\n");
		if(0 != strlen(g_szParms)) {
			g_bSaveSymbols = resolvep8(g_szParms);
			g_iLineType = TYPE_DIR;
                        g_iErrorNo ^= ERROR_UNKOP;

		}
	}
