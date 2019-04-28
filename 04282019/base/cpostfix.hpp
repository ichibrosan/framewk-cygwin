// ---------------------------------------------------
// cpostfix.hpp 24-Feb-11   Running on Mac OS X 10.6.6
// S/n 2011-1042-654321  Written by Douglas W. Goodall
// Copyright(c)2011 Douglas W. Goodall, United States.
// Pilha e algoritmo shunting yard (baseado wikipedia)
// Free for use.    Done by  Luiz Roberto Meier,  2010
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

static char szCpostfixHpp[] = "$Id: cpostfix.hpp,v 1.1 2011/03/24 11:58:05 doug Exp $";

// Pilha e algoritmo shunting yard (baseado no wikipedia 
// Free for use. Done by Luiz Roberto Meier , 2010

#ifdef POSTFIX

#define POSTFIX_NO_DEBUG 1
#define POSTFIX_DEBUG    2

#define BUFFER_SIZE  128
#define POSTFIX_SIZE 20

class CPostfix {
	char m_infix[BUFFER_SIZE];
	char m_output[BUFFER_SIZE];		// limite pode ser aumentado
	char m_pilha[POSTFIX_SIZE];	// tamanho da pilha 10
	int m_ele;
	int m_tos;
	int m_bDebug;
public:
	CPostfix(int);
	void push(int);
	char pop(void);
	void mostra(void);
	int isempty(void);
	int isfull(void);
	int preced(char);
	int convert(char *);
	char * getresult(void);
};		

CPostfix::CPostfix(int argc)
{
	m_tos = 0;
	m_ele = 0;
	memset(m_output,0,sizeof(m_output));
	memset(m_infix, 0,sizeof(m_infix));
	memset(m_pilha,0,sizeof(m_pilha));

	if(2 == argc) m_bDebug = 1;
	else          m_bDebug = 0;
}

// Fun��es para operar com pilha (baseado no assembly)
void CPostfix::push(int ele)
{
	m_pilha[m_tos]=ele;
	m_tos++;
}

char CPostfix::pop(void)
{
	m_tos--;
	return(m_pilha[m_tos]);
}

void CPostfix::mostra(void) 
{
	if(0 == m_bDebug) return;
 
	int x=m_tos;	
	printf("\n Elementos da pilha: ");
	while(x!=0)
		printf("%c, ",m_pilha[--x]);	
}

// Fun��es para definir a preced�ncia
int CPostfix::preced(char simb) 
{
    if (simb== '(') return 0;
    if (simb== ')') return 0;
    if (simb=='+' || simb=='-') return 1;
    if (simb=='*' || simb=='/') return 2;
    if (simb=='^') return 3;
    return 0;
}

int CPostfix::convert(char *szInput)
{
//  printf("int CPostfix::convert(\"%s\"); called\n",szInput);

//  int i=0,j=0,k=0,length;

	int i=0;
	int j=0;
	int k=0;
	int length = 0;
  	char temp = 0;

	memset(m_output,0,sizeof(m_output));
	memset(m_infix,0,sizeof(m_infix));

  strcpy(m_infix,szInput);

  length=strlen(m_infix);
  for(i=0;i<length;i++) {
    // N�meros s�o separados dos operadores aqui
    if(m_infix[i]!='+' && 
       m_infix[i]!='-' && 
       m_infix[i]!='*' && 
       m_infix[i]!='/' && 
       m_infix[i]!='^' && 
       m_infix[i]!=')' && 
       m_infix[i]!='(' ) {
      m_output[j++]=m_infix[i];
      if(1 == m_bDebug) {
	printf("\n Elemento adicionado na expressao final : %c",m_infix[i]);
      }
    } else { 
      // Se for um ()
      if(m_tos==0) { 
        // Se n�o existir um operador na pilha, adiciona nela
        push(m_infix[i]);
   	if(1 == m_bDebug) {
		printf("\n Elemento adicionado na pilha :%c",m_infix[i]);
	}
      } else { 
	// Operadores s�o retirados e colocados 
	// de acordo com a preced�ncia.
	if(m_infix[i]!=')' && 
	   m_infix[i]!='(') {
	  if(preced(m_infix[i]) <= 
	     preced(m_pilha[m_tos-1])) {
            while (preced(m_infix[i]) && 
		   preced(m_infix[i]) <= 
		   preced(m_pilha[m_tos-1])) {
              temp=pop();
              if(1 == m_bDebug) {
		printf("\n Elemento retirado da pilha :%c",temp);
              }
	      m_output[j++]=temp;
            }
            push(m_infix[i]);
            if(1 == m_bDebug) {
		printf("\n Elemento colocado na pilha :%c",m_infix[i]);
            }
	    mostra();
	  } else {
	    push(m_infix[i]);
	    if(1 == m_bDebug) {
		printf("\n Elemento adicionado na pilha : %c",m_infix[i]);
	    }
	    mostra();
	  }
	} else {	
          if(m_infix[i]=='(') {
	    push(m_infix[i]);
	    if(1 == m_bDebug) {
		printf("\n Elemento colocado na pilha : %c",m_infix[i]);
	    }
	  }
	  if(m_infix[i]==')') {
	    temp=pop(); 
            while(temp!='(') {
              m_output[j++]=temp;
	      temp=pop();
            }
	  }
	}
      }
    }	
  }
  while(m_tos!=0) {
    m_output[j++]=pop();
  }
  if(1 == m_bDebug) {
	printf("\n\nA expressao final e : %s\n\n",m_output);
  }
//system("PAUSE");	
  return EXIT_SUCCESS;
}

char * CPostfix::getresult(void)
{
	return m_output;
}

#endif

////////////////////////
// eof - cpostfix.hpp //
////////////////////////
