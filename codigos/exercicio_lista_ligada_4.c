#include <stdio.h>

typedef struct prod {
    int codigo;
    int estoque;
    struct prod *prox;
} Produto;

void lerProduto(Produto *p){
    scanf("%d %d", &p->codigo, &p->estoque);
    p->prox = NULL;
}

void mostrarLista(Produto *p){

    while(p != NULL){
        printf("%d %d\n", p->codigo, p->estoque);
        p = p->prox;
    }
}

int main(void){
    Produto a, b;

    lerProduto(&a);
    lerProduto(&b);
    a.prox = &b;

    mostrarLista(&a);
    return 0;
}
