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

enum TipoEstrutura
{
    HASH_DUPLO = 1,
    HASH_ABP = 2,
    HASH_LISTA = 3
};

enum ClassePolitica
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

    int tipo_estrutura;

} Estruturas;


int obter_total_votos(Estruturas *est)
{
    if (est->tipo_estrutura  == HASH_LISTA)
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

    bool votoExiste = pesquisar_voto(est,voto.id, &voto);

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

bool remocao_valida(int votosValidos){
    printf("\nmeliante removido, %d votos válidos no sistema.\n", votosValidos);
    return true;
}

bool remocao_invalida(int votosValidos){
    printf("\nmeliante não removido, %d votos válidos no sistema.\n", votosValidos);
    return false;
}


bool remover_voto(Estruturas *est, bool printLog, char *parametros[4]){
    
    if(parametros[1][0] == '\0')
        return invalido("titulo do eleitor");

    TChave ch;
    int status;
    strcpy(ch.tituloEleitor, parametros[1]);

    TElemento e;
    if(est->tipo_estrutura == HASH_LISTA)
       status = remove_hash_lista(est->hashLista, ch, &e);
    
    else if(est->tipo_estrutura == HASH_DUPLO)
        status = remove_hash_duplo(est->hashDuplo, ch, &e);
    
    else status = remove_hash_abp(est->hashAbp, ch, &e);

    if(status){
        if(e.status.votouPrefeito)
            decrementa_candidato(est->hashPrefeitos, e.prefeito);
        if(e.status.votouVereador)
            decrementa_candidato(est->hashVereadores, e.vereador);
    }

    if(!printLog) return status;

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

bool interpretar_acao(Estruturas *est, char *acao, char *resultado[4])
{

    quebrarString(acao, " ", resultado, 4);

    printf("ACAO %s\n\n ", acao);

    int a = atoi(resultado[0]);

    if (a < VOTAR || a > ENCERRAR)
        a = INVALIDO;
    switch (a)
    {
    case VOTAR:
        votar(est, resultado);
        return 1;

    case REMOVER:
        remover_voto(est, true, resultado);
        return 1;

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

Estruturas* cria_estruturas(int tipo_estrutura, unsigned int tamanhoVotos, unsigned int tamanhoCandidatos)
{
    Estruturas *est = (Estruturas *)malloc(sizeof(Estruturas));

    if(tipo_estrutura == HASH_ABP)
        est->hashAbp = cria_hash_abp(tamanhoVotos);

    else if(tipo_estrutura == HASH_DUPLO)
        est->hashDuplo = cria_hash_duplo(tamanhoVotos);
    
    else if(tipo_estrutura == HASH_LISTA)
        est->hashLista = cria_hash_lista(tamanhoVotos);
    
    else
        return NULL;
    
    est->tipo_estrutura = tipo_estrutura;

    est->hashPrefeitos = cria_hash_candidatos(tamanhoCandidatos);
    est->hashVereadores = cria_hash_candidatos(tamanhoCandidatos);

    

    return est;
}

int entrada_de_dados()
{
    int tipo_est = lerInteiro("Tipo da estrutura\n1-Hash Duplo\n2-Hash com Abp\n3-Hash com Lista\n->>");

    Estruturas *est = cria_estruturas(tipo_est, 1000, 100);

    if(est == NULL) return invalido("tipo estrutura invalido");

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

int main()
{
    if (setlocale(LC_ALL, "portuguese") == NULL)
        printf("\nLocalizacao invalida\n");

    return entrada_de_dados();

    return 0;
}
