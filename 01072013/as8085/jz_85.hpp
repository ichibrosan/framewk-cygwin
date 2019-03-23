// $Log: jz_85.hpp,v $
// Revision 1.2  2011/03/25 22:47:07  doug
// add log and trim gpl stuff
////

char jz_85[] = "$Id: jz_85.hpp,v 1.2 2011/03/25 22:47:07 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

if(0 == strcmp(strupr(g_szOpcode),"JZ")) {
	fprintf(g_flog,"Processing 8085 JZ g_szOpcode\n");
        g_iLineType = TYPE_8085;
        g_iErrorNo ^= ERROR_UNKOP;
	g_ucBytes[g_iBytesIndex++] = 0xCA;
	if(0 < strlen(g_szParms)) {
		value = resolvep16(g_szParms);
		g_ucBytes[g_iBytesIndex++] = value & 0x00ff;
		g_ucBytes[g_iBytesIndex++] = value >> 8;
	} else {
		g_iErrorNo |= ERROR_NOPARM;
	}
}

//////////////////
// eof - jz.hpp //
//////////////////
