// $Log: lz80.cpp,v $
// Revision 1.3  2011/04/14 15:13:09  doug
// get ready for release to wiki and server
//
//

// ---------------------------------------------------
// lz80.cpp     21-Feb-11   Running on Mac OS X 10.6.6
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
// 2/4/2011 dwg - cloned from my Borland version 

static char szLz80Cpp[] = "$Id: lz80.cpp,v 1.3 2011/04/14 15:13:09 doug Exp $";

#include "asdefs.hpp"
#define DWGALLOC
#define INIBIND
#define MEMORY
#include "includes.hpp"

int main(int argc,char **argv)
{
	int pc;

	Version(argv[0]);

	if(2 > argc) {
		printf("usage - l <addr>\n");
		exit(EXIT_FAILURE);
	}

	CAlloc * pAlloc = new CAlloc();
	CMemory * pMem = new CMemory(MEMSIZE);

	sscanf(argv[1],"%04X",&pc);
	int rc = 0;
	while(EXIT_SUCCESS == rc) {
		printf("%04X: %02X ",pc,pMem->peekb(pc));
		switch(pMem->peekb(pc++)) {
			case 0x00: printf("nop");        rc = 0; break;
			case 0x02: printf("ld (bc),a");  rc = 0; break;
			case 0x08: printf("ex af,af'");  rc = 0; break;
			case 0x0A: printf("ld a,(bc)");  rc = 0; break;
			case 0x12: printf("ld (de),a");  rc = 0; break;
			case 0x1A: printf("ld a,(de)");  rc = 0; break;
			case 0x27: printf("daa");        rc = 0; break;
			case 0x2F: printf("cpl");        rc = 0; break;
			case 0x34: printf("inc (hl)");   rc = 0; break;
			case 0x37: printf("scf");        rc = 0; break;
			case 0x3F: printf("ccf");        rc = 0; break;
			case 0x76: printf("halt");       rc = 0; break;
			case 0x86: printf("add (hl)");   rc = 0; break;
			case 0xD9: printf("exx");        rc = 0; break;
			case 0xE3: printf("ex (sp),hl"); rc = 0; break;
			case 0xEB: printf("ex de,hl");   rc = 0; break;
			case 0xED: printf("neg");        rc = 0; break;
			case 0xF3: printf("di");         rc = 0; break;
			case 0xF9: printf("ld sp,hl");   rc = 0; break;
			case 0xFB: printf("ei");         rc = 0; break;
			default: rc = 1;
		}
		printf("\n");
	}

	delete pMem;
		
	delete pAlloc;
}
