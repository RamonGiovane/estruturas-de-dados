#ifndef ABP_H_INCLUDED
#define ABP_H_INCLUDED
typedef int TChave;
typedef struct {
    TChave chave;
    /**demais componentes*/

}TElemento;

typedef struct Nodo{

    ///Dados que cada nó carrega
    TElemento info;

    ///Proximos elementos
    struct Nodo *esq, *dir;

}TNodo;

typedef TNodo *Apontador;

///Insere TElemento na arvore a partir de um ponteiro da raiz
int insereRecursivo(Apontador*, TElemento);

///Pesquisa a partir da raiz, TChave e se achar retorna como TElemento*
int pesquisaRecursiva(Apontador, TChave, TElemento*);

void printInOrdem(Apontador);

int removeRecursivo(Apontador*, TChave);

Apontador criaABP();

void terminaABP(Apontador p);

#endif // ABP_H_INCLUDED
