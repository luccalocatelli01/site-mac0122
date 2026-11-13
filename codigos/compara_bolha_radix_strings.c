/* compara_bolha_radix_strings.c — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. Material didático de MAC0122, IME-USP.
 * https://www.ime.usp.br/~leo/mac/mac122/ordena_string_compara_metodos.html */

// Prof. Leo^nidas - http://www.matematica.br http://line.ime.usp.br
// MAC122
// 2017/09/07

// Compara tempo efetivo de execucao de 2 metods de ordenacao, SEM trocar efetivamente as "strings" de posicao,
// usando vetor auxiliar para ordem (main.vetOrdem[]). Os metodos sao "Bolha" e "Radix".
// Supoe que os nomes usam apenas caracteres de 'a' ate' 'z' (pequena faixa de valores para "universo")

// Le arquivo com N+1 linhas, estando na primeir "N" e nas seguintes um nome cada

// Complexidade Bolha: O(n*n * u), se u = comprimento medio das palavras
// Complexidade Radix: O(n + u), se u = #universo

// Exercicio 1: Altere o codigo para ler as linhas e deduzir numero nomes
// Exercicio 2: Prove que o algoritmo de ordenacao Radiz e' de fato estavel

// Para depurar gerenciamento de memoria em caso de erro de 'malloc/free':
//  $ gcc -fsanitize=address -g -o ordena_string_por_frequencia ordena_string_por_frequencia.c
// Para compilar com caracteres especiais "L'\u00e1"
//  $ gcc -fsanitize=address -g -std=c99 -o ordena_string_compara_metodos ordena_string_compara_metodos.c

// Arquivos para teste:
// https://pt.wikipedia.org/wiki/Categoria:Matemáticos_do_Brasil

// Referencias:
// 1. "Chapter Ten. Radix Sorting" do Sedgewick (pg 154 "Program 10.2. MSD radix sort")
// 2. Paulo Feofilof: https://www.ime.usp.br/~pf/algoritmos/

#include <stdio.h>
#include <stdlib.h> // para "rand()"
#include <string.h> // para "strcmp(...)" e "strcpy(...)"
#include <time.h>   // para "clock_t", "clock()"

#define MAX           5000 // maximo de elementos
#define TAM             10 // testar com TAM elementos
#define MAXCOMPLINHA  1024 // tamanho maximo de uma linha
#define INTERVALO       27 // 'A' ate 'Z' (97 a 122)


// Comprimento de "strings"
int comprimento (char *vetStr) { // evita "strlen(vetStr[i])" devolvendo 1 a mais...
  int i = 0;
  while (vetStr[i]!='\0' && vetStr[i]!='\n') i++;
  return i;
  }

// Tentativa de trocar caracteres especiais para "base" em ASCII
// Ver: https://www.w3.org/People/danield/unic/unitra.htm ; https://www.w3.org/International/questions/qa-what-is-encoding
void sanitarizaASCII (int ind, char *nome) {
  int i = 0;
  char c1; //unsigned
  wchar_t c; // para conseguir armazenar caractere "estendido" (2 bytes)
  while ((c=nome[i])!='\0' && c!='\n') {
    if (c==' ') {
      }
    else
    if (c>='A' && c<='Z') { // 'A'=65, 'B'=66, ... 'W'=87, 'x'=88, 'y'=89, 'z'=90
      nome[i] = c + ('a' - 'A');
      }
    else
    if (c<'a' || c>'z') { // 'a'=97, 'b'=98, ... 'w'=119, 'x'=120, 'y'=121, 'z'=122
      switch (c) { // tente trocar alguns caracteres usando notacao Unicode
        case L'\u00e1' : // a'
        case L'\u00e0' : // `a
        case L'\u00e2' : // a^
        case L'\u00e3' : // a~
        case L'\u00e4' : // a"
             c1 = 'a'; printf(" *** i=%d, %s", i, nome); break;
        // ...
        case L'\u00e7' : // c,
             c1 = 'c'; printf(" *** i=%d, %s", i, nome); break;
        default: c1 = ' ';
        }
      nome[i] = c1;
      } //printf("2: nome=%s", nome);
    i++;
    }
  }

// Ler uma linha do arquivo apontado
char * leituraElemento (FILE *aptf, int i, char linha[]) {
  if (fgets(linha, MAXCOMPLINHA, aptf)==NULL || ferror(aptf) || feof(aptf) ) { // char *fgets(char *str, int n, FILE *stream)
    if (comprimento(linha)>0) { // tratar caso de ultima linha ter nome
      sanitarizaASCII(i, linha); // tenta "limpar" linha eliminando caracteres especiais (i apenas apoio 'a depuracao)
      return linha;
      }
    return NULL; // final de arquivo
    }
  sanitarizaASCII(i, linha);
  return linha;
  }

// Leia vetor de "string", devolva o comprimento da maior (uniformiza todas)
int leituraVetor (FILE *apf, char vetStr[][MAXCOMPLINHA], int vetOrdem[], int *N) {
  int *vetComprimentos;
  int i = 0, j, tamI, max = -1; //, imax;
  fscanf(apf, "%d", N);
  if (*N > MAX) {
    // printf("Erro! Primeira linha do arquivo de 'string' afirma existirem %d elementos, mas limite e' %d!\n", *N, MAX);
    return -*N;
    }
  vetComprimentos = malloc(*N * sizeof(int)); // comprimento das palavras (evita computar 2 vezes)

  leituraElemento(apf, 0, vetStr[0]); // pula restante da linha

  for (i = 0; i < *N; i++) {
    if (leituraElemento(apf, i, vetStr[i]) == NULL) { // EOF
      i--;
      break;
      }
    tamI = comprimento(vetStr[i]); // para nao usar "strlen(vetStr[i]" que pode devolver 1 a mais...
    vetComprimentos[i] = tamI;
    //D printf("#=%d : vetStr[%d]=%s", tamI, i, vetStr[i]);
    if (tamI>max) { max = tamI; } // imax = i; }
    }

  printf("leituraVetor: maior linha tem max=%d caracteres\n", max);
  for (i = 0; i < *N; i++) { // para uniformizar
    vetOrdem[i] = i; // ordem inicial e' identidade
    for (j = vetComprimentos[i]; j < max; j++) { // uniformiza "strings"
      vetStr[i][j] = ' ';
      }
    vetStr[i][j] = '\0';
    }
  free(vetComprimentos); // libera memoria alocada
  return max;
  } // int leituraVetor(FILE *apf, char vetStr[][MAXCOMPLINHA], int vetOrdem[], int *N)

void iniciaVetorOrdem (int ord[], int N) {
  int i;
  for (i = 0; i < N; i++)
    ord[i] = i;
  }

// Auxilia depuracao
void imprimeVetorOrdem (int ord[], int N) {
  int i;
  for (i = 0; i < N; i++) {
    printf("%3d", ord[i]);
    }
  printf("\n");
  }

// Imprime vetor de nomes usando vetor de ordem "ord[]"
void imprimeVetor (FILE *ap, char vetStr[][MAXCOMPLINHA], int ord[], int N) {
  int i;
  for (i = 0; i < N; i++) {
    fprintf(ap, " %3d : |%s|\n", i, vetStr[ord[i]]);
    }
  }

void imprimeVetorDireto (char vetStr[][MAXCOMPLINHA], int N) {
  int i;
  for (i = 0; i < N; i++) {
    printf(" %3d : |%s|\n", i, vetStr[i]);
    }
  }

//--------------------------------------------------------------------------
// Ordena via Bolha por vetor auxiliar (sem trocar elementos)
void trocaEmVetorOrd (int vetOrdem[], int i, int j) {
  int aux;
  aux = vetOrdem[i];
  vetOrdem[i] = vetOrdem[j];
  vetOrdem[j] = aux;
  }

void ordenaBolhaOrdem (char vetStr[][MAXCOMPLINHA], int ord[], int N) {
  int i, j;
  for (i = 1; i <= N; i++) {
    for (j = i; j > 0; j--) {
      if (strcmp(vetStr[ord[j-1]], vetStr[ord[j]]) > 0)
        trocaEmVetorOrd(ord, j, j-1);
      }
    }
  }

//--------------------------------------------------------------------------
// Ordena via Bolha trocando elementos
void trocaEmVetor (char vetStr[][MAXCOMPLINHA], int i, int j) {
  char aux[MAXCOMPLINHA]; // como trata-se de "string", cada copia e' um laco
  strcpy(aux, vetStr[i]);       // aux = vetStr[i];
  strcpy(vetStr[i], vetStr[j]); // vetStr[i] = vetStr[j];
  strcpy(vetStr[j], aux);       // vetStr[j] = aux;
  }

// Ordena via bolha trocando elementos
void ordenaBolha (char vetStr[][MAXCOMPLINHA], int N) {
  int i, j;
  for (i = 1; i <= N; i++) {
    for (j = i; j > 0; j--) {
      if (strcmp(vetStr[j-1], vetStr[j]) > 0)
        trocaEmVetor(vetStr, j, j-1);
      }
    }
  }

//--------------------------------------------------------------------------
// Ideia de "vetor de bits" associando caracteres ' ', 'a', 'b', 'c', ... 'as posicoes 0, 1, 2, ... do vetor
// Entretanto para funcionar o computo de frequencias acumuladas
// Devolve como indice a posicao seguinte (para liberar o 0 e permitir pegar o anterior dele)
int pegaIndice (char c, int U, int desc) {
  int ind;                // indice do caractere: ' ' = 32 -> 1; 'a' -> 2; 'b' -> 3; ...
  if (c==' ') ind = 1;    // encontra posicao (ind) do elemento no vetor auxiliar
  else ind = c - 'a' + 2; // 'a' -> 2; 'b' -> 3; ...
  if (ind<0 || ind>U) {   // detectar valores do "universo" erroneos...
    printf("Erro: ultrapassou universo previso!\nCaractere '%c' = %d -> %d > %d\n", c, c, ind, U);
    return -1;
    }
  return ind;
  }

// Ordena crescente v[0..n-1] supondo que os elementos do vetor pertencem ao universo 0..U-1
// Utiliza vetor de ordem 'vetOrdem[]' para NAO mover "strings"
// Supoe que vetor de "strings" 'vetStr[][]' esteja uniformizado
// (todas de mesmo comprimento, completadas com brancos 'a direita)
// IMPORTANTE: o metodo de ordenacao por "digito" menos significative e' estavel
void ordenaPorFrequencia (char vetStr[][MAXCOMPLINHA], int vetOrdem[], int tamLnh, int n, int U) {
  int ind, jj, i;
  int *vetFreqAcum, *vetAux, *vetOrd1;
  char *vet;
  vetFreqAcum = malloc((U+1) * sizeof(int)); // para freq de cada diferente elemento
  vetAux = malloc(n * sizeof(char)); // auxiliar para vetor de dados
  vet = malloc(n * sizeof(char)); // auxiliar para armazenar caractere da posicao jj das "strings"
  vetOrd1 = malloc(n * sizeof(int)); // auxiliar para atualizar vetor de ordem

  // Ideia:
  // 1. Computar frequencia de cada elemento considerando o "universo" (ideia de "vetor de bits"): O(n)
  // 2. Acumular as frequencias (de 0 ate U-1) somando frequencia acumulada anterior (FAA)
  // 3. A posicao da primeira ocorrencia de cada elemento eh dada pela FAA
  //    A proxima ocorrencia do elemento eh na posicao seguinte

  // Ordenar por "digito" menos significativo, como metodo e' estavel ao final ordena tudo
  for (jj = tamLnh-1; jj >= 0; jj--) {

    // 1. Computar frequencia de cada elemento considerando o "universo" (ideia de "vetor de bits"): O(n)
    for (i = 0; i <= U; i++)
      vetFreqAcum[i] = 0;
    for (i = 0; i < n; ++i) {
      vet[i] = vetStr[vetOrdem[i]][jj]; // pegar caractere respeitando a ordem
      if (vet[i]=='\0' || vet[i]==0) { // detecta erro: caractere invalido
        printf("Erro em ordenacao: caractere invalido na posicao %d de %s\n", jj, vetStr[i]); return;
        }
      ind = pegaIndice(vet[i], U, 0);
      if (ind<0) { // detecta erro: caractere fora do "universo" previso
        printf("Erro em ordenacao (1): indice invalido! (jj=%d, i=%d, c=%c)\n%s\n", jj, i, vet[i], vetStr[jj]); return;
        }
      vetFreqAcum[ind]++; // mais uma ocorrencia desse elemento
      }

    // 2. Acumular as frequencias (de 0 ate U-1) somando frequencia acumulada anterior FAA
    // Acumular frequencias: vetFreqAcum[i] recebera a frequencia de i-1 => recebe soma dos anteriores
    for (i = 1; i <= U; i++) {
      vetFreqAcum[i] += vetFreqAcum[i-1];
      }

    // 3. A posicao da primeira ocorrencia de cada elemento eh dada pela FAA
    //    A proxima ocorrencia do elemento eh na posicao seguinte
    // Como vetFreqAcum[i] eh a freq de todos os predecessores de i
    // entao o elemento de i deve ser posicionado no indice vetFreqAcum[i] e proximas ocorrencias nas seguintes
    for (i = 0; i < n; i++) {
      ind =  pegaIndice(vet[i], U, 1) - 1; // pegar indice do elemento no vetor "universo" (1 a menos pois o primeiro deve ir para 0 e sua freq e' 1)
      if (ind<0) { printf("Erro em ordenacao (2): indice invalido! (jj=%d, i=%d, c=%c)\n|%s|\n", jj, i, vet[i], vetStr[i]); return; }

      // vetOrd1[0..n-1] fornece "strings" em ordem crescente (menor na posicao 'vetOrdem[0]'
      vetOrd1[vetFreqAcum[ind]] = vetOrdem[i]; // elemento i tem posicao de ordem final 'vetFreqAcum[ind]'

      vetFreqAcum[ind]++;  // a proxima ocorrencia do elemento i deve ir para proxima posicao
      }

    // vetOrdem[0..n-1] fornece "strings" em ordem crescente (menor na posicao 'vetOrdem[0]'
    for (i = 0; i < n; i++) // nova ordem
      vetOrdem[i] = vetOrd1[i];

    } // for (jj = tamLnh-1; jj >= 0; jj--)

  free(vetFreqAcum); // libera memorias alocadas - importante se este metodo ficar ativo
  free(vetAux);
  free(vet);

  } // void ordenaPorFrequencia(char vetStr[][MAXCOMPLINHA], int vetOrdem[], int tamLnh, int n, int U)

// inicia aqui...
int main (int argc, char *argv[]) {
  FILE *apontEntrada, *apontSaida;
  char vetorDados[MAX][MAXCOMPLINHA];
  int vetOrdem[MAX];
  clock_t tempo_inicialF, tempo_finalF;   // via 'include "time.h"' para pegar tempo
  clock_t tempo_inicialB1, tempo_finalB1;
  clock_t tempo_inicialB2, tempo_finalB2;

  int tam, max;

  if (argc < 2) { //2 (argc < 3)
    //2 printf("Erro: eram esperados 2 nomes de arquivos, primeiro com nomes para ordenacao, segundo para saidas\n");
    //2 printf("./ordena_string_por_frequencia entradas saidas\n");
    printf("Erro: era esperado o nomes do arquivo com nomes a serem ordenados (primeira linha com N, seguido de N nomes)\n");
    printf("./ordena_string_compara_metodos entradas\n");
    return 1;
    }

  printf("Abre %s\n", argv[1]);
  apontEntrada = fopen(argv[1], "r");

  max = leituraVetor(apontEntrada, vetorDados, vetOrdem, &tam); // pegue tamanho uniformizado das "strings"
  fclose(apontEntrada);
  if (max < 0) {
    printf("Erro! Primeira linha do arquivo de 'string' afirma existirem %d elementos, mas limite e' %d!\n", -max, MAX);
    return 1;
    }

  printf("\n\n\nDados iniciais:\n");
  imprimeVetor(stdout, vetorDados, vetOrdem, tam);

  // 1. Ordena via frequencia (Radix) SEM trocas nas posicoes das "strings"
  tempo_inicialF = clock();
  ordenaPorFrequencia(vetorDados, vetOrdem, max, tam, INTERVALO);
  tempo_finalF = clock();

  printf("\nOrdenado por Frequencia sem trocas:\n");
  imprimeVetor(stdout, vetorDados, vetOrdem, tam);

  //2 printf("Abre arquivo para registrar nomes ordenados: %s\n", argv[2]);
  //2 apontSaida = fopen(argv[2], "w"); //
  //2 imprimeVetor(apontSaida, vetorDados, vetOrdem, tam);
  //2 fclose(apontSaida);

  // 2. Ordena via Bolha SEM trocas nas posicoes das "strings"
  iniciaVetorOrdem(vetOrdem, tam);
  tempo_inicialB1 = clock();
  ordenaBolhaOrdem(vetorDados, vetOrdem, tam-1);
  tempo_finalB1 = clock();
  printf("\nOrdenado por Bolha sem trocas:\n");
  imprimeVetor(stdout, vetorDados, vetOrdem, tam);

  // 3. Ordena via Bolha COM trocas nas posicoes das "strings"
  tempo_inicialB2 = clock();
  ordenaBolha(vetorDados, tam-1);
  tempo_finalB2 = clock();
  printf("\nOrdenado por Bolha com trocas:\n");
  imprimeVetorDireto(vetorDados, tam);

  printf(" tam = %5d\nTempos de execucao\n * Frequencia = %fs\n * Bolha ordem= %fs\n * Bolha      = %fs\n", tam,
         (double)(tempo_finalF  - tempo_inicialF)  / CLOCKS_PER_SEC,
         (double)(tempo_finalB1 - tempo_inicialB1) / CLOCKS_PER_SEC,
         (double)(tempo_finalB2 - tempo_inicialB2) / CLOCKS_PER_SEC);

  return 0;
  }
