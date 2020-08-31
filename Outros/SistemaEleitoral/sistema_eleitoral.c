#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "sistema_eleitoral.h"
#include "io.h"
#include "tabela_candidatos.h"


int obter_total_votos(Estruturas *est)
{
    if (est->tipo_estrutura == HASH_LISTA)
        return est->hashLista->n;

    if (est->tipo_estrutura == HASH_DUPLO)
        return est->hashDuplo->numElementos;

    return est->hashAbp->n;
}

bool pesquisar_voto(Estruturas *est, TChave id, TElemento *e)
{
    if (est->tipo_estrutura == HASH_LISTA)
        return pesquisa_hash_lista(est->hashLista, id, e) != -1 ? true : false;
    if (est->tipo_estrutura == HASH_DUPLO)
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

bool editar_voto(Estruturas *est, TElemento e)
{
    if (est->tipo_estrutura == HASH_LISTA)
        return altera_hash_lista(est->hashLista, e);
    else if (est->tipo_estrutura == HASH_DUPLO)
        return altera_hash_duplo(est->hashDuplo, e);

    return altera_hash_abp(est->hashAbp, e);
}

bool inserir_voto(Estruturas *est, TElemento e)
{

    if (est->tipo_estrutura == HASH_LISTA)
        return insere_hash_lista(est->hashLista, e);
    else if (est->tipo_estrutura == HASH_DUPLO)
        return insere_hash_duplo(est->hashDuplo, e);

    return insere_hash_abp(est->hashAbp, e);
}

bool checar_voto(char *parametros[4], int *classe, int *candidato)
{

    //Checando classe
    if (parametros[1][0] == '\0')
        return invalido("classe do candidato");

    *classe = atoi(parametros[1]);

    if (*classe < 1 || *classe > 2)
        return invalido("classe do candidato");

    //Checando titulo
    if (parametros[2][0] == '\0')
        return invalido("titulo do eleitor");

    if (parametros[3][0] == '\0')
        return invalido("numero do candidato");

    *candidato = atoi(parametros[3]);

    return true;
}

/**Insere um voto em uma das estruturas de <est> (Estruturas*).
 * A estrutura a ser inserida será a definida em <tipo_est> (int).
 * Os <parametros> (char*[4]) de entrada serão necessários para a contabilização do voto.
 * Retorna 1 em caso de sucesso, 0 do contrario*/
bool votar(Estruturas *est, char *parametros[4])
{

    int classe, candidato;
    TStatus def = TSTATUS_INIT;

    //Checar parametros
    if (!checar_voto(parametros, &classe, &candidato))
        return 0;

    //Salvando em TElemento
    TElemento voto;
    strcpy(voto.id.tituloEleitor, parametros[2]);

    bool votoExiste = pesquisar_voto(est, voto.id, &voto);

    //int totalDeVotos = obter_total_votos(est, tipo_est);

    if (!votoExiste)
        voto.status = def;

    int votosCandidato = registrar_escolha(est, classe, candidato, &voto);
    if (!votosCandidato)
        return 0;

    //Salavando TElemento em estrutura
    bool status = votoExiste ? editar_voto(est, voto)
                             : inserir_voto(est, voto);

    return !status ? votoInvalido() : votoValido(candidato, votosCandidato);
}

Ranking gerar_ranking(Estruturas *est, int classe, int tamanho){
    
    if(classe == PREFEITO)
        return obter_ranking(est->hashPrefeitos, tamanho);

    return obter_ranking(est->hashVereadores, tamanho);
}

bool apurar(Estruturas *est, char *parametros[4])
{

    int classe = 0;
    if (parametros[1][0] == '\0')
        return invalido("classe do candidato");

    classe = atoi(parametros[1]);
    if (classe < 1 || classe > 3)
        return invalido("classe do candidato");


    int tamanho_ranking = 0;
    if (parametros[2][0] == '\0')
        return invalido("tamanho do ranking");

    tamanho_ranking = atoi(parametros[2]);
    if (tamanho_ranking < 1 || tamanho_ranking > 100)
        return invalido("tamanho do ranking");

    
    Ranking ranking = gerar_ranking(est, classe, tamanho_ranking);

    print_ranking(ranking);

    termina_ranking(ranking);

    return 1;
    
}

bool remover_voto(Estruturas *est, char *parametros[4])
{

    if (parametros[1][0] == '\0')
        return invalido("titulo do eleitor");

    TChave ch;
    int status;
    strcpy(ch.tituloEleitor, parametros[1]);

    TElemento e;
    if (est->tipo_estrutura == HASH_LISTA)
        status = remove_hash_lista(est->hashLista, ch, &e);

    else if (est->tipo_estrutura == HASH_DUPLO)
        status = remove_hash_duplo(est->hashDuplo, ch, &e);

    else
        status = remove_hash_abp(est->hashAbp, ch, &e);

    if (status)
    {
        if (e.status.votouPrefeito)
            decrementa_candidato(est->hashPrefeitos, e.prefeito);
        if (e.status.votouVereador)
            decrementa_candidato(est->hashVereadores, e.vereador);
    }

    int votosValidos = obter_total_votos(est);

    return status ? remocao_valida(votosValidos) : remocao_invalida(votosValidos);
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

Estruturas *cria_estruturas(int tipo_estrutura, unsigned int tamanhoVotos, unsigned int tamanhoCandidatos)
{
    Estruturas *est = (Estruturas *)malloc(sizeof(Estruturas));

    if (tipo_estrutura == HASH_ABP)
        est->hashAbp = cria_hash_abp(tamanhoVotos);

    else if (tipo_estrutura == HASH_DUPLO)
        est->hashDuplo = cria_hash_duplo(tamanhoVotos);

    else if (tipo_estrutura == HASH_LISTA)
        est->hashLista = cria_hash_lista(tamanhoVotos);

    else
        return NULL;

    est->tipo_estrutura = tipo_estrutura;

    est->hashPrefeitos = cria_hash_candidatos(tamanhoCandidatos);
    est->hashVereadores = cria_hash_candidatos(tamanhoCandidatos);

    return est;
}
