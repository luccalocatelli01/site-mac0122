/* infixa_posfixa.c — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. Material didático de MAC0122, IME-USP.
 * https://www.ime.usp.br/~leo/mac/mac122/expressoes_infixa2posfixa.html */

// Prof. Leo^nidas - http://www.matematica.br http://line.ime.usp.br
// MAC0122 - 2017/10/08

// Descricao: Transforma uma expressao aritmetica em outra equivalente em notacao pos-fixada
//            notacao in-fixa  : EXP op EXP
//            notacao pos-fixa : EXP EXP op
// Interessante: a notacao pos-fixa dispensa parenteses! E.g. "(2+3)*4" fica como "2 3 + 4 *"

// Ideia: Usar uma pilha apenas para operadores, a cada operando anotar na "pilha final"
//  1. Para cada caractere da expressao de entrada (notacao in-fixa e usando uma unica letra) - lendo da esquerda para a direita a "string"
//  2.   Se caractere e' operando, insira na expressao pos-fixada
//  3.   Senao
//  4.   Se caractere e' '(', entao empilhe-o
//  5.   Senao
//  6.   Se caractere e' ')', entao desempilhe e insira-o na expressao pos-fixada, ate' encontrar '('
//  7.   Senao
//  8.   Enquanto a pilha nao vazia e precedencia do operador atual <= precedencia do operador no topo da pilha,
//  9.     desempilhe e insira-o na expressao pos-fixada
// 10.     empilhe operador atual
// 11. Desempilhe os operadores que restaram na pilha de operadores, inserindo cada um na expressao pos-fixada e na "pilha final"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 256
#define DEBUG 0

// Construtor do tipo "pilha"
typedef struct {
  int topo;
  unsigned comprimentoPilha;
  int * dadosPilha;
  } tipoPilha;

// Estrutura registrando a pilha (usar uma para operadores e uma para a expressao em notacao pos-fixa)
tipoPilha * criarPilha (unsigned comprimento) {
  tipoPilha * pilha = (tipoPilha*) malloc(sizeof(tipoPilha));
  if (!pilha)
    return NULL;
  pilha->topo = -1;
  pilha->comprimentoPilha = comprimento;
  pilha->dadosPilha = (int*) malloc(comprimento * sizeof(int));
  if (!pilha->dadosPilha)
    return NULL;
  return pilha;
  }

// Verifica se caractere e' operando (simplificacao: aceito apenas 'a' ate 'z' ou 'A' ate 'Z'
int ehOperando (char ch) {
  return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
  }

// Devolve a precedencia de operador (se operador, senao -1): ^ => 2; * / => 1; + 0 => 0
int ordemPrecedencia (char ch) {
  switch (ch) {
    case '+':  case '-': return 0;
    case '*':  case '/': return 1;
    case '^':            return 2;
    }
  return -1;
  }

void examinaPilha (int *vetor, int comp) { // examine pilha de 0 ate o topo = 'comp'
  int i;
  if (DEBUG) printf("Examina pilha de operadores: #pilha = %d\n ", comp);
  for (i=0; i<=comp; i++) {
    printf("%c, ", vetor[i]);
    }
  printf("\n");
  }

int pilhaVazia (tipoPilha* pilha) { // create
  return (pilha->topo == -1);
  }
char examinaTopoPilha (tipoPilha* pilha) { // examina
  //S if (pilha==NULL || pilha->topo==-1) { printf("examinaTopoPilha: pilha vazia! topo=%d\n", pilha->topo); return 255; } // pilha vazia => devolva maior ASCII
  return pilha->dadosPilha[pilha->topo];
  }
char desempilha (tipoPilha* pilha) { // desempilha
  if (!pilhaVazia(pilha))
    return pilha->dadosPilha[pilha->topo--] ;
  return '$';
  }
void empilha (tipoPilha *pilha, char c, int aux) { // empilhe
  if (c == ' ') { printf("empilha: ERRO branco! topo=%d\n", pilha->topo); return; }
  pilha->dadosPilha[++pilha->topo] = c;
  if (DEBUG) printf(" (%d: %d) c=%c ", aux, pilha->topo, c);
  }

// Insere operando ou operador para compor uma pilha completa em notacao pos-fixada
void insereItemExp (char *str, char c, int *k, tipoPilha *pilha) {
  if (c == ' ') return;
  str[++*k] = c;
  empilha(pilha, c, 3);
  }

// Converte um expressao composta por operadores com uma unica letra (em notacao in-fixa) em equivalente pos-fixa
int infixa2PosFixada (char* strExpIn, char* strExpPos, tipoPilha **pilhaOriginal, tipoPilha **pilhaFinal) {
  tipoPilha *pilha, *pilhaAux; // apenas para eliminar um apontamento '*'
  int i, k; char c;

  // Cria pilha usando vetor, de tamanho comprimentoPilha igual ao tamanho da expressao
  pilha = criarPilha(strlen(strExpIn));    // esta sera' a "pilha de operadores"
  pilhaAux = criarPilha(strlen(strExpIn)); // esta sera' a "pilha final" (com elementos na ordem da notacao pos-fixa)
  *pilhaOriginal = pilha;
  if (DEBUG) printf("infixa2PosFixada: pilhaOriginal->comprimentoPilha=%d\n", (*pilhaOriginal)->comprimentoPilha);

  for (i = 0, k = -1; strExpIn[i]; i++) { // Examina cada caractere (item lexico)
    c = strExpIn[i];
    if (ehOperando(c)) { // Caractere atual e' operando: solte-o
      insereItemExp(strExpPos, c, &k, pilhaAux); // Insere na "pilha final" e na expressao pos-fixa
      }
    else
    if (c == '(') { // Caractere atual e' '(': empilhe-o
      empilha(pilha, c, 1);
      if (DEBUG) { printf("empilha: "); examinaPilha(pilha->dadosPilha, pilha->topo); }
      }
    else
    if (c == ')') { // Caractere atual e' ')': desempilha e desempilhe ate encontrar um '('
      while (!pilhaVazia(pilha) && examinaTopoPilha(pilha) != '(') {
        insereItemExp(strExpPos, desempilha(pilha), &k, pilhaAux); // Insere na "pilha final" e na expressao pos-fixa
        if (DEBUG) { printf("desempilha: "); examinaPilha(pilha->dadosPilha, pilha->topo); }
        }
      if (!pilhaVazia(pilha) && examinaTopoPilha(pilha) != '(')
        return -1; // expressao invalida!?
      else {
        desempilha(pilha);
        if (DEBUG) { printf("desempilha: "); examinaPilha(pilha->dadosPilha, pilha->topo); }
        }
      } // if (c == ')')
    else { // Caractere atual e' operador: desempilhe enquanto precedencia dele for menor que do topo da pilha
      while (!pilhaVazia(pilha) && ordemPrecedencia(c) <= ordemPrecedencia(examinaTopoPilha(pilha))) {
        insereItemExp(strExpPos, desempilha(pilha), &k, pilhaAux); // Insere na "pilha final" e na expressao pos-fixa
        if (DEBUG) { printf("desempilha: "); examinaPilha(pilha->dadosPilha, pilha->topo); }
        }
      empilha(pilha, c, 2);
      if (DEBUG) { printf("empilha: "); examinaPilha(pilha->dadosPilha, pilha->topo); }
      }
    } // for (i = 0, k = -1; strExpIn[i]; i++)

  if (DEBUG) { printf("O que sobou na pilha k=%d: ", k); examinaPilha(pilha->dadosPilha, pilha->topo); }

  // desempilha todos os operadores que sobraram na pilha
  while (!pilhaVazia(pilha)) {
    insereItemExp(strExpPos, c = desempilha(pilha), &k, pilhaAux); // Insere na "pilha final" e na expressao pos-fixa
    if (DEBUG) { printf(" insere %d, k=%d: %c\n", pilha->topo, k, c); }
    }
  strExpPos[++k] = '\0'; // Finaliza "string" da expressao em notacao pos-fixa
  pilhaAux->comprimentoPilha = k; // Agora temos o tamanho da expressao em 'pos-fixa' (sem os parenteses)

  *pilhaFinal = pilhaAux; // Pilha final

  } // int infixa2PosFixada(char* strExpIn, char* strExpPos, tipoPilha **pilhaOriginal, tipoPilha **pilhaFinal)

// Programa principal
int main () {
  tipoPilha *pilha, *pilhaFinal;
  char strExpPos[MAX]; // Para a expressao final em notacao pos-fixa
  int i;
  char *strExp,
    strExpressao[][MAX] = { // Exemplos fixos
      "a+b*c",
      "(a+b)*c",
      "a+b*c^d",
      "a+b*c^d-e",
      "a+b*c^d-e*f",
      "a+b*c^d-e*f+g",
      "a+b*c^d-e*f+g-h",
      "a+b*c^d-e*f+g-h/i",
      "a+(b*c)^d-e*f+g-h/i",
      "a+(b*c)^(d-e)*f+g-h/i"
     };

  for (i=0; i<10; i++) {
    //printf("Digite uma expressao em notacao in-fixa: "); //D Se desejar digitar...
    //scanf("%s", strExp);
    strExp = strExpressao[i];
    infixa2PosFixada(strExp, strExpPos, &pilha, &pilhaFinal);

    printf("Expressao original: %s\n", strExp);
    printf("Expressao final   : %s\n", strExpPos);

    printf("                  : ");
    examinaPilha(pilhaFinal->dadosPilha, pilhaFinal->topo);
    }
  printf("\n");

  return 0;
  }
