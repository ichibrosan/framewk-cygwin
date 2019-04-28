// $Log: mkbindef.cpp,v $
// Revision 1.3  2011/04/14 15:13:09  doug
// get ready for release to wiki and server
//
//

// ---------------------------------------------------
// mkbindef.cpp 21-Feb-11   Running on Mac OS X 10.6.6
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
//#define __TRACE

static char szMkbindefCpp[] = "$Id: mkbindef.cpp,v 1.3 2011/04/14 15:13:09 doug Exp $";

#include "asdefs.hpp"
#define DWGALLOC
#define INIBIND
#include "includes.hpp"

char szBinary[16];

char * dec2bin(int dec)
{
	int working = dec;
	int temp;
	memset(szBinary,0,sizeof(szBinary));

	for(int i=0;i<8;i++) {
		if(working & 1) {
			szBinary[7-i] = '1';			
		} else {
			szBinary[7-i] = '0';
		}	
		temp = working;
		working = temp >> 1;			
	}
	return szBinary;
}


int main(int argc,char **argv)
{
	TRACE("Entering hello.cpp's main routine");
	
	Version(argv[0]);

	FILE * fd = fopen("cbindefs.hpp","w");

	fprintf(fd,"// ---------------------------------------------------\n");
	fprintf(fd,"// cbindefs.hpp   v%2d.%02d.%02d%c   %s\n",
		RMJ,RMN,RUP,'a'+RTP,version.getmachtype());
	fprintf(fd,"// S/n 20%d-%04d-654321    Licensed under the GNU GPL.\n",
		RMJ,atoi(version.getuid()));
	fprintf(fd,"// Copyright(c)20%d Douglas W. Goodall, United States.\n",
		RMJ);
	fprintf(fd,"// ---------------------------------------------------\n");

	fprintf(fd,"// This file is part of Vintage Modern Assembler Plus Tools.\n");
	fprintf(fd,"//\n");
	fprintf(fd,"// VMAPT is free software: you can redistribute it and/or modify\n");
	fprintf(fd,"// it under the terms of the GNU General Public License as published by\n");
	fprintf(fd,"// the Free Software Foundation, either version 3 of the License, or\n");
	fprintf(fd,"// (at your option) any later version.\n");
	fprintf(fd,"//\n");
	fprintf(fd,"// VMAPT is distributed in the hope that it will be useful,\n");
	fprintf(fd,"// but WITHOUT ANY WARRANTY; without even the implied warranty of\n");
	fprintf(fd,"// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n");
	fprintf(fd,"// GNU General Public License for more details.\n");
	fprintf(fd,"//\n");
	fprintf(fd,"// You should have received a copy of the GNU General Public License\n");
	fprintf(fd,"// along with VMAPT.  If not, see <http://www.gnu.org/licenses/>.\n");
	fprintf(fd,"//\n");

	for(int i=0;i<256;i++) {

		fprintf(fd,"#define Ob%s 0x%02X\n",dec2bin(i),i);
	}
	fprintf(fd,"// eof - cbindefs.hpp\n\n");
	
	TRACE("Exiting hello.cpp's main routine");
	
	return EXIT_SUCCESS;
}

