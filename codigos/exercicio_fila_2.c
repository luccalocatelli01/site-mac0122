/* Exercício: fila circular num vetor, com tamanho e aviso de fila cheia. */
#include <stdio.h>

#define CAPACIDADE 5

typedef struct {
    int itens[CAPACIDADE];
    int inicio;        /* posição do primeiro da fila */
    int quantidade;    /* quantos elementos há na fila */
} Fila;

int tamanho(const Fila *fila) { return fila->quantidade; }

/* Devolve 0 se a fila estava cheia. */
int inserir(Fila *fila, int valor) {
    if (fila->quantidade == CAPACIDADE) return 0;
    int fim = (fila->inicio + fila->quantidade) % CAPACIDADE;   /* dá a volta no vetor */
    fila->itens[fim] = valor;
    fila->quantidade++;
    return 1;
}

/* Supõe fila não vazia. */
int remover(Fila *fila) {
    int valor = fila->itens[fila->inicio];
    fila->inicio = (fila->inicio + 1) % CAPACIDADE;
    fila->quantidade--;
    return valor;
}

int main(void) {
    Fila fila = { .inicio = 0, .quantidade = 0 };
    for (int valor = 1; valor <= 5; valor++) inserir(&fila, valor);
    printf("inserir 6 na fila cheia: %s\n", inserir(&fila, 6) ? "ok" : "fila cheia");
    int primeiro = remover(&fila);
    int segundo = remover(&fila);
    printf("%d %d\n", primeiro, segundo);                /* 1 2 */
    inserir(&fila, 6); inserir(&fila, 7);                 /* usam as posições 0 e 1 de novo */
    printf("tamanho: %d\n", tamanho(&fila));              /* 5 */
    while (tamanho(&fila) > 0) printf("%d ", remover(&fila));   /* 3 4 5 6 7 */
    printf("\n");
    return 0;
}
