// $Log: lhex.cpp,v $
// Revision 1.3  2011/04/14 15:13:09  doug
// get ready for release to wiki and server
//
//

// ---------------------------------------------------
// lhex.cpp     21-Feb-11   Running on Mac OS X 10.6.6
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
// 2/4/2011 dwg - cloned from Borland version

static char szLhexCpp[] = "$Id: lhex.cpp,v 1.3 2011/04/14 15:13:09 doug Exp $";

#include "asdefs.hpp"
#define DWGALLOC
#define INIBIND
#define MEMORY
#include "includes.hpp"

// to create 2's compliment, flip all bits and add 1
// (xor with FF ) + 1 does that

// : <length> <addr> <type> <data> <checksum>

#define DATA_RECORD 0x00
#define EOF_RECORD  0x01

int main(int argc,char **argv)
{
	char g_szBuffer2[128];
	char szByteBuffer[2+1];
	char *p;
	int iTemp;
		
	char cColon;

	char szLength[2+1];
	int  iLength;
	
	char szAddress[4+1];
	unsigned int uiAddress;
	
	char szRecordType[2+1];
	unsigned char ucRecordType;
	
	char szData[80];
	unsigned char ucBinBuffer[32+1];
	
	char szChecksum[2+1];
	unsigned char ucChecksum;
			
	Version(argv[0]);

	if(1 == argc) {
		printf("usage - s <filespec>\n");
	}

	CAlloc * pAlloc = new CAlloc();
	if(NULL == pAlloc) {
		printf("pAlloc is NULL\n");
	}

	CMemory * pMem = new CMemory(MEMSIZE);

	FILE * fhex = fopen(argv[1],"r");		

	p = fgets(g_szBuffer2,sizeof(g_szBuffer2),fhex);			
	while(NULL != p) {
		g_szBuffer2[strlen(g_szBuffer2)-1] = 0;
//		printf("DEBUG: buffer -> \"%s\"\n",g_szBuffer2);

		cColon = g_szBuffer2[0];

		memset(szLength,0,sizeof(szLength));
		memcpy(szLength,&g_szBuffer2[1],2);
		sscanf(szLength,"%02X",&iLength);
//		printf("DEBUG: iLength is %d\n",iLength);
		
		memset(szAddress,0,sizeof(szAddress));
		memcpy(szAddress,&g_szBuffer2[3],4);
		sscanf(szAddress,"%04X",&uiAddress);
//		printf("DEBUG: uiAddress is %04X\n",uiAddress);
		
		memset(szRecordType,0,sizeof(szRecordType));
		memcpy(szRecordType,&g_szBuffer2[7],2);
		sscanf(szRecordType,"%02X",&ucRecordType);
//		printf("DEBUG: ucRecordType is %02X\n",ucRecordType);

		if(0 == ucRecordType) {
			memset(szData,0,sizeof(szData));
			memcpy(szData,&g_szBuffer2[9],iLength*2);
			for(int i=0;i<iLength;i++) {
				memset(szByteBuffer,0,sizeof(szByteBuffer));
				memcpy(szByteBuffer,&g_szBuffer2[1+2+4+2+(i*2)],2);
				sscanf(szByteBuffer,"%02X",&iTemp);
				ucBinBuffer[i] = iTemp;
				pMem->pokeb(uiAddress+i,(unsigned char)iTemp);
//				printf("DEBUG: ucBinBuffer[%d] is %02X\n",i,ucBinBuffer[i]);						
//				printf("----------------------------\n");

			}
		}
		memset(szChecksum,0,sizeof(szChecksum));
		memcpy(szChecksum,&g_szBuffer2[1+2+4+2+(iLength*2)],2);
		sscanf(szChecksum,"%02X",&ucChecksum);
//		printf("DEBUG: ucChecksum is %02X\n",ucChecksum);

		p = fgets(g_szBuffer2,sizeof(g_szBuffer2),fhex);
	}
	fclose(fhex);

	delete pMem;
		
	delete pAlloc;
}
