// $Log: l8085.cpp,v $
// Revision 1.3  2011/04/14 15:13:09  doug
// get ready for release to wiki and server
//
//

// ---------------------------------------------------
// l8085.cpp    21-Feb-11   Running on Mac OS X 10.6.6
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
// 2/4/2011 dwg - cloned from my Borland version 

static char szL8085Cpp[] = "$Id: l8085.cpp,v 1.3 2011/04/14 15:13:09 doug Exp $";

#include "asdefs.hpp"
#define DWGALLOC
#define INIBIND
#define MEMORY
#include "includes.hpp"

int main(int argc,char **argv)
{
	int pc;
	int g_ucBytes;
	unsigned char g_szOpcode;
	unsigned char parm8;
	unsigned int parm16;
	unsigned char byte1;
	unsigned char byte2;
	unsigned char byte3;
	char szI[80];

	Version(argv[0]);

	if(2 > argc) {
		printf("usage - l <addr>\n");
		exit(EXIT_FAILURE);
	}

	CAlloc * pAlloc = new CAlloc();
	CMemory * pMem = new CMemory(MEMSIZE);

	sscanf(argv[1],"%04X",&pc);
	int rc = 0;
	while(0 == rc) {
		g_szOpcode = pMem->peekb(pc);
		parm8  = pMem->peekb(pc+1);
		parm16 = pMem->peekw(pc+1);
		byte1  = g_szOpcode;
		byte2  = pMem->peekb(pc+1);
		byte3  = pMem->peekb(pc+2);

		switch(g_szOpcode) {

			// single byte g_szOpcodes
			

			case 0x00: sprintf(szI,"nop");
				g_ucBytes = 1; rc = 0; break;

			case 0x01: sprintf(szI,"lxi  b,0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;	

			case 0x02: sprintf(szI,"stax b,0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;
			
			case 0x03: sprintf(szI,"inx  b");
				g_ucBytes = 1; rc = 0; break;

			case 0x07: sprintf(szI,"rlc");
				g_ucBytes = 1; rc = 0; break;

			case 0x09: sprintf(szI,"dad  b");
				g_ucBytes = 1; rc = 0; break;

			case 0x0A: sprintf(szI,"ldax b,0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;

			case 0x0B: sprintf(szI,"dcx  b");
				g_ucBytes = 1; rc = 0; break;

			case 0x0F: sprintf(szI,"rrc");
				g_ucBytes = 1; rc = 0; break;

			case 0x11: sprintf(szI,"lxi  d,0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;

                        case 0x12: sprintf(szI,"stax d,0%04XH",parm16);
                                g_ucBytes = 3; rc = 0; break;

			case 0x13: sprintf(szI,"inx  d");
				g_ucBytes = 1; rc = 0; break;

			case 0x17: sprintf(szI,"ral");
				g_ucBytes = 1; rc = 0; break;

			case 0x19: sprintf(szI,"dad  d");
				g_ucBytes = 1; rc = 0; break;

			case 0x1A: sprintf(szI,"ldax d,0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;

			case 0x1B: sprintf(szI,"dcx  d");
				g_ucBytes = 1; rc = 0; break;

			case 0x1F: sprintf(szI,"rar");
				g_ucBytes = 1; rc = 0; break;

			case 0x20: sprintf(szI,"rim");
				g_ucBytes = 1; rc = 0;; break;


			case 0x21: sprintf(szI,"lxi h,0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;

			case 0x22: sprintf(szI,"shld 0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;

			case 0x23: sprintf(szI,"inx  h");
				g_ucBytes = 1; rc = 0; break;

			case 0x27: sprintf(szI,"daa");
				g_ucBytes = 1; rc = 0; break;

			case 0x29: sprintf(szI,"dad  h");
				g_ucBytes = 1; rc = 0; break;

			case 0x2A: sprintf(szI,"lhld 0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;

			case 0x2B: sprintf(szI,"dcx  h");
				g_ucBytes = 1; rc = 0; break;

			case 0x2F: sprintf(szI,"cma");
				g_ucBytes = 1; rc = 0; break;

			case 0x30: sprintf(szI,"sim");
				g_ucBytes = 1; rc = 0; break;

			case 0x31: sprintf(szI,"lxi  sp");
				g_ucBytes = 3; rc = 0; break;

			case 0x32: sprintf(szI,"sta  0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;

			case 0x33: sprintf(szI,"inx  sp");
				g_ucBytes = 1; rc = 0; break;

			case 0x34: sprintf(szI,"inr  m");
				g_ucBytes = 1; rc = 0; break;

			case 0x35: sprintf(szI,"dcr  m");
				g_ucBytes = 1; rc = 0; break;

			case 0x36: sprintf(szI,"mvi m");
				g_ucBytes = 3; rc = 0; break;

			case 0x37: sprintf(szI,"stc");
				g_ucBytes = 1; rc = 0; break;

			case 0x39: sprintf(szI,"dad  sp");
				g_ucBytes = 1; rc = 0; break;

			case 0x3A: sprintf(szI,"lda  0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;

			case 0x3B: sprintf(szI,"dcx  sp");
				g_ucBytes = 1; rc = 0; break;

			case 0x3F: sprintf(szI,"cmc");
				g_ucBytes = 1; rc = 0; break;

			case 0x76: sprintf(szI,"hlt");
				g_ucBytes = 1; rc = 0; break;

			case 0x8E: sprintf(szI,"adc  m");
				g_ucBytes = 1; rc = 0; break;

			case 0x96: sprintf(szI,"sub  m");
				g_ucBytes = 1; rc = 0; break;

			case 0x9E: sprintf(szI,"sbb  m");
				g_ucBytes = 1; rc = 0; break;

			case 0xA6: sprintf(szI,"ama  m");
				g_ucBytes = 1; rc = 0; break;

			case 0xAE: sprintf(szI,"xra  m");
				g_ucBytes = 1; rc = 0; break;

			case 0xB6: sprintf(szI,"ora  m");
				g_ucBytes = 1; rc = 0; break;

			case 0xBE: sprintf(szI,"cmp  m");
				g_ucBytes = 1; rc = 0; break;

			case 0xC0: sprintf(szI,"rnz");
				g_ucBytes = 1; rc = 0; break;


			case 0xC1: sprintf(szI,"pop  b");
				g_ucBytes = 1; rc = 0; break;

			case 0xC2: sprintf(szI,"jnz  0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;

			case 0xC3: sprintf(szI,"jmp  0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;

			case 0xC4: sprintf(szI,"cnz  0%04XH",parm16);
				g_ucBytes = 4; rc = 0; break;

			case 0xC5: sprintf(szI,"push b");
				g_ucBytes = 1; rc = 0; break;
		
			case 0xC6: sprintf(szI,"adi  0%02XH",parm8);
				g_ucBytes = 2; rc = 0; break;

			case 0xC8: sprintf(szI,"rz");
				g_ucBytes = 1; rc = 0; break;

			case 0xC9: sprintf(szI,"ret");
				g_ucBytes = 1; rc = 0; break;

			case 0xCA: sprintf(szI,"jz   0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;

			case 0xCD: sprintf(szI,"call 0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;

			case 0xCE: sprintf(szI,"aci  0%02XH",parm8);
				g_ucBytes = 2; rc = 0; break;

			case 0xD0: sprintf(szI,"rnc");
				g_ucBytes = 1; rc = 0; break;

			case 0xD1: sprintf(szI,"pop  d");
				g_ucBytes = 1; rc = 0; break;

			case 0xD2: sprintf(szI,"jnc  0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;

			case 0xD3: sprintf(szI,"out  0%02XH",parm8);
				g_ucBytes = 2; rc = 0; break;

			case 0xD4: sprintf(szI,"cnc  0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;

			case 0xD5: sprintf(szI,"push d");
				g_ucBytes = 1; rc = 0; break;

			case 0xD6: sprintf(szI,"sui  0%02XH",parm8);
				g_ucBytes = 2; rc = 0; break;

			case 0xD8: sprintf(szI,"rc");
				g_ucBytes = 1; rc = 0; break;

			case 0xDA: sprintf(szI,"jc   0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;

			case 0xDB: sprintf(szI,"in   0%02XH",parm8);
				g_ucBytes = 2; rc = 0; break;

			case 0xDC: sprintf(szI,"cc   0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;

			case 0xDE: sprintf(szI,"sbi  0%02XH",parm8);
				g_ucBytes = 2; rc = 0; break;

			case 0xE0: sprintf(szI,"rpo");
				g_ucBytes = 1; rc = 0; break;

			case 0xE1: sprintf(szI,"pop  h");
				g_ucBytes = 1; rc = 0; break;

			case 0xE2: sprintf(szI,"jpo  0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;

			case 0xE3: sprintf(szI,"xthl");
				g_ucBytes = 1; rc = 0; break;

			case 0xE4: sprintf(szI,"cpo  0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;

			case 0xE5: sprintf(szI,"push h");
				g_ucBytes = 1; rc = 0; break;

			case 0xE6: sprintf(szI,"ani");
				g_ucBytes = 1; rc = 0; break;
		
			case 0xE8: sprintf(szI,"rpe");
				g_ucBytes = 1; rc = 0; break;

			case 0xE9: sprintf(szI,"pchl");
				g_ucBytes = 1; rc = 0; break;

			case 0xEA: sprintf(szI,"jpe  0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;

			case 0xEB: sprintf(szI,"xchg");
				g_ucBytes = 1; rc = 0; break;

			case 0xEC: sprintf(szI,"cpe  0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;

			case 0xEE: sprintf(szI,"xri");
				g_ucBytes = 1; rc = 0; break;

			case 0xF0: sprintf(szI,"rp");
				g_ucBytes = 1; rc = 0; break;

			case 0xF1: sprintf(szI,"pop  psw");
				g_ucBytes = 1; rc = 0; break;

			case 0xF2: sprintf(szI,"jp   0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;

			case 0xF3: sprintf(szI,"di");
				g_ucBytes = 1; rc = 0;  break;

			case 0xF4: sprintf(szI,"cp   0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;

			case 0xF5: sprintf(szI,"push psw");
				g_ucBytes = 1; rc = 0; break;

			case 0xF6: sprintf(szI,"ori  0%02XH",parm8);
				g_ucBytes = 2; rc = 0; break;

			case 0xF8: sprintf(szI,"rm");
				g_ucBytes = 1; rc = 0; break;

			case 0xF9: sprintf(szI,"sphl");
				g_ucBytes = 1; rc = 0; break;

			case 0xFA: sprintf(szI,"jm   0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;

			case 0xFB: sprintf(szI,"ei");
				g_ucBytes = 1; rc = 0; break;

			case 0xFC: sprintf(szI,"cm   0%04XH",parm16);
				g_ucBytes = 3; rc = 0; break;

			case 0xFE: sprintf(szI,"cpi  0%02XH",parm8);
				g_ucBytes = 2; rc = 0; break;

			default: rc = 1;
		}
		if(0 == rc) {
			printf("%04X: ",pc);
			switch(g_ucBytes) {
				case 1:
					printf("%02X         ",
						byte1);
					break;
				case 2:
					printf("%02X %02X     ",
						byte1,byte2);
					break;
				case 3:
					printf("%02X %02X %02X  ",
						byte1,byte2,byte3);
					break;
			}
			printf("%s",szI);
			printf("\n");
			pc += g_ucBytes;
		}
	}

	delete pMem;
		
	delete pAlloc;
}
