#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED
#include <stdbool.h>
#include <time.h>
#include "tabela_candidatos.h"

int lerInteiro(const char *txt);
void lerString(const char *txt, char *retorno, int tamanho);
void quebrarString(char *s, const char *delimitador, char *resultado[], int size_resultado);
bool invalido(const char *dado);
bool votoValido(int candidato, int votosCandidato);
bool votoInvalido(void);
bool remocao_valida(int votosValidos);
bool remocao_invalida(int votosValidos);
void print_ranking(Ranking);
void print_exec(int, long);
clock_t cronometrar(clock_t start);
FILE* abrir_arquivo_leitura(const char * caminho);
bool ler_linha(FILE *f, char * conteudoLido, int tamanhoLinha);
bool checar_numero_primo(int numero);
int fechar_arquivo(FILE* f);
#endif
