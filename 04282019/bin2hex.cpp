// $Log: bin2hex.cpp,v $
// Revision 1.3  2011/04/14 15:13:09  doug
// get ready for release to wiki and server
//
//

// ---------------------------------------------------
// bin2hex.cpp  22-Mar-11   Running on Mac OS X 10.6.6
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

static char szBin2hexCpp[] = "$Id: bin2hex.cpp,v 1.3 2011/04/14 15:13:09 doug Exp $";

#include "asdefs.hpp"
#define INIBIND
#include "includes.hpp"

#define DATA_RECORD 0x00

int main(int argc,char **argv)
{
	unsigned char szBuffer[255];
	unsigned char ucTemp;

	Version(argv[0]);

	if(3 > argc) {
		printf("usage - %s <binary-file> <new-hex-file>\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	FILE * fdin = fopen(argv[1],"r");
	if(NULL == fdin) {
		printf("Sorry, cannot open %s for input\n",argv[1]);
		exit(EXIT_FAILURE);
	}

	FILE * fhex = fopen(argv[2],"w");
	if(NULL == fhex) {
		printf("Sorry, cannot open %s for output\n",argv[2]);
		fclose(fdin);
		exit(EXIT_FAILURE);
	}

	int o = 0;
	int rc = fread(szBuffer,1,16,fdin);
	while(0 < rc) {
                unsigned char checksum = 0;
                fprintf(fhex,":");
                fprintf(fhex,"%02X",rc);
                fprintf(fhex,"%04X",o);
                fprintf(fhex,"%02X",DATA_RECORD);
                for(int index=0;index<rc;index++) {
			ucTemp = szBuffer[index];
                	fprintf(fhex,"%02X",ucTemp);
                	checksum += ucTemp;
                }
                fprintf(fhex,"%02X",(unsigned char)((checksum^0xff)+1)&0xff);
                fprintf(fhex,"\n");

		rc = fread(szBuffer,1,16,fdin);
		o += 16;
	}

	return(EXIT_SUCCESS);
}

