#include <stdio.h>
#include <stdlib.h>
#include "cedula.h"
#include "lista.h"

Lista cria_lista(){
  Lista l;
  l= (Lista)malloc(sizeof(tipo_lista));
  if(l){ /*if(l!=NUL)*/
    l->first = NULL;
    l->last=NULL;
    l->n=0;
  }
  return l;
}

void termina_lista(Lista l){
  tipo_nodo *p;
  while(l->first){/*while(l->first!=NULL)*/
    p = l->first;
    l->first = l->first->next;
    free(p);
  }
  free(l);
}

int insere_inicio(Lista l, TElemento e){
  tipo_nodo *p;
  p =(tipo_nodo*)malloc(sizeof(tipo_nodo));

  if(!p)/*if(p==NULL)*/
    return 0;

  p->info = e;
  p->next=l->first;
  l->first = p;
  if(l->n==0)
    l->last =p;
  l->n++;
  return 1;
}

int remove_elemento(Lista l, TChave ch){
  
  TElemento _;

  int i = busca_elemento(l, ch, &_);

  return remove_elemento_i(l, i, &_);
}

int remove_elemento_i(Lista l, int indice, TElemento*e){
   tipo_nodo *p,*ant;
   int i;
   if(indice<1 || indice>l->n )
     return 0;
   p=l->first;
   for(i=1;i<indice;i++){
     ant = p;
     p=p->next;
   }
  
   *e=p->info;

   if(p==l->first)
     l->first = l->first->next;
   else
     if(p==l->last)  {
       l->last = ant;
       l->last->next = NULL;
     }
     else
        ant->next = p->next;
   free(p);
   return 1;
}

int insere_apos(Lista l, TElemento e){
   tipo_nodo *p;

   if(l->n==0)
     return insere_inicio(l,e);

   p=(tipo_nodo*)malloc(sizeof(tipo_nodo));

   if(!p)
     return 0;

   p->info = e;

   l->last->next = p;
   l->last = p;
   p->next = NULL;
   l->n++;
   return 1;
}


int insere_posicao(Lista l, TElemento e, int indice){
  tipo_nodo *p,*aux;
   int i;

  if(indice <1 || indice >l->n+1)
    return 0;

  if(indice ==1)
    return insere_inicio(l,e);
  else
    if(indice==l->n+1)
      return insere_apos(l,e);
    else{
       p=(tipo_nodo*)malloc(sizeof(tipo_nodo));

       if(!p)
         return 0;

       p->info = e;
       aux = l->first;
       for(i=1;i<indice-1;i++)
         aux= aux->next;
       p->next = aux->next;
       aux->next = p;
       l->n++;
       return 1;

    }

}

int busca_elemento(Lista l, TChave ch, TElemento *e){
  tipo_nodo *p;

  p= l->first;
  while(p){
    if(tchcmp(p->info.id, ch) == 0){
      *e=p->info;
      return 1;
    }
    p=p->next;
  }

  return 0;

}
int lista_vazia(Lista l){
   return l->n==0;
}

int lista_cheia(Lista l){
  tipo_nodo *p;

  p=(tipo_nodo*)malloc(sizeof(tipo_nodo));
  if(p==NULL)
    return 1;
  else{
    free(p);
    return 0;
  }
}

void print_lista(Lista l){
  if(l == NULL || l->n == 0) return;

  tipo_nodo* n = l->first;

  while (n)
  {
    print_tch(n->info.id);
    n = n->next;
  }
  
}