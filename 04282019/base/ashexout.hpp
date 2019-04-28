// ---------------------------------------------------
// ashexout.hpp 21-Feb-11   Running on Mac OS X 10.6.6
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

static char szAshexoutHpp[] = "$Id: ashexout.hpp,v 1.1 2011/03/24 11:58:05 doug Exp $";

// The purpose of this function is to write a number of binary 
// g_ucBytes from the global vector "unsigned char g_ucBytes[MEMSIZE];"
// into the open output file g_fhex.


// to create 2's compliment, flip all bits and add 1
// (xor with FF ) + 1 does that

// : <length> <addr> <type> <data> <checksum>

#define DATA_RECORD 0x00
#define EOF_RECORD  0x01

void hexout(int mypc,int mycount,int myoffset)
{
	fprintf(g_flog,"hexout(pc=%04X,count=%d,offset=%d); called\n",
		mypc,mycount,myoffset);

	if(TRUE == g_bDebug) {
        	printf("hexout(pc=%04X,count=%d,offset=%d); called\n",
                	mypc,mycount,myoffset);
	}

	unsigned char checksum = 0;
	char szHexTemp[4];
	
	fprintf(g_fhex,":");
	fprintf(g_fhex,"%02X",mycount);
	fprintf(g_fhex,"%04X",mypc);
	fprintf(g_fhex,"%02X",DATA_RECORD);
	for(int myindex=0;myindex<mycount;myindex++) {

		if(TRUE == g_bBinary) {		// if they asked
			if(NULL != g_pCMemory) {	// if it's available
				g_pCMemory->pokeb(mypc+myindex,
					     g_ucBytes[myindex+myoffset]);
			}
		}

		sprintf(szHexTemp,"%02X",g_ucBytes[myindex+myoffset]);
//		printf("strlen(szHexTemp) is %d\n",strlen(szHexTemp));
		fprintf(g_fhex,"%s",szHexTemp);
//		fprintf(g_fhex,"%02X",(unsigned char)g_ucBytes[myindex+myoffset]);
		checksum += g_ucBytes[myindex+myoffset];
	}

	fprintf(g_fhex,"%02X",(unsigned char)((checksum^0xff)+1));

	fprintf(g_fhex,"\n");
}

////////////////////////
// eof - ashexout.hpp //
////////////////////////

