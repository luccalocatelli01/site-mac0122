/* quicksort.c — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. Material didático de MAC0122, IME-USP.
 * https://www.ime.usp.br/~leo/mac/mac122/ordena_rapido.html */

// Prof. Leo^nidas - http://www.matematica.br http://line.ime.usp.br
// MAC0122 - 2017/08/23

// Biblioteca para: ordenar vetor de inteiros via metodo da Ordenacao Rapida. Complexidade: em media O(n log n)
// Exemplo de metodo no paradgma "DIVISAO e CONQUISTA"
// Invocar: #include "ordena_insercao.h"
//          ...
//          XbibliotecaLOBx__ordenaRapido(int V[], int esq, int dir)

// Programa recursivo para ordenar uma lista de inteiros usando a ideia separar menores e maiores que x
// depois ordenar cada trecho (se cada trecho for proximo de metade, resulta O(n log n)).

// Ordena Rapido (Quick Sort)
void XbibliotecaLOBx__ordenaRapido (int V[], int esq, int dir) {
  int i,j,x,w;

  // Particiona: separa menores que x para esquerda e maiores para direita
  i = esq;
  j = dir;
  x = V[esq]; // x <- qualquer valor entre V[esq] e V[dir]
  do { // Invariante: max{V[esq],...,V[i-1]  } <= x <= min{V[j+1],...,V[dir]  }
    while ( V[i] < x ) i++;
    while ( x < V[j] ) j--;
    if (i<=j) {
      if (i<j) {
        w    = V[i];
        V[i] = V[j];
        V[j] = w;
        }
      i++;
      j--;
      }
  } while (i<j); // max{V[esq],...,V[j]  } <= x <= min{V[i],...,V[dir]  }

  if (esq<j)
    XbibliotecaLOBx__ordenaRapido(V, esq, j); // ordena parte esquerda
  if (i<dir)
    XbibliotecaLOBx__ordenaRapido(V, i, dir); // ordena parte direita
  }

// ---------------------------------------------------------------------------
// Programa principal (acrescentado para o EP): ordena um vetor de exemplo.
#include <stdio.h>

#define N_EXEMPLO 10

static void imprimeVetor (int V[], int n) {
  int i;
  for (i = 0; i < n; i++) printf("%d ", V[i]);
  printf("\n");
  }

int main (void) {
  int V[N_EXEMPLO] = { 38, 27, 43, 3, 9, 82, 10, 27, 1, 55 };
  printf("Antes:  "); imprimeVetor(V, N_EXEMPLO);
  XbibliotecaLOBx__ordenaRapido(V, 0, N_EXEMPLO-1);
  printf("Depois: "); imprimeVetor(V, N_EXEMPLO);
  return 0;
  }
