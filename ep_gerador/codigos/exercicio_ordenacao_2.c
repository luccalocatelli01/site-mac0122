/* Exercício: quantas comparações o quicksort faz num vetor já ordenado? */
#include <stdio.h>
#include <stdlib.h>

long comparacoes = 0;

/* separa v[inicio..fim] usando o último elemento como pivô */
int separa(int vetor[], int inicio, int fim) {
    int pivo = vetor[fim], posicao = inicio;
    for (int indice = inicio; indice < fim; indice++) {
        comparacoes++;
        if (vetor[indice] <= pivo) {
            int temporario = vetor[indice]; vetor[indice] = vetor[posicao]; vetor[posicao] = temporario;
            posicao++;
        }
    }
    int temporario = vetor[fim]; vetor[fim] = vetor[posicao]; vetor[posicao] = temporario;
    return posicao;
}

void quicksort(int vetor[], int inicio, int fim) {
    if (inicio >= fim) return;
    int posicao_do_pivo = separa(vetor, inicio, fim);
    quicksort(vetor, inicio, posicao_do_pivo - 1);
    quicksort(vetor, posicao_do_pivo + 1, fim);
}

int main(void) {
    int tamanhos[] = {10, 100, 1000};
    for (int teste = 0; teste < 3; teste++) {
        int quantidade = tamanhos[teste];
        int *ordenado = malloc(quantidade * sizeof(int));
        int *embaralhado = malloc(quantidade * sizeof(int));
        srand(1);
        for (int indice = 0; indice < quantidade; indice++) {
            ordenado[indice] = indice;
            embaralhado[indice] = rand() % 100000;
        }
        comparacoes = 0; quicksort(ordenado, 0, quantidade - 1);
        long no_ordenado = comparacoes;
        comparacoes = 0; quicksort(embaralhado, 0, quantidade - 1);
        printf("n=%4d  ordenado: %6ld comparações (n(n-1)/2 = %6d)  aleatório: %6ld\n",
               quantidade, no_ordenado, quantidade * (quantidade - 1) / 2, comparacoes);
        free(ordenado); free(embaralhado);
    }
    return 0;
}
