#ifndef SISTEMA_ELEITORAL_H_INCLUDED
#define SISTEMA_ELEITORAL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include "cedula.h"
#include "hash_abp.h"
#include "hash_lista.h"
#include "hash_duplo.h"
#include "tabela_candidatos.h"
#include "io.h"



enum TipoEstrutura
{
    HASH_DUPLO = 1,
    HASH_ABP = 2,
    HASH_LISTA = 3
};

enum ClassePolitica
{
    PREFEITO = 0,
    VEREADOR = 1
};

typedef struct
{
    HashLista hashLista;
    HashDuplo hashDuplo;
    HashAbp hashAbp;

    HashCandidatos hashVereadores, hashPrefeitos;

    int tipo_estrutura;

} Estruturas;


int obter_colisoes(Estruturas *est);

int obter_total_votos(Estruturas *est);

bool pesquisar_voto(Estruturas *est, TChave id, TElemento *e);

int registrar_escolha(Estruturas *est, int classe, int numeroCandidato, TElemento *voto);

bool editar_voto(Estruturas *est, TElemento e);

bool inserir_voto(Estruturas *est, TElemento e);

bool checar_voto(char *parametros[4], int *classe, int *candidato);

/**Insere um voto em uma das estruturas de <est> (Estruturas*).
 * A estrutura a ser inserida será a definida em <tipo_est> (int).
 * Os <parametros> (char*[4]) de entrada serão necessários para a contabilização do voto.
 * Retorna 1 em caso de sucesso, 0 do contrario*/
bool votar(Estruturas *est, char *parametros[4]);

bool apurar(Estruturas *est, char *parametros[4]);

bool remover_voto(Estruturas *est, char *parametros[4]);

void encerrar(Estruturas *est);

Estruturas *cria_estruturas(int, unsigned int, unsigned int, unsigned int);

#endif