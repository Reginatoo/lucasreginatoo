#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "lista.h"

int limite_insert = 10;

void faz_insertion(void** v, int n, int (*comp)(const void*, const void*)) {
    int i, j;
    void* aux;
    for (i = 1; i < n; i++) {
        aux = v[i];
        j = i - 1;
        while (j >= 0 && comp(v[j], aux) > 0) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = aux;
    }
}

void intercala(void** v, int ini, int meio, int fim, int (*comp)(const void*, const void*)) {
    int tam1 = meio - ini + 1;
    int tam2 = fim - meio;
    
    void** esq = malloc(tam1 * sizeof(void*));
    void** dir = malloc(tam2 * sizeof(void*));

    for (int i = 0; i < tam1; i++) esq[i] = v[ini + i];
    for (int j = 0; j < tam2; j++) dir[j] = v[meio + 1 + j];

    int i = 0, j = 0, k = ini;
    while (i < tam1 && j < tam2) {
        if (comp(esq[i], dir[j]) <= 0) {
            v[k] = esq[i];
            i++;
        } else {
            v[k] = dir[j];
            j++;
        }
        k++;
    }

    while (i < tam1) {
        v[k] = esq[i];
        i++; k++;
    }
    while (j < tam2) {
        v[k] = dir[j];
        j++; k++;
    }
    
    free(esq);
    free(dir);
}

void msort(void** v, int ini, int fim, int (*comp)(const void*, const void*)) {
    if (ini < fim) {
        if ((fim - ini + 1) <= limite_insert) {
            faz_insertion(&v[ini], fim - ini + 1, comp);
        } else {
            int meio = ini + (fim - ini) / 2;
            msort(v, ini, meio, comp);
            msort(v, meio + 1, fim, comp);
            intercala(v, ini, meio, fim, comp);
        }
    }
}

void** lista_p_vetor(LISTA l, int n) {
    void** v = malloc(n * sizeof(void*));
    POSIC p = get_primeiro_no(l);
    for(int i = 0; i < n; i++) {
        v[i] = get_info_do_no(l, p);
        p = get_proximo_no(l, p);
    }
    return v;
}

void vetor_p_lista(LISTA l, void** v, int n) {
    while(!lista_esta_vazia(l)) {
        remover_da_lista(l, get_primeiro_no(l));
    }
    for(int i = 0; i < n; i++) {
        inserir_na_lista(l, v[i]);
    }
}

int (*cmp_tmp)(const void*, const void*);

int qsort_helper(const void* a, const void* b) {
    return cmp_tmp(*(const void**)a, *(const void**)b);
}

void ordenar_lista_qsort(LISTA l, int (*comp)(const void* a, const void* b)) {
    int n = tamanho_lista(l);
    if (n < 2) return;

    void** v = lista_p_vetor(l, n);
    
    cmp_tmp = comp;
    qsort(v, n, sizeof(void*), qsort_helper);

    vetor_p_lista(l, v, n);
    free(v);
}

void ordenar_lista_mergesort(LISTA l, int (*comp)(const void* a, const void* b)) {
    int n = tamanho_lista(l);
    if (n < 2) return;

    void** v = lista_p_vetor(l, n);

    msort(v, 0, n - 1, comp);

    vetor_p_lista(l, v, n);
    free(v);
}