// ---------------------------------------------------
// dd.hpp       23-Feb-11   Running on Mac OS X 10.6.6
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

if(0 == strcmp(strupr(g_szOpcode),"DD")) {
	fprintf(g_flog,"Processing Z80 DD  g_szOpcode\n");
	g_iErrorNo ^= ERROR_UNKOP;
	g_iLineType = TYPE_Z80;

	if(0 < strlen(g_szParms)) {

		unsigned long lTemp = resolvep32(g_szParms);
		unsigned int  uiTempl = (unsigned int)lTemp & 0x0000ffffL;
		unsigned int  uiTemph = (unsigned int)lTemp >> 16;

		fprintf(g_flog,"lTemp   was 0x%08lX\n",lTemp);
		fprintf(g_flog,"uiTempl was 0x%04X\n",uiTempl);
		fprintf(g_flog,"uiTemph was 0x%04X\n",uiTemph);

        	g_ucBytes[g_iBytesIndex++] = uiTempl & 0x00ff;
        	g_ucBytes[g_iBytesIndex++] = uiTempl >> 8;
        	g_ucBytes[g_iBytesIndex++] = uiTemph & 0x00ff;
		g_ucBytes[g_iBytesIndex++] = uiTemph >> 8;

	} else {
		g_iErrorNo |= ERROR_NOPARM;
	}
}

