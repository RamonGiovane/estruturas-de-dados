#ifndef HASHDUPLO_H_INCLUDED
#define HASHDUPLO_H_INCLUDED
#include "cedula.h"

typedef struct {
    TElemento *elementos;
    int tamanho;
    int numElementos;
    int numColisoes;

    int np;  // numero primo mais proximo e menor que tamanho
} t_hash_duplo;

typedef t_hash_duplo *HashDuplo;

HashDuplo cria_hash_duplo(unsigned int);
int insere_hash_duplo(HashDuplo, TElemento);
int pesquisa_hash_duplo(HashDuplo, TChave, TElemento *);
int remove_hash_duplo(HashDuplo, TChave, TElemento *);
int pesquisa_hash_duplo(HashDuplo, TChave, TElemento *);
int altera_hash_duplo(HashDuplo, TElemento);
void print_hash_duplo(HashDuplo);
void termina_hash_duplo(HashDuplo);
#endif  // HASHDUPLO_H_INCLUDED
