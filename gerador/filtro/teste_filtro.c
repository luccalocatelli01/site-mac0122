/* Arquivo C valido para experimentar as cinco classes do filtro. */
#include <stdio.h>
#define LIMITE 10 // Comentario depois de uma diretiva.
#define URL "http://exemplo.test"
#define SOMA(a, b) \
    ((a) + (b))
#define VALOR /* comentario no meio da diretiva */ 3
#define ASPA '"'

/* Um comentario pode ocupar
   varias linhas e conter "aspas", int, if e <tags> &. */
/***/ /**/

static int dividir(int a, int b) {
    return a / b;
}

int main(void) {
    int intervalo = 4, iff = 1, _for = 2;
    const char *s1 = "for if int";
    const char *s2 = "aspas \" dentro";
    const char *s3 = "// nao e comentario";
    const char *s4 = "/* tambem nao */";
    const char *s5 = "barra no fim \\";
    const char *s6 = "<b>oi</b> &lt;";
    char c1 = '"', c2 = '\'', c3 = '\\';

    // As palavras int e for e as "aspas" continuam sendo comentario.
    if (intervalo<LIMITE&&iff>0) {
        intervalo = SOMA(intervalo, dividir(10, 2));
    }

    printf("%s\n%s\n%s\n%s\n%s\n%s\n", s1, s2, s3, s4, s5, s6);
    printf("%c %c %c %c %s %d\n",
           c1, c2, c3, ASPA, URL, intervalo + _for + VALOR);
    return 0;
}
// Comentario final sem quebra de linha.