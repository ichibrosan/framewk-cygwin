// $Log: testenv.cpp,v $
// Revision 1.3  2011/04/14 15:13:09  doug
// get ready for release to wiki and server
//
//

// ---------------------------------------------------
// testenv.cpp  25-Feb-11   Running on Mac OS X 10.6.6
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

static char szTestenvCpp[] = "$Id: testenv.cpp,v 1.3 2011/04/14 15:13:09 doug Exp $";

#include "asdefs.hpp"
#include "includes.hpp"

int main(int argc,char **argv)
{
	Version(argv[0]);

	CEnvironment env;

	printf("BASH_VERSION         = %s\n",env.getbashversion());
	
	printf("COLUMNS              = %s\n",ini_read(argv[0],"Env","LINES"));
	printf("COMMAND_MODE         = %s\n",env.getcommandmode());
	printf("HOSTNAME             = %s\n",env.gethostname());
	printf("LINES                = %s\n",ini_read(argv[0],"Env","LINES"));
	printf("TERM                 = %s\n",env.getterm());
	printf("TERM_PROGRAM         = %s\n",env.gettermprogram());
	printf("TERM_PROGRAM_VERSION = %s\n",env.gettermprogramversion());
	printf("TMPDIR               = %s\n",env.gettmpdir());
	printf("UNKNOWN              = %s\n",ini_read(argv[0],"Env","UNK"));
	return(EXIT_SUCCESS);
}
