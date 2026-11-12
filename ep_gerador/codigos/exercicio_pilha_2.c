/* Exercício: quais permutações de 1 2 3 4 saem de uma pilha?
   Os números entram em ordem (1, 2, 3, 4); a cada passo podemos empilhar o
   próximo da entrada ou desempilhar o topo para a saída. */
#include <stdio.h>

#define QUANTIDADE 4

/* Simula: devolve 1 se a pilha consegue produzir a sequência desejada. */
int pilha_produz(const int desejada[]) {
    int pilha[QUANTIDADE], topo = -1;
    int proximo_da_entrada = 1;
    for (int posicao = 0; posicao < QUANTIDADE; posicao++) {
        /* empilha até o número desejado aparecer no topo */
        while (proximo_da_entrada <= QUANTIDADE && (topo == -1 || pilha[topo] != desejada[posicao])) {
            pilha[++topo] = proximo_da_entrada++;
        }
        if (topo == -1 || pilha[topo] != desejada[posicao]) return 0;   /* ficou embaixo de outro */
        topo--;
    }
    return 1;
}

/* Gera as 24 permutações em ordem crescente e testa cada uma. */
void testar_permutacoes(int permutacao[], int usados[], int posicao, int *possiveis) {
    if (posicao == QUANTIDADE) {
        int produz = pilha_produz(permutacao);
        *possiveis += produz;
        printf("%d %d %d %d  %s\n", permutacao[0], permutacao[1], permutacao[2], permutacao[3],
               produz ? "sim" : "NÃO");
        return;
    }
    for (int valor = 1; valor <= QUANTIDADE; valor++) {
        if (usados[valor]) continue;
        usados[valor] = 1;
        permutacao[posicao] = valor;
        testar_permutacoes(permutacao, usados, posicao + 1, possiveis);
        usados[valor] = 0;
    }
}

int main(void) {
    int permutacao[QUANTIDADE], usados[QUANTIDADE + 1] = {0}, possiveis = 0;
    testar_permutacoes(permutacao, usados, 0, &possiveis);
    printf("possíveis: %d de 24\n", possiveis);
    return 0;
}
