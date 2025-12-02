#ifndef circulo_h
#define circulo_h
#include <math.h>
typedef void* CIRCULO; 
/** 
* @brief criar uma estrutura de circulo com os seguintes parametros fornecidos
*@param id ID do circulo
*@param x coordenada x do circulo
*@param y coordenada y do circulo
*@param r raio do circulo
*@param cb cor da borda do circulo
*@param cp cor de dentro do circulo
*@return é retornado um ponteiro pelo CIRCULO para a estrutura de circulo criada
*/
CIRCULO cria_circulo(int id, float x, float y, float r, char* cb, char* cp);

/**
 * @brief obtem o ID do circulo
 * @param c o circulo a ser consultado
 * @return int o valor do ID do circulo
 */
int get_idC(CIRCULO c);

/**
 * @brief obtem a coordenada x do circulo
 * @param c o circulo a ser consultado
 * @return float o valor da coordenada x do centro do circulo
 */
float get_XC(CIRCULO c);

/**
 * @brief obtem a coordenada y do circulo
 * @param c o circulo a ser consultado
 * @return float o valor da coordenada y do centro do circulo
 */
float get_YC(CIRCULO c);

/**
 * @brief obtem o raio do circulo
 * @param c o circulo a ser consultado
 * @return float o valor do raio do circulo
 */
float get_RC(CIRCULO c);

/**
 * @brief obtem a cor da borda do circulo
 * @param c o circulo a ser consultado
 * @return float o valor da cor da borda do circulo
 */
char* get_cbC(CIRCULO c);

/**
 * @brief obtem a cor de dentro do circulo
 * @param c o circulo a ser consultado
 * @return float o valor da cor de dentro do circulo
 */
char* get_cpC(CIRCULO c);

 /**
 * @brief Calcula a área do círculo
 * @param c O círculo a ser consultado
 * @return A área do círculo
 */

 float get_areaC(CIRCULO c);
/**
 * @brief clona o circulo
 * @param o circulo a ser consultado
 */
 CIRCULO clone_circulo(CIRCULO c);

/**
 * @brief atualiza o id do círculo.
 * @param c o circulo a ser consultado
 * @param id o novo valor para o id do circulo
 */
void set_idC(CIRCULO c, int id);

/**
 * @brief Define a nova posição da âncora do círculo
 * @param c O círculo a ser modificado
 * @param x A nova coordenada x do centro
 * @param y A nova coordenada y do centro
 */
void set_posicaoC(CIRCULO c, float x, float y);

/**
 * @brief atualiza a coordenada x do centro do círculo.
 * @param c o circulo a ser consultado
 * @param x o novo valor para coordenada x
 */
void set_XC(CIRCULO c, float x);

/**
 * @brief atualiza a coordenada y do centro do círculo.
 * @param c o circulo a ser consultado
 * @param y o novo valor para coordenada y 
 */
void set_YC(CIRCULO c, float y);

/**
 * @brief atualiza o raio do círculo.
 * @param c o circulo a ser consultado
 * @param r o novo valor para o raio
 */
void set_RC(CIRCULO c, float r);

/**
 * @brief atualiza a cor da borda do circulo
 * @param c o circulo a ser consultado
 * @param cb a nova string para a cor da borda do circulo
 */
void set_cbC(CIRCULO c, const char* cb);

/**
 * @brief atualiza a cor de dentro do circulo
 * @param c o circulo a ser consultado
 * @param cp a nova string para a cor de dentro do circulo
 */
void set_cpC(CIRCULO c, const char* cp);

/**
 * @brief destroi a estrutura do circulo e libera a memoria
 * @param c o circulo a ser consultado
 */
void kill_circ(CIRCULO c);

#endif