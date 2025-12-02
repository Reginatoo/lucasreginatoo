#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

typedef struct no{
    void* info;
    struct no* proximo;
    struct no* anterior;
} no;

typedef struct{
    no* inicio;
    no* fim;
    int tamanho;
} listastruct;

LISTA criar_lista(){
    listastruct* l=(listastruct*)malloc(sizeof(listastruct));
    if (l==NULL){
        printf ("erro de alocação na lista \n");
        exit(1);
    }
    l->inicio=NULL;
    l->fim=NULL;
    l->tamanho=0;
    return l;
}

POSIC inserir_na_lista(LISTA l, void* info){
    listastruct* f1= (listastruct*)l;
    no* novo_no = (no*) malloc(sizeof(no));
    if (novo_no == NULL) {
        printf("Erro de alocação no nó da lista\n");
        exit(1);
    }
    novo_no->info=info;
    novo_no->proximo=NULL;
    novo_no->anterior=f1->fim;

    if(f1->inicio==NULL){
        f1->inicio=novo_no;
    }else{
        f1->fim->proximo=novo_no;
    }
    f1->fim=novo_no;
    f1->tamanho++;
    return novo_no;
}

void* remover_da_lista(LISTA l, POSIC p){
    listastruct* f1= (listastruct*)l;
    no* no_removido = (no*)p;

    if(f1->inicio==NULL || no_removido==NULL){
        printf("não ha nada para remover ou posicao invalida\n");
        return NULL;
    }

    void* info_a_retornar=no_removido->info;
    if(no_removido == f1->inicio){
        f1->inicio = no_removido->proximo;
        if(f1->inicio != NULL)
            f1->inicio->anterior = NULL;
    } else {
        no_removido->anterior->proximo = no_removido->proximo;
    }

    if(no_removido == f1->fim){
        f1->fim = no_removido->anterior;
        if(f1->fim != NULL)
            f1->fim->proximo = NULL;
    } else {
        no_removido->proximo->anterior = no_removido->anterior;
    }

    free(no_removido);
    f1->tamanho--;
    return(info_a_retornar);
}

POSIC inserir_antes_do_no(LISTA l, POSIC p, void* info){
    listastruct* f1= (listastruct*)l;
    no* atual = (no*)p;

    if(atual == NULL || atual == f1->inicio){
        no* novo_no = (no*) malloc(sizeof(no));
        novo_no->info = info;
        novo_no->anterior = NULL;
        novo_no->proximo = f1->inicio;

        if(f1->tamanho == 0){
            f1->fim = novo_no;
        } else {
            f1->inicio->anterior = novo_no;
        }
        f1->inicio = novo_no;
        f1->tamanho++;
        return novo_no;
    }

    no* novo_no = (no*) malloc(sizeof(no));
    novo_no->info = info;
    novo_no->proximo = atual;
    novo_no->anterior = atual->anterior;

    atual->anterior->proximo = novo_no;
    atual->anterior = novo_no;
    f1->tamanho++;
    return novo_no;
}

POSIC inserir_depois_do_no(LISTA l, POSIC p, void* info){
    listastruct* f1= (listastruct*)l;
    no* atual = (no*)p;

    if(atual == f1->fim || f1->tamanho == 0){
        return inserir_na_lista(l, info);
    }

    no* novo_no = (no*) malloc(sizeof(no));
    novo_no->info = info;
    novo_no->anterior = atual;
    novo_no->proximo = atual->proximo;

    atual->proximo->anterior = novo_no;
    atual->proximo = novo_no;
    f1->tamanho++;
    return novo_no;
}

int lista_esta_vazia(LISTA l) {
    listastruct* f1 = (listastruct*)l;
    if (f1 == NULL || f1->inicio == NULL) {
        return 1; 
    } else {
        return 0; 
    }
}

int tamanho_lista(LISTA l) {
    listastruct* f1 = (listastruct*)l;
    if (f1 == NULL) {
        return 0;
    }
    return f1->tamanho; 
}

POSIC get_primeiro_no(LISTA l) {
    listastruct* lista = (listastruct*)l;
    return lista->inicio;
}

POSIC get_ultimo_no(LISTA l) {
    listastruct* lista = (listastruct*)l;
    return lista->fim;
}

POSIC get_proximo_no(LISTA l, POSIC p) {
    if(p == NULL) return NULL;
    return ((no*)p)->proximo;
}

POSIC get_anterior_no(LISTA l, POSIC p) {
    if(p == NULL) return NULL;
    return ((no*)p)->anterior;
}

void* get_info_do_no(LISTA l, POSIC p) {
    if(p == NULL) return NULL;
    return ((no*)p)->info;
}

void kill_lista(LISTA l, void (*destruir_info)(void*)) {
    listastruct* f1 = (listastruct*)l;
    
    no* no_atual = f1->inicio;
    while (no_atual != NULL) {
        no* no_a_remover = no_atual;
        void* info_a_libertar = no_a_remover->info;
        no_atual = no_a_remover->proximo;
        
        if (destruir_info != NULL && info_a_libertar != NULL) {
            destruir_info(info_a_libertar);
        }
        free(no_a_remover);
    }
    free(f1);
}