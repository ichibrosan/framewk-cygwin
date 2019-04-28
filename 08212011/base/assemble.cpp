// ---------------------------------------------------
// assemble.cpp  9-May-11   Running on Mac OS X 10.6.6
// S/n 2011-1042-654321  Written by Douglas W. Goodall
// Copyright(c)2011 Douglas W. Goodall, United States.
// ---------------------------------------------------
// This file is part of Vintage Modern Assembler Plus Tools.
// VMAPT is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// VMAPT is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with VMAPT.  If not, see <http://www.gnu.org/licenses/>.

static char szAssembleCpp[] = "$Id: assemble.cpp,v 1.5 2011/04/14 15:13:09 doug Exp $";

//#define DEBUG
//#define __TRACE

//---------------------
#include "asdefs.hpp"
#define DIRCLASS
#define MEMORY
#define SRCCLASS
#include "includes.hpp"
//---------------------

enum {  TYPE_ERR,	// source line not identified yet
	TYPE_DIR,	// source line is directive
	TYPE_8085,	// source line is 8085 instruction
	TYPE_8080,	// source line is 8080 instruction
	TYPE_6502,	// source line is 6502 instruction
	TYPE_68000,	// source line is 6800 instruction
	TYPE_Z80,	// source line is z80  instruction
	TYPE_1620,	// source line is 1620 instruction
	TYPE_COMMENT,	// source line is comment
	TYPE_EMPTY,	// source line is empty
	NUM_LINETYPES };

// Errors are bits in g_iErrorNo
#define ERROR_NONE      0
#define ERROR_UNKOP    (1<<0)
#define ERROR_UNKSYM   (1<<1)
#define ERROR_RANGE    (1<<2)
#define ERROR_OPERATOR (1<<3)
#define ERROR_NOPARM   (1<<4)
#define ERROR_NOREG    (1<<5)
#define ERROR_NOMODE   (1<<6)
#define ERROR_NOVEC    (1<<7)
#define ERROR_SYNTAX   (1<<8)
#define ERROR_DIV0     (1<<9)
#define ERROR_SYMTYPE  (1<<10)
#define ERROR_INVNS    (1<<11)
#define ERROR_NOCPU    (1<<12)
#define ERROR_UNK_PUB  (1<<13)
#define ERROR_UNK_EXP  (1<<14)

enum {
	PROC_NONE,
	PROC_8080,
	PROC_8085,
	PROC_Z80,
	PROC_6502,
	PROC_68000,
	PROC_1620,
	NUM_PROCS
};

enum {	SEG_VAGUE,
	SEG_ABS,
	SEG_CODE,
	SEG_DATA,
	SEG_STACK,
	NUM_SEGS
};

#define LOCAL_DEFAULT_PAGELENGTH   50 
#define LOCAL_DEFAULT_PAGEWIDTH    74
#define LOCAL_DEFAULT_PROC         PROC_8085
#define LOCAL_DEFAULT_LISTINCLUDES TRUE

// Warnings are bits in g_iWarningNo
#define WARNING_NONE      0
#define WARNING_DIV0     (1<<0)
#define WARNING_EXTERNAL (1<<1)

char g_cToken;	// used by parser to store current input token

char *g_p;	// 

char g_szArgv0[DEFAULT_STRSIZE];

char g_szAsparseHpp[DEFAULT_STRSIZE];
char g_szAsprintHpp[DEFAULT_STRSIZE];
char g_szAssembleCpp[DEFAULT_STRSIZE];

char g_szBuffer[DEFAULT_STRSIZE];
char g_szBuffer2[DEFAULT_STRSIZE];
char g_szCommand[DEFAULT_STRSIZE];	// used for system() call
char g_szComments[DEFAULT_STRSIZE];
char g_szCopr[DEFAULT_STRSIZE];

char g_szFileNameASM[MAXNAMLEN];
char g_szFileNameBIN[MAXNAMLEN];
char g_szFileNameHEX[MAXNAMLEN];
char g_szFileNameLOG[MAXNAMLEN];
char g_szFileNameLST[MAXNAMLEN];
char g_szFileNameOBJ[MAXNAMLEN];
char g_szFileNameEXP[MAXNAMLEN];

char g_szLabel[DEFAULT_STRSIZE];	// filled in by parser
char g_szOpcode[DEFAULT_STRSIZE];	// filled in by parser
char g_szParms[DEFAULT_STRSIZE];	// filled in by parser
char g_szPc[DEFAULT_STRSIZE];
char g_szProgram[DEFAULT_STRSIZE];

char g_szRadixFormat8[8];
char g_szRadixFormat8Decimal[] = "%d";
char g_szRadixFormat8Hex[] = "%03X";

char g_szRadixFormat16[8];
char g_szRadixFormat16Decimal[] = "%d";
char g_szRadixFormat16Hex[] = "%05X";

char g_szRadixFormat32[8];
char g_szRadixFormat32Decimal[] = "%ld";
char g_szRadixFormat32Hex[] = "%09lX";

char g_szRadixFormat64[16];
char g_szRadixFormat64Decimal[] = "%lld";
char g_szRadixFormat64Hex[] = "%017llX";

char g_szListRadix[16];
char g_szListRadixHex[] = "%04X";
char g_szListRadixDec[] = "%05d";

char g_szRawComments[DEFAULT_STRSIZE];
char g_szRawLabel[DEFAULT_STRSIZE];
char g_szRawLine[DEFAULT_STRSIZE];
char g_szRawOpcode[DEFAULT_STRSIZE];
char g_szRawParms[DEFAULT_STRSIZE];

char g_szSep[DEFAULT_STRSIZE];
char g_szSerial[DEFAULT_STRSIZE];
char g_szSubttl[DEFAULT_STRSIZE];
char g_szTemp[DEFAULT_STRSIZE];
char g_szTitle[DEFAULT_STRSIZE];

char g_szStrBuffer[DEFAULT_STRSIZE];	// filled in by CSymbols::getstring

int  g_bBinary = DEFAULT_BINARY;
int  g_bComments;		// comment field (set in parser)
int  g_bEndFound;		// end statement found
int  g_bExported = FALSE;	// export directive used
int  g_bLabel;			// label field found
int  g_bOpcode;			// opcode field found
int  g_bParms;			// parms field found
int  g_bPass1;			// we are in pass 1 (set in main)
int  g_bPass2;			// we are in pass 2 (set in main)

int  g_bSTR = FALSE;
int  g_bE8  = FALSE;
int  g_bE16 = FALSE;
int  g_bE32 = FALSE;
int  g_bE64 = FALSE;

int  g_bP8  = FALSE;
int  g_bP16 = FALSE;
int  g_bP32 = FALSE;
int  g_bP64 = FALSE;

int  g_bU8  = FALSE;
int  g_bU16 = FALSE;
int  g_bU32 = FALSE;
int  g_bU64 = FALSE;

int  g_bSaveSymbols  = DEFAULT_SAVESYMBOLS;
int  g_bTypeIncludes = DEFAULT_TYPEINCLUDES;
int  g_bTypeSource   = DEFAULT_TYPESOURCE;
int  g_bListIncludes = LOCAL_DEFAULT_LISTINCLUDES;	      
int  g_b1stHdrLstd   = FALSE;
int  g_iBytesIndex;	// bytes emitted by this instruction
int  g_iErrorNo;		// global error bitmask 
int  g_iErrors = 0;	// number of errors in pass2
int  g_iFileLine;        // used by print function
int  g_iLineType;        // see line type enum
int  g_iPageLength;	// used by print function
int  g_iPageline;	// used by print function
int  g_iPageNumber;	// used by print function
int  g_iPageWidth;	// used by print function
int  g_iPc;		// program counter
int  g_iProc = LOCAL_DEFAULT_PROC;
int  g_iRc;		// used to receive return code
int  g_iSegment;	// current segment type
int  g_iSoboff;
int  g_iSobrante;
int  g_iSpaces = 5;	// used to format listing header
int  g_iSourceLevel;	// used by print function
int  g_iState;		// used by parser
int  g_iTriplets;	// triplets needed for string
int  g_iTripoff;	// number of bytes after triplets
int  g_iVerbosity;	// self documenting
int  g_iWarningNo;      // global warning bitmask
int  g_iWarnings;	// number of warnings in pass2
FILE *        g_fhex;           // Assembler hex     file handle
FILE *        g_flog;		// Assembler log     file handle
FILE *        g_flst;           // Assembler listing file handle
FILE *        g_fexp;		// Assembler export  file handle

CMemory *     g_pCMemory = NULL;
CSource *     g_pCSource1;  // Used for pass 1
CSource *     g_pCSource2;  // Used for pass 2

#ifndef MEMSIZE
#define MEMSIZE 32768
#endif
unsigned char g_ucBytes[MEMSIZE];	// filled by code handlers

unsigned char g_ucTemp;
unsigned int  g_uiTarget;        // used by ascommon/_bshort.hpp


#define CALC
#include "ascalc.hpp"

// The asprint module contains the "print" function which
// is used to format the listing file with page breaks...
#include "asprint.hpp"

// The CSymbols class provides a set of member functions
// used to create a symbol table, add entries, and reference
// them during the assembly process.
#include "asymbols.hpp"
CSymbols * g_pCSymbols;

#include "ashexout.hpp"
#include "asparse.hpp"

#define POSTFIX
#include "cpostfix.hpp"
CPostfix * g_pCPostfix;

#include "aseval.hpp"
CEval * g_pCEval;

#include "asomfgen.hpp"
COmfGen * g_pCOmfGen;

#include "asresolv.hpp"		// Expression and symbol resolvers
#include "asmultip.hpp"		// parse multiple parameters (csv)
#include "asdecdir.hpp"		// Decode directives
#include "asdec80.hpp"		// Decode 8080 operation codes
#include "asdec85.hpp"		// Decode 8085 operation codes
#include "asdec65.hpp"		// Decode 6502 operation codes
#include "asdec68k.hpp"		// Decode 68k  operation codes
#include "asdecz80.hpp"		// Decode Z-80 operation codes
#include "asdec20.hpp"		// Decode 1620 operation codes
#include "asouterr.hpp"
#include "asouthex.hpp"
#include "asoutlst.hpp"
#include "asoutwrn.hpp"


int main(int argc,char **argv)
{
	Version(argv[0]);
	strcpy(g_szArgv0,argv[0]);
        sprintf(g_szAssembleCpp,"%s %s %s",__FILE__,__TIME__,__DATE__);

	if(2 > argc) {
		printf("usage - %s <progname>\n",argv[0]);
		printf("example - %s testfile\n",argv[0]);	
		exit(EXIT_FAILURE);
	}

//	ini_read(argv[0],"Debug",argv[1]);
//	printf("g_szIniValue is %s\n",g_szIniValue);

	g_bPass1 = FALSE;
	g_bPass2 = FALSE;

	// Create an instance of the expression evaluation object
	g_pCEval = new CEval();

	// set default radices to decimal for all precisions
	strcpy(g_szRadixFormat8, g_szRadixFormat8Decimal );
	strcpy(g_szRadixFormat16,g_szRadixFormat16Decimal);
	strcpy(g_szRadixFormat32,g_szRadixFormat32Decimal);
	strcpy(g_szRadixFormat64,g_szRadixFormat64Decimal);
	strcpy(g_szListRadix,    g_szListRadixHex);

	// take provided program name an add source extension
	strcpy(g_szFileNameASM,argv[1]); strcat(g_szFileNameASM,".asm");

	// take provided program name and add listing extension
	strcpy(g_szFileNameLST,argv[1]); strcat(g_szFileNameLST,".lst");

	// save name for listing header
	strcpy(g_szProgram,g_szFileNameLST);
	
	// create logfile name
	strcpy(g_szFileNameLOG,argv[1]); strcat(g_szFileNameLOG,".log");
	
	// create hexfile name
	strcpy(g_szFileNameHEX,argv[1]); strcat(g_szFileNameHEX,".hex");

	// create binary file name
	strcpy(g_szFileNameBIN,argv[1]); strcat(g_szFileNameBIN,".bin");

	// create export file name
	strcpy(g_szFileNameEXP,argv[1]); strcat(g_szFileNameEXP,".exp");

	g_pCOmfGen = new COmfGen(argv[1]);
		
	g_iVerbosity = DEFAULT_VERBOSITY;

	g_pCSource1 = new CSource();
	g_iRc = g_pCSource1->srcopen(g_szFileNameASM); 
	if(EXIT_FAILURE == g_iRc) {
		printf("Sorry, cannot find source file %s\n",g_szFileNameASM);
		exit(EXIT_FAILURE);
	}

	printf("Assembling %s\n",g_szFileNameASM);

	g_flst = fopen(g_szFileNameLST,"w");
	if(NULL == g_flst) {
		printf("Sorry, can't open listing file %s\n",g_szFileNameLST);
		exit(EXIT_FAILURE);
	}

	g_flog = fopen(g_szFileNameLOG,"w");
	if(NULL == g_flog) {
		printf("Sorry, can't open log file %s\n",g_szFileNameLOG);
		fclose(g_flst); exit(EXIT_FAILURE);
	}

	g_fhex = fopen(g_szFileNameHEX,"w");
	if(NULL == g_fhex) {
		printf("Sorry, can't open hex file %s\n",g_szFileNameHEX);
		fclose(g_flst); fclose(g_flog); exit(EXIT_FAILURE);
	}

	g_pCSymbols = new CSymbols(argv[1]);
	g_pCSymbols->mynamespace("default");

	strcpy(g_szTitle,"Vintage Modern Assembler Plus Tools");
	sprintf(g_szSubttl,"Copyright (C) 20%d Douglas Goodall.",RMJ);
	strcpy(g_szSep,"  ");

	g_iPageLength = LOCAL_DEFAULT_PAGELENGTH;	
	g_iPageWidth  = LOCAL_DEFAULT_PAGEWIDTH;

	g_iPageNumber = 1;	


	g_pCSymbols->add("pagelgth",TYPE_U16,(unsigned int)g_iPageLength);
	g_pCSymbols->add("pagewdth",TYPE_U16,(unsigned int)g_iPageWidth);

	g_pCSymbols->add("ldefpgln",TYPE_U16,
		         (unsigned int)LOCAL_DEFAULT_PAGELENGTH);
	g_pCSymbols->add("ldefpgwd",TYPE_U16,
			 (unsigned int)LOCAL_DEFAULT_PAGEWIDTH);

	g_pCSymbols->add("assemble",TYPE_META,
			(unsigned char *)argv[0]);
	g_pCSymbols->add("program",TYPE_META,
			(unsigned char *)argv[1]);

	g_pCSymbols->add("username",TYPE_META,
			(unsigned char *)version.getuser());
        g_pCSymbols->add("machtype",TYPE_META,
                        (unsigned char *)version.getmachtype());
        g_pCSymbols->add("pwd",TYPE_META,
                        (unsigned char *)version.getpwd());
        
	ini_read(argv[0],"Env","HOSTNAME");
	if(0 < strlen(g_szIniValue)) {
		g_pCSymbols->add("hostname",TYPE_META,
             		        (unsigned char *)g_szIniValue);
	}

        ini_read(argv[0],"Env","HOSTTYPE");
        if(0 < strlen(g_szIniValue)) {
                g_pCSymbols->add("hosttype",TYPE_META,
                                (unsigned char *)g_szIniValue);
        }


	TRACE("starting pass1");
	g_iSegment = SEG_VAGUE;

	// Make the postfix part of the expression evaluation
	// engine available. 
        g_pCPostfix = new CPostfix(POSTFIX_NO_DEBUG);

	g_bPass1 = TRUE;

	fprintf(g_flog,"Start of pass one\n");

	printf("Pass One");

	// This program counter, should start at 0
	g_iPc = 0;
	
	g_bEndFound = FALSE;

	// Get the first line of the source program	
	g_p = g_pCSource1->srcgets();
	while(NULL != g_p) {
                strcpy(g_szBuffer,g_p);

		g_iSourceLevel = g_pCSource1->srcgetlevel();
		
		// Remove the trailing newline
		// left there by the fgets
		g_szBuffer[strlen(g_szBuffer)-1] = 0;

		// Save the raw input line before parsing
		strcpy(g_szRawLine,g_szBuffer);
		
		// Set default linetype to error in the
		// expectation that it will be changed
		// back by the parser when code is recognized.
		g_iLineType = TYPE_ERR;		// This is an enum
		g_iErrorNo  = ERROR_UNKOP;		// This is a bitfield
		g_iWarningNo  = WARNING_NONE;	// This is a bitfield

		// Assume to begin with no label, 
		// op, parm, or comment
		g_bLabel    = FALSE;
		g_bOpcode   = FALSE;
		g_bParms    = FALSE;
		g_bComments = FALSE;

		asparse();

		// what a workhorse this clump of code is :-)
		TRACE("adding label if present");
		if( (0 != strlen(g_szLabel))       && 
		    (0 != strncmp("EQU",g_szOpcode,3)) &&
		    (0 != strncmp("equ",g_szOpcode,3)) ) { 
		  g_pCSymbols->add(g_szLabel,TYPE_U8, (unsigned char)g_iPc);
		  g_pCSymbols->add(g_szLabel,TYPE_U16,(unsigned int )g_iPc);
		  g_pCSymbols->add(g_szLabel,TYPE_U32,(unsigned long)g_iPc);
		  g_pCSymbols->add(g_szLabel,TYPE_U64,(unsigned long long)g_iPc);
		  g_bU8  = TRUE;
		  g_bU16 = TRUE;
		  g_bU32 = TRUE;
		  g_bU64 = TRUE;
		}

		decode_directives();
		if(TYPE_ERR == g_iLineType) {
			switch(g_iProc) {
				case PROC_8080:	 decode_8080();  break;
				case PROC_8085:  decode_8085();  break;
				case PROC_6502:  decode_6502();  break;
				case PROC_68000: decode_68000(); break;
				case PROC_Z80:   decode_Z80();   break;
				case PROC_1620:	 decode_1620();  break;
			}
		}
		//not needed in pass one
		//#include "asoutlst.hpp"
		//#include "asouthex.hpp"
		//#include "asouterr.hpp"
		//#include "asooutwrn.hpp"

		// Bump the program counter by the number
		// of g_ucBytes generated by the current instruction
		g_iPc += g_iBytesIndex;

		// Fetch the next line if it exists,
		// then go back to the beginning of the while
		if(TRUE == g_bEndFound) {
			g_p = NULL;
		} else {
			g_p = g_pCSource1->srcgets();
		}
	};
	delete g_pCSource1;
	delete g_pCPostfix;

	g_bPass1 = FALSE;
	fprintf(g_flog,"End of pass one\n");

        //---------------------------------------------------

/*
	fprintf(g_flst,"%s",g_szProgram);
	// Insert needed spaces before page number field
	for(int i=0;i<g_iSpaces;i++) {
		fprintf(g_flst," ");
	}
	fprintf(g_flst,"Page %d %s Ver of %s %s",
		g_iPageNumber++,argv[0],__DATE__,__TIME__);
	fprintf(g_flst,"\n%s",g_szTitle);
	fprintf(g_flst,"\n%s",g_szSubttl);
*/
	TRACE("starting pass2");

	g_iSegment = SEG_VAGUE;

	// in case the namespace was changed in pass1
        g_pCSymbols->mynamespace("default");

	g_bPass2 = TRUE;
        g_pCPostfix = new CPostfix(POSTFIX_NO_DEBUG);

	g_pCSource2 = new CSource();
	g_pCSource2->srcopen(g_szFileNameASM);

//	printf("Pass2 Source file open, level %d line %d\n",
//		g_pCSource2->srcgetlevel(),g_pCSource2->srcgetlineno()+1);

	//---------------------------------------------------

	fprintf(g_flog,"Start of pass two\n");
	printf("\nPass Two\n");

	if(TRUE == g_bExported) {
        	g_fexp = fopen(g_szFileNameEXP,"w");
        	if(NULL == g_fexp) {
                	printf("Sorry, can't open exp file %s\n",
				g_szFileNameEXP);
                	fclose(g_fhex); fclose(g_flst); fclose(g_flog);
                	exit(EXIT_FAILURE);
        	}
		fprintf(g_fexp,
			"; Symbols exported from %s.asm\n",argv[1]);
	}

	if(TRUE == g_bBinary) {
        	g_pCMemory  = new CMemory(MEMSIZE,g_szFileNameBIN);
	}

	g_iPc = 0;		// program counter starts at 0	
	g_iFileLine = 0;	// file line number (zero rel)
	g_iPageline = 0;	// page line number (zero rel)

	g_bEndFound = FALSE;

	// Get the first line of the source program	
	g_p = g_pCSource2->srcgets();
	while(NULL != g_p) {
		if( TRUE == g_bTypeSource ) {
			if( 1 < g_pCSource2->srcgetlevel() ) {
				if( TRUE == g_bTypeIncludes ) {
					printf("[%d.%d] %s",
			       			g_pCSource2->srcgetlevel(),
			       			g_pCSource2->srcgetlineno(),
			       			g_p);
				}
			} else {
                        	printf("[%d.%d] %s",
                                       g_pCSource2->srcgetlevel(),
                                       g_pCSource2->srcgetlineno(),
                                       g_p);
			}
		}

		// get the include level for the listing file
		g_iSourceLevel = g_pCSource2->srcgetlevel();
		g_iFileLine    = g_pCSource2->srcgetlineno();

		// put the line in the global buffer
		strcpy(g_szBuffer,g_p);

		// Remove the trailing newline
		// left there by the fgets
		g_szBuffer[strlen(g_szBuffer)-1] = 0;

		// Save the raw input line before parsing
		strcpy(g_szRawLine,g_szBuffer);
		
		// Set default linetype to error in the
		// expectation that it will be changed
		// back by the parser when code is recognized.
		g_iLineType = TYPE_ERR;
                g_iErrorNo  = ERROR_UNKOP;
		g_iWarningNo  = WARNING_NONE;

		// Assume to begin with no 
		// label,op,parm,or comment
		g_bLabel    = FALSE;
		g_bOpcode   = FALSE;
		g_bParms    = FALSE;
		g_bComments = FALSE;

		asparse();

                // what a workhorse this clump of code is :-)
                TRACE("adding label if present");
                if( (0 != strlen(g_szLabel)) &&
		    (0 != strncmp("EQU",g_szOpcode,3)) &&
		    (0 != strncmp("equ",g_szOpcode,3)) &&
		    (0 != strncmp("CALC",g_szOpcode,4)) &&
                    (0 != strncmp("calc",g_szOpcode,4)) ) {
                        g_pCSymbols->add(g_szLabel,TYPE_U8, (unsigned char)g_iPc);
                        g_pCSymbols->add(g_szLabel,TYPE_U16,(unsigned int )g_iPc);
                        g_pCSymbols->add(g_szLabel,TYPE_U32,(unsigned long)g_iPc);
                        g_pCSymbols->add(g_szLabel,TYPE_U64,
				   (unsigned long long)g_iPc);
			g_bU8 = TRUE;
			g_bU16 = TRUE;
			g_bU32 = TRUE;
			g_bU64 = TRUE;
                }

                decode_directives();
                if(TYPE_ERR == g_iLineType) {
                        switch(g_iProc) {
                                case PROC_8080:  decode_8080();  break;
                                case PROC_8085:  decode_8085();  break;
                                case PROC_6502:  decode_6502();  break;
                                case PROC_68000: decode_68000(); break;
                                case PROC_Z80:   decode_Z80();   break;
				case PROC_1620:  decode_1620();  break;
                        }
                }

//		#include "asouthex.hpp"	// Output         to hex     file
		asouthex();

//		#include "asoutlst.hpp"	// Output line    to listing file
		asoutlst();

//		#include "asouterr.hpp"	// Output error   to listing file
		asouterr();

//		#include "asoutwrn.hpp"	// Output warning to listing file
		asoutwrn();

                // Bump the program counter by the number
                // of g_ucBytes generated by the current instruction
                g_iPc += g_iBytesIndex;

		if(TRUE == g_bEndFound) {
			g_p = NULL;
		} else {
			g_p = g_pCSource2->srcgets();
		}
		TRACE("end of pass2 while loop");
	};
	delete g_pCSource2;
	delete g_pCPostfix;

	if(TRUE == g_bBinary) {
		if(NULL != g_pCMemory) {
			delete g_pCMemory;
		}
	}

	printf("\n%d warnings\n",g_iWarnings);
	printf("%d errors\n",g_iErrors);
	fprintf(g_flog,"End of pass two\n");

	g_bPass2 = FALSE;

        g_pCSymbols->add("ascalc",TYPE_META,(unsigned char *)szAscalcHpp);
        g_pCSymbols->add("asdec65",TYPE_META,(unsigned char *)szAsdec65Hpp);
        g_pCSymbols->add("asdec68k",TYPE_META,(unsigned char *)szAsdec68kHpp);
        g_pCSymbols->add("asdec80",TYPE_META,(unsigned char *)szAsdec80Hpp);
        g_pCSymbols->add("asdec85",TYPE_META,(unsigned char *)szAsdec85Hpp);
        g_pCSymbols->add("asdecdir",TYPE_META,(unsigned char *)szAsdecdirHpp);
        g_pCSymbols->add("asdecz80",TYPE_META,(unsigned char *)szAsdecz80Hpp);
	g_pCSymbols->add("asdec20",TYPE_META,(unsigned char *)szAsdec20Hpp);
        g_pCSymbols->add("aseval",TYPE_META,(unsigned char *)szAsevalHpp);
        g_pCSymbols->add("ashexout",TYPE_META,(unsigned char *)szAshexoutHpp);
        g_pCSymbols->add("asouterr",TYPE_META,(unsigned char *)szAsouterrHpp);
        g_pCSymbols->add("asouthex",TYPE_META,(unsigned char *)szAsouthexHpp);
        g_pCSymbols->add("asoutlst",TYPE_META,(unsigned char *)szAsoutlstHpp);
        g_pCSymbols->add("asresolv",TYPE_META,(unsigned char *)szAsresolvHpp);
        g_pCSymbols->add("asoutwrn",TYPE_META,(unsigned char *)szAsoutwrnHpp);
	g_pCSymbols->add("asymbols",TYPE_META,(unsigned char *)szAsymbolsHpp);
        g_pCSymbols->add("assemble",TYPE_META,(unsigned char *)szAssembleCpp);
        g_pCSymbols->add("asprint", TYPE_META,(unsigned char *)szAsprintHpp);
        g_pCSymbols->add("asparse", TYPE_META,(unsigned char *)szAsparseHpp);

	// add the symbol table into the listing file
	if(TRUE == g_bSTR) g_pCSymbols->dump(TYPE_STRING,g_flst);
	
	if(TRUE == g_bU8)  g_pCSymbols->dump(TYPE_U8, g_flst);
	if(TRUE == g_bU16) g_pCSymbols->dump(TYPE_U16,g_flst);
	if(TRUE == g_bU32) g_pCSymbols->dump(TYPE_U32,g_flst);
	if(TRUE == g_bU64) g_pCSymbols->dump(TYPE_U64,g_flst);

        if(TRUE == g_bE8)  g_pCSymbols->dump(TYPE_E8, g_flst);
        if(TRUE == g_bE16) g_pCSymbols->dump(TYPE_E16,g_flst);
        if(TRUE == g_bE32) g_pCSymbols->dump(TYPE_E32,g_flst);
        if(TRUE == g_bE64) g_pCSymbols->dump(TYPE_E64,g_flst);

        if(TRUE == g_bP8)  g_pCSymbols->dump(TYPE_P8, g_flst);
        if(TRUE == g_bP16) g_pCSymbols->dump(TYPE_P16,g_flst);
        if(TRUE == g_bP32) g_pCSymbols->dump(TYPE_P32,g_flst);
        if(TRUE == g_bP64) g_pCSymbols->dump(TYPE_P64,g_flst);

	g_pCSymbols->dump(TYPE_META,g_flst);
	
	// Close all the input and output files.	
	if(NULL != g_flog) fclose(g_flog);
	if(NULL != g_flst) {
		fprintf(g_flst,"%c",ASCII_FORMFEED);
		fclose(g_flst);
	}

	// If errors occured, delete the hex file
	if(0 != g_iErrors) {
		sprintf(g_szCommand,"rm -f %s",g_szFileNameHEX);
		system(g_szCommand);
	}

	if(NULL != g_fexp) fclose(g_fexp);


	// this is a good place to consider writing the 
	// public symbols into the object file.
	g_pCOmfGen->genpubs();

	if(FALSE == g_bSaveSymbols) {
		delete g_pCSymbols;
	}

	delete g_pCEval;	// All done with the evaluation object

	delete g_pCOmfGen;
	
	if(0 == g_iErrors) {
		return(EXIT_SUCCESS);
	} else {
		return(EXIT_FAILURE);
	}
}

////////////////////////
// eof - assemble.cpp //
////////////////////////

