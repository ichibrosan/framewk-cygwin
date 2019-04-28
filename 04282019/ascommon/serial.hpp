// $Log: serial.hpp,v $
// Revision 1.2  2011/03/25 21:47:31  doug
// *** empty log message ***
//
// Revision 1.1  2011/03/25 07:19:17  doug
// Initial revision
//

char dir_serial[] = "$Id: serial.hpp,v 1.2 2011/03/25 21:47:31 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.
	
	if(0 == strcmp(strupr(g_szOpcode),"SERIAL")) {
		fprintf(g_flog,"Processing SERIAL directive\n");
		if(0 != strlen(g_szParms)) {
			strcpy(g_szSerial,g_szParms);
			g_iLineType = TYPE_DIR;
			g_pCSymbols->add("serialno",TYPE_STRING,g_szSerial);
                                g_iErrorNo ^= ERROR_UNKOP;

		}
	}
