/* arvore_expressao.c — EP MAC0122
 * Adaptado de: BRANDÃO, L. O. Material didático de MAC0122, IME-USP.
 * https://www.ime.usp.br/~leo/mac/mac122/arvores/arvore_bin_expressao_aleatoria.html */

// Prof. Leo^nidas - http://www.matematica.br http://line.ime.usp.br
// MAC0122 - 2017/10/08
// Primeira versao de: 2003

// Exemplo de: arvore binaria (AB); expressao aritmetica (EA) em notacao in-fixa; expressao em notacao pos-fixa; listas ligadas
// Descricao: Constroi uma AB representando uma Ea, depois a avalia de 2 modos (iterativo e recursivo)

// gcc -fsanitize=address -g -o arvore_bin_expressao_aleatoria arvore_bin_expressao_aleatoria.c

#include <stdio.h>
#include <stdlib.h>

#define MAX      2 // maxima profundidade da arvore
#define Infimo   1 // so' aceita "operando" apos nivel 1
#define MAXREC  30 // tamanho maximo para a pilha
#define RESTO    5 // fator para diminuir valor dos numeros gerados
#define SEMENTE 11 // para geracao de numeros aleatorios

typedef struct Filho {
  struct Filho *esq;
  char tipo;
  union { char c; int i; } info; // se tipo='d' => <operador => usar 'char c'>; se tipo='n' => <operando => usar 'int i'>
  struct Filho *dir;
  } No;

int topo_ap, topo_v; // para simplificar usarei como globais (CUIDADO: evite, pois gera dificuldades de manutencao)

// Prototipos de funcoes
void imprime_arvore(No *r, int col);
No *adiciona_filho(int cont);
void monta_exp(No **)
//V2 No *monta_exp(void);

// Imprime arvore usando deslocanmento horizontal para indicar maior profundidade
void imprime_arvore (No *r, int col) { // col indica profundidade do no'
  int aux;
  if ( r!= NULL ) {
    if ( (*r).dir!=NULL ) imprime_arvore( (*r).dir, col+1 );
    for (aux=0; aux<col; aux++)
      printf("   ");
    if ((*r).tipo=='d') printf("%c\n",(*r).info.c);
    else                printf("%d\n",(*r).info.i);
    if ( (*r).esq!=NULL ) imprime_arvore( (*r).esq, col+1);
    }
  }

// Constroi arvore usando apenas operadores '*' e '+'
No *adiciona_filho (int cont) {
  No *aux;
  int aux1, aux2, n; char c;
  aux = malloc(sizeof(No));
  if (cont<MAX) { // dentro do limite de profundidade
    // Para GCC:  aux1 = rand()%2; // 0 => operador, 1 => operando
    aux1 = (int)(rand()%2); // 0 => operador, 1 => operando
    if (aux1 && cont>Infimo) {
      // e' operando
      n = (rand() % RESTO);
      if (n==0) n = 1; // evita 0 (0*n=0)
      (*aux).info.i = n;
      (*aux).tipo   = 'n';
      (*aux).esq    = NULL;
      (*aux).dir    = NULL;
      }
    else { // else de if (aux1 && cont>Infimo)
      // e' operador
      aux2 = rand()%2; // 0 => '+', 1 => '*'
      if (aux2)
        c='*';
      else
        c='+';
      (*aux).info.c = c;
      (*aux).tipo   = 'd';
      // e' operador => tem dois filhos
      (*aux).esq    = adiciona_filho( cont+1 );
      (*aux).dir    = adiciona_filho( cont+1 );
      } // else
    } // if (cont<MAX)
  else { // ja' atingiu o limite de profundidade, forca ser operando
    printf("ultimo cont=%d MAX=%d\n",cont,MAX);
    n = (rand() % RESTO);
    if (n==0) n = 1; // evita 0 (0*n=0)
    (*aux).info.i = n;
    (*aux).tipo   = 'n';
    (*aux).esq    = NULL;
    (*aux).dir    = NULL;
    } // else if (cont<MAX)
  return aux;
  } // adiciona_filho

//V2 No *monta_exp (void)
void monta_exp (No **r) {
  //V2 No *r;
  int aux1; char c;
  *r = malloc(sizeof(No)); // no' r aponta para novo no'
  srand(SEMENTE);
  aux1 = rand() % 2; // 0 => '+', 1 => '*'
  if (aux1) // decide operador: '+' ou '*'
    c='*';
  else
    c='+';
  (**r).info.c = c;
  (**r).tipo   = 'd';
  (**r).esq    = adiciona_filho(0);
  (**r).dir    = adiciona_filho(0);
  printf("\n retornou \n");
  //V2 return r;
  }

// Calcula valor da expressao de modo iterativo
int Calc_exp_it (No *r) {
  No *Ap[MAXREC], *pai, *aux;
  int V[MAXREC], topo_ap, topo_v, aux_esq, aux_dir;

  // auxiliar para termino do algoritmo
  aux = malloc(sizeof(No));
  (*aux).esq = (*aux).dir=NULL;
  topo_ap = topo_v = -1;
  Ap[++topo_ap] = aux;
  while (r!=NULL) {
    if ((*r).tipo=='d') { // e' operador => empilhe
      Ap[++topo_ap] = r;
      pai = r;
      r = (*r).esq;
      }
   else // e' operando => desempilhe 2
     if (r==(*pai).dir) { // e' filho direito => computa expressao
       V[++topo_v] = (*r).info.i;
       while (r==(*pai).dir) { // pegue 3 do topo da pilha e opere: operador operando1 operando2 => operando1 operador operando2 = operando3
         aux_dir = V[topo_v--];
         aux_esq = V[topo_v];
         if ((*pai).info.c=='+')
           V[topo_v] = aux_dir + aux_esq; // empilhe 'operando3'
         else
           V[topo_v] = aux_dir * aux_esq; // empilhe 'operando3'
         r = pai;
         pai = Ap[--topo_ap];
         }
       r = (*pai).dir;
       } // if (r==(*pai).dir)
    else { // e' filho esquerdo
       V[++topo_v] = (*r).info.i;
       r = (*pai).dir;
       }
    } // while

  return V[0];
  }

// Calcula expressao de modo recursivo
int Calc_exp_rec (No *r) {
  int aux_esq, aux_dir;
  if (r!=NULL)
    if ( (*r).tipo=='d' ) { // e' operador
      aux_esq = Calc_exp_rec( (*r).esq );
      aux_dir = Calc_exp_rec( (*r).dir );
      if ( (*r).info.c=='+' )
        return aux_esq + aux_dir;
      else
        return aux_esq * aux_dir;
      }
    else
      return (*r).info.i;
  else
    return 0; // --> so' sera' necessario se a arv. for vazia!
  }

//
int main (void) {
  No *raiz;

  printf("INICIO\n");

  //V2 raiz=monta_exp();
  monta_exp(&raiz);

  imprime_arvore(raiz, 0);

  printf("\nValor (iterativo) %d\n",Calc_exp_it(raiz));
  printf("\nValor (recursivo) %d\n",Calc_exp_rec(raiz));
  return 0;
  }
