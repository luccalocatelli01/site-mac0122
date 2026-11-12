#include <stdio.h>

int contaOcorrencias(int v[], int n, int x){
    if(n == 0){
        return 0;
    }

    if(v[n - 1] == x){
        return 1 + contaOcorrencias(v, n - 1, x);
    }    

    return contaOcorrencias(v, n - 1, x);
}

int maximo(int v[], int n){
    int max_ant;

    if(n == 1){
        return v[0];
    }

    max_ant = maximo(v, n - 1);

    if(v[n - 1] > max_ant){
        return v[n - 1];
    }

    return max_ant;
}

int somaDigitos(int n){
    if(n == 0){
        return 0;
    }

    return (n % 10) + somaDigitos(n / 10);
}

int potencia(int a, int n){
    int h;
    if(n == 0){
        return 1;
    }
    if(n % 2 == 0){
        h = potencia(a, n/2);
        return h * h;

    } 

    return a * potencia(a, n - 1);
    
}

void inverte(int v[], int e, int d){

    int atual;

    if(e >= d){
        return ;
    }

    atual = v[d];
    v[d] = v[e];
    v[e] = atual;

    inverte(v, e + 1, d - 1);
}

int palindromo(char s[], int e, int d){

    if(e >= d){
        return 1;
    }

    if(s[e] != s[d]){
        return 0;
    }

    return palindromo(s, e + 1, d - 1);
}

int main(void)
{
    int v1[] = {1, 2, 1, 2, 1};
    int v2[] = {0, 2, 2, 3, 5, 6, 7, 7, 9};
    int v3[] = {1, 2, 3, 4, 5};
    char s1[] = "arara";
    char s2[] = "arrow";
    int i;

    printf("Ocorrencias de 1: %d\n",
           contaOcorrencias(v1, 5, 1));

    printf("Maximo: %d\n",
           maximo(v2, 9));

    printf("Soma dos digitos de 1234: %d\n",
           somaDigitos(1234));

    printf("2 elevado a 16: %d\n",
           potencia(2, 16));

    printf("3 elevado a 5: %d\n",
           potencia(3, 5));

    inverte(v3, 0, 4);

    printf("Vetor invertido:");

    for (i = 0; i < 5; i++) {
        printf(" %d", v3[i]);
    }

    printf("\n");

    printf("arara e palindromo: %d\n",
           palindromo(s1, 0, 4));

    printf("arrow e palindromo: %d\n",
           palindromo(s2, 0, 4));

    return 0;
}
