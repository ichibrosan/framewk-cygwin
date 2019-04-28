// $Log: namespac.hpp,v $
// Revision 1.2  2011/03/25 21:47:31  doug
// *** empty log message ***
//
// Revision 1.1  2011/03/25 07:19:17  doug
// Initial revision
//

char dir_namespac[] = "$Id: namespac.hpp,v 1.2 2011/03/25 21:47:31 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

if(0 == strcmp("NAMESPACE",strupr(g_szOpcode))) {
  char szNSin[DEFAULT_STRSIZE];
  char szNSout[DEFAULT_STRSIZE];
  int index = 0;
  g_iErrorNo   ^= ERROR_UNKOP;
  g_iLineType = TYPE_DIR;
  if(0 < strlen(g_szParms)) {
    strcpy(szNSin,g_szParms);
    for(int o=0;o<strlen(strupr(szNSin));o++) {
      if( g_pCEval->bIsNumeric(szNSin[o]) || 
	  g_pCEval->bIsAlpha(szNSin[o]) ) {
	szNSout[index++] = tolower(szNSin[o]);	
      }
    }
    szNSout[index++] = 0;
    if(0 < strlen(szNSout)) {
	    g_pCSymbols->mynamespace(szNSout);
    } else {
	    g_iErrorNo |= ERROR_INVNS;
    }
  } else {
	  g_iErrorNo |= ERROR_NOPARM;
  }
}

///////////////////////
// eof - symlist.hpp //
///////////////////////

