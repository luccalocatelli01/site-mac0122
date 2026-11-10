# Filtro colorizador — pacote final para integração

Este pacote contém o filtro desenvolvido para mostrar
código C em páginas HTML. 
## O que incorporar ao projeto

| Arquivo | Uso |
| --- | --- |
| filtro.h | Interface: incluir no arquivo C que chama colorir_codigo. |
| filtro.c | Implementação: compilar junto com os arquivos do gerador. Não contém main, penas a função de colorir. |
| estilo.css | Aparência: colocar no site, no caminho indicado pelo link das páginas. |

## Arquivos de apoio que também acompanham a entrega

| Arquivo | Uso |
| --- | --- |
| main_filtro.c | Programa independente para testar o filtro. Contém main. |
| teste_filtro.c | Código C válido com casos difíceis; é a entrada do filtro, não parte do gerador. Contém main. |
| exemplo_integracao.c | Outro programa independente: chama o filtro duas vezes na mesma página. Contém main. |
| LEIA-ME.md | Estas instruções. |
| VALIDACAO.txt | Resultado e limites da verificação do pacote. |
| previa_filtro.html | Demonstração pronta das cinco categorias, com o CSS desta pasta. |

Para incorporar o filtro ao gerador,
os três primeiros arquivos são suficientes. Os três programas com main não devem
ser compilados juntos. Não usar gcc *.c para criar um único executável.

## Testar o filtro sozinho

    gcc -std=c11 -Wall -Wextra main_filtro.c filtro.c -o colorir
    ./colorir teste_filtro.c > teste.html

Abrir teste.html no navegador. O estilo.css deve estar na mesma pasta.

Para gerar somente o fragmento, sem página completa:

    ./colorir teste_filtro.c --trecho > trecho.html

trecho.html não carrega CSS sozinho; ele foi feito para ser inserido em uma página.

## Testar como outro programa chama o filtro

    gcc -std=c11 -Wall -Wextra exemplo_integracao.c filtro.c -o exemplo_integracao
    ./exemplo_integracao teste_filtro.c

Abrir integracao.html no navegador. A página contém duas chamadas do filtro e
texto do gerador entre elas e depois delas. O exemplo não depende de main_filtro.c.

Para verificar separadamente se a entrada de teste compila:

    gcc -std=c11 -Wall -Wextra teste_filtro.c -o programa_de_teste

Não é necessário executar esse programa para colorir seu código.

## Contrato da função

    #include "filtro.h"
    void colorir_codigo(FILE *entrada, FILE *saida);

- entrada e saida devem ser fluxos válidos, já abertos, distintos e com os modos adequados.
- A função lê da posição atual da entrada até o fim.
- Escreve na posição atual da saída um fragmento <pre class="codigo">...</pre>.
- Não escreve html, head ou body.
- Não abre, fecha ou rebobina arquivos. Quem chama mantém a responsabilidade por eles.
- Cada chamada começa no estado NORMAL, sem herdar o contexto da chamada anterior.
- Protege <, > e & encontrados no código de entrada.
- Aplica somente as classes pragma, tipo, comando, comentario e cadeia.
- Literais de caractere, como 'a', também usam cadeia.
- Por ter retorno void, a função não fornece um código de erro. O chamador deve
  verificar ferror nos fluxos e o resultado de fflush/fclose da saída.

## Como incorporar ao gerador

No arquivo que cria a página:

    #include "filtro.h"

Dentro da função que já possui pagina_html aberto para escrita:

    FILE *codigo = fopen(caminho_do_codigo, "r");
    if (codigo == NULL) {
        fputs("<p>Codigo indisponivel.</p>", pagina_html);
    } else {
        colorir_codigo(codigo, pagina_html);
        /* Tratar ferror(codigo) e os erros da pagina no gerador. */
        fclose(codigo);
    }

Não chamar colorir_codigo se fopen retornar NULL.
Não executar o arquivo C que será exibido: ele é lido como texto.

Se filtro.h e filtro.c estiverem junto aos fontes do gerador, a compilação é,
por exemplo:

    gcc -std=c11 -Wall -Wextra gerador.c pagina.c filtro.c -o gerador

gerador.c e pagina.c são nomes ilustrativos; substituir pelos arquivos reais.
Se o filtro ficar numa subpasta filtro/:

    gcc -std=c11 -Wall -Wextra -Ifiltro gerador.c pagina.c filtro/filtro.c -o gerador

-I informa onde procurar filtro.h. Não incluir main_filtro.c, teste_filtro.c
nem exemplo_integracao.c na compilação do gerador.

## Como conectar o CSS

O gerador escreve no head de cada página:

    <meta charset="utf-8">
    <link rel="stylesheet" href="estilo.css">

Com esse href, estilo.css precisa ficar ao lado da página HTML.
Se a página estiver numa subpasta, ajustar o href ao caminho real.
O filtro não copia o CSS; essa cópia é responsabilidade da montagem do site.
Se o site já tiver uma folha de estilos, incorporar as regras com cuidado para
que outras regras não sobrescrevam as cores do código.

## Categorias e funcionamento

- pragma: linhas de diretivas, como #include e #define.
- tipo: lista explícita de palavras, incluindo int, char, double e FILE.
- comando: lista explícita de palavras, incluindo if, for, while e return.
- comentario: comentários // e /* ... */.
- cadeia: cadeias entre aspas duplas e literais de caractere.

O filtro usa estados para distinguir contexto e lê palavras inteiras antes de
consultar as listas. Assim, intervalo não recebe a cor de int. Dentro de cadeias
e comentários, não procura palavras-chave. Aspas escapadas, comentários no fim
do arquivo e continuações usuais de diretivas são tratados.

É um colorizador didático com listas fixas, não um compilador ou validador
sintático de C. Não simula integralmente todas as fases do pré-processador
(por exemplo, palavras ou delimitadores partidos por barra invertida e quebra
de linha). Requisitos novos devem virar casos de teste antes de alterar o filtro.

## Paleta e referência confirmadas

Referência indicada no enunciado:
https://en.wikipedia.org/wiki/Syntax_highlighting#Examples

Foram consultados os estilos efetivamente aplicados ao exemplo de C no tema
claro, em 09/11/2026. A revisão do artigo consultada foi:
https://en.wikipedia.org/w/index.php?title=Syntax_highlighting&oldid=1377048330

| Categoria do projeto | Cor adotada | Correspondência no exemplo |
| --- | --- | --- |
| pragma | #9C6500 | Diretiva #include |
| tipo | #B00040 | Tipo int |
| comando | #008000, negrito | Palavra-chave return |
| comentario | #3D7B7B, itálico | Comentário // |
| cadeia | #BA2121 | Texto da cadeia |

Esta é uma adaptação da paleta do exemplo às cinco categorias do enunciado.
O artigo não estabelece uma paleta universal obrigatória. Seu exemplo também
distingue subcategorias (como números e escapes), que não foram acrescentadas
ao contrato de cinco classes do grupo. Não se afirma equivalência visual de
cada token com o realçador completo da Wikipedia.

## Escopo deste pacote

Este é o pacote técnico do módulo colorizador para integração.
As páginas, os índices, o conteúdo TXT e os demais códigos do trabalho
pertencem à entrega coletiva e não estão incluídos neste módulo.
