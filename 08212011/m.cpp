// $Log: m.cpp,v $
// Revision 1.3  2011/04/14 15:13:09  doug
// get ready for release to wiki and server
//
//

// ---------------------------------------------------
// m.cpp        21-Feb-11   Running on Mac OS X 10.6.6
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

static char szMCpp[] = "$Id: m.cpp,v 1.3 2011/04/14 15:13:09 doug Exp $";

#include "asdefs.hpp"
#define DWGALLOC
#define INIBIND
#define MEMORY
#include "includes.hpp"

int main(int argc,char **argv)
{
	Version(argv[0]);

	if(4 > argc) {
		printf("usage - m <destaddr> <srcaddr> <length>\n");
		exit(EXIT_FAILURE);
	}

	unsigned int destaddr,srcaddr,length;
	sscanf(argv[1],"%04X",&destaddr);
	sscanf(argv[2],"%04X",&srcaddr);
	sscanf(argv[3],"%04X",&length);
	
	CMemory mem(MEMSIZE);
	for(int i=0;i<length;i++) {
		mem.pokeb(destaddr+i,mem.peekb(srcaddr+i));
	}
}
