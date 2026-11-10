#include <stdio.h>
#include <string.h>
#include "filtro.h"

int main(int argc, char *argv[]) {
    FILE *entrada;
    int erro;
    int so_trecho;

    if (argc < 2 || argc > 3 ||
        (argc == 3 && strcmp(argv[2], "--trecho") != 0)) {
        fprintf(stderr, "Uso: %s arquivo_de_entrada [--trecho]\n", argv[0]);
        return 1;
    }

    entrada = fopen(argv[1], "r");
    if (entrada == NULL) {
        perror(argv[1]);
        return 1;
    }
    so_trecho = (argc == 3);

    if (!so_trecho) {
        fputs("<!doctype html>\n<html lang=\"pt-BR\">\n<head>\n", stdout);
        fputs("<meta charset=\"utf-8\">\n<title>Teste do filtro</title>\n", stdout);
        fputs("<link rel=\"stylesheet\" href=\"estilo.css\">\n", stdout);
        fputs("</head>\n<body>\n", stdout);
    }

    colorir_codigo(entrada, stdout);

    if (!so_trecho) {
        fputs("\n</body>\n</html>\n", stdout);
    }

    erro = ferror(entrada);
    if (fclose(entrada) == EOF) {
        erro = 1;
    }
    if (fflush(stdout) == EOF || ferror(stdout)) {
        erro = 1;
    }
    if (erro) {
        fputs("Erro durante a leitura ou escrita.\n", stderr);
        return 1;
    }
    return 0;
}
