#include <stdlib.h>
#include <stdio.h>
#include "abp.h"
#include "io.h"
#include "cedula.h"
#include "hash_abp.h"



HashAbp cria_hash_abp(int tamanho){
    HashAbp thash = (HashAbp) malloc(sizeof(t_hash_abp));

    thash->tam = tamanho;
    thash->n = 0;
    thash->numColisoes = 0;

    thash->elementos = (Abp*) malloc(sizeof(Abp) * tamanho);

    for (int i = 0; i < tamanho; i++)
    {
        thash->elementos[i] = cria_abp();
    }

    thash->np = tamanho;
    while(!checar_numero_primo(thash->np) && thash->np-1 > 0) thash->np--; 

    return thash;

}

int insere_hash_abp(HashAbp th, TElemento e){

    int indice = tch_hash(e.id, th->tam);

    //Colisão!
    if(th->elementos[indice] != NULL)
        th->numColisoes += 1;

    int statusVotos = insere_abp(&th->elementos[indice], e);

    if(statusVotos) th->n += 1;

    return statusVotos;

}

int altera_hash_abp(HashAbp th, TElemento e){

    int indice = tch_hash(e.id, th->tam);

    return altera_abp(th->elementos[indice], e);
}

void termina_hash_abp(HashAbp th){

    if(th == NULL) return;
    
    for (int i = 0; i < th->tam; i++)
    {
        termina_abp(th->elementos[i]);
    }

    free(th->elementos);

    free(th);

}


int pesquisa_hash_abp (HashAbp th,  TChave ch,  TElemento *e){
    int i = tch_hash(ch, th->tam);

    return pesquisa_abp(th->elementos[i], ch, e);
}

int remove_hash_abp(HashAbp th, TChave ch, TElemento* e){
    int indice = tch_hash(ch, th->tam);

    int statusVotos = remove_abp(&(th)->elementos[indice], ch, e);

    if(statusVotos) th->n -= 1;

    return statusVotos;

}

void print_hash_abp(HashAbp th){
    int i;
    for(i=0; i<th->tam; i++){
        printf("\n%d: ", i);
        printInOrdem(th->elementos[i]);
    }

}
