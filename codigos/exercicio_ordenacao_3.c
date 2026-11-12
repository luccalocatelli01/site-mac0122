#include <stdio.h>

void troca(int *a, int *b){
    int w;
    w = *a;
    *a = *b;
    *b = w;
}

void imprime(int v[], int n){
    for(int i = 0; i < n; i ++){
        printf("%d ", v[i]);
    }

    printf("\n");
}

void ordenaViaSelecaoDireta(int v[], int n){
    int trocas = 0;
    int comparacoes = 0;
    for(int i = 0; i < n; i ++){
        int min = i;
        for(int j = i + 1; j < n; j ++){
            comparacoes ++;
            if(v[min] > v[j]){
                min = j;
            }
        }
        if(min != i){
            troca(&v[min], &v[i]);
            trocas ++;
        }
    }

    imprime(v, n);

    printf("Selecao: %d comparacoes, %d trocas\n", comparacoes, trocas);
}

void ordenaBolha(int v[], int n){
    int comparacoes = 0;
    int trocas = 0;
    for(int fim = n - 1; fim > 0; fim--){
        int trocou = 0;
        for(int j = 0; j < fim; j ++){
            comparacoes ++;
            if(v[j] > v[j + 1]){
                troca(&v[j], &v[j + 1]);
                trocas ++;
                trocou = 1;
            }
        }
        if(!trocou) break;
    }

    imprime(v, n);

    printf("Bolha: %d comparacoes, %d trocas\n", comparacoes, trocas);
}

void ordenaViaInsercaoDireta(int v[], int n){
    int atual;
    int comparacoes = 0;
    int deslocamentos = 0;
    for(int i = 1; i < n; i ++){
        atual = v[i];
        int j = i - 1;
        while(j >= 0){
            comparacoes ++;
            if(v[j] <= atual) break;
            v[j + 1] = v[j];
            deslocamentos ++;
            j --;
        }
        v[j + 1] = atual;
    }

    imprime(v, n);

    printf("Insercao: %d comparacoes, %d deslocamentos\n", comparacoes, deslocamentos);
}

int main(void){
    int v[8] = {7, 5, 3, 6, 3, 9, 8, 4};
    ordenaViaSelecaoDireta(v, 8);
    int b[8] = {7, 5, 3, 6, 3, 9, 8, 4};
    ordenaBolha(b, 8);
    int c[8] = {7, 5, 3, 6, 3, 9, 8, 4};
    ordenaViaInsercaoDireta(c, 8);
    return 0;
}
