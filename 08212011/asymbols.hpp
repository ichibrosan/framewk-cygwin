// $Log: asymbols.hpp,v $
// Revision 1.6  2011/04/14 15:13:09  doug
// get ready for release to wiki and server
//
// Revision 1.5  2011/04/05 10:48:58  doug
// added externals to dump member function
//
// Revision 1.4  2011/04/05 10:08:45  doug
// make some arrangements for externals
//
//
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

static char szAsymbolsHpp[] = "$Id: asymbols.hpp,v 1.6 2011/04/14 15:13:09 doug Exp $";

// 03/12/2011 dwg - The CTOR is passed a domain string which 
// has been the name of the program being assembled (w/out ext).
// I added ".sym" today so that the clean rule of the Makefile
// can remove all symbol directories with "rm -r *.sym".

// 02/21/2011 dwg - added getstr method (tested ok)

// 02/04/2011 dwg - copied from my Borland version

// 01/19/2011 dwg - instead of calling the add member
// function with a void * value, dependent on the type,
// now we are overloading the add function with three
// types of value parameters, char *, unsigned char,
// and unsigned int. This is more straightforward.
// The old add function was having trouble guessing the 
// radix of the numeric contents of the value string.

// 12/30/2010 - added getu16 to support the "jp" g_szOpcode

enum {
	TYPE_ALL,
	TYPE_STRING,
	TYPE_U8,
	TYPE_U16,
	TYPE_U32,
	TYPE_U64,
	TYPE_META,
	TYPE_E8,
	TYPE_E16,
	TYPE_E32,
	TYPE_E64,
	TYPE_P8,
	TYPE_P16,
	TYPE_P32,
	TYPE_P64,
	NUM_TYPES
};

class CSymbols {
	char m_domain[128];
	char m_namespace[128];
public:
	CSymbols(char *);
	void mynamespace(char *);
	int add(char *,int,char *);
	int add(char *,int,unsigned char *);
	int add(char *,int,unsigned char);
	int add(char *,int,unsigned int);
	int add(char *,int,unsigned long);
	int add(char *,int,unsigned long long);
	int del(char *,int);
	int dump(int,FILE *);
	unsigned char getu8( char *,int *);
	unsigned int  getu16(char *,int *);
	unsigned long getu32(char *,int *);
	unsigned long long getu64(char *,int *);

        int gete8(char *,int *);
        int gete16(char *,int *);
        int gete32(char *,int *);
        int gete64(char *,int *);

        int getp8(char *,int *);
        int getp16(char *,int *);
        int getp32(char *,int *);
        int getp64(char *,int *);

	char * getstr(char *,int *);
	char * getmeta(char *,int *);
	~CSymbols();
};

CSymbols::CSymbols(char *mydomain)
{
	assert(mydomain);

	char szCommand[DEFAULT_STRSIZE];
	strcpy(m_domain,mydomain);
	strcat(m_domain,".sym");

//	printf("asymbols: CSymbols::CSymbols(%s) says m_domain is %s\n",
//		mydomain,m_domain);

	sprintf(szCommand,"mkdir %s >assemble.tmp 2>assemble.tmp",m_domain);
	system(szCommand);
	system("rm -f assemble.tmp");
}

void CSymbols::mynamespace(char *ns)
{
	assert(m_domain);
	assert(ns);

	char szDirSpec[DEFAULT_STRSIZE];
	char szCommand[DEFAULT_STRSIZE];

	if(NULL == ns) {
		strcpy(m_namespace,"default.nsp");
	} else {
		strcpy(m_namespace,ns);
		strcat(m_namespace,".nsp");
	}

	strcpy(szDirSpec,m_domain);
	strcat(szDirSpec,"/");
	strcat(szDirSpec,m_namespace);
	sprintf(szCommand,"mkdir %s >assemble.tmp 2>assemble.tmp",szDirSpec);
	system(szCommand);
	system("rm -f assemble.tmp");
}

// TYPE_STRING
int CSymbols::add(char *name,int type,char * value)
{
	char szFilename[128];

	strcpy(szFilename,m_domain);
	strcat(szFilename,"/");
	strcat(szFilename,m_namespace);
	strcat(szFilename,"/");
	strcat(szFilename,name);
	strcat(szFilename,".str");
//	printf("asymbols.hpp: CSymbols::add(%s,%d,%s) "
//	       "says szFilename is %s\n",
//		name,type,value,szFilename);
	FILE * fd = fopen(szFilename,"w");
	assert(NULL != fd);
	fprintf(fd,"%s\n",value);
	fclose(fd);
	return EXIT_SUCCESS;
}

// TYPE_U8
int CSymbols::add(char *name,int type,unsigned char ucValue)
{
	char szFilename[128];
	strcpy(szFilename,m_domain);
	strcat(szFilename,"/");
	strcat(szFilename,m_namespace);
	strcat(szFilename,"/");
	strcat(szFilename,name);
	switch(type) {
		case TYPE_U8: strcat(szFilename,".u8"); g_bU8 = TRUE; break;
		case TYPE_E8: strcat(szFilename,".e8"); g_bE8 = TRUE; break;
		case TYPE_P8: strcat(szFilename,".p8"); g_bP8 = TRUE; break;
	}
	// This helps things work on a system with a case
	// sensitive file system.
	for(int i=0;i<strlen(szFilename);i++) {
		szFilename[i] = tolower(szFilename[i]);
	}
	
	FILE * fd = fopen(szFilename,"w");
	assert(NULL != fd);
	fprintf(fd,"%02X\n",ucValue);
	fclose(fd);
	return EXIT_SUCCESS;
}

// TYPE_U16
int CSymbols::add(char *name,int type,unsigned int uiValue)
{
	char szFilename[128];
	strcpy(szFilename,m_domain);
	strcat(szFilename,"/");
	strcat(szFilename,m_namespace);
	strcat(szFilename,"/");
	strcat(szFilename,name);
	switch(type) {
		case TYPE_U16: strcat(szFilename,".u16"); g_bU16 = TRUE; break;
		case TYPE_E16: strcat(szFilename,".e16"); g_bE16 = TRUE; break;
		case TYPE_P16: strcat(szFilename,".p16"); g_bP16 = TRUE; break;
	}
        for(int i=0;i<strlen(szFilename);i++) {
                szFilename[i] = tolower(szFilename[i]);
        }

	FILE * fd = fopen(szFilename,"w");
	assert(NULL != fd);
	fprintf(fd,"%04X\n",uiValue);
	fclose(fd);
	return EXIT_SUCCESS;
}

// TYPE_U32
int CSymbols::add(char *name,int type,unsigned long ulValue)
{
        char szFilename[128];
        strcpy(szFilename,m_domain);
        strcat(szFilename,"/");
        strcat(szFilename,m_namespace);
        strcat(szFilename,"/");
        strcat(szFilename,name);
	switch(type) {
        	case TYPE_U32: strcat(szFilename,".u32"); g_bU32 = TRUE; break;
		case TYPE_E32: strcat(szFilename,".e32"); g_bE32 = TRUE; break;
		case TYPE_P32: strcat(szFilename,".p32"); g_bP32 = TRUE; break;
	}

        for(int i=0;i<strlen(szFilename);i++) {
                szFilename[i] = tolower(szFilename[i]);
        }

        FILE * fd = fopen(szFilename,"w");
        assert(NULL != fd);
        fprintf(fd,"%08lX\n",ulValue);
        fclose(fd);
        return EXIT_SUCCESS;
}

// TYPE_U64
int CSymbols::add(char *name,int type,unsigned long long ullValue)
{
        char szFilename[128];
        strcpy(szFilename,m_domain);
        strcat(szFilename,"/");
        strcat(szFilename,m_namespace);
        strcat(szFilename,"/");
        strcat(szFilename,name);
	switch(type) {
        	case TYPE_U64: strcat(szFilename,".u64"); g_bU64 = TRUE; break;
		case TYPE_E64: strcat(szFilename,".e64"); g_bE64 = TRUE; break;
		case TYPE_P64: strcat(szFilename,".p64"); g_bP64 = TRUE; break;
	}
        for(int i=0;i<strlen(szFilename);i++) {
                szFilename[i] = tolower(szFilename[i]);
        }

        FILE * fd = fopen(szFilename,"w");
        assert(NULL != fd);
        fprintf(fd,"%16llX\n",ullValue);
        fclose(fd);
        return EXIT_SUCCESS;
}

// TYPE_META
int CSymbols::add(char *name,int type,unsigned char * value)
{
        char szFilename[128];

        strcpy(szFilename,m_domain);
        strcat(szFilename,"/");
        strcat(szFilename,m_namespace);
        strcat(szFilename,"/");
        strcat(szFilename,name);
        strcat(szFilename,".mta");

//      printf("asymbols.hpp: CSymbols::add(%s,%d,%s) "
//             "says szFilename is %s\n",
//              name,type,value,szFilename);

        FILE * fd = fopen(szFilename,"w");
        assert(NULL != fd);
        fprintf(fd,"%s\n",value);
        fclose(fd);
        return EXIT_SUCCESS;
}


int CSymbols::del(char *name,int type)
{
        char szFilename[128];
	char szCommand[128];

        strcpy(szFilename,m_domain);
        strcat(szFilename,"/");
        strcat(szFilename,m_namespace);
        strcat(szFilename,"/");
        strcat(szFilename,name);
	switch(type) {
		case TYPE_STRING: strcat(szFilename,".str"); break;
		case TYPE_U8:     strcat(szFilename,".u8");  break;
		case TYPE_U16:    strcat(szFilename,".u16"); break;
		case TYPE_U32:	  strcat(szFilename,".u32"); break;
		case TYPE_U64:    strcat(szFilename,".u64"); break;
		case TYPE_META:   strcat(szFilename,".mta"); break;
		default:	  assert(1==2);
	}

        for(int i=0;i<strlen(szFilename);i++) {
                szFilename[i] = tolower(szFilename[i]);
        }

	sprintf(szCommand,"rm %s",szFilename);
	system(szCommand);
}

int CSymbols::dump(int type,FILE *fdout)
{
  char szStringBuffer[DEFAULT_STRSIZE];
  unsigned int iValue;
  unsigned long lValue;
  unsigned long long llValue;

  unsigned char u8Buffer;
  unsigned int  u16Buffer;
  unsigned long u32Buffer;
  unsigned long long u64Buffer;

  char szFileSpec[DEFAULT_STRSIZE];

  strcpy(g_szBuffer2,"----------------------------------------------");
  print(fdout);

  char szType[3+1+1];
  switch(type) {

    case TYPE_E8:
      sprintf(g_szBuffer2,"Symbol table external bytes...");
      print(fdout);
      strcpy(szType,".e8"); 
      break;
    case TYPE_E16:
      sprintf(g_szBuffer2,"Symbol table external words...");
      print(fdout);
      strcpy(szType,".e16");
      break;
    case TYPE_E32:
      sprintf(g_szBuffer2,"Symbol table external dwords...");
      print(fdout);
      strcpy(szType,".e32");
      break;
    case TYPE_E64:
      sprintf(g_szBuffer2,"Symbol table external qwords...");
      print(fdout);
      strcpy(szType,".e64");
      break;


    case TYPE_P8:
      sprintf(g_szBuffer2,"Symbol table public bytes...");
      print(fdout);
      strcpy(szType,".p8");
      break;
    case TYPE_P16:
      sprintf(g_szBuffer2,"Symbol table public words...");
      print(fdout);
      strcpy(szType,".p16");
      break;
    case TYPE_P32:
      sprintf(g_szBuffer2,"Symbol table public dwords...");
      print(fdout);
      strcpy(szType,".p32");
      break;
    case TYPE_P64:
      sprintf(g_szBuffer2,"Symbol table public qwords...");
      print(fdout);
      strcpy(szType,".p64");
      break;



    case TYPE_STRING:
			sprintf(g_szBuffer2,"Symbol table string entries...");
			print(fdout);
			strcpy(szType,".str");
			break;
		case TYPE_U8:
			sprintf(g_szBuffer2,"Symbol table byte entries...");
			print(fdout);
			strcpy(szType,".u8");			
			break;
		case TYPE_U16:
			sprintf(g_szBuffer2,"Symbol table word entries...");
			print(fdout);
			strcpy(szType,".u16");
			break;
                case TYPE_U32:
                        sprintf(g_szBuffer2,"Symbol table dword entries...");
                        print(fdout);
                        strcpy(szType,".u32");
                        break;
		case TYPE_U64:
			sprintf(g_szBuffer2,"Symbol table qword entries...");
			print(fdout);
			strcpy(szType,".u64");
			break;
                case TYPE_META:
                        sprintf(g_szBuffer2,"Symbol table meta entries...");
                        print(fdout);
                        strcpy(szType,".mta");
                        break;

	}

	char szDirSpec[128];
	strcpy(szDirSpec,m_domain);
	strcat(szDirSpec,"/");
	strcat(szDirSpec,m_namespace);
        CDir * mydir = new CDir(szDirSpec);
	int rc = mydir->read();
	while(0 == rc) {

		char szFileTemp[128];
		mydir->getname(szFileTemp);
		int index;	
		for(index=0;index<strlen(szFileTemp);index++) {
			if('.' == szFileTemp[index]) {
				break;
			}
		}

		if(0 == strcmp(szType,&szFileTemp[index])) {

			sprintf(szFileSpec,"%s/%s",szDirSpec,szFileTemp);
			FILE * fdin = fopen(szFileSpec,"r");
			assert(fdin);
			fgets(szStringBuffer,sizeof(szStringBuffer),fdin);
			szStringBuffer[strlen(szStringBuffer)-1] = 0;
		
			switch(type) {
				case TYPE_STRING:
					sprintf(g_szBuffer2,
						"%s, \"%s\"",
						szFileTemp,szStringBuffer);
					print(fdout);
					break;



        case TYPE_E8:
                sscanf(szStringBuffer, g_szRadixFormat8Hex,&iValue);
                sprintf(g_szBuffer2, "%s, 0x%02X (%d)",
                        szFileTemp,iValue,iValue);
                print(fdout); break;
        case TYPE_E16:
                sscanf(szStringBuffer, g_szRadixFormat16Hex,&iValue);
                sprintf(g_szBuffer2, "%s, 0x%04X (%d)",
                        szFileTemp,iValue,iValue);
                print(fdout); break;
        case TYPE_E32:
                sscanf(szStringBuffer, g_szRadixFormat32Hex,&lValue);
                        sprintf(g_szBuffer2, "%s, 0x%08lX (%ld)",
                        szFileTemp,lValue,lValue);
                print(fdout); break;
         case TYPE_E64:
                sscanf(szStringBuffer, g_szRadixFormat64Hex, &llValue);
                sprintf(g_szBuffer2, "%s, 0x%017llX (%lld)",
                        szFileTemp,llValue,llValue);
                print(fdout); break;
 
        case TYPE_P8:
                sscanf(szStringBuffer, g_szRadixFormat8Hex,&iValue);
                sprintf(g_szBuffer2, "%s, 0x%02X (%d)",
                        szFileTemp,iValue,iValue);
                print(fdout); break;
        case TYPE_P16:
                sscanf(szStringBuffer, g_szRadixFormat16Hex,&iValue);
                sprintf(g_szBuffer2, "%s, 0x%04X (%d)",
                        szFileTemp,iValue,iValue);
                print(fdout); break;
        case TYPE_P32:
                sscanf(szStringBuffer, g_szRadixFormat32Hex,&lValue);
                        sprintf(g_szBuffer2, "%s, 0x%08lX (%ld)",
                        szFileTemp,lValue,lValue);
                print(fdout); break;
         case TYPE_P64:
                sscanf(szStringBuffer, g_szRadixFormat64Hex, &llValue);
                sprintf(g_szBuffer2, "%s, 0x%017llX (%lld)",
                        szFileTemp,llValue,llValue);
                print(fdout); break;



	case TYPE_U8:
		sscanf(szStringBuffer, g_szRadixFormat8Hex,&iValue);
		sprintf(g_szBuffer2, "%s, 0x%02X (%d)",
			szFileTemp,iValue,iValue);
		print(fdout); break;
	case TYPE_U16:
		sscanf(szStringBuffer, g_szRadixFormat16Hex,&iValue);
		sprintf(g_szBuffer2, "%s, 0x%04X (%d)",
			szFileTemp,iValue,iValue);
		print(fdout); break;
        case TYPE_U32:
                sscanf(szStringBuffer, g_szRadixFormat32Hex,&lValue);
        	        sprintf(g_szBuffer2, "%s, 0x%08lX (%ld)",
                        szFileTemp,lValue,lValue);
                print(fdout); break;
         case TYPE_U64:
                sscanf(szStringBuffer, g_szRadixFormat64Hex, &llValue);
                sprintf(g_szBuffer2, "%s, 0x%017llX (%lld)",
                        szFileTemp,llValue,llValue);
                print(fdout); break;

         case TYPE_META:
                sprintf(g_szBuffer2,
                        "%s, \"%s\"",
                        szFileTemp,szStringBuffer);
                print(fdout);
                break;
				default:
					assert(1==2);
			}
			fclose(fdin);		
		}
		rc = mydir->read();
	}
	delete mydir;
}

unsigned char CSymbols::getu8(char * symbol,int * rc)
{
        char szFileSpec[128];
        char g_szBuffer2[128];
        unsigned int u8Buffer;
        strcpy(szFileSpec,m_domain);
        strcat(szFileSpec,"/");
        strcat(szFileSpec,m_namespace);
        strcat(szFileSpec,"/");
        strcat(szFileSpec,symbol);
        strcat(szFileSpec,".u8");

        for(int i=0;i<strlen(szFileSpec);i++) {
                szFileSpec[i] = tolower(szFileSpec[i]);
        }

        FILE * fd = fopen(szFileSpec,"r");
        if(NULL == fd) {
                *rc = EXIT_FAILURE;
                return NULL;
        }
        fgets(g_szBuffer2,sizeof(g_szBuffer2),fd);
        fclose(fd);
        g_szBuffer2[strlen(g_szBuffer2)-1] = 0;
        sscanf(g_szBuffer2,"%2X",&u8Buffer);

        *rc = (int)EXIT_SUCCESS;
        return u8Buffer;
}

unsigned int CSymbols::getu16(char *symbol,int *rc)
{
	assert(m_domain);
	assert(m_namespace);
	char szFileSpec[128];
	char g_szBuffer2[128];
	unsigned int u16Buffer;
	strcpy(szFileSpec,m_domain);
	strcat(szFileSpec,"/");
	strcat(szFileSpec,m_namespace);
	strcat(szFileSpec,"/");
	strcat(szFileSpec,symbol);
	strcat(szFileSpec,".u16");

        for(int i=0;i<strlen(szFileSpec);i++) {
                szFileSpec[i] = tolower(szFileSpec[i]);
        }

	FILE * fd = fopen(szFileSpec,"r");
	if(NULL == fd) {
		*rc = EXIT_FAILURE;
		return 0;
	}
	fgets(g_szBuffer2,sizeof(g_szBuffer2),fd);
	fclose(fd);
	sscanf(g_szBuffer2,"%4X",&u16Buffer);
	*rc = (int)EXIT_SUCCESS;	
	return u16Buffer;
}

unsigned long CSymbols::getu32(char *symbol,int *rc)
{
        assert(m_domain);
        assert(m_namespace);
        char szFileSpec[128];
        char g_szBuffer2[128];
        unsigned int u32Buffer;
        strcpy(szFileSpec,m_domain);
        strcat(szFileSpec,"/");
        strcat(szFileSpec,m_namespace);
        strcat(szFileSpec,"/");
        strcat(szFileSpec,symbol);
        strcat(szFileSpec,".u32");

        for(int i=0;i<strlen(szFileSpec);i++) {
                szFileSpec[i] = tolower(szFileSpec[i]);
        }

        FILE * fd = fopen(szFileSpec,"r");
        if(NULL == fd) {
		assert(NULL != fd);
                *rc = EXIT_FAILURE;
                return 0;
        }
        fgets(g_szBuffer2,sizeof(g_szBuffer2),fd);
        fclose(fd);
        sscanf(g_szBuffer2,g_szRadixFormat32Hex,&u32Buffer);
        *rc = (int)EXIT_SUCCESS;
        return u32Buffer;
}

unsigned long long CSymbols::getu64(char *symbol,int *rc)
{
        assert(m_domain);
        assert(m_namespace);
        char szFileSpec[128];
        char g_szBuffer2[128];
        unsigned long long u64Buffer;
        strcpy(szFileSpec,m_domain);
        strcat(szFileSpec,"/");
        strcat(szFileSpec,m_namespace);
        strcat(szFileSpec,"/");
        strcat(szFileSpec,symbol);
        strcat(szFileSpec,".u64");

        for(int i=0;i<strlen(szFileSpec);i++) {
                szFileSpec[i] = tolower(szFileSpec[i]);
        }

        FILE * fd = fopen(szFileSpec,"r");
        if(NULL == fd) {
                *rc = EXIT_FAILURE;
                return 0;
        }
        fgets(g_szBuffer2,sizeof(g_szBuffer2),fd);
        fclose(fd);
        sscanf(g_szBuffer2,g_szRadixFormat64Hex,&u64Buffer);
        *rc = (int)EXIT_SUCCESS;
        return u64Buffer;
}

char * CSymbols::getstr(char *symbol,int *rc)
{ 	char szFileSpec[128];
	char g_szBuffer2[128];
	unsigned int u16Buffer;
	strcpy(szFileSpec,m_domain);
	strcat(szFileSpec,"/");
	strcat(szFileSpec,m_namespace);
	strcat(szFileSpec,"/");
	strcat(szFileSpec,symbol);
	strcat(szFileSpec,".str");
        for(int i=0;i<strlen(szFileSpec);i++) {
                szFileSpec[i] = tolower(szFileSpec[i]);
        }
	FILE * fd = fopen(szFileSpec,"r");
	if(NULL == fd) {
		*rc = EXIT_FAILURE;
		return NULL;
	}
	fgets(g_szBuffer2,sizeof(g_szBuffer2),fd);
	fclose(fd);
	g_szBuffer2[strlen(g_szBuffer2)-1] = 0;
	strcpy(g_szStrBuffer,g_szBuffer2);
	*rc = (int)EXIT_SUCCESS;	
	return g_szStrBuffer;
}

char * CSymbols::getmeta(char *symbol,int *rc)
{       char szFileSpec[128];
        char g_szBuffer2[128];
        unsigned int u16Buffer;
        strcpy(szFileSpec,m_domain);
        strcat(szFileSpec,"/");
        strcat(szFileSpec,m_namespace);
        strcat(szFileSpec,"/");
        strcat(szFileSpec,symbol);
        strcat(szFileSpec,".mta");
        for(int i=0;i<strlen(szFileSpec);i++) {
                szFileSpec[i] = tolower(szFileSpec[i]);
        }
        FILE * fd = fopen(szFileSpec,"r");
        if(NULL == fd) {
                *rc = EXIT_FAILURE;
                return NULL;
        }
        fgets(g_szBuffer2,sizeof(g_szBuffer2),fd);
        fclose(fd);
        g_szBuffer2[strlen(g_szBuffer2)-1] = 0;
        strcpy(g_szStrBuffer,g_szBuffer2);
        *rc = (int)EXIT_SUCCESS;
        return g_szStrBuffer;
}



int CSymbols::gete8(char * symbol,int * rc)
{
        char szFileSpec[128];
        char g_szBuffer2[128];
        strcpy(szFileSpec,m_domain);
        strcat(szFileSpec,"/");
        strcat(szFileSpec,m_namespace);
        strcat(szFileSpec,"/");
        strcat(szFileSpec,symbol);
        strcat(szFileSpec,".e8");
        for(int i=0;i<strlen(szFileSpec);i++) {
                szFileSpec[i] = tolower(szFileSpec[i]);
        }
        FILE * fd = fopen(szFileSpec,"r");
        if(NULL == fd) {
                *rc = EXIT_FAILURE;
                return EXIT_FAILURE;
        }
        fclose(fd);
        *rc = (int)EXIT_SUCCESS;
        return EXIT_SUCCESS;
}

int CSymbols::gete16(char *symbol,int *rc)
{
	char szFileSpec[128];
	char g_szBuffer2[128];
	strcpy(szFileSpec,m_domain);
	strcat(szFileSpec,"/");
	strcat(szFileSpec,m_namespace);
	strcat(szFileSpec,"/");
	strcat(szFileSpec,symbol);
	strcat(szFileSpec,".e16");
        for(int i=0;i<strlen(szFileSpec);i++) {
                szFileSpec[i] = tolower(szFileSpec[i]);
        }
	FILE * fd = fopen(szFileSpec,"r");
	if(NULL == fd) {
		*rc = EXIT_FAILURE;
		return EXIT_FAILURE;
	}
	fclose(fd);
	*rc = (int)EXIT_SUCCESS;	
	return EXIT_SUCCESS;
}

int CSymbols::gete32(char *symbol,int *rc)
{
        char szFileSpec[128];
        char g_szBuffer2[128];
        strcpy(szFileSpec,m_domain);
        strcat(szFileSpec,"/");
        strcat(szFileSpec,m_namespace);
        strcat(szFileSpec,"/");
        strcat(szFileSpec,symbol);
        strcat(szFileSpec,".e32");
        for(int i=0;i<strlen(szFileSpec);i++) {
                szFileSpec[i] = tolower(szFileSpec[i]);
        }
        FILE * fd = fopen(szFileSpec,"r");
        if(NULL == fd) {
		assert(NULL != fd);
                *rc = EXIT_FAILURE;
                return EXIT_FAILURE;
        }
        fclose(fd);
        *rc = (int)EXIT_SUCCESS;
        return EXIT_SUCCESS;
}

int CSymbols::gete64(char *symbol,int *rc)
{
        char szFileSpec[128];
        char g_szBuffer2[128];
        strcpy(szFileSpec,m_domain);
        strcat(szFileSpec,"/");
        strcat(szFileSpec,m_namespace);
        strcat(szFileSpec,"/");
        strcat(szFileSpec,symbol);
        strcat(szFileSpec,".e64");
        for(int i=0;i<strlen(szFileSpec);i++) {
                szFileSpec[i] = tolower(szFileSpec[i]);
        }
        FILE * fd = fopen(szFileSpec,"r");
        if(NULL == fd) {
                *rc = EXIT_FAILURE;
                return EXIT_FAILURE;
        }
        fclose(fd);
        *rc = (int)EXIT_SUCCESS;
        return EXIT_SUCCESS;
}





int CSymbols::getp8(char * symbol,int * rc)
{
        char szFileSpec[128];
        char g_szBuffer2[128];
        strcpy(szFileSpec,m_domain);
        strcat(szFileSpec,"/");
        strcat(szFileSpec,m_namespace);
        strcat(szFileSpec,"/");
        strcat(szFileSpec,symbol);
        strcat(szFileSpec,".p8");
        for(int i=0;i<strlen(szFileSpec);i++) {
                szFileSpec[i] = tolower(szFileSpec[i]);
        }
        FILE * fd = fopen(szFileSpec,"r");
        if(NULL == fd) {
                *rc = EXIT_FAILURE;
                return EXIT_FAILURE;
        }
        fclose(fd);
        *rc = (int)EXIT_SUCCESS;
        return EXIT_SUCCESS;
}

int CSymbols::getp16(char *symbol,int *rc)
{
	char szFileSpec[128];
	char g_szBuffer2[128];
	strcpy(szFileSpec,m_domain);
	strcat(szFileSpec,"/");
	strcat(szFileSpec,m_namespace);
	strcat(szFileSpec,"/");
	strcat(szFileSpec,symbol);
	strcat(szFileSpec,".p16");
        for(int i=0;i<strlen(szFileSpec);i++) {
                szFileSpec[i] = tolower(szFileSpec[i]);
        }
	FILE * fd = fopen(szFileSpec,"r");
	if(NULL == fd) {
		*rc = EXIT_FAILURE;
		return EXIT_FAILURE;
	}
	fclose(fd);
	*rc = (int)EXIT_SUCCESS;	
	return EXIT_SUCCESS;
}

int CSymbols::getp32(char *symbol,int *rc)
{
        char szFileSpec[128];
        char g_szBuffer2[128];
        strcpy(szFileSpec,m_domain);
        strcat(szFileSpec,"/");
        strcat(szFileSpec,m_namespace);
        strcat(szFileSpec,"/");
        strcat(szFileSpec,symbol);
        strcat(szFileSpec,".p32");
        for(int i=0;i<strlen(szFileSpec);i++) {
                szFileSpec[i] = tolower(szFileSpec[i]);
        }
        FILE * fd = fopen(szFileSpec,"r");
        if(NULL == fd) {
		assert(NULL != fd);
                *rc = EXIT_FAILURE;
                return EXIT_FAILURE;
        }
        fclose(fd);
        *rc = (int)EXIT_SUCCESS;
        return EXIT_SUCCESS;
}

int CSymbols::getp64(char *symbol,int *rc)
{
        char szFileSpec[128];
        char g_szBuffer2[128];
        strcpy(szFileSpec,m_domain);
        strcat(szFileSpec,"/");
        strcat(szFileSpec,m_namespace);
        strcat(szFileSpec,"/");
        strcat(szFileSpec,symbol);
        strcat(szFileSpec,".p64");
        for(int i=0;i<strlen(szFileSpec);i++) {
                szFileSpec[i] = tolower(szFileSpec[i]);
        }
        FILE * fd = fopen(szFileSpec,"r");
        if(NULL == fd) {
                *rc = EXIT_FAILURE;
                return EXIT_FAILURE;
        }
        fclose(fd);
        *rc = (int)EXIT_SUCCESS;
        return EXIT_SUCCESS;
}




CSymbols::~CSymbols()
{ 
	if(FALSE == g_bDebug) {
		sprintf(g_szCommand,"rm -r %s",m_domain);
		system(g_szCommand);
	}
}

///////////////////////
// eof - symbols.hpp //
///////////////////////

