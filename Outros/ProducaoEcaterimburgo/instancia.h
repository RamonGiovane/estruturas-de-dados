#ifndef INSTANCIA_H_INCLUDED
#define INSTANCIA_H_INCLUDED

typedef struct Pedido {
    int inicio;
    int duracao;
} Pedido;

typedef struct {
    Pedido* pedidos;
    int numeroPedidos;
    int tamanho;

    int resolucao;
} t_instancia;
typedef t_instancia* Instancia;


Instancia criar_instancia(int tamanho);
int adicionar_instancia(Instancia ins, Pedido p);
int ordernar_pedidos(Instancia ins);
void termina_instancia(Instancia ins);

#endif