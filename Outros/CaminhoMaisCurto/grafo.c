#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#define INFINITO 999999999
#define MEMBRO 1
#define NAOMEMBRO 0

Grafo cria_grafo(){
    
    int lin, col;

    Grafo g = (Grafo) malloc(sizeof(TGrafo));
    
    if(g){
    
      g->num_vert = 0;

      for(lin = 0; lin<MAX; lin++)
        for(col = 0; col<MAX; col++)
            g->arestas[lin][col].conectado = 0;
      
    }

    return g;

}

void caminho_mais_curto(Grafo g, TChave origem, TChave destino){
   int dist[MAX], perm[MAX], path[MAX];
    int corrente, s,t,i,k,dc;
    int menor_dist, nova_dist, caminho;

    for(i = 0 ; i < g->num_vert; i++){
        perm[i] = NAOMEMBRO;
        dist[i] = INFINITO;
    }

    s = pesquisa_vertice(g, origem);
    t = pesquisa_vertice(g, destino);
    perm[0] = MEMBRO;
    dist[0] = 0;

    corrente = s;
    k = corrente;

    while(corrente != t){ //calcula até a origem, para calcular de todos muda a condição de parada do loop

        menor_dist = INFINITO;
        dc = dist[corrente];

        for(i=0 ; i< g->num_vert; i++){
            if(perm[i] == NAOMEMBRO && g->arestas[corrente][i].conectado){

                nova_dist = dc + g->arestas[corrente][i].peso;

                if(nova_dist < dist[i]){
                    dist[i] = nova_dist;
                    path[i] = corrente;
                }

                if(dist[i]< menor_dist){
                    menor_dist = dist[i];
                    k = i;
                }
            }
        }

        printf("%d ", g->vertices[k].info.chave);
        corrente = k;
        perm[corrente] = MEMBRO;
    }

    printf("\n\nRESULTADO: ");
    caminho = t;

    printf("%d <- ", g->vertices[t].info.chave);

    while(caminho != s){
        printf("%d", g->vertices[path[caminho]].info.chave);
        caminho = path[caminho];

        if(caminho != s)
            printf(" <- ");
    }

    printf("\n\ncusto: %d\n\n", dist[t]);
}

//Retorna a posição do vértice com chave == ch ou -1 caso contrário
int pesquisa_vertice(Grafo g, TChave ch){

    for(int i = 0; i<g->num_vert; i++)
        if(g->vertices[i].info.chave == ch)
            return i;
    return -1;
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

int insere_aresta(Grafo g, TChave v1, TChave v2 , TPeso p){
   
    int p1 = pesquisa_vertice(g, v1);
    int p2 = pesquisa_vertice(g, v2);
   
    if(p1 == -1 || p2 == -1)
        return 0;
    
    //Ligando os dois vertices, se eles existem
    g->arestas[p1][p2].conectado = 1;
    g->arestas[p2][p1].conectado = 1;

    //Atribuindo os pesos dos vertices
    g->arestas[p1][p2].peso = p;
    g->arestas[p2][p1].peso = p;

    return 1;
 
}

int remove_aresta(Grafo g, TChave v1, TChave v2){
    int p1 = pesquisa_vertice(g, v1);
    int p2 = pesquisa_vertice(g, v2);
   
    if(p1 == -1 || p2 == -1)
        return 0;

    if(g->arestas[p1][p2].conectado == 0)
        return 0;
    
    g->arestas[p1][p2].conectado = 0;
    g->arestas[p2][p1].conectado = 0;

    return 1;
}
    
int remove_vertice(Grafo g, TChave ch){
    
    int i = pesquisa_vertice(g, ch);
    int t = g->num_vert -1;
    if(i == -1)
        return 0;
    
    g->vertices[i] = g->vertices[t];
   

    for(int k = 0; k<t; k++)
        g->arestas[i][k] = g->arestas[t][k];
    
    for(int k = 0; k<t; k++)
        g->arestas[k][i] = g->arestas[k][t];
    
    
    g->num_vert--;
   
    return 1;
    
}

//void termina_grafo(Grafo g);
// void imprime_grafo(Grafo g);