// ---------------------------------------------------
// add.hpp      10-Mar-11 DOSBox-0.74 Version 1.00.00a
// Serial No. 8208-4162-344865    All Rights Reserved.
// Copyright (C) 2010 Douglas Goodall,  United States.
// ---------------------------------------------------

if( 0 == strcmp(strupr(g_szOpcode),"ADD") ) {
  char szADDtemp[DEFAULT_STRSIZE];
  char szADDtemp2[DEFAULT_STRSIZE];
  char * psz;
  unsigned int uiTemp;
  strcpy(szADDtemp2,g_szParms);
  strcpy(szADDtemp,strupr(szADDtemp2));
  fprintf(g_flog,"...processing ADD g_szOpcode...\n");
  g_iErrorNo ^= ERROR_UNKOP;

// add (hl)
// add ix,pp
// add iy,rr
// add hl,ss
// add (ix+d)
// add (iy+d)
// add r
// add n
//

  if(0 == strlen(g_szParms)) {
    g_iErrorNo |= ERROR_NOPARM;
    g_iLineType = TYPE_Z80;
  }

  // add (hl)
  if(TYPE_ERR == g_iLineType) {
    if(0 == strcmp(strupr(g_szParms),"(HL)")) {
      g_ucBytes[g_iBytesIndex++] = 0x86;
      g_iLineType = TYPE_Z80;
    }
  }

  // 3/4/2011 dwg - add ix,pp
  if(TYPE_ERR == g_iLineType) {
    if(5 == strlen(szADDtemp)) {
      if(0 == strcmp("IX,BC",szADDtemp)) {
        g_ucBytes[g_iBytesIndex++] = 0xDD;
	g_ucBytes[g_iBytesIndex++] = 0x09 + 0x00;
        g_iLineType = TYPE_Z80;
      }
      if(0 == strcmp("IX,DE",szADDtemp)) {
        g_ucBytes[g_iBytesIndex++] = 0xDD;
        g_ucBytes[g_iBytesIndex++] = 0x09 + 0x10;
        g_iLineType = TYPE_Z80;
      }
      if(0 == strcmp("IX,IX",szADDtemp)) {
        g_ucBytes[g_iBytesIndex++] = 0xDD;
	g_ucBytes[g_iBytesIndex++] = 0x09 + 0x20;
        g_iLineType = TYPE_Z80;
      }
      if(0 == strcmp("IX,SP",szADDtemp)) {
        g_ucBytes[g_iBytesIndex++] = 0xDD;
	g_ucBytes[g_iBytesIndex++] = 0x09 + 0x30;
        g_iLineType = TYPE_Z80;
      }
    }
  }

  // add iy,pp
  if(TYPE_ERR == g_iLineType) {
    if(5 == strlen(szADDtemp)) {
      if(0 == strcmp("IY,BC",szADDtemp)) {
        g_ucBytes[g_iBytesIndex++] = 0xFD;
        g_ucBytes[g_iBytesIndex++] = 0x09 + 0x00;
        g_iLineType = TYPE_Z80;
      }
      if(0 == strcmp("IY,DE",szADDtemp)) {
        g_ucBytes[g_iBytesIndex++] = 0xFD;
        g_ucBytes[g_iBytesIndex++] = 0x09 + 0x10;
        g_iLineType = TYPE_Z80;
      }
      if(0 == strcmp("IY,IY",szADDtemp)) {
        g_ucBytes[g_iBytesIndex++] = 0xFD;
        g_ucBytes[g_iBytesIndex++] = 0x09 + 0x20;
        g_iLineType = TYPE_Z80;
      }
      if(0 == strcmp("IY,SP",szADDtemp)) {
        g_ucBytes[g_iBytesIndex++] = 0xFD;
        g_ucBytes[g_iBytesIndex++] = 0x09 + 0x30;
        g_iLineType = TYPE_Z80;
      }
    }
  }
  
  // add hl,ss
  if(TYPE_ERR == g_iLineType) {
    if(5 == strlen(szADDtemp)) {
      if(0 == strcmp("HL,BC",szADDtemp)) {
        g_ucBytes[g_iBytesIndex++] = 0x09 + 0x00;
        g_iLineType = TYPE_Z80;
      }
      if(0 == strcmp("HL,DE",szADDtemp)) {
        g_ucBytes[g_iBytesIndex++] = 0x09 + 0x10;
        g_iLineType = TYPE_Z80;
      }
      if(0 == strcmp("HL,HL",szADDtemp)) {
        g_ucBytes[g_iBytesIndex++] = 0x09 + 0x20;
        g_iLineType = TYPE_Z80;
      }
      if(0 == strcmp("HL,SP",szADDtemp)) {
        g_ucBytes[g_iBytesIndex++] = 0x09 + 0x30;
        g_iLineType = TYPE_Z80;
      }
    }
  }

  // add (ix+d)
  if(TYPE_ERR == g_iLineType) {
    int bFin = FALSE;
    if(0 == strncmp("(IX+",szADDtemp,4)) {
      g_iLineType = TYPE_Z80;
      for(int i=4;i<strlen(szADDtemp);i++) {
        if(')' == szADDtemp[i]) {
          szADDtemp[i] = 0;
          bFin = TRUE;
        }
      }
      g_ucBytes[g_iBytesIndex++] = 0xDD;
      g_ucBytes[g_iBytesIndex++] = 0x86;
      if(TRUE == bFin) {
        psz = &szADDtemp[4];
        #include "../ascommon/_disp.hpp"
      } else {
	g_iErrorNo |= ERROR_SYNTAX;
      }
    }
  }

  // add (iy+d)
  if(TYPE_ERR == g_iLineType) {
    int bFin = FALSE;
    if(0 == strncmp("(IY+",szADDtemp,4)) {
      g_iLineType = TYPE_Z80;
      for(int i=4;i<strlen(szADDtemp);i++) {
        if(')' == szADDtemp[i]) {
          szADDtemp[i] = 0;
          bFin = TRUE;
        }
      }
      g_ucBytes[g_iBytesIndex++] = 0xFD;
      g_ucBytes[g_iBytesIndex++] = 0x86;
      if(TRUE == bFin) {
        psz = &szADDtemp[4];
        #include "../ascommon/_disp.hpp"
      } else {
        g_iErrorNo |= ERROR_SYNTAX;
      }
    }   
  }

  // add r
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
  
  // add n
  if(TYPE_ERR == g_iLineType) {
    g_ucBytes[g_iBytesIndex++] = 0xC6;
    g_ucBytes[g_iBytesIndex++] = resolvep8(g_szParms);
    g_iLineType = TYPE_Z80;
  }

}

//////////////////
// eof - add.hpp //
//////////////////

