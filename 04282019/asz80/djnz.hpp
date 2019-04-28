// ---------------------------------------------------
// djnz.hpp      4-Mar-11 DOSBox-0.74 Version 1.00.00a
// Serial No. 8208-4162-344865    All Rights Reserved.
// Copyright (C) 2010 Douglas Goodall,  United States.
// ---------------------------------------------------

if( 0 == strcmp(strupr(g_szOpcode),"DJNZ") ) {
  fprintf(g_flog,"Processing DJNZ g_szOpcode\n");
  g_iLineType = TYPE_Z80;
  g_iErrorNo ^= ERROR_UNKOP;
  g_ucBytes[g_iBytesIndex++] = 0x10;
  if(0 < strlen(g_szParms)) {
    char *psz = g_szParms;
    #include "../ascommon/_disp.hpp"
  } else {
    g_iErrorNo |= ERROR_NOPARM;
  }
}

////////////////////
// eof - djnz.hpp //
////////////////////

