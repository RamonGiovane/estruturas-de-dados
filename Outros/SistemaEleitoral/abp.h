#ifndef ABP_H_INCLUDED
#define ABP_H_INCLUDED

#include "cedula.h"

typedef struct Nodo {
    /// Dados que cada nó carrega
    TElemento info;

    /// Proximos elementos
    struct Nodo *esq, *dir;

} TNodo;

typedef TNodo *Abp;

/// Insere TElemento na arvore a partir de um ponteiro da raiz
int insere_abp(Abp *, TElemento);

/// Insere TElemento na arvore a partir de um ponteiro da raiz
int insereNaoRecursivo(Abp *, TElemento);

/// Pesquisa a partir da raiz, TChave e se achar retorna como TElemento*
int pesquisa_abp(Abp, TChave, TElemento *);

/// Pesquisa a partir da raiz, TChave e se achar retorna como TElemento*
int pesquisaNaoRecursiva(Abp, TChave, TElemento *);

int altera_abp(Abp raiz, TElemento e);

void printInOrdem(Abp);

int remove_abp(Abp *, TChave, TElemento *);

int removeNaoRecursivo(Abp *, TChave);

Abp cria_abp();

void termina_abp(Abp p);

#endif  // ABP_H_INCLUDED
