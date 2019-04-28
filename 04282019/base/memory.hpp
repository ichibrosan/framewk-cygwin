// ---------------------------------------------------
// memory.hpp   21-Feb-11   Running on Mac OS X 10.6.6
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
// 2/4/2011 dwg - cloned from Borland vesion in preparation
// for porting to native Mac OS (on Intel) use.

static char szMemoryHpp[] = "$Id: memory.hpp,v 1.1 2011/03/24 11:58:05 doug Exp $";

#ifdef MEMORY

#define MEMSIZE 16384

class CMemory {
	unsigned char m_memory[MEMSIZE];
	int m_memsize;
	char m_szFilename[128];

public:
	CMemory(int);
	CMemory(int,char *);
	unsigned char peekb(int);
	unsigned int  peekw(int);
	void pokeb(int,unsigned char);
	void pokew(int,unsigned int);	
	~CMemory();
};

CMemory::CMemory(int memsize)
{
	TRACE("starting CMemory::CMemory...");
	m_memsize = memsize;
	strcpy(m_szFilename,"memory.bin");

	FILE * fd = fopen(m_szFilename,"r");
	if(NULL == fd) {
		fd = fopen(m_szFilename,"w");
		memset(m_memory,0,memsize);
		fwrite(m_memory,memsize,1,fd);
		fclose(fd);
		fd = fopen(m_szFilename,"r");
	}
	fread(m_memory,memsize,1,fd);
	fclose(fd);
	TRACE("...ending CMemory::CMemory");
}

CMemory::CMemory(int memsize,char *filename)
{
        TRACE("starting CMemory::CMemory...");
        m_memsize = memsize;
	strcpy(m_szFilename,filename);

        FILE * fd = fopen(filename,"r");
        if(NULL == fd) {
                fd = fopen(filename,"w");
                memset(m_memory,0,memsize);
                fwrite(m_memory,memsize,1,fd);
                fclose(fd);
                fd = fopen(filename,"r");
        }
        fread(m_memory,memsize,1,fd);
        fclose(fd);
        TRACE("...ending CMemory::CMemory");
}


unsigned char CMemory::peekb(int offset)
{
	TRACE("starting CMemory::peekb...");
	
	TRACE("...ending CMemory::peekb");
	
	return m_memory[offset];
}

unsigned int CMemory::peekw(int offset)
{
	TRACE("starting CMemory::peekw...");
	
	TRACE("...ending CMemory::peekw");

	return m_memory[offset] + (m_memory[offset+1]<<8) ;
}

void CMemory::pokeb(int offset,unsigned char data)
{
	TRACE("starting CMemory::pokeb...");
	
	TRACE("...ending CMemory::pokeb");

//	printf("CMemory::pokeb(%04X,%02X);\n",offset,data);
	m_memory[offset] = data;
}

void CMemory::pokew(int offset,unsigned int data)
{
	TRACE("starting CMemory::pokew...");
	
	m_memory[offset]   = data & 0xff;
	m_memory[offset+1] = data >> 8;

	TRACE("...ending CMemory::pokew");
}

CMemory::~CMemory()
{
	TRACE("starting CMemory::~CMemory...");
	
	FILE * fd = fopen(m_szFilename,"w");
	fwrite(m_memory,MEMSIZE,1,fd);
	fclose(fd);

	TRACE("...ending CMemory::~CMemory");
}

#endif

