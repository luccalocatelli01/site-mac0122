/* fusao.c — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. Material didático de MAC0122, IME-USP.
 * https://www.ime.usp.br/~leo/mac/mac122/ordena_fusao.html */

// Prof. Leo^nidas - http://www.matematica.br http://line.ime.usp.br
// MAC0122 - 2017/08/23

// Biblioteca para: ordenar vetor de inteiros via metodo da Fusao. Complexidade: O(n log n)
// Exemplo de metodo no paradgma "DIVISAO e CONQUISTA"
// Invocar: #include "ordena_fusao.h"
//          ...
//          XbibliotecaLOBx__ordenaMetadesFusao(int V[], int esq, int dir)

// Ordena por Fusao (Merge Sort)
// Programa recursivo para ordenar uma lista de inteiros usando a ideia ordenar 2 metades e depois fundi-las.

#define MAX       25000 // maximo de elementos (TAMINI + NTESTES * PASSO) - veja em 'ordena_compara_metodos.c'

// Se V[esq]<=V[esq+1]<=...<=V[med] e V[med+1]<=V[med+2]<=...<=V[dir]
// Entao funde em ordem unica V[esq] <= V[esq+1] <= ... <= V[dir-1] <= V[dir]
void XbibliotecaLOBx__Fusao (int V[], int esq, int med, int dir) {
  int Aux[MAX], i, j, k, e1, d1, e2, d2; // dir=e2
  e1 = esq;   d1 = med;
  e2 = med+1; d2 = dir;
  k = i = e1;
  j = e2;
  while (i<=d1 && j<=d2) { // compara os "topos", retire o menor dos dois colocando em nova pilha
    if (V[i]<V[j]) // "topo" da pilha 1 e' o menor
      Aux[k++] = V[i++];
    else
    if (V[i]>V[j]) // "topo" da pilha 2 e' o menor
      Aux[k++] = V[j++];
    else { // havendo empate pegue os dois "topos"
      Aux[k++] = V[i++];
      Aux[k++] = V[j++];
      }
    }
  while (i<=d1) // copia restante de V[e1..d1]
    Aux[k++] = V[i++];
  while (j<=d2)  // copia restante de V[e2..d2]
    Aux[k++] = V[j++];
  for (i=e1; i<=d2; i++) // reconstroi V[e1..d2] ordenado
    V[i]=Aux[i];
  }

// Ordena V[esq .. dir] usando tecnica de DIVISAO E CONQUISTA, divida em 2 metades
// ordene cada uma e depois funda para obter ordem das 2 partes
void XbibliotecaLOBx__ordenaMetadesFusao (int V[], int esq, int dir) {
  int med;
  med = (esq+dir)/2;
  if (esq<med)
    XbibliotecaLOBx__ordenaMetadesFusao(V, esq, med);   // ordena V[esq .. m]
  if (med<dir)
    XbibliotecaLOBx__ordenaMetadesFusao(V, med+1, dir); // ordena V[m+1 .. dir]
  XbibliotecaLOBx__Fusao(V, esq, med, dir); // funde em ordem unica V[esq .. m] com V[m+1 .. dir]
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
  XbibliotecaLOBx__ordenaMetadesFusao(V, 0, N_EXEMPLO-1);
  printf("Depois: "); imprimeVetor(V, N_EXEMPLO);
  return 0;
  }
