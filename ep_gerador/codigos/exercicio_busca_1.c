/* Exercício: rastrear a busca binária, mostrando e, m e d a cada passo. */
#include <stdio.h>

int busca_binaria(int vetor[], int quantidade, int procurado) {
    int esquerda = 0, direita = quantidade - 1;
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;   /* sem overflow */
        printf("e=%d m=%d d=%d v[m]=%d\n", esquerda, meio, direita, vetor[meio]);
        if (vetor[meio] == procurado) return meio;
        if (vetor[meio] < procurado) esquerda = meio + 1;
        else direita = meio - 1;
    }
    return -1;
}

int main(void) {
    int vetor[] = {10, 20, 30, 40, 50, 60, 70};
    printf("-> resultado %d\n\n", busca_binaria(vetor, 7, 55));
    printf("-> resultado %d\n", busca_binaria(vetor, 7, 20));
    return 0;
}
