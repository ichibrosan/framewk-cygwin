// ---------------------------------------------------
// asparse.hpp  21-Feb-11   Running on Mac OS X 10.6.6
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

static char szAsparseHpp[] = "$Id: asparse.hpp,v 1.1 2011/03/24 11:58:05 doug Exp $";

void asparse(void)
{
	sprintf(g_szAsparseHpp,"%s %s %s",__FILE__,__TIME__,__DATE__);

	fprintf(g_flog,"\nsrc: %s\n",g_szBuffer);

	memset(g_szLabel,0,sizeof(g_szLabel));
	memset(g_szOpcode,0,sizeof(g_szOpcode));
	memset(g_szParms,0,sizeof(g_szParms));
	memset(g_szComments,0,sizeof(g_szComments));
	int pindex = 0;
	g_iState = 0;
	g_iBytesIndex = 0;
	while(pindex < strlen(g_szBuffer)) {		
		g_cToken = g_szBuffer[pindex++];
		switch(g_iState) {
			case 0:	// looking for label start
				if(g_bDebug) {
					printf("0");
				}
				if(' ' == g_cToken) {
					g_iState = 2;	// looking for g_szOpcode start
					break;
				}	
				if(ASCII_TAB == g_cToken) {
					g_iState = 2;	// looking for g_szOpcode start
					break;
				}	
				if(';' == g_cToken) {
					g_bComments = 1;
					g_iState = 7;				
					g_szComments[strlen(g_szComments)] = g_cToken;
					break;
				}
				g_iState = 1;
				g_szLabel[strlen(g_szLabel)] = g_cToken;
				g_bLabel = 1;
				break;
			case 1:	// process label character
				if(g_bDebug) {
					printf("1");
				}
				if(':' == g_cToken) {
					g_iState = 2;	// wait for g_szOpcode
					break;
				}
				if(' ' == g_cToken) {
					g_iState = 2;	// wait for g_szOpcode
					break;
				}
				if(ASCII_TAB == g_cToken) {
					g_iState = 2;	// wait for g_szOpcode
							break;
				}
				g_szLabel[strlen(g_szLabel)] = g_cToken;				
				g_bLabel = 1;
				break;
			case 2: // wait for g_szOpcode
				if(g_bDebug) {
					printf("2");
				}
				if(';' == g_cToken) {
					g_iState = 6;	// wait for g_szOpcode
					break;
					g_szComments[strlen(g_szComments)] = g_cToken;
					
				}
				if(' ' == g_cToken) {
					break;
				}
				if(ASCII_TAB == g_cToken) {
					break;
				}	
				g_szOpcode[strlen(g_szOpcode)] = g_cToken;
				g_bOpcode = 1;
				g_iState = 3;
				break;
			
			case 3:	// process g_szOpcode
				if(g_bDebug) {
					printf("3");
				}
				if(' ' == g_cToken) {
					g_iState = 4;	// waiting for parm
					break;
				}
				if(ASCII_TAB == g_cToken) {
					g_iState = 4;	// waiting for		 	parm
					break;
				}			
				g_szOpcode[strlen(g_szOpcode)] = g_cToken;
				g_bOpcode = 1;
				break;
			case 4:	// wait for parm
				if(g_bDebug) {
					printf("4");
				}
				if(' ' == g_cToken) {
					break;		
				}
				if(ASCII_TAB == g_cToken) {
					break;
				}				
				g_iState = 5;	// process parm
				g_szParms[strlen(g_szParms)] = g_cToken;
				g_bParms = 1;
				break;
			case 5: // process parm
				if(g_bDebug) {
					printf("5");
				}
				if(ASCII_TAB == g_cToken) {
					g_iState = 6;
					break;
				}

// tabs are required to separate parms from comments
//				if(ASCII_SPACE == g_cToken) {
//					g_iState = 6;
//					break;
//				}

				// added 3/12/2011 dwg - 
				// handle g_szParms succeeded by semicolon
				// without intervening spaces
				if(ASCII_SEMI == g_cToken) {
                                  g_iState = 7;
                                  g_szComments[strlen(g_szComments)] = g_cToken;
                                  g_bComments = 1;
                                  break;
				}

				g_szParms[strlen(g_szParms)] = g_cToken;
				g_bParms = 1;
				break;
			case 6:	// waiting for remark
				if(g_bDebug) {
					printf("6");
				}
				if(' ' == g_cToken) {
					break;
				}
				
				if(ASCII_TAB == g_cToken) {
					break;
				}
				g_iState = 7;
				g_szComments[strlen(g_szComments)] = g_cToken;
				g_bComments = 1;
				break;
			case 7:	// process remark
				if(g_bDebug) {
					printf("7");
				}
				if('\n' == g_cToken) {
					break;
				}					
				g_szComments[strlen(g_szComments)] = g_cToken;
				g_bComments = 1;
				break;
		};
	};

	fprintf(g_flog,"label[%d] g_szOpcode[%d] g_szParms[%d] comments[%d]\n",
		strlen(g_szLabel),strlen(g_szOpcode),strlen(g_szParms),strlen(g_szComments));
}
	
// eof - asparse.hpp
