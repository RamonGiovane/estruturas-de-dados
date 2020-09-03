#include <stdio.h>
#include <stdlib.h>
#include "cedula.h"
#include "hash_duplo.h"
#include <string.h>
#include <math.h>

#define PRIME 11

HashDuplo cria_hash_duplo(unsigned int n)
{
  HashDuplo t = (HashDuplo)malloc(sizeof(t_hash_duplo));
  unsigned int i;
  if (t != NULL)
  {
    t->elementos = (TElemento *)malloc(sizeof(TElemento) * n);
    if (t->elementos != NULL)
    {
      for (i = 0; i < n; i++)
        t->elementos[i].status.vazio = 1;

      t->tamanho = n;
      t->numElementos = 0;
      t->numColisoes = 0;
    }
    else
    {
      free(t);
    }
  }
  return t;
}

// function to calculate first hash
int hash1(int key, int tamanho_tabela)
{
  return abs(key % tamanho_tabela);
}

int hash2(int key)
{
  return (PRIME - (key % PRIME));
}

int transforma_chave(TChave ch)
{
  int i, soma = 0;
  for (i = 0; ch.tituloEleitor[i] != '\0'; i++)
  {
    soma += ch.tituloEleitor[i] * (i + 1);
  }
  return abs(soma);
}

// function to insert key into hash table
int insere_hash_duplo(HashDuplo t, TElemento e)
{

  int key = transforma_chave(e.id);
  int hash = hash1(key, t->tamanho);
	int inc = hash2(key);
	int index = hash;
	int comps = 0;

  if(t->numElementos == t->tamanho) return 0;

	while (t->elementos[index].status.vazio == false) {
		
		//Se ja existe, retorna 0
		if (tchcmp(t->elementos[index].id, e.id) == 0){
			
      return 0;
		}

    t->numColisoes++;

		index = (index + inc) % t->tamanho;

		//if(index == hash) return 0;
		if(comps++ == t->tamanho) return 0;
	}

  t->elementos[index] = e;

  t->numElementos++;

  return 1;
}

// function to search key in hash table
int pesquisa_hash_duplo(HashDuplo t, TChave ch, TElemento *e)
{
  int size = t->tamanho;
  int key = transforma_chave(ch);
  int hash = hash1(key, size);
  int inc = hash2(key);

  int index = hash;
  int count = 0;

  if(t->numElementos == 0) return -1;

  while(true) 
  {
    if (tchcmp(t->elementos[index].id, ch) == 0){
      
      if(t->elementos[index].status.vazio == true) //Se esse elemento foi removido anteriormente
        return -1;
      
      *e = t->elementos[index];
      return index;
    }

    index = (index + inc) % size;
    count++;

    if(index == hash)
      break;
    
  }

  return -1;

}


int altera_hash_duplo(HashDuplo t, TElemento e)
{

  if (!t || t->numElementos == 0)
    return 0;

  int posicao = tch_hash(e.id, t->tamanho);
  int i = 0, incremento;

  while (i < t->tamanho)
  {

    incremento = tch_hash_inc(e.id, posicao, t->tamanho);

    if (t->elementos[posicao % t->tamanho].status.vazio == 0 &&
        tchcmp(e.id, t->elementos[posicao % t->tamanho].id) == 0)
    {

      t->elementos[posicao % t->tamanho] = e;

      return 1;
    }

    i++;
    posicao += incremento;
  }

  return 0;
}

int remove_hash_duplo(HashDuplo t, TChave ch, TElemento *e)
{
  int posicao;

  posicao = pesquisa_hash_duplo(t, ch, e);

  if (posicao != -1)
  {
    t->elementos[posicao].status.vazio = 1;
    t->numElementos--;
    return 1;
  }
  else
    return 0;
}

void termina_hash_duplo(HashDuplo t)
{
  if (t == NULL)
    return;

  free(t->elementos);
  free(t);
}

void print_hash_duplo(HashDuplo t)
{
  for (int i = 0; i < t->tamanho; i++)
  {
    printf("\n%d: ", i);
    if (!t->elementos[i].status.vazio)
      print_tch(t->elementos[i].id);
  }
}
