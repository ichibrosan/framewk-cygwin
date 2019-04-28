// $Log: dump.cpp,v $
// Revision 1.3  2011/04/14 15:13:09  doug
// get ready for release to wiki and server
//
//

// ---------------------------------------------------
// dump.cpp     21-Feb-11   Running on Mac OS X 10.6.6
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

static char szDumpCpp[] = "$Id: dump.cpp,v 1.3 2011/04/14 15:13:09 doug Exp $";

#include "asdefs.hpp"
#define INIBIND
#include "includes.hpp"

int main(int argc,char **argv)
{
	Version(argv[0]);

	unsigned char buffer[16];
	FILE *fp;
	int i;
	int j;
	int offset;
	int readcount;

	if(2 != argc) {
		printf("usage - dump <filespec>\n");
		exit(EXIT_FAILURE);
	}

	fp = fopen(argv[1],"rb");
	if(NULL == fp) {
		printf("Sorry, cannot open %s for input",argv[1]);
		exit(EXIT_FAILURE);
	}

	printf("\nFile:   %s\n",argv[1]);

	printf("\n");
	printf("        00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
	printf("   0123456789ABCDEF\n");
	printf("       ------------------------------------------------");
	printf("--------------------\n");
	offset = 0;
	readcount = fread(buffer,1,sizeof(buffer),fp);
	while(0 < readcount) {
		printf("%04X: | ",offset);
		for(i=0;i<readcount;i++) {
			printf("%02X ",buffer[i]);
		}
		if(sizeof(buffer) > readcount) {
			for(j=0;j<sizeof(buffer)-readcount;j++) {
				printf("   ");
			}
		}
		printf("| ");
		for(i=0;i<readcount;i++) {
			if(buffer[i] <  32 || buffer[i] > 126) {
				printf(".");
			} else {
				printf("%c",buffer[i]);
			}
		}

		if(sizeof(buffer) > readcount) {
			for(j=0;j<sizeof(buffer)-readcount;j++) {
				printf(" ");
			}
		}
		printf(" | \n");
		readcount = fread(buffer,1,sizeof(buffer),fp);
		offset += sizeof(buffer);
	}
        printf("       ------------------------------------------------");
        printf("--------------------\n");
	fclose(fp);
	exit(EXIT_SUCCESS);
}

