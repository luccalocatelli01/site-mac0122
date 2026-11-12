#include <stdio.h>

#define n 7

int adj[n][n];
int visitado[n];

void liga(int u, int v){
    adj[u][v] = 1;
    adj[v][u] = 1;
}

void dfs(int v){
    int w; 
    visitado[v] = 1;
    printf("%d ", v);
    for(w = 1; w < n; w ++){
        if(adj[v][w] == 1 && visitado[w] == 0){
            dfs(w);
        }
    }
}

void bfs(int inicio){
    int fila[n];
    int ini = 0, fim = 0;
    int v, w;

    fila[fim++] = inicio;
    visitado[inicio] = 1;

    while(ini < fim){
        v = fila[ini++];
        printf("%d ", v);
        for(w = 1; w < n; w ++){
            if(adj[v][w] == 1 && visitado[w] == 0){
                fila[fim++] = w;
                visitado[w] = 1;                
            }
        }
    }
}

int main(void){
    int i;

    liga(1, 2);
    liga(1, 3);
    liga(1, 4);
    liga(2, 5);
    liga(4, 6);

    for(i = 0; i < n; i++) visitado[i] = 0;
    dfs(1);
    printf("\n");

    for(i = 0; i < n; i++) visitado[i] = 0;
    bfs(1);
    printf("\n");

    return 0;
}
