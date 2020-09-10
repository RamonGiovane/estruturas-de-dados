#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

Grafo cria_grafo(){

    Grafo g = (Grafo) malloc(sizeof(TGrafo));

    if(g){

      g->num_vert = 0;

      for(int i = 0; i<MAX; i++){
        g->vertices[i].listaAdjacencia = (Lista) malloc(sizeof(TLista));
        g->vertices[i].listaAdjacencia->tamanho = 0;
      }

    }

    return g;

}

//Retorna a posição do vértice com chave == ch ou -1 caso contrário
int pesquisa_vertice(Grafo g, TChave ch){

    for(int i = 0; i<g->num_vert; i++)
        if(g->vertices[i].info.chave == ch)
            return i;
    return -1;
}


int insere_em_lista(Lista l, TChave ch, TPeso p){

    TElemento e;
    e.chave = ch;
    e.peso = p;

    if(!l) return 0;

    TNodo* n = (TNodo*) malloc(sizeof(TNodo));
    n->info = e;

    if(l->first == NULL){
        l->first = n;
        l->last = n;
    }

    else if(l->tamanho == 1){
        l->first->next = n;
        l->last = n;
    }
    else
    {
        l->last->next = n;
    }

    l->tamanho++;

    return 1;

}


int procura_em_lista(Lista l, TChave ch){

    if(!l) return 0;

    TNodo* n = l->first;

    while(n){
        if(n->info.chave == ch)
            return 1;

        n = n->next;
    }

    return 0;
}


int remove_em_lista(Lista l, TChave ch){
    if(!l) return 0;

    TNodo* n = l->first, *aux;

    //Se a lista esta vazia
    if(l->tamanho == 0) return 0;

    //Se a lista possui apenas 1 elemento
    if(l->tamanho == 1){
        free(l->first);
        l->tamanho--;
        return 1;
    }

    //Se o elemento a ser removido é o primeiro
    if(ch == n->info.chave){
        l->first = n->next;

        free(n);
        l->tamanho--;
        return 1;
    }

    n = n->next;
    aux = n;
    while(n){

        if(n->info.chave == ch){
            aux->next = n->next;
            free(aux);
            l->tamanho--;
            return 1;
        }

        aux = n;
        n = n->next;
    }

    return 0;
}

int insere_aresta(Grafo g, TChave v1, TChave v2, TPeso p){
    int p1 = pesquisa_vertice(g, v1);
    int p2 = pesquisa_vertice(g, v2);

    if(p1 != 1 || p2 != 1)
        return 0;

    //Insere na lista da chave v1 a chave v2, se ela nao existir
    if(!procura_em_lista(g->vertices[p1].listaAdjacencia, v2)) {
       insere_em_lista(g->vertices[p1].listaAdjacencia, v2, p);
    }

    //Insere na lista da chave v2 a chave v1, se ela nao existir
    if(!procura_em_lista(g->vertices[p2].listaAdjacencia, v1)) {
       insere_em_lista(g->vertices[p2].listaAdjacencia, v1, p);
    }

    return 1;
}


int insere_vertice(Grafo g, TElemento e){

    //Verifica se o grafo esta cheio ou se o vertice ja existe
    if(g->num_vert == MAX || pesquisa_vertice(g, e.chave) != -1)
        return 0;

    g->vertices[g->num_vert].info = e;
    g->num_vert++;

    g->vertices[g->num_vert].status = espera;

    return 1;
}



//Remove a aresta ch do vertice v no grafo g
int remove_aresta(Grafo g, TChave v, TChave ch){

    //Verifica se o vertice existe
    int i = pesquisa_vertice(g, v);

    if(i == -1)
        return 0;

    return remove_em_lista(g->vertices[i].listaAdjacencia, ch);

}

int remove_vertice(Grafo g, TChave ch){

    //Verifica se o vertice existe
    int i = pesquisa_vertice(g, ch);

    if(i == -1)
        return 0;

    //Tamanho do grafo
    int t = g->num_vert -1;

    g->vertices[i] = g->vertices[t];

    TNodo* n = g->vertices[t].listaAdjacencia->first;

    while(n){
        remove_aresta(g, n->info.chave, ch);
        n = n->next;
    }

    free(g->vertices[t].listaAdjacencia);

    g->num_vert--;

    return 1;

}

//void termina_grafo(Grafo g);
// void imprime_grafo(Grafo g);
