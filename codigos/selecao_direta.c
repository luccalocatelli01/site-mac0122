/* selecao_direta.c — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. Material didático de MAC0122, IME-USP.
 * https://www.ime.usp.br/~leo/mac/mac122/ordena_selecao.html */

// Prof. Leo^nidas - http://www.matematica.br http://line.ime.usp.br
// MAC0122 - 2017/08/21

// Ordena vetor de inteiros via metodo Selecao Direta. Complexidade: O(n^2)

#include <stdio.h>

#define MAX 60
#define INTERVALO 100  // para gerar valores pseudo-aleatorios (modulo 100 => numeros entre 0 e 99)

int determineIndiceDoMenor (int vet[], int ini, int n) {
  int indice, menor, i;
  indice = ini;
  menor = vet[ini];
  for (i=ini+1; i<n; i++) { // invariante: vet[indice] <= vet[j], j em { ini, ini+1, ini+2, ... i-2, i-1 }
    if (menor>vet[i]) { // novo menor
      menor = vet[i];
      indice = i;
      }
    } // complexidade: O(n)
  return indice; // indice do menor entre vet[ini .. n-1]
  }

// Ordena via Selecao Direta
void ordenaViaSelecaoDireta (int vet[], int n) {
  int ii, imin, aux;
  for (ii = 0; ii < n-1; ii++) { // invariante: vet[0]<=vet[1]<=...<=vet[ii-1] <= vet[j], j em { ii, ii+1, ..., n-1 }
    imin = determineIndiceDoMenor(vet, ii, n);
    aux = vet[ii];
    vet[ii] = vet[imin];
    vet[imin] = aux;
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

  ordenaViaSelecaoDireta(dados, n);

  printf("\nVetor ordenado:\n");
  for (ii = 0; ii < n; ii++)
    printf("%3d", dados[ii]);

  printf("\n");
  return 0;
  }
