// ---------------------------------------------------
// LD.HPP       28-Jan-11 DOSBox-0.74 Version 1.00.00a
// Serial No. 8208-4162-344865    All Rights Reserved.
// Copyright (C) 2010 Douglas Goodall,  United States.
// ---------------------------------------------------
	
if(0 == strcmp(strupr(g_szOpcode),"LD")) {

	unsigned int uiTemp;

	char szLDtemp[DEFAULT_STRSIZE];
	char szLDtemp2[DEFAULT_STRSIZE];

	strcpy(szLDtemp2,g_szParms);
	strcpy(szLDtemp,strupr(szLDtemp2));

	fprintf(g_flog,"Processing LD g_szOpcode\n");
	fprintf(g_flog,"szLDtemp = %s\n",szLDtemp);

	g_iErrorNo ^= ERROR_UNKOP;
	g_iLineType = TYPE_Z80;

	if(0 < strlen(g_szParms)) {
		int bDone = FALSE;
		if(0 == strcmp(strupr(g_szParms),"A,A")) {
			g_ucBytes[g_iBytesIndex++] = 0x7f;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"A,B")) {
			g_ucBytes[g_iBytesIndex++] = 0x78;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"A,C")) {
			g_ucBytes[g_iBytesIndex++] = 0x79;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"A,D")) {
			g_ucBytes[g_iBytesIndex++] = 0x7a;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"A,E")) {
			g_ucBytes[g_iBytesIndex++] = 0x7b;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"A,H")) {
			g_ucBytes[g_iBytesIndex++] = 0x7c;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"A,I")) {
			g_ucBytes[g_iBytesIndex++] = 0xed;
			g_ucBytes[g_iBytesIndex++] = 0x57;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"A,L")) {
			g_ucBytes[g_iBytesIndex++] = 0x7d;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"A,R")) {
			g_ucBytes[g_iBytesIndex++] = 0xed;
			g_ucBytes[g_iBytesIndex++] = 0x5f;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"A,(BC)")) {
			g_ucBytes[g_iBytesIndex++] = 0x0a;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"A,(DE)")) {
			g_ucBytes[g_iBytesIndex++] = 0x1a;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"A,(HL)")) {
			g_ucBytes[g_iBytesIndex++] = 0x7e;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"B,A")) {
			g_ucBytes[g_iBytesIndex++] = 0x47;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"B,B")) {
			g_ucBytes[g_iBytesIndex++] = 0x40;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"B,C")) {
			g_ucBytes[g_iBytesIndex++] = 0x41;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"B,D")) {
			g_ucBytes[g_iBytesIndex++] = 0x42;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"B,E")) {
			g_ucBytes[g_iBytesIndex++] = 0x43;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"B,H")) {
			g_ucBytes[g_iBytesIndex++] = 0x44;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"B,L")) {
			g_ucBytes[g_iBytesIndex++] = 0x45;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"B,(HL)")) {
			g_ucBytes[g_iBytesIndex++] = 0x46;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"C,A")) {
			g_ucBytes[g_iBytesIndex++] = 0x4f;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"C,B")) {
			g_ucBytes[g_iBytesIndex++] = 0x48;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"C,C")) {
			g_ucBytes[g_iBytesIndex++] = 0x49;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"C,D")) {
			g_ucBytes[g_iBytesIndex++] = 0x4a;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"C,E")) {
			g_ucBytes[g_iBytesIndex++] = 0x4b;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"C,H")) {
			g_ucBytes[g_iBytesIndex++] = 0x4c;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"C,L")) {
			g_ucBytes[g_iBytesIndex++] = 0x4d;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"C,(HL)")) {
			g_ucBytes[g_iBytesIndex++] = 0x4e;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"D,A")) {
			g_ucBytes[g_iBytesIndex++] = 0x57;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"D,B")) {
			g_ucBytes[g_iBytesIndex++] = 0x50;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"D,C")) {
			g_ucBytes[g_iBytesIndex++] = 0x51;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"D,D")) {
			g_ucBytes[g_iBytesIndex++] = 0x52;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"D,E")) {
			g_ucBytes[g_iBytesIndex++] = 0x53;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"D,H")) {
			g_ucBytes[g_iBytesIndex++] = 0x54;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"D,L")) {
			g_ucBytes[g_iBytesIndex++] = 0x55;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"D,(HL)")) {
			g_ucBytes[g_iBytesIndex++] = 0x56;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"E,A")) {
			g_ucBytes[g_iBytesIndex++] = 0x5f;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"E,B")) {
			g_ucBytes[g_iBytesIndex++] = 0x58;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"E,C")) {
			g_ucBytes[g_iBytesIndex++] = 0x59;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"E,D")) {
			g_ucBytes[g_iBytesIndex++] = 0x5a;
                        bDone = TRUE;
		}
                if(0 == strcmp(strupr(g_szParms),"E,E")) {
                        g_ucBytes[g_iBytesIndex++] = 0xE5;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"E,H")) {
                        g_ucBytes[g_iBytesIndex++] = 0xE5;
                        bDone = TRUE;
                }
		if(0 == strcmp(strupr(g_szParms),"E,L")) {
			g_ucBytes[g_iBytesIndex++] = 0x5d;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"E,(HL)")) {
			g_ucBytes[g_iBytesIndex++] = 0x5e;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"H,A")) {
			g_ucBytes[g_iBytesIndex++] = 0x67;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"H,B")) {
			g_ucBytes[g_iBytesIndex++] = 0x60;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"H,C")) {
			g_ucBytes[g_iBytesIndex++] = 0x61;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"H,D")) {
			g_ucBytes[g_iBytesIndex++] = 0x62;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"H,E")) {
			g_ucBytes[g_iBytesIndex++] = 0x63;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"H,H")) {
			g_ucBytes[g_iBytesIndex++] = 0x64;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"H,L")) {
			g_ucBytes[g_iBytesIndex++] = 0x65;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"H,(HL)")) {
			g_ucBytes[g_iBytesIndex++] = 0x66;
			bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"I,A")) {
			g_ucBytes[g_iBytesIndex++] = 0xED;
			g_ucBytes[g_iBytesIndex++] = 0x47;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"L,A")) {
			g_ucBytes[g_iBytesIndex++] = 0x6f;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"L,B")) {
			g_ucBytes[g_iBytesIndex++] = 0x6b;
                        bDone = TRUE;
		}
                if(0 == strcmp(strupr(g_szParms),"L,C")) {
                        g_ucBytes[g_iBytesIndex++] = 0x6b;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"L,D")) {
                        g_ucBytes[g_iBytesIndex++] = 0x6b;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"L,E")) {
                        g_ucBytes[g_iBytesIndex++] = 0x6b;
                        bDone = TRUE;
                }
		if(0 == strcmp(strupr(g_szParms),"L,H")) {
			g_ucBytes[g_iBytesIndex++] = 0x6c;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"L,L")) {
			g_ucBytes[g_iBytesIndex++] = 0x6d;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"L,(HL)")) {
			g_ucBytes[g_iBytesIndex++] = 0x6e;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"R,A")) {
			g_ucBytes[g_iBytesIndex++] = 0xED;
			g_ucBytes[g_iBytesIndex++] = 0x4f;
                        bDone = TRUE;
		}
		if(0 == strcmp(strupr(g_szParms),"SP,HL")) {
			g_ucBytes[g_iBytesIndex++] = 0xf9;
                        bDone = TRUE;
		}
		if(0 == strncmp(strupr(g_szParms),"BC,",3)) {
			g_ucBytes[g_iBytesIndex++] = 0x01;
			uiTemp = resolvep16(&g_szParms[3]);
			g_ucBytes[g_iBytesIndex++] = uiTemp & 0xff;
			g_ucBytes[g_iBytesIndex++] = uiTemp >> 8;
                        bDone = TRUE;
		}
               	if(0 == strncmp(strupr(g_szParms),"DE,",3)) {
                       	g_ucBytes[g_iBytesIndex++] = 0x11;
                       	uiTemp = resolvep16(&g_szParms[3]);
                       	g_ucBytes[g_iBytesIndex++] = uiTemp & 0xff;
                       	g_ucBytes[g_iBytesIndex++] = uiTemp >> 8;
                        bDone = TRUE;
               	}
               	if(0 == strncmp(strupr(g_szParms),"HL,",3)) {
                       	g_ucBytes[g_iBytesIndex++] = 0x21;
                       	uiTemp = resolvep16(&g_szParms[3]);
                       	g_ucBytes[g_iBytesIndex++] = uiTemp & 0xff;
                       	g_ucBytes[g_iBytesIndex++] = uiTemp >> 8;
                        bDone = TRUE;
               	}

                if(0 == strcmp("(HL),B",szLDtemp)) {
                        g_ucBytes[g_iBytesIndex++] =0x70 + 0x00;
                        bDone = TRUE;
                }
                if(0 == strcmp("(HL),C",szLDtemp)) {
                        g_ucBytes[g_iBytesIndex++] =0x70 + 0x01;
                        bDone = TRUE;
                }
                if(0 == strcmp("(HL),D",szLDtemp)) {
                        g_ucBytes[g_iBytesIndex++] =0x70 + 0x02;
                        bDone = TRUE;
                }
                if(0 == strcmp("(HL),E",szLDtemp)) {
                        g_ucBytes[g_iBytesIndex++] =0x70 + 0x03;
                        bDone = TRUE;
                }
                if(0 == strcmp("(HL),H",szLDtemp)) {
                        g_ucBytes[g_iBytesIndex++] =0x70 + 0x04;
                        bDone = TRUE;
		}
                if(0 == strcmp("(HL),L",szLDtemp)) {
                        g_ucBytes[g_iBytesIndex++] =0x70 + 0x05;
                        bDone = TRUE;
                }
                if(0 == strcmp("(HL),A",szLDtemp)) {
                        fprintf(g_flog,"proc ld (HL),A\n");
                        g_ucBytes[g_iBytesIndex++] =0x70 + 0x07;
                        bDone = TRUE;
		}
		if(FALSE == bDone) {
               		if(0 == strncmp(g_szParms,"B,",2)) {
                       		g_ucBytes[g_iBytesIndex++] = 0x06+0x00;
                       		g_ucBytes[g_iBytesIndex++] = resolvep8(&g_szParms[2]);
                        	bDone = TRUE;
               		}
               		if(0 == strncmp(g_szParms,"C,",2)) {
                       		g_ucBytes[g_iBytesIndex++] = 0x06+0x08;
                       		g_ucBytes[g_iBytesIndex++] = resolvep8(&g_szParms[2]);
                        	bDone = TRUE;
               		}
               		if(0 == strncmp(g_szParms,"D,",2)) {
                       		g_ucBytes[g_iBytesIndex++] = 0x06+0x10;
                       		g_ucBytes[g_iBytesIndex++] = resolvep8(&g_szParms[2]);
                        	bDone = TRUE;
               		}
			if(0 == strncmp(g_szParms,"E,",2)) {
				g_ucBytes[g_iBytesIndex++] = 0x06+0x18;
				g_ucBytes[g_iBytesIndex++] = resolvep8(&g_szParms[2]);
                        	bDone = TRUE;
			}
                	if(0 == strncmp(g_szParms,"H,",2)) {
                       		g_ucBytes[g_iBytesIndex++] = 0x06+0x20;
                       		g_ucBytes[g_iBytesIndex++] = resolvep8(&g_szParms[2]);
                        	bDone = TRUE;
                	}
                	if(0 == strncmp(g_szParms,"L,",2)) {
                       		g_ucBytes[g_iBytesIndex++] = 0x06+0x28;
                       		g_ucBytes[g_iBytesIndex++] = resolvep8(&g_szParms[2]);
                        	bDone = TRUE;
                	}
                	if(0 == strncmp(g_szParms,"A,",2)) {
                       		g_ucBytes[g_iBytesIndex++] = 0x06+0x38;
                       		g_ucBytes[g_iBytesIndex++] = resolvep8(&g_szParms[2]);
                        	bDone = TRUE;
                	}
		}
		if(FALSE == bDone) {
			g_iErrorNo |= ERROR_SYNTAX;
		}
 	} else {
		g_iErrorNo |= ERROR_NOPARM;
	}
}

//////////////////
// eof - ld.hpp //
//////////////////

