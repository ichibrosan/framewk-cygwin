// $Log: mov_85.hpp,v $
// Revision 1.2  2011/03/25 22:47:07  doug
// add log and trim gpl stuff
////

char mov_85[] = "$Id: mov_85.hpp,v 1.2 2011/03/25 22:47:07 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

if(0 == strcmp(strupr(g_szOpcode),"MOV")) {
	fprintf(g_flog,"Processing 8085 MOV g_szOpcode\n");
        g_iLineType = TYPE_8085;
        g_iErrorNo ^= ERROR_UNKOP;
	if(0 < strlen(g_szParms)) {
		int bDone = FALSE;
		if(0 == strcmp(strupr(g_szParms),"A,A")) {
			g_ucBytes[g_iBytesIndex++] = 0x7F;
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
                        g_ucBytes[g_iBytesIndex++] = 0x7A;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"A,E")) {
                        g_ucBytes[g_iBytesIndex++] = 0x7B;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"A,H")) {
                        g_ucBytes[g_iBytesIndex++] = 0x7C;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"A,L")) {
                        g_ucBytes[g_iBytesIndex++] = 0x7D;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"A,M")) {
                        g_ucBytes[g_iBytesIndex++] = 0x7E;
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
                if(0 == strcmp(strupr(g_szParms),"B,M")) {
                        g_ucBytes[g_iBytesIndex++] = 0x46;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"C,A")) {
                        g_ucBytes[g_iBytesIndex++] = 0x4F;
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
                        g_ucBytes[g_iBytesIndex++] = 0x4A;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"C,E")) {
                        g_ucBytes[g_iBytesIndex++] = 0x4B;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"C,H")) {
                        g_ucBytes[g_iBytesIndex++] = 0x4C;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"C,L")) {
                        g_ucBytes[g_iBytesIndex++] = 0x4D;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"C,M")) {
                        g_ucBytes[g_iBytesIndex++] = 0x4E;
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
                if(0 == strcmp(strupr(g_szParms),"D,M")) {
                        g_ucBytes[g_iBytesIndex++] = 0x56;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"E,A")) {
                        g_ucBytes[g_iBytesIndex++] = 0x5F;
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
                        g_ucBytes[g_iBytesIndex++] = 0x5A;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"E,E")) {
                        g_ucBytes[g_iBytesIndex++] = 0x5B;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"E,H")) {
                        g_ucBytes[g_iBytesIndex++] = 0x5C;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"E,L")) {
                        g_ucBytes[g_iBytesIndex++] = 0x5D;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"E,M")) {
                        g_ucBytes[g_iBytesIndex++] = 0x5E;
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
                if(0 == strcmp(strupr(g_szParms),"H,M")) {
                        g_ucBytes[g_iBytesIndex++] = 0x66;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"L,A")) {
                        g_ucBytes[g_iBytesIndex++] = 0x6F;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"L,B")) {
                        g_ucBytes[g_iBytesIndex++] = 0x68;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"L,C")) {
                        g_ucBytes[g_iBytesIndex++] = 0x69;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"L,D")) {
                        g_ucBytes[g_iBytesIndex++] = 0x6A;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"L,E")) {
                        g_ucBytes[g_iBytesIndex++] = 0x6B;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"L,H")) {
                        g_ucBytes[g_iBytesIndex++] = 0x6C;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"L,L")) {
                        g_ucBytes[g_iBytesIndex++] = 0x6D;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"L,M")) {
                        g_ucBytes[g_iBytesIndex++] = 0x6E;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"M,A")) {
                        g_ucBytes[g_iBytesIndex++] = 0x77;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"M,B")) {
                        g_ucBytes[g_iBytesIndex++] = 0x70;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"M,C")) {
                        g_ucBytes[g_iBytesIndex++] = 0x71;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"M,D")) {
                        g_ucBytes[g_iBytesIndex++] = 0x72;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"M,E")) {
                        g_ucBytes[g_iBytesIndex++] = 0x73;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"M,H")) {
                        g_ucBytes[g_iBytesIndex++] = 0x74;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"M,L")) {
                        g_ucBytes[g_iBytesIndex++] = 0x75;
                        bDone = TRUE;
                }
                if(0 == strcmp(strupr(g_szParms),"M,M")) {
                        g_ucBytes[g_iBytesIndex++] = 0x7F;
                        bDone = TRUE;
                }
		if(FALSE == bDone) {
			g_iErrorNo |= ERROR_NOREG;
		}
	} else {
		g_iErrorNo |= ERROR_NOPARM;
	}
}

///////////////////
// eof - mov.hpp //
///////////////////

