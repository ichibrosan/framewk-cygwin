// ---------------------------------------------------
// out.hpp       5-Mar-11   Running on Mac OS X 10.6.6
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

if(0 == strcmp(strupr(g_szOpcode),"OUT")){
  fprintf(g_flog,"Processing Z80 OUT g_szOpcode\n");

  char szOUTtemp[128];
  char szOUTtemp2[128];
  strcpy(szOUTtemp2,g_szParms);
  strcpy(szOUTtemp,strupr(szOUTtemp2));
  fprintf(g_flog,"szOUTtemp         is %s\n",szOUTtemp);
  fprintf(g_flog,"strlen(szOUTtemp) is %d\n",strlen(szOUTtemp));

  if(5 == strlen(szOUTtemp)) {
    fprintf(g_flog,"length was 5 ok\n");
    if(0 == strncmp("(C),",szOUTtemp,4) ) {
      fprintf(g_flog,"szOUTtemp[4] is %c\n",szOUTtemp[4]);

      switch(szOUTtemp[4]) {
	case 'B':
	  fprintf(g_flog,"out (c),b detected\n");
          g_ucBytes[g_iBytesIndex++] = 0xED;
          g_ucBytes[g_iBytesIndex++] = 0x41 + 0x00;
          g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
 	  break;
	case 'C':
          g_ucBytes[g_iBytesIndex++] = 0xED;
          g_ucBytes[g_iBytesIndex++] = 0x41 + 0x08;
          g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
	  break;
	case 'D':
          g_ucBytes[g_iBytesIndex++] = 0xED;
          g_ucBytes[g_iBytesIndex++] = 0x41 + 0x10;
          g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
	  break;
	case 'E':
          g_ucBytes[g_iBytesIndex++] = 0xED;
          g_ucBytes[g_iBytesIndex++] = 0x41 + 0x18;
          g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
	  break;
	case 'H':
          g_ucBytes[g_iBytesIndex++] = 0xED;
          g_ucBytes[g_iBytesIndex++] = 0x41 + 0x20;
          g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
	  break;
	case 'L':
          g_ucBytes[g_iBytesIndex++] = 0xED;
          g_ucBytes[g_iBytesIndex++] = 0x41 + 0x28;
          g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
	  break;
	case 'A':
          g_ucBytes[g_iBytesIndex++] = 0xED;
          g_ucBytes[g_iBytesIndex++] = 0x41 + 0x38;
          g_iLineType = TYPE_Z80;
          g_iErrorNo ^= ERROR_UNKOP;
	  break;
      }
    }
  }

  // check for "out (n),a"  and process if so...
  if(TYPE_ERR == g_iLineType) {
    if('(' == szOUTtemp[0]) {
      for(int l=1;l<strlen(szOUTtemp);l++) {
	if(')' == szOUTtemp[l]) {
	  szOUTtemp[l] = 0;
	}
      }  
      g_ucBytes[g_iBytesIndex++] = 0xD3;
      g_ucBytes[g_iBytesIndex++] = resolvep8(&szOUTtemp[1]);
      g_iLineType = TYPE_Z80; 
          g_iErrorNo ^= ERROR_UNKOP;
    }
  }

}
 
