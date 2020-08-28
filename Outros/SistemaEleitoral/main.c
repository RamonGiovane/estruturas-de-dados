#include <stdio.h>
#include <stdlib.h>
#include "cedula.h"
#include "hash_abp.h"
#include "abp.h"

int main()
{
    printf("Hello world!\n");

    int i;
    HashAbp t;

    t = cria_hash_abp(10);

    srand(1);
    
     TElemento e;

    for (size_t i = 0; i < 10; i++)
    {
       
        sprintf(e.id.tituloEleitor, "%d", rand() % 50);

        print_tch(e.id);

        insere_hash_abp(t, e);
    }
    
    printf("\n");
    print_hash_abp(t);

    termina_hash_abp(t);

    printf("\n");
    system("pause");


    return 0;
}
