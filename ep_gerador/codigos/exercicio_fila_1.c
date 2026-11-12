/* Exercício: fila feita com duas pilhas. */
#include <stdio.h>

#define TAMANHO 100

typedef struct {
    int itens[TAMANHO];
    int topo;                 /* -1 = vazia */
} Pilha;

void empilhar(Pilha *pilha, int valor) { pilha->itens[++pilha->topo] = valor; }
int desempilhar(Pilha *pilha) { return pilha->itens[pilha->topo--]; }
int pilha_vazia(const Pilha *pilha) { return pilha->topo == -1; }

/* entrada recebe quem chega; saida entrega quem sai.
   Ao passar tudo de entrada para saida, a ordem se inverte e o mais antigo
   fica no topo de saida. */
typedef struct {
    Pilha entrada;
    Pilha saida;
} Fila;

void inserir(Fila *fila, int valor) {
    empilhar(&fila->entrada, valor);
}

int remover(Fila *fila) {
    if (pilha_vazia(&fila->saida)) {
        while (!pilha_vazia(&fila->entrada)) {
            empilhar(&fila->saida, desempilhar(&fila->entrada));
        }
    }
    return desempilhar(&fila->saida);   /* supõe fila não vazia */
}

int main(void) {
    Fila fila = { .entrada = { .topo = -1 }, .saida = { .topo = -1 } };
    inserir(&fila, 1); inserir(&fila, 2); inserir(&fila, 3);
    printf("%d ", remover(&fila));      /* 1 */
    inserir(&fila, 4);
    printf("%d ", remover(&fila));      /* 2 */
    printf("%d ", remover(&fila));      /* 3 */
    printf("%d\n", remover(&fila));     /* 4 */
    return 0;
}
