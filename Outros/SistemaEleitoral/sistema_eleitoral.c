#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "sistema_eleitoral.h"
#include "io.h"
#include "tabela_candidatos.h"
#include "g_mocks.h"

int obter_colisoes(Estruturas *est){
    if (est->tipo_estrutura == HASH_LISTA)
        return est->hashLista->numColisoes;

    if (est->tipo_estrutura == HASH_DUPLO)
        return est->hashDuplo->numColisoes;

    return est->hashAbp->numColisoes;
}

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
    int status;

    if (classe == PREFEITO)
    {
        if (voto->status.votouPrefeito)
            return fvotoInvalido();
        else
        {
            voto->prefeito = numeroCandidato;
            voto->status.votouPrefeito = 1;

            status = computa_candidato(est->hashPrefeitos, numeroCandidato);

            if(status) g_p_insert++; else g_p_not_insert++;

            return status;
        }
    }
    else
    {
        if (voto->status.votouVereador)
            return fvotoInvalido();
        else
        {
            voto->vereador = numeroCandidato;
            voto->status.votouVereador = 1;
            status = computa_candidato(est->hashVereadores, numeroCandidato);

            if(status) g_v_insert++; else g_v_not_insert++;

            return status;
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
    int status;
    if (est->tipo_estrutura == HASH_LISTA)
        status = insere_hash_lista(est->hashLista, e);
    else if (est->tipo_estrutura == HASH_DUPLO)
        status = insere_hash_duplo(est->hashDuplo, e);

    else status = insere_hash_abp(est->hashAbp, e);

    g_e_insert++;
    return status;
}

bool checar_voto(char *parametros[4], int *classe, int *candidato)
{

    //Checando classe
    if (parametros[1][0] == '\0')
        return invalido("classe do candidato");

    *classe = atoi(parametros[1]);

    if (*classe < 0 || *classe > 1)
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
    // if(strcmp(parametros[3], "52415\n") == 0)
    //     printf("\nSTOP!");

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
        return fvotoInvalido();


    //Salavando TElemento em estrutura
    bool status = votoExiste ? editar_voto(est, voto)
                             : inserir_voto(est, voto);

    return !status ? fvotoInvalido() : fvotoValido(candidato, votosCandidato);
}

void gerar_ranking(Estruturas *est, int classe, int tamanho){
    
   

    if(classe == PREFEITO){
         print_ranking_str(est->hashPrefeitos, tamanho);
    }

    else{ 
       
        print_ranking_str(est->hashVereadores, tamanho);
    }
}

bool apurar(Estruturas *est, char *parametros[4])
{

    int classe = 0;
    if (parametros[1][0] == '\0')
        return invalido("classe do candidato");

    classe = atoi(parametros[1]);
    if (classe < 0 || classe > 1)
        return invalido("classe do candidato");


    int tamanho_ranking = 0;
    if (parametros[2][0] == '\0')
        return invalido("tamanho do ranking");

    tamanho_ranking = atoi(parametros[2]);
    if (tamanho_ranking < 1 || tamanho_ranking > 100)
        return invalido("tamanho do ranking");

    
    gerar_ranking(est, classe, tamanho_ranking);

    // print_ranking(ranking);

    // termina_ranking(ranking);

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
        g_e_del++; //mock

        if (e.status.votouPrefeito)
            if(decrementa_candidato(est->hashPrefeitos, e.prefeito)) g_p_del++; //mock
        if (e.status.votouVereador)
            if(decrementa_candidato(est->hashVereadores, e.vereador)) g_v_del++; //mock
    }

    int votosValidos = obter_total_votos(est);

    return status ? fremocao_valida(votosValidos) : fremocao_invalida(votosValidos);
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

Estruturas *cria_estruturas(int tipo_estrutura, unsigned int prefeitos, unsigned int vereadores, unsigned int candidatos)
{
    Estruturas *est = (Estruturas *)malloc(sizeof(Estruturas));

     est->hashAbp = NULL; est->hashDuplo = NULL; est->hashLista = NULL;


    candidatos *= 1.5;
    vereadores *= 1.5;
    prefeitos *= 1.5;

    while(!checar_numero_primo(candidatos)) 
        candidatos++;

    if (tipo_estrutura == HASH_ABP)
        est->hashAbp = cria_hash_abp(candidatos);

    else if (tipo_estrutura == HASH_DUPLO)
        est->hashDuplo = cria_hash_duplo(candidatos);

    else if (tipo_estrutura == HASH_LISTA)
        est->hashLista = cria_hash_lista(candidatos);

    else
        return NULL;

    while(!checar_numero_primo(prefeitos)) 
        prefeitos++;

    while(!checar_numero_primo(vereadores))
         vereadores++;

    est->tipo_estrutura = tipo_estrutura;

    est->hashPrefeitos = cria_hash_candidatos(prefeitos);
    est->hashVereadores = cria_hash_candidatos(vereadores);

    return est;
}
