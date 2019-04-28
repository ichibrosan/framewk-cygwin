// $Log: shex.cpp,v $
// Revision 1.3  2011/04/14 15:13:09  doug
// get ready for release to wiki and server
//
//

// ---------------------------------------------------
// shex.cpp     21-Feb-11   Running on Mac OS X 10.6.6
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
// 2/4/2011 dwg - cloned from Borland version

static char szShexCpp[] = "$Id: shex.cpp,v 1.3 2011/04/14 15:13:09 doug Exp $";

#include "asdefs.hpp"
#define DWGALLOC
#define INIBIND
#define MEMORY
#include "includes.hpp"


// to create 2's compliment, flip all bits and add 1
// (xor with FF ) + 1 does that

// : <length> <addr> <type> <data> <checksum>

#define DATA_RECORD 0x00
#define EOF_RECORD  0x01

int main(int argc,char **argv)
{
	TRACE("starting main...");
	
	Version(argv[0]);

	if(1 == argc) {
		printf("usage - shex <filespec>\n");
	}

	CAlloc * pAlloc = new CAlloc();
	if(NULL == pAlloc) {
		printf("pAlloc is NULL\n");
	}

	CMemory * pMem = new CMemory(MEMSIZE);

	TRACE("opening output file for writing");
	FILE * fhex = fopen(argv[1],"w");		
	
	for(int o=0;o<MEMSIZE;o+=16) {
		int check = 0;
		for(int i=0;i<16;i++) {
			check += pMem->peekb(o+i);
		}
		if(0 != check) {
			unsigned char checksum = 0;
			fprintf(fhex,":");
			if(g_bDebug) fprintf(fhex," ");
			fprintf(fhex,"%02X",16);
			if(g_bDebug) fprintf(fhex," ");
			fprintf(fhex,"%04X",o);
			if(g_bDebug) fprintf(fhex," ");
			fprintf(fhex,"%02X",DATA_RECORD);
			if(g_bDebug) fprintf(fhex," ");
			for(int index=0;index<16;index++) {
				fprintf(fhex,"%02X",pMem->peekb(index+o));
//				printf("%02X",pMem->peekb(index+o));
				checksum += pMem->peekb(index+o);
			}
//			printf("\n");
			if(g_bDebug) fprintf(fhex," ");
			fprintf(fhex,"%02X",(unsigned char)((checksum^0xff)+1)&0xff);
			fprintf(fhex,"\n");
		}
	}

	fclose(fhex);

	delete pMem;
		

	TRACE("...ending main");
}
