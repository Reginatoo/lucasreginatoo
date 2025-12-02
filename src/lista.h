#ifndef LISTA_H
#define LISTA_H

typedef void* LISTA;
typedef void* POSIC;

/**
 * @brief cria uma nova lista vazia
 * @return retorna ponteiro para nova lista criada
 */
LISTA criar_lista();

/**
 * @brief insere um novo elemento no final da lista
 * @param l a lista onde sera inserido
 * @param info a informacao a ser inserida
 * @return O identificador da posicao (POSIC) onde foi inserido
 */
POSIC inserir_na_lista(LISTA l, void* info);

/**
 * @brief insere um novo elemento logo apos uma posicao especifica
 * @param l a lista onde sera inserido
 * @param p a posicao de referencia
 * @param info a informacao a ser inserida
 * @return O identificador da nova posicao
 */
POSIC inserir_depois_do_no(LISTA l, POSIC p, void* info);

/**
 * @brief insere um novo elemento logo antes de uma posicao especifica
 * @param l a lista onde sera inserido
 * @param p a posicao de referencia
 * @param info a informacao a ser inserida
 * @return O identificador da nova posicao
 */
POSIC inserir_antes_do_no(LISTA l, POSIC p, void* info);

/**
 * @brief remove um elemento especifico da lista
 * @param l a lista a ser alterada
 * @param p a posicao do elemento a ser removido
 * @return O ponteiro para a informacao que estava guardada la
 */
void* remover_da_lista(LISTA l, POSIC p);

/**
 * @brief obtem o primeiro no da lista
 * @param l a lista a ser consultada
 * @return O identificador da posicao do primeiro elemento
 */
POSIC get_primeiro_no(LISTA l);

/**
 * @brief obtem o ultimo no da lista
 * @param l a lista a ser consultada
 * @return O identificador da posicao do ultimo elemento
 */
POSIC get_ultimo_no(LISTA l);

/**
 * @brief obtem o proximo no em relacao a um no informado
 * @param l a lista a ser consultada
 * @param p a posicao atual
 * @return O identificador da proxima posicao
 */
POSIC get_proximo_no(LISTA l, POSIC p);

/**
 * @brief obtem o no anterior em relacao a um no informado
 * @param l a lista a ser consultada
 * @param p a posicao atual
 * @return O identificador da posicao anterior
 */
POSIC get_anterior_no(LISTA l, POSIC p);

/**
 * @brief obtem a informacao guardada no no
 * @param l a lista a ser consultada
 * @param p a posicao a ser consultada
 * @return retorna o ponteiro da informacao guardada
 */
void* get_info_do_no(LISTA l, POSIC p);

/**
 * @brief Verifica se a lista esta vazia
 * @param l A lista a ser verificada
 * @return Retorna 1 se estiver vazia, 0 caso contrario
 */
int lista_esta_vazia(LISTA l);

/**
 * @brief Obtem o numero de elementos na lista
 * @param l A lista a ser consultada
 * @return O numero de elementos
 */
int tamanho_lista(LISTA l);

/**
 * @brief Destroi a lista e seus nos
 * @param l A lista a ser destruida
 * @param destruir_info Funcao opcional para liberar a memoria da informacao 
 */
void kill_lista(LISTA l, void (*destruir_info)(void*));

#endif