// ---------------------------------------------------
// sub.hpp       4-Mar-11 DOSBox-0.74 Version 1.00.00a
// Serial No. 8208-4162-344865    All Rights Reserved.
// Copyright (C) 2010 Douglas Goodall,  United States.
// ---------------------------------------------------

if( 0 == strcmp(strupr(g_szOpcode),"SUB") ) {
  	char szSUBtemp[DEFAULT_STRSIZE];
  	char szSUBtemp2[DEFAULT_STRSIZE];
  	char * psz;
  	unsigned int uiTemp;
  	strcpy(szSUBtemp2,g_szParms);
  	strcpy(szSUBtemp,strupr(szSUBtemp2));
  	fprintf(g_flog,"...processing SUB g_szOpcode...\n");
  	g_iErrorNo ^= ERROR_UNKOP;
  	g_iLineType = TYPE_Z80;

// sub (hl)
// sub (ix+d)
// sub (iy+d)
// sub r
// sub n
//

 	if(0 < strlen(g_szParms)) {
		int bDone = FALSE;

    		// 3/4/2011 dwg - sub (hl)
    		if(0 == strcmp(strupr(g_szParms),"(HL)")) {
      			g_ucBytes[g_iBytesIndex++] = 0x96;
			bDone = TRUE;
    		}

    		// sub (ix+d)
      		if(0 == strncmp("(IX+",szSUBtemp,4)) {
    		  	for(int i=4;i<strlen(szSUBtemp);i++) {
        			if(')' == szSUBtemp[i]) {
          				szSUBtemp[i] = 0;
        			}
     			}
      			g_ucBytes[g_iBytesIndex++] = 0xDD;
      			g_ucBytes[g_iBytesIndex++] = 0x96;
      			psz = &szSUBtemp[4];
      			#include "../ascommon/_disp.hpp"
			bDone = TRUE;
    		}

  		// sub (iy+d)
    		if(0 == strncmp("(IY+",szSUBtemp,4)) {
      			for(int i=4;i<strlen(szSUBtemp);i++) {
        			if(')' == szSUBtemp[i]) {
          				szSUBtemp[i] = 0;
        			}
      			}
      			g_ucBytes[g_iBytesIndex++] = 0xFD;
      			g_ucBytes[g_iBytesIndex++] = 0x96;
      			psz = &szSUBtemp[4];
      			#include "../ascommon/_disp.hpp"
			bDone = TRUE;
    		}	   			

 		// sub r
		if(FALSE == bDone ) {
      			bDone = TRUE;
			switch(g_szParms[0]) {
  				case 'B':
				case 'b':
	  				g_ucBytes[g_iBytesIndex++] = 0x80 + 0x10 + 0x00;
	  				break;
				case 'C':
				case 'c':
	  				g_ucBytes[g_iBytesIndex++] = 0x80 + 0x10 + 0x01;
	  				break;
				case 'D':
				case 'd':
	  				g_ucBytes[g_iBytesIndex++] = 0x80 + 0x10 + 0x02;
	 				break;
        			case 'E':
				case 'e':
          				g_ucBytes[g_iBytesIndex++] = 0x80 + 0x10 + 0x03;
          				break;
        			case 'H':
				case 'h':
          				g_ucBytes[g_iBytesIndex++] = 0x80 + 0x10 + 0x04;
          				break;
        			case 'L':
				case 'l':
          				g_ucBytes[g_iBytesIndex++] = 0x80 + 0x10 + 0x05;
          				break;
        			case 'A':
				case 'a':
          				g_ucBytes[g_iBytesIndex++] = 0x80 + 0x10 + 0x07;
          				break;
				default:
					bDone = FALSE;
					break;
			}
      		}
  
		if(FALSE == bDone) {
    			// sub n
   			g_ucBytes[g_iBytesIndex++] = 0xD6;
    			g_ucBytes[g_iBytesIndex++] = resolvep8(g_szParms);
		}
  	} else {
    		g_iErrorNo |= ERROR_NOPARM;
  	}
}

//////////////////
// eof - add.hpp //
//////////////////

