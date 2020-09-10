#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "abp.h"

int main()
{
    printf("Hello world!\n");

    int i;
    TipoTabela t;

    t = criaTabela(10);

    srand(1);
    
     TElemento e;

    for (size_t i = 0; i < 10; i++)
    {
       
        e.chave = rand() % 50;
        printf("\ne.chave = %d", e.chave);

        insereElemento(t, e);
    }
    
    printf("\n");
    imprime(t);

    terminaTabela(t);

    printf("\n");
    system("pause");


    return 0;
}
