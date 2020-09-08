#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

#include "io.h"
#include "instancia.h"

#define STD_BUF 256

// Tenta abrir o arquivo de entrada para leitura e o arquivo de saída para a
// escrita. Não é preciso manusear ponteiros aqui, pois isso ocorre
// internamente. Retorna 0 se nao for possivel abrir um dos arquivos.
int abrir_arquivos(int argc, char *argv[]) {
    if (argc != 3) return invalido("parametros de entrada do programa.");

    if (!abrir_arquivo_leitura(argv[1])) return invalido("arquivo de entrada");

    if (!abrir_arquivo_escrita(argv[2])) return invalido("arquivo de saída");

    return 1;
}

//Calcula o menor instante em que a tarefa que for processada por último terminará seu processamento.
void calcula_resolucao(Instancia ins){
   if(ins->numeroPedidos == 0) return;

    ordernar_pedidos(ins);

    int instante = ins->pedidos[0].inicio;
    for(int i = 0; i<ins->numeroPedidos; i++){

        if(ins->pedidos[i].inicio <= instante)
            instante += ins->pedidos[i].duracao;
        else instante = ins->pedidos[i].inicio + ins->pedidos[i].duracao;
    }

    ins->resolucao = instante;
}

//Adiciona um pedido a uma instancia
int novo_pedido(Instancia ins, int instante, int duracao){
    Pedido p;
    p.duracao = duracao;
    p.inicio = instante;

    return adicionar_instancia(ins, p);
}

//Calcula a resoulução da instancia, imprime no arquivo de saída e desaloca a memoria reservada por ela
void fechar_instancia(Instancia ins){
    if(ins){
        calcula_resolucao(ins);
        fiprint(ins->resolucao);
        termina_instancia(ins);
    }
}

//Fecha uma instancia se for diferente de NULL, aloca espaço e retorna uma nova
Instancia nova_instancia(Instancia ins, int tamanho){
    
    fechar_instancia(ins);
    
    ins = criar_instancia(tamanho);

    return ins;   
}
// Fecha os arquivos se estiverem abertos. Retorna sempre 0.
int fechar_arquivos() {
    // Tenta fechar os arquivos
    fechar_arquivo_escrita();
    fechar_arquivo_leitura();

    return 0;
}

//Abre e lê as linhas do arquivo de entrada. Abre o arquivo de saida. Termina a execucao quando o EOF da entrada for encontrado
int entrada_de_dados(int argc, char* argv[]){

    char lin[256];
    char* parametros[2];
    Instancia ins = NULL;

    if (!abrir_arquivos(argc, argv)) return fechar_arquivos();

    long c = cronometrar(0);

    while (ler_linha_arquivo(lin, STD_BUF))
    {
        int pedacos = quebrarString(lin, " ", parametros, STD_BUF);

        if(pedacos == 1)
            ins = nova_instancia(ins, atoi(parametros[0]));
        
        if(pedacos == 2)
            novo_pedido(ins, atoi(parametros[0]), atoi(parametros[1]));

    }

    fechar_instancia(ins);

    printf("Tempo de execução: %lu ms", cronometrar(c));

    return fechar_arquivos();
}

int main(int argc, char *argv[]) {
    
    setlocale(LC_ALL, "portuguese");
    return entrada_de_dados(argc, argv);
}

