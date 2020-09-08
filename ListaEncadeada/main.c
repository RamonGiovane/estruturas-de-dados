#include <stdio.h>

#include "lista.h"

int main() {
    printf("Cria lista");

    Lista l = cria_lista();

    printf("\nInsere 1, 3, 9, 6");

    TElemento e;

    e.chave = 1;
    insere_apos(l, e);

    e.chave = 3;
    insere_apos(l, e);

    e.chave = 9;
    insere_apos(l, e);

    e.chave = 6;
    insere_apos(l, e);

    printf("\n");
    print_lista(l);

    printf("\nRemove 3");

    remove_elemento(l, 3, &e);
    printf("\nElemento Removido: %d", e.chave);

    printf("\n");
    print_lista(l);

    termina_lista(l);

    return 1;
}