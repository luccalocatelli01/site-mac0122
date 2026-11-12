#include <string.h>
#include "pagina.h"

void gerar_pagina_txt(Pagina *pagina, Pagina todas_as_paginas[],
                      int quantidade_de_paginas, FILE *saida) {
    escrever_inicio_html(saida, pagina->titulo);

    fprintf(saida, "<dl class=\"ficha\">\n");

    for (int rotulo = 0; rotulo < NUMERO_DE_ROTULOS; rotulo++) {
        if (rotulo == ROTULO_ALGORITMO) continue;
        if (pagina->quantidade_de_valores[rotulo] == 0) continue;

        fprintf(saida, "<dt>%s</dt>\n<dd>", TITULOS_DOS_ROTULOS[rotulo]);

        for (int i = 0; i < pagina->quantidade_de_valores[rotulo]; i++) {
            if (i > 0) fprintf(saida, " · ");

            char *valor = pagina->valores[rotulo][i];
            int conceito = -1;

            if (rotulo == ROTULO_CONCEITOS) {
                conceito = encontrar_pagina_de_conceito(valor, todas_as_paginas, quantidade_de_paginas);
            }

            if (conceito != -1 && strcmp(todas_as_paginas[conceito].nome_do_html, pagina->nome_do_html) != 0) {
                fprintf(saida, "<a href=\"%s\">", todas_as_paginas[conceito].nome_do_html);
                escrever_texto_html(saida, valor);
                fprintf(saida, "</a>");
            } else if (rotulo == ROTULO_PROBLEMA) {
                fprintf(saida, "<a href=\"%s\">", ARQUIVOS_DOS_INDICES[ROTULO_PROBLEMA]);
                escrever_texto_html(saida, valor);
                fprintf(saida, "</a>");
            }else {
                escrever_texto_html(saida, valor);
            }
        }

        fprintf(saida, "</dd>\n");
    }

    fprintf(saida, "</dl>\n");

    FILE *txt = fopen(pagina->caminho_do_txt, "r");
    if (txt != NULL) {
        char linha[TAMANHO_DA_LINHA];
        int paragrafo_aberto = 0;
        int lista_aberta = 0;

        fseek(txt, pagina->posicao_do_corpo, SEEK_SET);

        while (fgets(linha, TAMANHO_DA_LINHA, txt) != NULL) {
            linha[strcspn(linha, "\r\n")] = '\0';

            if(linha[0] == '-'){
                char *referencia = linha + 1;
                while (*referencia == ' ') referencia++;

                if (paragrafo_aberto) {
                    fprintf(saida, "</p>\n");
                    paragrafo_aberto = 0;
                }
                if (!lista_aberta) {
                    fprintf(saida, "<ul>\n");
                    lista_aberta = 1;
                }
                fprintf(saida, "<li>");
                escrever_texto_html(saida, referencia);
                fprintf(saida, "</li>\n");
                continue;
            }

            if (lista_aberta) {
                fprintf(saida, "</ul>\n");
                lista_aberta = 0;
            }


            if(strncmp(linha, "@codigo", 7) == 0){
                char *nome = linha + 7;
                while(*nome == ' ') nome++;

                if(paragrafo_aberto){
                    fprintf(saida, "</p>\n");
                    paragrafo_aberto = 0;
                }
                inserir_codigo(saida, nome);
                continue;
            }

            if (linha[0] == '\0') {
                if (paragrafo_aberto) {
                    fprintf(saida, "</p>\n");
                    paragrafo_aberto = 0;
                }
            } else {
                if (paragrafo_aberto) {
                    fprintf(saida, "<br>\n");
                } else {
                    fprintf(saida, "<p>");
                    paragrafo_aberto = 1;
                }
                escrever_texto_html(saida, linha);
            }
        }

        if (paragrafo_aberto) {
            fprintf(saida, "</p>\n");
        }
        
        if (lista_aberta) {
            fprintf(saida, "</ul>\n");
        }

        fclose(txt);
    }

    if (pagina->eh_pagina_de_conceito && pagina->quantidade_de_valores[ROTULO_CONCEITOS] > 0) {
        char *conceito_da_pagina = pagina->valores[ROTULO_CONCEITOS][0];
        int lista_de_algoritmos_aberta = 0;

        for (int i = 0; i < quantidade_de_paginas; i++) {
            Pagina *outra = &todas_as_paginas[i];

            if (outra->eh_pagina_de_conceito || outra->eh_pagina_de_exercicios) continue;
            if (!pagina_tem_valor(outra, ROTULO_CONCEITOS, conceito_da_pagina)) continue;

            if (!lista_de_algoritmos_aberta) {
                fprintf(saida, "<h2>Algoritmos que usam este conceito</h2>\n<ul>\n");
                lista_de_algoritmos_aberta = 1;
            }
            fprintf(saida, "<li>");
            escrever_link_para_pagina(saida, outra);
            fprintf(saida, "</li>\n");
        }

        if (lista_de_algoritmos_aberta) fprintf(saida, "</ul>\n");
    }

    escrever_fim_html(saida);
} 