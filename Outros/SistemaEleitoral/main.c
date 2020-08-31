#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include "sistema_eleitoral.h"
#define STD_BUF 100

bool interpretar_acao(Estruturas *est, char *acao, char *resultado[4])
{

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
        break;

    case ENCERRAR:
        encerrar(est);
        return false;

    default:
        break;
    }

    return true;
}


int entrada_de_dados(int argc, char* argv[])
{
    int tipo_est = lerInteiro("Tipo da estrutura\n1-Hash Duplo\n2-Hash com Abp\n3-Hash com Lista\n->>");

    Estruturas *est = cria_estruturas(tipo_est, 1000, 100);

    if (est == NULL)
        return invalido("tipo estrutura invalido");

    char s_acao[STD_BUF];
    char *resultado[4];

    while (true)
    {

        lerString("\nDigite uma ação: ->>", s_acao, STD_BUF);

        if (!interpretar_acao(est, s_acao, resultado))
            return 0;
    }

    return 1;
}

int main(int argc, char* argv[])
{
    if (setlocale(LC_ALL, "portuguese") == NULL)
        printf("\nLocalizacao invalida\n");

    return entrada_de_dados(argc, argv);

    return 0;
}
