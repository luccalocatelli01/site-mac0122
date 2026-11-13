/* heapsort.c — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. Material didático de MAC0122, IME-USP.
 * https://www.ime.usp.br/~leo/mac/mac122/ordena_monte.html */

// Prof. Leo^nidas - http://www.matematica.br http://line.ime.usp.br
// MAC0122 - 2017/08/23

// Biblioteca para: ordenar vetor de inteiros via metodo da Propriedade de Monte. Complexidade: O(n log n)
// Exemplo de metodo no paradgma "DIVISAO e CONQUISTA"
// Invocar: #include "ordena_monte.h"
//          ...
//          XbibliotecaLOBx__ordenaMonte(int V[], int n);

// Ordena vetor de inteiros via metodo da Ordenacao por Propriedade de Monte. Complexidade: O(n log)
// Propriedade de Monte ("Heap Sort"):
//   para cada no de uma arvore, a informacao nele e' maior ou igual a de seus filhos
//   info(no) >= max{ info(no.esq), info(no.dir) }
// Usa um vetor para a arvore: para um no na posicao i do vetor, seus filhos estao nas posicoes V[2*i+1] e V[2*i+2]
// Observacao importante: se uma arvore e' o Monte, entao o maior elemento esta na primeira posicao, ou seja,
//   V[0] >= V[i], para todo i
// Programa recursivo para ordenar uma lista de inteiros usando a ideia manter propriedade de Monte e separa o maior.

// Macro para trocar par de valores
#define XbibliotecaLOBx__troquePar(V, IA, IB) {int aux = V[IA]; V[IA] = V[IB]; V[IB] = aux;}

// Supondo que V[] tem a propriedade de Monte exceto talvez em V[k]
// Entao "desca" o V[k] trocando-o com o maior filho ate' que fique maior que os 2 filhos
// Neste momento a propriedade de Monte estara restaurada
void XbibliotecaLOBx__desceElementoMonte (int V[], int k, int N) {
  int j;
  while (2*k + 1 < N) { // tem algum filho?  (V[k] -> { V[2*k, V[2*k+2] }
    j = 2*k + 1; // primeiro filho de "k"
    if (j < N-1 && V[j] < V[j+1]) // se tem 2 filhos e maior em j+1, aponte para j+1
      j++;
    if (V[k] >= V[j]) {
       break;
       }
    XbibliotecaLOBx__troquePar(V, k, j); // o "define" acima colocara aquele codigo aqui
    k = j; // recome com o "maior filho"
    }
  }

void XbibliotecaLOBx__ordenaMonte (int V[], int tam) {
  int k, N = tam;
  // Cria propriedade inicial de Monte
  for (k = N/2-1; k >= 0; k--) // comece pelo primeiro no que tem filho
    XbibliotecaLOBx__desceElementoMonte(V, k, N); // desca-o de modo sua sub-arvore ser Monte
  while (N > 0) {
    // Elemento no topo e' maior => passe para ultima posicao
    XbibliotecaLOBx__troquePar(V, 0, N-1);
    // Estragou propriedade de monte na posicao 0, desca para recuperar propriedade
    XbibliotecaLOBx__desceElementoMonte(V, 0, --N);
    }
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
  XbibliotecaLOBx__ordenaMonte(V, N_EXEMPLO);
  printf("Depois: "); imprimeVetor(V, N_EXEMPLO);
  return 0;
  }
