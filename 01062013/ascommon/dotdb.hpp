// dotdb.hpp 5/18/2011 dwg - derived from db.hpp

char dir_dotdb[] = "$Id$";

// Copyright(c)2011 Douglas W. Goodall, United States.
	
        if(0 == strcmp(strupr(g_szOpcode),".DB")) {
                fprintf(g_flog,"Processing .DB directive\n");
		int iCommas = iCommaCount(g_szParms);
		if(0 < iCommas) {
			for(int q=0;q<iCommas+1;q++) {
				char * p = pszParmN(g_szParms,q);
//printf("DEBUG: DB handler multi returned %s\n",p);
				g_ucBytes[g_iBytesIndex++] = resolvep8(p);
			}
                        g_iLineType = TYPE_DIR;
                        g_iErrorNo ^= ERROR_UNKOP;

		} else {
                	unsigned char ucTemp = resolvep8(g_szParms)&255;
                	fprintf(g_flog,"ucTemp is 0x%02X\n",ucTemp);
                	g_ucBytes[g_iBytesIndex++] = ucTemp;
                	g_iLineType = TYPE_DIR;
                	g_iErrorNo ^= ERROR_UNKOP;
		}

        }

//////////////////
// eof - db.hpp //
//////////////////
