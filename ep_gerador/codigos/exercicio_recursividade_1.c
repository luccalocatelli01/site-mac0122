/* Exercício: soma dos elementos positivos de v[0..n-1], recursiva. */
#include <stdio.h>

/* Ideia: a soma dos positivos de v[0..n-1] é a soma dos positivos de
   v[0..n-2] mais v[n-1], se v[n-1] for positivo. Base: n == 0 -> soma 0
   (um vetor vazio não tem positivos). */
int soma_dos_positivos(int vetor[], int quantidade) {
    if (quantidade == 0) return 0;
    int soma_do_resto = soma_dos_positivos(vetor, quantidade - 1);
    int ultimo = vetor[quantidade - 1];
    return ultimo > 0 ? soma_do_resto + ultimo : soma_do_resto;
}

int main(void) {
    int vetor[] = {3, -2, 5, 0, -7, 4};
    printf("%d\n", soma_dos_positivos(vetor, 6));   /* 12 */
    printf("%d\n", soma_dos_positivos(vetor, 0));   /* 0 */
    return 0;
}
