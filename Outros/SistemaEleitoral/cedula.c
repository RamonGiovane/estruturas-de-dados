#include "cedula.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*Compara dois TChave. Se forem iguais retorna 0.
Se ch1 > ch2, retorna um valor > 0.
Se ch1 < ch2 retorna um valor < 0.*/
int tchcmp(TChave ch1, TChave ch2) {
    return strcmp(ch1.tituloEleitor, ch2.tituloEleitor);
}

void print_tch(TChave ch) { printf("%s ", ch.tituloEleitor); }

void print_elemento(TElemento e) {
    printf(
        "Titulo de Eleitor: %s\nVoto para Prefeito %d\nVoto para "
        "Vereador%d\n\n",
        e.id.tituloEleitor, e.prefeito, e.vereador);
}

// Função Hash A: Gera um valor hash a partir de TChave
unsigned int tch_hash(TChave ch, unsigned int m) {
    
    return transforma_chave(ch) % m;
}

//Transforma um TChave em um valor numerico.
unsigned int transforma_chave(TChave ch) {
    unsigned int i, soma = 0;
    for (i = 0; ch.tituloEleitor[i] != '\0'; i++) {
        //Através de experimentos notou-se que o somatório de i a um número 
        //de casas decimais maiores
        //pode reduzir o número de colisões drasticamente.
        soma += ch.tituloEleitor[i] * (i + 1000);
    }
    return soma;
}
