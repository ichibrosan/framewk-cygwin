// $Log: extrn.hpp,v $
// Revision 1.2  2011/04/05 10:28:17  doug
// value is unused
//
// Revision 1.1  2011/04/05 10:20:20  doug
// Initial revision
//
//

char dir_extrn[] = "$Id: extrn.hpp,v 1.2 2011/04/05 10:28:17 doug Exp doug $";

// Copyright(c)2011 Douglas W. Goodall, United States.
	
if(0 == strcmp(strupr(g_szOpcode),"EXTRN8")) {
	fprintf(g_flog,"Processing EXTRN8 directive\n");
	if(0 != strlen(g_szParms)) {
		g_iLineType = TYPE_DIR;
		g_pCSymbols->add(g_szParms,TYPE_E8,(unsigned char)0);
		g_bE8 = TRUE;
		g_iErrorNo ^= ERROR_UNKOP;
	} 
}

if(0 == strcmp(strupr(g_szOpcode),"EXTRN16")) {
        fprintf(g_flog,"Processing EXTRN16 directive\n");
        if(0 != strlen(g_szParms)) {
                g_iLineType = TYPE_DIR;
                g_pCSymbols->add(g_szParms,TYPE_E16,(unsigned int)0);
		g_bE16 = TRUE;
                g_iErrorNo ^= ERROR_UNKOP;
        }
}

if(0 == strcmp(strupr(g_szOpcode),"EXTRN32")) {
        fprintf(g_flog,"Processing EXTRN32 directive\n");
        if(0 != strlen(g_szParms)) {
                g_iLineType = TYPE_DIR;
                g_pCSymbols->add(g_szParms,TYPE_E32,(unsigned long)0);
		g_bE32 = TRUE;
                g_iErrorNo ^= ERROR_UNKOP;
        }
}

if(0 == strcmp(strupr(g_szOpcode),"EXTRN64")) {
        fprintf(g_flog,"Processing EXTRN64 directive\n");
        if(0 != strlen(g_szParms)) {
                g_iLineType = TYPE_DIR;
                g_pCSymbols->add(g_szParms,TYPE_E64,(unsigned long long)0);
		g_bE64 = TRUE;
                g_iErrorNo ^= ERROR_UNKOP;
        }
}

///////////////////
// eof extrn.hpp //
///////////////////

