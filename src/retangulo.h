#ifndef retangulo_h
#define retangulo_h
    
    typedef void* RETANGULO;

    /**
     * @brief função para criar p retangulo
     * @param id ID do retangulo
     * @param x coordenada x do retangulo
     * @param y coordenada y do retangulo
     * @param w largura do retangulo
     * @param h altura do retangulo
     * @param cb cor da borda do retangulo
     * @param cp cor de dentro do retangulo
     */

    RETANGULO cria_retangulo(int id, float x, float y, float w, float h, char* cb, char* cp);
    /**
 * @brief obtem o ID do retangulo
 * @param r o retangulo a ser consultado
 * @return int o valor do ID do retangulo
 */
int get_idR(RETANGULO r);

/**
 * @brief obtem a coordenada x do retangulo
 * @param r o retangulo a ser consultado
 * @return float o valor da coordenada x do retangulo
 */
float get_XR(RETANGULO r);

/**
 * @brief obtem a coordenada y do retangulo
 * @param r o retangulo a ser consultado
 * @return float o valor da coordenada y do retangulo
 */
float get_YR(RETANGULO r);

/**
 * @brief Define a nova posição da âncora do retângulo.
 * @param r O retângulo a ser modificado
 * @param x A nova coordenada x do canto
 * @param y A nova coordenada y do canto
 */
void set_posicaoR(RETANGULO r, float x, float y);

/**
 * @brief Cria e retorna um novo retângulo que é uma cópia exata do original
 * @param r O retângulo a ser clonado
 * @return Um ponteiro para o novo retângulo
 */
RETANGULO clone_retangulo(RETANGULO r);

/**
 * @brief obtem a largura do retangulo
 * @param r o retangulo a ser consultado
 * @return float o valor da largura do retangulo
 */
float get_WR(RETANGULO r);

/**
 * @brief obtem a altura do retangulo
 * @param r o retangulo a ser consultado
 * @return float o valor da altura do retangulo
 */
float get_HR(RETANGULO r);

/**
 * @brief obtem a cor da borda do retangulo
 * @param r o retangulo a ser consultado
 * @return float o valor da cor da borda do retangulo
 */
char* get_cbR(RETANGULO r);

/**
 * @brief obtem a cor de dentro do retangulo
 * @param r o retangulo a ser consultado
 * @return float o valor da cor de dentro do retangulo
 */
char* get_cpR(RETANGULO r);

float get_areaR(RETANGULO r);

/**
 * @brief atualiza o id do retangulo.
 * @param r o retangulo a ser consultado
 * @param id o novo valor para o id do retangulo
 */
void set_idR(RETANGULO r, int id);

/**
 * @brief atualiza a coordenada x do retangulo.
 * @param r o retangulo a ser consultado
 * @param x o novo valor para coordenada x
 */
void set_XR(RETANGULO r, float x);

/**
 * @brief atualiza a coordenada y do retangulo.
 * @param r o retangulo a ser consultado
 * @param y o novo valor para coordenada y 
 */
void set_YR(RETANGULO r, float y);

/**
 * @brief atualiza a largura do retangulo.
 * @param r o retangulo a ser consultado.
 * @param w o novo valor para a largura.
 */
void set_WR(RETANGULO r, float w);

/**
 * @brief atualiza a altura do retangulo.
 * @param r o retangulo a ser consultado.
 * @param h o novo valor para a altura.
 */
void set_HR(RETANGULO r, float h);

/**
 * @brief atualiza a cor da borda do retangulo
 * @param r o retangulo a ser consultado
 * @param cb o nova string da cor da borda do retangulo
 */
void set_cbR(RETANGULO r, const char* cb);

/**
 * @brief atualiza a cor de dentro do retangulo
 * @param r o retangulo a ser consultado.
 * @param cp a nova string da cor de dentro do retangulo.
 */
void set_cpR(RETANGULO r, const char* cp);

/**
 * @brief destroi a estrutura do retangulo e libera a memoria
 * @param r o retangulo a ser consultado
 */
void kill_retang(RETANGULO r);

#endif