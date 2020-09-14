#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"

int main() {
    TElemento e;

    Grafo g = cria_grafo();

    e.chave = 1;
    insere_vertice(g, e);

    e.chave = 8;
    insere_vertice(g, e);

    e.chave = 2;
    insere_vertice(g, e);
   
    e.chave = 5;
    insere_vertice(g, e);

    e.chave = 3;
    insere_vertice(g, e);

    TChave c1, c2;
    c1 = 2;
    c2 = 5;
    insere_aresta(g, c1, c2, 8);

    c1 = 1;
    c2 = 5;
    insere_aresta(g, c1, c2, 4);

    c1 = 1;
    c2 = 3;
    insere_aresta(g, c1, c2, 3);

    c1 = 1;
    c2 = 8;
    insere_aresta(g, c1, c2, 5);

    c1 = 2;
    c2 = 8;
    insere_aresta(g, c1, c2, 4);

    c1 = 3;
    c2 = 5;
    insere_aresta(g, c1, c2, 2);

    c1 = 3;
    c2 = 2;
    insere_aresta(g, c1, c2, 2);

    c1 = 1;
    c2 = 2;
    caminho_mais_curto(g, c1, c2);


}