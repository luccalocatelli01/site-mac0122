/* Exercício: inverter uma lista ligada sem criar células novas. */
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int conteudo;
    struct No *proximo;
} No;

/* Inverte a lista e devolve o endereço do novo primeiro nó.
   Cada nó tem o ponteiro "proximo" virado para trás, um de cada vez. */
No *inverter(No *lista) {
    No *anterior = NULL;
    No *atual = lista;
    while (atual != NULL) {
        No *seguinte = atual->proximo;   /* guarda antes de perder */
        atual->proximo = anterior;       /* vira a seta */
        anterior = atual;                /* anda os dois um passo */
        atual = seguinte;
    }
    return anterior;                     /* o antigo último nó */
}

No *inserir_no_comeco(No *lista, int valor) {
    No *novo = malloc(sizeof(No));
    novo->conteudo = valor;
    novo->proximo = lista;
    return novo;
}

void imprimir(No *lista) {
    for (No *atual = lista; atual != NULL; atual = atual->proximo) printf("%d ", atual->conteudo);
    printf("\n");
}

int main(void) {
    No *lista = NULL;
    for (int valor = 5; valor >= 1; valor--) lista = inserir_no_comeco(lista, valor);
    imprimir(lista);            /* 1 2 3 4 5 */
    lista = inverter(lista);
    imprimir(lista);            /* 5 4 3 2 1 */
    while (lista != NULL) { No *proximo = lista->proximo; free(lista); lista = proximo; }
    return 0;
}
