#ifndef linha_h

#define linha_h
#include <math.h>

typedef void* LINHA;

/**
 * @brief cria e retorna uma linha
 * @param i ID da linha
 * @param x1 primeiro ponto x da linha
 * @param y1 primeiro ponto y da linha
 * @param x2 ultimo ponto x da linha
 * @param y2 ultimo ponto y da linha
 * @param c cor da linha
 * @return Retorna um ponteiro do tipo void para essa estrutura
 */

 LINHA cria_linha(int i, float x1, float y1, float x2, float y2, char* c);



/**
 * @brief Define a nova posição da âncora da linha
 * @param l A linha a ser modificada
 * @param x A nova coordenada x para o ponto 1
 * @param y A nova coordenada y para o ponto 1
 */
void set_posicaoL(LINHA l, float x, float y);


/**
 * @brief obtem o id do linha
 * @param l a linha do qual será obtida o id
 * @return O id da linha
*/
int get_idL (LINHA l);

/**
 * @brief obtem o valor da coordenada x1 do linha
 * @param l A linha do qual será obtida a coordenada x1
 * @return A coordenada x1 da linha
*/
float get_X1L(LINHA l);

/**
 * @brief obtem o valor da coordenada x2 do linha
 * @param l A linha do qual será obtida a coordenada x2
 * @return A coordenada x2 da linha  
*/
float get_X2L(LINHA l);

/**
 * @brief obtem o valor da coordenada y1 do linha
 * @param l A linha do qual será obtida a coordenada y1
 * @return A coordenada y1 da linha
*/
float get_Y1L(LINHA l);

/**
 * @brief obtem o valor da coordenada y2 do linha
 * @param l A linha do qual será obtida a coordenada y2
 * @return A coordenada y2 da linha
*/
float get_Y2L(LINHA l);

/**
 * @brief Calcula a área da linha
 * @param l A linha da qual a área será calculada
 * @return O valor da área da linha
*/
float get_areaL(LINHA l);
/**
 * @brief obtem a cor de preenchimento da linha
 * @param l A linha do qual será obtida a cor de preenchimento
 * @return Uma string com a cor de preenchimento da linha
 *
*/
char *get_CorL(LINHA l);

/**
 * @brief Cria e retorna uma nova linha que é uma cópia exata do original
 * @param l A linha a ser clonada
 * @return Um ponteiro para a nova linha
 */
LINHA clone_linha(LINHA l);

/**
 * @brief altera a coordenada x da linha
 * @param l O objeto linha cujo valor de x será atualizado
 * @param x Novo valor a ser atribuído à coordenada x
*/

void set_X1L(LINHA l, float x);

/**
 * @brief altera a coordenada x2 da linha
 * @param l O objeto linha cujo valor de x2 será atualizado
 * @param x2 Novo valor a ser atribuído à coordenada x2
*/

void set_X2L(LINHA l, float x2);

/**
 * @brief altera a coordenada y da linha
 * @param l O objeto linha cujo valor de y será atualizado
 * @param y Novo valor a ser atribuído à coordenada y
*/

void set_Y1L(LINHA l, float y);

/**
 * @brief altera a coordenada y2 da linha
 * @param l O objeto linha cujo valor de y2 será atualizado
 * @param y2 Novo valor a ser atribuído à coordenada y2
*/

void set_Y2L(LINHA l, float y2);

/**
 * @brief altera a cor da linha
 * @param l O objeto linha cujo a cor será atualizado
 * @param cor Novo valor a ser atribuído à cor
*/
void set_CorL(LINHA l, char *cor);

/**
 * @brief atualiza o id da linha
 * @param l a linha a ser consultada
 * @param id o novo valor para o id
 */
void set_idL(LINHA l, int id);

/**
 * @brief destroi a estrutura da linha e libera a memoria
 * @param l a linha a ser consultada
 */
void kill_linha(LINHA l);

#endif