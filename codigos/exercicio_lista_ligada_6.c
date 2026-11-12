#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int chave;
    struct No *prox;
} No;

void imprime(No *lista){
    if(lista == NULL){
        printf("\n");
        return;
    }

    printf("%d ", lista->chave);

    imprime(lista->prox);
}

void inserir(No **ptlista, int valor){

    No *novo = (No*) malloc(sizeof(No));
    novo->chave = valor;

    if(*ptlista == NULL || (*ptlista)->chave >= valor){
        novo->prox = *ptlista;
        *ptlista = novo;
        return;
    }

    No *atual = *ptlista;
    while(atual->prox != NULL && atual->prox->chave < valor){
        atual = atual->prox;
    }

    novo->prox = atual->prox;
    atual->prox = novo;
    
}

int main(void){
    No *lista = NULL;

    inserir(&lista, 5);
    inserir(&lista, 2);
    inserir(&lista, 8);
    inserir(&lista, 1);
    inserir(&lista, 6);

    imprime(lista);
    return 0;
}
