// ---------------------------------------------------
// and.hpp       4-Mar-11 DOSBox-0.74 Version 1.00.00a
// Serial No. 8208-4162-344865    All Rights Reserved.
// Copyright (C) 2010 Douglas Goodall,  United States.
// ---------------------------------------------------

if( 0 == strcmp(strupr(g_szOpcode),"AND") ) {
  char szANDtemp[128];
  char szANDtemp2[128];
  char * psz;
  unsigned int uiTemp;
  strcpy(szANDtemp2,g_szParms);
  strcpy(szANDtemp,strupr(szANDtemp2));
  fprintf(g_flog,"...processing AND g_szOpcode...\n");
  g_iErrorNo ^= ERROR_UNKOP;

// and (hl)
// and ix,pp
// and iy,rr
// and hl,ss
// and (ix+d)
// and (iy+d)
// and r
// and n
//

  // and (hl)
  if(0 == strcmp(strupr(g_szParms),"(HL)")) {
    g_ucBytes[g_iBytesIndex++] = 0x86;
    g_iLineType = TYPE_Z80;
  }

  // and ix,pp
  if(TYPE_ERR == g_iLineType) {
    if(5 == strlen(szANDtemp)) {
      if(0 == strcmp("IX,BC",szANDtemp)) {
        g_ucBytes[g_iBytesIndex++] = 0xDD;
	g_ucBytes[g_iBytesIndex++] = 0x09 + 0x00;
        g_iLineType = TYPE_Z80;
      }
      if(0 == strcmp("IX,DE",szANDtemp)) {
        g_ucBytes[g_iBytesIndex++] = 0xDD;
        g_ucBytes[g_iBytesIndex++] = 0x09 + 0x10;
        g_iLineType = TYPE_Z80;
      }
      if(0 == strcmp("IX,IX",szANDtemp)) {
        g_ucBytes[g_iBytesIndex++] = 0xDD;
	g_ucBytes[g_iBytesIndex++] = 0x09 + 0x20;
        g_iLineType = TYPE_Z80;
      }
      if(0 == strcmp("IX,SP",szANDtemp)) {
        g_ucBytes[g_iBytesIndex++] = 0xDD;
	g_ucBytes[g_iBytesIndex++] = 0x09 + 0x30;
        g_iLineType = TYPE_Z80;
      }
    }
  }

  // and iy,pp
  if(TYPE_ERR == g_iLineType) {
    if(5 == strlen(szANDtemp)) {
      if(0 == strcmp("IY,BC",szANDtemp)) {
        g_ucBytes[g_iBytesIndex++] = 0xFD;
        g_ucBytes[g_iBytesIndex++] = 0x09 + 0x00;
        g_iLineType = TYPE_Z80;
      }
      if(0 == strcmp("IY,DE",szANDtemp)) {
        g_ucBytes[g_iBytesIndex++] = 0xFD;
        g_ucBytes[g_iBytesIndex++] = 0x09 + 0x10;
        g_iLineType = TYPE_Z80;
      }
      if(0 == strcmp("IY,IY",szANDtemp)) {
        g_ucBytes[g_iBytesIndex++] = 0xFD;
        g_ucBytes[g_iBytesIndex++] = 0x09 + 0x20;
        g_iLineType = TYPE_Z80;
      }
      if(0 == strcmp("IY,SP",szANDtemp)) {
        g_ucBytes[g_iBytesIndex++] = 0xFD;
        g_ucBytes[g_iBytesIndex++] = 0x09 + 0x30;
        g_iLineType = TYPE_Z80;
      }
    }
  }
  
  // add hl,ss
  if(TYPE_ERR == g_iLineType) {
    if(5 == strlen(szANDtemp)) {
      if(0 == strcmp("HL,BC",szANDtemp)) {
        g_ucBytes[g_iBytesIndex++] = 0x09 + 0x00;
        g_iLineType = TYPE_Z80;
      }
      if(0 == strcmp("HL,DE",szANDtemp)) {
        g_ucBytes[g_iBytesIndex++] = 0x09 + 0x10;
        g_iLineType = TYPE_Z80;
      }
      if(0 == strcmp("HL,HL",szANDtemp)) {
        g_ucBytes[g_iBytesIndex++] = 0x09 + 0x20;
        g_iLineType = TYPE_Z80;
      }
      if(0 == strcmp("HL,SP",szANDtemp)) {
        g_ucBytes[g_iBytesIndex++] = 0x09 + 0x30;
        g_iLineType = TYPE_Z80;
      }
    }
  }

  // add (ix+d)
  if(TYPE_ERR == g_iLineType) {
    if(0 == strncmp("(IX+",szANDtemp,4)) {
      g_iLineType = TYPE_Z80;
      int bFin = FALSE;
      for(int i=4;i<strlen(szANDtemp);i++) {
        if(')' == szANDtemp[i]) {
          szANDtemp[i] = 0;
	  bFin = TRUE;
        }
      }
      g_ucBytes[g_iBytesIndex++] = 0xDD;
      g_ucBytes[g_iBytesIndex++] = 0x86;
      if(TRUE == bFin) {
        psz = &szANDtemp[4];
        #include "../ascommon/_disp.hpp"
      } else {
	g_iErrorNo |= ERROR_SYNTAX;
      }
    }
  }

  // and (iy+d)
  if(TYPE_ERR == g_iLineType) {
    if(0 == strncmp("(IY+",szANDtemp,4)) {
      g_iLineType = TYPE_Z80;
      int bFin = FALSE;
      for(int i=4;i<strlen(szANDtemp);i++) {
        if(')' == szANDtemp[i]) {
          szANDtemp[i] = 0;
	  bFin = TRUE;
        }
      }
      g_ucBytes[g_iBytesIndex++] = 0xFD;
      g_ucBytes[g_iBytesIndex++] = 0x86;
      if(TRUE == bFin) {
        psz = &szANDtemp[4];
        #include "../ascommon/_disp.hpp"
      } else {
	g_iErrorNo |= ERROR_SYNTAX;
      }
    }   
  }

  // and r
  if(TYPE_ERR == g_iLineType) {
    if(1 == strlen(g_szParms)) {
      switch(g_szParms[0]) {
  	case 'B':
	case 'b':
	  g_ucBytes[g_iBytesIndex++] = 0x80 + 0x00 + 0x00;
	  g_iLineType = TYPE_Z80;
	  break;
	case 'C':
	case 'c':
	  g_ucBytes[g_iBytesIndex++] = 0x80 + 0x00 + 0x01;
	  g_iLineType = TYPE_Z80;
	  break;
	case 'D':
	case 'd':
	  g_ucBytes[g_iBytesIndex++] = 0x80 + 0x00 + 0x02;
	  g_iLineType = TYPE_Z80; 
	  break;
        case 'E':
	case 'e':
          g_ucBytes[g_iBytesIndex++] = 0x80 + 0x00 + 0x03;
          g_iLineType = TYPE_Z80;
          break;
        case 'H':
	case 'h':
          g_ucBytes[g_iBytesIndex++] = 0x80 + 0x00 + 0x04;
          g_iLineType = TYPE_Z80;
          break;
        case 'L':
	case 'l':
          g_ucBytes[g_iBytesIndex++] = 0x80 + 0x00 + 0x05;
          g_iLineType = TYPE_Z80;
          break;
        case 'A':
	case 'a':
          g_ucBytes[g_iBytesIndex++] = 0x80 + 0x00 + 0x07;
          g_iLineType = TYPE_Z80;
          break;
      }
    }
  }
  
  // and n
  if(TYPE_ERR == g_iLineType) {
    if(0 < strlen(g_szParms)) {
      g_ucBytes[g_iBytesIndex++] = 0xC6;
      g_ucBytes[g_iBytesIndex++] = resolvep8(g_szParms);
    } else {
      g_iErrorNo |= ERROR_NOPARM;
    }
    g_iLineType = TYPE_Z80;
  }
}

//////////////////
// eof - add.hpp //
//////////////////

