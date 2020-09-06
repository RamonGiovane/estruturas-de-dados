#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "abp.h"
#include "io.h"
#include "tabela_candidatos.h"

#define PRIME 7

HashCandidatos cria_hash_candidatos(unsigned int n) {
    HashCandidatos t = (HashCandidatos)malloc(sizeof(t_hash_candidatos));
    unsigned int i;
    if (t != NULL) {
        t->elementos = (TCandidato *)malloc(sizeof(TCandidato) * n);
        if (t->elementos != NULL) {
            for (i = 0; i < n; i++) t->elementos[i].condicao = VAZIO;

            t->tamanho = n;
            t->numElementos = 0;
        } else {
            free(t);
        }
    }

    t->np = n;
    while (!checar_numero_primo(t->np) && t->np - 1 > 1) t->np--;

    return t;
}

int f_hash1(int key, int tamanho_tabela) { return abs(key % tamanho_tabela); }

int f_hash2(int key) { return (PRIME - (key % PRIME)); }

// Insere ou atualiza um candidato na tabela. Se o elemento não existir insere
// um novo, com 1 voto. Caso exista, incrementa o numero de votos com o valor
// passado. Retorna o numero de votos do candidato. Em caso de falha retorna 0.
int insere_atualiza(HashCandidatos t, int key, int incrementoVoto) {
    int hash = f_hash1(key, t->tamanho);
    int inc = f_hash2(key);
    int index = hash;
    int comps = 0;

    while (t->elementos[index].condicao == CHEIO) {
        // Se ja existe
        if (t->elementos[index].numeroCandidato == key) {
            // Atualiza candidato
            t->elementos[index].numeroVotos += incrementoVoto;
            return t->elementos[index].numeroVotos;
        }

        t->numColisoes++;
        index = (index + inc) % t->tamanho;

        if (comps++ == t->tamanho) return 0;
    }

    if (incrementoVoto == 1) {
        TCandidato c;
        c.numeroCandidato = key;
        c.numeroVotos = 1;
        c.condicao = CHEIO;

        t->elementos[index] = c;

        t->numElementos++;
    }

    return t->elementos[index].numeroVotos;
}

// Procura por um elemento na tabela.
// Caso encontre, retorna a posicao do elemento, do contrário, -1.
int search(HashCandidatos t, int key, TCandidato *c) {
    int size = t->tamanho;
    int hash = f_hash1(key, size);
    int inc = f_hash2(key);
    int count = 0;
    int index = hash;

    if (!t || t->numElementos == 0) return -1;

    while (count < size) {
        if (t->elementos[index].numeroCandidato != key) {
            if (t->elementos[index].condicao != VAZIO) {
                index = (index + inc) % size;
                count++;
            }

            else
                return -1;
        }

        *c = t->elementos[index];
        return index;
    }

    return -1;
}

int insere_candidato(HashCandidatos t, TCandidato c) {
    return insere_atualiza(t, c.numeroCandidato, 0);
}

/*retorna a posição da tabela caso encontre ou -1 em caso
contrário*/
int pesquisa_candidato(HashCandidatos t, int num, TCandidato *c) {
    return search(t, num, c);
}

/*Adiciona -1 voto ao candidato indicado por seu <numero>. Se ele ainda não
 * existir na tabela, retorna-se 0.*/
int decrementa_candidato(HashCandidatos t, int numero) {
    return insere_atualiza(t, numero, -1);
}

/*Adiciona +1 voto ao candidato indicado por seu <numero>. Se ele ainda não
existir na tabela, será inserido.
Retorna o número de votos deste candidato ou 0 caso não seja possível computar o
voto.*/
int computa_candidato(HashCandidatos t, int numero) {
    return insere_atualiza(t, numero, 1);
}

int remove_candidato(HashCandidatos t, int ch) {
    int posicao;
    TCandidato e;
    posicao = pesquisa_candidato(t, ch, &e);
    if (posicao != -1) {
        t->elementos[posicao].condicao = DELETADO;
        t->numElementos--;
        return 1;
    } else
        return 0;
}

void termina_hash_candidatos(HashCandidatos t) {
    if (t == NULL) return;

    free(t->elementos);
    free(t);
}

void print_candidatos(HashCandidatos t) {
    for (int i = 0; i < t->tamanho; i++) {
        printf("\n%d: ", i);
        if (t->elementos[i].condicao == CHEIO)
            printf("%d ", t->elementos[i].numeroCandidato);
    }
}
