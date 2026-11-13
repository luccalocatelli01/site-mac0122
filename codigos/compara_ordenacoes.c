/* compara_ordenacoes.c — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. Material didático de MAC0122, IME-USP.
 * https://www.ime.usp.br/~leo/mac/mac122/ordena_compara_metodos.html */

// Prof. Leo^nidas - http://www.matematica.br http://line.ime.usp.br
// MAC122
// 2017/08/23
//
// Compara os 6 metodos de ordenacao abaixo, listando tempos de execucao:
//  *  0 : O(n^2)     : Metodo da Bolha
//  *  1 : O(n^2)     : Metodo da Selecao Direta
//  *  2 : O(n^2)     : Metodo da Insercao Direta
//  *  3 : O(n log n) : Metodo Rapido ("Quick Sort")
//  *  4 : O(n log n) : Metodo da Fusao ("Merge Sort")
//  *  5 : O(n log n) : Metodo do Monte ("Heap Sort")

#include <stdio.h>
#include <time.h> // clock_t, clock()

#include <stdlib.h> // rand()

// As 6 funcoes abaixo ficavam nos arquivos ordena_*.h do professor;
// foram trazidas para ca para o programa compilar sozinho.

#define MAX       25000 // maximo de elementos (TAMINI + NTESTES * PASSO)

void XbibliotecaLOBx__ordenaBolha (int V[], int n) {
  int i, j, aux;
  for (i = n-1; i > 0; i--)
    for (j = 0; j < i; j++)
      if (V[j] > V[j+1]) { aux = V[j]; V[j] = V[j+1]; V[j+1] = aux; }
  }

void XbibliotecaLOBx__ordenaViaSelecaoDireta (int V[], int n) {
  int i, j, iMin, aux;
  for (i = 0; i < n-1; i++) {
    iMin = i;
    for (j = i+1; j < n; j++)
      if (V[j] < V[iMin]) iMin = j;
    aux = V[i]; V[i] = V[iMin]; V[iMin] = aux;
    }
  }

void XbibliotecaLOBx__ordenaViaInsercaoDireta (int V[], int n) {
  int i, j, x;
  for (i = 1; i < n; i++) {
    x = V[i];
    for (j = i-1; j >= 0 && V[j] > x; j--)
      V[j+1] = V[j];
    V[j+1] = x;
    }
  }

// Prof. Leo^nidas - http://www.matematica.br http://line.ime.usp.br
// MAC0122 - 2017/08/23

// Biblioteca para: ordenar vetor de inteiros via metodo da Ordenacao Rapida. Complexidade: em media O(n log n)
// Exemplo de metodo no paradgma "DIVISAO e CONQUISTA"
// Invocar: #include "ordena_insercao.h"
//          ...
//          XbibliotecaLOBx__ordenaRapido(int V[], int esq, int dir)

// Programa recursivo para ordenar uma lista de inteiros usando a ideia separar menores e maiores que x
// depois ordenar cada trecho (se cada trecho for proximo de metade, resulta O(n log n)).

// Ordena Rapido (Quick Sort)
void XbibliotecaLOBx__ordenaRapido (int V[], int esq, int dir) {
  int i,j,x,w;

  // Particiona: separa menores que x para esquerda e maiores para direita
  i = esq;
  j = dir;
  x = V[esq]; // x <- qualquer valor entre V[esq] e V[dir]
  do { // Invariante: max{V[esq],...,V[i-1]  } <= x <= min{V[j+1],...,V[dir]  }
    while ( V[i] < x ) i++;
    while ( x < V[j] ) j--;
    if (i<=j) {
      if (i<j) {
        w    = V[i];
        V[i] = V[j];
        V[j] = w;
        }
      i++;
      j--;
      }
  } while (i<j); // max{V[esq],...,V[j]  } <= x <= min{V[i],...,V[dir]  }

  if (esq<j)
    XbibliotecaLOBx__ordenaRapido(V, esq, j); // ordena parte esquerda
  if (i<dir)
    XbibliotecaLOBx__ordenaRapido(V, i, dir); // ordena parte direita
  }

// Prof. Leo^nidas - http://www.matematica.br http://line.ime.usp.br
// MAC0122 - 2017/08/23

// Biblioteca para: ordenar vetor de inteiros via metodo da Fusao. Complexidade: O(n log n)
// Exemplo de metodo no paradgma "DIVISAO e CONQUISTA"
// Invocar: #include "ordena_fusao.h"
//          ...
//          XbibliotecaLOBx__ordenaMetadesFusao(int V[], int esq, int dir)

// Ordena por Fusao (Merge Sort)
// Programa recursivo para ordenar uma lista de inteiros usando a ideia ordenar 2 metades e depois fundi-las.


// Se V[esq]<=V[esq+1]<=...<=V[med] e V[med+1]<=V[med+2]<=...<=V[dir]
// Entao funde em ordem unica V[esq] <= V[esq+1] <= ... <= V[dir-1] <= V[dir]
void XbibliotecaLOBx__Fusao (int V[], int esq, int med, int dir) {
  int Aux[MAX], i, j, k, e1, d1, e2, d2; // dir=e2
  e1 = esq;   d1 = med;
  e2 = med+1; d2 = dir;
  k = i = e1;
  j = e2;
  while (i<=d1 && j<=d2) { // compara os "topos", retire o menor dos dois colocando em nova pilha
    if (V[i]<V[j]) // "topo" da pilha 1 e' o menor
      Aux[k++] = V[i++];
    else
    if (V[i]>V[j]) // "topo" da pilha 2 e' o menor
      Aux[k++] = V[j++];
    else { // havendo empate pegue os dois "topos"
      Aux[k++] = V[i++];
      Aux[k++] = V[j++];
      }
    }
  while (i<=d1) // copia restante de V[e1..d1]
    Aux[k++] = V[i++];
  while (j<=d2)  // copia restante de V[e2..d2]
    Aux[k++] = V[j++];
  for (i=e1; i<=d2; i++) // reconstroi V[e1..d2] ordenado
    V[i]=Aux[i];
  }

// Ordena V[esq .. dir] usando tecnica de DIVISAO E CONQUISTA, divida em 2 metades
// ordene cada uma e depois funda para obter ordem das 2 partes
void XbibliotecaLOBx__ordenaMetadesFusao (int V[], int esq, int dir) {
  int med;
  med = (esq+dir)/2;
  if (esq<med)
    XbibliotecaLOBx__ordenaMetadesFusao(V, esq, med);   // ordena V[esq .. m]
  if (med<dir)
    XbibliotecaLOBx__ordenaMetadesFusao(V, med+1, dir); // ordena V[m+1 .. dir]
  XbibliotecaLOBx__Fusao(V, esq, med, dir); // funde em ordem unica V[esq .. m] com V[m+1 .. dir]
  }

// Prof. Leo^nidas - http://www.matematica.br http://line.ime.usp.br
// MAC0122 - 2017/08/23

// Biblioteca para: ordenar vetor de inteiros via metodo da Propriedade de Monte. Complexidade: O(n log n)
// Exemplo de metodo no paradgma "DIVISAO e CONQUISTA"
// Invocar: #include "ordena_monte.h"
//          ...
//          XbibliotecaLOBx__ordenaMonte(int V[], int n);

// Ordena vetor de inteiros via metodo da Ordenacao por Propriedade de Monte. Complexidade: O(n log)
// Propriedade de Monte ("Heap Sort"):
//   para cada no de uma arvore, a informacao nele e' maior ou igual a de seus filhos
//   info(no) >= max{ info(no.esq), info(no.dir) }
// Usa um vetor para a arvore: para um no na posicao i do vetor, seus filhos estao nas posicoes V[2*i+1] e V[2*i+2]
// Observacao importante: se uma arvore e' o Monte, entao o maior elemento esta na primeira posicao, ou seja,
//   V[0] >= V[i], para todo i
// Programa recursivo para ordenar uma lista de inteiros usando a ideia manter propriedade de Monte e separa o maior.

// Macro para trocar par de valores
#define XbibliotecaLOBx__troquePar(V, IA, IB) {int aux = V[IA]; V[IA] = V[IB]; V[IB] = aux;}

// Supondo que V[] tem a propriedade de Monte exceto talvez em V[k]
// Entao "desca" o V[k] trocando-o com o maior filho ate' que fique maior que os 2 filhos
// Neste momento a propriedade de Monte estara restaurada
void XbibliotecaLOBx__desceElementoMonte (int V[], int k, int N) {
  int j;
  while (2*k + 1 < N) { // tem algum filho?  (V[k] -> { V[2*k, V[2*k+2] }
    j = 2*k + 1; // primeiro filho de "k"
    if (j < N-1 && V[j] < V[j+1]) // se tem 2 filhos e maior em j+1, aponte para j+1
      j++;
    if (V[k] >= V[j]) {
       break;
       }
    XbibliotecaLOBx__troquePar(V, k, j); // o "define" acima colocara aquele codigo aqui
    k = j; // recome com o "maior filho"
    }
  }

void XbibliotecaLOBx__ordenaMonte (int V[], int tam) {
  int k, N = tam;
  // Cria propriedade inicial de Monte
  for (k = N/2-1; k >= 0; k--) // comece pelo primeiro no que tem filho
    XbibliotecaLOBx__desceElementoMonte(V, k, N); // desca-o de modo sua sub-arvore ser Monte
  while (N > 0) {
    // Elemento no topo e' maior => passe para ultima posicao
    XbibliotecaLOBx__troquePar(V, 0, N-1);
    // Estragou propriedade de monte na posicao 0, desca para recuperar propriedade
    XbibliotecaLOBx__desceElementoMonte(V, 0, --N);
    }
  }

#define TAMINI    10000 // testar com TAMINI elementos inicialmente
#define PASSO      1000 // crescimento no numero de elementos
#define NTESTES      15 // numero de testes, de 1000 em 1000
#define INTERVALO  1000

#define NMETODOS      6 // numero de metodos a serem testados

// Gera 'n' valores pseudo-aleatorios para o vetor V[]
void GeraVetor (int V[], int n) {
  int i;
  for (i=0; i<n; i++)
    V[i] = (int)(rand()%INTERVALO); // rand() E {0,...,(2^31)-1  }, srand
  }

// Copia dados de vetor original
void CopiaVetor (int VOrig[], int VNovo[], int n) {
  int i;
  for (i=0; i<n; i++) VNovo[i] = VOrig[i];
  }

// ImprimeVetor dados do vetor
void ImprimeVetor (int V[], int n) {
  int i;
  for (i=0; i<n; i++) printf("%4d", V[i]);
  printf("\n");
  }

// Compara metodos de ordenacao
int main (void) {
  int V[MAX], V0[MAX];
  int i, tam;
  int TM[NMETODOS], md;
  clock_t tempo_inicialB, tempo_finalB;
  clock_t tempo_inicialSD, tempo_finalSD;
  clock_t tempo_inicialID, tempo_finalID;
  clock_t tempo_inicialR, tempo_finalR;
  clock_t tempo_inicialF, tempo_finalF;
  clock_t tempo_inicialM, tempo_finalM;

  for (i=0; i<NMETODOS; i++) TM[i] = 0;

  printf("      n |     Bolha | Sel. Dir. | Ins. Dir. | Met. Rap. | Met. Fus. | Met. Mon. |\n");

  tam = TAMINI;
  for (i=0; i<NTESTES; i++) {
    GeraVetor(V0, tam);
    //d ImprimeVetor(V0, tam); //d

    // 0 : Metodo da Bolha
    CopiaVetor(V0, V, tam);
    tempo_inicialB = clock(); // "dispara o cronometro"...
    XbibliotecaLOBx__ordenaBolha(V, tam);
    tempo_finalB = clock();
    TM[0] += tempo_finalB - tempo_inicialB;

    // 1 : Metodo da Selecao Direta
    CopiaVetor(V0, V, tam);
    tempo_inicialSD = clock(); // "dispara o cronometro"...
    XbibliotecaLOBx__ordenaViaSelecaoDireta(V, tam);
    tempo_finalSD = clock();
    TM[1] += tempo_finalSD - tempo_inicialSD;

    // 2 : Metodo da Insercao Direta
    CopiaVetor(V0, V, tam);
    tempo_inicialID = clock(); // "dispara o cronometro"...
    XbibliotecaLOBx__ordenaViaInsercaoDireta(V, tam);
    tempo_finalID = clock();
    TM[2] += tempo_finalID - tempo_inicialID;

    // 3 : Metodo Rapido ("Quick Sort")
    CopiaVetor(V0, V, tam);
    tempo_inicialR = clock(); // "dispara o cronometro"...
    XbibliotecaLOBx__ordenaRapido(V, 0, tam-1);
    tempo_finalR = clock();
    TM[3] += tempo_finalR - tempo_inicialR;

    // 4 : Metodo da Fusao ("Merge Sort")
    CopiaVetor(V0, V, tam);
    tempo_inicialF = clock(); // "dispara o cronometro"...
    XbibliotecaLOBx__ordenaMetadesFusao(V, 0, tam-1);
    tempo_finalF = clock();
    TM[4] += tempo_finalF - tempo_inicialF;

    // 5 : Metodo do Monte ("Heap Sort")
    CopiaVetor(V0, V, tam);
    tempo_inicialM = clock(); // "dispara o cronometro"...
    XbibliotecaLOBx__ordenaMonte(V, tam);
    tempo_finalM = clock();
    TM[5] += tempo_finalM - tempo_inicialM;
    printf("  %5d |  %f |  %f |  %f |  %f |  %f |  %f |\n", tam,
           (double)(tempo_finalB  - tempo_inicialB)  / CLOCKS_PER_SEC,
           (double)(tempo_finalSD - tempo_inicialSD) / CLOCKS_PER_SEC,
           (double)(tempo_finalID - tempo_inicialID) / CLOCKS_PER_SEC,
           (double)(tempo_finalR  - tempo_inicialR)  / CLOCKS_PER_SEC,
           (double)(tempo_finalF  - tempo_inicialF)  / CLOCKS_PER_SEC,
           (double)(tempo_finalM  - tempo_inicialM)  / CLOCKS_PER_SEC);
    tam += PASSO;
    }

  printf("    med |  %f |  %f |  %f |  %f |  %f |  %f |\n",
         (double)(TM[0]) / (NTESTES * CLOCKS_PER_SEC), (double)(TM[1]) / (NTESTES * CLOCKS_PER_SEC),
         (double)(TM[2]) / (NTESTES * CLOCKS_PER_SEC), (double)(TM[3]) / (NTESTES * CLOCKS_PER_SEC),
         (double)(TM[4]) / (NTESTES * CLOCKS_PER_SEC), (double)(TM[5]) / (NTESTES * CLOCKS_PER_SEC));

  printf("\n");

  //d printf("\n\n\nDados iniciais:\n"); ImprimeVetor(V0, tam);
  //d printf("\nOrdenado:\n"); ImprimeVetor(V, tam);

  return 0;
  }
