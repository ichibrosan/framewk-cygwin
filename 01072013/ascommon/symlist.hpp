// $Log: symlist.hpp,v $
// Revision 1.2  2011/03/25 21:47:31  doug
// *** empty log message ***
//
// Revision 1.1  2011/03/25 07:19:17  doug
// Initial revision
//

char dir_symlist[] = "$Id: symlist.hpp,v 1.2 2011/03/25 21:47:31 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

if(0 == strcmp("SYMLIST",strupr(g_szOpcode))) {
	g_iErrorNo   ^= ERROR_UNKOP;
	g_iLineType = TYPE_DIR;

	if(TRUE == g_bPass2) {

		int bDone = FALSE;
	
		if(0 == strcmp("STRING",strupr(g_szParms))) {
			g_pCSymbols->dump(TYPE_STRING,g_flst);
			bDone = TRUE;
		}

                if(0 == strcmp("META",strupr(g_szParms))) {
                        g_pCSymbols->dump(TYPE_META,g_flst);
                        bDone = TRUE;
                }

        	if(0 == strcmp("U8",strupr(g_szParms))) {
                	g_pCSymbols->dump(TYPE_U8,g_flst);
                	bDone = TRUE;
        	}

        	if(0 == strcmp("U16",strupr(g_szParms))) {
                	g_pCSymbols->dump(TYPE_U16,g_flst);
                	bDone = TRUE;
        	}

        	if(0 == strcmp("U32",strupr(g_szParms))) {
                	g_pCSymbols->dump(TYPE_U32,g_flst);
                	bDone = TRUE;
        	}

        	if(0 == strcmp("U64",strupr(g_szParms))) {
                	g_pCSymbols->dump(TYPE_U64,g_flst);
                	bDone = TRUE;
        	}

		if(FALSE == bDone) {
			g_iErrorNo |= ERROR_SYMTYPE;
		}
	}
}

///////////////////////
// eof - symlist.hpp //
///////////////////////

