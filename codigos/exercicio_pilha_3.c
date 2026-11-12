#include <stdio.h>

typedef struct {
    int valores[5];
    int quantidade;
} Pilha;

int empilha(Pilha *p, int valor){
    if(p->quantidade < 5){
        p->valores[p->quantidade] = valor;
        p->quantidade ++;
        return 1;
    }

    return 0;
}

int desempilha(Pilha *p, int *retirado){
    if(p->quantidade > 0){
        p->quantidade --;
        *retirado = p->valores[p->quantidade];
        return 1;
    }

    return 0;
}

int main(void){
    int comandos;
    scanf("%d", &comandos);

    Pilha pilha = {{0}, 0};
    Pilha *p = &pilha;

    int x;
    char comando;

    while(comandos > 0){
        scanf(" %c", &comando);

        if(comando == 'E'){
            scanf("%d", &x);

            if(empilha(p, x) == 0){
                printf("cheia\n");
            }

        } else if(comando == 'D'){
            int retirado;

            if(desempilha(p, &retirado) == 1){
                printf("%d\n", retirado);
            } else {
                printf("vazia\n");
            }
        }

        comandos --;
    }

    return 0;
}
