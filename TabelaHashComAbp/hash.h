#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include "abp.h"

//Modelo 
typedef struct 
{
    int tam; // tamanho da Tabela
    int n; // numero de elementos na tabela
    Apontador* elementos; //vetor dinamico de Apontador

}tTabela;

typedef tTabela* TipoTabela;


//Funções
int funcaoHash(TChave chave, TipoTabela th);
TipoTabela criaTabela(int tamanho);
int insereElemento(TipoTabela th, TElemento e);
void terminaTabela(TipoTabela th);
int pesquisaElemento (TipoTabela th,  TChave ch,  TElemento *e);
int removeElemento(TipoTabela th, TChave ch);
void imprime(TipoTabela th);

#endif // HASH_H_INCLUDED
