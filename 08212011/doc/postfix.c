// Pilha e algoritmo shunting yard (baseado no wikipedia) 
// Free for use. Done by Luiz Roberto Meier , 2010

#include "includes.hpp"

//#include <string.h>
//#include <stdio.h>
#define size 10

char pilha[size]; // tamanho da pilha 10 
int tos=0, ele; // posi��o e elemento

void push();
char pop();
void mostra();
int isempty();
int isfull();

char infix[30],output[30]; // limite pode ser aumentado...
int preced(char);

// Fun��es para operar com pilha (baseado no assembly)
void push(int ele) {
	pilha[tos]=ele;
	tos++;
}

char pop() {
	tos--;
	return(pilha[tos]);
}

void mostra() {
	int x=tos;	
	printf("\n Elementos da pilha: ");
	while(x!=0)
	printf("%c, ",pilha[--x]);	
}

// Fun��es para definir a preced�ncia
int preced(char simb) {
    if (simb== '(') return 0;
    if (simb== ')') return 0;
    if (simb=='+' || simb=='-') return 1;
    if (simb=='*' || simb=='/') return 2;
    if (simb=='^') return 3;
    return 0;
}

int main()
{
	int i=0,j=0,k=0,length;
	char temp;
	printf("\nDigite uma expressao matematica : ");
	scanf("%s",infix);
	length=strlen(infix);
	for(i=0;i<length;i++) {
		// N�meros s�o separados dos operadores aqui
		if(infix[i]!='+' && infix[i]!='-' && infix[i]!='*' && infix[i]!='/' && infix[i]!='^' && infix[i]!=')' && infix[i]!='(' ) {
          output[j++]=infix[i];
          printf("\n Elemento adicionado na expressao final : %c",infix[i]);
		} else { // Se for um ()
			if(tos==0) { // Se n�o existir um operador na pilha, adiciona nela
               push(infix[i]);
			   printf("\n Elemento adicionado na pilha :%c",infix[i]);
			} else { // Operadores s�o retirados e colocados de acordo com a preced�ncia.
				if(infix[i]!=')' && infix[i]!='(') {
					if(preced(infix[i]) <= preced(pilha[tos-1])) {
                      while (preced(infix[i]) && preced(infix[i]) <= preced(pilha[tos-1])) {
                        temp=pop();
                        printf("\n Elemento retirado da pilha :%c",temp);
                        output[j++]=temp;
                      }
                      push(infix[i]);
                      printf("\n Elemento colocado na pilha :%c",infix[i]);
                      mostra();
					} else {
					  push(infix[i]);
					  printf("\n Elemento adicionado na pilha : %c",infix[i]);
					  mostra();
					}
				} else {	
                    if(infix[i]=='(') {
					  push(infix[i]);
					  printf("\n Elemento colocado na pilha : %c",infix[i]);
					}
					if(infix[i]==')') {
					  temp=pop(); 
                      while(temp!='(') {
                        output[j++]=temp;
					    temp=pop();
                      }
					}
				}
			}
		}	
	}
	while(tos!=0) {
		output[j++]=pop();
	}
     printf("\n\nA expressao final e : %s\n\n",output);
     
//     system("PAUSE");	
     return 0;
}
