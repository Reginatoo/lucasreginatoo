#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retangulo.h"
#include <math.h>
typedef struct{
    char tipo;
    int id;
    float x, y, w, h;
    char *corb, *corp;
}retang;

RETANGULO cria_retangulo(int id, float x, float y, float w, float h, char* cb, char* cp){
retang *r = malloc(sizeof(retang));
    if (r == NULL) {
        printf("Erro na alocação de memória na criação do retangulo");
        exit(1);
    }
    
    r->tipo = 'r';
    r->id = id;
    r->x = x;
    r->y = y;
    r->w = w;
    r->h = h;
    r->corb = strdup(cb);
     if(r->corb == NULL) {
        printf("Erro na alocação de memória para a cor de borda");
        exit(1);}
    r->corp = strdup(cp);
        if(r->corp == NULL) {
        printf("Erro na alocação de memória para a cor de preenchimento");
        exit(1);}
        return r;
}
 int get_idR(RETANGULO r){
     return ((retang*)r)->id;
}
float get_XR(RETANGULO r){
    return ((retang*)r)->x;
}

float get_YR(RETANGULO r){
     return ((retang*)r)->y;
}

float get_WR(RETANGULO r){
    return ((retang*)r)->w;
}
float get_HR(RETANGULO r){
    return ((retang*)r)->h;
}

char* get_cbR(RETANGULO r){
     return ((retang*)r)->corb;
}

char* get_cpR(RETANGULO r){
     return ((retang*)r)->corp;
}
RETANGULO clone_retangulo(RETANGULO r) {
    if (r == NULL) return NULL;
    
    return cria_retangulo(
        get_idR(r),
        get_XR(r),
        get_YR(r),
        get_WR(r),
        get_HR(r),
        get_cbR(r),
        get_cpR(r) 
    );
}

void set_posicaoR(RETANGULO r, float x, float y) {
    retang* r1 = (retang*)r;

    r1->x = x;
    r1->y = y;
}

float get_areaR(RETANGULO r){
   return ((retang*)r)->h * ((retang*)r)->w;
}
void set_XR(RETANGULO r, float x){
    ((retang*)r)->x = x;
}

void set_YR(RETANGULO r, float y){
    ((retang*)r)->y = y;
}

void set_WR(RETANGULO r, float w){
    ((retang*)r)->w = w;
}

void set_HR(RETANGULO r, float h){
    ((retang*)r)->h = h;
}

void set_cbR(RETANGULO r, const char* cb){
    retang* r1 = (retang*)r;
    free(r1->corb);
    r1->corb = strdup(cb);
     if(r1->corb == NULL) {
        printf("Erro na alocação de memória para a cor de borda");
        exit(1);}
    
}

void set_idR(RETANGULO r, int id){
   ((retang*)r)->id = id;
}

void set_cpR(RETANGULO r, const char* corp){
    retang* r1 = (retang*)r;
    free(r1->corp);
    r1->corp = strdup(corp);
     if(r1->corp == NULL) {
        printf("Erro na alocação de memória para a cor de preenchimento");
        exit(1);}
    
}

void kill_retang(RETANGULO r){
    retang* r1 = (retang*)r;
    if (r1 == NULL) {
        return;
    }
    free(r1->corb);
    free(r1->corp);
    free(r1);
}