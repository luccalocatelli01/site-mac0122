#include <stdio.h>

typedef struct no {
    int valor;
    struct no *esq;
    struct no *dir;
} No;

int somaArvore(No *raiz){
    if(raiz == NULL){
        return 0;
    }  

    int somaEsq = somaArvore(raiz->esq);
    int somaDir = somaArvore(raiz->dir);
    
    return raiz->valor + somaEsq + somaDir;
}

void posOrdem(No *raiz){
    if(raiz == NULL){
        return;
    }
    
    posOrdem(raiz->esq);
    posOrdem(raiz->dir);
    printf("%d\n", raiz->valor);
    
}

void preOrdem(No *raiz){
    if(raiz == NULL){
        return;
    }

    printf("%d\n", raiz->valor);
    preOrdem(raiz->esq);
    preOrdem(raiz->dir);
}

void emOrdem(No *raiz){

    if(raiz == NULL){
        return;
    }
    
    emOrdem(raiz->esq);
    printf("%d\n", raiz->valor);
    emOrdem(raiz->dir);
    
    
}

int main(void){
    No a, b, c;

    a.valor = 10;
    a.esq = &b;
    a.dir = &c;

    b.valor = 4;
    b.esq = NULL;
    b.dir = NULL;

    c.valor = 7;
    c.esq = NULL;
    c.dir = NULL;

    printf("%d\n", somaArvore(&a));
    printf("Pós ordem:\n");
    posOrdem(&a);
    printf("Pré ordem:\n");
    preOrdem(&a);
    printf("Em ordem:\n");
    emOrdem(&a);


    return 0;
}
