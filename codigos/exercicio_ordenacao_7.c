#include <stdio.h>

void countingSort(int v[], int n, int k){
    int count[k];
    int aux[n];
    int i, j;

    for(j = 0; j < k; j ++){
        count[j] = 0;
    }

    for(i = 0; i < n; i ++){
        count[v[i]] ++;
    }

    for(j = 1; j < k; j ++){
        count[j] += count[j - 1];
    }

    for(i = n - 1; i >= 0; i --){
        count[v[i]]--;
        aux[count[v[i]]] = v[i];
    }

    for(i = 0; i < n; i ++){
        v[i] = aux[i];
    }
}

int main(void){
    int v[5] = {3, 1, 3, 0, 2};
    countingSort(v, 5, 4);
    for(int i = 0; i < 5; i ++){
        printf("%d ", v[i]);
    }
    printf("\n");
    return 0;
}
