/* Programa independente que simula o gerador do grupo.
   Compilar: gcc -std=c11 -Wall -Wextra exemplo_integracao.c filtro.c -o exemplo_integracao
   Executar: ./exemplo_integracao teste_filtro.c
   O main_filtro.c NAO participa dessa compilacao. */
#include <stdio.h>
#include "filtro.h"

int main(int argc, char *argv[]) {
    FILE *codigo;
    FILE *pagina;
    int erro;

    if (argc != 2) {
        fprintf(stderr, "Uso: %s arquivo_codigo.c\n", argv[0]);
        return 1;
    }
    codigo = fopen(argv[1], "r");
    if (codigo == NULL) {
        perror(argv[1]);
        return 1;
    }
    pagina = fopen("integracao.html", "w");
    if (pagina == NULL) {
        perror("integracao.html");
        fclose(codigo);
        return 1;
    }

    fputs("<!doctype html>\n<html lang=\"pt-BR\"><head>\n", pagina);
    fputs("<meta charset=\"utf-8\"><title>Teste de integracao</title>\n", pagina);
    fputs("<link rel=\"stylesheet\" href=\"estilo.css\"></head><body>\n", pagina);
    fputs("<h1>Pagina montada por outro programa</h1>\n", pagina);

    colorir_codigo(codigo, pagina);
    erro = ferror(codigo);

    /* Prova que o chamador continua usando a mesma pagina e a mesma entrada. */
    fputs("\n<p>O gerador continua escrevendo depois do filtro.</p>\n", pagina);
    rewind(codigo);
    fputs("<h2>Segunda chamada independente</h2>\n", pagina);
    colorir_codigo(codigo, pagina);
    erro = erro || ferror(codigo);
    fputs("\n<p>Fim da pagina.</p>\n</body></html>\n", pagina);

    if (fclose(codigo) == EOF) {
        erro = 1;
    }
    if (fclose(pagina) == EOF) {
        erro = 1;
    }
    if (erro) {
        fputs("Erro ao ler ou gravar a pagina.\n", stderr);
        return 1;
    }
    puts("Pagina criada: integracao.html");
    return 0;
}
