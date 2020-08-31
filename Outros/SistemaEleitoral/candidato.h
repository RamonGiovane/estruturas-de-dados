#ifndef CANDIDATO_H_INCLUDED
#define CANDIDATO_H_INCLUDED
#include <stdbool.h>

typedef struct {
    bool vazio;
    unsigned int numeroVotos;
}TStatusCandidato;

typedef struct{
    int numeroCandidato;
    TStatusCandidato status;
}TCandidato;

#endif