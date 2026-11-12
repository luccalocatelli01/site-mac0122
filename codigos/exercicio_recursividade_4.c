#include <stdio.h>

int devolve_pos(int x, int k, int n, int v[n]){
    if(k == n){
        return -1;
    }
    if(x == v[k]){
        return k;
    }
    
    return devolve_pos(x, k + 1, n, v);
}

int main(void){
    int x, k = 0, n;
    scanf("%d", &n);
    int v[n];
    for(int i = 0; i < n; i ++){
        scanf("%d", &v[i]);
    }
    scanf("%d", &x);
    if(devolve_pos(x, k, n, v) == -1){
        printf("%d nao encontrado\n", x);
    } else {
    printf("%d encontrado em %d\n", x, devolve_pos(x, k, n, v));
    }
    return 0;
}
