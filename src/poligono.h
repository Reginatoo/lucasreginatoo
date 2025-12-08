#ifndef POLIGONO_H
#define POLIGONO_H
typedef void* Poligono;

/**
 * @brief Cria um novo polígono 
 * @return Ponteiro para o polígono 
 */
Poligono cria_poligono();

/**
 * @brief Adiciona um vértice ao polígono
 * @param p O polígono alvo
 * @param x Coordenada X do vértice
 * @param y Coordenada Y do vértice
 */
void insere_vertice(Poligono p, float x, float y);

/**
 * @brief Verifica se um ponto está dentro do polígono
 * @param p O polígono
 * @param x Coordenada X do ponto 
 * @param y Coordenada Y do ponto 
 */
int ponto_dentro_poligono(Poligono p, float x, float y);

/**
 * @brief Calcula o retângulo do polígono
 * @param p O polígono
 * @param min_x Ponteiro para receber o menor x
 * @param min_y Ponteiro para receber o menor y
 * @param max_x Ponteiro para receber o maior x
 * @param max_y Ponteiro para receber o maior y
 */
void get_limites(Poligono p, float *min_x, float *min_y, float *max_x, float *max_y);

/**
 * @brief Retorna a quantidade de vértices armazenados
 */
int get_qtd_vertices(Poligono p);

/**
 * @brief pega um vértice específico
 * @param p O polígono
 * @param indice O índice do vértice
 * @param x Ponteiro para receber o X
 * @param y Ponteiro para receber o Y
 */
int get_vertice(Poligono p, int indice, float *x, float *y);

/**
 * @brief Libera toda a memória alocada para o polígono
 */
void kill_poligono(Poligono p);

#endif