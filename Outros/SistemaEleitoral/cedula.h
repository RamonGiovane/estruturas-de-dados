#ifndef CEDULA_H_INCLUDED
#define CEDULA_H_INCLUDED
#define TITULO_ELEITOR 8
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define TSTATUS_INIT {false, false, false}

typedef struct TChave
{
    char tituloEleitor[TITULO_ELEITOR];

} TChave;

typedef struct TStatus
{
    bool vazio;
    bool votouPrefeito;
    bool votouVereador;
}TStatus;


typedef struct
{
    int prefeito;
    int vereador;
    TChave id;
    TStatus status;

} TElemento;

/*Compara dois TChave. Se forem iguais retorna 0.
Se ch1 > ch2, retorna um valor > 0.
Se ch1 < ch2 retorna um valor < 0.*/
int tchcmp(TChave ch1, TChave ch2);

void print_tch(TChave ch);

void print_elemento(TElemento e);

//Função Hash A: Gera um valor hash a partir de TChave
unsigned int tch_hash_a(TChave ch, unsigned int m);
//Funcão Hash B: Gera uma valor hash a partir de TChave
unsigned int tch_hash_b(TChave ch, unsigned int m);

#endif // CEDULA_H_INCLUDED