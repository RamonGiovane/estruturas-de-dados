#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED
#include <stdbool.h>
#include <time.h>



int quebrarString(char *s, const char *delimitador, char *resultado[], int size_resultado);

//Prints no console
bool invalido(const char *dado);

//Prints no arquivo de saida
void fprint_votos(int candidato, int votos);

//Printa uma linha com um char* no arquivo
void fprint(const char*);

//Printa uma linha com um inteiro no arquivo
void fiprint(int);

clock_t cronometrar(clock_t start);

bool abrir_arquivo_leitura(const char * caminho);
bool ler_linha_arquivo(char * conteudoLido, int tamanhoLinha);
bool fechar_arquivo_leitura();

bool abrir_arquivo_escrita(const char * caminho);
bool fechar_arquivo_escrita();

#endif
