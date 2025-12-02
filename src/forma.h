#ifndef FORMA_H
#define FORMA_H

#include <stdio.h>
#include "lista.h"

typedef void* form;

/**
 * @brief pega o tipo da forma olhando pro primeiro byte da estrutura
 * @param forma o ponteiro generico da forma
 * @return retorna c, r, l ou t dependendo do que for
 */
char get_tipo_da_forma(void* forma);

/**
 * @brief procura na lista inteira uma forma que tenha esse id especifico
 * @param f a lista onde a gente vai procurar
 * @param id o numero do id que estamos buscando
 * @return retorna o ponteiro pra forma se achar, ou NULL se nao achar nada
 */
void* encontrar_forma_por_id(LISTA f, int id);

/**
 * @brief descobre o id da forma nao importa qual tipo ela seja
 * @param forma o ponteiro pra forma
 * @return o valor do id
 */
int get_id_da_forma(void* forma);

/**
 * @brief calcula a area da forma, se for linha ou texto retorna 0
 * @param forma o ponteiro pra forma
 * @return o valor da area calculada
 */
float get_area_da_forma(void* forma);

/**
 * @brief pega a coordenada x da ancora da forma
 * @param forma o ponteiro pra forma
 * @return o valor de x
 */
float get_x_da_forma(void* forma);

/**
 * @brief pega a coordenada y da ancora da forma
 * @param forma o ponteiro pra forma
 * @return o valor de y
 */
float get_y_da_forma(void* forma);

/**
 * @brief pega a cor da borda da forma
 * @param forma o ponteiro pra forma
 * @return a string com a cor da borda
 */
char* get_corb_da_forma(void* forma);

/**
 * @brief pega a cor de preenchimento da forma
 * @param forma o ponteiro pra forma
 * @return a string com a cor de dentro
 */
char* get_corp_da_forma(void* forma);

/**
 * @brief atualiza o id da forma
 * @param forma a forma que vai ser alterada
 * @param id o novo id
 */
void set_id_da_forma(void* forma, int id);

/**
 * @brief muda a cor da borda da forma
 * @param forma a forma a ser alterada
 * @param nova_cor a string da nova cor
 */
void set_corb_da_forma(void* forma, char* nova_cor);

/**
 * @brief muda a cor de preenchimento da forma
 * @param forma a forma a ser alterada
 * @param nova_cor a string da nova cor
 */
void set_cp_da_forma(void* forma, char* nova_cor);

/**
 * @brief move a forma para uma nova posicao x e y
 * @param forma a forma que vai ser movida
 * @param x a nova coordenada x
 * @param y a nova coordenada y
 */
void set_posicao_da_forma(void* forma, float x, float y);

/**
 * @brief cria uma copia exata da forma e retorna o ponteiro pra ela
 * @param forma a forma original que vamos clonar
 * @return o ponteiro para a nova forma clonada
 */
form clone_forma(void* forma);

/**
 * @brief chama a funcao kill especifica de cada tipo pra liberar memoria
 * @param forma a forma que vamos destruir
 */
void destruir_forma_generica(void* forma);

/**
 * @brief escreve os dados da forma num arquivo txt pra gente conferir
 * @param arq_txt o arquivo onde vamos escrever
 * @param forma a forma que vamos imprimir
 */
void imprimir_dados_forma(FILE* arq_txt, void* forma);

#endif