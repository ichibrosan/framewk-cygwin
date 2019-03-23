// $Log: sbr_85.hpp,v $
// Revision 1.2  2011/03/25 22:47:07  doug
// add log and trim gpl stuff
////

char sbr_85[] = "$Id: sbr_85.hpp,v 1.2 2011/03/25 22:47:07 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

if(0 == strcmp(strupr(g_szOpcode),"SBR")) {
	fprintf(g_flog,"Processing 8085 SBR g_szOpcode\n");
        g_ucBytes[g_iBytesIndex++] = 0x9F;
        g_iLineType = TYPE_8085;
	if(0 < strlen(g_szParms)) {
		switch(g_szParms[0]) {
			case 'a':
			case 'A':
				g_ucBytes[g_iBytesIndex++] = 0x9F;
				break;
                        case 'b':
			case 'B':
                                g_ucBytes[g_iBytesIndex++] = 0x98;
                                break;
                        case 'c':
			case 'C':
                                g_ucBytes[g_iBytesIndex++] = 0x99;
                                break;
                        case 'd':
			case 'D':
                                g_ucBytes[g_iBytesIndex++] = 0x9A;
                                break;
                        case 'e':
			case 'E':
                                g_ucBytes[g_iBytesIndex++] = 0x9B;
                                break;
                        case 'h':
			case 'H':
                                g_ucBytes[g_iBytesIndex++] = 0x9C;
                                break;
                        case 'l':
			case 'L':
                                g_ucBytes[g_iBytesIndex++] = 0x9D;
                                break;
			case 'm':
                        case 'M':
                                g_ucBytes[g_iBytesIndex++] = 0x9E;
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
// eof - sbr.hpp //
///////////////////

