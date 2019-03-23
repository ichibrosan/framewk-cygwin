// ---------------------------------------------------
// call.hp       3-Mar-11 DOSBox-0.74 Version 1.00.00a
// Serial No. 8208-4162-344865    All Rights Reserved.
// Copyright (C) 2010 Douglas Goodall,  United States.
// ---------------------------------------------------

if( 0 == strcmp(strupr(g_szOpcode),"CALL") ) {
  char szCALLtemp[DEFAULT_STRSIZE];
  char szCALLtemp2[DEFAULT_STRSIZE];
  unsigned int uiTemp;
  strcpy(szCALLtemp2,g_szParms);
  strcpy(szCALLtemp,strupr(szCALLtemp2));
  fprintf(g_flog,"...processing CALL g_szOpcode...\n");
  g_iErrorNo ^= ERROR_UNKOP;

  if(TYPE_ERR == g_iLineType) {
    if(3 < strlen(g_szParms)) {
      if(',' == g_szParms[1]) {
	switch(g_szParms[0]) {
	  case 'Z':
	  case 'z':
	    g_ucBytes[g_iBytesIndex++] = 0xC4 + 0x08;
	    uiTemp = resolvep16(&g_szParms[2]);
	    g_ucBytes[g_iBytesIndex++] = uiTemp & 255;
	    g_ucBytes[g_iBytesIndex++] = uiTemp >> 8; 
	    g_iLineType = TYPE_Z80;
	    break;
	  case 'C':
	  case 'c':
	    g_ucBytes[g_iBytesIndex++] = 0xC4 + 0x18;
            uiTemp = resolvep16(&g_szParms[2]);
            g_ucBytes[g_iBytesIndex++] = uiTemp & 255;
            g_ucBytes[g_iBytesIndex++] = uiTemp >> 8;
	    g_iLineType = TYPE_Z80;
	    break;
	  case 'P':
	  case 'p':
	    g_ucBytes[g_iBytesIndex++] = 0xC4 + 0x30;
            uiTemp = resolvep16(&g_szParms[2]);
            g_ucBytes[g_iBytesIndex++] = uiTemp & 255;
            g_ucBytes[g_iBytesIndex++] = uiTemp >> 8;
	    g_iLineType = TYPE_Z80; 
	    break;
          case 'M':
	  case 'm':
            g_ucBytes[g_iBytesIndex++] = 0xC4 + 0x38;
            uiTemp = resolvep16(&g_szParms[2]);
            g_ucBytes[g_iBytesIndex++] = uiTemp & 255;
            g_ucBytes[g_iBytesIndex++] = uiTemp >> 8;
            g_iLineType = TYPE_Z80;
            break;
	}
      }
    }
  }
  if(TYPE_ERR == g_iLineType) {
    if(3 < strlen(g_szParms)) {
      if(',' == g_szParms[2]) {
	if(0 == strncmp("NZ",szCALLtemp,2)) {
            g_ucBytes[g_iBytesIndex++] = 0xC4 + 0x00;
            uiTemp = resolvep16(&g_szParms[3]);
            g_ucBytes[g_iBytesIndex++] = uiTemp & 255;
            g_ucBytes[g_iBytesIndex++] = uiTemp >> 8;
            g_iLineType = TYPE_Z80;
        }
        if(0 == strncmp("NC",szCALLtemp,2)) {
            g_ucBytes[g_iBytesIndex++] = 0xC4 + 0x10;
            uiTemp = resolvep16(&g_szParms[3]);
            g_ucBytes[g_iBytesIndex++] = uiTemp & 255;
            g_ucBytes[g_iBytesIndex++] = uiTemp >> 8;
            g_iLineType = TYPE_Z80;
        }   
        if(0 == strncmp("PO",szCALLtemp,2)) {
            g_ucBytes[g_iBytesIndex++] = 0xC4 + 0x20;
            uiTemp = resolvep16(&g_szParms[3]);
            g_ucBytes[g_iBytesIndex++] = uiTemp & 255;
            g_ucBytes[g_iBytesIndex++] = uiTemp >> 8;
            g_iLineType = TYPE_Z80;
        }   
        if(0 == strncmp("PE",szCALLtemp,2)) {
            g_ucBytes[g_iBytesIndex++] = 0xC4 + 0x28;
            uiTemp = resolvep16(&g_szParms[3]);
            g_ucBytes[g_iBytesIndex++] = uiTemp & 255;
            g_ucBytes[g_iBytesIndex++] = uiTemp >> 8;
            g_iLineType = TYPE_Z80;
        }   
      }
    }
  }
  if(TYPE_ERR == g_iLineType) {
    //int rc;	
    //unsigned int value = g_pCSymbols->getu16(g_szParms,&rc);
    g_ucBytes[g_iBytesIndex++] = 0xCD;
    if(0 < strlen(g_szParms)) {
      unsigned int uiValue = resolvep16(g_szParms);
      fprintf(g_flog,"value is %04X\n",value);
      g_ucBytes[g_iBytesIndex++] = uiValue & 0x00ff;
      g_ucBytes[g_iBytesIndex++] = uiValue >> 8;
    } else {
      g_iErrorNo |= ERROR_NOPARM;
    }
  }
  g_iLineType = TYPE_Z80;
}

//////////////////
// eof - call.hpp //
//////////////////

