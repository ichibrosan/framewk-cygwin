// $Log: asomfgen.hpp,v $
// Revision 1.1  2011/04/14 15:13:09  doug
// Initial revision
//
//

// ---------------------------------------------------
// asomfgen.hpp  5-Apr-11   Running on Mac OS X 10.6.6
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

class COmfGen {
	char m_szFileName[DEFAULT_STRSIZE];
	char m_szModuleName[DEFAULT_STRSIZE];
	FILE * m_fd;
public:
	COmfGen(char *);
	void GenMHR(void);
	void genpubs(void);
	void GenMER(void);
	~COmfGen();

};

COmfGen::COmfGen(char *szModuleName)
{
	strcpy(m_szModuleName,szModuleName);
	strcpy(m_szFileName,m_szModuleName);
	strcat(m_szFileName,".obj");
	m_fd = fopen(m_szFileName,"w");
	GenMHR();
}

void COmfGen::GenMHR(void)
{
	fprintf(m_fd,"<RECTYP=0x02><RECLEN=0x00><MODNAME=%s><TRNID><CHKSUM=0x00>",m_szModuleName);
}

void COmfGen::genpubs(void)
{
}

void COmfGen::GenMER(void)
{
	fprintf(m_fd,"<RECTYP==0x04><RECLEN=><MODNAME=%s><REGMSK><CHKSUM=0x00>",
		m_szModuleName);
}

COmfGen::~COmfGen()
{
	GenMER();
	if(NULL != m_fd) fclose(m_fd);
}

////////////////////////
// eof - asomfgen.hpp //
////////////////////////

