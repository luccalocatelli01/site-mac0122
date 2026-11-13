/* apontadores.c — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. Material didático de MAC0122, IME-USP.
 * https://www.ime.usp.br/~leo/mac/mac122/introducao_apontadores.html */

// Prof. Leo^nidas - http://www.matematica.br http://line.ime.usp.br
// MAC0122 - 2017/09/25

// Introducao aos apontadores em C: explica o uso dos operadores "&" e "*"
// Explica como funcionam os parametros da funcao "main"

#include <stdio.h>

// A funcao "main" e' o ponto de entrada do programa C e pode ser invocado recebendo parametros e devolvendo um resultado ("int").
// "int"          => funcao inicial (main) deve devolver inteiro (0 => sem erro; 1 => com erro)
// "int argc"     => recebera o numero de parametros usados na chamada deste programa C
// "char *argv[]" => recebera cada parametro usado na chamada deste programa (sendo o primeiro seu proprio nome)
int main (int argc, char *argv[]) {
  int n, i, a, b, *ap; // "ap" e' um apontador para variaveis do tipo "int"
  printf("Parametros usados:\n argc=%d\n", argc);
  for (i=0; i<argc; i++)
    printf(" %d : %s\n", i, argv[i]);

   // O operador "&" implica em pegar o endereco da variavel, nao o seu valor (lembrete, desse modo
   //   o motivo do "scanf" precisar do endereco da variavel, nao seu valor, e' para poder altera-la com o valor lido)
   // O operador "*" e' aplicavel apenas `a variaveis apontadoras (para variaveis) e
   //   implica que deve ser devolvido o conteudo da variavel apontada (pelo apontador)
   ap = &a;  // (i)  "ap" recebe o endereco reservado a variavel "a" ("ap" aponta para "a")
   *ap = 10; // (ii) como "ap" aponta para a variavel "a", entao essa ultima posicao de memoria recebera o valor 10
   printf("%d\n", a); // apenas para conferir a observacao (ii) acima
   return 0;
   }
