// ---------------------------------------------------
// makedeco.cpp 24-Feb-11   Running on Mac OS X 10.6.6
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

// 02/25/2011 dwg - don't add .hpp files starting with _

//#define __TRACE

#include "asdefs.hpp"
//#define DWGALLOC
#define INIBIND
#define DIRCLASS
#include "includes.hpp"

char szHppBuffer[1023];

int main(int argc,char **argv)
{
  memset(szHppBuffer,0,sizeof(szHppBuffer));

  char szBuffer[1024];

  Version(argv[0]);

  FILE * fd = fopen("decoincl.hpp","w");
  if(NULL == fd) {
    printf("Sorry, cannot open \"decoincl.hpp\" for output\n");
    exit(EXIT_FAILURE);
  }
  CDir *  dir2 = new CDir(".");
  assert(dir2);
  int rc2= dir2->read();
  while(EXIT_SUCCESS == rc2){
    dir2->getname(szBuffer);
    if(DT_REG == dir2->gettype()) {
      if(4 < strlen(szBuffer)) {
	if(0 != strcmp("decoincl.hpp",szBuffer)) {
          if(0 == strcmp(".hpp",&szBuffer[strlen(szBuffer)-4])) {
	    if('_' != szBuffer[0]) {
 	      fprintf(fd,"#include \"%s/%s\"\n",
	 	      version.getpwd(),szBuffer);
	    }
 	  }
	}
      }
    }
    rc2 = dir2->read();
  }
  delete dir2;
  fclose(fd);
  return EXIT_SUCCESS;
}

