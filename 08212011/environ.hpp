// ---------------------------------------------------
// environ.hpp  21-Feb-11   Running on Mac OS X 10.6.6
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

static char szEnvironHpp[] = "$Id: environ.hpp,v 1.1 2011/03/24 11:58:05 doug Exp $";

class CEnvironment {
	char m_szBashVersion[80];
	char m_szCommandMode[80];
	char m_szHostname[80];
	char m_szMachtype[64];
	char m_szOstype[128];
	char m_szPwd[255];
	char m_szTerm[255];
	char m_szTermProgram[255];
	char m_szTermProgramVersion[255];
	char m_szTmpdir[255];
	char m_szToken[255];
	char m_szUid[16];
	char m_szUser[32];
	int m_iLines;
	void grab(char *);
public:
	CEnvironment();
	char * getbashversion(void);
	char * getcommandmode(void);
	char * gethostname(void);
	char * getmachtype(void);
	char * getostype(void);
	char * getpwd(void);
	char * gettermprogram(void);
	char * gettermprogramversion(void);
	char * gettmpdir(void);
	char * getterm(void);
	char * getuid(void);
	char * getuser(void);
};

CEnvironment::CEnvironment()
{
	char g_szBuffer2[80];

	grab("BASH_VERSION");         strcpy(m_szBashVersion,       m_szToken);
	grab("COMMAND_MODE");	      strcpy(m_szCommandMode,       m_szToken);
	grab("HOSTNAME");             strcpy(m_szHostname,          m_szToken);
	grab("MACHTYPE");             strcpy(m_szMachtype,          m_szToken);
	grab("OSTYPE");               strcpy(m_szOstype,            m_szToken);
	grab("PWD");                  strcpy(m_szPwd,               m_szToken);
	grab("UID");                  strcpy(m_szUid,               m_szToken);
	grab("USER");                 strcpy(m_szUser,              m_szToken);
	grab("TERM");	              strcpy(m_szTerm,              m_szToken);
	grab("TERM_PROGRAM");         strcpy(m_szTermProgram,       m_szToken);
	grab("TERM_PROGRAM_VERSION"); strcpy(m_szTermProgramVersion,m_szToken);
	grab("TMPDIR");               strcpy(m_szTmpdir,            m_szToken);
}

char * CEnvironment::getbashversion(void)
{
	return(m_szBashVersion);
}

char * CEnvironment::getcommandmode(void)
{
	return(m_szCommandMode);
}


char * CEnvironment::gethostname(void)
{
	return(m_szHostname);
}

char * CEnvironment::getmachtype(void)
{
	return(m_szMachtype);
}

char * CEnvironment::getostype(void)
{
	return(m_szOstype);
}

char * CEnvironment::getpwd(void)
{
	return(m_szPwd);
}

char * CEnvironment::gettermprogram(void)
{
	return(m_szTermProgram);
}

char * CEnvironment::gettermprogramversion(void)
{
	return(m_szTermProgramVersion);
}

char * CEnvironment::gettmpdir(void)
{
	return(m_szTmpdir);
}

char * CEnvironment::getterm(void)
{
	return(m_szTerm);
}


char * CEnvironment::getuid(void)
{
	return(m_szUid);
}

char * CEnvironment::getuser(void)
{
	return(m_szUser);
}

void CEnvironment::grab(char *what)
{
	char g_szBuffer2[80];
	char szCommand[80];
	char szFilename[128];

	sprintf(szCommand,"echo $%s >%s.env",what,what);
        system(szCommand);
	sprintf(szFilename,"%s.env",what);
        FILE * fd = fopen(szFilename,"r");
        assert(fd);
        fgets(g_szBuffer2,sizeof(g_szBuffer2),fd);
        fclose(fd);
        g_szBuffer2[strlen(g_szBuffer2)-1] = 0;
	sprintf(szCommand,"rm -f %s",szFilename);
        system(szCommand);
	strcpy(m_szToken,g_szBuffer2);
//	printf("%s was %s\n",what,g_szBuffer2);
}

///////////////////////
// eof - environ.hpp //
///////////////////////

