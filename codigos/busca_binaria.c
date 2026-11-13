/* busca_binaria.c — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. Material didático de MAC0122, IME-USP.
 * https://www.ime.usp.br/~leo/mac/mac122/busca_binaria.html */

// Prof. Leo^nidas - http://www.matematica.br http://line.ime.usp.br
// MAC0122 - 2017/08/16
//
// Descricao: funcao "buscaBinaria(int vet[], int e, int d, int x)"
// 1. Devolve i se x ocorre entre as posicoes e e d, -1 em caso contrario
// 2. Dados programa principal que
//    * entrada dados: dados no codigo, pois tem que estar ordenado!
//    * buscas:        usando a funcao de 1, o usuario devera digitar um valor, se negativo pare (e nada imprime), senao
//                     verifique se valor no vetor (imprimindo sua posicao ou -1 se nao estiver no vetor)
//                     o programa para quando usuario digitar um valor negativo (neste caso o programa deve imprimir NADA).

#include <stdio.h>

#define MAX 50

// Ideia: pega elemento do meio, se menor que x busca na metade direita, se maior, busca na metade esquerda
// Complexidade: O(log n) pois a cada passo elimina metade dos elementos
// Param:   'vet[]' vetor com dados, 'int e' indice esquerdo, 'int d' indice direito, 'int x' elemento buscado
// Devolve: j entre e e d se encontrou na posicao j; -1 se x nao pertence a 'vet[e..d]'
int buscaBinaria (int vet[], int e, int d, int x) {
  int m;
  while (e <= d) {   // invariante: 'x' NAO pertence a 'vet[0..e-1]' e nem a 'vet[d+1..n-1]'
    m = (e + d) / 2; // media (lembre-se: divisao inteira)
    if (vet[m]<x) // metade esquerda NAO contem x
      e = m+1;
    else
    if (vet[m]>x) // metade direita NAO contem x
      d = m-1;
    else
      return m; // encontrou!
    }
  return -1;
  }

int main (void) {
  int n = 9, vet[] = { 0, 2, 2, 3, 5, 6, 7, 7, 9 }; // tem que estar ordenado...
  int i, x = 0;
  // entrada de dados: tem que estar ordenado!
  //D scanf("%d", &n); for (i=0; i<n; i++) scanf("%d", &vet[i]);
  for (i=0; i<n; i++) printf("%d ", vet[i]);
  printf("\nBuscas...\n");
  // buscar elementos (digitar negativo finaliza programa)
  x = 0;
  while (x>=0) {
    scanf("%d", &x);
    if (x>=0) {
      i = buscaBinaria(vet, 0, n-1, x); // EP: era n (lia vet[n], fora do vetor)
      if (i>=0)
         printf("* achei %d em vet[%d]\n", x, i);
      else
         printf("* %d nao esta no vetor!\n", x); // NAO encontrado
      }
    }
  return 0;
  }
