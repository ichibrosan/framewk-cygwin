// $Log: listincl.hpp,v $
// Revision 1.3  2011/04/04 13:05:54  doug
// add listinc as alias for listincl
//
// Revision 1.2  2011/03/25 21:47:31  doug
// *** empty log message ***
//
// Revision 1.1  2011/03/25 07:19:17  doug
// Initial revision
//

char dir_listincl[] = "$Id: listincl.hpp,v 1.3 2011/04/04 13:05:54 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.
	
	if(0 == strcmp(strupr(g_szOpcode),"LISTINCL")) {
		fprintf(g_flog,"Processing LISTINCL directive\n");
		if(0 != strlen(g_szParms)) {
			g_bListIncludes = resolvep8(g_szParms);
			g_iLineType = TYPE_DIR;
                        g_iErrorNo ^= ERROR_UNKOP;
		}
	}

        if(0 == strcmp(strupr(g_szOpcode),"LISTINC")) {
                fprintf(g_flog,"Processing LISTINC directive\n");
                if(0 != strlen(g_szParms)) {
                        g_bListIncludes = resolvep8(g_szParms);
                        g_iLineType = TYPE_DIR;
                        g_iErrorNo ^= ERROR_UNKOP;
                }
        }


////////////////////////
// eof - listincl.hpp //
////////////////////////
