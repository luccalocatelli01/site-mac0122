#include <stdio.h> 

int avaliarPosfixa(char *expr){
    int pilha[100];
    int topo = -1;
    int i = 0;
    while(expr[i] != '\0'){
        if(expr[i] >= '0' && expr[i] <= '9'){
            pilha[++topo] = expr[i] - '0';
        } else {
            int op1, op2;
            op2 = pilha[topo--];
            op1 = pilha[topo--];
            switch(expr[i]){
                case '+':
                    pilha[++topo] = op1 + op2;
                    break;
                case '-':
                    pilha[++topo] = op1 - op2;
                    break;
                case '/':
                    pilha[++topo] = op1 / op2;
                    break;
                case '*':
                    pilha[++topo] = op1 * op2;
                    break;
            }

        }
        i++;
    }

    return pilha[topo];
}

int main(void){
    printf("%d\n", avaliarPosfixa("23+4*"));
    printf("%d\n", avaliarPosfixa("234*+"));
    printf("%d\n", avaliarPosfixa("82-"));
    printf("%d\n", avaliarPosfixa("52-3*"));
    return 0;
}
