#ifndef HASH_CANDIDATOS_H_INCLUDED
#define HASH_CANDIDATOS_H_INCLUDED
#include <stdbool.h>

#include "abp.h"
#include "candidato.h"

typedef struct {
    TCandidato* elementos;
    int tamanho;
    int numElementos;
    int numColisoes;

    int np;  // numero primo mais proximo e menor que tamanho
} t_hash_candidatos;

typedef t_hash_candidatos* HashCandidatos;

HashCandidatos cria_hash_candidatos(unsigned int);
int insere_candidato(HashCandidatos, TCandidato);
int pesquisa_candidato(HashCandidatos, int, TCandidato*);
int remove_candidato(HashCandidatos, int);
int pesquisa_candidato(HashCandidatos, int, TCandidato*);

void print_candidatos(HashCandidatos);
void termina_hash_candidatos(HashCandidatos);
int computa_candidato(HashCandidatos, int);
int decrementa_candidato(HashCandidatos, int);

#endif  // HASH_CANDIDATOS_H_INCLUDED