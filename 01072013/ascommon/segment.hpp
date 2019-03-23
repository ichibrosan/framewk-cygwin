
char dir_segment[] = "$Id$";

// Copyright(c)2011 Douglas W. Goodall, United States.

if(0 == strcmp(strupr(g_szOpcode),"SEGMENT")) {
	g_iLineType = TYPE_DIR;
	g_iErrorNo ^= ERROR_UNKOP;
	fprintf(g_flog,"Processing SEGMENT directive\n");
	if(0 != strlen(g_szParms)) {
		switch(g_szParms[0]) {
			case 'A':
			case 'a': g_iSegment = SEG_ABS; break;
			case 'C':
			case 'c': g_iSegment = SEG_CODE; break;
			case 'D':
			case 'd': g_iSegment = SEG_DATA; break;
			case 'S':
			case 's': g_iSegment = SEG_STACK; break;
			default:  g_iSegment = SEG_VAGUE; break;
		}
	} else {
		g_iErrorNo |= ERROR_NOPARM;
	}
}
