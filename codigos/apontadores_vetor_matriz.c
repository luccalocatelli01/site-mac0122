/* apontadores_vetor_matriz.c — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. Material didático de MAC0122, IME-USP.
 * https://www.ime.usp.br/~leo/mac/mac122/introducao_apontadores_vetor_matriz.html */

// Prof. Leo^nidas - http://www.matematica.br http://line.ime.usp.br
// MAC0122 - 2017/09

// Introducao aos apontadores em C
// Principio: os sistema operacionais alocam memoria de modo consecutivo, ou seja, para "int a, b;"
// o espaco para o 'a' estara' ao lado do espaco para o 'b'. No Linux o espaco do 'a' vem antes (i.e., alocacao "crescente").
// Se voce^ usa outro sistema operacional, faca alguns testes para descobrir... (veja o bloco comentado com /* e */)

// gcc -fsanitize=address -g -o introducao_apontadores introducao_apontadores.c

#include <stdio.h>

int main (void) {
  int a, b, c;                            // os espacos para estas variaveis estarao consecutivos
  int *ap_a = &a, *ap_b = &b, *ap_c = &c; // declar apontadores, apontando para as variaveis 'a, b, c': '&' devolve o endereco da variavel
  float x, y, z;
  float *ap_x = &x, *ap_y = &y, *ap_z = &z; // idem para 'x, y, z'

  int M[2][3][4], conta = 1, i, j, k, *p; // para teste com matrizes/"arranjos"

  // Agora vamos atribuir valores `as variaveis 'a,b,c,x,y,z' a partir de seus apontadores:
  *ap_a = 1; *ap_b = 3; *ap_c = 5; // operador '*' devolve conteudo apontado (logo aplicavel apenas a apontadores)
  *ap_x = 1; *ap_y = 3; *ap_z = 5; // assim, estamos atribuindo valores `as variaveis 'a,b,c,x,y,z'!
  printf("a=%d, b=%d, c=%d\nx=%.1f, y=%.1f, z=%.1f\n", a, b, c, x, y, z); // devera imprimir: "a=1, b=3, c=5" e "x=1.0, y=3.0, z=5.0"

  /* Esta e' a vantagem de usar comando de linha (quando necessario e' facil "desligar" um bloco inteiro
  // Se fizer uma entrada via teclado, pode usar o "scanf" com os apontadores
  printf("Digitar um inteiro e um float: ");
  scanf("%d %f", ap_a, ap_x);     // passa os enderecos das variaveis 'a' e 'x'
  printf("a=%d, x=%.1f\n", a, x); // logo imprime os valores digitados
  */

  // Agora facamos um teste com um agregado de dados do tipo matriz
  // Ao declarar um vetor "int v[5];", reserva-se 5 posicoes para "int" sendo
  // a primeira para X, entao a segunda para X+1 e assim por diante (supondo "end. crescente")
  // Ao declarar uma matriz "int m[3][4];" reserva-se 3*4 posicoes, sendo
  // * X,   X+1, X+2 para a primeira linha (m[0])
  // * X+3, X+4, X+5 para a segunda linha (m[1]) e assim por diante
  // Ao declarar uma matriz "int m[2][3][4];" reserva-se 2*3*4 posicoes, sendo
  // * X,   X+1, X+2, X+3 para a "primeira" matriz m[0][0] (m[0][0][0] ate m[0][0][3])
  // * X+3, X+4, X+5, X+6 para a "segunda"  matriz m[0][1] (m[0][1][0] ate m[0][1][3]) e assim por diante
  // PORTANTO, "M[i][j]" comporta-se com um vetor, ou seja, havendo uma funcao que tenha vetor para parametro formal,
  // pode receber como parametro efetivo "M[i][j]".
  // Exercicio: Implemente uma funcao 'produtoInterno' que faca o produto interno de dois vetores, depois use-a para computar A*x (A matriz e x vetor)
  for (i=0; i<2; i++)
    for (j=0; j<3; j++)
      for (k=0; k<4; k++)
        M[i][j][k] = conta++;

  // Supondo um sistema operacional como o Linux no qual o enderecamento e' crescente.
  p = M; // aponta para inicio da matriz
  for (i=0; i<2*3*4; i++)
    printf("%2d ", *p++);
  printf("\n");
  // Revendo, agora imprimindo via matriz e pulando linhas
  for (i=0; i<2; i++) {
    printf("---\nMatriz %d\n", i);
    for (j=0; j<3; j++) {
      for (k=0; k<4; k++)
        printf("%2d ", M[i][j][k]);
      printf("\n");
      }
    }

  // Supondo um sistema operacional que use enderecamento decrescente (e.g., como o ?)
  /*
  p = M; // aponta para inicio da matriz
  for (i=0; i<2*3*4; i++)
    printf("%2d ", *p--);
  printf("\n");
   */

  return 0;
  }
