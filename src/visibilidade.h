#ifndef VISIBILIDADE_H
#define VISIBILIDADE_H

#include "poligono.h"
#include "lista.h" 

/**
 * @brief Calcula o polígono de visibilidade 
 * @param x_bomba Coordenada X da explosão
 * @param y_bomba Coordenada Y da explosão
 * @param lista_anteparos Lista contendo os segmentos
 */
Poligono calcular_visibilidade(float x_bomba, float y_bomba, LISTA lista_anteparos);

#endif