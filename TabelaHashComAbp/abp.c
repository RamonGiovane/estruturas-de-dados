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

        return 1; /// Inser��o realizada com sucesso
    }

    ///Se � maior que a raiz vai para direita
    if (e.chave > (*raiz)->info.chave)
        return insereRecursivo(&(*raiz)->dir, e);

    ///Se � maior que a raiz vai para esquerda
    if (e.chave < (*raiz)->info.chave)
        return insereRecursivo(&(*raiz)->esq, e);

    return 0; ///Elemento j� existe
}


///Insere TElemento na arvore a partir de um ponteiro da raiz
int insereNaoRecursivo(Apontador *raiz, TElemento e)
{

    while (*raiz != NULL)
    {

        if (e.chave == (*raiz)->info.chave)
            return 0;

        if (e.chave > (*raiz)->info.chave)
            raiz = &(*raiz)->dir;

        else if (e.chave < (*raiz)->info.chave)
            raiz = &(*raiz)->esq;
    }

    //Se saiu do while, quer dizer que chegou-se no filho (null) de uma folha
    *raiz = (Apontador)malloc(sizeof(TNodo));
    (*raiz)->info = e;
    (*raiz)->esq = NULL;
    (*raiz)->dir = NULL;

    return 1; /// Inser��o realizada com sucesso
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

    //se nao � maior, nem igual, vai para a esquerda
    return pesquisaRecursiva(raiz->esq, chave, retorno);
}

///Pesquisa a partir da raiz, TChave e se achar retorna como
/// TElemento*
int pesquisaNaoRecursiva(Apontador raiz, TChave chave,
                      TElemento *retorno)
{

    while(raiz != NULL) {

        if (raiz->info.chave == chave) {
            *retorno = raiz->info;
            return 1;
        }

         if (chave > raiz->info.chave)
            raiz = raiz->dir;

        else
            raiz = raiz->esq;

    }

    return 0;

}


int removeRecursivo(Apontador *raiz, TChave chave)
{

    if (*raiz == NULL)
        return 0;

    if (chave > (*raiz)->info.chave)
        return removeRecursivo(&(*raiz)->dir, chave);

    if (chave < (*raiz)->info.chave)
        return removeRecursivo(&(*raiz)->esq, chave);

    //Se nao caiu em nenhum dos ifs, achou-se o elemento a
    // ser removido
    Apontador aux = *raiz; //aux esta apontando pra quem eu quero remover

    if ((*raiz)->dir == NULL) // se *raiz n�o tem filho direito
        *raiz = (*raiz)->esq;

    else if ((*raiz)->esq == NULL) //se *raiz n�o tem filho esquerdo
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

int removeNaoRecursivo(Apontador *raiz, TChave chave)
{

    while (*raiz != NULL)
    {

        if ((*raiz)->info.chave == chave)
            break;

        if (chave > (*raiz)->info.chave)
            raiz = &(*raiz)->dir;

        else if (chave < (*raiz)->info.chave)
            raiz = &(*raiz)->esq;
    }

    if (*raiz == NULL)
        return 0;

    //Se nao caiu em nenhum dos ifs, achou-se o elemento a
    // ser removido
    Apontador aux = *raiz; //aux esta apontando pra quem eu quero remover

    if ((*raiz)->dir == NULL) // se *raiz n�o tem filho direito
        *raiz = (*raiz)->esq;

    else if ((*raiz)->esq == NULL) //se *raiz n�o tem filho esquerdo
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
    //Usa pos-ordem
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

