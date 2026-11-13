/* bolha_strings.c — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. Material didático de MAC0122, IME-USP.
 * https://www.ime.usp.br/~leo/mac/mac122/ordena_string_bolha.html */

// Prof. Leo^nidas - http://www.matematica.br http://line.ime.usp.br
// MAC122
// 2017/09/07

// Ordena vetor de palavras ("strings") usando o metodo da Bolha e trocando efetivamente as palavras de posicao
// Le de arquivo "N\n" e a seguir N linhas com um nome cada
// Complexidade: O(n*n * u), se u = comprimento medio das palavras

// Exercicio 1: Altere o codigo para ler as linhas e deduzir numero nomes
// Exercicio 2: Prove que o algoritmo de ordenacao implementado e' estavel

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCOMPLINHA    512 // maior comprimento de linha aceito
#define MAX           10000 // maior quantidade de linhas aceitas (no arquivo de entrada)

// Leia proxima linha do arquivo apontado por 'aptf', devolva no endereco da "string" que a recebeu
char * leituraElemento (FILE *aptf, char linha[]) {
  if (fgets(linha, MAXCOMPLINHA, aptf)==NULL || ferror(aptf) || feof(aptf) ) { // char *fgets(char *str, int n, FILE *stream)
    printf(" - %s", linha);
    if (linha != NULL) return linha;
    return NULL; // final de arquivo
    }
  printf(" * %s", linha);
  return linha;
  }

// Leia todas as linhas (de palavras) presentes no arquivo de entrada
// Primeira linha deve ter um inteiro com numero de palavras no arquivo (isso pode ser alterado, experimente)
void leituraVetor (FILE *apf, char vetStr[][MAXCOMPLINHA], int *N) {
  int i = 0, f;
  char *linha0;
  fscanf(apf, "%d", N); printf(" - n=%d\n", *N);
  f = *N;
  // Em geral, apos ler o inteiro o apontador e' posicionado para proximo caractere que
  // corresponderia ao final de linha ('\n'), assim precisa forcar para evitar pegar esta linha "nula".
  linha0 = leituraElemento(apf, vetStr[i]);
  if (linha0!=NULL && linha0[0]=='\0') f = *N+1; // ignore primeira linha
  for (i = 0; i < f; i++)
    if (leituraElemento(apf, vetStr[i]) == NULL)
      break;
  }

// Auxiliar
void imprimeVetor (char vetStr[][MAXCOMPLINHA], int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("%s", vetStr[i]);
    }
  }

// Troque de lugar as "strings" nas posicoes i e j
void trocaEmVetor (char vetStr[][MAXCOMPLINHA], int i, int j) {
  char aux[MAXCOMPLINHA];
  strcpy(aux, vetStr[i]);       // aux <- vetStr[i];
  strcpy(vetStr[i], vetStr[j]); // vetStr[i] <- vetStr[j];
  strcpy(vetStr[j], aux);       // vetStr[j] <- aux;
  }

// Ordena comparando palavras usando o metodo da Bolha e trocando as "strings" de posicao.
void ordenaBolha (char vetStr[][MAXCOMPLINHA], int N) {
  int i, j;
  for (i = 1; i < N; i++) { //D printf("\ni=%3d: ", i);
    for (j = i; j > 0; j--) { //D printf("%d ", j);
      if (strcmp(vetStr[j-1], vetStr[j]) > 0)
        trocaEmVetor(vetStr, j, j-1);
      }
    } //D printf("\n");
  }

// Comeca aqui!
int main (int argc, char *argv[]) {
  FILE *apont;
  char vetorDados[MAX][MAXCOMPLINHA];
  int N;

  if (argc < 2) {
      printf("Necessario um nome de arquivo como parametro\n");
      printf("Arquivo com: N seguido de N strings para ordenar\n");
      return 1;
      }
  printf("Abre %s\n", argv[1]); //return 1;
  apont = fopen(argv[1], "r");

  leituraVetor(apont, vetorDados, &N);

  printf("\nInicial:\n");
  imprimeVetor(vetorDados, N);

  ordenaBolha(vetorDados, N);

  printf("\nOrdenado:\n");
  imprimeVetor(vetorDados, N);

  return 0;

  }
