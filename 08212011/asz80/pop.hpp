// ---------------------------------------------------
// pop.hpp      21-Feb-11   Running on Mac OS X 10.6.6
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

if(0 == strcmp(strupr(g_szOpcode),"POP")) {
	g_iErrorNo ^= ERROR_UNKOP;
	fprintf(g_flog,"Processing Z80  POP g_szOpcode\n");
	if(0 < strlen(g_szParms)) {
		int bDone = FALSE;
		if(0 == strcmp(strupr(g_szParms),"AF")) {
			g_ucBytes[g_iBytesIndex++] = 0x71;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"B")) {
			g_ucBytes[g_iBytesIndex++] = 0xC1;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"D")) {
			g_ucBytes[g_iBytesIndex++] = 0xD1;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"H")) {
			g_ucBytes[g_iBytesIndex++] = 0xE1;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"BC")) {
			g_ucBytes[g_iBytesIndex++] = 0xC1;
			bDone = TRUE;
		}
                if(0 == strcmp(strupr(g_szParms),"DE")) {
                        g_ucBytes[g_iBytesIndex++] = 0xD1;
			bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"HL")) {
                        g_ucBytes[g_iBytesIndex++] = 0xE1;
			bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"PSW")) {
                        g_ucBytes[g_iBytesIndex++] = 0xF1;
			bDone = TRUE;
                }
		if(FALSE == bDone) {
			g_iErrorNo |= ERROR_NOREG;
		}
	} else {
		g_iErrorNo |= ERROR_NOPARM;
	}
}

