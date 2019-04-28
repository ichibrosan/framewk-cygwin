// $Log: typesrc.hpp,v $
// Revision 1.3  2011/04/03 04:37:33  doug
// fix syntax error
//
// Revision 1.2  2011/04/03 04:35:45  doug
// fix tag problem
//
// Revision 1.1  2011/04/03 04:26:17  doug
// Initial revision
//
//

char dir_typesrc[] = "$Id: typesrc.hpp,v 1.3 2011/04/03 04:37:33 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.
	
	if(0 == strcmp(strupr(g_szOpcode),"TYPESRC")) {
		fprintf(g_flog,"Processing TYPESRC directive\n");
		if(0 != strlen(g_szParms)) {
			g_bTypeSource = resolvep8(g_szParms);
			g_iLineType = TYPE_DIR;
			g_iErrorNo ^= ERROR_UNKOP;
		}
	}
