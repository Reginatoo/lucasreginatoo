#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circulo.h"
#include <math.h>
#define M_PI 3.14159265358979323846
typedef struct{
    char tipo;
    int id;
    float x, y, r;
    char *corb, *corp;
}circ;

CIRCULO cria_circulo(int id, float x, float y, float r, char* cb, char* cp){
circ *c = malloc(sizeof(circ));
    if (c == NULL) {
        printf("Erro na alocação de memória na criação do circulo");
        exit(1);
    }
    
    c->tipo = 'c';
    c->id = id;
    c->x = x;
    c->y = y;
    c->r = r;
    c->corb = strdup(cb);
     if(c->corb == NULL) {
        printf("Erro na alocação de memória para a cor de borda");
        exit(1);}
    c->corp = strdup(cp);
        if(c->corp == NULL) {
        printf("Erro na alocação de memória para a cor de preenchimento");
        exit(1);}
        return c;
}
 int get_idC(CIRCULO c){
     return ((circ*)c)->id;
}
float get_XC(CIRCULO c){
    return ((circ*)c)->x;
}

float get_YC(CIRCULO c){
     return ((circ*)c)->y;
}

float get_RC(CIRCULO c){
    return ((circ*)c)->r;
}

char* get_cbC(CIRCULO c){
     return ((circ*)c)->corb;
}

char* get_cpC(CIRCULO c){
     return ((circ*)c)->corp;
}

float get_areaC(CIRCULO c){
   return M_PI * ((circ*)c)->r * ((circ*)c)->r;
}
CIRCULO clone_circulo(CIRCULO c) {
    if (c == NULL) return NULL;
    return cria_circulo(
      get_idC(c),     
      get_XC(c),
      get_YC(c),
      get_RC(c),
      get_cbC(c),
      get_cpC(c)
    );
}
void set_XC(CIRCULO c, float x){
    ((circ*)c)->x = x;
}

void set_YC(CIRCULO c, float y){
    ((circ*)c)->y = y;
}

void set_RC(CIRCULO c, float r){
    ((circ*)c)->r = r;
}

void set_posicaoC(CIRCULO c, float x, float y) {
    circ* c1 = (circ*)c;
    
    c1->x = x;
    c1->y = y;
}
void set_cbC(CIRCULO c, const char* cb){
    circ* c1 = (circ*)c;
    free(c1->corb);
    c1->corb = strdup(cb);
     if(c1->corb == NULL) {
        printf("Erro na alocação de memória para a cor de borda");
        exit(1);}
    
}

void set_idC(CIRCULO c, int id){
   ((circ*)c)->id = id;
}

void set_cpC(CIRCULO c, const char* corp){
    circ* c1 = (circ*)c;
    free(c1->corp);
    c1->corp = strdup(corp);
     if(c1->corp == NULL) {
        printf("Erro na alocação de memória para a cor de preenchimento");
        exit(1);}
    
}

void kill_circ(CIRCULO c){
    circ* c1 = (circ*)c;
    if (c1 == NULL) {
        return;
    }
    free(c1->corb);
    free(c1->corp);
    free(c1);
}