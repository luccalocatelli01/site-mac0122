#include <stdio.h>

typedef struct {
    int codigo;
    int estoque;
} Produto;

int vender(Produto *p, int quantidade){
    if(quantidade > 0 && quantidade <= p->estoque){
        p->estoque = (p->estoque) - quantidade;
        return 1;
    } else {
        return 0;
    }
}

int main(void){

    Produto bola;
    Produto *p;
    p = &bola;

    scanf("%d %d", &(p->codigo), &(p->estoque));

    int v1, v2, v3;
    scanf("%d %d %d", &v1, &v2, &v3);

    
    int x = vender(p, v1);
    int y = vender(p, v2);
    int z = vender(p, v3);
    printf("%d %d %d\n", x, y, z);

    printf("%d %d\n", bola.codigo, p->estoque);


return 0;
}
