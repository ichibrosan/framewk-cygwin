// ---------------------------------------------------
// asouthex.hpp  6-Mar-11   Running on Mac OS X 10.6.6
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

static char szAsouthexHpp[] = "$Id: asouthex.hpp,v 1.1 2011/03/24 11:58:05 doug Exp $";

void asouthex(void)
{
	int mypc = g_iPc;
	
	if( 3 < g_iBytesIndex ) {
		if(g_bDebug) {
			printf("\nemitlst says g_iBytesIndex > 3\n");
		}
		g_iTriplets = g_iBytesIndex / 3;
		if(g_bDebug) {
			printf("\ntriplets = %d\n",g_iTriplets);
		}
		g_iSobrante = g_iBytesIndex - (g_iTriplets * 3);
		if(g_bDebug) {
			printf("\nsobrante = %d\n",g_iSobrante);
		}
		for(int t=0;t<g_iTriplets;t++) {
			g_iTripoff = t * 3;
			if(g_bDebug) {
				printf(" t = %d ",t);
			}
			hexout(mypc,3,g_iTripoff);
			mypc += 3;
		}
		if(0 != g_iSobrante) { 
			g_iSoboff = g_iTriplets * 3;
			switch(g_iSobrante) {
				case 1:
					hexout(mypc,1,g_iSoboff);
					mypc += 1;
					break;								
				case 2:
					hexout(mypc,2,g_iSoboff);
					mypc += 2;
					break;
			};			
		}
	} else {
		switch(g_iBytesIndex) {
			case 1:
				hexout(mypc,1,0);
				mypc += 1;
				break;
			case 2:
				hexout(mypc,2,0);
				mypc += 2;
				break;
			case 3:
				hexout(mypc,3,0);
				mypc += 3;
				break;
		};
	}
}

////////////////////////
// eof - asouthex.hpp //
////////////////////////
