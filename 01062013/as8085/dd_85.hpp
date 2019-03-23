// $Log$
// 

char dd_85[] = "$Id: dd_85.hpp,v 1.2 2011/03/25 22:47:07 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

        if(0 == strcmp(strupr(g_szOpcode),"DD")) {
                fprintf(g_flog,"Processing DD directive\n");
                g_iLineType = TYPE_DIR;
                g_iErrorNo ^= ERROR_UNKOP;
		int iCommas = iCommaCount(g_szParms);
		if(0 < iCommas) {
			for(int q=0;q<iCommas+1;q++) {
				char * p = pszParmN(g_szParms,q);
				unsigned long ulTemp = resolvep32(p);
        	      		unsigned int  uiTempl = (unsigned int)ulTemp & 0x0000ffffL;
	              		unsigned int  uiTemph = (unsigned int)ulTemp >> 16;
                		g_ucBytes[g_iBytesIndex++] = uiTempl & 0x00ff;
                		g_ucBytes[g_iBytesIndex++] = uiTempl >> 8;
                		g_ucBytes[g_iBytesIndex++] = uiTemph & 0x00ff;
	              		g_ucBytes[g_iBytesIndex++] = uiTemph >> 8;
			}
		} else {
              		unsigned long lTemp = resolvep32(g_szParms);
              		unsigned int  uiTempl = (unsigned int)lTemp & 0x0000ffffL;
              		unsigned int  uiTemph = (unsigned int)lTemp >> 16;
                	g_ucBytes[g_iBytesIndex++] = uiTempl & 0x00ff;
                	g_ucBytes[g_iBytesIndex++] = uiTempl >> 8;
                	g_ucBytes[g_iBytesIndex++] = uiTemph & 0x00ff;
              		g_ucBytes[g_iBytesIndex++] = uiTemph >> 8;
		}

        }

/////////////////////
// eof - dw_85.hpp //
/////////////////////

