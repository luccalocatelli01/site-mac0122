#include <stdio.h>
#include <string.h>

typedef struct registro {
    int id;
    char nome[20];
    struct registro *prox;
} tipoRegistro;

int main(void){
    tipoRegistro ana;
    tipoRegistro bruno;

    strcpy(ana.nome, ("Ana"));
    ana.id = 1;
    tipoRegistro *p = &ana;
    ana.prox = &bruno;
    p = p->prox;
    strcpy(p->nome, ("Bruno"));
    p->id = 2;
    p->prox = NULL;

    p = &ana;
    while(p != NULL){
        printf("%d %s\n", p->id, p->nome);
        p = p->prox;
    }

    return 0;
}
