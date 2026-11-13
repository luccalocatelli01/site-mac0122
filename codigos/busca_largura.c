/* busca_largura.c — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. Material didático de MAC0122, IME-USP.
 * https://www.ime.usp.br/~leo/mac/mac122/grafos/busca_em_largura.html */

// Prof. Leo^nidas - http://www.matematica.br http://line.ime.usp.br
// MAC0122 - 2017/10/30

// Busca em largura em grafos: utilizando fila.
// Exemplo de grafo construido modo "estatico" (vide 'criaGrafo1()' e 'criaGrafo2()'.

// Para evitar construcao ciclica, criar um vetor de nos e cada um com
// uma lista de vizinhos apontando para o inteiro do vetor.

// $ gcc -fsanitize=address -g -o busca_em_largura busca_em_largura.c

#include <stdio.h>
#include "fila_lista.h" // estrutura para fila e funcoes para criar, inserir e remover

#define MAXNOS 10 // numero maximo de nos do grafo

typedef struct noV { // Lista de vizinhos
  int indice;        // supoe que os nos do grafo estao em um vetor
  struct noV *prox;
  } Lista;

typedef struct no { // Cada no do grafo
  int info;
  Lista *vizinhos;
  } No;

// Globais
No    *vetNosGrafo[MAXNOS]; // vetor de nos do grafo
Lista *vetProxViz[MAXNOS];  // (truque) vetor de nos do grafo com proximo vizinho do no' a ser visitado
int visitado[MAXNOS];       // auxiliar para marcar os nos visitados
int inserido[MAXNOS];       // auxiliar para marcar os nos ja inseridos alguma vez na fila
int nVG;                    // numero de nos do grafo
tipoRegistroFila *primeiro, *ultimo; // "../lista_ligada/fila_lista_ligada_struct.h" declara 'tipoRegistroFila'

// Lista os vizinhos do no' de indice "i": imprime "indice" e "rotulo" de cada vizinho
void listaVizinhos (int i) {
  No *no = vetNosGrafo[i];
  Lista *viz;
  int ind;
  if (no==NULL) { printf("Erro: nao existe o no %d\n", i); return; }
  if ((viz = no->vizinhos)==NULL) { printf("<vazio>\n"); return; }
  while (viz != NULL) {
    ind = viz->indice;
    printf("<%d: ", ind);
    printf("%d > ", vetNosGrafo[ind]->info);
    viz = viz->prox;
    }
  printf("\n");
  }


// Atencao, precisa de alocacao dinamica e antes de voltar para quem chamou,
// e' necessario que alguma variavel de quem chamou preserve os apontadores.
void criaGrafo1 () { // Grafo 1                       (1)---(2)
  nVG = 4;                   // num. nos do grafo      |  \  |
  No *no1, *no2, *no3, *no4; //                       (3)---(4)
  Lista *lista1, *lista2, *lista3,
        *lista4, *listaAux; // uma lista de adjacentes para cada no
  no1 = malloc(sizeof(No)); no2 = malloc(sizeof(No));
  no3 = malloc(sizeof(No)); no4 = malloc(sizeof(No));
  no1->info = 1; no2->info = 2; no3->info = 3; no4->info = 4;
  vetNosGrafo[0] = no1;          // No 1 : tem como vizinhos 2, 3, 4 - neste ponto preserva-se os end alocados
  listaAux = malloc(sizeof(Lista)); listaAux->indice = 1; // no 2
  lista1   = listaAux;
  listaAux = malloc(sizeof(Lista)); listaAux->indice = 2; // no 3
  lista1->prox = listaAux;
  listaAux = malloc(sizeof(Lista)); listaAux->indice = 3; // no 4
  listaAux->prox = NULL;
  lista1->prox->prox = listaAux; vetProxViz[0] = lista1;
  no1->vizinhos = lista1;
  vetNosGrafo[1] = no2;          // No 2 : tem como vizinhos 1, 4
  listaAux = malloc(sizeof(Lista)); listaAux->indice = 0; // no 1
  lista2   = listaAux;
  listaAux = malloc(sizeof(Lista)); listaAux->indice = 3; // no 4
  listaAux->prox = NULL;
  lista2->prox = listaAux; vetProxViz[1] = lista2;
  no2->vizinhos = lista2;
  vetNosGrafo[2] = no3;          // No 3 : tem como vizinhos 1, 4
  listaAux = malloc(sizeof(Lista)); listaAux->indice = 0; // no 1
  lista3   = listaAux;
  listaAux = malloc(sizeof(Lista)); listaAux->indice = 3; // no 4
  listaAux->prox = NULL;
  lista3->prox = listaAux; vetProxViz[2] = lista3;
  no3->vizinhos = lista3;
  vetNosGrafo[3] = no4;          // No 4 : tem como vizinhos 1, 2, 3
  listaAux = malloc(sizeof(Lista)); listaAux->indice = 0; // no 1
  lista4   = listaAux;
  listaAux = malloc(sizeof(Lista)); listaAux->indice = 1; // no 2
  lista4->prox = listaAux;
  listaAux = malloc(sizeof(Lista)); listaAux->indice = 2; // no 3
  listaAux->prox = NULL;
  lista4->prox->prox = listaAux; vetProxViz[3] = lista4;
  no4->vizinhos = lista4;
  }

void criaGrafo2 () { // Grafo 2                       (1)---(2)
  nVG = 4;                   // num. nos do grafo            |  \     (nao terminar em '\')
  No *no1, *no2, *no3, *no4; //                             (3)---(4)
  Lista *lista1, *lista2, *lista3,
        *lista4, *listaAux; // uma lista de adjacentes para cada no
  no1 = malloc(sizeof(No)); no2 = malloc(sizeof(No));
  no3 = malloc(sizeof(No)); no4 = malloc(sizeof(No));
  no1->info = 1; no2->info = 2; no3->info = 3; no4->info = 4;
  vetNosGrafo[0] = no1;          // No 1 : tem como vizinhos 2
  listaAux = malloc(sizeof(Lista)); listaAux->indice = 1; // no 2
  listaAux->prox = NULL;
  lista1   = listaAux; vetProxViz[0] = lista1;
  no1->vizinhos = lista1;
  vetNosGrafo[1] = no2;          // No 2 : tem como vizinhos 1, 3, 4
  listaAux = malloc(sizeof(Lista)); listaAux->indice = 0; // no 1
  lista2   = listaAux;
  listaAux = malloc(sizeof(Lista)); listaAux->indice = 2; // no 3
  lista2->prox = listaAux;
  listaAux = malloc(sizeof(Lista)); listaAux->indice = 3; // no 4
  listaAux->prox = NULL;
  lista2->prox->prox = listaAux; vetProxViz[1] = lista2;
  no2->vizinhos = lista2;
  vetNosGrafo[2] = no3;          // No 3 : tem como vizinhos 2, 4
  listaAux = malloc(sizeof(Lista)); listaAux->indice = 1; // no 2
  lista3   = listaAux;
  listaAux = malloc(sizeof(Lista)); listaAux->indice = 3; // no 4
  listaAux->prox = NULL;
  lista3->prox = listaAux; vetProxViz[2] = lista3;
  no3->vizinhos = lista3;
  vetNosGrafo[3] = no4;          // No 4 : tem como vizinhos 2, 3
  listaAux = malloc(sizeof(Lista)); listaAux->indice = 1; // no 2
  lista4   = listaAux;
  listaAux = malloc(sizeof(Lista)); listaAux->indice = 2; // no 3
  listaAux->prox = NULL;
  lista4->prox = listaAux; vetProxViz[3] = lista4;
  no4->vizinhos = lista4;
  }

void iniciaVisitados (int n) { // inicia cada no' como NAO visitado e NAO inserido na fila
  int i;
  for (i=0; i<n; i++) {
    visitado[i] = 0; // marque como NAO visitado
    inserido[i] = 0; // marque como NAO inserido
    }
  }

void visite (int i) { // Visite o no'
  printf("<%d: ", i);
  if (vetNosGrafo[i]==NULL) { printf("x > - erro! 'visite(%d)'!\n", i); return ; } //S seguranca
  printf("%d > ", vetNosGrafo[i]->info);
  visitado[i] = 1; // marque como visitado
  }

int temVizinho (No *item) { // Verifica se o no' tem algum vizinho
  if (item==NULL) { printf("Erro! 'temVizinho(NULL)'!\n"); return 0; } //S seguranca
  return item->vizinhos!=NULL; // se nao NULL => tem filhos
  }

// Truque para pegar iterativa (a cada chamada) os vizinhos de um no'
int proximoVizinho (int indice) { // devolva proximo vizinho de vetNosGrafo[indice]
  Lista *viz = vetProxViz[indice]; // pegue atual vizinho do no de indice dado
  if (viz==NULL) { //D printf("<sem vizinhos>");
    return -1; // este no NAO tem vizinhos!
    }
  vetProxViz[indice] = viz->prox;  // avance para o seguinte
  return viz->indice; // devolva indice do ultimo
  }

// Algoritmo de busca em largura.
// Utiliza uma fila para inserir vizinhos de cada no' visitado.
// Usa vetor de "bits" (visitado[], inserido[]) para marcar visitados e inseridos.
void buscaEmLargura (int vg) { // recebe primeiro elemento da fila
  No *aux, *no = vetNosGrafo[0];
  tipoRegistroFila *item;
  int ind, aux_ind, conta = 0;
  item = criarRegFila(0, "no"); // define item->ind = conta
  iniciaVisitados(vg);
  inserirFila(&primeiro, &ultimo, item); inserido[0] = 1; // marque como inserido
  while (filaNaoVazia(primeiro)) { // ../lista_ligada/fila_lista_ligada_struct.h: filaNaoVazia(...)
    //D printf("Indices na fila: "); imprimirFilaToda(primeiro);
    item = removerFila(&primeiro, &ultimo);
    ind = item->ind;
    //D printf("\n-------------\nbuscaEmLargura: conta=%d, item->ind=%d\n", conta, ind);
    if (visitado[ind]==0) { // verifica se item ainda nao foi visitado
      visite(ind); printf(" : ");
      //D printf(" vizinhos de item->ind=%d (vetProxViz[%d]->indice=%d): ", ind, ind, vetProxViz[ind]->indice);
      while ((aux_ind = proximoVizinho(ind))>=0) {
        if (inserido[aux_ind]!=1) { // insere apenas se NAO foi inserido antes
          item = criarRegFila(aux_ind, "no"); conta++;
          inserirFila(&primeiro, &ultimo, item); inserido[aux_ind] = 1; // marque como inserido
          //D printf("(v=0, item->ind=%d) ", item->ind);
          printf(" <%d, %d> ", item->ind, vetNosGrafo[aux_ind]->info);
          }
        else printf("[%d, %d] ", aux_ind, vetNosGrafo[aux_ind]->info); // ja inserido
        }
      }
    //D else printf(" %d ja foi visitado *****\n", ind);
    printf("\n");
    } // while (filaNaoVazia(primeiro))
  } // void buscaEmLargura (int vg)


int main (void) {
  int i;
  printf("Simulando operacoes: nos\n");
  criaGrafo2(); // nVG = 4
  for (i=0; i<nVG; i++) { // inserir os 5 item
    printf("%d: ", vetNosGrafo[i]->info);
    listaVizinhos(i);
    }
  buscaEmLargura(nVG);
  printf("\n");

  return 0;
  }
