#include <stdio.h>

void ordena(int v[], int n){
    if(n <= 1){
        return;
    }
    
    int max = 0;
    for(int i = 1; i < n; i ++){
        if(v[i] > v[max]) max = i;
    }
    
    int w = v[n - 1];
    v[n - 1] = v[max];
    v[max] = w;

    ordena(v, n - 1);   
}

void ordenaPorDigito(int v[], int n, int casa){
    int p[n];

    for(int i = 0; i < n; i++){
        p[i] = (v[i] / casa) % 10;
    }

    for(int i = 1; i < n; i++){
        int digito = p[i];
        int numero = v[i];
        int j = i - 1;

        while(j >= 0 && p[j] > digito){
            p[j + 1] = p[j];
            v[j + 1] = v[j];
            j--;
        }

        p[j + 1] = digito;
        v[j + 1] = numero;
    }
}

int main(void){
    int n;
    scanf("%d", &n);

    if(n <= 0){
        return 0;
    }

    int v[n];
    for(int i = 0; i < n; i++){
        scanf("%d", &v[i]);
    }

    int h[n];
    for(int i = 0; i < n; i++){
        h[i] = v[i];
    }

    ordena(h, n);

    int casas = 1;
    while(h[n - 1] / casas >= 10){
        casas = casas * 10;
    }

    for(int casa = 1; casa <= casas; casa = casa * 10){
        ordenaPorDigito(v, n, casa);

        if(casa == casas){
            break;
        }
    }

    for(int i = 0; i < n; i++){
        printf("%d ", v[i]);
    }
    printf("\n");

    return 0;
}
