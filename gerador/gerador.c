/*
 * gerador.c — EP MAC0122, fase 1
 *
 * Lê os TXT do curso e gera o site. Aqui ficam a leitura dos TXT, os índices
 * de Técnica, Autores e Data e o main. A organização por semanas (início,
 * Algoritmo, Conceitos, Problema) está em organizacao.c.
 *
 * Uso: ./gerador <pasta_de_saida> <pasta_dos_codigos> arquivo1.txt arquivo2.txt ...
 *      (o Makefile já chama assim: make site)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include "pagina.h"

#define MAXIMO_DE_PAGINAS 200

/* Uma linha de uma página indexadora: "Joseph Kruskal" -> página 3. */
typedef struct {
    char chave[TAMANHO_DO_VALOR];
    int indice_da_pagina;
} Entrada;

/* =================== funções auxiliares (prontas) =================== */

/* Tira espaços, tabs e \n do começo e do fim do texto, no próprio vetor. */
static void remover_espacos_das_pontas(char *texto) {
    int tamanho = strlen(texto);
    while (tamanho > 0 && isspace((unsigned char) texto[tamanho - 1])) {
        tamanho--;
        texto[tamanho] = '\0';
    }
    int inicio = 0;
    while (isspace((unsigned char) texto[inicio])) {
        inicio++;
    }
    if (inicio > 0) {
        memmove(texto, texto + inicio, tamanho - inicio + 1);
    }
}

/* Recebe o nome antes do ':' ("Tecnica", "Técnica", "conceitos"...) e
   devolve o TipoDeRotulo, ou -1 se não for nenhum dos 6. */
static int identificar_rotulo(const char *nome) {
    for (int rotulo = 0; rotulo < NUMERO_DE_ROTULOS; rotulo++) {
        if (comparar_textos_sem_acento(nome, NOMES_DOS_ROTULOS[rotulo]) == 0) {
            return rotulo;
        }
    }
    return -1;
}

/* Guarda um valor no rótulo, se ainda couber. */
static void adicionar_valor(Pagina *pagina, int rotulo, const char *valor) {
    int quantidade = pagina->quantidade_de_valores[rotulo];
    if (quantidade >= MAXIMO_DE_VALORES) {
        fprintf(stderr, "aviso: %s tem valores demais em %s; o resto foi ignorado\n",
                pagina->caminho_do_txt, NOMES_DOS_ROTULOS[rotulo]);
        return;
    }
    strncpy(pagina->valores[rotulo][quantidade], valor, TAMANHO_DO_VALOR - 1);
    pagina->valores[rotulo][quantidade][TAMANHO_DO_VALOR - 1] = '\0';
    pagina->quantidade_de_valores[rotulo] = quantidade + 1;
}

/* Abre <pasta>/<nome> para escrita. */
static FILE *abrir_arquivo_de_saida(const char *pasta, const char *nome) {
    char caminho[2 * TAMANHO_DO_CAMINHO];
    snprintf(caminho, sizeof caminho, "%s/%s", pasta, nome);
    FILE *arquivo = fopen(caminho, "w");
    if (arquivo == NULL) {
        fprintf(stderr, "erro: não consegui criar %s\n", caminho);
    }
    return arquivo;
}

/* =============== leitura do cabeçalho do TXT (Camila) =============== */

/*
 * Lê linha por linha (fgets) até a linha "---" ou até o fim do arquivo.
 * Cada linha "Rotulo: valor1, valor2" é cortada no ':' (nome e resto).
 * Rótulos desconhecidos e vazios são ignorados. Algoritmo e Problema guardam
 * o resto inteiro (o Problema tem vírgulas); os outros 4 são quebrados em
 * cada vírgula com strtok. Ao achar "---", guarda em posicao_do_corpo onde o
 * texto começa (ftell) e devolve 1; se o arquivo acabar antes, devolve 0.
 */
static int ler_cabecalho(FILE *arquivo, Pagina *pagina) {
    char linha[TAMANHO_DA_LINHA];

    while (fgets(linha, sizeof linha, arquivo) != NULL) {
        char copia_linha[TAMANHO_DA_LINHA];
        strcpy(copia_linha, linha);
        remover_espacos_das_pontas(copia_linha);
        
        if (strcmp(copia_linha, "---") == 0){
            pagina->posicao_do_corpo = ftell(arquivo);
            return 1;
        }

        char *dois_pontos = strchr(linha, ':');
        if(dois_pontos == NULL) continue;
        *dois_pontos = '\0';
        char *resto = dois_pontos + 1;
        remover_espacos_das_pontas(linha);
        remover_espacos_das_pontas(resto);

        int rotulo = identificar_rotulo(linha);
        if (rotulo == -1) continue;
        if (resto[0] == '\0') continue;

        if (rotulo == ROTULO_ALGORITMO || rotulo == ROTULO_PROBLEMA) {
            adicionar_valor(pagina, rotulo, resto);
        } else {
            char *pedaco = strtok(resto, ",");
            while (pedaco != NULL) {
                remover_espacos_das_pontas(pedaco);
                if (pedaco[0] != '\0') {
                    adicionar_valor(pagina, rotulo, pedaco);
                }
                pedaco = strtok(NULL, ",");
            }
        }
    }
    return 0;
}

/* =================== leitura de uma página (pronta) =================== */

/* Título da página nos links: o Algoritmo; numa página de conceito, o
   Conceito; se não houver nenhum, o nome do arquivo sem ".txt". */
static void definir_titulo(Pagina *pagina, const char *nome_do_arquivo) {
    if (pagina->quantidade_de_valores[ROTULO_ALGORITMO] > 0) {
        strcpy(pagina->titulo, pagina->valores[ROTULO_ALGORITMO][0]);
    } else if (pagina->eh_pagina_de_conceito
               && pagina->quantidade_de_valores[ROTULO_CONCEITOS] > 0) {
        strcpy(pagina->titulo, pagina->valores[ROTULO_CONCEITOS][0]);
    } else {
        strncpy(pagina->titulo, nome_do_arquivo, TAMANHO_DO_VALOR - 1);
        char *ponto = strrchr(pagina->titulo, '.');
        if (ponto != NULL) *ponto = '\0';
    }
}

/* Lê um TXT inteiro para a struct. Devolve 1 se deu certo. */
static int ler_pagina(const char *caminho_do_txt, Pagina *pagina) {
    FILE *arquivo = fopen(caminho_do_txt, "r");
    if (arquivo == NULL) {
        fprintf(stderr, "erro: não consegui abrir %s\n", caminho_do_txt);
        return 0;
    }

    memset(pagina, 0, sizeof *pagina);
    strncpy(pagina->caminho_do_txt, caminho_do_txt, TAMANHO_DO_CAMINHO - 1);

    /* "../txt/fusao.txt" -> nome do arquivo "fusao.txt" -> "fusao.html" */
    const char *barra = strrchr(caminho_do_txt, '/');
    const char *nome_do_arquivo = (barra != NULL) ? barra + 1 : caminho_do_txt;
    strncpy(pagina->nome_do_html, nome_do_arquivo, TAMANHO_DO_CAMINHO - 6);
    char *ponto = strrchr(pagina->nome_do_html, '.');
    if (ponto != NULL) *ponto = '\0';
    strcat(pagina->nome_do_html, ".html");

    pagina->eh_pagina_de_conceito = (strncmp(nome_do_arquivo, "conceito_", 9) == 0);
    pagina->eh_pagina_de_exercicios = (strncmp(nome_do_arquivo, "exercicios_", 11) == 0);

    if (!ler_cabecalho(arquivo, pagina)) {
        fprintf(stderr, "aviso: %s não tem a linha ---\n", caminho_do_txt);
    }
    fclose(arquivo);

    definir_titulo(pagina, nome_do_arquivo);
    return 1;
}

/* ================= ordenação das entradas (Camila) ================= */

/* Valor em algarismos romanos de uma letra (I, V, X, L, C), ou 0. */
static int valor_romano(char letra) {
    switch (letra) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        default:  return 0;
    }
}

/*
 * Ano de um texto do rótulo Data, para ordenar em ordem cronológica:
 *   "1945" -> 1945      "c. 300 a.C." -> -300      "séc. XIX" -> 1800
 * Texto sem ano nenhum vai para o fim.
 */
static int ano_do_texto(const char *texto) {
    for (const char *cursor = texto; *cursor != '\0'; cursor++) {
        if (isdigit((unsigned char) *cursor)) {
            int ano = atoi(cursor);
            if (strstr(texto, "a.C.") != NULL || strstr(texto, "a. C.") != NULL) ano = -ano;
            return ano;
        }
    }
    /* sem dígitos: procura um século em romanos ("séc. XIX") */
    for (const char *cursor = texto; *cursor != '\0'; cursor++) {
        int comeco_de_palavra = (cursor == texto || cursor[-1] == ' ');
        if (comeco_de_palavra && valor_romano(*cursor) > 0) {
            int seculo = 0;
            while (valor_romano(*cursor) > 0) {
                int atual = valor_romano(*cursor);
                int proximo = valor_romano(cursor[1]);
                seculo += (atual < proximo) ? -atual : atual;   /* IX = 9, XI = 11 */
                cursor++;
            }
            return (seculo - 1) * 100;
        }
    }
    return 1000000;
}

/* Ordem de duas entradas: em Data, pelo ano; nos outros rótulos, pela chave,
   sem ligar pra acento e maiúscula. Empate: na ordem das páginas. */
static int comparar_entradas(const Entrada *primeira, const Entrada *segunda, int rotulo) {
    int resultado;
    if (rotulo == ROTULO_DATA) {
        resultado = ano_do_texto(primeira->chave) - ano_do_texto(segunda->chave);
    } else {
        resultado = comparar_textos_sem_acento(primeira->chave, segunda->chave);
    }
    if (resultado != 0) return resultado;
    return primeira->indice_da_pagina - segunda->indice_da_pagina;
}

/*
 * Ordenação por fusão (mergesort) das entradas, com intervalos semiabertos
 * [inicio, fim). comparar_entradas(&a, &b, rotulo) negativo = a vem antes de b.
 *
 * intercalar: junta as metades ordenadas [inicio, meio) e [meio, fim) no
 * vetor auxiliar e copia de volta. Em empate pega a da esquerda (estável).
 */
static void intercalar(Entrada entradas[], Entrada auxiliar[], int inicio, int meio, int fim, int rotulo) {
    int esquerda = inicio;
    int direita = meio;
    int destino = inicio;
    while (esquerda < meio && direita < fim) {
        if (comparar_entradas(&entradas[esquerda], &entradas[direita], rotulo) <= 0) {
            auxiliar[destino++] = entradas[esquerda++];
        } else {
            auxiliar[destino++] = entradas[direita++];
        }
    }
    while (esquerda < meio) {
        auxiliar[destino++] = entradas[esquerda++];
    }
    while (direita < fim) {
        auxiliar[destino++] = entradas[direita++];
    }
    for (int posicao = inicio; posicao < fim; posicao++) {
        entradas[posicao] = auxiliar[posicao];
    }
}

static void mergesort_entradas(Entrada entradas[], Entrada auxiliar[], int inicio, int fim, int rotulo) {
    if (fim - inicio <= 1) return;
    int meio = inicio + (fim - inicio) / 2;
    mergesort_entradas(entradas, auxiliar, inicio, meio, rotulo);
    mergesort_entradas(entradas, auxiliar, meio, fim, rotulo);
    intercalar(entradas, auxiliar, inicio, meio, fim, rotulo);
}

static void ordenar_entradas(Entrada entradas[], int quantidade, int rotulo) {
    if (quantidade <= 1) return;
    Entrada *auxiliar = malloc(quantidade * sizeof(Entrada));
    if (auxiliar == NULL) return;
    mergesort_entradas(entradas, auxiliar, 0, quantidade, rotulo);
    free(auxiliar);
}

/* ================ escrita dos grupos (Camila) ================ */

/*
 * Usada em Técnica, Autores e Data. As entradas já estão ordenadas, então
 * chaves iguais estão vizinhas. Cada grupo de chaves iguais
 * (comparar_textos_sem_acento == 0) vira um cartão:
 *
 *   <section class="cartao grupo cor-N">       <- N = número do grupo % 5 (cor da borda)
 *   <h2>chave</h2>
 *   <ul>
 *   <li><a href="nome_do_html">titulo</a></li>     <- uma por entrada do grupo
 *   </ul>
 *   </section>
 *
 * inicio_do_grupo marca a primeira entrada do grupo e atual anda enquanto a
 * chave for igual; o próximo grupo começa onde atual parou.
 */
static void escrever_grupos(FILE *saida, Entrada entradas[], int quantidade, Pagina paginas[]) {
    int inicio_do_grupo = 0;
    int contador_de_grupos = 0;
    while (inicio_do_grupo < quantidade) {
        fprintf(saida, "<section class=\"cartao grupo cor-%d\">\n<h2>", contador_de_grupos % 5);
        escrever_texto_html(saida, entradas[inicio_do_grupo].chave);
        fprintf(saida, "</h2>\n<ul>\n");
        int atual = inicio_do_grupo;
        while (atual < quantidade && comparar_textos_sem_acento(entradas[inicio_do_grupo].chave, entradas[atual].chave) == 0) {
            fprintf(saida, "<li>");
            escrever_link_para_pagina(saida, &paginas[entradas[atual].indice_da_pagina]);
            fprintf(saida, "</li>\n");
            atual++;
        }
        fprintf(saida, "</ul>\n</section>\n");
        inicio_do_grupo = atual;
        contador_de_grupos++;
    }
}

/* ============ índices de Técnica, Autores e Data (prontos) ============ */

/* Junta todas as entradas de um rótulo, ordena e escreve a página. */
static void gerar_indexadora(const char *pasta, int rotulo,
                             Pagina paginas[], int quantidade_de_paginas) {
    Entrada *entradas = malloc((quantidade_de_paginas * MAXIMO_DE_VALORES + 1) * sizeof(Entrada));
    if (entradas == NULL) {
        fprintf(stderr, "erro: sem memória\n");
        return;
    }

    int quantidade_de_entradas = 0;
    for (int indice_da_pagina = 0; indice_da_pagina < quantidade_de_paginas; indice_da_pagina++) {
        Pagina *pagina = &paginas[indice_da_pagina];
        /* conceitos e exercícios não entram nos índices */
        if (pagina->eh_pagina_de_conceito || pagina->eh_pagina_de_exercicios) continue;
        for (int valor = 0; valor < pagina->quantidade_de_valores[rotulo]; valor++) {
            strcpy(entradas[quantidade_de_entradas].chave, pagina->valores[rotulo][valor]);
            entradas[quantidade_de_entradas].indice_da_pagina = indice_da_pagina;
            quantidade_de_entradas++;
        }
    }

    ordenar_entradas(entradas, quantidade_de_entradas, rotulo);

    FILE *saida = abrir_arquivo_de_saida(pasta, ARQUIVOS_DOS_INDICES[rotulo]);
    if (saida != NULL) {
        escrever_inicio_html(saida, TITULOS_DOS_ROTULOS[rotulo]);
        escrever_grupos(saida, entradas, quantidade_de_entradas, paginas);
        escrever_fim_html(saida);
        fclose(saida);
    }
    free(entradas);
}

/* =============================== main =============================== */

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Uso: %s <pasta_de_saida> <pasta_dos_codigos> arquivo1.txt [arquivo2.txt ...]\n",
                argv[0]);
        return 1;
    }
    const char *pasta_de_saida = argv[1];
    pasta_dos_codigos = argv[2];
    mkdir(pasta_de_saida, 0755);   /* se a pasta já existir, não tem problema */

    Pagina *paginas = malloc(MAXIMO_DE_PAGINAS * sizeof(Pagina));
    if (paginas == NULL) {
        fprintf(stderr, "erro: sem memória\n");
        return 1;
    }

    int quantidade_de_paginas = 0;
    for (int argumento = 3; argumento < argc; argumento++) {
        if (quantidade_de_paginas == MAXIMO_DE_PAGINAS) {
            fprintf(stderr, "aviso: mais de %d TXT; o resto foi ignorado\n", MAXIMO_DE_PAGINAS);
            break;
        }
        if (ler_pagina(argv[argumento], &paginas[quantidade_de_paginas])) {
            quantidade_de_paginas++;
        }
    }

    ler_semanas("semanas.txt", paginas, quantidade_de_paginas);

    /* início e índices por semana / por conceito (organizacao.c) */
    gerar_pagina_inicial(pasta_de_saida, paginas, quantidade_de_paginas);
    gerar_indice_de_algoritmos(pasta_de_saida, paginas, quantidade_de_paginas);
    gerar_indice_de_conceitos(pasta_de_saida, paginas, quantidade_de_paginas);
    gerar_indice_de_problemas(pasta_de_saida, paginas, quantidade_de_paginas);

    /* índices ordenados (este arquivo) */
    gerar_indexadora(pasta_de_saida, ROTULO_TECNICA, paginas, quantidade_de_paginas);
    gerar_indexadora(pasta_de_saida, ROTULO_AUTORES, paginas, quantidade_de_paginas);
    gerar_indexadora(pasta_de_saida, ROTULO_DATA, paginas, quantidade_de_paginas);

    /* uma página por TXT (pagina_txt.c, do Lucca) */
    for (int indice = 0; indice < quantidade_de_paginas; indice++) {
        if (paginas[indice].eh_pagina_de_exercicios) continue;
        FILE *saida = abrir_arquivo_de_saida(pasta_de_saida, paginas[indice].nome_do_html);
        if (saida == NULL) continue;
        gerar_pagina_txt(&paginas[indice], paginas, quantidade_de_paginas, saida);
        fclose(saida);
    }

    printf("%d arquivos lidos; site gerado em %s/\n", quantidade_de_paginas, pasta_de_saida);
    free(paginas);
    return 0;
}
