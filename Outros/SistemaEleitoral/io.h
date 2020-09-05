#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED
#include <stdbool.h>
#include <time.h>
#include "tabela_candidatos.h"

int lerInteiro(const char *txt);
void lerString(const char *txt, char *retorno, int tamanho);
void quebrarString(char *s, const char *delimitador, char *resultado[], int size_resultado);

//Prints no console
bool invalido(const char *dado);
bool votoValido(int candidato, int votosCandidato);
bool votoInvalido(void);
bool remocao_valida(int votosValidos);
bool remocao_invalida(int votosValidos);
void print_exec(int, long);

//Prints no arquivo de saida
void fprint_votos(int candidato, int votos);
void fprint(const char*);
bool fvotoValido(int candidato, int votosCandidato);
bool fvotoInvalido(void);
bool fremocao_valida(int votosValidos);
bool fremocao_invalida(int votosValidos);
void fprint_exec(int, long);

clock_t cronometrar(clock_t start);

bool checar_numero_primo(int numero);

bool abrir_arquivo_leitura(const char * caminho);
bool ler_linha_arquivo(char * conteudoLido, int tamanhoLinha);
bool fechar_arquivo_leitura();

bool abrir_arquivo_escrita(const char * caminho);
bool fechar_arquivo_escrita();

#endif
