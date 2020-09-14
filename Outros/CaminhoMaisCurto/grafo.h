#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#define MAX 10
typedef int TChave;
typedef unsigned int TPeso;
typedef enum {espera, pronto, processado} TStatus;

typedef struct 
{
    TChave chave;

}TElemento;


typedef struct
{
    TElemento info;
    TStatus status;
}TVertice;

typedef struct
{
    int conectado;
    TPeso peso;

}TAresta;

typedef struct 
{
    TVertice vertices[MAX];
    TAresta arestas[MAX][MAX];
    int num_vert; //numero de vertices
}TGrafo;

typedef TGrafo* Grafo;

Grafo cria_grafo();
void caminho_mais_curto(Grafo g, TChave origem, TChave destino);
void termina_grafo(Grafo g);
int pesquisa_vertice(Grafo g, TChave ch);
int insere_vertice(Grafo g, TElemento e);
int insere_aresta(Grafo g, TChave v1, TChave v2 , TPeso p);
int remove_vertice(Grafo g, TChave ch);
int remove_aresta(Grafo g, TChave v1, TChave v2);
void imprime_grafo(Grafo g);




#endif // GRAFO_H_INCLUDED
