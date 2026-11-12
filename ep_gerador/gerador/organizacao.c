/*
 * organizacao.c — EP MAC0122, fase 1
 *
 * Organização do site pelas semanas do curso:
 *   - lê o semanas.txt (título de cada semana, ordem das páginas, destaques)
 *   - index.html, algoritmo.html e conceitos.html organizados por semana
 *   - problema.html organizado por conceito, com os exercícios extras
 */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pagina.h"

#define MAXIMO_DE_SEMANAS 30
#define MAXIMO_DE_ITENS 300

typedef struct {
    int numero;                          /* "Semana 3" -> 3 */
    char titulo[TAMANHO_DO_VALOR];       /* "Grafos, árvores, complexidade e busca" */
} Semana;

/* Um item = uma linha de página do semanas.txt, na ordem do arquivo. */
typedef struct {
    int indice_da_semana;                /* posição em semanas[] */
    int indice_da_pagina;                /* posição em paginas[] */
} Item;

static Semana semanas[MAXIMO_DE_SEMANAS];
static int quantidade_de_semanas = 0;
static Item itens[MAXIMO_DE_ITENS];
static int quantidade_de_itens = 0;

/* ============================ semanas.txt ============================ */

static void tirar_espacos(char *texto) {
    int tamanho = strlen(texto);
    while (tamanho > 0 && isspace((unsigned char) texto[tamanho - 1])) {
        texto[--tamanho] = '\0';
    }
    int inicio = 0;
    while (isspace((unsigned char) texto[inicio])) inicio++;
    if (inicio > 0) memmove(texto, texto + inicio, tamanho - inicio + 1);
}

/* "fusao" -> índice da página fusao.html, ou -1 */
static int encontrar_pagina_pelo_nome(const char *nome, Pagina paginas[], int quantidade_de_paginas) {
    char nome_do_html[TAMANHO_DO_CAMINHO];
    snprintf(nome_do_html, sizeof nome_do_html, "%s.html", nome);
    for (int indice = 0; indice < quantidade_de_paginas; indice++) {
        if (strcmp(paginas[indice].nome_do_html, nome_do_html) == 0) return indice;
    }
    return -1;
}

void ler_semanas(const char *caminho, Pagina paginas[], int quantidade_de_paginas) {
    FILE *arquivo = fopen(caminho, "r");
    if (arquivo == NULL) {
        fprintf(stderr, "aviso: %s não encontrado; tudo vai para \"Outras páginas\"\n", caminho);
        return;
    }

    char linha[TAMANHO_DA_LINHA];
    int paginas_que_faltam = 0;
    while (fgets(linha, sizeof linha, arquivo) != NULL) {
        tirar_espacos(linha);
        if (linha[0] == '\0' || linha[0] == '#') continue;   /* vazia ou comentário */

        /* "Semana 3: título" abre uma semana nova */
        if (strncmp(linha, "Semana", 6) == 0 && strchr(linha, ':') != NULL) {
            if (quantidade_de_semanas == MAXIMO_DE_SEMANAS) continue;
            Semana *semana = &semanas[quantidade_de_semanas];
            semana->numero = atoi(linha + 6);
            char *titulo = strchr(linha, ':') + 1;
            tirar_espacos(titulo);
            strncpy(semana->titulo, titulo, TAMANHO_DO_VALOR - 1);
            quantidade_de_semanas++;
            continue;
        }

        /* qualquer outra linha é o nome de uma página; "*" na frente = destaque */
        if (quantidade_de_semanas == 0) {
            fprintf(stderr, "aviso: semanas.txt: \"%s\" antes da primeira semana\n", linha);
            continue;
        }
        int destaque = (linha[0] == '*');
        char *nome = destaque ? linha + 1 : linha;
        tirar_espacos(nome);

        int indice_da_pagina = encontrar_pagina_pelo_nome(nome, paginas, quantidade_de_paginas);
        if (indice_da_pagina < 0) {
            paginas_que_faltam++;   /* TXT ainda não escrito: só não aparece */
            continue;
        }
        if (quantidade_de_itens == MAXIMO_DE_ITENS) continue;

        Pagina *pagina = &paginas[indice_da_pagina];
        pagina->semana = semanas[quantidade_de_semanas - 1].numero;
        pagina->destaque = destaque;
        itens[quantidade_de_itens].indice_da_semana = quantidade_de_semanas - 1;
        itens[quantidade_de_itens].indice_da_pagina = indice_da_pagina;
        quantidade_de_itens++;
    }
    fclose(arquivo);
    if (paginas_que_faltam > 0) {
        fprintf(stderr, "aviso: %d páginas do semanas.txt ainda não têm TXT\n", paginas_que_faltam);
    }
}

/* =========================== auxiliares =========================== */

static FILE *abrir_saida(const char *pasta, const char *nome) {
    char caminho[2 * TAMANHO_DO_CAMINHO];
    snprintf(caminho, sizeof caminho, "%s/%s", pasta, nome);
    FILE *arquivo = fopen(caminho, "w");
    if (arquivo == NULL) fprintf(stderr, "erro: não consegui criar %s\n", caminho);
    return arquivo;
}

static int eh_algoritmo(const Pagina *pagina) {
    return !pagina->eh_pagina_de_conceito && !pagina->eh_pagina_de_exercicios;
}

/* 1 se a semana tem pelo menos uma página do tipo pedido */
static int semana_tem(int indice_da_semana, Pagina paginas[], int quer_conceitos) {
    for (int item = 0; item < quantidade_de_itens; item++) {
        if (itens[item].indice_da_semana != indice_da_semana) continue;
        Pagina *pagina = &paginas[itens[item].indice_da_pagina];
        if (quer_conceitos ? pagina->eh_pagina_de_conceito : eh_algoritmo(pagina)) return 1;
    }
    return 0;
}

static void escrever_titulo_da_semana(FILE *saida, int indice_da_semana) {
    fprintf(saida, "<h2 id=\"semana-%d\">Semana %d · ",
            semanas[indice_da_semana].numero, semanas[indice_da_semana].numero);
    escrever_texto_html(saida, semanas[indice_da_semana].titulo);
    fprintf(saida, "</h2>\n");
}

/* <ul> com as páginas da semana, do tipo pedido, na ordem do semanas.txt */
static void escrever_lista_da_semana(FILE *saida, int indice_da_semana, Pagina paginas[],
                                     int quer_conceitos, int quantidade_de_paginas,
                                     int mostrar_quem_usa) {
    fprintf(saida, "<ul class=\"lista-da-semana\">\n");
    for (int item = 0; item < quantidade_de_itens; item++) {
        if (itens[item].indice_da_semana != indice_da_semana) continue;
        Pagina *pagina = &paginas[itens[item].indice_da_pagina];
        if (quer_conceitos ? !pagina->eh_pagina_de_conceito : !eh_algoritmo(pagina)) continue;

        fprintf(saida, "<li>");
        escrever_link_para_pagina(saida, pagina);

        /* nos conceitos: quais algoritmos usam aquele conceito */
        if (mostrar_quem_usa && pagina->quantidade_de_valores[ROTULO_CONCEITOS] > 0) {
            const char *conceito = pagina->valores[ROTULO_CONCEITOS][0];
            int primeiro = 1;
            for (int outra = 0; outra < quantidade_de_paginas; outra++) {
                if (!eh_algoritmo(&paginas[outra])) continue;
                if (!pagina_tem_valor(&paginas[outra], ROTULO_CONCEITOS, conceito)) continue;
                fprintf(saida, primeiro ? "<span class=\"usado-em\">usado em: " : " · ");
                escrever_link_para_pagina(saida, &paginas[outra]);
                primeiro = 0;
            }
            if (!primeiro) fprintf(saida, "</span>");
        }
        fprintf(saida, "</li>\n");
    }
    fprintf(saida, "</ul>\n");
}

/* páginas do tipo pedido que não estão no semanas.txt */
static void escrever_outras(FILE *saida, Pagina paginas[], int quantidade_de_paginas,
                            int quer_conceitos) {
    int primeira = 1;
    for (int indice = 0; indice < quantidade_de_paginas; indice++) {
        Pagina *pagina = &paginas[indice];
        if (pagina->semana != 0) continue;
        if (quer_conceitos ? !pagina->eh_pagina_de_conceito : !eh_algoritmo(pagina)) continue;
        if (primeira) {
            fprintf(saida, "<h2>Outras páginas</h2>\n<ul class=\"lista-da-semana\">\n");
            primeira = 0;
        }
        fprintf(saida, "<li>");
        escrever_link_para_pagina(saida, pagina);
        fprintf(saida, "</li>\n");
    }
    if (!primeira) fprintf(saida, "</ul>\n");
}

/* ============================ index.html ============================ */

void gerar_pagina_inicial(const char *pasta, Pagina paginas[], int quantidade_de_paginas) {
    FILE *saida = abrir_saida(pasta, "index.html");
    if (saida == NULL) return;
    escrever_inicio_html(saida, "MAC0122 · Princípios de Desenvolvimento de Algoritmos");

    fprintf(saida, "<p class=\"apresentacao\">Conteúdo da Avaliação 1, organizado pelas "
                   "semanas do curso. Os destaques em negrito são os assuntos que caíram na "
                   "prova. Pelo menu, dá pra procurar os mesmos algoritmos por técnica, autor, "
                   "data, conceito ou problema.</p>\n");

    for (int semana = 0; semana < quantidade_de_semanas; semana++) {
        int tem_algoritmos = semana_tem(semana, paginas, 0);
        int tem_conceitos = semana_tem(semana, paginas, 1);
        if (!tem_algoritmos && !tem_conceitos) continue;

        fprintf(saida, "<section class=\"semana\">\n");
        escrever_titulo_da_semana(saida, semana);
        if (tem_algoritmos) {
            fprintf(saida, "<h3>Algoritmos</h3>\n");
            escrever_lista_da_semana(saida, semana, paginas, 0, quantidade_de_paginas, 0);
        }
        if (tem_conceitos) {
            fprintf(saida, "<h3>Conceitos</h3>\n");
            escrever_lista_da_semana(saida, semana, paginas, 1, quantidade_de_paginas, 0);
        }
        fprintf(saida, "</section>\n");
    }
    escrever_outras(saida, paginas, quantidade_de_paginas, 0);

    escrever_fim_html(saida);
    fclose(saida);
}

/* ========================= algoritmo.html ========================= */

void gerar_indice_de_algoritmos(const char *pasta, Pagina paginas[], int quantidade_de_paginas) {
    FILE *saida = abrir_saida(pasta, ARQUIVOS_DOS_INDICES[ROTULO_ALGORITMO]);
    if (saida == NULL) return;
    escrever_inicio_html(saida, TITULOS_DOS_ROTULOS[ROTULO_ALGORITMO]);

    for (int semana = 0; semana < quantidade_de_semanas; semana++) {
        if (!semana_tem(semana, paginas, 0)) continue;
        fprintf(saida, "<section class=\"semana\">\n");
        escrever_titulo_da_semana(saida, semana);
        escrever_lista_da_semana(saida, semana, paginas, 0, quantidade_de_paginas, 0);
        fprintf(saida, "</section>\n");
    }
    escrever_outras(saida, paginas, quantidade_de_paginas, 0);

    escrever_fim_html(saida);
    fclose(saida);
}

/* ========================= conceitos.html ========================= */

void gerar_indice_de_conceitos(const char *pasta, Pagina paginas[], int quantidade_de_paginas) {
    FILE *saida = abrir_saida(pasta, ARQUIVOS_DOS_INDICES[ROTULO_CONCEITOS]);
    if (saida == NULL) return;
    escrever_inicio_html(saida, TITULOS_DOS_ROTULOS[ROTULO_CONCEITOS]);

    for (int semana = 0; semana < quantidade_de_semanas; semana++) {
        if (!semana_tem(semana, paginas, 1)) continue;
        fprintf(saida, "<section class=\"semana\">\n");
        escrever_titulo_da_semana(saida, semana);
        escrever_lista_da_semana(saida, semana, paginas, 1, quantidade_de_paginas, 1);
        fprintf(saida, "</section>\n");
    }
    escrever_outras(saida, paginas, quantidade_de_paginas, 1);

    escrever_fim_html(saida);
    fclose(saida);
}

/* ========================== problema.html ========================== */

/*
 * Exercícios extras: o corpo do exercicios_<conceito>.txt tem blocos assim
 *
 *   @exercicio
 *   Fonte: FEOFILOFF, P. ... (adaptado).
 *   Enunciado, em um ou mais parágrafos (linha em branco separa).
 *   @resolucao
 *   Resolução, em parágrafos.
 *   @pre            <- trecho mostrado exatamente como está (tabela, rastreio)
 *   ...
 *   @fimpre
 *   @codigo exercicio_busca_1.c
 *   @fim
 */
static void escrever_exercicios(FILE *saida, Pagina *pagina_de_exercicios) {
    FILE *arquivo = fopen(pagina_de_exercicios->caminho_do_txt, "r");
    if (arquivo == NULL) return;
    fseek(arquivo, pagina_de_exercicios->posicao_do_corpo, SEEK_SET);

    int numero_do_exercicio = 0;
    int dentro_do_exercicio = 0, dentro_da_resolucao = 0;
    int dentro_do_pre = 0, paragrafo_aberto = 0;
    char linha[TAMANHO_DA_LINHA];

    fprintf(saida, "<h3>Exercícios extras de livros</h3>\n");
    while (fgets(linha, sizeof linha, arquivo) != NULL) {
        if (dentro_do_pre) {
            if (strncmp(linha, "@fimpre", 7) == 0) {
                fprintf(saida, "</pre>\n");
                dentro_do_pre = 0;
            } else {
                escrever_texto_html(saida, linha);
            }
            continue;
        }

        tirar_espacos(linha);
        int eh_comando = (linha[0] == '@');
        if ((eh_comando || linha[0] == '\0') && paragrafo_aberto) {
            fprintf(saida, "</p>\n");
            paragrafo_aberto = 0;
        }

        if (strcmp(linha, "@exercicio") == 0) {
            numero_do_exercicio++;
            fprintf(saida, "<div class=\"exercicio\">\n<h4>Exercício %d</h4>\n", numero_do_exercicio);
            dentro_do_exercicio = 1;
        } else if (strcmp(linha, "@resolucao") == 0) {
            fprintf(saida, "<details class=\"resolucao\">\n<summary>Ver resolução</summary>\n");
            dentro_da_resolucao = 1;
        } else if (strcmp(linha, "@pre") == 0) {
            fprintf(saida, "<pre class=\"rastreio\">");
            dentro_do_pre = 1;
        } else if (strncmp(linha, "@codigo", 7) == 0) {
            char *nome = linha + 7;
            tirar_espacos(nome);
            inserir_codigo(saida, nome);
        } else if (strcmp(linha, "@fim") == 0) {
            if (dentro_da_resolucao) fprintf(saida, "</details>\n");
            if (dentro_do_exercicio) fprintf(saida, "</div>\n");
            dentro_do_exercicio = dentro_da_resolucao = 0;
        } else if (strncmp(linha, "Fonte:", 6) == 0 && dentro_do_exercicio) {
            /* a linha da fonte é um parágrafo só dela, com estilo próprio */
            if (paragrafo_aberto) fprintf(saida, "</p>\n");
            fprintf(saida, "<p class=\"fonte\">");
            escrever_texto_html(saida, linha);
            fprintf(saida, "</p>\n");
            paragrafo_aberto = 0;
        } else if (linha[0] != '\0' && dentro_do_exercicio) {
            if (!paragrafo_aberto) {
                fprintf(saida, "<p>");
                paragrafo_aberto = 1;
            } else {
                fprintf(saida, " ");
            }
            escrever_texto_html(saida, linha);
        }
    }
    if (paragrafo_aberto) fprintf(saida, "</p>\n");
    if (dentro_do_pre) fprintf(saida, "</pre>\n");
    if (dentro_da_resolucao) fprintf(saida, "</details>\n");
    if (dentro_do_exercicio) fprintf(saida, "</div>\n");
    fclose(arquivo);
}

/* Problemas dos algoritmos que usam o conceito; frases iguais viram um item só. */
static int escrever_problemas_do_conceito(FILE *saida, const char *conceito,
                                          Pagina paginas[], int quantidade_de_paginas) {
    int escreveu = 0;
    for (int indice = 0; indice < quantidade_de_paginas; indice++) {
        Pagina *pagina = &paginas[indice];
        if (!eh_algoritmo(pagina)) continue;
        if (!pagina_tem_valor(pagina, ROTULO_CONCEITOS, conceito)) continue;
        if (pagina->quantidade_de_valores[ROTULO_PROBLEMA] == 0) continue;
        const char *problema = pagina->valores[ROTULO_PROBLEMA][0];

        /* essa frase já foi escrita por uma página anterior? */
        int repetida = 0;
        for (int anterior = 0; anterior < indice && !repetida; anterior++) {
            Pagina *outra = &paginas[anterior];
            repetida = eh_algoritmo(outra)
                && pagina_tem_valor(outra, ROTULO_CONCEITOS, conceito)
                && outra->quantidade_de_valores[ROTULO_PROBLEMA] > 0
                && comparar_textos_sem_acento(outra->valores[ROTULO_PROBLEMA][0], problema) == 0;
        }
        if (repetida) continue;

        if (!escreveu) fprintf(saida, "<h3>Problemas</h3>\n<ul class=\"problemas\">\n");
        escreveu = 1;
        fprintf(saida, "<li><span class=\"problema\">");
        escrever_texto_html(saida, problema);
        fprintf(saida, "</span><span class=\"resolvido-por\">resolvido por: ");
        int primeiro = 1;
        for (int outra = indice; outra < quantidade_de_paginas; outra++) {
            Pagina *candidata = &paginas[outra];
            if (!eh_algoritmo(candidata)) continue;
            if (!pagina_tem_valor(candidata, ROTULO_CONCEITOS, conceito)) continue;
            if (candidata->quantidade_de_valores[ROTULO_PROBLEMA] == 0) continue;
            if (comparar_textos_sem_acento(candidata->valores[ROTULO_PROBLEMA][0], problema) != 0) continue;
            if (!primeiro) fprintf(saida, " · ");
            escrever_link_para_pagina(saida, candidata);
            primeiro = 0;
        }
        fprintf(saida, "</span></li>\n");
    }
    if (escreveu) fprintf(saida, "</ul>\n");
    return escreveu;
}

/* pagina_do_conceito pode ser NULL (conceito que só tem exercícios); aí o
   título sai sem link. */
static void escrever_bloco_do_conceito(FILE *saida, const char *conceito,
                                       Pagina *pagina_do_conceito,
                                       Pagina paginas[], int quantidade_de_paginas) {
    /* exercícios: o exercicios_*.txt cujo Conceitos é este */
    Pagina *exercicios = NULL;
    for (int indice = 0; indice < quantidade_de_paginas && exercicios == NULL; indice++) {
        if (paginas[indice].eh_pagina_de_exercicios
            && pagina_tem_valor(&paginas[indice], ROTULO_CONCEITOS, conceito)) {
            exercicios = &paginas[indice];
        }
    }

    /* conceito sem problema e sem exercício não aparece */
    int tem_problema = 0;
    for (int indice = 0; indice < quantidade_de_paginas && !tem_problema; indice++) {
        tem_problema = eh_algoritmo(&paginas[indice])
            && pagina_tem_valor(&paginas[indice], ROTULO_CONCEITOS, conceito)
            && paginas[indice].quantidade_de_valores[ROTULO_PROBLEMA] > 0;
    }
    if (!tem_problema && exercicios == NULL) return;

    fprintf(saida, "<section class=\"conceito\">\n<h2>");
    if (pagina_do_conceito != NULL) escrever_link_para_pagina(saida, pagina_do_conceito);
    else escrever_texto_html(saida, conceito);
    fprintf(saida, "</h2>\n");
    escrever_problemas_do_conceito(saida, conceito, paginas, quantidade_de_paginas);
    if (exercicios != NULL) escrever_exercicios(saida, exercicios);
    fprintf(saida, "</section>\n");
}

void gerar_indice_de_problemas(const char *pasta, Pagina paginas[], int quantidade_de_paginas) {
    FILE *saida = abrir_saida(pasta, ARQUIVOS_DOS_INDICES[ROTULO_PROBLEMA]);
    if (saida == NULL) return;
    escrever_inicio_html(saida, "Problemas e exercícios");

    fprintf(saida, "<p class=\"apresentacao\">Para cada conceito: os problemas que os algoritmos "
                   "do curso resolvem e exercícios extras de livros, com a resolução escondida "
                   "(tente antes de abrir).</p>\n");

    /* 1) conceitos na ordem do semanas.txt; 2) conceitos fora dele;
       3) exercícios de conceitos que ainda não têm página */
    for (int item = 0; item < quantidade_de_itens; item++) {
        Pagina *pagina = &paginas[itens[item].indice_da_pagina];
        if (pagina->eh_pagina_de_conceito && pagina->quantidade_de_valores[ROTULO_CONCEITOS] > 0) {
            escrever_bloco_do_conceito(saida, pagina->valores[ROTULO_CONCEITOS][0], pagina,
                                       paginas, quantidade_de_paginas);
        }
    }
    for (int indice = 0; indice < quantidade_de_paginas; indice++) {
        Pagina *pagina = &paginas[indice];
        if (pagina->eh_pagina_de_conceito && pagina->semana == 0
            && pagina->quantidade_de_valores[ROTULO_CONCEITOS] > 0) {
            escrever_bloco_do_conceito(saida, pagina->valores[ROTULO_CONCEITOS][0], pagina,
                                       paginas, quantidade_de_paginas);
        }
    }
    for (int indice = 0; indice < quantidade_de_paginas; indice++) {
        Pagina *pagina = &paginas[indice];
        if (!pagina->eh_pagina_de_exercicios || pagina->quantidade_de_valores[ROTULO_CONCEITOS] == 0) continue;
        const char *conceito = pagina->valores[ROTULO_CONCEITOS][0];
        if (encontrar_pagina_de_conceito(conceito, paginas, quantidade_de_paginas) < 0) {
            escrever_bloco_do_conceito(saida, conceito, NULL, paginas, quantidade_de_paginas);
        }
    }

    escrever_fim_html(saida);
    fclose(saida);
}
