#include <stdio.h>

void trocaErrado(int *p, int *novo){
    p = novo;
    printf("%d\n", *p);
}

void trocaCerto(int **pp, int *novo){
    *pp = novo;
}

int main(void){
    int a = 1;
    int b = 2;
    int *p = &a;

    trocaErrado(p, &b);
    printf("%d\n", *p);

    trocaCerto(&p, &b);
    printf("%d\n", *p);

    return 0;
}
