/* fibonacci.c — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. Material didático de MAC0122, IME-USP.
 * https://www.ime.usp.br/~leo/mac/mac122/introducao_recursividade_fibonacci_gettime.html */

// Prof. Leo^nidas - http://www.matematica.br http://line.ime.usp.br
// MAC0122 - 2017/08/04

// Eficiencia = algoritmos + estuturas de dados + matematica + ...
// Sequencia de Fibonacci: Fi = 1, se i=1 ou i=2 e Fi = F(i-1)+F(i-2), se i>2

#include <stdio.h>
#include <time.h> // clock_t, clock()

// Fibonacci iterado: computa de modo "guloso", a partir do menor indice, nunca repetindo (O(n))
int fib (int n) {
  int i, F1=1, F2=1, F;
  if (n<3) return 1;
  for (i=3; i<=n; i++) {
    F = F1+F2;
    F1 = F2;
    F2 = F;
    }
  return F;
  }

// Fibonacci recursivo: computa repetidas vezes (O(2^n))
int fibRec (int n) { // os finalizadores ';' sao opcionais em Python
  if (n==1 || n==2) return 1;     // final de recorrencia
  return fibRec(n-1) + fibRec(n-2); // senao devolve
  }

int main (void) {
  int n, fibA; clock_t tempo_inicial, tempo_final;
  scanf("%d", &n);

  tempo_inicial = clock(); // "dispara o cronometro"...
  fibA = fib(n);
  tempo_final = clock();
  printf("Iterativo: %3d -> %3d em %f segundos\n", n, fibA, (double)(tempo_final - tempo_inicial) / CLOCKS_PER_SEC);

  tempo_inicial = clock(); // "dispara o cronometro"...
  fibA = fibRec(n);
  tempo_final = clock();
  printf("Recursivo: %3d -> %3d em %f segundos\n", n, fibA, (double)(tempo_final - tempo_inicial) / CLOCKS_PER_SEC);
  return 0;
  }
