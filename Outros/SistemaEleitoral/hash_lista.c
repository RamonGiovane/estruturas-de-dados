#include <stdlib.h>
#include <stdio.h>
#include "abp.h"
#include "cedula.h"
#include "lista.h"
#include "hash_lista.h"


int funcao_hash(TChave id, HashLista th){
   
    int soma = 0;
 
    for(int i = 0; i<3; i++){
        
        if(id.tituloEleitor[i] == '\0') break;

        soma += id.tituloEleitor[i];
    }
        
    
    return soma % th->tam;
}

HashLista cria_hash_lista(int tamanho){
    HashLista thash = (HashLista) malloc(sizeof(t_hash_lista));

    thash->tam = tamanho;
    thash->n = 0;

    thash->elementos = (Lista*) malloc(sizeof(Lista) * tamanho);

    for (size_t i = 0; i < tamanho; i++)
    {
        thash->elementos[i] = cria_lista();
    }

    return thash;

}

int insere_hash_lista(HashLista th, TElemento e){

    int indice = funcao_hash(e.id, th);

    printf("\tindice %d\n", indice);
    return insere_apos(th->elementos[indice], e);

}


void termina_hash_lista(HashLista th){

    for (size_t i = 0; i < th->tam; i++)
    {
        termina_lista(th->elementos[i]);
    }

    free(th->elementos);

    free(th);

}


int pesquisa_hash_lista (HashLista th,  TChave ch,  TElemento *e){
    int i = funcao_hash(ch, th);

    return busca_elemento(th->elementos[i], ch, e);
}

int remove_hash_lista(HashLista th, TChave ch){
    int indice = funcao_hash(ch, th);

    return remove_elemento(th->elementos[indice], ch);
}

void print_hash_lista(HashLista th){
    printf("Not implemented");
}
