// $Log$
//

char dir_public[] = "$Id$";

// Copyright(c)2011 Douglas W. Goodall, United States.
	
if(0 == strcmp(strupr(g_szOpcode),"PUBLIC8")) {
	fprintf(g_flog,"Processing PUBLIC8 directive\n");
        g_iErrorNo ^= ERROR_UNKOP;
        g_iLineType = TYPE_DIR;
	if(0 != strlen(g_szParms)) {
		int rc;
		g_pCSymbols->getu8(g_szParms,&rc);
		if(EXIT_SUCCESS == rc) {
			g_pCSymbols->add(g_szParms,TYPE_P8,(unsigned char)0);
			g_bP8 = TRUE;
		} else {
			g_iErrorNo |= ERROR_UNK_PUB;
		}
	} 
}

if(0 == strcmp(strupr(g_szOpcode),"PUBLIC16")) {
        fprintf(g_flog,"Processing PUBLIC16 directive\n");
        g_iErrorNo ^= ERROR_UNKOP;
        g_iLineType = TYPE_DIR;
        if(0 != strlen(g_szParms)) {
		int rc;
		g_pCSymbols->getu16(g_szParms,&rc);
		if(EXIT_SUCCESS == rc) {
                	g_pCSymbols->add(g_szParms,TYPE_P16,(unsigned int)0);
			g_bP16 = TRUE;
		} else {
                        g_iErrorNo |= ERROR_UNK_PUB;
		}
        }
}

if(0 == strcmp(strupr(g_szOpcode),"PUBLIC32")) {
        fprintf(g_flog,"Processing PUBLIC32 directive\n");
        g_iErrorNo ^= ERROR_UNKOP;
        g_iLineType = TYPE_DIR;
        if(0 != strlen(g_szParms)) {
		int rc;
		g_pCSymbols->getu32(g_szParms,&rc);
		if(EXIT_SUCCESS == rc) {
                	g_pCSymbols->add(g_szParms,TYPE_P32,(unsigned long)0);
			g_bP32 = TRUE;
        	} else {
			g_iErrorNo |= ERROR_UNK_PUB;
		}
	}
}

if(0 == strcmp(strupr(g_szOpcode),"PUBLIC64")) {
        fprintf(g_flog,"Processing PUBLIC64 directive\n");
        g_iErrorNo ^= ERROR_UNKOP;
        g_iLineType = TYPE_DIR;
        if(0 != strlen(g_szParms)) {
		int rc;
		g_pCSymbols->getu64(g_szParms,&rc);
		if(EXIT_SUCCESS == rc) {
                	g_pCSymbols->add(g_szParms,TYPE_P64,(unsigned long long)0);
			g_bP64 = TRUE;
		} else {
			g_iErrorNo |= ERROR_UNK_PUB;
		}
        }
}

////////////////////
// eof public.hpp //
////////////////////

