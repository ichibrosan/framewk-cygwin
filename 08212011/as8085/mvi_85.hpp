// $Log: mvi_85.hpp,v $
// Revision 1.2  2011/03/25 22:47:07  doug
// add log and trim gpl stuff
////

char mvi_85[] = "$Id: mvi_85.hpp,v 1.2 2011/03/25 22:47:07 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

// 3/23/2011 dwg - fixed binary "mvi a,"

if(0 == strcmp(strupr(g_szOpcode),"MVI")) {
	fprintf(g_flog,"Processing 8085 MVI g_szOpcode\n");
        g_iErrorNo ^= ERROR_UNKOP;
	g_iLineType = TYPE_8085;
	if(0 < strlen(g_szParms)) {
		switch(g_szParms[0]) {
			case 'a':
			case 'A':
				g_ucBytes[g_iBytesIndex++] = 0x3E;
				g_ucBytes[g_iBytesIndex++] = resolvep8(&g_szParms[2])&255;	
				break;	
			case 'b':
			case 'B':
				g_ucBytes[g_iBytesIndex++] = 0x06;
				g_ucBytes[g_iBytesIndex++] = resolvep8(&g_szParms[2])&255;	
				break;
			case 'c':
			case 'C':
				g_ucBytes[g_iBytesIndex++] = 0x0E;
				g_ucBytes[g_iBytesIndex++] = resolvep8(&g_szParms[2])&255;	
				break;
			case 'd':
			case 'D':
				g_ucBytes[g_iBytesIndex++] = 0x16;
				g_ucBytes[g_iBytesIndex++] = resolvep8(&g_szParms[2])&255;	
				break;
			case 'e':
			case 'E':
				g_ucBytes[g_iBytesIndex++] = 0x1E;
				g_ucBytes[g_iBytesIndex++] = resolvep8(&g_szParms[2])&255;	
				break;
			case 'h':
			case 'H':
				g_ucBytes[g_iBytesIndex++] = 0x26;
				g_ucBytes[g_iBytesIndex++] = resolvep8(&g_szParms[2])&255;	
				break;
			case 'l':
			case 'L':
				g_ucBytes[g_iBytesIndex++] = 0x2E;
				g_ucBytes[g_iBytesIndex++] = resolvep8(&g_szParms[2])&255;	
				break;
			case 'm':
			case 'M':
				g_ucBytes[g_iBytesIndex++] = 0x36;
				g_ucBytes[g_iBytesIndex++] = resolvep8(&g_szParms[2])&255;	
				break;
			default:
				g_iErrorNo |= ERROR_NOREG;
				break;
		}
	} else {
		g_iErrorNo |= ERROR_NOPARM;
	}
}

///////////////////
// eof - mvi.hpp //
///////////////////

