#include <stdio.h>
#include <stdlib.h>
#include "cedula.h"
#include "abp.h"

///Insere TElemento na arvore a partir de um ponteiro da raiz
int insere_abp(Abp *raiz, TElemento e)
{

    if (*raiz == NULL)
    { ///Chegou na folha
        *raiz = (Abp)malloc(sizeof(TNodo));
        (*raiz)->info = e;
        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;

        return 1; /// Inserção realizada com sucesso
    }

    ///Se é maior que a raiz vai para direita
    if (tchcmp(e.id, (*raiz)->info.id) > 0)
        return insere_abp(&(*raiz)->dir, e);

    ///Se é menor que a raiz vai para esquerda
    if (tchcmp(e.id, (*raiz)->info.id) < 0)
        return insere_abp(&(*raiz)->esq, e);

    return 0; ///Elemento já existe
}


///Pesquisa a partir da raiz, TChave e se achar retorna como
/// TElemento*
int pesquisa_abp(Abp raiz, TChave id,
                      TElemento *retorno)
{
    if (raiz == NULL)
        return 0;

    if (tchcmp(raiz->info.id, id) == 0)
    {
        *retorno = raiz->info;
        return 1;
    }

    if (tchcmp(id, raiz->info.id) > 0)
        return pesquisa_abp(raiz->dir, id, retorno);

    //se nao é maior, nem igual, vai para a esquerda
    return pesquisa_abp(raiz->esq, id, retorno);
}

///Pesquisa a partir da raiz, TChave e se achar retorna como
/// TElemento*
int altera_abp(Abp raiz, TElemento e)
{
    if (raiz == NULL)
        return 0;

    if (tchcmp(raiz->info.id, e.id) == 0)
    {
        raiz->info = e;
        return 1;
    }

    if (tchcmp(e.id, raiz->info.id) > 0)
        return altera_abp(raiz->dir, e);

    //se nao é maior, nem igual, vai para a esquerda
    return altera_abp(raiz->esq, e);
}



int remove_abp(Abp *raiz, TChave id)
{

    if (*raiz == NULL)
        return 0;

    if (tchcmp(id, (*raiz)->info.id) > 0)
        return remove_abp(&(*raiz)->dir, id);

    if (tchcmp(id, (*raiz)->info.id) < 0)
        return remove_abp(&(*raiz)->esq, id);

    //Se nao caiu em nenhum dos ifs, achou-se o elemento a
    // ser removido
    Abp aux = *raiz; //aux esta apontando pra quem eu quero remover

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


void printInOrdem(Abp p)
{
    //ESQUERDA, PROCESSA PAI, DIREITA
    if (p != NULL)
    {
        printInOrdem(p->esq);
        print_tch(p->info.id);
        printInOrdem(p->dir);
    }
}

void termina_abp(Abp p)
{
    //Usa pos-ordem
    if (p != NULL)
    {
        termina_abp(p->esq);
        termina_abp(p->dir);
        free(p);
    }
}

Abp cria_abp()
{
    return NULL;
}

