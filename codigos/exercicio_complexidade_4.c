#include <stdio.h>
#include <time.h>

unsigned long chamadas;

int fib_rec(int n)
{
    chamadas++;
    if (n <= 1) {
        return 1;
    }
    return fib_rec(n - 1) + fib_rec(n - 2);
}

int fib_it(int n)
{
    int anterior;
    int atual;
    int soma;
    int i;

    if (n <= 1) {
        return 1;
    }

    anterior = 1;
    atual = 1;

    for (i = 2; i <= n; i++) {
        soma = anterior + atual;
        anterior = atual;
        atual = soma;
    }

    return atual;
}

int main(void)
{
    int valores[3];
    int i;
    int n;
    int resultado_rec;
    int resultado_it;
    clock_t inicio;
    clock_t fim;
    double tempo_rec;
    double tempo_it;

    valores[0] = 30;
    valores[1] = 35;
    valores[2] = 40;

    for (i = 0; i < 3; i++) {
        n = valores[i];

        chamadas = 0;
        inicio = clock();
        resultado_rec = fib_rec(n);
        fim = clock();
        tempo_rec = (double) (fim - inicio) / CLOCKS_PER_SEC;

        inicio = clock();
        resultado_it = fib_it(n);
        fim = clock();
        tempo_it = (double) (fim - inicio) / CLOCKS_PER_SEC;

        printf("n = %d\n", n);
        printf("rec: %d | chamadas: %lu | tempo: %.6f s\n",
               resultado_rec, chamadas, tempo_rec);
        printf("it:  %d | iteracoes: %d | tempo: %.6f s\n\n",
               resultado_it, n > 1 ? n - 1 : 0, tempo_it);
    }

    return 0;
}
