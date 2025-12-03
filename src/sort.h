#ifndef SORT_H
#define SORT_H

#include "lista.h"

/**
 * @brief Ordena a lista usando QuickSort
 * @param l a lista a ser ordenada
 * @param comparar ponteiro para a funcao que define a ordem 
 */
void ordenar_lista_qsort(LISTA l, int (*comparar)(const void* a, const void* b));

/**
 * @brief Ordena a lista usando MergeSort
 * @param l a lista a ser ordenada
 * @param comparar ponteiro para a funcao que define a ordem
 */
void ordenar_lista_mergesort(LISTA l, int (*comparar)(const void* a, const void* b));

#endif