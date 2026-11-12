#include <stdio.h>

int comparacoes;

int particiona(int V[], int esq, int dir) {
    int pivo = V[dir];
    int entra = esq;

    for (int i = esq; i < dir; i++) {
        comparacoes++;
        if (V[i] <= pivo) {
            int w = V[i];
            V[i] = V[entra];
            V[entra] = w;
            entra++;
        }
    }

    int w = V[dir];
    V[dir] = V[entra];
    V[entra] = w;
    return entra;
}

void ordenaRapido(int V[], int esq, int dir) {
    if (esq >= dir) {
        return;
    }

    int entra = particiona(V, esq, dir);
    ordenaRapido(V, esq, entra - 1);
    ordenaRapido(V, entra + 1, dir);

    printf("Trecho ordenado: ");
    for (int i = esq; i <= dir; i++) {
        printf("%d ", V[i]);
    }
    printf("\n");
}

int main(void) {
    int v[8] = {7, 5, 3, 6, 3, 9, 8, 4};
    comparacoes = 0;
    ordenaRapido(v, 0, 7);
    printf("Comparacoes: %d\n", comparacoes);

    int w[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    comparacoes = 0;
    ordenaRapido(w, 0, 7);
    printf("Comparacoes com o vetor ja ordenado: %d\n", comparacoes);
    return 0;
}
