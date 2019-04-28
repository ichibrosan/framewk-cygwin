// $Log: dotequ.hpp,v $
// Revision 1.2  2011/03/25 21:47:31  doug
// *** empty log message ***
//
// Revision 1.1  2011/03/25 07:19:17  doug
// Initial revision
//

char dir_dotequ[] = "$Id: dotequ.hpp,v 1.2 2011/03/25 21:47:31 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.
	
	if(0 == strcmp(strupr(g_szOpcode),".EQU")) {
		fprintf(g_flog,"Processing .EQU directive\n");
		if(0 != strlen(g_szParms)) {
			g_iLineType = TYPE_DIR;
	  g_pCSymbols->add(g_szLabel,TYPE_U8, 
			   (unsigned char)resolvep64(g_szParms));
	  g_pCSymbols->add(g_szLabel,TYPE_U16,
			   (unsigned int)resolvep64(g_szParms));
	  g_pCSymbols->add(g_szLabel,TYPE_U32,
			   (unsigned long)resolvep64(g_szParms));
	  g_pCSymbols->add(g_szLabel,TYPE_U64,
			   (unsigned long long)resolvep64(g_szParms));
			g_iErrorNo ^= ERROR_UNKOP;
		} 
	}
