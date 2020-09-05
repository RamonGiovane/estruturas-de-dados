#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "io.h"
#include "tabela_candidatos.h"

static FILE* _def_output_file = NULL;
static FILE* _def_input_file = NULL;

int linhasLidas = 0;

int lerInteiro(const char *txt)
{
    printf("%s", txt);
    int r;
    scanf("%d", &r);
    return r;
}

void lerString(const char *txt, char *retorno, int tamanho)
{
    printf("%s", txt);
    setbuf(stdin, NULL);
    fgets(retorno, tamanho, stdin);
    setbuf(stdin, NULL);

    for (int i = 0; i < tamanho; i++)
    {

        if (retorno[i] == '\0')
            break;

        if (retorno[i] == '\n')
        {
            retorno[i] = '\0';
            break;
        }
    }
}

void quebrarString(char *s, const char *delimitador, char *resultado[], int size_resultado)
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
}

bool invalido(const char *dado)
{
    printf("\nErro ao processar: %s.\n", dado);
    return false;
}

bool votoValido(int candidato, int votosCandidato){
    printf("\nvoto computado, candidato %d tem %d voto(s)\n", candidato, votosCandidato);
    return true;
}
bool votoInvalido()
{
    printf("\nvoto não computado.\n");
    return false;
}

bool remocao_valida(int votosValidos)
{
    printf("\nmeliante removido, %d voto(s) válido(s) no sistema.\n", votosValidos);
    return true;
}

bool remocao_invalida(int votosValidos)
{
    printf("\nmeliante não removido, %d voto(s) válido(s) no sistema.\n", votosValidos);
    return false;
}


void print_exec(int colisoes, long tempo){
    printf("\n\n=============\n");
    printf("Número de Colisões: %d", colisoes);
    printf("\nTempo de Execução: %lu ms\n\n", tempo);
}

bool abrir_arquivo_leitura(const char * caminho){

    if(_def_input_file) return true;

    _def_input_file = fopen(caminho, "r");
    return _def_input_file != NULL;
}

bool ler_linha_arquivo(char * conteudoLido, int tamanhoLinha){

    bool status = fgets(conteudoLido, tamanhoLinha, _def_input_file) != NULL;
    if(status) linhasLidas++;
    return status;
}

bool fechar_arquivo_leitura(){
   
    if(_def_input_file == NULL) return false;
  
    bool status = fclose(_def_input_file) != 0;
    _def_input_file = NULL;
    return status;
}

bool checar_numero_primo(int numero){

    for (int i = 2; i <= numero / 2; i++) {

        // condition for non-prime
        if (numero % i == 0) {
            return false;
        }
    }

    return true;
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



bool fvotoValido(int candidato, int votosCandidato){

    fprintf(_def_output_file, "voto computado, candidato %d tem %d voto(s)\n", candidato, votosCandidato);
    return true;
}
bool fvotoInvalido()
{
    fprintf(_def_output_file, "voto não computado.\n");
    return false;
}

bool fremocao_valida(int votosValidos)
{
    fprintf(_def_output_file, "meliante removido, %d voto(s) válido(s) no sistema.\n", votosValidos);
    return true;
}

bool fremocao_invalida(int votosValidos)
{
    fprintf(_def_output_file, "meliante não removido, %d voto(s) válido(s) no sistema.\n", votosValidos);
    return false;
}

void fprint_votos(int candidato, int votos){
    fprintf(_def_output_file, "%d %d voto(s)\n", candidato, votos);
}

void fprint(const char * text){
    fprintf(_def_output_file,  "\n%s", text);
}


void fprint_exec(int colisoes, long tempo){
    fprintf(_def_output_file, "\nNúmero de Colisões: %d", colisoes);
    fprintf(_def_output_file, "\nTempo de Execução: %lu ms\n\n", tempo);
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
