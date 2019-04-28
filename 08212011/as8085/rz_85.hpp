// $Log: rz_85.hpp,v $
// Revision 1.2  2011/03/25 22:47:07  doug
// add log and trim gpl stuff
////

char rz_85[] = "$Id: rz_85.hpp,v 1.2 2011/03/25 22:47:07 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

if(0 == strcmp(strupr(g_szOpcode),"RZ")) {
	fprintf(g_flog,"Processing 8085 RZ g_szOpcode\n");
	g_ucBytes[g_iBytesIndex++] = 0xC8;
	g_iLineType = TYPE_8085;
        g_iErrorNo ^= ERROR_UNKOP;
}

//////////////////
// eof - rz.hpp //
//////////////////

