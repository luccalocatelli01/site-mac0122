/* fila_lista.h — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. Material didático de MAC0122, IME-USP.
 * https://www.ime.usp.br/~leo/mac/mac122/lista_ligada/fila_lista_ligada_struct.h */

// Prof. Leo^nidas - http://www.matematica.br http://line.ime.usp.br
// MAC0122 - 2017/10/31

// Bibliotec para fila (primeiro a entrar, primeiro a sair) ou "queue" (FIFO - "first in, first out")
// Usa conceito de apontador para apontador ("**apont")
// Exemplo usando lista ligada (com 'typedef' e 'struct'), inserir e remover da fila

#include <string.h> // para 'strcpy(...)'
#include <stdlib.h> // para 'malloc(...)'

#define TAM 10 // limite para numero de caracteres para a chave do registro

typedef struct regFila {  // define estrutura 'dado'
  int ind;
  char nome[TAM];
  struct regFila *prox; // aponta para uma estrutura 'dado'
  } tipoRegistroFila;

// Para depuracao: imprimir registro
void imprimir (tipoRegistroFila *item) {
  if (item == NULL) { // fila vazia
    printf("<vazio>");
    return;
    }
  printf("(%d, %s)", item->ind, item->nome);
  }

// Testar: imprimir fila toda (comecando do primeiro)
void imprimirFilaToda (tipoRegistroFila *primeiro) {
  tipoRegistroFila *item = primeiro;
  int i;
  printf("Situacao da fila: ");
  while (item!=NULL) {
    imprimir(item);
    printf(" ");
    item = item->prox; //printf(" - %s\n", nomes[i]);
    }
  printf("\n");
  }

int filaNaoVazia (tipoRegistroFila *primeiro) {
  if (primeiro != NULL) // fila vazia (apontado eh vazio)
    return 1;
  return 0;
  }

// Criar item de registro
tipoRegistroFila *criarRegFila (int indice, char *nome) {
  tipoRegistroFila *item = malloc(sizeof(tipoRegistroFila));
  // Nao basta apontar para "string" apontada por "nome", precisa copiar todos seus caracteres na posicao nova apontada por "item"
  strcpy(item->nome, nome);
  item->ind   = indice;
  item->prox = NULL; // importante!
  return item;
  }

// Inserir ao final da fila
void inserirFila (tipoRegistroFila **primeiro, tipoRegistroFila **ultimo, tipoRegistroFila *item) {
  if (*primeiro == NULL) { // fila vazia (apontado eh vazio)
    *primeiro = item; // para alterar quem chama
    *ultimo = item;
    }
  else {
    (*ultimo)->prox = item;
    *ultimo = item; // para alterar quem chama    
    }
  }

// Remover o ultimo da fila (apos usar o dado poderia-se devolve-lo `a fila de memoria com "free(item);")
// Tem que passar endereco do apontador para apontador de registros para poder altera-lo
tipoRegistroFila *removerFila (tipoRegistroFila **primeiro, tipoRegistroFila **ultimo) {
  tipoRegistroFila *item1 = NULL;
  if (*primeiro == NULL) { // fila vazia
    return NULL;
    }
  item1 = *primeiro;
  *primeiro = (*primeiro)->prox;
  if (*primeiro==NULL) *ultimo = NULL;
  return item1; // devolva o (anterior) ultimo
  }

