/*
 * html_comum.c — EP MAC0122, fase 1
 * Funções auxiliares usadas pelo gerador, pela organização e pela página de
 * cada TXT.
 */
#include <ctype.h>
#include <string.h>
#include "pagina.h"
#include "filtro.h"

const char *NOMES_DOS_ROTULOS[NUMERO_DE_ROTULOS] = {
    "Tecnica", "Algoritmo", "Autores", "Data", "Conceitos", "Problema"
};

const char *TITULOS_DOS_ROTULOS[NUMERO_DE_ROTULOS] = {
    "Técnica", "Algoritmos", "Autores", "Data", "Conceitos", "Problema"
};

const char *ARQUIVOS_DOS_INDICES[NUMERO_DE_ROTULOS] = {
    "tecnica.html", "algoritmo.html", "autores.html",
    "data.html", "conceitos.html", "problema.html"
};

const char *pasta_dos_codigos = "../codigos";

/* <!DOCTYPE> e <head>, iguais em todas as páginas */
static void escrever_cabeca(FILE *saida, const char *titulo) {
    fprintf(saida, "<!DOCTYPE html>\n<html lang=\"pt-BR\">\n<head>\n");
    fprintf(saida, "<meta charset=\"UTF-8\">\n");
    fprintf(saida, "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n");
    fprintf(saida, "<title>");
    escrever_texto_html(saida, titulo);
    fprintf(saida, " - MAC0122</title>\n");
    fprintf(saida, "<link rel=\"stylesheet\" href=\"estilo.css\">\n</head>\n<body>\n");
}

/* Os 6 botões dos índices; o da página atual fica marcado. */
static void escrever_botoes(FILE *saida, const char *classe, const char *titulo_da_pagina) {
    fprintf(saida, "<nav class=\"%s\">\n", classe);
    for (int rotulo = 0; rotulo < NUMERO_DE_ROTULOS; rotulo++) {
        int atual = titulo_da_pagina != NULL && strcmp(titulo_da_pagina, TITULOS_DOS_ROTULOS[rotulo]) == 0;
        fprintf(saida, "<a href=\"%s\"%s>%s</a>\n", ARQUIVOS_DOS_INDICES[rotulo],
                atual ? " aria-current=\"page\"" : "", TITULOS_DOS_ROTULOS[rotulo]);
    }
    fprintf(saida, "</nav>\n");
}

void escrever_inicio_html(FILE *saida, const char *titulo) {
    escrever_cabeca(saida, titulo);
    fprintf(saida, "<header class=\"topo\">\n");
    fprintf(saida, "<a class=\"marca\" href=\"index.html\"><span>Página-guia de</span> MAC0122</a>\n");
    escrever_botoes(saida, "menu", titulo);
    fprintf(saida, "</header>\n<main>\n<h1>");
    escrever_texto_html(saida, titulo);
    fprintf(saida, "</h1>\n");
}

void escrever_inicio_html_da_capa(FILE *saida) {
    escrever_cabeca(saida, "Página-guia");
    fprintf(saida, "<header class=\"capa\">\n");
    fprintf(saida, "<p class=\"capa-chamada\">Página-guia de</p>\n");
    fprintf(saida, "<h1 class=\"capa-titulo\">MAC0122</h1>\n");
    fprintf(saida, "<div class=\"capa-faixa\">\n");
    fprintf(saida, "<img class=\"capa-computador\" src=\"imagens/computador.png\" alt=\"\">\n");
    fprintf(saida, "<img class=\"capa-grafo\" src=\"imagens/grafo.png\" alt=\"\">\n");
    fprintf(saida, "</div>\n");
    escrever_botoes(saida, "botoes", NULL);
    fprintf(saida, "</header>\n<main>\n");
}

void escrever_fim_html(FILE *saida) {
    fprintf(saida, "</main>\n</body>\n</html>\n");
}

void escrever_texto_html(FILE *saida, const char *texto) {
    for (const char *caractere = texto; *caractere != '\0'; caractere++) {
        switch (*caractere) {
            case '&': fputs("&amp;", saida); break;
            case '<': fputs("&lt;", saida); break;
            case '>': fputs("&gt;", saida); break;
            case '"': fputs("&quot;", saida); break;
            default:  fputc(*caractere, saida);
        }
    }
}

void escrever_link_para_pagina(FILE *saida, const Pagina *pagina) {
    fprintf(saida, "<a href=\"%s\">", pagina->nome_do_html);
    if (pagina->destaque) fprintf(saida, "<strong>");
    escrever_texto_html(saida, pagina->titulo);
    if (pagina->destaque) fprintf(saida, "</strong>");
    fprintf(saida, "</a>");
}

void inserir_codigo(FILE *saida, const char *nome_do_arquivo) {
    char caminho[2 * TAMANHO_DO_CAMINHO];
    snprintf(caminho, sizeof caminho, "%s/%s", pasta_dos_codigos, nome_do_arquivo);
    FILE *codigo = fopen(caminho, "r");
    if (codigo == NULL) {
        fprintf(stderr, "aviso: código %s não encontrado\n", caminho);
        fprintf(saida, "<p class=\"aviso\">Código <code>");
        escrever_texto_html(saida, nome_do_arquivo);
        fprintf(saida, "</code> ainda não disponível.</p>\n");
        return;
    }
    fprintf(saida, "<p class=\"nome-do-codigo\"><code>");
    escrever_texto_html(saida, nome_do_arquivo);
    fprintf(saida, "</code></p>\n");
    colorir_codigo(codigo, saida);
    fprintf(saida, "\n");
    fclose(codigo);
}

/*
 * Em UTF-8, as letras acentuadas do português ocupam 2 bytes: o primeiro é
 * sempre 0xC3 e o segundo diz qual letra é (0xA1 = á, 0xA7 = ç, 0x81 = Á...).
 * Esta função lê UMA letra a partir de *cursor, devolve a letra sem acento e
 * em minúscula, e avança o cursor 1 ou 2 bytes.
 */
static int proximo_caractere_sem_acento(const char **cursor) {
    const unsigned char *atual = (const unsigned char *) *cursor;

    if (atual[0] == 0xC3 && atual[1] != '\0') {
        /* maiúsculas acentuadas vão de 0x80 a 0x9F e as minúsculas de 0xA0 a
           0xBF: ligar o bit 0x20 transforma maiúscula em minúscula */
        unsigned char segundo_byte = atual[1] | 0x20;
        *cursor += 2;
        if (segundo_byte >= 0xA0 && segundo_byte <= 0xA5) return 'a';
        if (segundo_byte == 0xA7) return 'c';
        if (segundo_byte >= 0xA8 && segundo_byte <= 0xAB) return 'e';
        if (segundo_byte >= 0xAC && segundo_byte <= 0xAF) return 'i';
        if (segundo_byte == 0xB1) return 'n';
        if (segundo_byte >= 0xB2 && segundo_byte <= 0xB6) return 'o';
        if (segundo_byte >= 0xB9 && segundo_byte <= 0xBC) return 'u';
        return 0x100 + segundo_byte;   /* outro símbolo: vai pro fim da ordem */
    }

    *cursor += 1;
    return tolower(atual[0]);
}

int comparar_textos_sem_acento(const char *primeiro, const char *segundo) {
    while (*primeiro != '\0' || *segundo != '\0') {
        int letra_do_primeiro = (*primeiro != '\0') ? proximo_caractere_sem_acento(&primeiro) : 0;
        int letra_do_segundo = (*segundo != '\0') ? proximo_caractere_sem_acento(&segundo) : 0;
        if (letra_do_primeiro != letra_do_segundo) {
            return letra_do_primeiro - letra_do_segundo;
        }
    }
    return 0;
}

int pagina_tem_valor(const Pagina *pagina, int rotulo, const char *valor) {
    for (int indice = 0; indice < pagina->quantidade_de_valores[rotulo]; indice++) {
        if (comparar_textos_sem_acento(pagina->valores[rotulo][indice], valor) == 0) {
            return 1;
        }
    }
    return 0;
}

int encontrar_pagina_de_conceito(const char *nome_do_conceito,
                                 Pagina todas_as_paginas[], int quantidade_de_paginas) {
    for (int indice = 0; indice < quantidade_de_paginas; indice++) {
        Pagina *candidata = &todas_as_paginas[indice];
        if (candidata->eh_pagina_de_conceito
            && candidata->quantidade_de_valores[ROTULO_CONCEITOS] > 0
            && comparar_textos_sem_acento(candidata->valores[ROTULO_CONCEITOS][0],
                                          nome_do_conceito) == 0) {
            return indice;
        }
    }
    return -1;
}
