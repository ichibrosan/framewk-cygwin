// ---------------------------------------------------
// asdecdir.hpp 25-Feb-11   Running on Mac OS X 10.6.6
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

static char szAsdecdirHpp[] = "$Id: asdecdir.hpp,v 1.1 2011/03/24 11:58:05 doug Exp $";

void decode_directives()
{
	int rc;
	unsigned int value;
		
	// The strupr function happens to fold
	// strings. This code preserves the
	// orginal case, to be restored after
	// g_szOpcode processing (see below)
	strcpy(g_szRawLabel,g_szLabel);
	strcpy(g_szRawOpcode,g_szOpcode);
	strcpy(g_szRawParms,g_szParms);
	strcpy(g_szRawComments,g_szComments);

	if( (strlen(g_szLabel)==0) && (strlen(g_szOpcode)==0) &&
	    (strlen(g_szParms)==0) && (strlen(g_szComments)>0) ) {
	 	g_iLineType = TYPE_COMMENT;   
		g_iErrorNo ^= ERROR_UNKOP;
	} 

	if( (strlen(g_szLabel)==0) && (strlen(g_szOpcode)==0) &&
	    (strlen(g_szParms)==0) && (strlen(g_szComments)==0) ) {
	 	g_iLineType = TYPE_EMPTY; 
		g_iErrorNo ^= ERROR_UNKOP;  
	} 

//#ifdef NEVER
	if(0 < strlen(g_szOpcode)) {
#include "ascommon/decoincl.hpp"
	}
//#endif

	// This code restores the original case of 
	// strings that were unintentionally folded
	// to upper case by strupr function.
	strcpy(g_szLabel,g_szRawLabel);
	strcpy(g_szOpcode,g_szRawOpcode);
	strcpy(g_szParms,g_szRawParms);
	strcpy(g_szComments,g_szRawComments);
}

// eof - decodir.hpp
