// ---------------------------------------------------
// includes.hpp 21-Feb-11   Running on Mac OS X 10.6.6
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
// 2011/02/01 dwg - added bcctrace functionality

static char szIncludesHpp[] = "$Id: includes.hpp,v 1.2 2011/04/03 04:53:07 doug Exp $";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <dirent.h>
#include <ctype.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <errno.h>

#include "cbindefs.hpp"
#include "portab.hpp"
#include "globdata.hpp"
#include "bcctrace.hpp"
#include "strupr.hpp"
#include "strlwr.hpp"
#include "environ.hpp"
#define INIBIND
#include "inibind.hpp"
#include "version.hpp"
#include "versbind.hpp"
//#include "cpostfix.hpp"
#define DWGALLOC
#include "dwgalloc.hpp"
#include "dirclass.hpp"
#include "memory.hpp"
#include "pcascii.hpp"
#include "srcclass.hpp"
 
// eof - includes.hpp

