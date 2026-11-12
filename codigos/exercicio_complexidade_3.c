#include <stdio.h>

int main(void){
    int contador = 0, n;

    scanf("%d", &n);

    int soma = 0;
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < 10; j ++){
            soma += i * j;
            contador ++;
        }
    }

    printf("(A) laco de n com laco de r = 10 dentro: %d\n", contador);
    soma = 0;
    contador = 0;

    for(int i = 1; i <= n; i = i * 2){
        soma += i;
        contador ++;
    }

    printf("(B) i dobrando ate n: %d\n", contador);
    soma = 0;
    contador = 0;

    for(int i = 0; i < n; i ++){
        for(int j = i; j < n; j ++){
            soma += i + j;
            contador ++;
        }
    }

    printf("(C) j de i ate n, para cada i: %d\n", contador);
    soma = 0;
    contador = 0;

    for(int i = 0; i < n; i ++){
        for(int j = 1; j < n; j = j * 2){
            soma += i + j;
            contador ++;
        }
    }

    printf("(D) laco de n com j dobrando dentro: %d\n", contador);
    soma = 0;
    contador = 0;

    for(int i = 0; i < n; i ++){
        soma += i;
        contador ++;
    }

    printf("(E) um laco de n: %d\n", contador);

    return 0;
}
