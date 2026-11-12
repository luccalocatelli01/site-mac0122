#include <stdio.h>

int soma_rec(int n){
    if(n <= 1){
        return n;
    } 

    return n + soma_rec(n - 1);
}

int fatorial(int n){
    if(n <= 1){
        return 1;
    }

    return n * fatorial(n - 1);
}

int main(void){
    int n;
    scanf("%d", &n);
    printf("%d\n", soma_rec(n));
    printf("%d\n", fatorial(n));

    return 0;
}
