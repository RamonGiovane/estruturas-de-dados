#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#define MAX 10
typedef int TChave;
typedef unsigned int TPeso;
typedef enum {espera, pronto, processado} TStatus;

typedef struct 
{
    TChave chave;
    TPeso peso;

}TElemento;


typedef struct Nodo
{
    TElemento info;
   struct Nodo *next;

}TNodo;

typedef struct
{
   TNodo *first, *last;
   int tamanho;
}TLista;

typedef TLista* Lista;

typedef struct{
    TElemento info;
    Lista listaAdjacencia;
    TStatus status;
}TVertice;

typedef struct 
{
    TVertice vertices[MAX];
    int num_vert; //numero de vertices
    
}TGrafo;

typedef TGrafo* Grafo;

Grafo cria_grafo();
void termina_grafo(Grafo g);
int pesquisa_vertice(Grafo g, TChave ch);
int insere_vertice(Grafo g, TElemento e);
int insere_aresta(Grafo g, TChave v1, TChave v2 , TPeso p);
int remove_vertice(Grafo g, TChave ch);
int remove_aresta(Grafo g, TChave v1, TChave v2);
void imprime_grafo(Grafo g);


#endif // GRAFO_H_INCLUDED
