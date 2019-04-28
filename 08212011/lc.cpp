// $Log: lc.cpp,v $
// Revision 1.3  2011/04/14 15:13:09  doug
// get ready for release to wiki and server
//
//

// ---------------------------------------------------
// lc.cpp       21-Feb-11   Running on Mac OS X 10.6.6
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
// 2/4/2011 dwg - cloned from the Borland version

static char szLcCpp[] = "$Id: lc.cpp,v 1.3 2011/04/14 15:13:09 doug Exp $";

#include "asdefs.hpp"
#define INIBIND
#include "includes.hpp"

int main(int argc,char **argv)
{
	char *p;
	char buffer[255];
	FILE *fp;
	int lines;
			
	Version(argv[0]);

	if(2 != argc) {
		printf("usage - %s <filespec>\n",argv[0]);
		exit(EXIT_FAILURE);	
	}
	
	fp = fopen(argv[1],"r");
	if(NULL == fp) {
		printf("Sorry, cannot open %s for input\n",argv[1]);
		exit(EXIT_FAILURE);
	}	
	lines = 0;
	p = fgets(buffer,sizeof(buffer),fp);
	while(NULL != p) {
		lines++;
		p = fgets(buffer,sizeof(buffer),fp);
	}
	fclose(fp);

	printf("File %s has %d lines\n",argv[1],lines);
	exit(EXIT_SUCCESS);
}
