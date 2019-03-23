// $Log: pageleng.hpp,v $
// Revision 1.2  2011/03/25 21:47:31  doug
// *** empty log message ***
//
// Revision 1.1  2011/03/25 07:19:17  doug
// Initial revision
//

char dir_pageleng[] = "$Id: pageleng.hpp,v 1.2 2011/03/25 21:47:31 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.
	
	if(0 == strcmp(strupr(g_szOpcode),"PAGELENGTH")) {
		fprintf(g_flog,"Processing PAGELENGTH directive\n");
		if(0 != strlen(g_szParms)) {
			g_iPageLength = resolvep8(g_szParms);
			g_iLineType = TYPE_DIR;
			g_pCSymbols->add("pageleng",TYPE_U16,
				 (unsigned int)g_iPageLength);
			g_iErrorNo ^= ERROR_UNKOP;
		}
	}

