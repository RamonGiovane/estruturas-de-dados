#include "lista.h"

#include <stdio.h>
#include <stdlib.h>


Lista cria_lista() {
    Lista l;
    l = (Lista)malloc(sizeof(tipo_lista));
    if (l) {
        l->first = NULL;
        l->last = NULL;
        l->n = 0;
    }
    return l;
}

void termina_lista(Lista l) {
    Nodo p;
    while (l->first) {
        p = l->first;
        l->first = l->first->next;
        free(p);
    }
    free(l);
}

int insere_inicio(Lista l, TElemento e) {
    Nodo p;
    p = (Nodo)malloc(sizeof(tipo_nodo));

    if (!p) return 0;

    p->info = e;
    p->next = l->first;
    l->first = p;

    if (l->n == 0) l->last = p;

    l->n++;
    return 1;
}

int remove_elemento(Lista l, TChave ch, TElemento *e) {
    Nodo p, ant;

    if (!l || l->n == 0) return 0;

    p = l->first;
    while (p && p->info.chave != ch) {
        ant = p;
        p = p->next;
    }

    if (!p) return 0;

    *e = p->info;

    if (p == l->first)
        l->first = l->first->next;

    else if (p == l->last) {
        l->last = ant;
        l->last->next = NULL;
    } else
        ant->next = p->next;

    l->n--;
    free(p);
    return 1;
}

int altera_elemento(Lista l, TElemento e) {
    Nodo n;

    if (!l || l->n == 0) return 0;

    n = l->first;

    while (n) {
        if (n->info.chave == e.chave) {
            n->info = e;
            return 1;
        }

        n = n->next;
    }

    return 0;
}

int insere_apos(Lista l, TElemento e) {
    Nodo p;

    if (l->n == 0) return insere_inicio(l, e);

    p = (Nodo )malloc(sizeof(tipo_nodo));

    if (!p) return 0;

    p->info = e;

    l->last->next = p;
    l->last = p;
    p->next = NULL;
    l->n++;
    return 1;
}

int busca_elemento(Lista l, TChave ch, TElemento *e) {
    Nodo p;

    p = l->first;
    while (p) {
        if (p->info.chave == ch) {
            *e = p->info;
            return 1;
        }
        p = p->next;
    }

    return 0;
}

int lista_vazia(Lista l) { return l->n == 0; }

void print_lista(Lista l) {
    if (l == NULL || l->n == 0) return;

    Nodo n = l->first;

    while (n) {
        printf("%d\n", n->info.chave);
        n = n->next;
    }
}
