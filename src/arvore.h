#ifndef ARVORE_H
#define ARVORE_H

typedef void* Arvore;
typedef int (*Fcomp)(void* a, void* b);
typedef void (*Fvisit)(void* info, void* aux);

/**
 * @brief cria uma nova árvore 
 * @param comparador Função que define a regra de ordenação
 */
Arvore cria_arvore(Fcomp comparador);

/**
 * @brief Insere um novo dado na árvore 
 * @param t A árvore
 * @param info O ponteiro para o dado a ser guardado 
 */
void insere_arvore(Arvore t, void* info);

/**
 * @brief Remove um nó específico da árvore
 * @param t A árvore
 * @param chave Um ponteiro contendo a chave de busca
 * @return O ponteiro do dado removido 
 */
void* remove_arvore(Arvore t, void* chave);

/**
 * @brief Busca um elemento na árvore
 * @return O ponteiro para o elemento encontrado
 */
void* busca_arvore(Arvore t, void* chave);

/**
 * @brief Percorre a árvore 
 * @param visit Função chamada para cada nó 
 * @param aux Dado auxiliar 
 */
void percorre_arvore(Arvore t, Fvisit visit, void* aux);

/**
 * @brief Retorna o menor elemento da árvore 
 * @return O dado do menor nó 
 */
void* get_menor_dado(Arvore t);

/**
 * @brief Destrói a estrutura da árvore 
 */
void kill_arvore(Arvore t);

#endif