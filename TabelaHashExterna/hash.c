#include <stdlib.h>
#include <stdio.h>
#include "abp.h"
#include "hash.h"


int funcaoHash(TChave chave, TipoTabela th){
    return chave % th->tam;
}

TipoTabela criaTabela(int tamanho){
    TipoTabela thash = (TipoTabela) malloc(sizeof(tTabela));

    thash->tam = tamanho;
    thash->n = 0;

    thash->elementos = (Apontador*) malloc(sizeof(Apontador) * tamanho);

    for (size_t i = 0; i < tamanho; i++)
    {
        thash->elementos[i] = criaABP();
    }

    return thash;

}

int insereElemento(TipoTabela th, TElemento e){

    int indice = funcaoHash(e.chave, th);

    printf(" indice %d ", indice);
    return insereRecursivo(&th->elementos[indice], e);

}


void terminaTabela(TipoTabela th){

    for (size_t i = 0; i < th->tam; i++)
    {
        terminaABP(th->elementos[i]);
    }

    free(th->elementos);

    free(th);

}


int pesquisaElemento (TipoTabela th,  TChave ch,  TElemento *e){
    int i = funcaoHash(ch, th);

    return pesquisaRecursiva(th->elementos[i], ch, e);
}

int removeElemento(TipoTabela th, TChave ch){
    int indice = funcaoHash(ch, th);

    return removeRecursivo(th->elementos, ch);
}

void imprime(TipoTabela th){
    int i;
    for(i=0; i<th->tam; i++)
        printInOrdem(th->elementos[i]);
}
