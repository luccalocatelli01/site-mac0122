/*
 * pagina.h — EP MAC0122, fase 1
 *
 * Tudo o que as partes do gerador compartilham: a struct Pagina e as
 * funções auxiliares de HTML.
 *
 *   gerador.c      leitura dos TXT, índices de Técnica, Autores e Data, main (Camila)
 *   organizacao.c  semanas, início, índices de Algoritmo, Conceitos e Problema
 *   pagina_txt.c   página de cada TXT (Lucca)
 *   html_comum.c   funções auxiliares usadas por todos
 *   filtro.c       código C colorido (Bernardo)
 */
#ifndef PAGINA_H
#define PAGINA_H

#include <stdio.h>

#define NUMERO_DE_ROTULOS 6
#define MAXIMO_DE_VALORES 20      /* valores por rótulo (ex.: 5 conceitos) */
#define TAMANHO_DO_VALOR 512      /* tamanho máximo de cada valor */
#define TAMANHO_DO_CAMINHO 512
#define TAMANHO_DA_LINHA 4096

/* A posição de cada rótulo nos vetores abaixo e na struct. */
typedef enum {
    ROTULO_TECNICA = 0,
    ROTULO_ALGORITMO,
    ROTULO_AUTORES,
    ROTULO_DATA,
    ROTULO_CONCEITOS,
    ROTULO_PROBLEMA
} TipoDeRotulo;

/* Uma página = um arquivo TXT. */
typedef struct {
    char caminho_do_txt[TAMANHO_DO_CAMINHO];  /* ex.: "../txt/fusao.txt" */
    char nome_do_html[TAMANHO_DO_CAMINHO];    /* ex.: "fusao.html" */
    char titulo[TAMANHO_DO_VALOR];            /* nome que aparece nos links */

    /* valores[ROTULO_CONCEITOS][0] = "Ordenação", [1] = "Recursividade"...
       quantidade_de_valores[ROTULO_CONCEITOS] = 2 */
    char valores[NUMERO_DE_ROTULOS][MAXIMO_DE_VALORES][TAMANHO_DO_VALOR];
    int quantidade_de_valores[NUMERO_DE_ROTULOS];

    long posicao_do_corpo;          /* posição (ftell) logo depois da linha "---";
                                       o corpo do texto começa aqui */
    int eh_pagina_de_conceito;      /* 1 se o arquivo se chama conceito_*.txt */
    int eh_pagina_de_exercicios;    /* 1 se o arquivo se chama exercicios_*.txt
                                       (não vira página; aparece em Problema) */

    /* preenchidos a partir do semanas.txt (organizacao.c) */
    int semana;                     /* 0 = não está no semanas.txt */
    int destaque;                   /* 1 = aparece em negrito */
} Pagina;

/* "Tecnica", "Algoritmo"... — como o rótulo aparece no TXT */
extern const char *NOMES_DOS_ROTULOS[NUMERO_DE_ROTULOS];
/* "Técnica", "Algoritmo"... — como o rótulo aparece no site */
extern const char *TITULOS_DOS_ROTULOS[NUMERO_DE_ROTULOS];
/* "tecnica.html", "algoritmo.html"... — página indexadora de cada rótulo */
extern const char *ARQUIVOS_DOS_INDICES[NUMERO_DE_ROTULOS];

/* Pasta onde estão os .c citados nos @codigo (vem da linha de comando). */
extern const char *pasta_dos_codigos;

/* ---------- auxiliares de HTML (html_comum.c) ---------- */

/* Escreve <!DOCTYPE>, <head> com o estilo.css, o menu com os 6 índices e o
   título em <h1>. Depois dela vem o conteúdo da página. */
void escrever_inicio_html(FILE *saida, const char *titulo);
/* Fecha o <main>, o <body> e o <html>. */
void escrever_fim_html(FILE *saida);
/* Escreve um texto trocando &, <, > e " pelos códigos HTML. */
void escrever_texto_html(FILE *saida, const char *texto);
/* Escreve <a href="pagina.html">título</a>, em negrito se for destaque. */
void escrever_link_para_pagina(FILE *saida, const Pagina *pagina);
/* Insere o código colorido de <pasta_dos_codigos>/<nome_do_arquivo>
   (chama o filtro do Bernardo). Se o arquivo não existir, avisa na página. */
void inserir_codigo(FILE *saida, const char *nome_do_arquivo);

/* Compara dois textos ignorando maiúsculas e acentos (UTF-8):
   "Árvore" == "arvore". Devolve <0, 0 ou >0, como o strcmp. */
int comparar_textos_sem_acento(const char *primeiro, const char *segundo);

/* 1 se a página tem `valor` entre os valores do rótulo (sem ligar pra acento). */
int pagina_tem_valor(const Pagina *pagina, int rotulo, const char *valor);

/* Índice da página conceito_*.txt cujo Conceitos é nome_do_conceito,
   ou -1 se não existir. */
int encontrar_pagina_de_conceito(const char *nome_do_conceito,
                                 Pagina todas_as_paginas[], int quantidade_de_paginas);

/* ---------- organização do site (organizacao.c) ---------- */

/* Lê o semanas.txt: título de cada semana, ordem das páginas e destaques. */
void ler_semanas(const char *caminho, Pagina paginas[], int quantidade_de_paginas);
/* index.html: algoritmos e conceitos por semana. */
void gerar_pagina_inicial(const char *pasta, Pagina paginas[], int quantidade_de_paginas);
/* algoritmo.html: algoritmos por semana. */
void gerar_indice_de_algoritmos(const char *pasta, Pagina paginas[], int quantidade_de_paginas);
/* conceitos.html: conceitos por semana, com os algoritmos que usam cada um. */
void gerar_indice_de_conceitos(const char *pasta, Pagina paginas[], int quantidade_de_paginas);
/* problema.html: por conceito, os problemas dos algoritmos e os exercícios extras. */
void gerar_indice_de_problemas(const char *pasta, Pagina paginas[], int quantidade_de_paginas);

/* ---------- página de cada TXT (pagina_txt.c, do Lucca) ---------- */

/* Escreve em `saida` a página HTML inteira de `pagina` (do <!DOCTYPE> ao
   </html>). O corpo do TXT começa em pagina->posicao_do_corpo.
   todas_as_paginas serve para achar as páginas de conceito e fazer os links. */
void gerar_pagina_txt(Pagina *pagina, Pagina todas_as_paginas[],
                      int quantidade_de_paginas, FILE *saida);

#endif
