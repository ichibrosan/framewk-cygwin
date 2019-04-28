// $Log: hello.cpp,v $
// Revision 1.3  2011/04/14 15:13:09  doug
// get ready for release to wiki and server
//
//

// ---------------------------------------------------
// hello.cpp    21-Feb-11   Running on Mac OS X 10.6.6
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
// The "includes.hpp" file has in turn a number of
// include macros that read in standard and custom
// header files. This simplifies most programs.

static char szHelloCpp[] = "$Id: hello.cpp,v 1.3 2011/04/14 15:13:09 doug Exp $";

#include "asdefs.hpp"
#include "includes.hpp"

int main(int argc,char **argv)
{
	// The Version macro instanciates a CVersion
	// object which does a few things, such as
	// referencing the program's ini file to see
	// if a full banner should be output. The
	// first time the program is run, an ini file 
	// is created with the banner enabled. The 
	// hello.ini file can be edited and the banner 
	// value changed to "None" which will suppress
	// the banner on startup.
	Version(argv[0]);
	printf("version.getdebug()            is %s\n",version.getdebug());
	printf("version.getmachtype()         is %s\n",version.getmachtype());
	printf("version.getostype()           is %s\n",version.getostype());
	printf("version.getpwd()              is %s\n",version.getpwd());
	printf("version.getsyncro()           is %s\n",version.getsyncro());
	printf("version.getuid()              is %s\n",version.getuid());
	printf("version.getuser()             is %s\n",version.getuser());

	// The global data (globdata.hpp) contains framework
	// wide constants used by both the framework and
	// framework applications
	printf("globdata.hpp: g_bDebug        is ");
	switch(g_bDebug) {
		case FALSE: printf("FALSE\n"); break;
		case TRUE:  printf("TRUE\n");  break;
	}
	printf("globdata.hpp: g_bLog          is ");
        switch(g_bLog) {
                case FALSE: printf("FALSE\n"); break;
                case TRUE:  printf("TRUE\n");  break;
        }
	printf("globdata.hpp: g_bMonitor      is ");
        switch(g_bMonitor) {
                case FALSE: printf("FALSE\n"); break;
                case TRUE:  printf("TRUE\n");  break;
        }
	printf("globdata.hpp: g_bTrace        is ");
        switch(g_bTrace) {
                case FALSE: printf("FALSE\n"); break;
                case TRUE:  printf("TRUE\n");  break;
        }

	// Each application gets it's own configuration 
	// file (program.ini). The ini_read function 
	// can access any of the keys in the file by section.
                ini_read(argv[0],"Options","Banner");
	printf("ini_read(,\"Options\",\"Banner\") is %s\n",g_szIniValue);
                ini_read(argv[0],"Env","HOME");
        printf("ini_read(,\"Env\",\"HOME\")       is %s\n",g_szIniValue);
              ini_read(argv[0],"Env","HOSTNAME");
        printf("ini_read(,\"Env\",\"HOSTNAME\")   is %s\n",g_szIniValue);
              ini_read(argv[0],"Env","HOSTTYPE");
        printf("ini_read(,\"Env\",\"HOSTTYPE\")   is %s\n",g_szIniValue);
	      ini_read(argv[0],"Env","LOGNAME");
        printf("ini_read(,\"Env\",\"LOGNAME\")    is %s\n",g_szIniValue);
              ini_read(argv[0],"Env","PWD");
        printf("ini_read(,\"Env\",\"PWD\")        is %s\n",g_szIniValue);

	return EXIT_SUCCESS;
}

