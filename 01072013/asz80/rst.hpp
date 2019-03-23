// ---------------------------------------------------
// rst.hpp      21-Feb-11   Running on Mac OS X 10.6.6
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

if(0 == strcmp(strupr(g_szOpcode),"RST")) {
	fprintf(g_flog,"Processing 8085 RST g_szOpcode\n");
	g_iErrorNo ^= ERROR_UNKOP;
	g_iLineType = TYPE_Z80;
	if(0 < strlen(g_szParms)) {
		if(0 == strcmp("00H",strupr(g_szParms))) strcpy(g_szParms,"0");
                if(0 == strcmp("01H",strupr(g_szParms))) strcpy(g_szParms,"1");
                if(0 == strcmp("02H",strupr(g_szParms))) strcpy(g_szParms,"2");
                if(0 == strcmp("03H",strupr(g_szParms))) strcpy(g_szParms,"3");
                if(0 == strcmp("04H",strupr(g_szParms))) strcpy(g_szParms,"4");
                if(0 == strcmp("05H",strupr(g_szParms))) strcpy(g_szParms,"5");
                if(0 == strcmp("06H",strupr(g_szParms))) strcpy(g_szParms,"6");
                if(0 == strcmp("07H",strupr(g_szParms))) strcpy(g_szParms,"7");
                if(0 == strcmp("$00",strupr(g_szParms))) strcpy(g_szParms,"0");
                if(0 == strcmp("$01",strupr(g_szParms))) strcpy(g_szParms,"1");
                if(0 == strcmp("$02",strupr(g_szParms))) strcpy(g_szParms,"2");
                if(0 == strcmp("$03",strupr(g_szParms))) strcpy(g_szParms,"3");
                if(0 == strcmp("$04",strupr(g_szParms))) strcpy(g_szParms,"4");
                if(0 == strcmp("$05",strupr(g_szParms))) strcpy(g_szParms,"5");
                if(0 == strcmp("$06",strupr(g_szParms))) strcpy(g_szParms,"6");
                if(0 == strcmp("$07",strupr(g_szParms))) strcpy(g_szParms,"7");
		switch(g_szParms[0]) {
			case '0':
				g_ucBytes[g_iBytesIndex++] = 0xC7;
				break;
			case '1':
                                g_ucBytes[g_iBytesIndex++] = 0xCF;
                                break;
			case '2':
                                g_ucBytes[g_iBytesIndex++] = 0xD7;
                                break;
			case '3':
                                g_ucBytes[g_iBytesIndex++] = 0xDF;
                                break;
			case '4':
                                g_ucBytes[g_iBytesIndex++] = 0xE7;
                                break;
			case '5':
                                g_ucBytes[g_iBytesIndex++] = 0xEF;
                                break;
			case '6':
                                g_ucBytes[g_iBytesIndex++] = 0xF7;
                                break;
			case '7':
                                g_ucBytes[g_iBytesIndex++] = 0xFF;
                                break;
			default:
				g_iErrorNo |= ERROR_NOVEC;
				break;
		}

	} else {
		g_iErrorNo |= ERROR_NOPARM;
	}
}


