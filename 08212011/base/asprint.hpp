// ---------------------------------------------------
// asprint.hpp  24-Mar-11   Running on Mac OS X 10.6.6
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

static char szAsprintHpp[] = "$Id: asprint.hpp,v 1.2 2011/03/25 05:48:10 doug Exp $";

// 3/24/2011 dwg - make print of includes conditional

void print(FILE *fpl)
{

  char cSegment;

  char sep;
  char szBufovfl[128];

  switch(g_iSegment) {
    case SEG_VAGUE: cSegment = 'U';  break;
    case SEG_ABS:   cSegment = 'A';  break;
    case SEG_CODE:  cSegment = 'C';  break;
    case SEG_DATA:  cSegment = 'D';  break;
    case SEG_STACK: cSegment = 'S';  break;
    defaut:         cSegment = '?';  break;
  }

  sprintf(g_szAsprintHpp,"%s %s %s",__FILE__,__TIME__,__DATE__);

  if(FALSE == g_b1stHdrLstd) {
        fprintf(fpl,"%s",g_szProgram);
        // Insert needed spaces before page number field
        for(int i=0;i<g_iSpaces;i++) {
                fprintf(fpl," ");
        }
        fprintf(fpl,"Page %d %s Ver %2d.%02d.%02d%c",
                g_iPageNumber++,g_szArgv0,RMJ,RMN,RUP,'a'+RTP);
        fprintf(fpl,"\n%s",g_szTitle);
        fprintf(fpl,"\n%s",g_szSubttl);
	g_b1stHdrLstd = TRUE;
  }

  if( (1 == g_iSourceLevel) || (TRUE == g_bListIncludes) ) {
    sep = ':';
    if(g_iPageWidth-6 < strlen(g_szBuffer2)) {
      while(g_iPageWidth-6 < strlen(g_szBuffer2)) {
	strcpy(szBufovfl,&g_szBuffer2[g_iPageWidth-6]);
	g_szBuffer2[g_iPageWidth-6] = 0;
	fprintf(fpl,"\n%4d%c%c%c%d %s+",
		g_iFileLine,sep,cSegment,sep,g_iSourceLevel,g_szBuffer2);	
	sep = '+';
	if(g_iPageLength == ++g_iPageline) {
	  fprintf(fpl,"\n%c%s",ASCII_FORMFEED,g_szProgram);
	  for(int i=0;i<g_iSpaces;i++) {
	    fprintf(fpl," ");
	  }
	  fprintf(fpl,"Page %d %s Ver %2d.%02d.%02d%c",
		g_iPageNumber++,g_szArgv0,RMJ,RMN,RUP,'a'+RTP);
	  fprintf(fpl,"\n%s",g_szTitle);
	  fprintf(fpl,"\n%s",g_szSubttl); 
	  g_iPageline = 3;	
	}
	strcpy(g_szBuffer2,szBufovfl);
      }
      sprintf(g_szPc,g_szListRadix,g_iPc);
      fprintf(fpl,"\n%4d%c%c%c%d %s:          %s",
	      g_iFileLine,sep,cSegment,sep,g_iSourceLevel,g_szPc,g_szBuffer2); 	
      if(g_iPageLength == ++g_iPageline) {
	fprintf(fpl,"\n%c%s",ASCII_FORMFEED,g_szProgram); 
	for(int i=0;i<g_iSpaces;i++) {
	  fprintf(fpl," ");
	}
	fprintf(fpl,"Page %d %s Ver %2d.%02d.%02d%c",
		g_iPageNumber++,g_szArgv0,RMJ,RMN,RUP,'a'+RTP);
	fprintf(fpl,"\n%s",g_szTitle);
	fprintf(fpl,"\n%s",g_szSubttl);
	g_iPageline = 3;	
      }
    } else {
      fprintf(fpl,"\n%4d:%c%c%d %s",g_iFileLine,cSegment,sep,g_iSourceLevel,g_szBuffer2);	
      if(g_iPageLength == ++g_iPageline) {
	fprintf(fpl,"\n%c%s",ASCII_FORMFEED,g_szProgram);
	for(int i=0;i<g_iSpaces;i++) {
	  fprintf(fpl," ");
	}
	fprintf(fpl,"Page %d %s Ver %2d.%02d.%02d%c",
		g_iPageNumber++,g_szArgv0,RMJ,RMN,RUP,'a'+RTP);
	fprintf(fpl,"\n%s",g_szTitle);
	fprintf(fpl,"\n%s",g_szSubttl);
	g_iPageline = 3;	
      }
    }
  }
}

///////////////////////
// eof - asprint.hpp //
///////////////////////
