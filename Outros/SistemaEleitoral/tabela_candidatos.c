#include "tabela_candidatos.h"
#include "abp.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Função Hash A: Gera um valor hash a partir de um int
unsigned int f_hash(int ch, unsigned int m)
{

	
	return ch % m;
}

//Funcão Hash B: Gera uma valor hash de incremento a partir de um int
unsigned int f_hash_inc(int ch, int p,  unsigned int m)
{
	return (m - (p * ch % m)) + 1;
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
				t->elementos[i].status.vazio = true;
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
	int posicao = f_hash(e.numeroCandidato, t->tamanho), incremento;
	TCandidato eAux;

	if (t->numElementos == t->tamanho)
		return 0;

	if (pesquisa_candidato(t, e.numeroCandidato, &eAux) != -1)
		return 0;

	while (1)
	{
		
		incremento = f_hash_inc(e.numeroCandidato, posicao, t->tamanho);

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

	int posicao = f_hash(num, t->tamanho), i = 0, incremento;


	while (i < t->tamanho)
	{
		incremento = f_hash_inc(num, posicao, t->tamanho);

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

/*Adiciona -1 voto ao candidato indicado por seu <numero>. Se ele ainda não existir na tabela, retorna-se 0.*/
int decrementa_candidato(HashCandidatos t, int numero)
{

	if (!t)
		return 0;

	int posicao = f_hash(numero, t->tamanho), i = 0, incremento;

	while (i < t->tamanho)
	{

		incremento = f_hash_inc(numero, posicao, t->tamanho);

		//Se achar...
		if (t->elementos[posicao % t->tamanho].status.vazio == 0 &&
				numero == t->elementos[posicao % t->tamanho].numeroCandidato)
		{

			//Computa menos um voto
			t->elementos[posicao % t->tamanho].status.numeroVotos -= 1;
			return 1;
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

	int posicao = f_hash(numero, t->tamanho), i = 0, incremento;

	while (i < t->tamanho)
	{

		incremento = f_hash_inc(numero, posicao, t->tamanho);

		//Se achar...
		if (t->elementos[posicao % t->tamanho].status.vazio == 0 &&
				numero == t->elementos[posicao % t->tamanho].numeroCandidato)
		{

			//Computa mais um voto
			t->elementos[posicao % t->tamanho].status.numeroVotos += 1;
			return t->elementos[posicao % t->tamanho].status.numeroVotos;
		}

		i++;
		posicao += incremento;
	}

	//Se não achar, insere um novo
	TCandidato c;
	c.numeroCandidato = numero;
	c.status.numeroVotos = 1;
	c.status.vazio = false;

	if (!insere_candidato(t, c))
		return 0;

	return 1;
}

int altera_candidato(HashCandidatos t, TCandidato c)
{

	if (!t || t->numElementos == 0)
		return 0;

	int posicao = f_hash(c.numeroCandidato, t->tamanho);
	int i = 0, incremento;

	while (i < t->tamanho)
	{

		incremento = f_hash_inc(c.numeroCandidato, posicao, t->tamanho);

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
	if(t == NULL) return;

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

int comparador_ranking(const void * v1, const void *v2){
    
	const TCandidato * e1 = (TCandidato*) v1;
	const TCandidato * e2 = (TCandidato*) v2;
	
	if(e1->status.numeroVotos > e2->status.numeroVotos)
        return -1;
    if(e1->status.numeroVotos < e2->status.numeroVotos)
        return 1;

    return e1->numeroCandidato - e2->numeroCandidato;
}

Ranking obter_ranking(HashCandidatos t, int tamanhoRanking)
{
	TCandidato * ranking = (TCandidato*) malloc(sizeof(TCandidato) * tamanhoRanking);
   
    int count = 0;
    for(int i = 0; count<tamanhoRanking && i<t->tamanho; i++)
        if(t->elementos[i].status.vazio == false) 
            ranking[count++] = t->elementos[i];
    

    qsort(ranking, count, sizeof(TCandidato), comparador_ranking);

    Ranking r = (Ranking) malloc(sizeof(t_hash_candidatos));

    r->elementos = ranking;
    r->numElementos = count;
    r->tamanho = tamanhoRanking;

    return r;

}

void print_ranking_str(HashCandidatos t, int tamanhoRanking)
{
	TCandidato ranking[tamanhoRanking];
   
    int count = 0;
    for(int i = 0; count<tamanhoRanking && i<t->tamanho; i++)
        if(t->elementos[i].status.vazio == false) 
            ranking[count++] = t->elementos[i];
    

    qsort(ranking, count, sizeof(TCandidato), comparador_ranking);

	for(int i = 0; i < count; i++)
		printf("\n%d %d votos", ranking[i].numeroCandidato, ranking[i].status.numeroVotos);
   

}


void termina_ranking(Ranking r){
    termina_hash_candidatos(r);
}
