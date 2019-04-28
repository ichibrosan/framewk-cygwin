// $Log: asoutwrn.hpp,v $
// Revision 1.2  2011/04/14 15:13:09  doug
// get ready for release to wiki and server
//
//

// ---------------------------------------------------
// asoutwrn.hpp 12-Mar-11   Running on Mac OS X 10.6.6
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

static char szAsoutwrnHpp[] = "$Id: asoutwrn.hpp,v 1.2 2011/04/14 15:13:09 doug Exp $";

void asoutwrn(void)
{

  if(0 != (WARNING_DIV0 & g_iWarningNo)) {
        sprintf(g_szBuffer2,"%04X: Warning: Divide by Zero %s%s",g_iPc,g_szSep,g_szOpcode);
        print(g_flst);
        printf("%04X: Warning: Divide by Zero %s%s%s%s%s%s%s\n",
                g_iPc,g_szLabel,g_szSep,g_szOpcode,
		g_szSep,g_szParms,g_szSep,g_szComments);
//      g_iErrors++;
	g_iWarnings++;
  }

  if(0 != (WARNING_EXTERNAL & g_iWarningNo)) {
        sprintf(g_szBuffer2,"%04X: Warning: Unresolved External %s%s%s%s",g_iPc,g_szSep,g_szOpcode,g_szSep,g_szParms);
        print(g_flst);
        printf("%04X: Warning: Unresolved External %s%s%s%s%s%s%s\n",
                g_iPc,g_szLabel,g_szSep,g_szOpcode,
                g_szSep,g_szParms,g_szSep,g_szComments);
//      g_iErrors++;
	g_iWarnings++;
  }




//}

}

// eof - emiterr.hpp
