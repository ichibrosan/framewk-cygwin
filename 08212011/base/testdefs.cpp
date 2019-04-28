// $Log: testdefs.cpp,v $
// Revision 1.3  2011/04/14 15:13:09  doug
// get ready for release to wiki and server
//
//

// ---------------------------------------------------
// testdefs.cpp 21-Feb-11   Running on Mac OS X 10.6.6
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

static char szTestdefsCpp[] = "$Id: testdefs.cpp,v 1.3 2011/04/14 15:13:09 doug Exp $";


//#define __TRACE

#include "asdefs.hpp"
#define BINDEFS
#define DWGALLOC
#define INIBIND
#include "includes.hpp"

int main(int argc,char **argv)
{
	TRACE("Entering hello.cpp's main routine");
	
	Version(argv[0]);

	printf("Ob11100101 becomes 0x%02X\n",Ob11100101);

	TRACE("Exiting hello.cpp's main routine");
	
	return EXIT_SUCCESS;
}

