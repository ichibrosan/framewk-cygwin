// $Log: bin2com.cpp,v $
// Revision 1.1  2011/04/14 15:13:09  doug
// Initial revision
//
//

// ---------------------------------------------------
// bin2com.cpp  11-Apr-11   Running on Mac OS X 10.6.6
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

static char szBin2comCpp[] = "$Id: bin2com.cpp,v 1.1 2011/04/14 15:13:09 doug Exp $";

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
	unsigned char buffer[0xff00+1];
	char szCmd[80];

	TRACE("starting main...");
	
	Version(argv[0]);

	if(1 == argc) {
		printf("usage - bin2com <binfilespec> <comfilespec>\n");
	}

	TRACE("opening output file for writing");
	FILE * fbin = fopen(argv[1],"r");
	if(NULL == fbin) {
		printf("Sorry, unable to open %s for input\n",argv[1]);
		exit(EXIT_FAILURE);
	}
		
	FILE * fcom = fopen(argv[2],"w");
	if(NULL == fcom) {
		printf("Sorry, unableto open %s for output\n",argv[2]);
		fclose(fbin);
		exit(EXIT_FAILURE);
	}
	
	unsigned int uiBytes = fread(buffer,1,0x100,fbin);
	if(0x100 != uiBytes) {
		printf("Sorry, unable to read binary prefix\n");
		exit(EXIT_FAILURE);
	}
	
	uiBytes = fread(buffer,1,0xff00,fbin);
	if(0 == uiBytes) {
		printf("Sorry, unable to read remainder of program\n");
		exit(EXIT_FAILURE);
	}

	unsigned int uiBytes2 = fwrite(buffer,1,uiBytes,fcom);
	if(uiBytes != uiBytes2) {
		printf("Sorry, problem writing .COM file\n");
		fclose(fbin);
		fclose(fcom);
		sprintf(szCmd,"rm -f %s\n",argv[2]);
		system(szCmd);
		exit(EXIT_FAILURE);
	}

	fclose(fbin);
	fclose(fcom);
	printf("%s written successfully\n",argv[2]);
}

