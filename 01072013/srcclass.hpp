// ---------------------------------------------------
// srcclass.hpp 21-Feb-11   Running on Mac OS X 10.6.6
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
#ifdef SRCCLASS

static char szSrcclassHpp[] = "$Id: srcclass.hpp,v 1.1 2011/03/24 11:58:05 doug Exp $";

#define SRC_DEPTH 10

class CSource {
	char *m_p;
	char m_buffer[255];
	FILE * m_fd[SRC_DEPTH];
	int m_index;
	int m_iLine[SRC_DEPTH];
public:
	CSource();
	char * srcgets(void);
	int    srcopen(char *); 
	int    srcgetlevel(void);
	int    srcgetlineno(void);
};

CSource::CSource()
{
	m_index = 0;
}

int CSource::srcgetlineno(void)
{
	return(m_iLine[m_index-1]);
}

int CSource::srcopen(char * szFileName)
{
	if(SRC_DEPTH > m_index) {
		m_fd[m_index] = fopen(szFileName,"r");
		if(NULL == m_fd[m_index]) {
			return EXIT_FAILURE;
		} else {
			m_iLine[m_index] = 0;
			m_index++;
			return EXIT_SUCCESS;
		}
	} else {
		return EXIT_FAILURE;
	}
}

char * CSource::srcgets(void)
{
	while(0 != m_index) {
		m_p = fgets(m_buffer,sizeof(m_buffer),m_fd[m_index-1]);
		if(NULL != m_p) {
			m_iLine[m_index-1]++;
			return(m_p);
		} else {
			fclose(m_fd[m_index-1]);
			m_index--;
		}
	}
	return NULL;
}

int CSource::srcgetlevel(void)
{
	return m_index;
}

#endif

////////////////////////
// eof - srcclass.hpp //
////////////////////////
