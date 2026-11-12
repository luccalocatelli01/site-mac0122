/* Exercício: Fibonacci recursivo x iterativo — quantas chamadas e quantas somas. */
#include <stdio.h>

long chamadas = 0;

long fibonacci_recursivo(int posicao) {
    chamadas++;
    if (posicao <= 1) return posicao;
    return fibonacci_recursivo(posicao - 1) + fibonacci_recursivo(posicao - 2);
}

long fibonacci_iterativo(int posicao) {
    long anterior = 0, atual = 1;          /* F(0) e F(1) */
    if (posicao == 0) return 0;
    for (int passo = 2; passo <= posicao; passo++) {
        long proximo = anterior + atual;   /* uma soma por passo: n - 1 somas */
        anterior = atual;
        atual = proximo;
    }
    return atual;
}

int main(void) {
    int posicoes[] = {5, 10, 20, 30};
    for (int indice = 0; indice < 4; indice++) {
        int posicao = posicoes[indice];
        chamadas = 0;
        long resultado = fibonacci_recursivo(posicao);
        printf("F(%d) = %ld | recursivo: %ld chamadas | iterativo: %ld\n",
               posicao, resultado, chamadas, fibonacci_iterativo(posicao));
    }
    return 0;
}
