// ---------------------------------------------------
// asoutlst.hpp 21-Feb-11   Running on Mac OS X 10.6.6
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

static char szAsoutlstHpp[] = "$Id: asoutlst.hpp,v 1.2 2011/03/25 05:48:59 doug Exp $";

void asoutlst(void)
{
        unsigned int mypc = g_iPc;

	
	if( (g_iBytesIndex == 0) && (strlen(g_szLabel)==0)  &&
	                         (strlen(g_szOpcode)==0) &&
				 (strlen(g_szParms)==0)  &&
				 (strlen(g_szComments)!=0) ) {
	} else {
		// this code pads out the fields so they
		// align in the listing file
		for(int x=0;x<8;x++) {
			if(strlen(g_szLabel) < 8) strcat(g_szLabel," ");
		}
	
		for(int y=0;y<8;y++) {
			if(strlen(g_szOpcode) < 9) strcat(g_szOpcode," ");
		}
	}			 
	
	
	if( 3 < g_iBytesIndex ) {

		// if the number of byte > 3, it is
		// necessary to print the original line
		// so you can tell what called the expansion
		
		// if the number of g_ucBytes is 3 or less, 
		// the normal print function handles it.
				
		strcpy(g_szBuffer2,"               ");
		strcat(g_szBuffer2,g_szLabel);		
		for(int i=0;i<(10-strlen(g_szLabel));i++) {
			strcat(g_szBuffer2," ");
		}
		strcat(g_szBuffer2,g_szOpcode);
		for(int i=0;i<(11-strlen(g_szOpcode));i++) {
			strcat(g_szBuffer2," ");
		}
		strcat(g_szBuffer2,g_szParms);
		for(int i=0;i<30;i++) {
			strcat(g_szBuffer2," ");
		}
		strcat(g_szBuffer2,g_szComments);
		print(g_flst);


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
			sprintf(g_szParms,"%03XH,%03XH,%03XH",
				g_ucBytes[g_iTripoff],
				g_ucBytes[g_iTripoff+1],
				g_ucBytes[g_iTripoff+2]);
				
			sprintf(g_szComments,"; %c%c%c",
				g_ucBytes[g_iTripoff],
				g_ucBytes[g_iTripoff+1],
				g_ucBytes[g_iTripoff+2]);
				
			sprintf(g_szPc,g_szListRadix,mypc);
			sprintf(g_szBuffer,"%s: %02X %02X %02X %s%s%s%s%s%s%s",
				g_szPc,
				g_ucBytes[g_iTripoff],
				g_ucBytes[g_iTripoff+1],
				g_ucBytes[g_iTripoff+2],
//				g_szLabel,g_szSep,g_szOpcode,
				g_szLabel,g_szSep,"db       ",
				g_szSep,g_szParms,g_szSep,g_szComments);
			strcpy(g_szBuffer2,g_szBuffer);
			print(g_flst);
			mypc += 3;
		}
		if(0 != g_iSobrante) { 
			g_iSoboff = g_iTriplets * 3;
			switch(g_iSobrante) {
				case 1:
					sprintf(g_szParms,"%03XH          ",
						g_ucBytes[g_iSoboff]);
			
					sprintf(g_szComments,"; %c",
						g_ucBytes[g_iSoboff]);
                        		
					sprintf(g_szPc,g_szListRadix,mypc);	
					sprintf(g_szBuffer,"%s: %02X       %s%s%s%s%s%s%s",
						g_szPc,
						g_ucBytes[g_iSoboff],
//						g_szLabel,g_szSep,g_szOpcode,
						g_szLabel,g_szSep,"db       ",
						g_szSep,g_szParms,g_szSep,g_szComments);
					strcpy(g_szBuffer2,g_szBuffer);
					print(g_flst);
					mypc += 1;
					break;								
				case 2:
					sprintf(g_szParms,"%03XH,%03XH     ",
						g_ucBytes[g_iSoboff],
						g_ucBytes[g_iSoboff+1]);
				
					sprintf(g_szComments,"; %c%c",
						g_ucBytes[g_iSoboff],
						g_ucBytes[g_iSoboff+1]);

                        		sprintf(g_szPc,g_szListRadix,mypc);	
					sprintf(g_szBuffer,"%s: %02X %02X    %s%s%s%s%s%s%s",
						g_szPc,
						g_ucBytes[g_iSoboff],
						g_ucBytes[g_iSoboff+1],
//						g_szLabel,g_szSep,g_szOpcode,
						g_szLabel,g_szSep,"db       ",
						g_szSep,g_szParms,g_szSep,g_szComments);
					strcpy(g_szBuffer2,g_szBuffer);
					print(g_flst);
					mypc += 2;
					break;
			};			
		}
	} else {
		switch(g_iBytesIndex) {
			case 0:
                        	sprintf(g_szPc,g_szListRadix,mypc);
				sprintf(g_szBuffer,"%s:          %s%s%s%s%s%s%s",
					g_szPc,g_szLabel,g_szSep,g_szOpcode,g_szSep,g_szParms,g_szSep,g_szComments);
				break;
			case 1:
                        	sprintf(g_szPc,g_szListRadix,mypc);
				sprintf(g_szBuffer,"%s: %02X       %s%s%s%s%s%s%s",
					g_szPc,g_ucBytes[0],g_szLabel,g_szSep,g_szOpcode,g_szSep,
//					mypc,g_ucBytes[0],g_szLabel,g_szSep,"db       ",g_szSep,
						g_szParms,g_szSep,g_szComments);
				mypc += 1;				
				break;
			case 2:
                        	sprintf(g_szPc,g_szListRadix,mypc);
				sprintf(g_szBuffer,"%s: %02X %02X    %s%s%s%s%s%s%s",
					g_szPc,g_ucBytes[0],g_ucBytes[1],g_szLabel,g_szSep,g_szOpcode,
//					mypc,g_ucBytes[0],g_ucBytes[1],g_szLabel,g_szSep,"db       ",
						g_szSep,g_szParms,g_szSep,g_szComments);
				mypc += 2;
				break;
			case 3:
                        	sprintf(g_szPc,g_szListRadix,mypc);
				sprintf(g_szBuffer,"%s: %02X %02X %02X %s%s%s%s%s%s%s",
					g_szPc,g_ucBytes[0],g_ucBytes[1],g_ucBytes[2],g_szLabel,g_szSep,
					g_szOpcode,g_szSep,g_szParms,g_szSep,g_szComments);
//					"db       ",g_szSep,g_szParms,g_szSep,g_szComments);
				mypc += 3;
				break;
		};
		strcpy(g_szBuffer2,g_szBuffer);
		print(g_flst);
	}
}	
// eof - emitlst.hpp
