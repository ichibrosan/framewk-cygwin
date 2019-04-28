// ---------------------------------------------------
// jr.hpp        4-Feb-11 DOSBox-0.74 Version 1.00.00a
// Serial No. 8208-4162-344865    All Rights Reserved.
// Copyright (C) 2010 Douglas Goodall,  United States.
// ---------------------------------------------------

if( 0 == strcmp(strupr(g_szOpcode),"JR") ) {
  char szJRtemp[DEFAULT_STRSIZE];
  char szJRtemp2[DEFAULT_STRSIZE];
  char * psz;
  strcpy(szJRtemp2,g_szParms);
  strcpy(szJRtemp,strupr(szJRtemp2));
  fprintf(g_flog,"...processing JR g_szOpcode...\n");
  if(TYPE_ERR == g_iLineType) {
    if(3 < strlen(g_szParms)) {
      if(',' == g_szParms[1]) {
	switch(g_szParms[0]) {
	  case 'Z':
	  case 'z':
	    g_ucBytes[g_iBytesIndex++] = 0x28;
	    psz = &g_szParms[2];
            #include "../ascommon/_disp.hpp"
	    g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
	    break;
	  case 'C':
	  case 'c':
	    g_ucBytes[g_iBytesIndex++] = 0x38;
	    psz = &g_szParms[2];
            #include "../ascommon/_disp.hpp"
	    g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
	    break;
	}
      }
    }
  }
  if(TYPE_ERR == g_iLineType) {
    if(3 < strlen(g_szParms)) {
      if(',' == g_szParms[2]) {
	if(0 == strncmp("NZ",szJRtemp,2)) {
            g_ucBytes[g_iBytesIndex++] = 0x20;
	    psz = &g_szParms[3];
	    #include "../ascommon/_disp.hpp"
            g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
        }
        if(0 == strncmp("NC",szJRtemp,2)) {
            g_ucBytes[g_iBytesIndex++] = 0x30;
	    psz = &g_szParms[3];
            #include "../ascommon/_disp.hpp"
            g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
        }   
      }
    }
  }
  if(TYPE_ERR == g_iLineType) {
    g_ucBytes[g_iBytesIndex++] = 0x18;
    psz = g_szParms;
    #include "../ascommon/_disp.hpp"
    g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
  }
}

//////////////////
// eof - jr.hpp //
//////////////////

