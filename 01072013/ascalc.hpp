// ---------------------------------------------------
// ascalc.hpp   10-Mar-11   Running on Mac OS X 10.6.6
// S/n 2011-1042-654321  Written by Douglas W. Goodall
// Copyright(c)2011 Douglas W. Goodall, United States.
// ---------------------------------------------------
// This file is part of Vintage Modern Assembler Plus Tools.
// VMAPT is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// VMAPT is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with VMAPT.  If not, see <http://www.gnu.org/licenses/>.


#ifdef CALC

static char szAscalcHpp[] = "$Id: ascalc.hpp,v 1.1 2011/03/24 11:58:05 doug Exp $";

// minimal parser for simpletwo term expression
void calc(char * p,char *t1,char *op,char *t2)
{
        char szDelim[]  = "+-*/&|";
        char g_szBuffer2[128];
	char szOp[128];
	char szTerm1[128];

	strcpy(szTerm1,p);
        strcpy(g_szBuffer2,p);
        char * pDelim = strpbrk(g_szBuffer2,szDelim);
	char * pBuffer = g_szBuffer2;
	unsigned long diff = pDelim - pBuffer;
	int iDiff = (int)diff;
        szTerm1[iDiff] = 0;
	strcpy(t1,szTerm1);
	strcpy(szOp,&g_szBuffer2[iDiff]);
	szOp[1] = 0;
        strcpy(op,szOp);
	strcpy(t2,&g_szBuffer2[iDiff+1]);
}

#endif

//////////////////////
// eof - ascalc.cpp //
//////////////////////

