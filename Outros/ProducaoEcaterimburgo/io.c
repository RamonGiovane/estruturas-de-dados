#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "io.h"


static FILE* _def_output_file = NULL;
static FILE* _def_input_file = NULL;


//Retorna o número de pedaços em que a string foi quebrada
int quebrarString(char *s, const char *delimitador, char *resultado[], int size_resultado)
{

    char *token = strtok(s, delimitador);
    int i = 0;

    while (token != NULL && i < size_resultado)
    {
        resultado[i++] = token;

        token = strtok(NULL, delimitador);
    }

    if(i > 0) 
        for(int x = 0; resultado[i-1][x] != '\0'; x++)
            if(resultado[i-1][x] == '\n')
                resultado[i-1][x] = '\0';
    
    return i;
}

bool invalido(const char *dado)
{
    printf("\nErro ao processar: %s.\n", dado);
    return false;
}

bool abrir_arquivo_leitura(const char * caminho){

    if(_def_input_file) return true;

    _def_input_file = fopen(caminho, "r");
    return _def_input_file != NULL;
}

bool ler_linha_arquivo(char * conteudoLido, int tamanhoLinha){

    bool status = fgets(conteudoLido, tamanhoLinha, _def_input_file) != NULL;
    return status;
}

bool fechar_arquivo_leitura(){
   
    if(_def_input_file == NULL) return false;
  
    bool status = fclose(_def_input_file) != 0;
    _def_input_file = NULL;
    return status;
}

clock_t cronometrar(clock_t start){


    if(start == 0){
       return clock();
    }

    clock_t t2 = clock();
    clock_t elapsed;
    elapsed = ((double)t2 - start) / CLOCKS_PER_SEC * 1000;

    return elapsed;

}

void fiprint(int numero){
    char text[30];
    sprintf(text, "%d", numero);
    fprintf(_def_output_file,  "%s\n", text);
}

void fprint(const char * text){
    fprintf(_def_output_file,  "\n%s", text);
}

bool abrir_arquivo_escrita(const char * caminho){

    if(_def_output_file) return true;

    _def_output_file = fopen(caminho, "w+");
    return _def_output_file != NULL;
}

bool fechar_arquivo_escrita(){

    if(_def_output_file == NULL) return false;

    fclose(_def_output_file);
    _def_output_file = NULL;
    return true;
}
