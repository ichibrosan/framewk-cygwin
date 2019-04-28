// $Log: sim_85.hpp,v $
// Revision 1.2  2011/03/25 22:47:07  doug
// add log and trim gpl stuff
////

char sim_85[] = "$Id: sim_85.hpp,v 1.2 2011/03/25 22:47:07 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

if(0 == strcmp(strupr(g_szOpcode),"SIM")) {
	fprintf(g_flog,"Processing 8085 SIM g_szOpcode\n");
	g_ucBytes[g_iBytesIndex++] = 0x30;
	g_iLineType = TYPE_8085;
        g_iErrorNo ^= ERROR_UNKOP;
}

///////////////////
// eof - sim.hpp //
///////////////////

