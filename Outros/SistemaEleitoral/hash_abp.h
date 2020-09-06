#ifndef HASH_ABP_H_INCLUDED
#define HASH_ABP_H_INCLUDED

#include "abp.h"

// Modelo
typedef struct {

    int tam;         // tamanho da Tabela
    int n;           // numero de elementos na tabela
    Abp* elementos;  // vetor dinamico de Abps

    int numColisoes;

} t_hash_abp;

typedef t_hash_abp* HashAbp;

// Funções
HashAbp cria_hash_abp(int tamanho);
int insere_hash_abp(HashAbp th, TElemento e);
void termina_hash_abp(HashAbp th);
int pesquisa_hash_abp(HashAbp th, TChave ch, TElemento* e);
int remove_hash_abp(HashAbp th, TChave ch, TElemento* e);
void print_hash_abp(HashAbp th);
int altera_hash_abp(HashAbp th, TElemento e);

#endif  // HASH_ABP_H_INCLUDED
