// $Log: rst_85.hpp,v $
// Revision 1.2  2011/03/25 22:47:07  doug
// add log and trim gpl stuff
////

char rst_85[] = "$Id: rst_85.hpp,v 1.2 2011/03/25 22:47:07 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

if(0 == strcmp(strupr(g_szOpcode),"RST")) {
	fprintf(g_flog,"Processing 8085 RST g_szOpcode\n");
        g_iLineType = TYPE_8085;
	g_iErrorNo ^= ERROR_UNKOP;
	if(0 < strlen(g_szParms)) {
		switch(g_szParms[0]) {
			case '0':
				g_ucBytes[g_iBytesIndex++] = 0xC7;
				break;
			case '1':
                                g_ucBytes[g_iBytesIndex++] = 0xCF;
                                break;
			case '2':
                                g_ucBytes[g_iBytesIndex++] = 0xD7;
                                break;
			case '3':
                                g_ucBytes[g_iBytesIndex++] = 0xDF;
                                break;
			case '4':
                                g_ucBytes[g_iBytesIndex++] = 0xE7;
                                break;
			case '5':
                                g_ucBytes[g_iBytesIndex++] = 0xEF;
                                break;
			case '6':
                                g_ucBytes[g_iBytesIndex++] = 0xF7;
                                break;
			case '7':
                                g_ucBytes[g_iBytesIndex++] = 0xFF;
                                break;
			default:
				g_iErrorNo |= ERROR_NOVEC;
				break;
		}
	} else {
		g_iErrorNo |= ERROR_NOPARM;
	}
}

///////////////////
// eof - rst.hpp //
///////////////////

