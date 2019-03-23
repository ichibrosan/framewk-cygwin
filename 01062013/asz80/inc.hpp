// ---------------------------------------------------
// INC.HPP      28-Jan-11 DOSBox-0.74 Version 1.00.00a
// Serial No. 8208-4162-344865    All Rights Reserved.
// Copyright (C) 2010 Douglas Goodall,  United States.
// ---------------------------------------------------

if(0 == strcmp(strupr(g_szOpcode),"INC")) {
	fprintf(g_flog,"...processing INC g_szOpcode...\n");
	g_iErrorNo ^= ERROR_UNKOP;

	if(0 < strlen(g_szParms)) {
		switch(g_szParms[0]) {
			case 'A':
			case 'a':
				g_ucBytes[g_iBytesIndex++] = 0x3c;
				break;
			case 'B':
			case 'b':
				g_ucBytes[g_iBytesIndex++] = 0x04;
				break;
			case 'C':
			case 'c':
                        	g_ucBytes[g_iBytesIndex++] = 0x0c;
				break;
			case 'D':
			case 'd':                
                        	g_ucBytes[g_iBytesIndex++] = 0x14;
				break;
                	case 'E':
			case 'e':
                        	g_ucBytes[g_iBytesIndex++] = 0x1c;
				break;
			case 'H':
			case 'h':                
                        	g_ucBytes[g_iBytesIndex++] = 0x24;
				break;
			case 'L':
			case 'l':                  
                        	g_ucBytes[g_iBytesIndex++] = 0x2c;
				break;
		}
  
		if(0 == strcmp(strupr(g_szParms),"BC")) {
			g_ucBytes[g_iBytesIndex++] = 0x03;
		}
		if(0 == strcmp(strupr(g_szParms),"DE")) {
			g_ucBytes[g_iBytesIndex++] = 0x13;
		}
		if(0 == strcmp(strupr(g_szParms),"HL")) {
			g_ucBytes[g_iBytesIndex++] = 0x23;
		}
		if(0 == strcmp(strupr(g_szParms),"IX")) {
			g_ucBytes[g_iBytesIndex++] = 0xdd;
			g_ucBytes[g_iBytesIndex++] = 0x23;
		}
		if(0 == strcmp(strupr(g_szParms),"IY")) {
			g_ucBytes[g_iBytesIndex++] = 0xfd;
			g_ucBytes[g_iBytesIndex++] = 0x23;
		}
		if(0 == strcmp(strupr(g_szParms),"L")) {
			g_ucBytes[g_iBytesIndex++] = 0x2c;
		}
		if(0 == strcmp(strupr(g_szParms),"SP")) {
			g_ucBytes[g_iBytesIndex++] = 0x33;
		}
		if(0 == strcmp(strupr(g_szParms),"(HL)")) {
			g_ucBytes[g_iBytesIndex++] = 0x34;
		}
	} else {
		g_iErrorNo |= ERROR_NOPARM;
	}
}

