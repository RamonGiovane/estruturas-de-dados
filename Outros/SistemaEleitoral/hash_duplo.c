#include <stdio.h>
#include <stdlib.h>
#include "cedula.h"
#include "hash_duplo.h"
#include "io.h"
#include <string.h>
#include <math.h>

#define PRIME 3

HashDuplo cria_hash_duplo(unsigned int n)
{
  HashDuplo t = (HashDuplo)malloc(sizeof(t_hash_duplo));
  unsigned int i;
  if (t != NULL) {
    t->elementos = (TElemento *)malloc(sizeof(TElemento) * n);
    if (t->elementos != NULL)
    {
      for (i = 0; i < n; i++)
        t->elementos[i].condicao = VAZIO;

      t->tamanho = n;
      t->numElementos = 0;
      t->numColisoes = 0;
    }
    
    else
      free(t);
    
  }
  
  t->np = n-1;
  while(!checar_numero_primo(t->np) && t->np-1 > 1) t->np--; 

  return t;
}

int hash1(int key, int tamanho_tabela)
{
  return abs(key % tamanho_tabela);
}

int hash2(int key, int np)
{
  return (PRIME - (key % PRIME));
}

unsigned int transforma_chave(TChave ch)
{
  unsigned int i, soma = 0;
  for (i = 0; ch.tituloEleitor[i] != '\0'; i++)
  {
    soma += ch.tituloEleitor[i] * (i + 1000);
  }
  
  return soma;
}

// function to insert key into hash table
int insere_hash_duplo(HashDuplo t, TElemento e)
{

  unsigned int key = transforma_chave(e.id);
  int hash = hash1(key, t->tamanho);
	int inc = hash2(key, t->np);
	int index = hash;

  if(t->numElementos == t->tamanho) return 0;

  //Percorre a tabela até achar um elemento com estado VAZIO ou DELETADO
	while (t->elementos[index].condicao == CHEIO) {
		
		//Se quem eu quero inserir ja existe, retorna 0
		if (tchcmp(t->elementos[index].id, e.id) == 0)
      return 0;
		

    t->numColisoes++;
		index = (index + inc) % t->tamanho;

	}
  
  e.condicao = CHEIO;
  t->elementos[index] = e;
  t->numElementos++;

  return 1;
}

// function to search key in hash table
int pesquisa_hash_duplo(HashDuplo t, TChave ch, TElemento *e)
{
  int size = t->tamanho;
  unsigned int key = transforma_chave(ch);
  int hash = hash1(key, size);
  int inc = hash2(key, t->np);

  int index = hash;
  int count = 0;

  if(!t || t->numElementos == 0) return -1;

  while (count < size) 
  {
    
     //Se já existe um elemento na posicao escolhida e não é quem procuro...
    if (tchcmp(t->elementos[index].id, ch) != 0){
      
      //Se estiver CHEIO ou REMOVIDO, procura-se pela proxima posicao
      if(t->elementos[index].condicao != VAZIO){ 
        index = (index + inc) % size;
        count++;
        
      }

      //Se for um elemento vazio, quer dizer que quem eu procuro sequer foi adicionado
      else return -1;
      
    }
    else{
      if(t->elementos[index].condicao == DELETADO){
        index = (index + inc) % size;
        count++;
      }
      else{
       *e = t->elementos[index];
        return index;
      }
      
      
    }
    
  }

  return -1;

}


int altera_hash_duplo(HashDuplo t, TElemento e)
{

 TElemento old;

  int pos = pesquisa_hash_duplo(t, e.id, &old);

  if(pos == -1) return 0;

  e.condicao = CHEIO;
  t->elementos[pos] = e;

  return 1;
}

int remove_hash_duplo(HashDuplo t, TChave ch, TElemento *e)
{
  int posicao = pesquisa_hash_duplo(t, ch, e);

  if (posicao != -1){
    t->elementos[posicao].condicao = DELETADO;
    t->numElementos--;
    return 1;
  }
  
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
    if (t->elementos[i].condicao == CHEIO)
      print_tch(t->elementos[i].id);
  }
}
