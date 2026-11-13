/* insercao_direta.c — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. Material didático de MAC0122, IME-USP.
 * https://www.ime.usp.br/~leo/mac/mac122/ordena_insercao.html */

// Prof. Leo^nidas - http://www.matematica.br http://line.ime.usp.br
// MAC0122 - 2017/08/21

// Ordena vetor de inteiros via metodo Insercao Direta. Complexidade: O(n^2)

#include <stdio.h>

#define MAX 60
#define INTERVALO 100  // para gerar valores pseudo-aleatorios (modulo 100 => numeros entre 0 e 99)

// Ordena via Insercao Direta
void ordenaViaInsercaoDireta (int vet[], int n) {
  int ii, jj, aux;
  for (ii = 1; ii < n; ii++) { // invariante: vet[0]<=vet[1]<=...<=vet[ii-1]
    aux = vet[ii];
    jj = ii;
    while (jj > 0 && vet[jj-1] > aux) { // invariante antes da comparacao: aux < vet[j], j em { jj+1, jj+2, ..., ii }
      vet[jj] = vet[jj-1];
      jj--;
      }
    vet[jj] = aux; //
    }
  } // complexidade: O(n^2)

int main () {
  int dados[MAX];
  int n, ii, ordem;
  printf("\n\n\nDados iniciais:\n");
  // scanf ("%d", &n); for (ii = 0; ii < n; ii++) scanf("%d", &dados[ii]);
  n = 10;
  for (ii=0; ii<n; ii++) {
    dados[ii] = rand() % INTERVALO;
    printf("%3d", dados[ii]);
    }

  ordenaViaInsercaoDireta(dados, n);

  printf("\nVetor ordenado:\n");
  for (ii = 0; ii < n; ii++)
    printf("%3d", dados[ii]);

  printf("\n");
  return 0;
  }
