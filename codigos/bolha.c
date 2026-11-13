/* bolha.c — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. Material didático de MAC0122, IME-USP.
 * https://www.ime.usp.br/~leo/mac/mac122/ordena_bolha.html */

// Prof. Leo^nidas - http://www.matematica.br http://line.ime.usp.br
// MAC0122 - 2017/08/21

// Ordena vetor de inteiros via metodo da Bolha. Complexidade: O(n^2)

#include <stdio.h>

#define MAX 100
#define INTERVALO 100  // para gerar valores pseudo-aleatorios (modulo 100 => numeros entre 0 e 99)

// Ordena vet[0..n-1] usando metodo da Bolha
void ordenaBolha (int vet[], int n) {
  int ii, jj, aux;
  for (ii=0; ii<n-1; ii++) // invariante: vet[0]<=vet[1]<=...<=vet[ii-1] <= vet[j], j em { ii, ii+1, ..., n-1 }
    for (jj=n-1; jj>ii; jj--)  // invariante: vet[jj] <= vet[j], j em { jj+1, jj+2, ..., n-1 }
      if (vet[jj-1]>vet[jj]) { // troque-os
        aux = vet[jj-1];
        vet[jj-1] = vet[jj];
        vet[jj] = aux;
        }
  }

int main (void) {
  int dados[MAX];
  int ii, n;

  printf("\n\n\nDados iniciais:\n");
  // scanf ("%d", &n); for (ii = 0; ii < n; ii++) scanf("%d", &dados[ii]);
  n = 10;
  for (ii=0; ii<n; ii++) {
    dados[ii] = rand() % INTERVALO;
    printf("%3d", dados[ii]);
    }

  ordenaBolha(dados, n);

  printf("\nOrdenado:\n");
  for (ii=0; ii<n; ii++)
    printf("%3d", dados[ii]);
  printf("\n");

  return 0;
  }
