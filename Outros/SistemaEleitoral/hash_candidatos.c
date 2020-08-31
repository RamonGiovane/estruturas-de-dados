#include "hash_candidatos.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Função Hash A: Gera um valor hash a partir de um int
unsigned int hash_a(int ch, unsigned int m)
{
    printf(" hash %d - hash mod M %d\n", ch, ch % m);
    return ch % m;
}

//Funcão Hash B: Gera uma valor hash a partir de um int
unsigned int hash_b(int ch, unsigned int m)
{
    return (11 - ch) % m;
}

HashCandidatos cria_hash_candidatos(unsigned int n)
{
    HashCandidatos t = (HashCandidatos)malloc(sizeof(t_hash_candidatos));
    unsigned int i;
    if (t != NULL)
    {
        t->elementos = (TCandidato *)malloc(sizeof(TCandidato) * n);
        if (t->elementos != NULL)
        {
            for (i = 0; i < n; i++)
                t->elementos[i].status.vazio = 1;
            t->tamanho = n;
            t->numElementos = 0;
        }
        else
        {
            free(t);
        }
    }
    return t;
}

int insere_candidato(HashCandidatos t, TCandidato e)
{
    int posicao = hash_a(e.numeroCandidato, t->tamanho), incremento;
    TCandidato eAux;

    if (t->numElementos == t->tamanho)
        return 0;

    if (pesquisa_candidato(t, e.numeroCandidato, &eAux) != -1)
        return 0;

    incremento = hash_b(e.numeroCandidato, t->tamanho);
    while (1)
    {

        if (t->elementos[posicao % t->tamanho].status.vazio == 0)
        {
            posicao += incremento;
        }

        else
        {
            t->elementos[posicao % t->tamanho] = e;
            t->numElementos++;
            return 1;
        }
    }
}

/*retorna a posição da tabela caso encontre ou -1 em caso
contrário*/
int pesquisa_candidato(HashCandidatos t, int num, TCandidato *c)
{

    if (!t || t->numElementos == 0)
        return -1;

    int posicao = hash_a(num, t->tamanho), i = 0, incremento;

    incremento = hash_b(num, t->tamanho);

    while (i < t->tamanho)
    {
        if (t->elementos[posicao % t->tamanho].status.vazio == 0 &&
            num == t->elementos[posicao % t->tamanho].numeroCandidato)
        {

            *c = t->elementos[posicao % t->tamanho];
            return posicao % t->tamanho;
        }
        i++;
        posicao += incremento;
    }

    return -1;
}

/*Adiciona -1 voto ao candidato indicado por seu <numero>. Se ele ainda não existir na tabela, retorna-se 0.
Caso exista, retorna-se o número de votos que ele possui*/
int decrementa_candidato(HashCandidatos t, int numero)
{

    if (!t)
        return 0;

    int posicao = hash_a(numero, t->tamanho), i = 0, incremento;

    incremento = hash_b(numero, t->tamanho);

    while (i < t->tamanho)
    {

        //Se achar...
        if (t->elementos[posicao % t->tamanho].status.vazio == 0 &&
            numero == t->elementos[posicao % t->tamanho].numeroCandidato)
        {

            //Computa mais um voto
            t->elementos[posicao % t->tamanho].status.numeroVotos -= 1;
            return  t->elementos[posicao % t->tamanho].status.numeroVotos;
        }

        i++;
        posicao += incremento;
    }

    return 0;
}



/*Adiciona +1 voto ao candidato indicado por seu <numero>. Se ele ainda não existir na tabela, será inserido.
Retorna o número de votos deste candidato ou 0 caso não seja possível computar o voto.*/
int computa_candidato(HashCandidatos t, int numero)
{

    if (!t)
        return 0;

    int posicao = hash_a(numero, t->tamanho), i = 0, incremento;

    incremento = hash_b(numero, t->tamanho);

    while (i < t->tamanho)
    {

        //Se achar...
        if (t->elementos[posicao % t->tamanho].status.vazio == 0 &&
            numero == t->elementos[posicao % t->tamanho].numeroCandidato)
        {

            //Computa mais um voto
            t->elementos[posicao % t->tamanho].status.numeroVotos += 1;
            return  t->elementos[posicao % t->tamanho].status.numeroVotos;
        }

        i++;
        posicao += incremento;
    }

    //Se não achar, insere um novo
    TCandidato c;
    c.numeroCandidato = numero;
    c.status.numeroVotos = 1;
    c.status.vazio = false;
    
    if(!insere_candidato(t, c)) return 0;

    return 1;
}

int altera_candidato(HashCandidatos t, TCandidato c)
{

    if (!t || t->numElementos == 0)
        return 0;

    int posicao = hash_a(c.numeroCandidato, t->tamanho);
    int i = 0, incremento;

    incremento = hash_b(c.numeroCandidato, t->tamanho);

    while (i < t->tamanho)
    {

        if (t->elementos[posicao % t->tamanho].status.vazio == 0 &&
            c.numeroCandidato == t->elementos[posicao % t->tamanho].numeroCandidato)
        {

            t->elementos[posicao % t->tamanho] = c;

            return 1;
        }

        i++;
        posicao += incremento;
    }

    return 0;
}

int remove_candidato(HashCandidatos t, int ch)
{
    int posicao;
    TCandidato e;
    posicao = pesquisa_candidato(t, ch, &e);
    if (posicao != -1)
    {
        t->elementos[posicao].status.vazio = 1;
        t->numElementos--;
        return 1;
    }
    else
        return 0;
}

void termina_hash_candidatos(HashCandidatos t)
{
    free(t->elementos);
    free(t);
}

void print_candidatos(HashCandidatos t)
{
    for (int i = 0; i < t->tamanho; i++)
    {
        printf("\n%d: ", i);
        if (!t->elementos[i].status.vazio)
            printf("%d ", t->elementos[i].numeroCandidato);
    }
}
