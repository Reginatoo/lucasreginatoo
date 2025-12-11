#ifndef SVG_H
#define SVG_H

#include <stdio.h>
#include "lista.h"
#include "poligono.h"

/**
 * @brief Inicia o arquivo SVG 
 * @param caminho_svg Caminho do arquivo
 * @return Ponteiro para o arquivo
 */
FILE* iniciar_svg(char* caminho_svg, LISTA lista_para_zoom);

/**
 * @brief Fecha o aqr svg
 */
void finalizar_svg(FILE* svg);

/**
 * @brief Percorre a lista e desenha todas as formas
 */
void desenhar_lista_formas(FILE* svg, LISTA chao);

/**
 * @brief Desenha o polígono
 * @param p o polígono a ser desenhado
 * @param cor a cor de preenchimento
 * @param opacidade a opacidade
 */
void svg_desenha_poligono(FILE* svg, Poligono p, char* cor, float opacidade);


#endif