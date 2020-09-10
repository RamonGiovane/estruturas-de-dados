#include <stdio.h>
#include <stdlib.h>
#include "abp.h"

int main()
{
    printf("Hello world!\n");

    Apontador p = criaABP();

    TElemento e;
    e.chave = 7;

    TElemento e1;
    e1.chave = 8;

    TElemento e2;
    e2.chave = 6;

    TElemento e3;
    e3.chave = 10;

    TElemento e4;

    insereNaoRecursivo(&p, e);
    insereNaoRecursivo(&p, e1);
    insereNaoRecursivo(&p, e2);
    insereNaoRecursivo(&p, e3);

    printInOrdem(p);

    printf("\n Remove 6 \n\n");

    removeNaoRecursivo(&p, 6);

    
    printf("\n Pesquisa 8:  ");
    pesquisaNaoRecursiva(p, 8, &e4);
    printf("%d\n\n", e4.chave);

    printInOrdem(p);

    terminaABP(p);

    printf("\n");
    system("pause");

    return 0;
}
