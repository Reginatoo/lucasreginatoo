#ifndef SVG_H
#define SVG_H

#include "lista.h"

/**
 * @brief Gera o arquivo SVG desenhando todas as formas da lista
 * @param caminho_svg O nome/caminho do arquivo de saida
 * @param chao A lista contendo as formas
 */
void desenhar_svg(char* caminho_svg, LISTA chao);

#endif