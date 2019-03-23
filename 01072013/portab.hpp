// ---------------------------------------------------
// portab.hpp   22-Feb-11   Running on Mac OS X 10.6.6
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

static char szPortabHpp[] = "$Id: portab.hpp,v 1.1 2011/03/24 11:58:05 doug Exp $";

#define TRUE  1
#define FALSE 0

#define COPR "©"

// Comparison strings for $MACHTYPE
// used by ../mktoday.cpp
//
// This string works for Doug's Mac Book Pro
// running Snow Leopard 10.6.6
//#define MACOSX "x86_64-apple-darwin10.0"
#define MACOSX "x86_64-apple-darwin11"
//
// This string works for Doug's Server
// running Scientific Linux (Red Hat Server)
#define LINUX  "x86_64-redhat-linux-gnu"

#define CYGWIN "i686-pc-cygwin"

// eof - portab.hpp

