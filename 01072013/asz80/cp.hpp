// ---------------------------------------------------
// cp.hpp        3-Mar-11   Running on Mac OS X 10.6.6
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

if(0 == strcmp(strupr(g_szOpcode),"CP")) {
	fprintf(g_flog,"Processing Z80  CP g_szOpcode\n");

	char szCPtemp[DEFAULT_STRSIZE];
	char szCPtemp2[DEFAULT_STRSIZE];

	strcpy(szCPtemp2,g_szParms);
	strcpy(szCPtemp,strupr(szCPtemp2));
	fprintf(g_flog,"szCPtemp is %s\n",szCPtemp);
	g_iErrorNo ^= ERROR_UNKOP;

//	three kinds of cp exist
//		cp (hl)
//		cp R
//		cp N

	fprintf(g_flog,"g_szParms are %s\n",g_szParms);

	if(0 == strcmp("(HL)",szCPtemp)) {
        	fprintf(g_flog,"using cp (HL)");
		g_ucBytes[g_iBytesIndex++] = 0xBE;
		g_iLineType = TYPE_Z80;
	}

	if(1 == strlen(g_szParms)) {

		switch(szCPtemp[0]) {
			case 'A':
			case 'a':
                        	fprintf(g_flog,"using cp A");
				g_ucBytes[g_iBytesIndex++] = 0x80+0x38+0x07;  // A
                        	g_iLineType = TYPE_Z80;
				break;
			case 'B':
			case 'b':	
                        	fprintf(g_flog,"using cp B");
                                g_ucBytes[g_iBytesIndex++] = 0x80+0x38+0x00;  // B
                        	g_iLineType = TYPE_Z80;
                                break;
			case 'C':
			case 'c':                       
                        	fprintf(g_flog,"using cp C");
                                g_ucBytes[g_iBytesIndex++] = 0x80+0x38+0x01;  // C
                        	g_iLineType = TYPE_Z80;
                                break;
                        case 'D':
			case 'd':
				fprintf(g_flog,"using cp D");
                                g_ucBytes[g_iBytesIndex++] = 0x80+0x38+0x02;  // D
                        	g_iLineType = TYPE_Z80;
                                break;
			case 'E':
			case 'e':
                        	fprintf(g_flog,"using cp E");
                                g_ucBytes[g_iBytesIndex++] = 0x80+0x38+0x03;  // E
                        	g_iLineType = TYPE_Z80;
                                break;
			case 'H':
			case 'h':
                        	fprintf(g_flog,"using cp H");
                                g_ucBytes[g_iBytesIndex++] = 0x80+0x38+0x04;  // H
                        	g_iLineType = TYPE_Z80;
                                break;
			case 'L':
			case 'l':
                        	fprintf(g_flog,"using cp L");
                                g_ucBytes[g_iBytesIndex++] = 0x80+0x38+0x05;  // L
                        	g_iLineType = TYPE_Z80;
                                break;
                }
	}

        if(TYPE_ERR == g_iLineType) {
		fprintf(g_flog,"using cp N");
                g_ucBytes[g_iBytesIndex++] = 0xC0+0x38+0x06;
		if(0 < strlen(g_szParms)) {
			g_ucBytes[g_iBytesIndex++] = resolvep8(g_szParms);
		} else {
			g_iErrorNo |= ERROR_NOPARM;
		}
        }
	g_iLineType = TYPE_Z80;
}

//////////////////
// eof - cp.hpp //
//////////////////

