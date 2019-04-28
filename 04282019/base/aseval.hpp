// $Log: aseval.hpp,v $
// Revision 1.2  2011/04/14 15:13:09  doug
// get ready for release to wiki and server
//
//

// ---------------------------------------------------
// aseval.hpp   28-Feb-11   Running on Mac OS X 10.6.6
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

static char szAsevalHpp[] = "$Id: aseval.hpp,v 1.2 2011/04/14 15:13:09 doug Exp $";

//#define POSTFIX
//#include "includes.hpp"

#define CEVAL_TOKENS 26

class CEval {
public:
	struct TOKENS_TAG {
  		char szVarName[128];
  		int  iTokeType;
  		char cVarOper;
		char cVarParen;
  		unsigned long long ullValue;
	} m_tokens[CEVAL_TOKENS];
	int m_iTokendex;
	CEval();
	void clear(void);
	int bIsAlpha(char);
	int bIsNumeric(char);
	int bIsOperator(char);
	int bIsWhitespace(char);
	int bIsParen(char);
	int bExpression(char *);
	int iGotAlphaToken(char *);
	int iGotNumericToken(unsigned long long,char *);
	int iGotOperatorToken(unsigned char);
	int iGotParenToken(unsigned char);
	void dump(void);
	int tokenize(char *);
	int gather(char *);
	unsigned long long evaluate(char *);
};


enum { TOK_VAR_ALPHA, TOK_VAR_NUM, TOK_OP, TOK_PAREN };


CEval::CEval()
{
	TRACE("CEval::CEval() started");
	m_iTokendex = 0;
	clear();
}

int CEval::gather(char *szInput)
{
	TRACE("CEval::gather() started");
        int iInputdex = 0;
        for(int i=0;i<m_iTokendex;i++) {
                switch(m_tokens[i].iTokeType) {
                        case TOK_VAR_NUM:
                        case TOK_VAR_ALPHA:
                                szInput[iInputdex++] =
                                        'A'+i;
                                break;
                        case TOK_OP:
                                szInput[iInputdex++] =
                                        m_tokens[i].cVarOper;
                                break;
                        case TOK_PAREN:
                                szInput[iInputdex++] =
                                        m_tokens[i].cVarParen;
                                break;
                }
        }
	szInput[iInputdex] = 0;

	return(EXIT_SUCCESS);
}


void CEval::clear(void)
{
	TRACE("CEval::clear() started");
	m_iTokendex = 0;
	memset(m_tokens,0,sizeof(m_tokens));
}

int CEval::bIsAlpha(char c)
{
	TRACE("CEval::bIsAlpha() called");
	if( ('a' <= c) && ('z' >= c) ) return TRUE;
	if( ('A' <= c) && ('Z' >= c) ) return TRUE;
	return FALSE;
}

int CEval::bIsNumeric(char c)
{
	TRACE("CEval::bIsNumeric()O started");
	if( ('0' <= c) && ('9' >= c) ) {
		TRACE("CEval::bIsNumeric detected 0-9");
		return TRUE;
	}
	if( '$' == c ) {
		TRACE("CEval::bIsNumeric detected $");
		return TRUE;
	}

	return FALSE;
}

int CEval::bIsOperator(char c) {
	TRACE("CEval::bIsOperator() called");

        if('+' == c) return TRUE;
        if('-' == c) return TRUE;
        if('*' == c) return TRUE;
        if('/' == c) return TRUE;
        return FALSE;
}

int CEval::bIsParen(char c) {
	TRACE("CEval::bIsParen() called");

        if('(' == c) return TRUE;
        if(')' == c) return TRUE;
        return FALSE;
}


int CEval::bIsWhitespace(char c)
{
	TRACE("CEval::bIsWhitespace() called");

        if(' ' == c) return TRUE;
        return FALSE;
}


int CEval::bExpression(char *szParm)
{
	TRACE("CEval::bExpression() called");
	if(TRUE == g_bDebug) {
	  printf("\nCEval::bExpression(\"%s\") called for line #%d\n",szParm,g_iFileLine);
	}

        for(int i=0;i<strlen(szParm);i++) {
                if('+' == szParm[i]) return TRUE;
                if('-' == szParm[i]) return TRUE;
                if('*' == szParm[i]) return TRUE;
                if('/' == szParm[i]) return TRUE;
//                if('(' == szParm[i]) return TRUE;
//                if(')' == szParm[i]) return TRUE;
        }
        return FALSE;
}




int CEval::iGotAlphaToken(char * sz)
{
	TRACE("CEval::iGotAlphaToken() started");

	int rc;

	m_tokens[m_iTokendex].iTokeType = TOK_VAR_ALPHA;

	m_tokens[m_iTokendex].ullValue = 
		(unsigned long long)g_pCSymbols->getu64(sz,&rc);

	strcpy(m_tokens[m_iTokendex++].szVarName,sz);
}

int CEval::iGotNumericToken(unsigned long long number,char *szNumber)
{
	TRACE("CEval::iGotNumericToken() started");

	m_tokens[m_iTokendex].iTokeType = TOK_VAR_NUM;
	strcpy(m_tokens[m_iTokendex].szVarName,szNumber);

	m_tokens[m_iTokendex++].ullValue = number;
}

int CEval::iGotOperatorToken(unsigned char c)
{
	TRACE("CEval::iGotOperatorToken() started");

	m_tokens[m_iTokendex].iTokeType = TOK_OP;
	m_tokens[m_iTokendex++].cVarOper = c;
}

int CEval::iGotParenToken(unsigned char c)
{
	TRACE("CEval::iGotParenToken() started");

        m_tokens[m_iTokendex].iTokeType = TOK_PAREN;
	m_tokens[m_iTokendex++].cVarParen = c;
}

void CEval::dump(void)
{
	TRACE("CEval::dump() called");

	if(TRUE == g_bDebug) {
	int iSpaces;

  printf("\n");
  printf("-------------------------------------------------------------------\n");
  printf("| Index | Pseudo | Token Type | Symbol Value in Hex  | Token      |\n");
  printf("-------------------------------------------------------------------");
  for(int i=0;i<m_iTokendex;i++) {
    printf("\n|  %2d   |   %c   ",i,'A'+i);
    switch(m_tokens[i].iTokeType) {
      case TOK_VAR_ALPHA:
	printf(" | VAR_ALPHA ");
	printf(" | 0x%017llX ",m_tokens[i].ullValue);
	printf(" | \"%s\" ",m_tokens[i].szVarName);
	iSpaces = 8 - strlen(m_tokens[i].szVarName);
	if(0 < iSpaces) {
	  for(int x=0;x<iSpaces;x++) {
	    printf(" ");
	  }
	}
	printf("|");
	break;
      case TOK_VAR_NUM:
	printf(" | VAR_NUM   ");
	printf(" | 0x%017llX ",m_tokens[i].ullValue);
        printf(" | \"%s\" ",m_tokens[i].szVarName);
        iSpaces = 8 - strlen(m_tokens[i].szVarName);
        if(0 < iSpaces) {
          for(int x=0;x<iSpaces;x++) {
            printf(" ");
          }
        }
        printf("|");
        break;
      case TOK_OP:
	printf(" | VAR_OP    ");
	printf(" |                     ");
	printf(" | '%c'        |",m_tokens[i].cVarOper);
	break;
      case TOK_PAREN:
	printf(" | VAR_PAREN ");
	printf(" |                     ");
	printf(" | '%c'        | ",m_tokens[i].cVarParen);
	break;
    }
  }
  printf("\n-------------------------------------------------------------------");
  }
}

// The purpose of the tokenize function is to scan an
// input string and fill in a structure with one
// record per term. Each term can be classified as a
// number or an operator or an alpha field.

int CEval::tokenize(char *szinput)
{
	TRACE("CEval::tokenize() called");
	clear();

  TRACE("tokenize starting");

  TRACE("Clearing alpha buffer");
  char szAlpha[128];
  int iAlphadex = 0;
  memset(szAlpha,0,sizeof(szAlpha));

  TRACE("Clearing numeric buffer");
  char szNumber[128];
  int iNumberdex = 0;
  memset(szNumber,0,sizeof(szNumber));

  TRACE("Clearing tokens structure");
  memset(&m_tokens,0,sizeof(m_tokens));

  // iBufferdex is an index into the szinput
  // parameter. The srting is scanned left 
  // to right from the first to the last char.
  int iBufferdex = 0;

  // State 1 is the initial state which attempts
  // to classify the token type based on it's 
  // first character.
  int iState = 1;

  // The iTokendex is an index into the token
  // structure. After each token is assembled,
  // a token structure entry is filled in and
  // the iTokendex is incremented.
  int iTokendex = 0;

//  // Trim off trailing spaces left after parsing
//  while(' ' == szinput[strlen(szinput)-1]) {
//	szinput[strlen(szinput)-1] = 0;
//  }

  // The iLength variable contains the number
  // of characters in the inpout string. The
  // tokenizer scans from an index of zero through
  // iLength -1.
  int iLength = strlen(szinput);

  unsigned long long ullValue;
  TRACE("starting tokenization");
  while(iBufferdex < iLength) {
    TRACE("iBufferdex < iLength");
    int c = szinput[iBufferdex++];
    fprintf(g_flog,"szinput token is %c\n",c);
    switch(iState) {
      case 1:	// start with 1st char
        TRACE("case 1");
        fprintf(g_flog,"case 1 starting\n");
	if(TRUE == bIsAlpha(c)) {
          TRACE("its alpha");
	  szAlpha[iAlphadex++] = c;
 	  iState = 2;
	  break;
	}
	if(TRUE == bIsNumeric(c)) {
	  TRACE("its numeric");
          fprintf(g_flog,"case 1 found numeric %c\n",c);
	  if('$' != c) {
            fprintf(g_flog,"case 1 numeric not $\n");
	    szNumber[iNumberdex++] = c;
	  }
          fprintf(g_flog,"case 1 setting state 3 to continue numeric\n");
	  iState = 3;
	  break;
	}
	if(TRUE == bIsOperator(c)) {
          TRACE("its an operator");
	  iGotOperatorToken(c);
	  break;
	}
	if(TRUE == bIsParen(c)) {
          TRACE("its a paren ");
	  iGotParenToken(c);
	  break;
	}
      case 2:	// continue collecting alpha token
        TRACE("case 2");
	if(TRUE == bIsWhitespace(c)) {
	  TRACE("its whitespace");
	  iGotAlphaToken(szAlpha);
	  memset(szAlpha,0,sizeof(szAlpha));
	  iAlphadex = 0;

	  iState = 1;
	  break;
	}
        if(TRUE == bIsOperator(c)) {
	  TRACE("its an operator");
	  iGotAlphaToken(szAlpha);
	  memset(szAlpha,0,sizeof(szAlpha));
	  iAlphadex = 0;

	  iGotOperatorToken(c);

	  iState =1;
	  break;
	}
	if(TRUE == bIsParen(c)) {
	  TRACE("its a paren");
	  iGotAlphaToken(szAlpha);
	  memset(szAlpha,0,sizeof(szAlpha));
	  iAlphadex = 0;

	  iGotParenToken(c);

	  iState = 1;
	  break;
	}
	szAlpha[iAlphadex++] = c;
	break;
      case 3: // contiue collecting numeric token
        TRACE("case 3, collecting numeric token");
        fprintf(g_flog,"case 3 starting, c is %c\n",c);
        if(TRUE == bIsWhitespace(c)) {
          TRACE("its whitespace");
	  fprintf(g_flog,"case 3 whitespace detected\n");
          sscanf(szNumber,g_szRadixFormat64,&ullValue);
          iGotNumericToken(ullValue,szNumber);
          memset(szNumber,0,sizeof(szNumber));
          iNumberdex = 0;
	  fprintf(g_flog,"case 3 setting state 1 again\n");
          iState = 1;
          break;
        }
        if(TRUE == bIsOperator(c)) {
          TRACE("its an operator");
	  fprintf(g_flog,"case 3 detected operator %c\n",c);
          sscanf(szNumber,g_szRadixFormat64,&ullValue);
          iGotNumericToken(ullValue,szNumber);
          memset(szNumber,0,sizeof(szNumber));
          iNumberdex = 0;

          iGotOperatorToken(c);
	  fprintf(g_flog,"case 3 setting state 1 again \n");
          iState =1;
          break;
        }
        if(TRUE == bIsParen(c)) {
          TRACE("its a paren");
	  fprintf(g_flog,"case 3 detected paren %c\n",c);
          sscanf(szNumber,g_szRadixFormat64,&ullValue);
          iGotNumericToken(ullValue,szNumber);
          memset(szNumber,0,sizeof(szNumber));
          iNumberdex = 0;

	  iGotParenToken(c);
	  fprintf(g_flog,"case 3 setting state 1 again\n");
	  iState = 1;
	  break;
        }
        szNumber[iNumberdex++] = c;
        break;
    }
  }
  return(EXIT_SUCCESS);
}


// The purpose of the evaluate function is
// to accept an input string in reverse
// polish notation, consisting of letters
// and operands. The letters are actually
// indexes into the tokens structure which
// contains all known information about 
// each token. As it traverses from the 
// left to the right, each letter is used
// tokens structure to retrieve the type
// and value of each term as needed for
// the evaluation process.

unsigned long long CEval::evaluate(char *string )
{
  TRACE("CEval::evaluate() called");

  unsigned long long ullStack[32];
  int ullIndex = 0;
  memset(&ullStack,0,sizeof(ullStack));

  unsigned long long acc = 0;

  int iLength = strlen(string);
  int index = 0;
  unsigned char c;

  while(index < iLength) {
    TRACE("index < iLength");
    if(TRUE == g_bDebug) {
      for(int x=0;x<ullIndex;x++) {
  	  printf("<%d> ",ullStack[x]);
      }
      printf("\n");
    }

    c = string[index];

    if(TRUE == bIsAlpha(c)) {
      ullStack[ullIndex++] = m_tokens[c-'A'].ullValue;
    }

    if(TRUE == bIsOperator(c)) {
      assert(ullIndex >= 2);
      switch(c) {
	case '+':
	  if(TRUE == g_bDebug) {
	    printf("<+>\n");
	  }
  	  ullStack[ullIndex-2] += ullStack[ullIndex-1];
	  ullStack[ullIndex-1] = 0;
	  ullIndex--;
	  break;
	case '-':
	  if(TRUE == g_bDebug) {
	    printf("<->\n");
	  }

          ullStack[ullIndex-2] -= ullStack[ullIndex-1];
          ullStack[ullIndex-1] = 0;
	  ullIndex--;
	  break;
	case '*':
	  if(TRUE == g_bDebug) {
	    printf("<*>\n");
	  }
          ullStack[ullIndex-2] *= ullStack[ullIndex-1];
          ullStack[ullIndex-1] = 0;
          ullIndex--;
          break;
	case '/':
	  if(TRUE == g_bDebug) {
	    printf("</>\n");
	  }
	  if(ullStack[ullIndex-1] == 0) {
	  	g_iErrorNo |= ERROR_DIV0;
		ullStack[ullIndex-1] = 1;
	  }
          ullStack[ullIndex-2] /= ullStack[ullIndex-1];
          ullStack[ullIndex-1] = 0;
          ullIndex--;
          break;
      }		
    }	
    index++;	
  }
  if(TRUE == g_bDebug) {
    printf("<%d>",ullStack[0]);
  }
  return ullStack[0];
}

//////////////////////
// eof - aseval.hpp //
//////////////////////

 
