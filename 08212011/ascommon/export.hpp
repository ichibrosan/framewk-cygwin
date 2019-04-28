// $Log$
//

char dir_export[] = "$Id$";

// Copyright(c)2011 Douglas W. Goodall, United States.

if(0 == strcmp(strupr(g_szOpcode),"EXPORT")) {
        fprintf(g_flog,"Processing EXPORT directive\n");
        g_iErrorNo ^= ERROR_UNKOP;
        g_iLineType = TYPE_DIR;
        if(0 != strlen(g_szParms)) {
		g_bExported = TRUE;
                int rc;
                unsigned int uiBuffer;
                uiBuffer = g_pCSymbols->getu16(g_szParms,&rc);
                if(EXIT_SUCCESS == rc) {
                        if(TRUE == g_bPass2) {
                                fprintf(g_fexp,"%s\tequ\t$%05X\n",
                                        g_szParms,uiBuffer);
                        }
                } else {
                        g_iErrorNo |= ERROR_UNK_EXP;
                }
        }
}


	
if(0 == strcmp(strupr(g_szOpcode),"EXPORT8")) {
	fprintf(g_flog,"Processing EXPORT8 directive\n");
        g_iErrorNo ^= ERROR_UNKOP;
        g_iLineType = TYPE_DIR;
	if(0 != strlen(g_szParms)) {
                g_bExported = TRUE;
		int rc;
		unsigned char ucBuffer;
		ucBuffer = g_pCSymbols->getu8(g_szParms,&rc);
		if(EXIT_SUCCESS == rc) {
			if(TRUE == g_bPass2) {
				fprintf(g_fexp,"%s\tequ8\t$%03X\n",
					g_szParms,ucBuffer);
			}
		} else {
			g_iErrorNo |= ERROR_UNK_EXP;
		}
	} 
}

if(0 == strcmp(strupr(g_szOpcode),"EXPORT16")) {
        fprintf(g_flog,"Processing EXPORT16 directive\n");
        g_iErrorNo ^= ERROR_UNKOP;
        g_iLineType = TYPE_DIR;
        if(0 != strlen(g_szParms)) {
                g_bExported = TRUE;
		int rc;
		unsigned int uiBuffer;
		uiBuffer = g_pCSymbols->getu16(g_szParms,&rc);
		if(EXIT_SUCCESS == rc) {
			if(TRUE == g_bPass2) {
				fprintf(g_fexp,"%s\tequ16\t$%05X\n",
					g_szParms,uiBuffer);
			}
		} else {
                        g_iErrorNo |= ERROR_UNK_EXP;
		}
        }
}

if(0 == strcmp(strupr(g_szOpcode),"EXPORT32")) {
        fprintf(g_flog,"Processing EXPORT32 directive\n");
        g_iErrorNo ^= ERROR_UNKOP;
        g_iLineType = TYPE_DIR;
        if(0 != strlen(g_szParms)) {
                g_bExported = TRUE;
		int rc;
		unsigned long ulBuffer;
		ulBuffer = g_pCSymbols->getu32(g_szParms,&rc);
		if(EXIT_SUCCESS == rc) {
			if(TRUE == g_bPass2) {
				fprintf(g_fexp,"%s\tequ32\t$%09X\n",
					g_szParms,ulBuffer);
			}
        	} else {
			g_iErrorNo |= ERROR_UNK_EXP;
		}
	}
}

if(0 == strcmp(strupr(g_szOpcode),"EXPORT64")) {
        fprintf(g_flog,"Processing EXPORT64 directive\n");
        g_iErrorNo ^= ERROR_UNKOP;
        g_iLineType = TYPE_DIR;
        if(0 != strlen(g_szParms)) {
                g_bExported = TRUE;
		int rc;
		unsigned long long ullBuffer;
		ullBuffer = g_pCSymbols->getu64(g_szParms,&rc);
		if(EXIT_SUCCESS == rc) {
			if(TRUE == g_bPass2) {
				fprintf(g_fexp,"%s\tequ64\t$)017X\n",
					g_szParms,ullBuffer);
			}
		} else {
			g_iErrorNo |= ERROR_UNK_EXP;
		}
        }
}

////////////////////
// eof export.hpp //
////////////////////

