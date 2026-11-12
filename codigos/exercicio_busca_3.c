#include <stdio.h>

int buscabinaria(int v[], int n, int x){
    int e = 0, d = n - 1;
    while(e <= d){
        int m = (e + d) / 2;
        if(v[m] == x){
            return m;
        } else if(v[m] > x){
            d = m - 1;
        } else e = m + 1;
    }
    
    return -1;
}

int main(void){
    int v[7] = {1, 3, 4, 7, 9, 11, 15};

    printf("%d\n", buscabinaria(v, 7, 7));
    printf("%d\n", buscabinaria(v, 7, 1));
    printf("%d\n", buscabinaria(v, 7, 15));
    printf("%d\n", buscabinaria(v, 7, 8));

    return 0;
}
