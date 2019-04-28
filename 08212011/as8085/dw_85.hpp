// $Log: dw_85.hpp,v $
// Revision 1.2  2011/03/25 22:47:07  doug
// add log and trim gpl stuff
////

char dw_85[] = "$Id: dw_85.hpp,v 1.2 2011/03/25 22:47:07 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

        if(0 == strcmp(strupr(g_szOpcode),"DW")) {
                fprintf(g_flog,"Processing DW directive\n");
                g_iLineType = TYPE_DIR;
                g_iErrorNo ^= ERROR_UNKOP;
		int iCommas = iCommaCount(g_szParms);
		if(0 < iCommas) {
			for(int q=0;q<iCommas+1;q++) {
				char * p = pszParmN(g_szParms,q);
				unsigned int uiTemp = resolvep16(p);
				g_ucBytes[g_iBytesIndex++] = uiTemp & 255;
				g_ucBytes[g_iBytesIndex++] = uiTemp >> 8; 
			}
		} else {
                	unsigned int uiTemp = resolvep16(g_szParms);
                	fprintf(g_flog,"uiTemp is 0x%04X\n",uiTemp);
                	g_ucBytes[g_iBytesIndex++] = uiTemp & 255;
			g_ucBytes[g_iBytesIndex++] = uiTemp >> 8;
		}

        }

//////////////////
// eof - dw.hpp //
//////////////////

