// ---------------------------------------------------
// SERIAL.HPP   28-Jan-11 DOSBox-0.74 Version 1.00.00a
// Serial No. 8208-4162-344865    All Rights Reserved.
// Copyright (C) 2010 Douglas Goodall,  United States.
// ---------------------------------------------------

if( 0 == strcmp(strupr(g_szOpcode),"JP") ) {
  char szJPtemp[DEFAULT_STRSIZE];
  char szJPtemp2[DEFAULT_STRSIZE];
  unsigned int uiTemp;
  strcpy(szJPtemp2,g_szParms);
  strcpy(szJPtemp,strupr(szJPtemp2));
  fprintf(g_flog,"...processing JP g_szOpcode...\n");
  if(0 == strcmp(strupr(g_szParms),"(HL)")) {
    g_ucBytes[g_iBytesIndex++] = 0xe9;
    g_iLineType = TYPE_Z80;
    g_iErrorNo ^= ERROR_UNKOP;
  }
  if(0 == strcmp(strupr(g_szParms),"(IX)")) {
    g_ucBytes[g_iBytesIndex++] = 0xdd;
    g_ucBytes[g_iBytesIndex++] = 0xe9;
    g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
  }
  if(0 == strcmp(strupr(g_szParms),"(IY)")) {
    g_ucBytes[g_iBytesIndex++] = 0xfd;
    g_ucBytes[g_iBytesIndex++] = 0xe9;
    g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
  }
  if(TYPE_ERR == g_iLineType) {
    if(3 < strlen(g_szParms)) {
      if(',' == g_szParms[1]) {
	switch(g_szParms[0]) {
	  case 'Z':
	    g_ucBytes[g_iBytesIndex++] = 0xC2 + 0x08;
	    uiTemp = resolvep16(&g_szParms[2]);
	    g_ucBytes[g_iBytesIndex++] = uiTemp & 255;
	    g_ucBytes[g_iBytesIndex++] = uiTemp >> 8; 
	    g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
	    break;
	  case 'C':
	    g_ucBytes[g_iBytesIndex++] = 0xC2 + 0x18;
            uiTemp = resolvep16(&g_szParms[2]);
            g_ucBytes[g_iBytesIndex++] = uiTemp & 255;
            g_ucBytes[g_iBytesIndex++] = uiTemp >> 8;
	    g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
	    break;
	  case 'P':
	    g_ucBytes[g_iBytesIndex++] = 0xC2 + 0x30;
            uiTemp = resolvep16(&g_szParms[2]);
            g_ucBytes[g_iBytesIndex++] = uiTemp & 255;
            g_ucBytes[g_iBytesIndex++] = uiTemp >> 8;
	    g_iLineType = TYPE_Z80; 
          g_iErrorNo ^= ERROR_UNKOP;
	    break;
          case 'M':
            g_ucBytes[g_iBytesIndex++] = 0xC2 + 0x38;
            uiTemp = resolvep16(&g_szParms[2]);
            g_ucBytes[g_iBytesIndex++] = uiTemp & 255;
            g_ucBytes[g_iBytesIndex++] = uiTemp >> 8;
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
	if(0 == strncmp("NZ",szJPtemp,2)) {
            g_ucBytes[g_iBytesIndex++] = 0xC2 + 0x00;
            uiTemp = resolvep16(&g_szParms[3]);
            g_ucBytes[g_iBytesIndex++] = uiTemp & 255;
            g_ucBytes[g_iBytesIndex++] = uiTemp >> 8;
            g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
        }
        if(0 == strncmp("NC",szJPtemp,2)) {
            g_ucBytes[g_iBytesIndex++] = 0xC2 + 0x10;
            uiTemp = resolvep16(&g_szParms[3]);
            g_ucBytes[g_iBytesIndex++] = uiTemp & 255;
            g_ucBytes[g_iBytesIndex++] = uiTemp >> 8;
            g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
        }   
        if(0 == strncmp("PO",szJPtemp,2)) {
            g_ucBytes[g_iBytesIndex++] = 0xC2 + 0x20;
            uiTemp = resolvep16(&g_szParms[3]);
            g_ucBytes[g_iBytesIndex++] = uiTemp & 255;
            g_ucBytes[g_iBytesIndex++] = uiTemp >> 8;
            g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
        }   
        if(0 == strncmp("PE",szJPtemp,2)) {
            g_ucBytes[g_iBytesIndex++] = 0xC2 + 0x28;
            uiTemp = resolvep16(&g_szParms[3]);
            g_ucBytes[g_iBytesIndex++] = uiTemp & 255;
            g_ucBytes[g_iBytesIndex++] = uiTemp >> 8;
            g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
        }   
      }
    }
  }
  if(TYPE_ERR == g_iLineType) {
    int rc;	
    unsigned int value = g_pCSymbols->getu16(g_szParms,&rc);
    fprintf(g_flog,"value is %04X\n",value);
    g_ucBytes[g_iBytesIndex++] = 0xc3;
    g_ucBytes[g_iBytesIndex++] = value & 0x00ff;
    g_ucBytes[g_iBytesIndex++] = value >> 8;
    g_iLineType = TYPE_Z80;
    g_iErrorNo ^= ERROR_UNKOP;
  }
}

//////////////////
// eof - jp.hpp //
//////////////////

