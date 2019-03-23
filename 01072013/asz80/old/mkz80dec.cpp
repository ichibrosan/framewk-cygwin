#include <stdio.h>
#include <stdlib.h>
#include <string.h>
\
int main(int argc,char **argv)
{
	char g_szBuffer2[128];

	FILE * fd2 = fopen("stuff2","w");
	FILE * fd = fopen("stuff","r");
	char *p = fgets(g_szBuffer2,sizeof(g_szBuffer2),fd);
	while(NULL != p) {
		g_szBuffer2[strlen(g_szBuffer2)-1] = 0;
		fprintf(fd2,"#include \"asz80/%s\"\n",g_szBuffer2);
		p = fgets(g_szBuffer2,sizeof(g_szBuffer2),fd);
	}
	fclose(fd);
	fclose(fd2);
}

