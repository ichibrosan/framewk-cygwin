// ---------------------------------------------------
// filename.ext 21-Feb-11   Running on Mac OS X 10.6.6
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

#include "asdefs.hpp"
#include "includes.hpp"

int main(int argc,char **argv)
{
	Version(argv[0]);

	FILE * fd1 = fopen(argv[1],"r");
	FILE * fd2 = fopen("tempfile.tmp","w");

	char szTemp[255];
	char * p;

	p = fgets(szTemp,sizeof(szTemp),fd1);
	while(NULL != p) {

		if(0 < strlen(szTemp)) {
			if(0x0d == szTemp[strlen(szTemp)-1]) {
				szTemp[strlen(szTemp)-1] = 0;
			}
		}

		if(0 < strlen(szTemp)) {
                	if(0x0a == szTemp[strlen(szTemp)-1]) {
                        	szTemp[strlen(szTemp)-1] = 0;
                	}
		}

		if(0 < strlen(szTemp)) {
                	if(0x0d == szTemp[strlen(szTemp)-1]) {
                        	szTemp[strlen(szTemp)-1] = 0;
                	}
		}

		if(0 < strlen(szTemp)) {
                	if(0x0a == szTemp[strlen(szTemp)-1]) {
                        	szTemp[strlen(szTemp)-1] = 0;
                	}
		}

		fprintf(fd2,"%s\n",szTemp);
		p = fgets(szTemp,sizeof(szTemp),fd1);

	}
	fclose(fd1);
	fclose(fd2);
        sprintf(szTemp,"cp tempfile.tmp %s",argv[1]);
        system(szTemp);
	system("rm -f tempfile.tmp");
	return EXIT_SUCCESS;
}

