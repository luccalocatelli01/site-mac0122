/* ordenacao_frequencia.c — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. Material didático de MAC0122, IME-USP.
 * https://www.ime.usp.br/~leo/mac/mac122/ordena_por_frequencia.html */

// Prof. Leo^nidas - http://www.matematica.br ; http://line.ime.usp.br
// MAC122
// 2017/09/07
//
// Baseado no metodo de ordenacao para caracteres do tipo "digito menos significativo" ("least significant digits first" - LSD)
// Exemplo de metodo no paradigma "GULOSO"
//
// Aplicacao ao caso de inteiros: ordena supondo que numeros estao em pequena faixa de valores ("universo")
//
// Usa a ideia de "vetor de bits" para representar conjunto: x presente <=> vet[x]==1.
// Aqui usaremos o indice deslocado de 1                   : x presente <=> vet[x+1]==1
//
// Complexidade do algoritmo de ordenacao : O(n + u), se u = #universo

// Algumas referencias:
// - "Chapter Ten. Radix Sorting" do livro do Sedgewick "Algorithms in C"/"C++ Programming"
// - "Ordenacao digital", material do prof. Paulo Feofiloff: https://www.ime.usp.br/~pf/algoritmos/aulas/radix.html

#include <stdio.h>  // para 'printf' e 'scanf'
#include <stdlib.h> // para "rand()" para gerar valores "pseudo-aleatorios" (agilizar "entrada de dados")

#define TAM        10 // tamanho para o vetor de dados (maximo de elementos no vetor de dados)
#define INTERVALO 100 // gerar elementos entre 0..INTERVALO-1 para compor o conjunto "universo"

// Prototipos para funcoes utilizadas (importante caso ocorra dependencia cruzada - funcao 'a()' depende de 'b()' e 'b()' depende de 'a()')
void gerarVetorDados(int [], int, int);
void imprimeVetor(int [], int);
void ordenaPorFrequencia(int *, int, int);

// Gerar 'n' valores pseudo-aleatorios para o vetor V[]
void gerarVetorDados (int V[], int n, int intervalo) {
  int i;
  for (i=0; i<n; i++)
    V[i] = (int)(rand() % intervalo); //1 rand() gera inteiro entre {0,...,(2^31)-1  }, srand() pode mudar "semente"
    //2 V[i] = n-i-1; //2 outro teste...
    //3 V[i] = i % 2; //3 outro teste...
  }

// Imprime dados do vetor
void imprimeVetor (int V[], int n) {
  int i;
  for (i=0; i<n; i++)
    printf("%4d", V[i]);
  printf("\n");
  }

// Ordena crescente v[0..n-1] supondo que os elementos do vetor pertencem ao universo 0..U-1
void ordenaPorFrequencia (int *vet, int n, int U) {
  int ind, ii, i;
  int *vetFreqAcum, *vetAux;
  vetFreqAcum = malloc((U+1) * sizeof(int)); // para freq de cada diferente elemento
  vetAux = malloc(n * sizeof(int)); // auxiliar para vetor de dados

  // Ideia:
  // 1. Computar frequencia de cada elemento considerando o "universo" (ideia de "vetor de bits"): O(n)
  // 2. Acumular as frequencias (de 0 ate U-1) somando frequencia acumulada anterior (FAA)
  // 3. A posicao da primeira ocorrencia de cada elemento e' dada pela FAA
  //    A posicao da proxima ocorrencia do mesmo elemento e' na posicao seguinte

  // 1. Computar frequencia de cada elemento considerando o "universo" (ideia de "vetor de bits"): O(n)
  for (i = 0; i <= U; i++)
    vetFreqAcum[i] = 0;
  for (i = 0; i < n; ++i) { // anotar a freq de i na posicao i+1 => permite pegar a freq do 0 (0+1-1)
    ind = vet[i]; // encontra posicao (ind) do elemento no "vetor de bits"
    vetFreqAcum[ind+1]++; // mais uma ocorrencia desse elemento => usar posicao seguinte
    //D1 printf(" %3d", vetFreqAcum[ind+1]); //D1 para examinar as frequencias
    }
  //D1 printf("\n");

  // 2. Acumular as frequencias (de 0 ate U-1) somando frequencia acumulada anterior (FAA)
  // Acumular frequencias: vetFreqAcum[i] recebera a frequencia de i-1 => recebe soma dos anteriores
  for (i = 1; i <= U; i++) {
    vetFreqAcum[i] += vetFreqAcum[i-1];
    }
  //D1 printf("FAA: "); imprimeVetor(vetFreqAcum, U); // no conj universo

  // 3. A posicao da primeira ocorrencia de cada elemento e' dada pela FAA
  //    A posicao da proxima ocorrencia do mesmo elemento e' na posicao seguinte
  // Como vetFreqAcum[i] e' a freq. de todos os predecessores de i
  // entao o elemento de i deve ser posicionado no indice vetFreqAcum[i] e proximas ocorrencias nas seguintes
  for (i = 0; i < n; i++) {
    ind = vet[i];                      // pegar indice do elemento no vetor "universo" (1 a menos pois o primeiro deve ir para 0 e sua freq e' 1)
    vetAux[vetFreqAcum[ind]] = vet[i]; // colocar na posicao considerando os anteriores
    vetFreqAcum[ind]++;                // a proxima ocorrencia do elemento i deve ir para proxima posicao
    //D2 printf("(%2d) %2d para posicao %2d\n", ind-1, vet[i], vetFreqAcum[ind-1]);
    }
  //D1 printf("FAA: "); imprimeVetor(vetFreqAcum, U);

  // vetAux[0..n-1] este em ordem crescente
  for (i = 0; i < n; ++i)
    vet[i] = vetAux[i];

  free(vetFreqAcum); // libera memoria
  free(vetAux);
  }

// inicia aqui...
int main (void) {
  int V[TAM], tam;
  int continua, loc, x;
  char c;

  printf("\n\n\nDados iniciais:\n");
  tam = TAM;
  gerarVetorDados(V, tam, INTERVALO);
  imprimeVetor(V, tam);

  ordenaPorFrequencia(V, tam, INTERVALO);

  printf("\nOrdenado:\n");
  imprimeVetor(V, tam);

  return 0;
  }
