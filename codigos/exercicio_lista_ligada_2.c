/* Exercício: remover de uma lista ligada todas as células com conteúdo x. */
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int conteudo;
    struct No *proximo;
} No;

/* ponteiro_para_lista aponta para o ponteiro que guarda o primeiro nó
   (o mesmo truque do No **ptLista da P1): assim o primeiro nó não é um
   caso especial. */
void remover_todos(No **ponteiro_para_lista, int valor) {
    No **ponteiro_atual = ponteiro_para_lista;
    while (*ponteiro_atual != NULL) {
        if ((*ponteiro_atual)->conteudo == valor) {
            No *removido = *ponteiro_atual;
            *ponteiro_atual = removido->proximo;   /* quem apontava para ele pula ele */
            free(removido);
            /* não anda: o novo *ponteiro_atual ainda não foi examinado */
        } else {
            ponteiro_atual = &(*ponteiro_atual)->proximo;
        }
    }
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
    int valores[] = {7, 7, 3, 7, 5, 7};
    No *lista = NULL;
    for (int indice = 5; indice >= 0; indice--) lista = inserir_no_comeco(lista, valores[indice]);
    imprimir(lista);              /* 7 7 3 7 5 7 */
    remover_todos(&lista, 7);
    imprimir(lista);              /* 3 5 */
    while (lista != NULL) { No *proximo = lista->proximo; free(lista); lista = proximo; }
    return 0;
}
