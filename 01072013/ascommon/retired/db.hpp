// $Log: db.hpp,v $
// Revision 1.2  2011/03/25 21:47:31  doug
// *** empty log message ***
//
// Revision 1.1  2011/03/25 07:19:17  doug
// Initial revision
//

char dir_db[] = "$Id: db.hpp,v 1.2 2011/03/25 21:47:31 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.
	
	if(0 == strcmp(strupr(g_szOpcode),"DB")) {
		fprintf(g_flog,"Processing DB directive\n");
		unsigned char ucTemp = resolvep8(g_szParms)&255;
		fprintf(g_flog,"ucTemp is 0x%02X\n",ucTemp);
		g_ucBytes[g_iBytesIndex++] = ucTemp; 
		g_iLineType = TYPE_DIR;
		g_iErrorNo ^= ERROR_UNKOP;
	}

//////////////////
// eof - db.hpp //
//////////////////
