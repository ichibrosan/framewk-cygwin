// $Log: rpo_85.hpp,v $
// Revision 1.2  2011/03/25 22:47:07  doug
// add log and trim gpl stuff
////

char rpo_85[] = "$Id: rpo_85.hpp,v 1.2 2011/03/25 22:47:07 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

if(0 == strcmp(strupr(g_szOpcode),"RPO")) {
	fprintf(g_flog,"Processing 8085 RPO g_szOpcode\n");
        g_iLineType = TYPE_8085;
        g_iErrorNo ^= ERROR_UNKOP;
	g_ucBytes[g_iBytesIndex++] = 0xE0;
}

///////////////////
// eof - rpo.hpp //
///////////////////

