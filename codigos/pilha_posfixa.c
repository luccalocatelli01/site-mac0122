/* pilha_posfixa.c — EP MAC0122
 * Escrito pelo grupo seguindo a P1 (Q4): avaliação de expressão pós-fixa com pilha.
 * Pilha em vetor no estilo da aula (topo começa em -1, ++topo, topo--).
 * Base: FEOFILOFF, P. Algoritmos em linguagem C. Elsevier, 2009 (cap. de pilhas). */

#include <stdio.h>
#include <ctype.h>

#define MAXPILHA 100
#define MAXLINHA 256

int pilha[MAXPILHA];
int topo = -1;

void empilha (int x) {
  if (topo == MAXPILHA - 1) {
    printf("Erro: pilha cheia\n");
    return;
    }
  pilha[++topo] = x;
  }

int desempilha (void) {
  if (topo < 0) {
    printf("Erro: pilha vazia (expressao mal formada)\n");
    return 0;
    }
  return pilha[topo--];
  }

/* Avalia uma expressão pós-fixa com inteiros não negativos e os operadores + - * /.
 * Os números podem ter mais de um dígito e são separados por espaço.
 * Ex.: "5 1 2 + 4 * + 3 -" vale 14. */
int avaliaPosfixa (char expr[]) {
  int i = 0, a, b, num;
  topo = -1;
  while (expr[i] != '\0' && expr[i] != '\n') {
    if (isdigit((unsigned char) expr[i])) {
      num = 0;
      while (isdigit((unsigned char) expr[i]))
        num = 10 * num + (expr[i++] - '0');
      empilha(num);
      continue;
      }
    if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
      b = desempilha();   /* o segundo operando sai primeiro */
      a = desempilha();
      switch (expr[i]) {
        case '+': empilha(a + b); break;
        case '-': empilha(a - b); break;
        case '*': empilha(a * b); break;
        case '/':
          if (b == 0) { printf("Erro: divisao por zero\n"); empilha(0); }
          else empilha(a / b);
          break;
        }
      }
    i++;
    }
  return desempilha();
  }

int main (void) {
  char linha[MAXLINHA];
  /* Uma expressão por linha (ver pilha_posfixa_entrada.txt). */
  while (fgets(linha, MAXLINHA, stdin) != NULL) {
    if (linha[0] == '\n' || linha[0] == '\0') continue;
    printf("%s", linha);
    printf("  = %d\n", avaliaPosfixa(linha));
    }
  return 0;
  }
