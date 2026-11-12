#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    char valor;
    struct no *esq;
    struct no *dir;
} no;

no *novono(char valor, no *esq, no *dir){
    no *novo = (no*) malloc(sizeof(no));
    novo->valor = valor;
    novo->esq = esq;
    novo->dir = dir;

    return novo;
}

void pre(no *raiz){
    if(raiz == NULL){
        return;
    }

    printf(" %c", raiz->valor);
    pre(raiz->esq);
    pre(raiz->dir);
}

void em(no *raiz){
    if(raiz == NULL){
        return;
    }

    
    em(raiz->esq);
    printf(" %c", raiz->valor);
    em(raiz->dir);
}

void pos(no *raiz){
    if(raiz == NULL){
        return;
    }

    
    pos(raiz->esq);
    pos(raiz->dir);
    printf(" %c", raiz->valor);
}

int altura(no *raiz){
    if(raiz == NULL){
        return -1;
    }

    int dir = altura(raiz->dir);
    int esq = altura(raiz->esq);
    int x;

    if(dir >= esq) x = dir;
    else x = esq;

    return 1 + x;
}

int contaFolhas(no *raiz){
    if(raiz == NULL){
        return 0;
    }
    if(raiz->esq == NULL && raiz->dir == NULL){
        return 1;
    }

    return contaFolhas(raiz->dir) + contaFolhas(raiz->esq);
}

int main(void){
    no *a = novono('A', NULL, NULL);
    no *b = novono('B', NULL, NULL);
    no *c = novono('C', NULL, NULL);
    no *d = novono('D', NULL, NULL);
    no *e = novono('E', NULL, NULL);
    no *vezes = novono('*', b, c);
    no *mais = novono('+', a, vezes);
    no *divide = novono('/', d, e);
    no *raiz = novono('-', mais, divide);

    pre(raiz);
    printf("\n");
    em(raiz);
    printf("\n");
    pos(raiz);
    printf("\n");
    printf("Altura: %d\n", altura(raiz));
    printf("Folhas: %d\n", contaFolhas(raiz));
    return 0;
}
