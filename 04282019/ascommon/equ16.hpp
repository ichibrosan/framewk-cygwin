// $Log: equ16.hpp,v $
// Revision 1.2  2011/03/25 21:47:31  doug
// *** empty log message ***
//
// Revision 1.1  2011/03/25 07:19:17  doug
// Initial revision
//

char dir_equ16[] = "$Id: equ16.hpp,v 1.2 2011/03/25 21:47:31 doug Exp doug $";

// Copyright(c)2011 Douglas W. Goodall, United States.
	
	if(0 == strcmp(strupr(g_szOpcode),"EQU16")) {
		fprintf(g_flog,"Processing EQU16 directive\n");
		if(0 != strlen(g_szParms)) {
			g_iLineType = TYPE_DIR;
			g_pCSymbols->add(g_szLabel,TYPE_U16,(unsigned int)resolvep16(g_szParms));
			g_bU16 = TRUE;
			g_iErrorNo ^= ERROR_UNKOP;
		} 
	}
