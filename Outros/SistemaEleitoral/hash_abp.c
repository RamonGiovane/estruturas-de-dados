#include <stdlib.h>
#include <stdio.h>
#include "abp.h"
#include "cedula.h"
#include "hash_abp.h"


int funcao_hash(TChave id, HashAbp th){
   
    int soma = 0;
 
    for(int i = 0; i<3; i++){
        
        if(id.tituloEleitor[i] == '\0') break;

        soma += id.tituloEleitor[i];
    }
        
    
    return soma % th->tam;
}

HashAbp cria_hash_abp(int tamanho){
    HashAbp thash = (HashAbp) malloc(sizeof(t_hash_abp));

    thash->tam = tamanho;
    thash->n = 0;

    thash->elementos = (Abp*) malloc(sizeof(Abp) * tamanho);

    for (size_t i = 0; i < tamanho; i++)
    {
        thash->elementos[i] = cria_abp();
    }

    return thash;

}

int insere_hash_abp(HashAbp th, TElemento e){

    int indice = funcao_hash(e.id, th);

    printf("\tindice %d\n", indice);
    return insere_abp(&th->elementos[indice], e);

}


void termina_hash_abp(HashAbp th){

    for (size_t i = 0; i < th->tam; i++)
    {
        termina_abp(th->elementos[i]);
    }

    free(th->elementos);

    free(th);

}


int pesquisa_hash_abp (HashAbp th,  TChave ch,  TElemento *e){
    int i = funcao_hash(ch, th);

    return pesquisa_abp(th->elementos[i], ch, e);
}

int remove_hash_abp(HashAbp th, TChave ch){
    int indice = funcao_hash(ch, th);

    return remove_abp(&(th)->elementos[indice], ch);
}

void print_hash_abp(HashAbp th){
    int i;
    for(i=0; i<th->tam; i++)
        printInOrdem(th->elementos[i]);
}
