#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct registro{
    int id;
    char nome[20];
    struct registro *prox;
} tipoRegistro;

tipoRegistro *criaRegistro(char *nome, int id){
    tipoRegistro *v;

    v = calloc(1, sizeof *v);
    if(v == NULL){
        return NULL;
    }

    v->id = id;
    strcpy(v->nome, nome);
    v->prox = NULL;
    
    return v;
}

void insereFim(tipoRegistro **primeiro, tipoRegistro *novo){

    if(*primeiro == NULL){
        *primeiro = novo;
    } else {
        tipoRegistro *v;
        v = *primeiro;
        
        while(v->prox != NULL){
            v = v->prox;
        }

        v->prox = novo;
    }

}

void imprimeLista(tipoRegistro *p){
    while(p != NULL){
        printf("%d %s\n", p->id, p->nome);
        p = p->prox;
    }
}

void liberaLista(tipoRegistro **primeiro){
    tipoRegistro *v;

    while(*primeiro != NULL){
        v = *primeiro;
        *primeiro = (*primeiro)->prox;
        free(v);
    }    
}

int main(void){
    tipoRegistro *primeiro = NULL;
    tipoRegistro *novo;
    char nomes[5][20] = {
        "aluno 1",
        "aluno 2",
        "aluno 3",
        "aluno 4",
        "aluno 5"
    };

    for(int i = 0; i < 5; i++){
        novo = criaRegistro(nomes[i], i + 1);

        if(novo == NULL){
            liberaLista(&primeiro);
            return 1;
        }

        insereFim(&primeiro, novo);
    }

    imprimeLista(primeiro);
    liberaLista(&primeiro);

    return 0;
}
