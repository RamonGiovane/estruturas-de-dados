#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include "cedula.h"


typedef struct nodo{
  TElemento info;
  struct nodo *next;
}tipo_nodo;

typedef struct{
  tipo_nodo *first,*last;
   int n;/*tamanho da Lista*/
}tipo_lista;

typedef tipo_lista *Lista;

Lista cria_lista();
void termina_lista(Lista);
int insere_inicio(Lista , TElemento);
int insere_inicio(Lista l, TElemento e);
//Remove elemento pelo indice
int remove_elemento_i(Lista, int,TElemento*);

//Remove elemento pela chave
int remove_elemento(Lista, TChave, TElemento*);

int insere_apos(Lista , TElemento );
int insere_posicao(Lista, TElemento, int );
int busca_elemento(Lista,TChave, TElemento *);
int altera_elemento(Lista, TElemento);
int lista_vazia(Lista);
int lista_cheia(Lista);
void print_lista(Lista l);

#endif // LISTA_H_INCLUDED
