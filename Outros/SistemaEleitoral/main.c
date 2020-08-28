#include <stdio.h>
#include <stdlib.h>
#include "cedula.h"
#include "hash_abp.h"
#include "hash_lista.h"
#include "hash_duplo.h"
#include "abp.h"

int main()
{
    printf("Hello world!\n");

  

    char strs[5][10] = {"foo", "bar", "bletch", "zipty", "zhadfg"};

    //HashAbp t = cria_hash_abp(10);

    //HashLista t = cria_hash_lista(10);

    HashDuplo t = cria_hash_duplo(10);

    TElemento e;

    for (int i = 0; i < 5; i++)
    {
        sprintf(e.id.tituloEleitor, "%s", strs[i]);

        print_tch(e.id);

        insere_hash_duplo(t, e);
        //insere_hash_lista(t, e);
        //insere_hash_abp(t, e);
    }
    
    printf("\n");
    print_hash_duplo(t);
    //print_hash_lista(t);
    //print_hash_abp(t);

    termina_hash_duplo(t);
    //termina_hash_lista(t);
    //termina_hash_abp(t);

    printf("\n");
    system("pause");


    return 0;
}
