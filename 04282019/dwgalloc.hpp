// ---------------------------------------------------
// dwgalloc.hpp 21-Feb-11   Running on Mac OS X 10.6.6
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

static char szDwgallocHpp[] = "$Id: dwgalloc.hpp,v 1.1 2011/03/24 11:58:05 doug Exp $";

// 2011/02/01 dwg - cleaned up logging code. All logging
// activity now dependent on bDebug being TRUE at runtime.
// This is of course dependent on the ini file's Option:Debug
// value.

#ifdef DWGALLOC

#define MAX_CHUNKS 32
#define ALLOC_OK   TRUE
#define ALLOC_NONE FALSE

class CAlloc {
	struct {
		char note[32];
		char file[128];
		int line;
		long size;
		int state;
		void * p;
	} m_chunk[MAX_CHUNKS];
	FILE *m_fp;
	int m_chunks;
public:
	CAlloc();
	~CAlloc();
	void dump(void);
	void * alloc(char *,int,long,char *);
	void myfree(void *);
};

CAlloc::CAlloc()
{
	
	if(TRUE == g_bDebug) {
		printf("CAlloc::CAlloc(); starting\n");
	}
	
	m_chunks = 0;

	if(TRUE == g_bDebug) {
		m_fp = fopen("dwgalloc.log","w");
	}
	
	for(int index=0;index<MAX_CHUNKS;index++) {
		m_chunk[index].size = 0L;
		m_chunk[index].line = 0;
		m_chunk[index].state = ALLOC_NONE;
	}
	
	if(TRUE == g_bDebug) printf("CAlloc::CAlloc(); ending\n");
}

void CAlloc::dump(void) 
{
	
	printf("struct {\n");
	for(int index=0;index<m_chunks;index++) {
		printf("  m_chunk[%d]={",index);
		printf( " file=%s"
			" line=%d"
			" size=%ld"
			" state=%X"
			" ptr->%08lX"
			" %s"
			" }\n",
			m_chunk[index].file,
			m_chunk[index].line,
			m_chunk[index].size,
			m_chunk[index].state,
			m_chunk[index].p,
			m_chunk[index].note);
	}
	printf("} m_chunk[%d];\n",MAX_CHUNKS);

}


void * CAlloc::alloc(char * file,int line,long size,char *note)
{
	
	assert(MAX_CHUNKS > m_chunks);
	
	if(MAX_CHUNKS == m_chunks) {
		return NULL;
	}

	int chunk = m_chunks++;

	strcpy(m_chunk[chunk].file,file);
	strcpy(m_chunk[chunk].note,note);
	m_chunk[chunk].line = line;
	m_chunk[chunk].size = size;
	m_chunk[chunk].p = malloc(size);

	if(NULL != m_chunk[chunk].p) {

		m_chunk[chunk].state = ALLOC_OK;

		if(TRUE == g_bDebug) {
			fprintf(m_fp,
				"CAlloc::alloc("
				"file=%s,"
				"line=%d"
				",size=%ldL,"
				"p = %08lX,"
				"%s ) alloc ok\n",
				file,
				line,
				size,
				m_chunk[chunk].p,
				note);
			}
	} 

	if(TRUE == g_bDebug) {
		printf("CAlloc::alloc(file=%s,line=%d,size=%lX); returning %08lX\n",
			file,line,size,m_chunk[chunk].p);
	}
	
	
	return m_chunk[chunk].p;			
}

void CAlloc::myfree(void *chunk)
{

	char szFunc[32];
	
	strcpy(szFunc,"Checking ");

	if(TRUE == g_bDebug) printf("CAlloc::free(%08lX) starting;  ",chunk);

	fprintf(m_fp,"CAlloc::free trying to free %08lX\n",chunk);
	for(int index=0;index<m_chunks;index++) {
		
		if(TRUE == g_bDebug) {
			fprintf(m_fp,
				"CAlloc::myfree() %s ch %d,"
				"%s:"
				"line=%d,"
				"size=%ld,"
				"ptr %08lX\n",
				szFunc,
				index,
				m_chunk[index].file,
				m_chunk[index].line,
				m_chunk[index].size,
				m_chunk[index].p);
		}

		if(chunk == m_chunk[index].p) {
			
			if(TRUE == g_bDebug) { 
				fprintf(m_fp,
					"CAlloc::myfree() found specified chunk %8lX\n",chunk);
			}
			
			free(chunk);
			m_chunk[index].state = ALLOC_NONE;

			strcpy(szFunc,"Ignoring ");
			break;
		}

	}

	if(TRUE == g_bDebug) {
		fprintf(m_fp,"CAlloc::myfree() Done with CAlloc::myfree();\n");
	}
	
}


CAlloc::~CAlloc()
{
	
	if(TRUE == g_bDebug) printf("CAlloc::~CAlloc();     starting   ");

	if(TRUE == g_bDebug) {
		fprintf(m_fp,
			"CAlloc::~CAlloc() Releasing unreleased allocations:\n");
	}
	
	for(int index=0;index<m_chunks;index++) {
		
		if(ALLOC_OK == m_chunk[index].state) {
		
			if(TRUE == g_bDebug) {
				fprintf(m_fp,
					"chunk %d, state %d, file %s, line %d, size %ld\n",
					index,
					m_chunk[index].state,
					m_chunk[index].file,
					m_chunk[index].line,
					m_chunk[index].size);
			}
				
			free(m_chunk[index].p);			
				m_chunk[index].state = ALLOC_NONE;

		}
	}
	
	if(TRUE == g_bDebug) {
		fprintf(m_fp,"CAlloc::~CAlloc(); ending\n");
		fclose(m_fp);
	}
	
	if(TRUE == g_bDebug) printf("CAlloc::~CAlloc();     ending\n");
	
}

// This is a fun function that uses the dwgalloc alloc wrapper
// and returns a pointer to a dynamically allocated string
// containing the requested value from the ini file. The 
// calling function must have previously instanciated a
// CAlloc object and pass the pointer through as the firth
// parameter so the allocation can be charged to the proper
// allocation object.
char * ini_alloc(CAlloc *a,char * prog, char * section, char * key, char *note)
{
	
	char *p;
	
	ini_read(prog,section,key);
	
	p = (char *)a->alloc( __FILE__,
			      __LINE__, 
			      long(strlen(g_szIniValue)+1), 
			      note );
	
	strcpy(p,g_szIniValue);

	return p;
}

#endif

// eof
																																			
