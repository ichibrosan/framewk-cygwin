// $Log: asresolv.hpp,v $
// Revision 1.3  2011/04/14 15:13:09  doug
// get ready for release to wiki and server
//
//

// ---------------------------------------------------
// asresolv.hpp  2-Mar-11   Running on Mac OS X 10.6.6
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

static char szAsresolvHpp[] = "$Id: asresolv.hpp,v 1.3 2011/04/14 15:13:09 doug Exp $";


//---------------------------------------------------

unsigned char X8(char *p)
{
      TRACE("X8() started");
	  char szTemp[255];
        unsigned char ucValue;

        strcpy(szTemp,p);
        strcat(szTemp," ");
        g_pCEval->clear();
        g_pCEval->tokenize(szTemp);
        g_pCEval->dump();
        g_pCEval->gather(szTemp);
        g_pCPostfix->convert(szTemp);
        strcpy(szTemp,g_pCPostfix->getresult());
        ucValue = (unsigned char)g_pCEval->evaluate(szTemp);
//printf("DEBUG: X8 returning 0x%02X\n",ucValue);
        return( ucValue );
}

unsigned int resolvep8(char *p)
{
        unsigned int ucValue;
	int iValue;
        int     rc;
	char szLocal[32];

//printf("DEBUG: resolvep8 was passed %s\n",p);

        if(TRUE == g_pCEval->bExpression(p)) {
                return(X8(p));
        }

        if(0 == strncmp("@",p,1)) {
                return g_iPc;
        }

        // handle literal character 'C'
        char szTick[] = "'";
        if( (szTick[0] == g_szParms[0]) &&
            (szTick[0] == g_szParms[2]) ) {
//printf("DEBUG: resolve8p() says tick detected, g_szParms are %s\n",g_szParms);
		strcpy(szLocal,p);
                ucValue = szLocal[1];
//printf("DEBUG: resolvep8 tick handler returning 0x%02X\n",ucValue);
                return ucValue;
        }

        if(p[0] == '$') p[0] = '0';
        if( (p[0] > 0x2f) && (p[0] < 0x3a) ) {
                sscanf(p,g_szRadixFormat8,&iValue);
		ucValue = (unsigned char) iValue;
                return ucValue;
        } 

        ucValue = g_pCSymbols->getu8(p,&rc);
        if(EXIT_FAILURE == rc) {
		if(EXIT_SUCCESS == g_pCSymbols->gete8(p,&rc)) {
			g_iWarningNo |= WARNING_EXTERNAL;
			ucValue = 0;
		} else {
        		g_iErrorNo |= ERROR_UNKSYM;
		}
        }

	return ucValue;
}

//---------------------------------------------------

unsigned int X16(char *p)
{
	TRACE("X16() started");
	fprintf(g_flog,"X16() called\n");

	char szTemp[255];
	unsigned long long result;

	strcpy(szTemp,p);
	strcat(szTemp," ");
	g_pCEval->clear();
	g_pCEval->tokenize(szTemp);
	g_pCEval->dump();
	g_pCEval->gather(szTemp);
	g_pCPostfix->convert(szTemp);
	strcpy(szTemp,g_pCPostfix->getresult());
	result = g_pCEval->evaluate(szTemp);

	sprintf(szTemp,"X16(%s) returned 0x%04X (%d)\n",p,result,result);
	fprintf(g_flog,"%s",szTemp);

	return( (unsigned int)result );
}

unsigned int resolvep16(char *p)
{
        unsigned int uiValue;
        int     rc;

        if(TRUE == g_pCEval->bExpression(p)) {
                return(X16(p));
        }

        if(0 == strncmp("@",p,1)) {
                return g_iPc;
        }

        if(p[0] == '$') p[0] = '0';
        if( (p[0] > 0x2f) && (p[0] < 0x3a) ) {
                sscanf(p,g_szRadixFormat16,&uiValue);
                return uiValue;
        }

        uiValue = g_pCSymbols->getu16(p,&rc);
        if(EXIT_FAILURE == rc) {
        	g_iErrorNo |= ERROR_UNKSYM;
        }

	return uiValue;
}

//---------------------------------------------------

unsigned char X32(char *p)
{
	TRACE("X32() started");

        char szTemp[255];
        unsigned long ulValue;

        strcpy(szTemp,p);
        strcat(szTemp," ");
        g_pCEval->clear();
        g_pCEval->tokenize(szTemp);
        g_pCEval->dump();
        g_pCEval->gather(szTemp);
        g_pCPostfix->convert(szTemp);
        strcpy(szTemp,g_pCPostfix->getresult());
        ulValue = (unsigned long)g_pCEval->evaluate(szTemp);
        return( ulValue );
}

unsigned long resolvep32(char *p)
{
        unsigned long ulValue;
        int     rc;

        if(TRUE == g_pCEval->bExpression(p)) {
                return(X32(p));
        }

        if(0 == strncmp("@",p,1)) {
                return g_iPc;
        }

        if(p[0] == '$') p[0] = '0';
        if( (p[0] > 0x2f) && (p[0] < 0x3a) ) {
                sscanf(p,g_szRadixFormat32,&ulValue);
                return ulValue;
        }

        ulValue =  g_pCSymbols->getu32(p,&rc);
        if(EXIT_FAILURE == rc) {
		printf("resolvep32(%s) detected error ",p);
        	g_iErrorNo |= ERROR_UNKSYM;
        }

	return ulValue;
}

//---------------------------------------------------

unsigned long long X64(char *p)
{
        char szTemp[255];
	char szTemp2[255];
        strcpy(szTemp,p);
        strcat(szTemp," ");
        g_pCEval->clear();
        g_pCEval->tokenize(szTemp);
        g_pCEval->dump();
        g_pCEval->gather(szTemp);
        g_pCPostfix->convert(szTemp);
        strcpy(szTemp,g_pCPostfix->getresult());
        unsigned long long ullValue = (unsigned long long)g_pCEval->evaluate(szTemp);
	return( ullValue );
}

unsigned long long resolvep64(char *p)
{
	int rc;
	unsigned long long ullValue;

        if(TRUE == g_pCEval->bExpression(p)) {
                return(X64(p));
        }

        if(0 == strncmp("@",p,1)) {
                return (unsigned long long)g_iPc;
        }

        if(p[0] == '$') p[0] = '0';
        if( (p[0] > 0x2f) && (p[0] < 0x3a) ) {
                sscanf(p,g_szRadixFormat64,&ullValue);
                return ullValue;
        }

        ullValue = g_pCSymbols->getu64(p,&rc);
        if(EXIT_FAILURE == rc) {
        	g_iErrorNo |= ERROR_UNKSYM;
        }

	return ullValue;
}

////////////////////////
// eof - asresolv.hpp //
////////////////////////
