// $Log: asmall.cpp,v $
// Revision 1.3  2011/04/14 15:13:09  doug
// get ready for release to wiki and server
//
//

// ---------------------------------------------------
// asmall.cpp   21-Feb-11   Running on Mac OS X 10.6.6
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
//#define __TRACE

static char szAsmallCpp[] = "$Id: asmall.cpp,v 1.3 2011/04/14 15:13:09 doug Exp $";

#include "asdefs.hpp"
#define DWGALLOC
#define INIBIND
#define DIRCLASS
#include "includes.hpp"

#define BUFFERSIZE 2048
char szBinBuffer[BUFFERSIZE];
char szHppBuffer[BUFFERSIZE];
char szAsmBuffer[BUFFERSIZE];
char szHexBuffer[BUFFERSIZE];
char szIncBuffer[BUFFERSIZE];
char szSymBuffer[BUFFERSIZE];

#define FILENAMESIZE 128
char  szMkFileName[FILENAMESIZE];
char szSrcFileName[FILENAMESIZE];
char szTgtFileName[FILENAMESIZE];
char szHexFileName[FILENAMESIZE];
char szAsmFileName[FILENAMESIZE];

char szMachtype[64];
char szTimeDate[64];

int getdate()
{
	TRACE("getdate() starting");
	char szLocal[64];
	system("date > date.tmp");
	FILE * fd = fopen("date.tmp","r");
	if(NULL == fd) {
		printf("Sorry, could not open date.tmp for input\n");
		exit(EXIT_FAILURE);
	}
	fgets(szLocal,sizeof(szLocal),fd);
	fclose(fd);
	system("rm -f date.tmp");
	strcpy(szTimeDate,szLocal);
	return EXIT_SUCCESS;
}

int makemake(char *szFilename,FILE *mfp)
{
  TRACE("makemake() starting");
  TRACE(szFilename);

  char g_szBuffer2[128];
  char szRoot[128];

  strcpy(szRoot,szFilename);
  szRoot[strlen(szRoot)-4] = 0;

  strcpy(szMkFileName,"mkfiles/");
  strcat(szMkFileName,szFilename);
  szMkFileName[strlen(szMkFileName)-4] = 0;
  strcat(szMkFileName,".mak");

  strcpy(szSrcFileName,szFilename);
  szSrcFileName[strlen(szSrcFileName)-4] = 0;
  strcat(szSrcFileName,".asm");

  strcpy(szHexFileName,szFilename);
  szHexFileName[strlen(szHexFileName)-4] = 0;
  strcat(szHexFileName,".hex");

  FILE * fp = fopen(szMkFileName,"w");
  if(NULL == fp) {
    printf("Error: cannot open %s for output\n",szMkFileName);
    exit(EXIT_FAILURE);
  }

  char szProg[128];
  strcpy(szProg,szMkFileName);

  fprintf(fp,"# ---------------------------------------------------\n");
  fprintf(fp,"# %s  Ver %2d.%02d.%02d%c  %s\n",
	szProg,RMJ,RMN,RUP,'a'+RTP,szMachtype);
  fprintf(fp,"# Serial No. 2011-1042-654321    All Rights Reserved.\n");
  fprintf(fp,"# Copyright (C) 2011 Douglas Goodall,  United States.\n");
  fprintf(fp,"# ---------------------------------------------------\n");


  fprintf(fp,"# %s autogenerated by %s \n# %s",
	  szMkFileName,__FILE__,szTimeDate);
  fprintf(fp,"# Copyright (c)2011 Douglas Goodall. Rights Reserved.\n\n");
  fprintf(fp,"AS = ../assemble\n");
  fprintf(fp,"\n");
  fprintf(fp,"INCFILES  = %s\n",szIncBuffer);
  fprintf(fp,"\n");
  fprintf(fp,"%s:\t%s $(INCFILES) $(AS) ",szHexFileName,szSrcFileName);
  fprintf(fp,"\n");
  fprintf(fp,"\t$(AS) %s \n",szRoot);
  fprintf(fp,"\n");
  fprintf(fp,"clean:\n");
  fprintf(fp,"\trm -f *.ini *.exp *.obj *.bin %s *.lst *.log *.hex\n",
	szTgtFileName);
  fprintf(fp,"\n");
  fprintf(fp,"# eof - %s\n",szMkFileName);
  fclose(fp);

  return(EXIT_SUCCESS);
}



int main(int argc,char **argv)
{
  TRACE("main() starting");

  char szMkFileName[128];
  char szSrcFileName[128];
  char szTgtFileName[128];
  char szSrcRoot[128];

  TRACE("clearing buffers");
  memset(szBinBuffer,0,sizeof(szBinBuffer));
  memset(szHppBuffer,0,sizeof(szHppBuffer));
  memset(szAsmBuffer,0,sizeof(szAsmBuffer));
  memset(szHexBuffer,0,sizeof(szHexBuffer));
  memset(szIncBuffer,0,sizeof(szIncBuffer));
  memset(szSymBuffer,0,sizeof(szSymBuffer));

  getdate();

//This version worked on Mac OS X
//char g_szBuffer2[__DARWIN_MAXPATHLEN];

  // This version works anywhere
  char g_szBuffer2[1024];

  Version(argv[0]);

  TRACE("doing asm scan");
  FILE * viasm = fopen("editasm","w");
  fprintf(viasm,"# editasm - generated by %s\n",argv[0]);
  CDir *  dir1 = new CDir(".");
  int rc = dir1->read();
  while(EXIT_SUCCESS == rc) {
    dir1->getname(g_szBuffer2);
    if(DT_REG == dir1->gettype()) {
      if(4 < strlen(g_szBuffer2)) {
	if(0 == strcmp(".asm",&g_szBuffer2[strlen(g_szBuffer2)-4])) {
		fprintf(viasm,"vi %s\n",g_szBuffer2);
		strcpy(szTgtFileName,g_szBuffer2);
		szTgtFileName[strlen(szTgtFileName)-4] = 0;
		strcat(szHexBuffer,szTgtFileName);
		strcat(szHexBuffer,".hex ");
	}
      }
    }
    rc = dir1->read();
  }
  delete dir1;
  fclose(viasm);
  system("chmod +x editasm");
  TRACE("done with dir1");

  TRACE("doing inc scan");

  FILE * vifd = fopen("editinc","w");
  fprintf(vifd,"# editinc - generated by %s\n",argv[0]);
  CDir *  dir2 = new CDir(".");
  assert(dir2);
  TRACE("calling dir2 read");
  int rc2= dir2->read();
  while(EXIT_SUCCESS == rc2){
    TRACE("calling dir2 getname");
    dir2->getname(g_szBuffer2);
    TRACE(g_szBuffer2);
    TRACE("calling dir2 gettype");
    if(DT_REG == dir2->gettype()) {
      TRACE("is regular file");
      if(4 < strlen(g_szBuffer2)) {
        TRACE("is long enough");
        if(0 == strcmp(".inc",&g_szBuffer2[strlen(g_szBuffer2)-4])) {
                TRACE("is a .inc");
		fprintf(vifd,"vi %s\n",g_szBuffer2);
		TRACE("copy to szTgtFileName");
                strcpy(szTgtFileName,g_szBuffer2);
		TRACE("trimming extension");
                szTgtFileName[strlen(szTgtFileName)-4] = 0;
		TRACE("appending inc buffer");
                strcat(szIncBuffer,szTgtFileName);
                strcat(szIncBuffer,".inc ");
        }
      }
    }
    rc2 = dir2->read();
  }
  delete dir2;
  fclose(vifd);
  system("chmod +x editinc");
  TRACE("done with dir2");

  TRACE("writing main makefile");
  FILE * mfp = fopen("Makefile","w");
  fprintf(mfp,"# ---------------------------------------------------\n");
  fprintf(mfp,"# Makefile     Ver %2d.%02d.%02d%c  %s\n",
        RMJ,RMN,RUP,'a'+RTP,version.getmachtype());
  fprintf(mfp,"# Serial No. 2011-1042-654321    All Rights Reserved.\n");
  fprintf(mfp,"# Copyright (C) 2011 Douglas Goodall,  United States.\n");
  fprintf(mfp,"# ---------------------------------------------------\n");


  fprintf(mfp,"# Created by %s  %s\n\n", __FILE__,szTimeDate);
 
//  fprintf(mfp,"AS = ../assemble\n");
  fprintf(mfp,"AS = ./assemble\n");

  fprintf(mfp,"\n");

  fprintf(mfp,"HEXFILES = %s\n",szHexBuffer);
  fprintf(mfp,"\n");

  fprintf(mfp,"INCFILES = %s\n",szIncBuffer);
  fprintf(mfp,"\n");

  fprintf(mfp,"all:\t$(HEXFILES)\n");
  fprintf(mfp,"\n\n");

  TRACE("doing main asm scan");
  CDir *  dir3 = new CDir(".");
  int rc3 = dir3->read();
  while(EXIT_SUCCESS == rc3) {
    dir3->getname(g_szBuffer2);
    if(DT_REG == dir3->gettype()) {
      if(4 < strlen(g_szBuffer2)) {
	if(0 == strcmp(".asm",&g_szBuffer2[strlen(g_szBuffer2)-4])) {
		TRACE("calling makemake");
		makemake(g_szBuffer2,mfp);
		TRACE("returned from makemake");
		
	 	strcpy(szHexFileName,g_szBuffer2);
		szHexFileName[strlen(szHexFileName)-4] = 0;
		//
		// collect names of symbol directories
		strcat(szSymBuffer,szHexFileName);
		strcat(szSymBuffer," ");
		//
		strcat(szHexFileName,".hex");

		strcpy(szSrcRoot,g_szBuffer2);
		szSrcRoot[strlen(szSrcRoot)-4] = 0;
	 
  		fprintf(mfp,"%s:\t%s $(AS) Makefile $(INCFILES) ",
			szHexFileName,g_szBuffer2);
		fprintf(mfp,"\n");
  		
		fprintf(mfp,"\t$(AS) %s ",szSrcRoot);
		fprintf(mfp,"\n\n");
	}
      }
    }
    rc3 = dir3->read();
  }
  fprintf(mfp,"clean:\n");
  fprintf(mfp,"\trm -f *.exp *.obj *.bin editthem *.lst *.log *.hex \n");
  fprintf(mfp,"\trm -r -f %s *.ini *.sym\n",szSymBuffer);
  fprintf(mfp,"\n");
  fprintf(mfp,"# eof - Makefile\n");
  fclose(mfp);
  delete dir3;
  TRACE("done with dir3");

  if(NULL != argv[1]) {
    char szCommand[128];
    sprintf(szCommand,"make %s",argv[1]);
    system(szCommand);
  } else {
    system("make");
  }

  return EXIT_SUCCESS;
}

//////////////////////
// eof - asmall.cpp //
//////////////////////

