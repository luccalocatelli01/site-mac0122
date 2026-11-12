#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    double cpf;
    char nome[50];
} Registro;

void inserirRegistro(Registro *reg, int id, double cpf, char *nome){
    reg->id = id;
    reg->cpf = cpf;
    strcpy(reg->nome, nome);
}

int buscaPorIdAux(Registro vet[], int n, int id, int i) {
    if (i == n) {
        return -1;
    }

    if (vet[i].id == id) {
        return i;
    }

    return buscaPorIdAux(vet, n, id, i + 1);
}

int buscaPorId(Registro vet[], int n, int id) {
    return buscaPorIdAux(vet, n, id, 0);
}

int buscaPorNomeAux(Registro vet[], int n, char *nome, int i){
    if(i == n){
        return -1;
    }

    if(strcmp(vet[i].nome, nome) == 0){
        return i;
    }

    return buscaPorNomeAux(vet, n, nome, i + 1);
}

int buscaPorNome(Registro vet[], int n, char *nome){
    return buscaPorNomeAux(vet, n, nome, 0);
}

int main(void)
{
    Registro vet[4];

    inserirRegistro(&vet[0], 2, 0.0, "ana");
    inserirRegistro(&vet[1], 1, 0.0, "bia");
    inserirRegistro(&vet[2], 2, 0.0, "caio");
    inserirRegistro(&vet[3], 1, 0.0, "ana");

    printf("ID 1: %d | esperado: 1\n", buscaPorId(vet, 4, 1));
    printf("ID 9: %d | esperado: -1\n", buscaPorId(vet, 4, 9));
    printf("Nome caio: %d | esperado: 2\n", buscaPorNome(vet, 4, "caio"));
    printf("Nome ze: %d | esperado: -1\n", buscaPorNome(vet, 4, "ze"));

    return 0;
}
