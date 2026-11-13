/* busca_profundidade.c — EP MAC0122
 * Implementação do pseudocódigo do prof.: BRANDÃO, L. O. MAC0122 (2026), e-Disciplinas USP,
 * pasta "Códigos semana 09: busca em profundidade/largura em grafos", arquivo busca_em_profundidade.txt.
 * O Moodle só tem o pseudocódigo; o programa abaixo foi escrito pelo grupo, com a pilha
 * em vetor (topo começa em -1) e o grafo em matriz de adjacência.
 * Base: CORMEN, T. H. et al. Algoritmos: teoria e prática. 3. ed. Elsevier, 2012 (DFS). */

#include <stdio.h>

#define MAXNOS   10
#define MAXPILHA (MAXNOS * MAXNOS) // um vértice pode ser empilhado uma vez por aresta

int n = 8;                 // número de vértices do exemplo
int adj[MAXNOS][MAXNOS];   // adj[i][j] = 1 se existe aresta i-j
int visitado[MAXNOS];

int pilha[MAXPILHA];
int topo = -1;

void insere (int v)        { pilha[++topo] = v; }
int  removePilha (void)    { return pilha[topo--]; }
int  pilhaNaoVazia (void)  { return topo >= 0; }

void insereAresta (int i, int j) {
  adj[i][j] = adj[j][i] = 1;  // grafo não dirigido
  }

// Mesmo laço do pseudocódigo: tira um vértice da pilha; se ainda não foi
// visitado, visita e empilha todos os seus vizinhos.
void buscaEmProfundidade (int no) {
  int filho;
  insere(no);
  while (pilhaNaoVazia()) {
    no = removePilha();
    if (!visitado[no]) {
      visitado[no] = 1;
      printf("visita %d\n", no);
      for (filho = n - 1; filho >= 0; filho--) // de trás para frente: o menor vizinho sai primeiro
        if (adj[no][filho] && !visitado[filho])
          insere(filho);
      }
    }
  }

int main (void) {
  int i;
  // Grafo de exemplo: 0-1, 0-2, 1-3, 1-4, 2-5, 4-6, 5-6; o 7 fica isolado
  insereAresta(0, 1); insereAresta(0, 2);
  insereAresta(1, 3); insereAresta(1, 4);
  insereAresta(2, 5); insereAresta(4, 6);
  insereAresta(5, 6);

  for (i = 0; i < n; i++) visitado[i] = 0;
  printf("Busca em profundidade a partir do vertice 0:\n");
  buscaEmProfundidade(0);

  printf("Nao alcancados:");
  for (i = 0; i < n; i++)
    if (!visitado[i]) printf(" %d", i);
  printf("\n");
  return 0;
  }
