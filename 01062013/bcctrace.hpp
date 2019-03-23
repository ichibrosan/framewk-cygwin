// ---------------------------------------------------
// bcctrace.hpp 21-Feb-11   Running on Mac OS X 10.6.6
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
// These routines emulate the trace and warn functionality
// from the Borland C++ 4.x compiler environment.

static char szBcctraceHpp[] = "$Id: bcctrace.hpp,v 1.1 2011/03/24 11:58:05 doug Exp $";

#define TRACE(x) TRACEX(__FILE__,__LINE__,x);

void TRACEX(char *szFile,int line,char *szStr)
{
#ifdef __TRACE
	printf("TRACE: %s[%d] %s\n",szFile,line,szStr);
#endif
	if(TRUE == g_bTrace) {
        	printf("TRACE: %s[%d] %s\n",szFile,line,szStr);
	}
}

#define WARN(x) WARNX(__FILE__,__LINE__,x);

void WARNX(char *szFile,int line,char *szStr)
{
#ifdef __WARN
	printf("WARN: %s[%d] %s\n",szFile,line,szStr);
#endif
}

// eof - bcctrace.hpp
