#include <stdlib.h>
#include <stdio.h>
#include "abp.h"
#include "cedula.h"
#include "lista.h"
#include "hash_lista.h"


HashLista cria_hash_lista(int tamanho)
{
    HashLista thash = (HashLista)malloc(sizeof(t_hash_lista));

    thash->tam = tamanho;
    thash->n = 0;
    thash->numColisoes = 0;

    thash->elementos = (Lista *)malloc(sizeof(Lista) * tamanho);

    for (int i = 0; i < tamanho; i++)
    {
        thash->elementos[i] = cria_lista();
    }

    return thash;
}

int insere_hash_lista(HashLista th, TElemento e)
{

    int indice = tch_hash_a(e.id, th->tam);

    printf("\tindice %d\n", indice);
    return insere_apos(th->elementos[indice], e);
}

int altera_hash_lista(HashLista th, TElemento e){

    int indice = tch_hash_a(e.id, th->tam);

    return altera_elemento(th->elementos[indice], e);
}

void termina_hash_lista(HashLista th)
{

    for (int i = 0; i < th->tam; i++)
    {
        termina_lista(th->elementos[i]);
    }

    free(th->elementos);

    free(th);
}

int pesquisa_hash_lista(HashLista th, TChave ch, TElemento *e)
{
    int i = tch_hash_a(ch, th->tam);

    return busca_elemento(th->elementos[i], ch, e);
}

int remove_hash_lista(HashLista th, TChave ch, TElemento* e)
{
    int indice = tch_hash_a(ch, th->tam);

    return remove_elemento(th->elementos[indice], ch, e);
}

void print_hash_lista(HashLista th)
{
    for (int i = 0; i < th->tam; i++)
    {
        printf("\n%d: ", i);
        print_lista(th->elementos[i]);
    }
}
