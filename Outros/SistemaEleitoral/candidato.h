#ifndef CANDIDATO_H_INCLUDED
#define CANDIDATO_H_INCLUDED
#include <stdbool.h>
#include "condicao.h"

typedef struct {
    int condicao;
}TStatusCandidato;

typedef struct{
    int numeroCandidato;
    unsigned int numeroVotos;
    TStatusCandidato status;
    TCondicao condicao;
}TCandidato;

#endif