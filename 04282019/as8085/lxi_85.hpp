// $Log: lxi_85.hpp,v $
// Revision 1.2  2011/03/25 22:47:07  doug
// add log and trim gpl stuff
////

char lxi_85[] = "$Id: lxi_85.hpp,v 1.2 2011/03/25 22:47:07 doug Exp $";

// Copyright(c)2011 Douglas W. Goodall, United States.

if(0 == strcmp(strupr(g_szOpcode),"LXI")) {
	fprintf(g_flog,"Processing 8085 LXI g_szOpcode\n");
        g_iLineType = TYPE_8085;
        g_iErrorNo ^= ERROR_UNKOP;
	if(0 < strlen(g_szParms)) {
		if(',' == g_szParms[1]) {
			// single letter register
			switch(g_szParms[0]) {
				case 'b':
				case 'B':
	                                g_ucBytes[g_iBytesIndex++] = 0x01;
        	                        value = resolvep16(&g_szParms[2]);
                	                g_ucBytes[g_iBytesIndex++] = value & 0x00ff;
                        	        g_ucBytes[g_iBytesIndex++] = value >> 8;
                                	break;
                                case 'd':
                                case 'D':
                                        g_ucBytes[g_iBytesIndex++] = 0x11;
                                        value = resolvep16(&g_szParms[2]);
                                        g_ucBytes[g_iBytesIndex++] = value & 0x00ff;
                                        g_ucBytes[g_iBytesIndex++] = value >> 8;
                                        break;
                                case 'h':
                                case 'H':
                                        g_ucBytes[g_iBytesIndex++] = 0x21;
                                        value = resolvep16(&g_szParms[2]);
                                        g_ucBytes[g_iBytesIndex++] = value & 0x00ff;
                                        g_ucBytes[g_iBytesIndex++] = value >> 8;
                                        break;
				default:
					g_iErrorNo |= ERROR_NOREG;
					break;
			}
		}
		if(',' == g_szParms[2]) {
			// double letter register
			switch(g_szParms[0]) {
				case 'b':
				case 'B':
					g_ucBytes[g_iBytesIndex++] = 0x01;
					value = resolvep16(&g_szParms[3]);
					g_ucBytes[g_iBytesIndex++] = value & 0x00ff;
					g_ucBytes[g_iBytesIndex++] = value >> 8;
					break;
                        	case 'd':
				case 'D':
                                	g_ucBytes[g_iBytesIndex++] = 0x11;
                                	value = resolvep16(&g_szParms[3]);
                                	g_ucBytes[g_iBytesIndex++] = value & 0x00ff;
                                	g_ucBytes[g_iBytesIndex++] = value >> 8;
                                	break;
                        	case 'h':
				case 'H':
                                	g_ucBytes[g_iBytesIndex++] = 0x21;
                                	value = resolvep16(&g_szParms[3]);
                                	g_ucBytes[g_iBytesIndex++] = value & 0x00ff;
                                	g_ucBytes[g_iBytesIndex++] = value >> 8;
                                	break;
                                case 's':
				case 'S':
                                        g_ucBytes[g_iBytesIndex++] = 0x31;
                                        value = resolvep16(&g_szParms[3]);
                                        g_ucBytes[g_iBytesIndex++] = value & 0x00ff;
                                        g_ucBytes[g_iBytesIndex++] = value >> 8;
                                        break;
				default:
					g_iErrorNo |= ERROR_NOREG;
					break;
			}
		}
	} else {
		g_iErrorNo |= ERROR_NOPARM;
	}	
//printf("DEBUG: lxi_85.hpp - lxi processing completed\n");
}

///////////////////
// eof - lxi.hpp //
///////////////////

