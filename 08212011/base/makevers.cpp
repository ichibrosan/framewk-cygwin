// $Log: makevers.cpp,v $
// Revision 1.3  2011/04/14 15:13:09  doug
// get ready for release to wiki and server
//
//

// ---------------------------------------------------
// makevers.cpp 22-Feb-11   Running on Mac OS X 10.6.6
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

static char szMakeversCpp[] = "$Id: makevers.cpp,v 1.3 2011/04/14 15:13:09 doug Exp $";


//
// 02192011 dwg - enhance for Mac OS X or Linux

// 02012011 dwg - Add -n to copy command so no files will 
// be accidentally overwritten by the copylast script. It
// shouldn't happen because of the Makefile test, but just
// in case.

// The function of the "makevers" program is to primarily 
// assure the existence of the "version.hpp" which is used
// by all other programs in the build. It also places a
// the "copylast" script in the build's bin directory in 
// case mktoday decides the new directory needs to be 
// populated.

// This is the only program in the VMAPT that doesn't use
// the generic "includes.hpp". It can't because the
// "version.hpp" may not exist yet.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// User LINUX and MACOSX frm portab.hpp
#include "portab.hpp"

// Use CEnvironment::getmachtype() and getuser()
#include "environ.hpp"

//        1         2         3         4         5         6         7
//234567890123456789012345678901234567890123456789012345678901234567890123456789

//           1         2
// 0123456789012345678901234567
// Sat Jan 29 14:43:54 PST 2011
char g_szBuffer2[256];

int main(int argc,char **argv)
{
	char szMonth[4];
	char szDay[4];
	char szYear[5];
	char szHour[3];
	int iMonth;
	char szDirSpec[128];
	char szCommand[128];

	// makevers has to use CEnvironment because
	// the version support cannot be used before
	// version.hpp is created. CEnv... uses grab
	char szMachtype[128];
	char szUid[16];
	char szUser[32];
	CEnvironment * env = new CEnvironment();
	strcpy(szMachtype,env->getmachtype());
	strcpy(szUid,     env->getuid());
	strcpy(szUser,    env->getuser());

	system("date > date.tmp");
	FILE * fd = fopen("date.tmp","r");
	if(NULL == fd) {
		printf("Sorry, could not open date.tmp for input\n");
		exit(EXIT_FAILURE);
	}
	fgets(g_szBuffer2,sizeof(g_szBuffer2),fd);
	fclose(fd);
	system("rm -f date.tmp");

	memset(szMonth,0,sizeof(szMonth));
	memset(szDay,0,sizeof(szDay));
	memset(szYear,0,sizeof(szYear));
	memset(szHour,0,sizeof(szHour));
	strncpy(szMonth,&g_szBuffer2[4],3);
	strncpy(szDay,&g_szBuffer2[8],2);
	strncpy(szYear,&g_szBuffer2[26],2);
	strncpy(szHour,&g_szBuffer2[11],2);
	if(0 == strcmp("Jan",szMonth)) iMonth = 1;
	if(0 == strcmp("Feb",szMonth)) iMonth = 2;
	if(0 == strcmp("Mar",szMonth)) iMonth = 3;
	if(0 == strcmp("Apr",szMonth)) iMonth = 4;
	if(0 == strcmp("May",szMonth)) iMonth = 5;
	if(0 == strcmp("Jun",szMonth)) iMonth = 6;
	if(0 == strcmp("Jul",szMonth)) iMonth = 7;
	if(0 == strcmp("Aug",szMonth)) iMonth = 8;
	if(0 == strcmp("Sep",szMonth)) iMonth = 9;
	if(0 == strcmp("Oct",szMonth)) iMonth = 10;
	if(0 == strcmp("Nov",szMonth)) iMonth = 11;
	if(0 == strcmp("Dec",szMonth)) iMonth = 12;

        printf("---------------------------------------------------\n");

        printf("makevers.cpp Ver %2d.%02d.%02d%c  %s\n",
                atoi(szYear),iMonth,atoi(szDay),'a'+atoi(szHour),
		szMachtype);

        printf("Serial No. 20%s-%04d-654321 Licensed under GNU GPL.\n",
		szYear,atoi(szUid));
        printf("Copyright(c)20%s Douglas W. Goodall, United States.\n",
		szYear);
        printf("---------------------------------------------------\n");


	fd = fopen("version.hpp","w");
	if(NULL == fd) {
		printf("Sorry, cannot open version.hpp for output\n");
		exit(EXIT_FAILURE);
	}
//	printf("DEBUG: szYear is %s\n",szYear);

        fprintf(fd,"// ---------------------------------------------------\n");
        fprintf(fd,"// version.hpp  Ver %2d.%02d.%02d%c  %s\n",
                atoi(szYear),iMonth,atoi(szDay),'a'+atoi(szHour),
		szMachtype);
        fprintf(fd,"// Serial No. 20%s-%04d-654321                        \n",
		szYear,atoi(szUid));
        fprintf(fd,"// Copyright(c)20%s Douglas W. Goodall, United States.\n",
		szYear);
        fprintf(fd,"// ---------------------------------------------------\n");

	fprintf(fd,"// machine generated by %s\n",__FILE__);
	fprintf(fd,"//    %s\n",g_szBuffer2);
	fprintf(fd,"#define RMJ %d\n",atoi(szYear));
	fprintf(fd,"#define RMN %d\n",iMonth);
	fprintf(fd,"#define RUP %d\n",atoi(szDay));
	fprintf(fd,"#define RTP %d\n",atoi(szHour));
	fclose(fd);

	if(0 == strcmp(LINUX,szMachtype)) {
		char szCopyStr[128];
		sprintf(szCopyStr,"/home/%s/public_html/src/framewk/bin/copylast",
			szUser);
		fd = fopen(szCopyStr,"w");
		assert(fd);
        	sprintf(szDirSpec,"/home/%s/src/framewk/%02d%02d20%02d",
                	szUser,iMonth,atoi(szDay),atoi(szYear));
	}
	if(0 == strcmp(MACOSX,szMachtype)) {
		char szCopyStr[128];
		sprintf(szCopyStr,"/Users/%s/framewk/bin/copylast",
			szUser);
        	fd = fopen(szCopyStr,"w");
        	assert(fd);
		sprintf(szDirSpec,"/Users/%s/framewk/"
				  "%02d%02d20%02d",
                		  szUser,iMonth,
				  atoi(szDay),atoi(szYear));
	}

	fprintf(fd,"#!/bin/bash\n");
	if(0 == strcmp(MACOSX,szMachtype)) {
		fprintf(fd,"cp -R -n %s/* .\n",szDirSpec);
	}
	if(0 == strcmp(LINUX,szMachtype)) {
        	fprintf(fd,"cp -R %s/* .\n",szDirSpec);
	}
	fprintf(fd,"ls\n");
	fclose(fd);

	if(0 == strcmp(MACOSX,szMachtype)) {
		sprintf(szCommand,"chmod +x /Users/%s/framewk/bin/copylast",
			szUser);
		system(szCommand);
	}
	if(0 == strcmp(LINUX,szMachtype)) {
        	sprintf(szCommand,
		   "chmod +x /home/%s/public_html/src/framewk/bin/copylast",
			szUser);
		system(szCommand);
	}

	return EXIT_SUCCESS;
}

