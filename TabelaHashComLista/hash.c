#include <stdio.h>
#include <stdlib.h>

#include "lista.h"
#include "hash.h"

int f_hash(TChave ch, int tamanhoTabela){
    return ch % tamanhoTabela;
}

HashLista cria_hash_lista(int tamanho) {
    HashLista thash = (HashLista)malloc(sizeof(t_hash_lista));

    thash->tam = tamanho;
    thash->n = 0;
    thash->numColisoes = 0;

    thash->elementos = (Lista *)malloc(sizeof(Lista) * tamanho);

    for (int i = 0; i < tamanho; i++) 
        thash->elementos[i] = cria_lista();
    

    return thash;
}

int insere_hash_lista(HashLista th, TElemento e) {
    int indice = f_hash(e.chave, th->tam);
   
    int status = insere_apos(th->elementos[indice], e);

      if (status)
         th->n += 1;
        

    return status;
}

int altera_hash_lista(HashLista th, TElemento e) {
    int indice = f_hash(e.chave, th->tam);

    return altera_elemento(th->elementos[indice], e);
}

void termina_hash_lista(HashLista th) {
    if (th == NULL) return;

    for (int i = 0; i < th->tam; i++) {
        termina_lista(th->elementos[i]);
    }

    free(th->elementos);

    free(th);
}

int pesquisa_hash_lista(HashLista th, TChave ch, TElemento *e) {
    int i = f_hash(ch, th->tam);

    return busca_elemento(th->elementos[i], ch, e);
}

int remove_hash_lista(HashLista th, TChave ch, TElemento *e) {
    int indice = f_hash(ch, th->tam);

    int statusVotos = remove_elemento(th->elementos[indice], ch, e);

    if (statusVotos) th->n -= 1;

    return statusVotos;
}

void print_hash_lista(HashLista th) {
    for (int i = 0; i < th->tam; i++) {
        printf("\n%d: ", i);
        print_lista(th->elementos[i]);
    }
}
