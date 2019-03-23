// $Log: typeinc.hpp,v $
// Revision 1.1  2011/04/04 13:36:46  doug
// Initial revision
//
//

char dir_typeinc[] = "$Id: typeinc.hpp,v 1.1 2011/04/04 13:36:46 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.
	
	if(0 == strcmp(strupr(g_szOpcode),"TYPEINC")) {
		fprintf(g_flog,"Processing TYPEINC directive\n");
		if(0 != strlen(g_szParms)) {
			g_bTypeIncludes = resolvep8(g_szParms);
			g_iLineType = TYPE_DIR;
			g_iErrorNo ^= ERROR_UNKOP;
		}
	}

        if(0 == strcmp(strupr(g_szOpcode),"TYPEINCL")) {
                fprintf(g_flog,"Processing TYPEINCL directive\n");
                if(0 != strlen(g_szParms)) {
                        g_bTypeIncludes = resolvep8(g_szParms);
                        g_iLineType = TYPE_DIR;
                        g_iErrorNo ^= ERROR_UNKOP;
                }
        }

