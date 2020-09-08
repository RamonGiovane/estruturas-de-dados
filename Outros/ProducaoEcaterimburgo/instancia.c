#include <stdlib.h>
#include "instancia.h"
#define N 100000
#define P 10000

Instancia criar_instancia(int tamanho){
    
    if(tamanho > N) return NULL;

    Instancia ins = (Instancia) malloc(sizeof(t_instancia));
    
    if(ins != NULL){
        ins->numeroPedidos = 0;
        ins->pedidos = (Pedido*) malloc(sizeof(Pedido)*tamanho);
        ins->tamanho = tamanho;
        ins->resolucao = 0;
    }

    return ins;
}


int adicionar_instancia(Instancia ins, Pedido p){
    
    if(!ins || ins->numeroPedidos == ins->tamanho) return 0;
   
    if(p.duracao > P) return 0;
   
    ins->pedidos[ins->numeroPedidos] = p;
    ins->numeroPedidos += 1;

    return 1;

}

int comparar_pedidos(const void * e1, const void* e2){
    const Pedido * p1 = (Pedido*) e1, * p2 = (Pedido*) e2;

    if(p1->inicio < p2->inicio)
        return -1;

    if(p1->inicio > p2->inicio)
        return 1;
    
    return p1->duracao - p2->duracao;

}

int ordernar_pedidos(Instancia ins){
    if(!ins || ins->numeroPedidos == 0)
        return 0;
    
    qsort(ins->pedidos, ins->numeroPedidos, sizeof(Pedido), comparar_pedidos);

    return 1;
}

void termina_instancia(Instancia ins){
    if(!ins) return;

    free(ins->pedidos);
    free(ins);
}

