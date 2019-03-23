// $Log: out_85.hpp,v $
// Revision 1.2  2011/03/25 22:47:07  doug
// add log and trim gpl stuff
////

char out_85[] = "$Id: out_85.hpp,v 1.2 2011/03/25 22:47:07 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

if(0 == strcmp(strupr(g_szOpcode),"OUT")) {
	fprintf(g_flog,"Processing 8085 OUT g_szOpcode\n");
        g_iLineType = TYPE_8085;
        g_iErrorNo ^= ERROR_UNKOP;
	g_ucBytes[g_iBytesIndex++] = 0xD3;
	if(0 < strlen(g_szParms)) {
		g_ucBytes[g_iBytesIndex++] = resolvep8(g_szParms)&255;
	} else {
		g_iErrorNo |= ERROR_NOPARM;
	}
}

///////////////////
// eof - out.hpp //
///////////////////

