// $Log: asouterr.hpp,v $
// Revision 1.2  2011/04/14 15:13:09  doug
// get ready for release to wiki and server
//
//

// ---------------------------------------------------
// emiterr.hpp  21-Feb-11   Running on Mac OS X 10.6.6
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

static char szAsouterrHpp[] = "$Id: asouterr.hpp,v 1.2 2011/04/14 15:13:09 doug Exp $";

void asouterr(void)
{

  if(0 != (ERROR_NOCPU & g_iErrorNo)) {
    sprintf(g_szBuffer2,"%04X: Invalid Processor",g_iPc);
    print(g_flst);
    printf("%04X: Invalid Processor %s%s%s%s%s%s%s\n",
           g_iPc,g_szLabel,g_szSep,g_szOpcode,g_szSep,g_szParms,g_szSep,g_szComments);
    g_iErrors++;
  }

  if(0 != (ERROR_INVNS & g_iErrorNo)) {
    sprintf(g_szBuffer2,"%04X: Invalid Namespace",g_iPc);
    print(g_flst);
    printf("%04X: Invalid Namespace %s%s%s%s%s%s%s\n",
           g_iPc,g_szLabel,g_szSep,g_szOpcode,g_szSep,g_szParms,g_szSep,g_szComments);
    g_iErrors++;
  }

  if(0 != (ERROR_UNKOP & g_iErrorNo)) {
        sprintf(g_szBuffer2,"%04X: Err Unknown Opcode %s%s",g_iPc,g_szSep,g_szOpcode);
        print(g_flst);
        printf("%04X: Err Unknown Opcode %s%s%s%s%s%s%s\n",
                g_iPc,g_szLabel,g_szSep,g_szOpcode,g_szSep,g_szParms,g_szSep,g_szComments);
        g_iErrors++;
  }

  if(0 != (ERROR_OPERATOR & g_iErrorNo)) {
    sprintf(g_szBuffer2,"%04X: Error Unknown Operator",g_iPc);
    print(g_flst);
    printf("%04X: Error Unknown Operator %s%s%s%s%s%s%s\n",
           g_iPc,g_szLabel,g_szSep,g_szOpcode,g_szSep,g_szParms,g_szSep,g_szComments);
    g_iErrors++;
  }

  if(0 != (ERROR_UNKSYM & g_iErrorNo)) {
    if(TRUE == g_bPass2) {
        sprintf(g_szBuffer2,"%04X: Error Unknown Symbol",g_iPc);
        print(g_flst);
        printf("%04X: Error Unknown Symbol %s%s%s%s%s%s%s\n",
                g_iPc,g_szLabel,g_szSep,g_szOpcode,g_szSep,g_szParms,g_szSep,g_szComments);
        g_iErrors++;
    }
  }

  if(0 != (ERROR_NOPARM & g_iErrorNo)) {
    if(TRUE == g_bPass2) {
        sprintf(g_szBuffer2,"%04X: Error Missing Parameter(s) ",g_iPc);
        print(g_flst);
        printf("%04X: Error Missing Parameter(s) %s%s%s%s%s%s%s\n",
                g_iPc,g_szLabel,g_szSep,g_szOpcode,g_szSep,g_szParms,g_szSep,g_szComments);
        g_iErrors++;
    }
  }

  if(0 != (ERROR_NOREG & g_iErrorNo)) {
    if(TRUE == g_bPass2) {
        sprintf(g_szBuffer2,"%04X: Error Invalid Register",g_iPc);
        print(g_flst);
        printf("%04X: Error Invalid Register %s%s%s%s%s%s%s\n",
                g_iPc,g_szLabel,g_szSep,g_szOpcode,g_szSep,g_szParms,g_szSep,g_szComments);
        g_iErrors++;
    }
  }

  if(0 != (ERROR_NOMODE & g_iErrorNo)) {
    if(TRUE == g_bPass2) {
        sprintf(g_szBuffer2,"%04X: Error Missing Mode",g_iPc);
        print(g_flst);
        printf("%04X: Error Missing Mode %s%s%s%s%s%s%s\n",
                g_iPc,g_szLabel,g_szSep,g_szOpcode,g_szSep,g_szParms,g_szSep,g_szComments);
        g_iErrors++;
    }
  }

  if(0 != (ERROR_NOVEC & g_iErrorNo)) {
    if(TRUE == g_bPass2) {
        sprintf(g_szBuffer2,"%04X: Error Invalid Vector",g_iPc);
        print(g_flst);
        printf("%04X: Error Invalid Vector %s%s%s%s%s%s%s\n",
                g_iPc,g_szLabel,g_szSep,g_szOpcode,g_szSep,g_szParms,g_szSep,g_szComments);
        g_iErrors++;
    }
  }

  if(0 != (ERROR_RANGE & g_iErrorNo)) {
    if(TRUE == g_bPass2) {
        sprintf(g_szBuffer2,"%04X: Range Error",g_iPc);
        print(g_flst);
        printf("%04X: Range Error %s%s%s%s%s%s%s\n",
                g_iPc,g_szLabel,g_szSep,g_szOpcode,g_szSep,g_szParms,g_szSep,g_szComments);
        g_iErrors++;
    }
  }

  if(0 != (ERROR_DIV0 & g_iErrorNo)) {
    if(TRUE == g_bPass2) {
        sprintf(g_szBuffer2,"%04X: Divide by Zero Error",g_iPc);
        print(g_flst);
        printf("%04X: Divide by Zero Error %s%s%s%s%s%s%s\n",
                g_iPc,g_szLabel,g_szSep,g_szOpcode,g_szSep,g_szParms,g_szSep,g_szComments);
        g_iErrors++;
    }
  }

  if(0 != (ERROR_SYMTYPE & g_iErrorNo)) {
    if(TRUE == g_bPass2) {
        sprintf(g_szBuffer2,"%04X: Unknown Symbol Type",g_iPc);
        print(g_flst);
        printf("%04X: Unknown Symbol Type %s%s%s%s%s%s%s\n",
                g_iPc,g_szLabel,g_szSep,g_szOpcode,g_szSep,g_szParms,g_szSep,g_szComments);
        g_iErrors++;
    }
  }

  if(0 != (ERROR_UNK_PUB & g_iErrorNo)) {
    if(TRUE == g_bPass2) {
        sprintf(g_szBuffer2,"%04X: Unknown Public Symbol %s%s",g_iPc,g_szSep,g_szParms);
        print(g_flst);
        printf("%04X: Unknown Public Symbol %s%s%s%s%s%s%s\n",
                g_iPc,g_szLabel,g_szSep,g_szOpcode,g_szSep,g_szParms,g_szSep,g_szComments);
        g_iErrors++;
    }
  }


}

// eof - emiterr.hpp
