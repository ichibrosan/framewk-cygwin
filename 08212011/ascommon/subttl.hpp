// $Log: subttl.hpp,v $
// Revision 1.3  2011/04/04 12:47:22  doug
// add "subtitle" as alias to subttl
//
// Revision 1.2  2011/03/25 21:47:31  doug
// *** empty log message ***
//
// Revision 1.1  2011/03/25 07:19:17  doug
// Initial revision
//

char dir_subttl[] = "$Id: subttl.hpp,v 1.3 2011/04/04 12:47:22 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.
	
	if(0 == strcmp(strupr(g_szOpcode),"SUBTTL")) {
		fprintf(g_flog,"Processing SUBTTL directive\n");
		if(0 != strlen(g_szParms)) {
			strcpy(g_szSubttl,g_szParms);
			g_iLineType = TYPE_DIR;
			g_pCSymbols->add("subttl",TYPE_STRING,g_szSubttl);
                        g_iErrorNo ^= ERROR_UNKOP;

		}
	}

        if(0 == strcmp(strupr(g_szOpcode),"SUBTITLE")) {
                fprintf(g_flog,"Processing SUBTITLE directive\n");
                if(0 != strlen(g_szParms)) {
                        strcpy(g_szSubttl,g_szParms);
                        g_iLineType = TYPE_DIR;
                        g_pCSymbols->add("subttl",TYPE_STRING,g_szSubttl);
                        g_iErrorNo ^= ERROR_UNKOP;

                }
        }

