// $Log: _disp.hpp,v $
// Revision 1.4  2011/03/25 21:47:31  doug
// *** empty log message ***
//
// Revision 1.3  2011/03/25 07:30:04  doug
// *** empty log message ***
//

// Copyright(c)2011 Douglas W. Goodall, United States.

// 3/8/2011 dwg - set range error in global status

	g_uiTarget = resolvep16(psz);
	if(g_uiTarget < g_iPc) {
		if( (g_iPc-g_uiTarget) > 126) {
			g_iErrorNo |= ERROR_RANGE;
			g_ucBytes[g_iBytesIndex++] = 0xE5;
		} else {
			// emit backward displacement
			g_ucBytes[g_iBytesIndex++] =
				256-(g_iPc-g_uiTarget-1);
		}
	}
	if(g_uiTarget > g_iPc) {
		if( (g_uiTarget-g_iPc) > 126) {
			g_iErrorNo |= ERROR_RANGE;
			g_ucBytes[g_iBytesIndex++] = 0xE5;
		} else {
			// emit forward displacement
			g_ucBytes[g_iBytesIndex++] = g_uiTarget-g_iPc-2;
		}		
	}

