/* vetor_struct.c — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. Material didático de MAC0122, IME-USP.
 * https://www.ime.usp.br/~leo/mac/mac122/modelo_vetor_struct.html */

// Prof. Leo^nidas - http://www.matematica.br http://line.ime.usp.br
// MAC0122 - 2026/09/13; 2017/09/22
//
// Descricao: Exemplo de uso de "struct" e "typedef" (para construir novos tipos) e passagem por referencia de "struct".

#include <stdio.h>
#include <string.h> // para 'strcpy(...)'

#define MAX 50 // numero maximo de registros
#define TE  10 // numero maximo de nomes no exemplo

typedef struct { // declaracao de construtor de tipo composto
   int id;     // identificador interno do registro
   double cpf; // usar 'double' para evitar que 9 digitos "estoure" a precisao de "float"
   char nome[MAX];
   } Registro; // nome do novo tipo

// Exemplo de declaracao de vetor de constantes
char * exemplosNomes[] = { "aluno 0", "aluno 1", "aluno 2", "aluno 3", "aluno 4", "aluno 5", "aluno 6", "aluno 7", "aluno 8", "aluno 9" };
int vetCPF[] = { 123123123.12, 213123133.13, 312123143.14, 423123153.15, 523123163.16,
     623123173.17, 723123183.18, 823123193.19, 923123203.20, 987123213.21 }; // "simular" CPF - para nao precisar digitar...
// Busca registro cujo identificador eh ID
// Devolve: j entre e e d se encontrou na posicao j; -1 se x nao pertence a 'vet[e..d]'
int buscaPorId (Registro vet[], int n, int id) {
   // fazer...
   return -1;
   }

// Busca registro por nome
// Devolve: j entre e e d se encontrou na posicao j; -1 se x nao pertence a 'vet[e..d]'
int buscaPorNome (Registro vet[], int n, char *nome) {
   // fazer...
   return -1;
   }

void imprimirRegistro (Registro reg) {
   printf(" - %3d : %11.2f : %s\n", reg.id, reg.cpf, reg.nome);
   }

// Insere dados para registro
// Obrigatorio passar o Registro por referencia para o parametro efetivo ser alterado (onde houve a chamada)
void inserirRegistro (Registro *reg, int idP, double cpfP, char *nomeP) {
   reg->id = idP;   // Note que para pegar campo de "apontador para registro" usa-se a diretiva "->",
   reg->cpf = cpfP; // experimente compilar com "*reg.id = idP; *reg.cpf = cpfP;" para ver o que ocorre
   strcpy(reg->nome, nomeP);
   }

// Comeca aqui...
int main (void) {
   Registro dados[MAX]; // vetor de registros
   int n = TE;
   int i;
   double cpf;
   // entrada de dados: tem que estar ordenado!
   for (i=0; i<n; i++) {
     cpf = vetCPF[i]; // dados de CPF
     inserirRegistro(&dados[i], i, cpf, exemplosNomes[i]);
     imprimirRegistro(dados[i]);
     }
   return 0;
   }
