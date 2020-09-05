#include "tabela_candidatos.h"
#include "abp.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define PRIME 101

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

int f_hash1(int key, int tamanho_tabela)
{
	return abs(key % tamanho_tabela);
}

int f_hash2(int key)
{
	return (PRIME - (key % PRIME));
}

// function to insert key into hash table
int insert(HashCandidatos t, int key, int incrementoVoto)
{

	int hash = f_hash1(key, t->tamanho);
	int inc = f_hash2(key);
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
	int hash = f_hash1(key, size);
	int inc = f_hash2(key);

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

