#include "tabela_candidatos.h"
#include "abp.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define PRIME 7

//Função Hash A: Gera um valor hash a partir de um int
unsigned int f_hash(int ch, unsigned int m)
{

	return ch % m;
}

//Funcão Hash B: Gera uma valor hash de incremento a partir de um int
unsigned int f_hash_inc(int ch, int p, unsigned int m)
{
	return (m - (p * ch % m));
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

// function to calculate first hash
int Chash1(int key, int tamanho_tabela)
{
	return abs(key % tamanho_tabela);
}

int Chash2(int key)
{
	return (PRIME - (key % PRIME));
}

// function to insert key into hash table
int insert(HashCandidatos t, int key, int incrementoVoto)
{

	// // if hash table is full
	// if (t->numElementos == t->tamanho)
	// 	return 0;

	int hash = Chash1(key, t->tamanho);
	int inc = Chash2(key);
	int index = hash;
	int comps = 0;

	while (t->elementos[index].status.vazio == false) {
		
		//Se ja existe
		if (t->elementos[index].numeroCandidato == key){
			
			t->elementos[index].status.numeroVotos += incrementoVoto;			
			return t->elementos[index].status.numeroVotos;
		}

		index = (index + inc) % t->tamanho;

		//if(index == hash) return 0;
		if(comps++ == t->tamanho) return 0;
	}

	if(incrementoVoto == 1){
		TCandidato c;
		c.numeroCandidato = key;
		c.status.numeroVotos = 1;
		c.status.vazio = false;
		
		t->elementos[index] = c;
		
		t->numElementos++;
	}

	return 1;
}

// function to search key in hash table
int search(HashCandidatos t, int key, TCandidato *c)
{
	int size = t->tamanho;
	int hash = Chash1(key, size);
	int inc = Chash2(key);

	int index = hash;

	if (t->numElementos == 0)
		return -1;

	while (!t->elementos[index].status.vazio)
	{

		if (t->elementos[index].numeroCandidato == c->numeroCandidato)
		{
			*c = t->elementos[index];
			return index;
		}

		index = (index + inc) % size;

		if (index == hash)
			break;
	}

	return -1;
}

int insere_candidato(HashCandidatos t, TCandidato c)
{
	return insert(t, c.numeroCandidato, 0);
}

/*retorna a posição da tabela caso encontre ou -1 em caso
contrário*/
int pesquisa_candidato(HashCandidatos t, int num, TCandidato *c)
{
	return search(t, num, c);
}

/*Adiciona -1 voto ao candidato indicado por seu <numero>. Se ele ainda não existir na tabela, retorna-se 0.*/
int decrementa_candidato(HashCandidatos t, int numero)
{
	
	return insert(t, numero, -1);
	
}

/*Adiciona +1 voto ao candidato indicado por seu <numero>. Se ele ainda não existir na tabela, será inserido.
Retorna o número de votos deste candidato ou 0 caso não seja possível computar o voto.*/
int computa_candidato(HashCandidatos t, int numero)
{
	return insert(t, numero, 1);
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
	if (t == NULL)
		return;

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

int comparador_ranking(const void *v1, const void *v2)
{

	const TCandidato *e1 = (TCandidato *)v1;
	const TCandidato *e2 = (TCandidato *)v2;

	if (e1->status.numeroVotos > e2->status.numeroVotos)
		return -1;
	if (e1->status.numeroVotos < e2->status.numeroVotos)
		return 1;

	return e1->numeroCandidato - e2->numeroCandidato;
}

Ranking obter_ranking(HashCandidatos t, int tamanhoRanking)
{
	TCandidato *ranking = (TCandidato *)malloc(sizeof(TCandidato) * tamanhoRanking);

	int count = 0;
	for (int i = 0; count < tamanhoRanking && i < t->tamanho; i++)
		if (t->elementos[i].status.vazio == false)
			ranking[count++] = t->elementos[i];

	qsort(ranking, count, sizeof(TCandidato), comparador_ranking);

	Ranking r = (Ranking)malloc(sizeof(t_hash_candidatos));

	r->elementos = ranking;
	r->numElementos = count;
	r->tamanho = tamanhoRanking;

	return r;
}

void print_ranking_str(HashCandidatos t, int tamanhoRanking)
{
	TCandidato ranking[t->numElementos];

	int count = 0;
	for (int i = 0; count < t->numElementos && i < t->tamanho; i++)
		if (t->elementos[i].status.vazio == false){

			ranking[count++] = t->elementos[i];
		}

	qsort(ranking, count, sizeof(TCandidato), comparador_ranking);

	if (tamanhoRanking > count)
		tamanhoRanking = count;

	for (int i = 0; i < tamanhoRanking; i++)
		fprint_votos(ranking[i].numeroCandidato, ranking[i].status.numeroVotos);

}

void termina_ranking(Ranking r)
{
	termina_hash_candidatos(r);
}
