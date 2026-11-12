#include <stdio.h>

void fusao(int v[], int esq, int med, int dir){
    int i = esq, j = med + 1;
    int w[dir - esq + 1];
    int n = 0;
    while(i <= med && j <= dir){
        if(v[i] <= v[j]){
            w[n] = v[i];
            i ++;
        } else {
            w[n] = v[j];
            j ++;
        }
        n ++;
    }

    while (i <= med) {
        w[n] = v[i];
        i++;
        n++;
    }

    while (j <= dir) {
        w[n] = v[j];
        j++;
        n++;
    }

    for(int k = 0; k < n; k ++){
        v[esq + k] = w[k];
    }
}

void ordena_por_fusao(int v[], int esq, int dir){
    if(esq >= dir){
        return;
    }

    int med = (esq + dir) / 2;

    ordena_por_fusao(v, esq, med);
    ordena_por_fusao(v, med + 1, dir);
    fusao(v, esq, med, dir);
}

int main(){
    int v[8] = {7, 5, 3, 6, 3, 9, 8, 4};
    ordena_por_fusao(v, 0, 7);
    for(int i = 0; i < 8; i ++){
        printf("%d ", v[i]);
    }
    printf("\n");
    return 0;
}
