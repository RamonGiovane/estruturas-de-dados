#include <stdio.h>
#include <stdlib.h>
#include "abp.h"

///Insere TElemento na arvore a partir de um ponteiro da raiz
int insereRecursivo(Apontador *raiz, TElemento e)
{

    if (*raiz == NULL)
    { ///Chegou na folha
        *raiz = (Apontador)malloc(sizeof(TNodo));
        (*raiz)->info = e;
        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;

        return 1; /// Inserção realizada com sucesso
    }

    ///Se é maior que a raiz vai para direita
    if (e.chave > (*raiz)->info.chave)
        return insereRecursivo(&(*raiz)->dir, e);

    ///Se é maior que a raiz vai para esquerda
    if (e.chave < (*raiz)->info.chave)
        return insereRecursivo(&(*raiz)->esq, e);

    return 0; ///Elemento já existe
}

///Pesquisa a partir da raiz, TChave e se achar retorna como
/// TElemento*
int pesquisaRecursiva(Apontador raiz, TChave chave,
                      TElemento *retorno)
{
    if (raiz == NULL)
        return 0;

    if (raiz->info.chave == chave)
    {
        *retorno = raiz->info;
        return 1;
    }

    if (chave > raiz->info.chave)
        return pesquisaRecursiva(raiz->dir, chave, retorno);

    //se nao é maior, nem igual, vai para a esquerda
    return pesquisaRecursiva(raiz->esq, chave, retorno);
}

void printInOrdem(Apontador p)
{
    //ESQUERDA, PROCESSA PAI, DIREITA
    if (p != NULL)
    {
        printInOrdem(p->esq);
        printf("\n%d", p->info.chave);
        printInOrdem(p->dir);
    }
}

void terminaABP(Apontador p)
{

    if (p != NULL)
    {
        terminaABP(p->esq);
        terminaABP(p->dir);
        free(p);
    }
}

Apontador criaABP()
{
    return NULL;
}

int removeRecursivo(Apontador *raiz, TChave chave)
{

    printf("0 chave %d\n", (*raiz)->info.chave);
    if (*raiz == NULL)
        return 0;

    if (chave > (*raiz)->info.chave)
        return removeRecursivo(&(*raiz)->dir, chave);

    if (chave < (*raiz)->info.chave)
        return removeRecursivo(&(*raiz)->esq, chave);

    //Se nao caiu em nenhum dos ifs, achou-se o elemento a
    // ser removido
    Apontador aux = *raiz; //aux esta apontando pra quem eu quero remover

    if ((*raiz)->dir == NULL) // se *raiz não tem filho direito
        *raiz = (*raiz)->esq; 

    else if ((*raiz)->esq == NULL) //se *raiz não tem filho esquerdo
        *raiz = (*raiz)->dir; 

    
    else // se tem os dois filhos
    {
        raiz = &(*raiz)->esq;

        while ((*raiz)->dir != NULL)
        {
         
            raiz = &(*raiz)->dir;
        }
        
        aux->info = (*raiz)->info;
        aux = *raiz;
        *raiz = aux->esq;
    }

    free(aux);
    return 1;
}
