// $Log: dd_85.hpp,v $
// Revision 1.2  2011/03/25 22:47:07  doug
// add log and trim gpl stuff
////

char dd_85[] = "$Id: dd_85.hpp,v 1.2 2011/03/25 22:47:07 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

if(0 == strcmp(strupr(g_szOpcode),"DD")) {
	fprintf(g_flog,"Processing 8085 DD  g_szOpcode\n");
        g_iLineType = TYPE_8085;
        g_iErrorNo ^= ERROR_UNKOP;
	if(0 < strlen(g_szParms)) {
		unsigned long lTemp = resolvep32(g_szParms);
		unsigned int  uiTempl = (unsigned int)lTemp & 0x0000ffffL;
		unsigned int  uiTemph = (unsigned int)lTemp >> 16;

		fprintf(g_flog,"lTemp   was 0x%08lX\n",lTemp);
		fprintf(g_flog,"uiTempl was 0x%04X\n",uiTempl);
		fprintf(g_flog,"uiTemph was 0x%04X\n",uiTemph);

                g_ucBytes[g_iBytesIndex++] = uiTempl & 0x00ff;
                g_ucBytes[g_iBytesIndex++] = uiTempl >> 8;
                g_ucBytes[g_iBytesIndex++] = uiTemph & 0x00ff;
		g_ucBytes[g_iBytesIndex++] = uiTemph >> 8;
	} else {
		g_iErrorNo |= ERROR_NOPARM;
	}
}

//////////////////
// eof - dd.hpp //
//////////////////

