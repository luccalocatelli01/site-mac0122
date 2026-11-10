#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "filtro.h"

#define MAX_PALAVRA 256

/* O estado indica como interpretar o caractere que esta sendo lido. */
typedef enum {
    NORMAL, PRAGMA, COM_LINHA, COM_BLOCO, CADEIA, CARACTERE
} Estado;

static const char *TIPOS[] = {
    "int", "char", "float", "double", "void", "short", "long",
    "signed", "unsigned", "struct", "union", "enum", "typedef",
    "const", "static", "extern", "FILE", "size_t", "bool", NULL
};

static const char *COMANDOS[] = {
    "if", "else", "for", "while", "do", "switch", "case", "default",
    "break", "continue", "return", "goto", "sizeof", NULL
};

/* Escreve texto da entrada, protegendo os caracteres especiais do HTML. */
static void escreve(int c, FILE *saida) {
    if (c == '<') {
        fputs("&lt;", saida);
    } else if (c == '>') {
        fputs("&gt;", saida);
    } else if (c == '&') {
        fputs("&amp;", saida);
    } else {
        putc(c, saida);
    }
}


/* Olha o proximo caractere e o devolve: a proxima leitura ainda o encontrara. */
static int espia(FILE *entrada) {
    int c = getc(entrada);
    if (c != EOF) {
        ungetc(c, entrada);
    }
    return c;
}

static void abre(const char *classe, FILE *saida) {
    fprintf(saida, "<span class=\"%s\">", classe);
}

static void fecha(FILE *saida) {
    fputs("</span>", saida);
}

/* Depois de uma barra invertida, copia o proximo sem interpreta-lo.
   Mantem CR e LF juntos quando a entrada usa quebras do Windows. */
static void copia_escapado(FILE *entrada, FILE *saida) {
    int c = getc(entrada);
    if (c != EOF) {
        escreve(c, saida);
        if (c == '\r' && espia(entrada) == '\n') {
            escreve(getc(entrada), saida);
        }
    }
}

/* Devolve 1 se encontrar a palavra; 0 se chegar ao fim da lista. */
static int esta_na_lista(const char *palavra, const char *lista[]) {
    int i;

    for (i = 0; lista[i] != NULL; i++) {
        if (strcmp(palavra, lista[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

/* A primeira letra ja foi lida pelo laco principal. */
static void trata_palavra(int c, FILE *entrada, FILE *saida) {
    char palavra[MAX_PALAVRA];
    int n = 0;
    int longa = 0;

    while (c != EOF && (isalnum(c) || c == '_')) {
        /* Se nao couber, copia em partes, sem tentar colorir a palavra. */
        if (n == MAX_PALAVRA - 1) {
            palavra[n] = '\0';
            fputs(palavra, saida);
            n = 0;
            longa = 1;
        }

        palavra[n] = (char) c;
        n++;
        c = getc(entrada);
    }
    palavra[n] = '\0';

    /* O caractere que encerrou a palavra pertence ao laco principal. */
    if (c != EOF) {
        ungetc(c, entrada);
    }

    if (!longa && esta_na_lista(palavra, TIPOS)) {
        fputs("<span class=\"tipo\">", saida);
        fputs(palavra, saida);
        fputs("</span>", saida);
    } else if (!longa && esta_na_lista(palavra, COMANDOS)) {
        fputs("<span class=\"comando\">", saida);
        fputs(palavra, saida);
        fputs("</span>", saida);
    } else {
        fputs(palavra, saida);
    }
}

void colorir_codigo(FILE *entrada, FILE *saida) {
    Estado estado = NORMAL;
    Estado retorno_comentario = NORMAL;
    int inicio_linha = 1;
    int aspas_pragma = 0;
    int c;

    fputs("<pre class=\"codigo\">", saida);
    c = getc(entrada);

    while (c != EOF) {
        switch (estado) {
        case NORMAL:
            if (c == '\n' || c == '\r') {
                escreve(c, saida);
                inicio_linha = 1;
            } else if (isspace(c)) {
                escreve(c, saida);
            } else if (c == '/' && espia(entrada) == '/') {
                abre("comentario", saida);
                escreve(c, saida);
                escreve(getc(entrada), saida);
                estado = COM_LINHA;
            } else if (c == '/' && espia(entrada) == '*') {
                abre("comentario", saida);
                escreve(c, saida);
                escreve(getc(entrada), saida);
                retorno_comentario = NORMAL;
                estado = COM_BLOCO;
            } else if (c == '#' && inicio_linha) {
                abre("pragma", saida);
                escreve(c, saida);
                aspas_pragma = 0;
                inicio_linha = 0;
                estado = PRAGMA;
            } else if (c == '"') {
                abre("cadeia", saida);
                escreve(c, saida);
                inicio_linha = 0;
                estado = CADEIA;
            } else if (c == '\'') {
                abre("cadeia", saida);
                escreve(c, saida);
                inicio_linha = 0;
                estado = CARACTERE;
            } else if (isalnum(c) || c == '_') {
                trata_palavra(c, entrada, saida);
                inicio_linha = 0;
            } else {
                escreve(c, saida);
                inicio_linha = 0;
            }
            break;

        case COM_LINHA:
            if (c == '\n' || c == '\r') {
                fecha(saida);
                escreve(c, saida);
                inicio_linha = 1;
                estado = NORMAL;
            } else if (c == '\\' &&
                       (espia(entrada) == '\n' || espia(entrada) == '\r')) {
                escreve(c, saida);
                copia_escapado(entrada, saida);
            } else {
                escreve(c, saida);
            }
            break;

        case COM_BLOCO:
            if (c == '*' && espia(entrada) == '/') {
                escreve(c, saida);
                escreve(getc(entrada), saida);
                fecha(saida);
                estado = retorno_comentario;
                if (estado == PRAGMA) {
                    abre("pragma", saida);
                }
            } else {
                escreve(c, saida);
                if (c == '\n' || c == '\r') {
                    inicio_linha = 1;
                }
            }
            break;

        case CADEIA:
        case CARACTERE:
            /* Os dois estados seguem a mesma regra; muda a aspa de fechamento. */
            if (c == '\\') {
                escreve(c, saida);
                copia_escapado(entrada, saida);
            } else if ((estado == CADEIA && c == '"') ||
                       (estado == CARACTERE && c == '\'')) {
                escreve(c, saida);
                fecha(saida);
                estado = NORMAL;
            } else if (c == '\n' || c == '\r') {
                /* Recuperacao para uma aspa esquecida no codigo de entrada. */
                fecha(saida);
                escreve(c, saida);
                inicio_linha = 1;
                estado = NORMAL;
            } else {
                escreve(c, saida);
            }
            break;

        case PRAGMA:
            if (c == '\n' || c == '\r') {
                fecha(saida);
                escreve(c, saida);
                inicio_linha = 1;
                estado = NORMAL;
            } else if (c == '\\' &&
                       (aspas_pragma || espia(entrada) == '\n' ||
                        espia(entrada) == '\r')) {
                escreve(c, saida);
                copia_escapado(entrada, saida);
            } else if (!aspas_pragma && c == '/' && espia(entrada) == '/') {
                fecha(saida);
                abre("comentario", saida);
                escreve(c, saida);
                escreve(getc(entrada), saida);
                estado = COM_LINHA;
            } else if (!aspas_pragma && c == '/' && espia(entrada) == '*') {
                fecha(saida);
                abre("comentario", saida);
                escreve(c, saida);
                escreve(getc(entrada), saida);
                retorno_comentario = PRAGMA;
                estado = COM_BLOCO;
            } else {
                if (aspas_pragma == 0 && (c == '"' || c == '\'')) {
                    aspas_pragma = c;
                } else if (c == aspas_pragma) {
                    aspas_pragma = 0;
                }
                escreve(c, saida);
            }
            break;
        }
        c = getc(entrada);
    }

    /* A ultima linha pode terminar sem uma quebra de linha. */
    if (estado != NORMAL) {
        fecha(saida);
    }
    fputs("</pre>", saida);
}
