
// $Log: dq_85.hpp,v $
// Revision 1.2  2011/03/25 22:47:07  doug
// add log and trim gpl stuff
////

char dq_85[] = "$Id: dq_85.hpp,v 1.2 2011/03/25 22:47:07 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

//if(0 == strcmp(strupr(g_szOpcode),"DQ")) {
//	fprintf(g_flog,"Processing 8085 DQ  g_szOpcode\n");
//       g_iLineType = TYPE_8085;
//        g_iErrorNo ^= ERROR_UNKOP;
//	if(0 < strlen(g_szParms)) {
//		unsigned long long llTemp = resolvep64(g_szParms);
//		unsigned long       lTempl = llTemp&0x00000000ffffffffLL;
//		unsigned long       lTemph = llTemp>>32;
//		unsigned long lTemp = lTempl;
//		unsigned int  uiTempl = (unsigned int)lTemp & 0x0000ffffL;
//		unsigned int  uiTemph = (unsigned int)lTemp >> 16;
//                g_ucBytes[g_iBytesIndex++] = uiTempl & 0x00ff;
//                g_ucBytes[g_iBytesIndex++] = uiTempl >> 8;
//                g_ucBytes[g_iBytesIndex++] = uiTemph & 0x00ff;
//		g_ucBytes[g_iBytesIndex++] = uiTemph >> 8;
//                lTemp = lTemph;
//                uiTempl = (unsigned int)lTemp & 0x0000ffffL;
//                uiTemph = (unsigned int)lTemp >> 16;
//                g_ucBytes[g_iBytesIndex++] = uiTempl & 0x00ff;
//                g_ucBytes[g_iBytesIndex++] = uiTempl >> 8;
//                g_ucBytes[g_iBytesIndex++] = uiTemph & 0x00ff;
//                g_ucBytes[g_iBytesIndex++] = uiTemph >> 8;
//	} else {
//		g_iErrorNo |= ERROR_NOPARM;
//	}
//}

        if(0 == strcmp(strupr(g_szOpcode),"DQ")) {
                fprintf(g_flog,"Processing DQ directive\n");
                g_iLineType = TYPE_DIR;
                g_iErrorNo ^= ERROR_UNKOP;
		int iCommas = iCommaCount(g_szParms);
		if(0 < iCommas) {
			for(int q=0;q<iCommas+1;q++) {
				char * p = pszParmN(g_szParms,q);
              			unsigned long long llTemp  = resolvep64(p);
             			unsigned long       lTempl = llTemp&0x00000000ffffffffLL;
              			unsigned long       lTemph = llTemp>>32;
              			unsigned long  lTemp  = lTempl;
              			unsigned int  uiTempl = (unsigned int)lTemp & 0x0000ffffL;
              			unsigned int  uiTemph = (unsigned int)lTemp >> 16;
                		g_ucBytes[g_iBytesIndex++] = uiTempl & 0x00ff;
                		g_ucBytes[g_iBytesIndex++] = uiTempl >> 8;
                		g_ucBytes[g_iBytesIndex++] = uiTemph & 0x00ff;
              			g_ucBytes[g_iBytesIndex++] = uiTemph >> 8;
                		lTemp = lTemph;
                		uiTempl = (unsigned int)lTemp & 0x0000ffffL;
                		uiTemph = (unsigned int)lTemp >> 16;
                		g_ucBytes[g_iBytesIndex++] = uiTempl & 0x00ff;
                		g_ucBytes[g_iBytesIndex++] = uiTempl >> 8;
                		g_ucBytes[g_iBytesIndex++] = uiTemph & 0x00ff;
                		g_ucBytes[g_iBytesIndex++] = uiTemph >> 8;
			}
		} else {
              		unsigned long long llTemp = resolvep64(g_szParms);
              		unsigned long       lTempl = llTemp&0x00000000ffffffffLL;
              		unsigned long       lTemph = llTemp>>32;
              		unsigned long lTemp = lTempl;
              		unsigned int  uiTempl = (unsigned int)lTemp & 0x0000ffffL;
              		unsigned int  uiTemph = (unsigned int)lTemp >> 16;
                	g_ucBytes[g_iBytesIndex++] = uiTempl & 0x00ff;
                	g_ucBytes[g_iBytesIndex++] = uiTempl >> 8;
                	g_ucBytes[g_iBytesIndex++] = uiTemph & 0x00ff;
              		g_ucBytes[g_iBytesIndex++] = uiTemph >> 8;
                	lTemp = lTemph;
               		uiTempl = (unsigned int)lTemp & 0x0000ffffL;
               		uiTemph = (unsigned int)lTemp >> 16;
               		g_ucBytes[g_iBytesIndex++] = uiTempl & 0x00ff;
                	g_ucBytes[g_iBytesIndex++] = uiTempl >> 8;
                	g_ucBytes[g_iBytesIndex++] = uiTemph & 0x00ff;
                	g_ucBytes[g_iBytesIndex++] = uiTemph >> 8;
		}
        }

/////////////////////
// eof - dq_85.hpp //
/////////////////////


















//////////////////
// eof - dq.hpp //
//////////////////

