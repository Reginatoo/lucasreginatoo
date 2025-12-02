#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linha.h"
#include <math.h>
typedef struct{
    char tipo;
    int id;
    float x1, y1, x2, y2;
    char *cor;
}lin;

LINHA cria_linha(int id,  float x1, float y1, float x2, float y2, char* cor){
lin *l = malloc(sizeof(lin));
    if (l == NULL) {
        printf("Erro na alocação de memória na criação do linha");
        exit(1);
    }
    
    l->tipo = 'l';
    l->id = id;
    l->x1 = x1;
    l->y1 = y1;
    l->x2 = x2;
    l->y2 = y2;
    l->cor = strdup(cor);
     if(l->cor == NULL) {
        printf("Erro na alocação de memória para a cor");
        exit(1);}
    
        return l;
}
 int get_idL(LINHA l){
     return ((lin*)l)->id;
}
float get_X1L(LINHA l){
    return ((lin*)l)->x1;
}

float get_Y1L(LINHA l){
     return ((lin*)l)->y1;
}

float get_X2L(LINHA l){
    return ((lin*)l)->x2;
}
float get_Y2L(LINHA l){
    return ((lin*)l)->y2;
}

char* get_CorL(LINHA l){
     return ((lin*)l)->cor;
}
float get_areaL(LINHA l) {
    lin* l1 = (lin*)l;
    float dx = l1->x1 - l1->x2;
    float dy = l1->y1 - l1->y2;
    float comprimento = sqrt((dx*dx) + (dy*dy));
    return 2.0 * comprimento;
}
LINHA clone_linha(LINHA l) {
    if (l == NULL) return NULL;

    return cria_linha(
        get_idL(l),
        get_X1L(l),
        get_Y1L(l),
        get_X2L(l),
        get_Y2L(l),
        get_CorL(l)
    );
}
void set_X1L(LINHA l, float x1){
    ((lin*)l)->x1 = x1;
}
void set_X2L(LINHA l, float x2){
    ((lin*)l)->x2 = x2;
}

void set_Y1L(LINHA l, float y1){
    ((lin*)l)->y1 = y1;
}
void set_Y2L(LINHA l, float y2){
    ((lin*)l)->y2 = y2;
}

void set_CorL(LINHA l, char* c){
    lin* c1 = (lin*)l;
    free(c1->cor);
    c1->cor = strdup(c);
     if(c1->cor == NULL) {
        printf("Erro na alocação de memória para a cor");
        exit(1);}
    
}
void set_posicaoL(LINHA l, float x, float y) {
    lin* l1 = (lin*)l;
    
    float delta_x = l1->x2 - l1->x1;
    float delta_y = l1->y2 - l1->y1;
    l1->x1 = x;
    l1->y1 = y;
    l1->x2 = x + delta_x;
    l1->y2 = y + delta_y;
}

void set_idL(LINHA l, int id){
   ((lin*)l)->id = id;
}

void kill_linha(LINHA c){
    lin* c1 = (lin*)c;
    if (c1 == NULL) {
        return;
    }
    free(c1->cor);
    free(c1);
}