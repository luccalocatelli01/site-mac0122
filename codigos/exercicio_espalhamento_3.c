#include <stdio.h>

int inserir(int tabela[], int chave){
    int n = chave % 7;
    int inicio = n;

    if(tabela[n] == -1){
        tabela[n] = chave;
    } else {
        while(tabela[n] != -1){
            n ++;
            if(n == 7) n = 0;
            if(n == inicio) return -1;
        }
        tabela[n] = chave;
    }

    return n;
}

int buscar(int tabela[], int chave){
    int n = chave % 7;
    if(tabela[n] == -1) return -1;
    int inicio = n;
    while(tabela[n] != chave){
        n ++;
        if(n == 7) n = 0;
        if(n == inicio || tabela[n] == -1) return -1;
    }

    return n;
}

int main(void){
    int vetor[7];
    for(int i = 0; i < 7; i++){
        vetor[i] = -1;
    }

    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    inserir(vetor, a);
    inserir(vetor, b);
    inserir(vetor, c);
    inserir(vetor, d);

    int x;
    scanf("%d", &x);

    printf("%d\n", buscar(vetor, x));
    return 0;
}
