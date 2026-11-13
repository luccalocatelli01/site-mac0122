/* busca_linear.c — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. Material didático de MAC0122, IME-USP.
 * https://www.ime.usp.br/~leo/mac/mac122/busca_nao_ordenado.html */

// Prof. Leo^nidas - http://www.matematica.br http://line.ime.usp.br
// MAC0122 - 2017
//
// Descricao:
// 1. funcao "busca(int vet[], int n, int x)" que devolve i se x ocorre primeiro na posicao i, -1 em caso contrario
// 2. programa principal que
//    * entrada dados: usuario digita valores ate que entra negativo, primeiro valor e' guardado na posicao 0 e assim por diante
//                     o ultimo valor digitado (negado) NAO sera' armazenado!
//    * buscas:        usando a funcao de 1, o usuario devera digitar um valor, se negativo pare (e nada imprime), senao
//                     verifique se valor no vetor (imprimindo sua posicao ou -1 se nao estiver no vetor)
//                     o programa para quando usuario digitar um valor negativo (neste caso o programa deve imprimir NADA).

#include <stdio.h>

#define MAX 50

// Vetor nao ordenado
// Param:   'vet[]' vetor com dados, 'int n' numero de elementos no vetor, 'int x' elemento buscado
// Devolve: j entre 0 e n-1 se encontrou na posicao j; -1 se x nao pertence a 'vet[]'
int busca (int vet[], int n, int x) {
  int j;
  for (j=0; j<n; j++) { // invariante: x NAO pertence a 'vet[0]' ate 'vet[j-1]'
    if (vet[j]==x)
      return j;         // se executar essa linha => 'vet[j]' contem x e e' a primeira ocorrencia
    }
  return -1;
  }

int main (void) {
  int n, vet[MAX];
  int i, x = 0;
  // entrada de dados - tamanho do vetor (quantos dados uteis)
  scanf("%d", &n);
  // entrada de dados - supor valor nao negativos
  for (i=0; i<n; i++)
    scanf("%d", &vet[i]);

  // busca elementos (digitar negativo finaliza programa)
  x = 0;
  while (x>=0) {
    scanf("%d", &x);
    if (x>=0) {
      i = busca(vet, n, x);
      if (i>=0)
         printf("%d\n", i);
      else
         printf("-1\n"); // NAO encontrado
      }
    }
  return 0;
  }
