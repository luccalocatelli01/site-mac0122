/* pilha_lista.c — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. Material didático de MAC0122, IME-USP.
 * https://www.ime.usp.br/~leo/mac/mac122/lista_ligada/introducao_pilha_lista_ligada_struct.html */

// Prof. Leo^nidas - http://www.matematica.br http://line.ime.usp.br
// MAC0122 - 2017/10/02

// Introducao ao conceito de PILHA (primeiro a entrar, primeiro a sair) ou "stack" (LIFO - "last in, first out")
// Usa conceito de apontador para apontador ("**apont")
// Exemplo usando lista ligada (com 'typedef' e 'struct'), inserir e remover da pilha

// Exercicio: Fazer uma implementacao equivalente utilizando vetor no lugar de lista ligada.

// gcc -fsanitize=address -g -o introducao_pilha_lista_ligada_struct introducao_pilha_lista_ligada_struct.c

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
  if (item == NULL) { // pilha vazia
    printf("<vazio>");
    return;
    }
  printf("(%d, %s)", item->id, item->nome);
  }

// Testar: imprimir pilha toda
void imprimirPilhaToda (tipoRegistro *topo) {
  tipoRegistro *item = topo;
  int i;
  printf("Situacao da pilha: ");
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

// Inserir no topo da pilha: versao 1 devolvendo o topo
tipoRegistro *inserir (tipoRegistro *item, tipoRegistro *topo) {
  if (topo != NULL) { // pilha vazia
    item->prox = topo;
    return item;
    }
  return item;
  }

// Inserir no topo da pilha: versao 2 atualizando o topo
void inserirV2 (tipoRegistro *item, tipoRegistro **topo) {
  if (*topo != NULL) { // pilha vazia (apontado eh vazio)
    item->prox = *topo;
    }
  *topo = item; // para alterar quem chama
  }

// Remover do topo da pilha (apos usar o dado poderia-se devolve-lo `a pilha de memoria com "free(item);")
// Tem que passar endereco do apontador para apontador de registros para poder altera-lo
tipoRegistro *remover (tipoRegistro **topo) {
  tipoRegistro *item;
  if (*topo == NULL) { // pilha vazia
    return NULL;
    }
  item = *topo;
  *topo = (*topo)->prox;
  return item;
  }

int main (void) {
  int i;
  char nomes[][TAM] = { "aluno 1", "aluno 2", "aluno 3", "aluno 4", "aluno 5" };
  tipoRegistro *item0, *item, *topo = NULL;

  printf("Simulando operacoes:\n");
  for (i=0; i<5; i++) { // inserir os 5 item
    item = criar(i, nomes[i]); // imprimirPilhaToda(item);
    if (i%2 == 0) // usar versao 1
      topo = inserir(item, topo);
    else // usar versao 2
      inserirV2(item, &topo); // tem que passar o local em que o apontador para topo esta (para altera-lo)
    imprimirPilhaToda(topo);
    }

  item0 = remover(&topo); // remover item "(4, aluno 5)"
  printf("Removido item: "); imprimir(item0); printf("\n");

  item = remover(&topo); // remover item "(3, aluno 4)"
  printf("Removido item: "); imprimir(item); printf("\n");

  inserirV2(item0, &topo); // inserir item "(4, aluno 5)"
  printf("Inserido item: "); imprimir(item0); printf("\n");

  printf("Situacao final da pilha: ");
  imprimirPilhaToda(topo);
  return 0;
  }
