#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "cedula.h"

/*Compara dois TChave. Se forem iguais retorna 0.
Se ch1 > ch2, retorna um valor > 0.
Se ch1 < ch2 retorna um valor < 0.*/
int tchcmp(TChave ch1, TChave ch2)
{
    return strcmp(ch1.tituloEleitor, ch2.tituloEleitor);
}


void print_tch(TChave ch)
{
    printf("%s ", ch.tituloEleitor);
}

void print_elemento(TElemento e)
{
    printf("Titulo de Eleitor: %s\nVoto para Prefeito %d\nVoto para Vereador%d\n\n",
           e.id.tituloEleitor, e.prefeito, e.vereador);
}

//Função Hash A: Gera um valor hash a partir de TChave
unsigned int tch_hash_a(TChave ch, unsigned int m)
{
    unsigned int i, soma = 0;
    for (i = 0; i < TITULO_ELEITOR / 2 && ch.tituloEleitor[i] != '\0'; i++)
    {
        soma += ch.tituloEleitor[i] * (ch.tituloEleitor[0] + 1);
    }
    printf(" hash %d - hash mod M %d\n", soma, soma%m);
    return soma % m;
}

//Funcão Hash B: Gera uma valor hash a partir de TChave
unsigned int tch_hash_b(TChave ch, unsigned int m)
{
    unsigned int i, soma = 1;
    for (i = 0; i < TITULO_ELEITOR && ch.tituloEleitor[i] != '\0'; i++){
        soma +=  ch.tituloEleitor[i]  + (ch.tituloEleitor[i] % TITULO_ELEITOR);
    }
    printf(" hash %d - hash mod M %d\n", soma, (11 - soma) % m);
    return (11 - soma) % m;
}