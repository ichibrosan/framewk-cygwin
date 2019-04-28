// $Log: asmultip.hpp,v $
// Revision 1.1  2011/04/03 05:18:25  doug
// Initial revision
//
//


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

// This function returns the number of commas that occur
// in a string that is passed as a parameter. It is most
// likely that a directive handler calls this to discover
// how many parameters are present prior to parsing.

int iCommaCount(char *szParms)
{
	int iCommas = 0;
	for(int i=0;i<strlen(szParms);i++) {
		if(',' == szParms[i]) {
			iCommas++;
		}
	}
	return iCommas;
}

char * pszParmN(char *szString,int iParmNo)
{
	int iEnds[20];
	memset(&iEnds,0,sizeof(iEnds));
	int iStarts[20];
	memset(&iStarts,0,sizeof(iStarts));
	char szLocal[DEFAULT_STRSIZE];
	strcpy(szLocal,szString);  
	int iNumber = 0;
	iStarts[iNumber] = 0; 
	for(int i=0;i<strlen(szLocal);i++) {
		if(',' == szLocal[i]) {
			iEnds[iNumber++] = i;
                	iStarts[iNumber] = i+1;
		} 
	}
//	for(int j=0;j<iNumber+1;j++) {
//		printf("start %2d end %2d\n",iStarts[j],iEnds[j]);
//	}
//	printf("DEBUG: szLocal is %s\n",szLocal);
	szLocal[iEnds[iParmNo]] = 0;
	strcpy(g_szTemp,&szLocal[iStarts[iParmNo]]);
	return g_szTemp;
}

////////////////////////
// eof - asexperi.hpp //
////////////////////////
