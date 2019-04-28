// ---------------------------------------------------
// versbind.hpp  6-Mar-11   Running on Mac OS X 10.6.6
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

static char szVersbindHpp[] = "$Id: versbind.hpp,v 1.1 2011/03/24 11:58:05 doug Exp $";


// The purpose of this include file and the class 
// defined within is to allow a program as simple
// as the example above to display a standard banner
// and also other behaviors such as config files.


class CVersion {
	char m_szDebug[DEFAULT_STRSIZE];
	char m_szTrace[DEFAULT_STRSIZE];
	char m_szWarn[DEFAULT_STRSIZE];
	char m_szMachtype[DEFAULT_STRSIZE];
	char m_szOstype[DEFAULT_STRSIZE];
	char m_szPwd[DEFAULT_STRSIZE];
	char m_szSyncro[DEFAULT_STRSIZE];
	char m_szUid[DEFAULT_STRSIZE];
	char m_szUser[DEFAULT_STRSIZE];
public:
	CVersion(char *);
	char * getdebug(void);
	char * gettrace(void);
	char * getwarn(void);
	char * getmachtype(void);
	char * getostype(void);
	char * getpwd(void);
	char * getsyncro(void);
	char * getuid(void);
	char * getuser(void);
};

CVersion::CVersion(char *prog)  
{
	TRACE("CVersion::CVersion() starting");

	char szValue[DEFAULT_STRSIZE];
	char szTemp[DEFAULT_STRSIZE];
	char szTemp2[DEFAULT_STRSIZE];
	char szCommand[DEFAULT_STRSIZE];

	g_bTrace = DEFAULT_TRACE;
	g_bWarn  = DEFAULT_WARN;

	sprintf(szCommand,"rm -f %s.ini",prog);
	strcpy(m_szSyncro,DEFAULT_SERIAL);

	CEnvironment * env = new CEnvironment();
	strcpy(m_szMachtype,env->getmachtype());
	strcpy(m_szOstype,  env->getostype());
	strcpy(m_szPwd,     env->getpwd());
	strcpy(m_szUid,     env->getuid());
	strcpy(m_szUser,    env->getuser());

	ini_read(prog,"Options","Debug");
	if(0 == strlen(g_szIniValue)) {
		strcpy(g_szIniValue,"False");
	}
	strcpy(m_szDebug,g_szIniValue);
	if(0 == strcmp(strupr("TRUE"),m_szDebug)) {
		g_bDebug = TRUE;
	} else {
		g_bDebug = FALSE;
	}

        ini_read(prog,"Options","Trace");
        if(0 == strlen(g_szIniValue)) {
                strcpy(g_szIniValue,"False");
        }
        strcpy(m_szTrace,g_szIniValue);
        if(0 == strcmp(strupr("TRUE"),m_szTrace)) {
                g_bTrace = TRUE;
        } else {
                g_bTrace = FALSE;
        }

        ini_read(prog,"Options","Warn");
        if(0 == strlen(g_szIniValue)) {
                strcpy(g_szIniValue,"False");
        }
        strcpy(m_szWarn,g_szIniValue);
        if(0 == strcmp(strupr("TRUE"),m_szWarn)) {
                g_bWarn = TRUE;
        } else {
                g_bWarn = FALSE;
        }

	ini_read(prog,"Options","Banner");
        if(0 == strlen(g_szIniValue)) {
                strcpy(g_szIniValue,"Full");
        }
	if(0 == strcmp("Full",g_szIniValue)) {
		strcpy(szTemp,prog);

		// remove ./ or ../ on the from of the program
		if('.' == szTemp[0] | '/' == szTemp[0]) {
			strcpy(szTemp2,&szTemp[1]);
			strcpy(szTemp,szTemp2);
		}
                if('.' == szTemp[0] | '/' == szTemp[0]) {
                        strcpy(szTemp2,&szTemp[1]);
                        strcpy(szTemp,szTemp2);
                }
                if('.' == szTemp[0] | '/' == szTemp[0]) {
                        strcpy(szTemp2,&szTemp[1]);
                        strcpy(szTemp,szTemp2);
                }

		// assure name is 8 chars for banner alignment
		while(8 > strlen(szTemp)) {
			strcat(szTemp," ");
		}

		printf("------------------------------------------------\n");
                printf("%s  Ver %2d.%02d.%02d%c  %s\n",
                        szTemp,RMJ,RMN,RUP,'a'+RTP,m_szMachtype);
		printf("Serial 20%2d-%04d-%s  Licensed under GNU GPL.\n",
			RMJ,atoi(m_szUid),m_szSyncro);
		printf("Copyright (c)20%2d Douglas Goodall, United States\n",
			RMJ);
		printf("------------------------------------------------\n");
	}		
}

char * CVersion::getdebug(void)
{
	return m_szDebug;
}

char * CVersion::gettrace(void)
{
        return m_szTrace;
}

char * CVersion::getwarn(void)
{
        return m_szWarn;
}




char * CVersion::getmachtype(void)
{
	return m_szMachtype;
}

char * CVersion::getostype(void)
{
	return m_szOstype;
}

char * CVersion::getpwd(void)
{
	return m_szPwd;
}

char * CVersion::getsyncro(void)
{
	return m_szSyncro;
}

char * CVersion::getuid(void)
{
	return m_szUid;
}

char * CVersion::getuser(void)
{
	return m_szUser;
}

// This define allows the most simple 
// invocation of the version support
// and output of the banner if the ini
// file so indicates...
#define Version(x) CVersion version(x)
 
// eof - versbind.hpp

