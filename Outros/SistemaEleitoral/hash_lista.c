#include "hash_lista.h"

#include <stdio.h>
#include <stdlib.h>

#include "abp.h"
#include "cedula.h"
#include "io.h"
#include "lista.h"

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
    int indice = tch_hash(e.id, th->tam);
    bool colisao = false;
    // Colisão
    if (th->elementos[indice]->n > 0) colisao = true;

    int statusVotos = insere_apos(th->elementos[indice], e);

      if (statusVotos){
         th->n += 1;
         if(colisao) th->numColisoes += 1;
    }

    return statusVotos;
}

int altera_hash_lista(HashLista th, TElemento e) {
    int indice = tch_hash(e.id, th->tam);

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
    int i = tch_hash(ch, th->tam);

    return busca_elemento(th->elementos[i], ch, e);
}

int remove_hash_lista(HashLista th, TChave ch, TElemento *e) {
    int indice = tch_hash(ch, th->tam);

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
