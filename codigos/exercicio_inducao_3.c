#include <stdio.h>

unsigned long contador;

void hanoi(int n, int a, int c, int b){
    
    if(n == 0){
        return;
    }

    hanoi(n - 1, a, b, c);


    contador ++;
    printf("%d --> %d\n", a, c);

    hanoi(n - 1, b, c, a);
}

int main(){

    contador = 0;
    hanoi(3, 1, 3, 2);
    printf("Movimentos: %lu\n", contador);
    return 0;
}
