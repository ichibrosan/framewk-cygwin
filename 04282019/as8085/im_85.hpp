// $Log: im_85.hpp,v $
// Revision 1.2  2011/03/25 22:47:07  doug
// add log and trim gpl stuff
////

char im_85[] = "$Id: im_85.hpp,v 1.2 2011/03/25 22:47:07 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

if(0 == strcmp(strupr(g_szOpcode),"IM")) {
	fprintf(g_flog,"Processing 8085 IM g_szOpcode\n");
        g_iLineType = TYPE_8085;
        g_iErrorNo ^= ERROR_UNKOP;
        g_ucBytes[g_iBytesIndex++] = 0xed;
	if(0 < strlen(g_szParms)) {
		switch(g_szParms[0]) {
			case '0':
				g_ucBytes[g_iBytesIndex++] = 0x46;
				break;
			case '1':
				g_ucBytes[g_iBytesIndex++] = 0x56;
				break;
			case '2':			
				g_ucBytes[g_iBytesIndex++] = 0x5e;
				break;
			default:
				g_iErrorNo |= ERROR_NOMODE;
				break;
		}
	} else {
		g_iErrorNo |= ERROR_NOPARM;
	}
}

//////////////////
// eof - im.hpp //
//////////////////

