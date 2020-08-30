#ifndef HASH_CANDIDATOS_H_INCLUDED
#define HASH_CANDIDATOS_H_INCLUDED
#include <stdbool.h>

typedef struct {
    bool vazio;
    unsigned int numeroVotos;
}TStatusCandidato;

typedef struct{
    int numeroCandidato;
    TStatusCandidato status;
}TCandidato;


typedef struct{
  TCandidato* elementos;
  int tamanho;
  int numElementos;
}t_hash_candidatos;

typedef t_hash_candidatos *HashCandidatos;

HashCandidatos cria_hash_candidatos(unsigned int);
int insere_candidato(HashCandidatos, TCandidato);
int pesquisa_candidato(HashCandidatos, int, TCandidato*);
int remove_candidato(HashCandidatos,int);
int pesquisa_candidato(HashCandidatos, int, TCandidato*);
int altera_candidato(HashCandidatos, TCandidato);
void print_candidatos(HashCandidatos);
void termina_hash_candidatos(HashCandidatos);
int computa_candidato(HashCandidatos, int);

#endif // HASH_CANDIDATOS_H_INCLUDED