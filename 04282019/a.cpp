// $Log: a.cpp,v $
// Revision 1.3  2011/04/14 15:13:09  doug
// get ready for release to wiki and server
//
//

// ---------------------------------------------------
// a.cpp        21-Feb-11   Running on Mac OS X 10.6.6
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

static char szACpp[] = "$Id: a.cpp,v 1.3 2011/04/14 15:13:09 doug Exp $";

#include "asdefs.hpp"
#define DWGALLOC
#define INIBIND
#define MEMORY
#include "includes.hpp"

int main(int argc,char **argv)
{
	int offset;

	Version(argv[0]);

	if(2 > argc) {
		printf("usage - a <addr>\n");
		printf("This initial version assembles 4 instructions\n");
		exit(EXIT_FAILURE);
	}


	CAlloc * pAlloc = new CAlloc();
	CMemory * pMem = new CMemory(MEMSIZE);

	sscanf(argv[1],"%04X",&offset);
	pMem->pokew(offset  ,0x57e7);
	pMem->pokew(offset+2,0x5fed);
	pMem->pokew(offset+4,0x47ed);
	pMem->pokew(offset+6,0x4fed);
	
	delete pMem;
		
	delete pAlloc;
}
