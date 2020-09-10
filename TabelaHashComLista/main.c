#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "lista.h"

int main()
{
    printf("Hello world!\n");

    HashLista t;

    t = cria_hash_lista(10);

    srand(1);

     TElemento e;

    for (size_t i = 0; i < 10; i++)
    {

        e.chave = rand() % 50;
        printf("\ne.chave = %d", e.chave);

        insere_hash_lista(t, e);
    }

    printf("\n");
    print_hash_lista(t);

    termina_hash_lista(t);

    printf("\n");
    system("pause");


    return 0;
}
