/* processa_arquivo.c — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. Material didático de MAC0122, IME-USP.
 * https://www.ime.usp.br/~leo/mac/mac122/exemplo_processa_arquivo.html */

// MAC122 - 2017 - Prof. Leo^nidas O. Branda~o
// POLI - Computacao

// Introducao a leitura/gravacao de arquivos (usando 'fgets')
// Modelo de codigo para leitura de arquivo texto, fazendo um processamento simples e gerando
// como resposta um arquivo HTML.
// Ilustra o funcionamento das funcoes 'strlen(...)' e 'strcpy(...)' da biblioteca "string.h".

// Para compilar com exame de "estouro" de vetor (e usar padrao o padrao ISO de 1990 para a linguaem C"):
// $ gcc -fsanitize=address -g -std=c99 -o exemplo_processa_arquivo exemplo_processa_arquivo.c

#include <stdio.h>
#include <stdlib.h> // para 'malloc(...)'
// #include <string.h> // se for usar a funcao 'strcpy(...)' da biblioteca (aqui implementei como 'strcpyNosso(...)')a

#define MAXLINHAS    100
#define MAXCOMPLINHA 255
#define MAXN          60

// Variaveis globais para gerar um cabelha e um rodape no arquivo de saida.
// O '\' ao final indica que a linha NAO acabou...
char CABECALHO[] = "<!DOCTYPE html>\
<html class=\"client-nojs\" lang=\"en\" dir=\"ltr\">\
<head>\
 <meta charset=\"UTF-8\"/>\
 <title>MAC122 :: modelo para ler/processar/gravar</title>\
</head>\
<h3>MAC122 :: modelo para ler/processar/gravar</h3>\
<font color=\"#0000aa\"><p>Veja os primeiros caracteres das linhas nao vazias do arquivo <tt>%s</tt>.</p></font>\
<table>\n";

char RODAPE[] = "\n</table>\n</body>\n</html>";

// Verifica comprimento da linha (codificado de modo compacto)
int strlenNosso (char *strScr) {
  int tam = 0;
  while (*strScr++) tam++; // pa'ra quando encontrar '\0' (finalizador de "strings" em C)
  return tam;
  }

// Copia os caracteres de 'strorig' em 'strdest'. Note que 'strdest' ja TEM que ter espaco alocado!
char *strcpyNosso (char *strdest, const char *strorig) {
  char *apont = strdest;
  while ((*strdest++ = *strorig++)) ; // copia caractere a caractere
  return apont; // devolva o endereca da "string" que recebeu a copia
  }

// Se linha nao nula, copie um parte inicial e avise tamanho
// senao devolva -1
int processaLinha (char linha[], char vet[], int conta) { // 'conta' apenas para ajudar depuracao...
  int i, j, total = 0;
  if (conta==-1) printf("processaLinha: %s\n", linha); // para testes
  if (linha[0]=='\0' || linha[0]=='\n') return -1; // linha vazia, nada a fazer...
  i = 0;
  while (linha[i]==' ' || linha[i]==9) i++; // ignora brancos e TAB = encontra primeiro caracter util (ASCII 9 => TAB)
  j = i;
  while (linha[j]!='\0' && linha[j]!='\n') j++; // encontrar ultimo caractere (nao final)
  if (conta==-1) printf(" (i=%d, j=%d): linha[%d]=%c=%d\n", i, j, j-1, linha[j-1], linha[j-1]); // para testes
  vet[total++] = linha[i++]; // copie primeiro caractere
  if (i<j) {
    vet[total++] = linha[i++]; // havendo, copie segundo
    if (i<j) {
      vet[total++] = linha[i++]; // havendo, copia terceiro
      if (i<j) {
        vet[total++] = linha[i++]; // havendo, copia quarto
        }
      }
    }
  vet[total] = '\0'; // finaliza "string"
  if (conta==-1) printf(" vet=%s\n", vet);
  return i;
  }

// Funcao para leitura de arquivo com texto.
// Recebe: 'nomeArqEnt' nome do arquivo e 'vet_nomes' vetor de "strings" para armazenar linhas lidas
// Devolve: numero de caracteres no arquivo
int leitura (char *nomeArqEnt, char vet_nomes[][MAXN]) {
  FILE *in_file  = fopen(nomeArqEnt, "r"); // read only
  char linha[MAXCOMPLINHA];
  int conta = 0, resp;

  if (in_file == NULL) { // Arquivo existe?
    printf("Erro! Nao foi possivel abrir o arquivo %s\n", nomeArqEnt);
    fclose(in_file);
    return -1;
    }
  printf("---\nInicia leitura do arquivo %s\n", nomeArqEnt);

  conta = 0;
  while (1) { // elimina linhas iniciais
    if (fgets(linha, MAXCOMPLINHA, in_file)==NULL || ferror(in_file) || feof(in_file) ) // char *fgets(char *str, int n, FILE *stream)
      break; // final de arquivo
    resp = processaLinha(linha, vet_nomes[conta], conta);
    if (resp>0) { // mais uma "substring" copiada!
      // printf("%3d : %s", conta, linha);
      conta++;
      }
    }
  printf("Total de linhas: %d\n---\n", conta);
  fclose(in_file);
  return conta;
  } // int leitura(char *nomeArqEnt, char vet_nomes[][MAXN])

// Comece por aqui!
// argv[0]="./programa_compara" e demais os argumentos usados
int main (int argc, char **argv) {
  char *arq_entra; //[MAXN];
  char arq_saida[MAXN];

  char vetDados[MAXLINHAS][MAXN]; // ilustrando como pegar trechos do codigo...

  int conta = 0;
  int conta_Apolo = 0;
  int i, n;

  if (argc < 3) {
    printf("Faltaram os nomes dos arquivos de entrada C ou de saida HTML (na verdade NAO esta gravando, para gravar 'descomente' os \\S)\n");
    printf("Linha de comando: ./exemplo_processa_arquivo nome_arquivo.c nome_arquivo.html\n");
    return 1; // faltou um parametro, erro
    }

  //D printf("#argc=%d\n", argc); n = argc; for (i=0; i<n; i++) printf(" %d : %s\n", i, argv[i]);
  arq_entra = malloc((strlenNosso(argv[1])+1) * sizeof(char)); // printf(" %d : %s\n", strlenNosso(argv[1]), argv[1]);
  strcpyNosso(arq_entra, argv[1]); //D printf("arq_entra = %s\n", arq_entra);

  conta = leitura(arq_entra, vetDados);
  if (conta<0) {
    printf("\nErro na leitura do arquivo %s (codigo %d)\n", arq_entra, conta);
    return 1;
    }

  //D printf("---\nfinal leitura arquivo IME: conta=%d\n", conta);
  // Gerar a resposta de processamento (imprimir na tela e gerar novo arquivo)
  FILE *out_file = fopen(argv[2], "w"); // "write only"
  printf("Lista de primeiros (ate) 4 caracteres de cada linha nao nula\n");
  fprintf(out_file, CABECALHO, arq_entra);
  for (i=0; i<conta; i++) {
    printf("%3d : %s\n", i, vetDados[i]);
    fprintf(out_file, " <tr><td>Linha %3d : </td> <td> %s </td></tr>\n", i, vetDados[i]);
    }
  fprintf(out_file, RODAPE);
  fclose(out_file);

  return 0;
  }
