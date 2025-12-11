#ifndef ANTEPARO_H
#define ANTEPARO_H

typedef void* Anteparo;

/**
 * @brief Aloca um novo anteparo 
 * @param id id do anteparo
 * @param x1 x inicial
 * @param y1 y inicial
 * @param x2 x final
 * @param y2 y final
 * @return Ponteiro pro anteparo 
 */
Anteparo cria_anteparo(int id, float x1, float y1, float x2, float y2);

/**
 * @brief Getters das coordenadas
 * @param a o anteparo 
 * @return a coordenada solicitada
 */
float get_ant_x1(Anteparo a);
float get_ant_y1(Anteparo a);
float get_ant_x2(Anteparo a);
float get_ant_y2(Anteparo a);
int get_ant_id(Anteparo a);

/**
 * @brief Llimpa a estrutura da memória
 * @param a o anteparo 
 */
void kill_anteparo(Anteparo a);

#endif