#ifndef CANDIDATO_H_INCLUDED
#define CANDIDATO_H_INCLUDED
#include <stdbool.h>

typedef struct {
    bool vazio;
}TStatusCandidato;

typedef struct{
    int numeroCandidato;
    unsigned int numeroVotos;
    TStatusCandidato status;
}TCandidato;

#endif