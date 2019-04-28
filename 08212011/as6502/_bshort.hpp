// ---------------------------------------------------
// _bshort.hpp  22-Feb-11   Running on Mac OS X 10.6.6
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

// When calculating branches a forward branch of 6 skips the 
// following 6 g_ucBytes so, effectively the program counter points 
// to the address that is 8 g_ucBytes beyond the address of the 
// branch g_szOpcode; and a backward branch of $FA (256-6) goes
// to an address 7 g_ucBytes before the branch instruction

		int tgt = resolvep16(g_szParms);
		if(tgt < g_iPc) {
			if( (g_iPc-tgt) > 126) {
				g_iErrorNo |= ERROR_RANGE;
				g_ucBytes[g_iBytesIndex++] = 0xE5;
			} else {
				// emit backward displacement
				g_ucBytes[g_iBytesIndex++] =
					256-(g_iPc-tgt-1);
			}
		}
		if(tgt > g_iPc) {
			if( (tgt-g_iPc) > 126) {
				g_iErrorNo |= ERROR_RANGE;
				g_ucBytes[g_iBytesIndex++] = 0xE5;
			} else {
				// emit forward displacement

//	printf("tgt(0x%04X) - pc(0x%04X) = 0x%04X\n",
//		tgt,g_iPc,tgt-g_iPc);

				g_ucBytes[g_iBytesIndex++] = tgt-g_iPc-2;
			}		
		}

