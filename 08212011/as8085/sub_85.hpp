// $Log: sub_85.hpp,v $
// Revision 1.2  2011/03/25 22:47:07  doug
// add log and trim gpl stuff
////

char sub_85[] = "$Id: sub_85.hpp,v 1.2 2011/03/25 22:47:07 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

if(0 == strcmp(strupr(g_szOpcode),"SUB")) {
	fprintf(g_flog,"Processing 8085 SUB`g_szOpcode\n");
        g_iLineType = TYPE_8085;
	g_iErrorNo ^= ERROR_UNKOP;
	if(0 < strlen(g_szParms)) {
		switch(g_szParms[0]) {
			case 'a':
			case 'A':
				g_ucBytes[g_iBytesIndex++] = 0x97;
				break;
                        case 'b':
			case 'B':
                                g_ucBytes[g_iBytesIndex++] = 0x90;
                                break;
                        case 'c':
			case 'C':
                                g_ucBytes[g_iBytesIndex++] = 0x91;
                                break;
                        case 'd':
			case 'D':
                                g_ucBytes[g_iBytesIndex++] = 0x92;
                                break;
                        case 'e':
			case 'E':
                                g_ucBytes[g_iBytesIndex++] = 0x93;
                                break;
                        case 'h':
			case 'H':
                                g_ucBytes[g_iBytesIndex++] = 0x94;
                                break;
                        case 'l':
			case 'L':
                                g_ucBytes[g_iBytesIndex++] = 0x95;
                                break;
                        case 'm':
			case 'M':
                                g_ucBytes[g_iBytesIndex++] = 0x96;
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
// eof - sub.hpp //
///////////////////

