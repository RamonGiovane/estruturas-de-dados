#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include "cedula.h"
#include "hash_abp.h"
#include "hash_lista.h"
#include "hash_duplo.h"
#include "hash_candidatos.h"
#include "io.h"
#define STD_BUF 100

enum Acao
{
    VOTAR = 0,
    REMOVER = 1,
    APURAR = 2,
    ENCERRAR = 3,
    INVALIDO = -1
};

enum Estrutura
{
    HASH_DUPLO = 1,
    HASH_ABP = 2,
    HASH_LISTA = 3
};

enum Classes
{
    PREFEITO = 1,
    VEREADOR = 2
};

typedef struct
{
    HashLista hashLista;
    HashDuplo hashDuplo;
    HashAbp hashAbp;

    HashCandidatos hashVereadores, hashPrefeitos;

} Estruturas;


int obter_total_votos(Estruturas *est, int tipo_est)
{
    if (tipo_est == HASH_LISTA)
        return est->hashLista->n;

    if (tipo_est == HASH_DUPLO)
        return est->hashDuplo->numElementos;

    return est->hashAbp->n;
}

bool pesquisar_voto(Estruturas *est, int tipo_est, TChave id, TElemento *e)
{
    if (tipo_est == HASH_LISTA)
        return pesquisa_hash_lista(est->hashLista, id, e) != -1 ? true : false;
    if (tipo_est == HASH_DUPLO)
        return pesquisa_hash_duplo(est->hashDuplo, id, e) != -1 ? true : false;

    return pesquisa_hash_abp(est->hashAbp, id, e) != 0 ? true : false;
}

int registrar_escolha(Estruturas *est, int classe, int numeroCandidato, TElemento *voto)
{
    if (classe == PREFEITO)
    {
        if (voto->status.votouPrefeito)
            return votoInvalido();
        else
        {
            voto->prefeito = numeroCandidato;
            voto->status.votouPrefeito = 1;

            return computa_candidato(est->hashPrefeitos, numeroCandidato);
        }
    }
    else
    {
        if (voto->status.votouVereador)
            return votoInvalido();
        else
        {
            voto->vereador = numeroCandidato;
            voto->status.votouVereador = 1;
            return computa_candidato(est->hashVereadores, numeroCandidato);
        }
    }
    return 0;
}

bool editar_voto(Estruturas *est, int tipo_est, TElemento e)
{
    if (tipo_est == HASH_LISTA)
        return altera_hash_lista(est->hashLista, e);
    else if (tipo_est == HASH_DUPLO)
        return altera_hash_duplo(est->hashDuplo, e);

    return altera_hash_abp(est->hashAbp, e);
}

bool inserir_voto(Estruturas *est, int tipo_est, TElemento e)
{

    if (tipo_est == HASH_LISTA)
        return insere_hash_lista(est->hashLista, e);
    else if (tipo_est == HASH_DUPLO)
        return insere_hash_duplo(est->hashDuplo, e);

    return insere_hash_abp(est->hashAbp, e);
}

bool checar_voto(char *parametros[4], int *classe, int *candidato)
{

    //Checando classe
    if (parametros[1] == NULL)
        return invalido("classe do candidato");

    *classe = atoi(parametros[1]);

    if (*classe < 1 || *classe > 2)
        return invalido("classe do candidato");

    //Checando titulo
    if (parametros[2] == NULL)
        return invalido("titulo do eleitor");

    if (parametros[3] == NULL)
        return invalido("numero do candidato");

    *candidato = atoi(parametros[3]);

    return true;
}

/**Insere um voto em uma das estruturas de <est> (Estruturas*).
 * A estrutura a ser inserida será a definida em <tipo_est> (int).
 * Os <parametros> (char*[4]) de entrada serão necessários para a contabilização do voto.
 * Retorna 1 em caso de sucesso, 0 do contrario*/
bool votar(Estruturas *est, int tipo_est, char *parametros[4])
{

    int classe, candidato;
    TStatus def = TSTATUS_INIT;

    //Checar parametros
    if (!checar_voto(parametros, &classe, &candidato))
        return 0;

    //Salvando em TElemento
    TElemento voto;
    strcpy(voto.id.tituloEleitor, parametros[2]);

    bool votoExiste = pesquisar_voto(est, tipo_est, voto.id, &voto);

    //int totalDeVotos = obter_total_votos(est, tipo_est);

    if (!votoExiste)
        voto.status = def;

    int votosCandidato = registrar_escolha(est, classe, candidato, &voto);
    if (!votosCandidato)
        return 0;

    //Salavando TElemento em estrutura
    bool status = votoExiste ? editar_voto(est, tipo_est, voto) 
        : inserir_voto(est, tipo_est, voto);

    return !status ? votoInvalido() : votoValido(candidato, votosCandidato);
}

void encerrar(Estruturas *est)
{
    termina_hash_lista(est->hashLista);
    termina_hash_abp(est->hashAbp);
    termina_hash_duplo(est->hashDuplo);

    termina_hash_candidatos(est->hashPrefeitos);
    termina_hash_candidatos(est->hashVereadores);

    free(est);
}

bool interpretar_acao(Estruturas *est, int tipo_est, char *acao, char *resultado[4])
{

    quebrarString(acao, " ", resultado, 4);

    printf("ACAO %s\n\n ", acao);

    int a = atoi(resultado[0]);

    if (a < VOTAR || a > ENCERRAR)
        a = INVALIDO;
    switch (a)
    {
    case VOTAR:
        votar(est, tipo_est, resultado);
        return 1;

    case REMOVER:
        printf("\nAcao de remover");
        break;

    case APURAR:
        printf("Acao de apurar");
        break;

    case ENCERRAR:
        encerrar(est);
        return false;

    default:
        break;
    }

    return true;
}

Estruturas *cria_estruturas(unsigned int tamanhoVotos, unsigned int tamanhoCandidatos)
{
    Estruturas *est = (Estruturas *)malloc(sizeof(Estruturas));

    est->hashAbp = cria_hash_abp(tamanhoVotos);
    est->hashDuplo = cria_hash_duplo(tamanhoVotos);
    est->hashLista = cria_hash_lista(tamanhoVotos);

    est->hashPrefeitos = cria_hash_candidatos(tamanhoCandidatos);
    est->hashVereadores = cria_hash_candidatos(tamanhoCandidatos);

    return est;
}

int entrada_de_dados()
{
    Estruturas *est = cria_estruturas(1000, 100);

    int tipo_est = lerInteiro("Tipo da estrutura\n1-Hash Duplo\n2-Hash com Abp\n3-Hash com Lista\n->>");

    if (tipo_est < 1 || tipo_est > 3)
        return invalido("tipo estrutura invalido");

    char s_acao[STD_BUF];
    char *resultado[4];

    while (true)
    {

        lerString("Digite uma ação: ", s_acao, STD_BUF);

        if (!interpretar_acao(est, tipo_est, s_acao, resultado))
            return 0;
    }

    return 1;
}

int main()
{
    if (setlocale(LC_ALL, "portuguese") == NULL)
        printf("\nLocalizacao invalida\n");

    return entrada_de_dados();

    return 0;
}
