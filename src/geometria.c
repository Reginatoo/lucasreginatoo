#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> /* Para strlen */
#include "geometria.h"
#include "lista.h"

/* Headers para ler os dados das formas originais */
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

typedef struct {
    float x, y;
} Ponto;

/* Struct Segmento escondida aqui */
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

float get_seg_x1(SEGMENTO s){ 
    return ((StSegmento*)s)->p1.x;
 }
float get_seg_y1(SEGMENTO s) {
     return ((StSegmento*)s)->p1.y;
 }
float get_seg_x2(SEGMENTO s) { 
    return ((StSegmento*)s)->p2.x; 
}
float get_seg_y2(SEGMENTO s) {
     return ((StSegmento*)s)->p2.y; 
    }
int get_seg_id(SEGMENTO s) {
     return ((StSegmento*)s)->id_original; 
    }

void kill_segmento(SEGMENTO s) {
    if (s) free(s);
}

float distancia_pontos(float x1, float y1, float x2, float y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}