/* recursao_maior.c — EP MAC0122
 * Escrito pelo grupo, seguindo a P1 (Q6): maior(int v[], int k, int n).
 * Base: FEOFILOFF, P. Algoritmos em linguagem C. Elsevier, 2009 (cap. de recursão). */

#include <stdio.h>

/* Devolve o índice de um elemento máximo de v[k..n-1].
 * Supõe 0 <= k < n.
 * Caso base: se o trecho tem um só elemento (k == n-1), ele é o máximo.
 * Caso geral: acha o máximo de v[k+1..n-1] e compara com v[k]. */
int maior (int v[], int k, int n) {
  int j;
  if (k == n - 1)
    return k;
  j = maior(v, k + 1, n);   /* índice do máximo de v[k+1..n-1] */
  if (v[k] >= v[j])
    return k;
  return j;
  }

int main (void) {
  int v[] = { 12, 7, 31, 4, 31, 18, -2, 25 };
  int n = 8, i, im;

  printf("v = ");
  for (i = 0; i < n; i++) printf("%d ", v[i]);
  printf("\n");

  im = maior(v, 0, n);
  printf("Indice do maior: %d (v[%d] = %d)\n", im, im, v[im]);
  return 0;
  }
