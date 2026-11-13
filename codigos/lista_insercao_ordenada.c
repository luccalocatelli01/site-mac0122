/* lista_insercao_ordenada.c — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. Material didático de MAC0122, IME-USP.
 * https://www.ime.usp.br/~leo/mac/mac122/lista_ligada/introducao_lista_ligada.html
 * Mudança: inserção ordenada com No **ptLista, como cobrado na P1 (Q3). */

#include <stdio.h>
#include <stdlib.h>

typedef struct no {
  int info;
  struct no *prox;
  } No;

/* Insere x na lista apontada por *ptLista, mantendo ordem crescente.
 * Recebe o ENDEREÇO do apontador para o início, porque se x for o menor
 * o primeiro nó muda e quem chamou precisa ver a mudança. */
void insereOrdenado (No **ptLista, int x) {
  No *novo, **pt;
  novo = malloc(sizeof(No));
  if (novo == NULL) {
    printf("Erro: sem memoria\n");
    return;
    }
  novo->info = x;
  pt = ptLista;
  while (*pt != NULL && (*pt)->info < x)  /* anda até o primeiro nó com info >= x */
    pt = &(*pt)->prox;
  novo->prox = *pt;
  *pt = novo;   /* liga o novo no lugar certo (também cobre o caso do primeiro nó) */
  }

void imprimeLista (No *lista) {
  No *p;
  for (p = lista; p != NULL; p = p->prox)
    printf("%d -> ", p->info);
  printf("NULL\n");
  }

void liberaLista (No *lista) {
  No *p;
  while (lista != NULL) {
    p = lista;
    lista = lista->prox;
    free(p);
    }
  }

int main (void) {
  No *lista = NULL;
  int valores[] = { 30, 10, 50, 20, 10, 5, 40 };
  int i, n = 7;
  for (i = 0; i < n; i++) {
    insereOrdenado(&lista, valores[i]);
    printf("insere %2d: ", valores[i]);
    imprimeLista(lista);
    }
  liberaLista(lista);
  return 0;
  }
