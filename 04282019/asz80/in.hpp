// ---------------------------------------------------
// in.hpp        5-Mar-11   Running on Mac OS X 10.6.6
// S/n 2011-1042-654321  Written by Douglas W. Goodall
// Copyright(c)2011 Douglas W. Goodall, United States.
// ---------------------------------------------------
// This file is part of Vintage Modern Assembler Plus Tools.
//
// VMAPT is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// VMAPT is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with VMAPT.  If not, see <http://www.gnu.org/licenses/>.
//

if(0 == strcmp(strupr(g_szOpcode),"IN")){
  fprintf(g_flog,"Processing Z80 IN g_szOpcode\n");
  g_iErrorNo ^= ERROR_UNKOP;

  char szINtemp[DEFAULT_STRSIZE];
  char szINtemp2[DEFAULT_STRSIZE];
  strcpy(szINtemp2,g_szParms);
  strcpy(szINtemp,strupr(szINtemp2));

  if(5 == strlen(szINtemp)) {
    if(0 == strncmp(",(C)",&szINtemp[1],4) ) {
      switch(szINtemp[0]) {
	case 'B':
          g_ucBytes[g_iBytesIndex++] = 0xED;
          g_ucBytes[g_iBytesIndex++] = 0x41 + 0x00;
 	  break;
	case 'C':
          g_ucBytes[g_iBytesIndex++] = 0xED;
          g_ucBytes[g_iBytesIndex++] = 0x41 + 0x08;
	  break;
	case 'D':
          g_ucBytes[g_iBytesIndex++] = 0xED;
          g_ucBytes[g_iBytesIndex++] = 0x41 + 0x10;
	  break;
	case 'E':
          g_ucBytes[g_iBytesIndex++] = 0xED;
          g_ucBytes[g_iBytesIndex++] = 0x41 + 0x18;
	  break;
	case 'H':
          g_ucBytes[g_iBytesIndex++] = 0xED;
          g_ucBytes[g_iBytesIndex++] = 0x41 + 0x20;
	  break;
	case 'L':
          g_ucBytes[g_iBytesIndex++] = 0xED;
          g_ucBytes[g_iBytesIndex++] = 0x41 + 0x28;
	  break;
	case 'A':
          g_ucBytes[g_iBytesIndex++] = 0xED;
          g_ucBytes[g_iBytesIndex++] = 0x41 + 0x38;
	  break;
	default:
	  g_iErrorNo |= ERROR_NOREG;
	  g_iLineType = TYPE_ERR;
	  break;
      }
    }
  }

  // check for "in a,(n)"  and process if so...
  if(TYPE_ERR == g_iLineType) {
    if(0 < strlen(szINtemp)) {
      if(0 == strncmp("A,(",szINtemp,3)) {
        int bFin = FALSE;
        for(int l=3;l<strlen(szINtemp);l++) {
	  if(')' == szINtemp[l]) {
	    szINtemp[l] = 0;
	    bFin = TRUE;
	  }
        }  
        if(TRUE == bFin) {
      	  g_ucBytes[g_iBytesIndex++] = 0xD3;
      	  g_ucBytes[g_iBytesIndex++] = resolvep8(&szINtemp[3]);
	  g_iLineType = TYPE_Z80;
        } else {
	  g_iErrorNo |= ERROR_SYNTAX;
        }
      }
    } else {
      g_iErrorNo |= ERROR_NOPARM;
    }
  }

}

////////////////// 
// eof - in.hpp //
//////////////////

