// $Log: dcr_85.hpp,v $
// Revision 1.2  2011/03/25 22:47:07  doug
// add log and trim gpl stuff
////

char dcr_85[] = "$Id: dcr_85.hpp,v 1.2 2011/03/25 22:47:07 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

if(0 == strcmp(strupr(g_szOpcode),"DCR")) {
	TRACE("processing 8085 dcr g_szOpcode");
	fprintf(g_flog,"Processing 8085 DCR g_szOpcode\n");
	g_iErrorNo ^= ERROR_UNKOP;
	g_iLineType = TYPE_8085;
	if(0 < strlen(g_szParms)) {
		switch(g_szParms[0]) {
			case 'a':
			case 'A':
				g_ucBytes[g_iBytesIndex++] = 0x3D;
				break;
                        case 'b':
			case 'B':
                                g_ucBytes[g_iBytesIndex++] = 0x05;
                                break;
                        case 'c':
			case 'C':
                                g_ucBytes[g_iBytesIndex++] = 0x0D;
                                break;
                        case 'd':
			case 'D':
                                g_ucBytes[g_iBytesIndex++] = 0x15;
                                break;
                        case 'e':
			case 'E':
                                g_ucBytes[g_iBytesIndex++] = 0x1D;
                                break;
                        case 'h':
			case 'H':
                                g_ucBytes[g_iBytesIndex++] = 0x25;
                                break;
                        case 'l':
			case 'L':
                                g_ucBytes[g_iBytesIndex++] = 0x2D;
                                break;
                        case 'm':
			case 'M':
                                g_ucBytes[g_iBytesIndex++] = 0x35;
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
// eof - dcr.hpp //
///////////////////

