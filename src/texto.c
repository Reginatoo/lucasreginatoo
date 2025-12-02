#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "texto.h"
#include <math.h>
typedef struct{
    char tipo;
    int id;
    float x, y;
    char *corb, *corp, *txt, *familia, *peso, *tam;
    char a;
}text;

TEXTO cria_texto(int id, float x, float y, char* cb, char* cp, char a, char* txt, char* familia_atual, char* peso_atual, char* tam_atual){
text *t = malloc(sizeof(text));
    if (t == NULL) {
        printf("Erro na alocação de memória na criação do texto");
        exit(1);
    }
    
    t->tipo = 't';
    t->id = id;
    t->x = x;
    t->y = y;
    t->a = a;
    t->txt = strdup(txt);
     if(t->txt == NULL) {
        printf("Erro na alocação de memória para o conteudo do texto");
        exit(1);}
    t->corp = strdup(cp);
        if(t->corp == NULL) {
        printf("Erro na alocação de memória para a cor de preenchimento");
        exit(1);}
        t->corb = strdup(cb);
        if(t->corb == NULL) {
        printf("Erro na alocação de memória para a cor da borda");
        exit(1);}

        t->familia = strdup(familia_atual);
        t->peso = strdup(peso_atual);
        t->tam = strdup(tam_atual);
    return t;
    }
    int get_idT(TEXTO t){
     return ((text*)t)->id;
}
float get_xT(TEXTO t){
    return ((text*)t)->x;
}

float get_yT(TEXTO t){
     return ((text*)t)->y;
}

void set_posicaoT(TEXTO t, float x, float y) {
    text* t1 = (text*)t;
    t1->x = x;
    t1->y = y;
}

char get_aT(TEXTO t){
    return ((text*)t)->a;
}
char* get_txtT(TEXTO t){
    return ((text*)t)->txt;
}

char* get_cbT(TEXTO t){
     return ((text*)t)->corb;
}

char* get_cpT(TEXTO t){
     return ((text*)t)->corp;
}

TEXTO clone_texto(TEXTO t) {
    if (t == NULL) return NULL;

    return cria_texto(
        get_idT(t),
        get_xT(t),
        get_yT(t),
        get_cbT(t),
        get_cpT(t),
        get_aT(t),
        get_txtT(t),
        get_familiaT(t),
        get_pesoT(t),
        get_tamT(t)
    );
}

float get_areaT(TEXTO t){
    return strlen(((text*)t)->txt) * 20.0;
}
char* get_familiaT(TEXTO t) {
     return ((text*)t)->familia;
     }
char* get_pesoT(TEXTO t) { 
    return ((text*)t)->peso;
 }
char* get_tamT(TEXTO t) { 
    return ((text*)t)->tam;
}

void set_xT(TEXTO t, float x){
    ((text*)t)->x = x;
}

void set_yT(TEXTO t, float y){
    ((text*)t)->y = y;
}

void set_cbT(TEXTO t, const char* cb){
    text* t1 = (text*)t;
    free(t1->corb);
    t1->corb = strdup(cb);
     if(t1->corb == NULL) {
        printf("Erro na alocação de memória para a cor de borda");
        exit(1);}
    
}

void set_idT(TEXTO t, int id){
   ((text*)t)->id = id;
}

void set_cpT(TEXTO t, const char* corp){
    text* t1 = (text*)t;
    free(t1->corp);
    t1->corp = strdup(corp);
     if(t1->corp == NULL) {
        printf("Erro na alocação de memória para a cor de preenchimento");
        exit(1);}
     }
void kill_texto(TEXTO t) {
    text* t1 = (text*)t;
    if (t == NULL) {
        return;
    }
    free(t1->corb);
    free(t1->corp);
    free(t1->txt);
    free(t1->familia);
    free(t1->peso);
    free(t1->tam);
    free(t);
}
