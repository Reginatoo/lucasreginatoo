#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

typedef struct no {
    void* info;
    struct no* esq;
    struct no* dir;
} No;

typedef struct {
    No* raiz;
    Fcomp cmp;
} StArvore;

static No* novo_no(void* info) {
    No* n = (No*) malloc(sizeof(No));
    if (n) {
        n->info = info;
        n->esq = NULL;
        n->dir = NULL;
    }
    return n;
}

static No* min_no(No* n) {
    No* atual = n;
    while (atual && atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

static No* insere_rec(No* n, void* info, Fcomp cmp) {
    if (n == NULL) {
        return novo_no(info);
    }
    if (cmp(info, n->info) < 0) {
        n->esq = insere_rec(n->esq, info, cmp);
    } else {
        n->dir = insere_rec(n->dir, info, cmp);
    }
    return n;
}

static void* busca_rec(No* n, void* chave, Fcomp cmp) {
    if (n == NULL) return NULL;
    int r = cmp(chave, n->info);
    if (r == 0) return n->info;
    if (r < 0) return busca_rec(n->esq, chave, cmp);
    return busca_rec(n->dir, chave, cmp);
}

static No* remove_rec(No* n, void* chave, Fcomp cmp, void** salva_info) {
    if (n == NULL) return NULL;
    int r = cmp(chave, n->info);

    if (r < 0) {
        n->esq = remove_rec(n->esq, chave, cmp, salva_info);
    } else if (r > 0) {
        n->dir = remove_rec(n->dir, chave, cmp, salva_info);
    } else {
        if (salva_info) *salva_info = n->info;
        
        if (n->esq == NULL) {
            No* temp = n->dir;
            free(n);
            return temp;
        } else if (n->dir == NULL) {
            No* temp = n->esq;
            free(n);
            return temp;
        }

        No* temp = min_no(n->dir);
        n->info = temp->info;
        n->dir = remove_rec(n->dir, temp->info, cmp, NULL);
    }
    return n;
}

static void percorre_rec(No* n, Fvisit visit, void* aux) {
    if (n != NULL) {
        percorre_rec(n->esq, visit, aux);
        visit(n->info, aux);
        percorre_rec(n->dir, visit, aux);
    }
}

static void libera_nos_rec(No* n) {
    if (n != NULL) {
        libera_nos_rec(n->esq);
        libera_nos_rec(n->dir);
        free(n);
    }
}

Arvore cria_arvore(Fcomp comparador) {
    StArvore* t = (StArvore*) malloc(sizeof(StArvore));
    if (t) {
        t->raiz = NULL;
        t->cmp = comparador;
    }
    return (Arvore) t;
}

void insere_arvore(Arvore t, void* info) {
    StArvore* tree = (StArvore*) t;
    if (tree) {
        tree->raiz = insere_rec(tree->raiz, info, tree->cmp);
    }
}

void* remove_arvore(Arvore t, void* chave) {
    StArvore* tree = (StArvore*) t;
    if (tree) {
        void* removido = NULL;
        tree->raiz = remove_rec(tree->raiz, chave, tree->cmp, &removido);
        return removido;
    }
    return NULL;
}

void* busca_arvore(Arvore t, void* chave) {
    StArvore* tree = (StArvore*) t;
    if (tree) {
        return busca_rec(tree->raiz, chave, tree->cmp);
    }
    return NULL;
}

void percorre_arvore(Arvore t, Fvisit visit, void* aux) {
    StArvore* tree = (StArvore*) t;
    if (tree) {
        percorre_rec(tree->raiz, visit, aux);
    }
}

void* get_menor_dado(Arvore t) {
    StArvore* tree = (StArvore*) t;
    if (tree == NULL || tree->raiz == NULL) {
        return NULL;
    }
    No* min = min_no(tree->raiz);
    return min->info;
}

void libera_arvore(Arvore t) {
    StArvore* tree = (StArvore*) t;
    if (tree) {
        libera_nos_rec(tree->raiz);
        free(tree);
    }
}