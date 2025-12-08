#include <stdlib.h>
#include <float.h>
#include "poligono.h"

typedef struct {
    float x, y;
} Ponto;
typedef struct {
    Ponto* vertices;
    int qtd;
    int cap;
} StPoligono;

Poligono cria_poligono() {
    StPoligono* pol = (StPoligono*) malloc(sizeof(StPoligono));
    if (pol) {
        pol->qtd = 0;
        pol->cap = 100;
        pol->vertices = (Ponto*) malloc(pol->cap * sizeof(Ponto));
    }
    return (Poligono) pol;
}
void insere_vertice(Poligono p, float x, float y) {
    StPoligono* pol = (StPoligono*) p;
    if (!pol) return;
    if (pol->qtd == pol->cap) {
        pol->cap *= 2;
        pol->vertices = (Ponto*) realloc(pol->vertices, pol->cap * sizeof(Ponto));
    }
    if (pol->vertices) {
        pol->vertices[pol->qtd].x = x;
        pol->vertices[pol->qtd].y = y;
        pol->qtd++;
    }
}

int ponto_dentro_poligono(Poligono p, float x, float y) {
    StPoligono* pol = (StPoligono*) p;
    if (!pol) return 0;
    int i, j;
    int dentro = 0;
    int n = pol->qtd;
    for (i = 0, j = n - 1; i < n; j = i++) {
        if (((pol->vertices[i].y > y) != (pol->vertices[j].y > y)) &&
            (x < (pol->vertices[j].x - pol->vertices[i].x) * (y - pol->vertices[i].y) / 
                 (pol->vertices[j].y - pol->vertices[i].y) + pol->vertices[i].x)) {
            dentro = !dentro;
        }
    }
    return dentro;
}

void get_limites(Poligono p, float *min_x, float *min_y, float *max_x, float *max_y) {
    StPoligono* pol = (StPoligono*) p;
    if (!pol || pol->qtd == 0) return;

    *min_x = FLT_MAX;
    *min_y = FLT_MAX;
    *max_x = -FLT_MAX;
    *max_y = -FLT_MAX;

    for (int i = 0; i < pol->qtd; i++) {
        if (pol->vertices[i].x < *min_x) *min_x = pol->vertices[i].x;
        if (pol->vertices[i].y < *min_y) *min_y = pol->vertices[i].y;
        if (pol->vertices[i].x > *max_x) *max_x = pol->vertices[i].x;
        if (pol->vertices[i].y > *max_y) *max_y = pol->vertices[i].y;
    }
}

int get_qtd_vertices(Poligono p) {
    StPoligono* pol = (StPoligono*) p;
    if (!pol) return 0;
    return pol->qtd;
}

int get_vertice(Poligono p, int indice, float *x, float *y) {
    StPoligono* pol = (StPoligono*) p;
    if (!pol || indice < 0 || indice >= pol->qtd) return 0;

    *x = pol->vertices[indice].x;
    *y = pol->vertices[indice].y;
    return 1;
}

void libera_poligono(Poligono p) {
    StPoligono* pol = (StPoligono*) p;
    if (pol) {
        if (pol->vertices) free(pol->vertices);
        free(pol);
    }
}