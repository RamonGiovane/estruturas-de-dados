#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include "sistema_eleitoral.h"
#include <time.h>
#define STD_BUF 100

#include "g_mocks.h"


bool interpretar_acao(Estruturas *est, char *acao){


    char *resultado[4];

    quebrarString(acao, " ", resultado, 4);

    int a = atoi(resultado[0]);



    switch (a)
    {
    case VOTAR:
        votar(est, resultado);
        return 1;

    case REMOVER:
        remover_voto(est, resultado);
        return 1;

    case APURAR:
        apurar(est, resultado);
        return 1;

    case ENCERRAR:
        return 0;

    default:
        return 1;
    }

}

int ler_tipo_estrutura(){

    char linha[255];
    ler_linha_arquivo(linha, 255);

    int t = atoi(linha);

    return (t < 1 || t > 3)  ? invalido("tipo de estrutura") : t;
}

int ler_capacidades(int * numVereadores, int * numPrefeitos, int * numEleitores){

    char linha[255], *valores[3];
    ler_linha_arquivo(linha, 255);

    quebrarString(linha, " ", valores, 3);

    *numVereadores = atoi(valores[0]);
    *numPrefeitos = atoi(valores[1]);
    *numEleitores = atoi(valores[2]);

    return 1;
}


int ler_entrada(int argc, char* argv[]){

    long tempo = cronometrar(0);

    if(!abrir_arquivo_leitura("input.txt"))
        return invalido("arquivo de entrada");

    if(!abrir_arquivo_escrita("output.txt"))
        return invalido("arquivo de saída");


    char linha[255];
    int vereadores, prefeitos, candidatos;

    //Le a primeira linha: tipo da estrutura
    int tipo_est = ler_tipo_estrutura();

    //Le a segunda linha: numero de candidatos
    ler_capacidades(&vereadores, &prefeitos, &candidatos);

    Estruturas *est = cria_estruturas(tipo_est, vereadores, prefeitos, candidatos);

    if (est == NULL)
        return invalido("tipo estrutura invalido");



    //Lê acoes
    while (ler_linha_arquivo(linha, 255))
    {

        fprint(linha);
        
        if (!interpretar_acao(est, linha))
            break;
    }

    print_exec(obter_colisoes(est), cronometrar(tempo));

    print_ranking_str(est->hashPrefeitos, 5000);

    encerrar(est);

    

    printf("\n\nEleitores inseridos: %d\nEleitores removidos: %d\nVereadores inseridos:%d", g_e_insert, g_e_del, g_v_insert);
    printf("\nVereadores removidos: %d\nPrefeitos inseridos: %d\nVereadores removidos: %d\n", g_v_del, g_p_insert, g_p_del);


    system("pause");

    fechar_arquivo_escrita();
    fechar_arquivo_leitura();

    return 0;

}


int main(int argc, char* argv[])
{

    if (setlocale(LC_ALL, "portuguese") == NULL)
        printf("\nLocalizacao invalida\n");

    return ler_entrada(argc, argv);


}
