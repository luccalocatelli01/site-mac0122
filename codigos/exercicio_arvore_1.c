/* Exercício: contar os nós e imprimir as folhas (em ordem e-r-d) de uma árvore binária. */
#include <stdio.h>
#include <stdlib.h>

typedef struct NoDaArvore {
    int conteudo;
    struct NoDaArvore *esquerda, *direita;
} NoDaArvore;

/* nós da árvore = 0 se vazia; senão 1 (a raiz) + nós da esquerda + nós da direita */
int contar_nos(NoDaArvore *raiz) {
    if (raiz == NULL) return 0;
    return 1 + contar_nos(raiz->esquerda) + contar_nos(raiz->direita);
}

/* e-r-d: esquerda, raiz, direita; só imprime quem não tem filhos */
void imprimir_folhas(NoDaArvore *raiz) {
    if (raiz == NULL) return;
    imprimir_folhas(raiz->esquerda);
    if (raiz->esquerda == NULL && raiz->direita == NULL) printf("%d ", raiz->conteudo);
    imprimir_folhas(raiz->direita);
}

NoDaArvore *novo_no(int conteudo, NoDaArvore *esquerda, NoDaArvore *direita) {
    NoDaArvore *no = malloc(sizeof(NoDaArvore));
    no->conteudo = conteudo;
    no->esquerda = esquerda;
    no->direita = direita;
    return no;
}

void liberar(NoDaArvore *raiz) {
    if (raiz == NULL) return;
    liberar(raiz->esquerda);
    liberar(raiz->direita);
    free(raiz);
}

int main(void) {
    /*        1
            /   \
           2     3
          / \     \
         4   5     6      */
    NoDaArvore *raiz = novo_no(1, novo_no(2, novo_no(4, NULL, NULL), novo_no(5, NULL, NULL)),
                                  novo_no(3, NULL, novo_no(6, NULL, NULL)));
    printf("nós: %d\n", contar_nos(raiz));   /* 6 */
    printf("folhas: ");
    imprimir_folhas(raiz);                    /* 4 5 6 */
    printf("\n");
    liberar(raiz);
    return 0;
}
