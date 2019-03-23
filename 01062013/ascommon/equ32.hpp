// $Log: equ32.hpp,v $
// Revision 1.2  2011/03/25 21:47:31  doug
// *** empty log message ***
//
// Revision 1.1  2011/03/25 07:19:17  doug
// Initial revision
//

char dir_equ32[] = "$Id: equ32.hpp,v 1.2 2011/03/25 21:47:31 doug Exp doug $";

// Copyright(c)2011 Douglas W. Goodall, United States.
	
	if(0 == strcmp(strupr(g_szOpcode),"EQU32")) {
		fprintf(g_flog,"Processing EQU32 directive\n");
		if(0 != strlen(g_szParms)) {
			g_iLineType = TYPE_DIR;
			g_pCSymbols->add(g_szLabel,TYPE_U32,(unsigned long)resolvep32(g_szParms));
			g_bU32 = TRUE;
			g_iErrorNo ^= ERROR_UNKOP;
		} 
	}
