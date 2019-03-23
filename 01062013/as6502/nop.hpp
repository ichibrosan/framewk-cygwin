char nop_65[] = "$Log$";

// ---------------------------------------------------
// nop.hpp      22-Feb-11   Running on Mac OS X 10.6.6
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

	if(0 == strcmp(strupr(g_szOpcode),"NOP")) {
		fprintf(g_flog,"Processing 6502 NOP g_szOpcode\n");
		g_ucBytes[g_iBytesIndex++] = 0xEA;
		g_iLineType = TYPE_6502;
		g_iErrorNo ^= ERROR_UNKOP;
	}

