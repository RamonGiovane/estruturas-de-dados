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

    insereRecursivo(&p, e);
    insereRecursivo(&p, e1);
    insereRecursivo(&p, e2);
    insereRecursivo(&p, e3);


    printInOrdem(p);

    printf("\n Remove 6 \n\n");

    removeRecursivo(&p, 7);

    printInOrdem(p);

    terminaABP(p);


    return 0;


}
