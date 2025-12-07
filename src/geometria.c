#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "geometria.h"
#include "lista.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

typedef struct {
    float x, y;
} Ponto;

typedef struct {
    Ponto p1;
    Ponto p2;
    int id_original;
} StSegmento;

SEGMENTO cria_segmento(float x1, float y1, float x2, float y2, int id) {
    StSegmento* seg = (StSegmento*) malloc(sizeof(StSegmento));
    seg->p1.x = x1;
    seg->p1.y = y1;
    seg->p2.x = x2;
    seg->p2.y = y2;
    seg->id_original = id;
    return (SEGMENTO) seg;
}

float get_seg_x1(SEGMENTO s) { return ((StSegmento*)s)->p1.x; }
float get_seg_y1(SEGMENTO s) { return ((StSegmento*)s)->p1.y; }
float get_seg_x2(SEGMENTO s) { return ((StSegmento*)s)->p2.x; }
float get_seg_y2(SEGMENTO s) { return ((StSegmento*)s)->p2.y; }
int get_seg_id(SEGMENTO s)   { return ((StSegmento*)s)->id_original; }

void kill_segmento(SEGMENTO s) {
    if (s) free(s);
}

float distancia_pontos(float x1, float y1, float x2, float y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

LISTA retangulo_para_segmentos(void* r) {
    LISTA l = criar_lista();
    int id = get_idR(r);
    float x = get_XR(r);
    float y = get_YR(r);
    float w = get_WR(r);
    float h = get_HR(r);

    inserir_na_lista(l, cria_segmento(x, y, x + w, y, id));
    inserir_na_lista(l, cria_segmento(x, y + h, x + w, y + h, id));
    inserir_na_lista(l, cria_segmento(x, y, x, y + h, id));
    inserir_na_lista(l, cria_segmento(x + w, y, x + w, y + h, id));

    return l;
}

LISTA circulo_para_segmentos(void* c) {
    LISTA l = criar_lista();
    int id = get_idC(c);
    float x = get_XC(c);
    float y = get_YC(c);
    float r = get_RC(c);

    inserir_na_lista(l, cria_segmento(x, y - r, x, y + r, id));
    
    return l;
}

LISTA linha_para_segmentos(void* lin) {
    LISTA l = criar_lista();
    inserir_na_lista(l, cria_segmento(
        get_X1L(lin), get_Y1L(lin), 
        get_X2L(lin), get_Y2L(lin), 
        get_idL(lin)
    ));
    return l;
}

LISTA texto_para_segmentos(void* t) {
    LISTA l = criar_lista();
    float x = get_xT(t);
    float y = get_yT(t);
    
    char* conteudo = get_txtT(t);
    float largura = 0;
    if (conteudo) largura = strlen(conteudo) * 10.0;
    
    inserir_na_lista(l, cria_segmento(x, y, x + largura, y, get_idT(t)));
    return l;
}

float prod_vet(Ponto a, Ponto b, Ponto c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int intersectam(SEGMENTO s1, SEGMENTO s2) {
    StSegmento *a = (StSegmento*) s1;
    StSegmento *b = (StSegmento*) s2;

    float d1 = prod_vet(a->p1, a->p2, b->p1);
    float d2 = prod_vet(a->p1, a->p2, b->p2);
    float d3 = prod_vet(b->p1, b->p2, a->p1);
    float d4 = prod_vet(b->p1, b->p2, a->p2);

    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
        ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) {
        return 1;
    }
    return 0;
}