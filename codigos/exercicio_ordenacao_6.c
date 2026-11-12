#include <stdio.h>

void ajustaHeap(int v[], int n, int i){
    if(i * 2 + 1 >= n){
        return;
    } 
    if(i * 2 + 1 == n - 1){
        if(v[i] < v[2 * i + 1]){
            int w = v[i];
            v[i] = v[2*i + 1];
            v[2 * i + 1] = w;  
        }
        return;
    }

    if(v[i] < v[2*i + 1] || v[i] < v[2*i + 2]){
        if(v[2*i + 1] >= v[2*i + 2]){
            int w = v[i];
            v[i] = v[2*i + 1];
            v[2 * i + 1] = w;  
            ajustaHeap(v, n, 2*i + 1);
        } else {
            int w = v[i];
            v[i] = v[2*i + 2];
            v[2 * i + 2] = w;
            ajustaHeap(v, n, 2*i + 2);
        }
    }
}

void heapSort(int v[], int n){
    if(n <= 0){
        return;
    }

    for(int i = n / 2 - 1; i >= 0; i--){
        ajustaHeap(v, n, i);
    }

    int fim = n - 1;
    while(fim > 0){
        int w = v[0];
        v[0] = v[fim];
        v[fim] = w;
        ajustaHeap(v, fim, 0);
        fim --;
    }
}

int main(void){
    int v[7] = {2, 7, 8, 4, 3, 6, 5};
    ajustaHeap(v, 7, 0);
    for(int i = 0; i < 7; i ++){
        printf("%d ", v[i]);
    }
    printf("\n");
    int p[8] = {7, 5, 3, 6, 3, 9, 8, 4};
    heapSort(p, 8);
    for(int i = 0; i < 8; i ++){
        printf("%d ", p[i]);
    }
    printf("\n");
    return 0;
}
