#ifndef CEDULA_H_INCLUDED
#define CEDULA_H_INCLUDED
#define TITULO_ELEITOR 14
#include <string.h>
#include <stdio.h>

typedef struct TChave
{
    char tituloEleitor[TITULO_ELEITOR];

}TChave;


typedef struct {
    int votoPrefeito;
    int votoVereador;
    TChave id;

}TElemento;


/*Compara dois TChave. Se forem iguais retorna 0.
Se ch1 > ch2, retorna um valor > 0.
Se ch1 < ch2 retorna um valor < 0.*/
inline int tchcmp(TChave ch1, TChave ch2){
    return strcmp(ch1.tituloEleitor, ch2.tituloEleitor);
}

inline void print_tch(TChave ch){
    printf("%s\n", ch.tituloEleitor);
}

inline void print_elemento(TElemento e){
    printf("Titulo de Eleitor: %s\nVoto para Prefeito %d\nVoto para Vereador\n\n",
     e.id.tituloEleitor, e.votoPrefeito, e.votoVereador);
}

#endif // CEDULA_H_INCLUDED