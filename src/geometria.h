#ifndef GEOMETRIA_H
#define GEOMETRIA_H
#include "lista.h"

typedef void* SEGMENTO;

/**
 * @brief cria um segmento de reta entre dois pontos e guarda o id da forma original
 * @param x1 coordenada x inicial
 * @param y1 coordenada y inicial
 * @param x2 coordenada x final
 * @param y2 coordenada y final
 * @param id id da forma que gerou o segmento
 * @return ponteiro para o segmento criado
 */
SEGMENTO cria_segmento(float x1, float y1, float x2, float y2, int id);

/* Getters para os dados dos segmentos */
float get_seg_x1(SEGMENTO s);
float get_seg_y1(SEGMENTO s);
float get_seg_x2(SEGMENTO s);
float get_seg_y2(SEGMENTO s);
int get_seg_id(SEGMENTO s);


/**
 * @brief calcula a distancia entre dois pontos
 * @param x1 coordenada x inicial
 * @param y1 coordenada y inicial
 * @param x2 coordenada x final
 * @param y2 coordenada y final
 */
float distancia_pontos(float x1, float y1, float x2, float y2);

/**
 * @brief verifica se dois segmentos se intersectam
 * @param s1 primeiro segmento
 * @param s2 segundo segmento
 * @return 1 se houver interseccao, 0 caso contrario
 */
int intersectam(SEGMENTO s1, SEGMENTO s2);

/**
 * @brief converte um circulo em uma lista de segmentos
 * @param circulo o circulo original
 * @return lista contendo os segmentos gerados
 */
LISTA circulo_para_segmentos(void* circulo);

/**
 * @brief converte um retangulo em uma lista de segmentos 
 * @param retangulo o retangulo original
 * @return lista contendo os segmentos gerados
 */
LISTA retangulo_para_segmentos(void* retangulo);

/**
 * @brief converte uma linha em uma lista de segmentos
 * @param linha a linha original
 * @return lista contendo o segmento gerado
 */
LISTA linha_para_segmentos(void* linha);

/**
 * @brief converte um texto em uma lista de segmentos
 * @param texto o texto original
 * @return lista contendo o segmento gerado
 */
LISTA texto_para_segmentos(void* texto);

/**
 * @brief destroi a estrutura do segmento
 * @param s o segmento a ser liberado
 */
void kill_segmento(SEGMENTO s);


#endif