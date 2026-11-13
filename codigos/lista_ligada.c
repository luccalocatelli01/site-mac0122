/* lista_ligada.c — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. Material didático de MAC0122, IME-USP.
 * https://www.ime.usp.br/~leo/mac/mac122/lista_ligada/introducao_lista_ligada.html */

// Prof. Leo^nidas - http://www.matematica.br http://line.ime.usp.br
// MAC0122 - 2017/09

// Introducao `as listas ligadas em C
// Principio: usando alocacao dinamica de memoria, podemos usar registros e apontadores para definir a ordem dos dados.
// Exemplo de lista com insercao ao final
// Se 'prox' tiver com o valor nulo (NULL), entao a lista finalizou.

// Para ajudar na depuracao, compilar com diretivas para verificar acesso `a posicoes invalidas (via apontadores ou vetores)
// $ gcc -fsanitize=address -g -o introducao_lista_ligada introducao_lista_ligada.c

#include <stdio.h>
#include <string.h> // para 'strcpy(...)'
#include <stdlib.h> // para o 'malloc(...)' e 'free(...)'

#define TAM 10 // limite para numero de caracteres em campo do registro
#define M 5    // limite para vetor de registros

typedef struct reg {  // define estrutura 'dado'
  int id;
  char nome[TAM];   // precisa deste espaco
  struct reg *prox; // aponta para uma estrutura 'dado'
  } tipoRegistro;

// Cria um registro devolvendo um apontador para ele
tipoRegistro *criaRegistro (char *nome, int id) {
  tipoRegistro *item = malloc(sizeof(tipoRegistro));
  //tipoRegistro *item = malloc(TAM * sizeof(char) + sizeof(int) + sizeof(tipoRegistro *));
  strcpy(item->nome, nome);
  item->id = id;
  item->prox = NULL;
  return item;
  }

// Construir uma lista ligada de itens (registros), inserindo sempre na ultima posicao
// Exercicios 1. Implementar uma funcao que insere na ultima posicao (ja' no codigo, mas dentro da "main")
// Exercicios 2. Implementar uma funcao que remova o elemento cujo campo 'nome' tenha determinado valor
// Exercicios 3. Implementar uma funcao que remova o elemento cujo campo 'id' tenha determinado valor
// ATENCAO: nos exercicios 2 e 3, cuidado com situacoes extremas (lista vazia, item a ser removido ser o primeiro ou ser o ultimo)
int main (void) {
  int i;
  char nomes[][TAM] = { "aluno 1", "aluno 2", "aluno 3", "aluno 4", "aluno 5" }; // vetor de nomes estatico (para NAO precisar digitar...)
  tipoRegistro *primeiro, *apont, *novo;

  primeiro = criaRegistro(nomes[0], 0); // crie o primeiro elemento
  apont = primeiro;
  for (i=1; i<5; i++) {
    novo = criaRegistro(nomes[i], i); // crie novo elemento
    apont->prox = novo;                 // faca com que o apontador para proximo do ultimo aponte para este novo registro
    apont = novo;
    }
  apont = primeiro;
  while (apont!=NULL) {
    printf(" - %d : %s\n", apont->id, apont->nome);
    // Depois de usar, se NAO mais precisar do registro pode devolve-lo ao "banco de memoria" usando
    // free(apont);
    apont = apont->prox; // pegue o proximo registro
    }

  return 0;
  }
