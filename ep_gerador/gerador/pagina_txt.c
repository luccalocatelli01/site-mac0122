/*
 * pagina_txt.c — PROVISÓRIO
 * O Lucca substitui este arquivo pela versão dele (mesma assinatura do
 * pagina.h). Esta versão já mostra a ficha, o texto em parágrafos e o
 * código colorido, para o site poder ser testado.
 */
#include <string.h>
#include "pagina.h"

void gerar_pagina_txt(Pagina *pagina, Pagina todas_as_paginas[],
                      int quantidade_de_paginas, FILE *saida) {
    escrever_inicio_html(saida, pagina->titulo);

    /* ficha com os rótulos (menos o Algoritmo, que já é o título) */
    fprintf(saida, "<dl class=\"ficha\">\n");
    for (int rotulo = 0; rotulo < NUMERO_DE_ROTULOS; rotulo++) {
        if (rotulo == ROTULO_ALGORITMO || pagina->quantidade_de_valores[rotulo] == 0) continue;
        fprintf(saida, "<dt>%s</dt><dd>", TITULOS_DOS_ROTULOS[rotulo]);
        for (int valor = 0; valor < pagina->quantidade_de_valores[rotulo]; valor++) {
            const char *texto = pagina->valores[rotulo][valor];
            if (valor > 0) fprintf(saida, " · ");
            int conceito = (rotulo == ROTULO_CONCEITOS)
                ? encontrar_pagina_de_conceito(texto, todas_as_paginas, quantidade_de_paginas) : -1;
            if (conceito >= 0 && &todas_as_paginas[conceito] != pagina) {
                fprintf(saida, "<a href=\"%s\">", todas_as_paginas[conceito].nome_do_html);
                escrever_texto_html(saida, texto);
                fprintf(saida, "</a>");
            } else {
                escrever_texto_html(saida, texto);
            }
        }
        fprintf(saida, "</dd>\n");
    }
    fprintf(saida, "</dl>\n");

    /* corpo: parágrafos separados por linha em branco; @codigo vira código */
    FILE *arquivo = fopen(pagina->caminho_do_txt, "r");
    if (arquivo != NULL) {
        char linha[TAMANHO_DA_LINHA];
        int paragrafo_aberto = 0;
        fseek(arquivo, pagina->posicao_do_corpo, SEEK_SET);
        while (fgets(linha, sizeof linha, arquivo) != NULL) {
            linha[strcspn(linha, "\r\n")] = '\0';
            if (linha[0] == '\0' || strncmp(linha, "@codigo", 7) == 0) {
                if (paragrafo_aberto) fprintf(saida, "</p>\n");
                paragrafo_aberto = 0;
                if (linha[0] != '\0') {
                    char *nome = linha + 7;
                    while (*nome == ' ') nome++;
                    inserir_codigo(saida, nome);
                }
                continue;
            }
            fprintf(saida, paragrafo_aberto ? "<br>\n" : "<p>");
            paragrafo_aberto = 1;
            escrever_texto_html(saida, linha);
        }
        if (paragrafo_aberto) fprintf(saida, "</p>\n");
        fclose(arquivo);
    }

    escrever_fim_html(saida);
}
