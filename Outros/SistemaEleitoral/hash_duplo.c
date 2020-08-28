#include <stdio.h>
#include <stdlib.h>
#include "cedula.h"
#include "hash_duplo.h"
#include <string.h>

HashDuplo cria_hash_duplo(unsigned int n){
   HashDuplo t = (HashDuplo)malloc(sizeof(t_hash_duplo));
   unsigned int i;
   if(t!=NULL){
     t->elementos = (TElemento*)malloc(sizeof(TElemento)*n);
     if(t->elementos!=NULL){
      for(i=0;i<n;i++)
        t->elementos[i].vazio = 1;
      t->tamanho =n;
      t->numElementos =0;
     }
     else{
       free(t);
     }

   }
   return t;
}



int insere_hash_duplo(HashDuplo t,TElemento e){
  int posicao = tch_hash_a(e.id, t->tamanho),incremento;
  TElemento eAux;

  if(t->numElementos==t->tamanho)
    return 0;

  if(pesquisa_hash_duplo(t, e.id, &eAux)!=-1)
    return 0;

  incremento = tch_hash_b(e.id, t->tamanho);
  while(1){
    
    if(t->elementos[posicao%t->tamanho].vazio == 0){      
      posicao += incremento;
    }
    
    else{
      t->elementos[posicao%t->tamanho] = e;
      t->numElementos++;
      return 1;
    }

  }

}

/*retorna a posição da tabela caso encontre ou -1 em caso
contrário*/
int pesquisa_hash_duplo(HashDuplo t,TChave ch,TElemento*e){
  int posicao = tch_hash_a(ch,t->tamanho),i=0,incremento;

  if(t->numElementos ==0)
    return -1;

  incremento = tch_hash_b(ch,t->tamanho);

  while(i<t->tamanho){
    if(t->elementos[posicao%t->tamanho].vazio == 0 &&
       tchcmp(ch,t->elementos[posicao%t->tamanho].id) == 0){
       *e = t->elementos[posicao%t->tamanho];
       return posicao%t->tamanho;
    }
    i++;
    posicao+=incremento;
  }

  return -1;
}


int remove_hash_duplo(HashDuplo t ,TChave ch){
  int posicao ;
  TElemento e;
  posicao = pesquisa_hash_duplo(t,ch, &e);
  if(posicao !=-1){
    t->elementos[posicao].vazio = 1;
    t->numElementos--;
    return 1;
  }
  else
    return 0;
}

void termina_hash_duplo(HashDuplo t){
  free(t->elementos);
  free(t);
}

void print_hash_duplo(HashDuplo t){
  for (int i = 0; i < t->tamanho; i++)
  {
    printf("\n%d: ", i);
    if(!t->elementos[i].vazio)
      print_tch(t->elementos[i].id);
  }
  
}
