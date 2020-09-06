#ifndef hash_lista_H_INCLUDED
#define hash_lista_H_INCLUDED

#include "lista.h"

// Modelo
typedef struct {
    int tam;           // tamanho da Tabela
    int n;             // numero de elementos na tabela
    Lista* elementos;  // vetor dinamico de Listas encadeadas

    int numColisoes;

} t_hash_lista;

typedef t_hash_lista* HashLista;

// Funções
HashLista cria_hash_lista(int tamanho);
int insere_hash_lista(HashLista th, TElemento e);
void termina_hash_lista(HashLista th);
int pesquisa_hash_lista(HashLista th, TChave ch, TElemento* e);
int remove_hash_lista(HashLista th, TChave ch, TElemento* e);
void print_hash_lista(HashLista th);
int altera_hash_lista(HashLista th, TElemento e);

#endif  // hash_lista_H_INCLUDED
