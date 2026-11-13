/* fila_lista.c — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. Material didático de MAC0122, IME-USP.
 * https://www.ime.usp.br/~leo/mac/mac122/lista_ligada/introducao_fila_lista_ligada_struct.html */

// Prof. Leo^nidas - http://www.matematica.br http://line.ime.usp.br
// MAC0122 - 2017/10/02

// Introducao ao conceito de FILA (primeiro a entrar, primeiro a sair) ou "queue" (FIFO - "first in, first out")
// Usa conceito de apontador para apontador ("**apont")
// Exemplo usando lista ligada (com 'typedef' e 'struct'), inserir e remover da fila

// Exercicio: Fazer uma implementacao equivalente utilizando vetor no lugar de lista ligada.

// gcc -fsanitize=address -g -o introducao_fila_lista_ligada_struct introducao_fila_lista_ligada_struct.c

#include <stdio.h>
#include <string.h> // para 'strcpy(...)'
#include <stdlib.h> // para 'malloc(...)'

#define TAM 10 // limite para numero de caracteres em campo do registro
#define M 5    // limite para vetor de registros

typedef struct reg {  // define estrutura 'dado'
  int id;
  char nome[TAM];
  struct reg *prox; // aponta para uma estrutura 'dado'
  } tipoRegistro;

// Para depuracao: imprimir registro
void imprimir (tipoRegistro *item) {
  if (item == NULL) { // fila vazia
    printf("<vazio>");
    return;
    }
  printf("(%d, %s)", item->id, item->nome);
  }

// Testar: imprimir fila toda (comecando do primeiro)
void imprimirFilaToda (tipoRegistro *primeiro) {
  tipoRegistro *item = primeiro;
  int i;
  printf("Situacao da fila: ");
  while (item!=NULL) {
    imprimir(item);
    printf(" ");
    item = item->prox; //printf(" - %s\n", nomes[i]);
    }
  printf("\n");
  }

// Criar item de registro
tipoRegistro *criar (int id, char *nome) {
  tipoRegistro *item = malloc(sizeof(tipoRegistro));
  // Nao basta apontar para "string" apontada por "nome", precisa copiar todos seus caracteres na posicao nova apontada por "item"
  strcpy(item->nome, nome);
  item->id   = id;
  item->prox = NULL; // importante!
  return item;
  }

// Inserir ao final da fila
void inserir (tipoRegistro *item, tipoRegistro **primeiro, tipoRegistro **ultimo) {
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
tipoRegistro *remover (tipoRegistro **primeiro, tipoRegistro **ultimo) {
  tipoRegistro *item1, *item2 = NULL;
  if (*primeiro == NULL) { // fila vazia
    return NULL;
    }
  item1 = *primeiro;
  while (item1->prox != NULL) {
    item2 = item1;
    item1 = item1->prox; // avance
    }
  if (item2==NULL) { // tinha apenas 1 elemento
    *ultimo = item1; // anterior ao ultimo
    *primeiro = item1;
    }
  else {
    item2->prox = NULL;
    *ultimo = item2;
    }
  return item1; // devolva o (anterior) ultimo
  }

int main (void) {
  int i;
  char nomes[][TAM] = { "aluno 1", "aluno 2", "aluno 3", "aluno 4", "aluno 5" };
  tipoRegistro *item0, *item, *primeiro = NULL, *ultimo = NULL;

  printf("Simulando operacoes:\n");
  for (i=0; i<5; i++) { // inserir os 5 item
    item = criar(i, nomes[i]); // imprimirFilaToda(item);
    inserir(item, &primeiro, &ultimo); // tem que passar o local em que o apontador para primeiro esta (para altera-lo)
    imprimirFilaToda(primeiro);
    }

  item0 = remover(&primeiro, &ultimo); // remover item "(4, aluno 5)"
  printf("Removido item: "); imprimir(item0); printf("\n");

  item = remover(&primeiro, &ultimo); // remover item "(3, aluno 4)"
  printf("Removido item: "); imprimir(item); printf("\n");

  inserir(item0, &primeiro, &ultimo); // inserir item "(4, aluno 5)"
  printf("Inserido item: "); imprimir(item0); printf("\n");

  printf("Situacao final da fila: ");
  imprimirFilaToda(primeiro);
  return 0;
  }
