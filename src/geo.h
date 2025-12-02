#ifndef GEO_H
#define GEO_H

#include "lista.h"

/*
 * @brief Le um arquivo .geo e preenche a lista com as formas
 * @param caminho_geo Caminho completo para o arquivo
 * @param chao A lista ja criada onde as formas serao inseridas
 */
void ler_geo(char* caminho_geo, LISTA chao);

#endif