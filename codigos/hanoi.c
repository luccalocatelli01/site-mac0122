/* hanoi.c — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. MAC0122 (2026), e-Disciplinas USP, pasta "Exemplos da semana 02",
 * arquivo aula_04_hanoi.c.
 * Mudanças do EP: mover_disco e hanoi passaram de int (sem return) para void, e foi
 * retirada a variável não usada 'tempoh', para compilar sem aviso com -Wall -Wextra. */

// Aula 04 (2026/08/05)

// Complexidade de algoritmo
// Modelo: divisao e conquista
// Movimentar de modo otimo n discos de A para C

#include <stdio.h>
#include <time.h> // clock_t, clock()

#define DEPURACAO 0

int totalm; // global para contar movimentos

void mover_disco (int n, int origem, int destino) {
  if (DEPURACAO) printf("%d (%5d): %d -> %d\n", n, totalm, origem, destino); //D
  totalm++;
  }

// Mover n discos de A (origem) para C (destino), usando B como auxiliar
void hanoi (int n, int A, int C, int B) {
  if (n==1) mover_disco(1, A, C);
  else {
    hanoi(n-1, A, B, C);
    mover_disco(n, A, C);
    hanoi(n-1, B, C, A);
    }
  }

int main (void) {
  int i;
  clock_t tempo_inicial, tempo_final;
  double t_rec;
  printf("  n | Hanoi(n)    | Tempo \n");
  for (i=1; i<20; i++) {
    if (DEPURACAO) printf("-------------\n"); //D
    totalm = 0; // global para contar movimentos
    tempo_inicial = clock(); // "dispara o cronometro"...
    hanoi(i, 1, 3, 2);
    tempo_final = clock();
    t_rec = (double)(tempo_final - tempo_inicial) / CLOCKS_PER_SEC; // tempo_final-tempo_inicial
    printf(" %2d | %11d | %13.8f \n", i, totalm, t_rec);
    }
  return 0; // A zero value from main() indicates success
  }
