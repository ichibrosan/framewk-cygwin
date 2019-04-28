// or.hpp        4-Mar-11 DOSBox-0.74 Version 1.00.00a
// Serial No. 8208-4162-344865    All Rights Reserved.
// Copyright (C) 2010 Douglas Goodall,  United States.
// ---------------------------------------------------

if( 0 == strcmp(strupr(g_szOpcode),"OR") ) {
  char szORtemp[DEFAULT_STRSIZE];
  char szORtemp2[DEFAULT_STRSIZE];
  char * psz;
  unsigned int uiTemp;
  strcpy(szORtemp2,g_szParms);
  strcpy(szORtemp,strupr(szORtemp2));
  fprintf(g_flog,"...processing OR g_szOpcode...\n");

// or (hl)
// or (ix+d)
// or (iy+d)
// or r
// or n
//

  // or (hl)
  if(0 == strcmp(strupr(g_szParms),"(HL)")) {
    g_ucBytes[g_iBytesIndex++] = 0xB6;
    g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;

  }

  // or (ix+d)
  if(TYPE_ERR == g_iLineType) {
    if(0 == strncmp("(IX+",szORtemp,4)) {
      for(int i=4;i<strlen(szORtemp);i++) {
        if(')' == szORtemp[i]) {
          szORtemp[i] = 0;
        }
      }
      g_ucBytes[g_iBytesIndex++] = 0xDD;
      g_ucBytes[g_iBytesIndex++] = 0xB6;
      psz = &szORtemp[4];
      #include "../ascommon/_disp.hpp"
      g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
    }
  }

  // or (iy+d)
  if(TYPE_ERR == g_iLineType) {
    if(0 == strncmp("(IY+",szORtemp,4)) {
      for(int i=4;i<strlen(szORtemp);i++) {
        if(')' == szORtemp[i]) {
          szORtemp[i] = 0;
        }
      }
      g_ucBytes[g_iBytesIndex++] = 0xFD;
      g_ucBytes[g_iBytesIndex++] = 0xB6;
      psz = &szORtemp[4];
      #include "../ascommon/_disp.hpp"
      g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
    }   
  }

  // or r
  if(TYPE_ERR == g_iLineType) {
    if(1 == strlen(g_szParms)) {
      switch(g_szParms[0]) {
  	case 'B':
	case 'b':
	  g_ucBytes[g_iBytesIndex++] = 0x80 + 0x30 + 0x00;
	  g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
	  break;
	case 'C':
	case 'c':
	  g_ucBytes[g_iBytesIndex++] = 0x80 + 0x30 + 0x01;
	  g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
	  break;
	case 'D':
	case 'd':
	  g_ucBytes[g_iBytesIndex++] = 0x80 + 0x30 + 0x02;
	  g_iLineType = TYPE_Z80; 
          g_iErrorNo ^= ERROR_UNKOP;
	  break;
        case 'E':
	case 'e':
          g_ucBytes[g_iBytesIndex++] = 0x80 + 0x30 + 0x03;
          g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
          break;
        case 'H':
	case 'h':
          g_ucBytes[g_iBytesIndex++] = 0x80 + 0x30 + 0x04;
          g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
          break;
        case 'L':
	case 'l':
          g_ucBytes[g_iBytesIndex++] = 0x80 + 0x30 + 0x05;
          g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
          break;
        case 'A':
	case 'a':
          g_ucBytes[g_iBytesIndex++] = 0x80 + 0x30 + 0x07;
          g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
          break;
      }
    }
  }
  
  // or n
  if(TYPE_ERR == g_iLineType) {
    int rc;	
    g_ucBytes[g_iBytesIndex++] = 0xC6 + 0x30;
    g_ucBytes[g_iBytesIndex++] = resolvep8(g_szParms);
    g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
  }

}

//////////////////
// eof - add.hpp //
//////////////////

