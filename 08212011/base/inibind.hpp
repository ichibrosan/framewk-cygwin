// ---------------------------------------------------
// inibind.hpp  13-Mar-11   Running on Mac OS X 10.6.6
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

static char szInibindHpp[] = "$Id: inibind.hpp,v 1.1 2011/03/24 11:58:05 doug Exp $";

// 3/13/2011 - add warning variable to ini file
// 12/6/2010 - add logging variable to ini file
// 9/13/2010 - don't use strupr on value portion


#ifdef INIBIND

#define SELF argv[0]

/*
 open ini file and read entry
 returns NULL is section or key not found,
 otherwise pointer to result string
*/
char * ini_read(
	char *filename,
	char *section,
	char *key) 
{

	char *p;
	FILE *fp;
	char buffer[128];
	char buffer2[128];
	char szSection[128];
	char szKey[128];
	char szIni[128];	
	char g_szBuffer2[128];
	strcpy(szIni,filename);

// If this were DOS, we would remove the ".exe"
//	szIni[strlen(szIni)-1] = 0;     /* eat third type byte  */
//	szIni[strlen(szIni)-1] = 0;     /* eat second type byte */
//	szIni[strlen(szIni)-1] = 0;     /* eat first type byte  */

	strcat(szIni,".ini");

	memset(g_szIniValue,0,sizeof(g_szIniValue));

	fp = fopen(szIni,"r");

	// If the file doesn't exist, create a new
	// one and give it a fun set of entries.
	if(NULL == fp) {
		fp = fopen(szIni,"w");
		fprintf(fp,"[Options]\n");
		fprintf(fp,"Banner=Full\n");
		fprintf(fp,"Debug=False\n");
		fprintf(fp,"Language=English\n");
		fprintf(fp,"Logging=False\n");
		fprintf(fp,"Monitor=False\n");
		fprintf(fp,"Trace=False\n");
		fprintf(fp,"Warning=False\n");
		fprintf(fp,"[Debug]\n");
		fprintf(fp,"[Env]\n");
		system("set > environ.tmp");
		FILE * fp2 = fopen("environ.tmp","r");
		char * p2 = fgets(g_szBuffer2,sizeof(g_szBuffer2),fp2);
		while(NULL != p2) {
			fprintf(fp,"%s",g_szBuffer2);
			p2 = fgets(g_szBuffer2,sizeof(g_szBuffer2),fp2);
		}
		fclose(fp2);
		fprintf(fp,"[End]\n");
		fclose(fp);
		system("rm environ.tmp");
		fp = fopen(szIni,"r");
		assert(fp);
	}

	// Create a section header for comparison
	sprintf(szSection,"[%s]",section);

	// Scan the ini file looking for the section header
	p = fgets(buffer,sizeof(buffer),fp);
	while(NULL != p) {
		// remove trailing newline
		buffer[strlen(buffer)-1] =  0;

		// IS this the sectiom we are looking for?
		if(0 == strcmp(buffer,szSection)) {
			p = fgets(buffer,sizeof(buffer),fp);
			while(NULL != p) {
				buffer[strlen(buffer)-1] = 0;
				strcpy(buffer2,buffer);
				if(buffer[0] == '[') {
					return(NULL);
				}

				// Create key string for comparison
				sprintf(szKey,"%s=",key);
				if(0 == strncmp(buffer,szKey,strlen(szKey))) {
					fclose(fp);
					strcpy(g_szIniValue,
					       &buffer2[strlen(szKey)]);
					return(g_szIniValue);
				}
				p = fgets(buffer,sizeof(buffer),fp);
			}
		}
		p = fgets(buffer,sizeof(buffer),fp);
	}
	fclose(fp);

	return NULL;	// return NULL if we couldn't find the
			// section and key we were looking for
}


void ini_write(
	char *filename,
	char *machtype,
	char *ostype,
	char *pwd,
	char *uid,
	char *user) 
{
	TRACE("ini_read2() starting");
	char *p;
	FILE *fp;
	char buffer[128];
	char buffer2[128];
	char szSection[128];
	char szKey[128];
	char szIni[128];	

	strcpy(szIni,filename);
//	szIni[strlen(szIni)-1] = 0;     /* eat third type byte  */
//	szIni[strlen(szIni)-1] = 0;     /* eat second type byte */
//	szIni[strlen(szIni)-1] = 0;     /* eat first type byte  */
	strcat(szIni,".ini");

	memset(g_szIniValue,0,sizeof(g_szIniValue));

	TRACE("open ini for write");
	TRACE(szIni);
	fp = fopen(szIni,"w");
	assert(fp);
	fprintf(fp,"[Options]\n");
	fprintf(fp,"Banner=Full\n");
	fprintf(fp,"Debug=False\n");
	fprintf(fp,"Language=English\n");
	fprintf(fp,"Logging=False\n");
	fprintf(fp,"Monitor=False\n");
	fprintf(fp,"[Environment]\n");
	fprintf(fp,"Machtype=%s\n",machtype);
	fprintf(fp,"Uid=%s\n",uid);
	fprintf(fp,"User=%s\n",user);
	fprintf(fp,"Ostype=%s\n",ostype);
	fprintf(fp,"Pwd=%s\n",pwd);
	fprintf(fp,"[End]\n");
	fclose(fp);
}



int ini_is_section(
	char *filename,
	char *section) 
{

	char *p;
	FILE *fp;
	char buffer[128];
	char szSection[128];
	char szKey[128];
	char szIni[128];	

	strcpy(szIni,filename);
	szIni[strlen(szIni)-1] = 0;     /* eat third type byte  */
	szIni[strlen(szIni)-1] = 0;     /* eat second type byte */
	szIni[strlen(szIni)-1] = 0;     /* eat first type byte  */
	strcat(szIni,"ini");
	memset(g_szIniValue,0,sizeof(g_szIniValue));
	fp = fopen(szIni,"r");
	if(NULL == fp) {
		return(EXIT_FAILURE);
	}
	sprintf(szSection,"[%s]",section);
	p = fgets(buffer,sizeof(buffer),fp);
	while(NULL != p) {
		buffer[strlen(buffer)-1] =  0;
		if(0 == strcmp(buffer,szSection)) {
			return EXIT_SUCCESS;
		}
		p = fgets(buffer,sizeof(buffer),fp);
	}
	fclose(fp);

	return 0;
}

int ini_make_section(char *filename,char *section)
{
	
	char buffer[128];
	char buffer1[128];
	char szCmd[128];
	char *p;
	char *p1;
	char *p2;
	char szIni1[128];
	char szIni2[128];
	
	FILE *fp1;
	FILE *fp2;
		
	strcpy(szIni2,filename);
	szIni2[strlen(szIni2)-1] = 0;     /* eat third type byte  */
	szIni2[strlen(szIni2)-1] = 0;     /* eat second type byte */
	szIni2[strlen(szIni2)-1] = 0;     /* eat first type byte  */
	strcat(szIni2,"tmp");

	strcpy(szIni1,filename);
	szIni1[strlen(szIni1)-1] = 0;     /* eat third type byte  */
	szIni1[strlen(szIni1)-1] = 0;     /* eat second type byte */
	szIni1[strlen(szIni1)-1] = 0;     /* eat first type byte  */
	strcat(szIni1,"ini");

	fp2 = fopen(szIni2,"w");
	if(NULL == fp2) {
		printf("Sorry, cannot open %s for writing\n",szIni2);
		return(EXIT_FAILURE);
	}

	fp1 = fopen(szIni1,"r");
	if(NULL == fp1) {
		printf("Sorry, cannot open %s for reading\n",szIni1);
		return(EXIT_FAILURE);
	}	
	p1 = fgets(buffer1,sizeof(buffer1),fp1);
	while(NULL != p1) {
		buffer1[strlen(buffer1)-1] = 0;
		if(0 == strcmp(section,buffer1)) {
			printf("Section %s is already there\n",section);
			fclose(fp1);
			fclose(fp2);
			return(EXIT_FAILURE);
		}
		if(0 == strcmp("[END]",buffer1)) {
			fprintf(fp2,"%s\n",section);
			fprintf(fp2,"%s\n",buffer1);
			fclose(fp1);
			fclose(fp2);
			
			fp1 = fopen(szIni1,"w");
			fp2 = fopen(szIni2,"r");
			p = fgets(buffer,sizeof(buffer),fp2);
			while(NULL != p) {
				fprintf(fp1,"%s",buffer);
				p = fgets(buffer,sizeof(buffer),fp2);
			}
			fclose(fp1);
			fclose(fp2);
			return(EXIT_SUCCESS);
		} else {
			fprintf(fp2,"%s\n",buffer1);
		}
		p1 = fgets(buffer1,sizeof(buffer1),fp1);
	}	
	fprintf(fp2,"[End]\n");
	fclose(fp1);
	fclose(fp2);

	fp1 = fopen(szIni1,"w");
	fp2 = fopen(szIni2,"r");
	p = fgets(buffer,sizeof(buffer),fp2);
	while(NULL != p) {
		fprintf(fp1,"%s",buffer);
		p = fgets(buffer,sizeof(buffer),fp2);
	}
	fclose(fp1);
	fclose(fp2);

	
	return(EXIT_SUCCESS);
}

#endif

///////////////////////
// eof - inibind.hpp //
///////////////////////

