// ---------------------------------------------------
// globdata.hpp 12-Mar-11   Running on Mac OS X 10.6.6
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
// 1/12/2011 dwg - added bLog global variable set by versbind CTOR

static char szGlobdataHpp[] = "$Id: globdata.hpp,v 1.1 2011/03/24 11:58:05 doug Exp $";

char g_szIniValue[DEFAULT_STRSIZE];

// The versbind processing sets this boolean depending
// on the settings of the program's ini file. It defaults
// to FALSE. The version processing doesn't use the ini_alloc 
// so you have time to set the debug bool with the ini file
// prior to normal usage of the CAlloc class.

int g_bDebug   = DEFAULT_DEBUG;
int g_bLog     = DEFAULT_LOG;
int g_bMonitor = DEFAULT_MONITOR;
int g_bTrace   = DEFAULT_TRACE;
int g_bWarn    = DEFAULT_WARN;

////////////////////////
// eof - globdata.hpp //
////////////////////////
