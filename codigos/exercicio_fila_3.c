#include <stdio.h>

typedef struct {
    int senhas[5];
    int quantidade;
} Fila;

int entraFila(Fila *f, int senha){
    if(f->quantidade < 5){
        f->senhas[f->quantidade] = senha;
        f->quantidade ++;
        return 1;
    }

    return 0;
}

int atendeFila(Fila *f, int *atendida){
    if(f->quantidade > 0){
        *atendida = f->senhas[0];
        f->quantidade --;
        for(int i = 0; i < f->quantidade; i ++){
            f->senhas[i] = f->senhas[i + 1];
        }
        return 1;
    }

    return 0;
}

int main(void){
    Fila fila = {{0}, 0};
    Fila *p = &fila;

    
    int comandos;
    scanf("%d", &comandos);
    char comando;
    while(comandos > 0){
        scanf(" %c", &comando);
        int x;

        if(comando == 'E'){
            scanf("%d", &x);
            if(!entraFila(p, x)) printf("cheia\n");
        } else if (comando == 'A'){
            if(atendeFila(p, &x)) printf("%d\n", x);
            else printf("vazia\n");
        }
    
        comandos --;
    }

    return 0;
}
