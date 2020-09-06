#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include "sistema_eleitoral.h"
#include <time.h>
#define STD_BUF 256

//Tipos possiveis de ações
enum Acao
{
    VOTAR = 0,
    REMOVER = 1,
    APURAR = 2,
    ENCERRAR = 3,
};

// ! Deve ser chamado quando o arquivo estiver apontando para a terceira linha do arquivo em diante
//Lê uma ação, computa e printa o resultado no arquivo de saída.
//Retorna 1 se a ação for lida ou 0 se ação lida for == 3.
bool ler_acao(Estruturas *est, char *acao)
{

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

// ! Deve ser chamado quando arquivo estiver apontando para a primeira linha do arquivo;
// Lê o numero da estrutura. Em caso de erro, retorna 0.
int ler_tipo_estrutura()
{

    char linha[STD_BUF];
    ler_linha_arquivo(linha, STD_BUF);

    int t = atoi(linha);

    return (t < 1 || t > 3) ? invalido("tipo de estrutura") : t;
}

// ! Deve ser chamado quando o arquivo estiver apontando para a segunda linha do arquivo.
//Lê o numero de vereadores, prefeitos e eleitores. Retorna-os por referencia 
int ler_capacidades(int *numVereadores, int *numPrefeitos, int *numEleitores)
{

    char linha[255], *valores[3];
    ler_linha_arquivo(linha, 255);

    quebrarString(linha, " ", valores, 3);

    *numVereadores = atoi(valores[0]);
    *numPrefeitos = atoi(valores[1]);
    *numEleitores = atoi(valores[2]);

    return 1;
}

//Tenta abrir o arquivo de entrada para leitura e o arquivo de saída para a escrita.
//Não é preciso manusear ponteiros aqui, pois isso ocorre internamente.
//Retorna 0 se nao for possivel abrir um dos arquivos.
int abrir_arquivos(int argc, char * argv[]){
    
    if(argc != 3)
        return invalido("parametros de entrada do programa.");

    if (!abrir_arquivo_leitura(argv[1]))
        return invalido("arquivo de entrada");

    if (!abrir_arquivo_escrita(argv[2]))
        return invalido("arquivo de saída");

    return 1;
}

//Fecha os arquivos se estiverem abertos. Retorna sempre 0.
int fechar_arquivos(){

    //Tenta fechar os arquivos
    fechar_arquivo_escrita();
    fechar_arquivo_leitura();

    return 0;
}

//Abre os arquivos passados nos argumentos de inicio do programa.
//Le o arquivo de entrada, gera a saida.
//Retorna 0 se nenhum erro ocorrer.
int entrada_de_dados(int argc, char *argv[])
{

    if(!abrir_arquivos(argc, argv))
        return fechar_arquivos();

    char linha[255];
    int vereadores, prefeitos, eleitores;

    //Comeca a cronometrar
    long tempo = cronometrar(0);

    //Le a primeira linha: tipo da estrutura
    int tipo_est = ler_tipo_estrutura();

    //Le a segunda linha: numero de candidatos e eleitores
    ler_capacidades(&vereadores, &prefeitos, &eleitores);

    Estruturas *est = cria_estruturas(tipo_est, vereadores, prefeitos, eleitores);

    if (est == NULL)
        return invalido("tipo estrutura invalido");

    //Lê acoes
    while (ler_linha_arquivo(linha, 255))
    {

        //Le uma linha com uma ação
        fprint(linha);

        //Se ler_acao retornar 0 significa que a ação 3 foi lida
        if (!ler_acao(est, linha))
            break;
    }

    //Para o cronometro
    tempo = cronometrar(tempo);

    printf("Numero colisoes vereador: %d\nNumero colisoes prefeito: %d\n", est->hashVereadores->numColisoes, est->hashPrefeitos->numColisoes);
    //Printa resumo
    print_exec(obter_colisoes(est), tempo);
    fprint_exec(obter_colisoes(est), tempo);

    //Encerra as estruturas
    encerrar(est);

    
    return fechar_arquivos();
}

int main(int argc, char *argv[])
{

    if (setlocale(LC_ALL, "portuguese") == NULL)
        printf("\nLocalizacao invalida\n");

    return entrada_de_dados(argc, argv);
}
