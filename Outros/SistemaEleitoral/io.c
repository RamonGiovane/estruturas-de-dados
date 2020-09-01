#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "io.h"
#include "tabela_candidatos.h"

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
    printf("\nmeliante removido, %d votos válidos no sistema.\n", votosValidos);
    return true;
}

bool remocao_invalida(int votosValidos)
{
    printf("\nmeliante não removido, %d votos válidos no sistema.\n", votosValidos);
    return false;
}

// void print_ranking(Ranking r){
    
//     printf("\n=== RANKING ===\n");
//     for(int i = 0; i<r->numElementos; i++)
//         printf("%d %d votos(s)\n", r->elementos[i].numeroCandidato, r->elementos[i].status.numeroVotos);
// }

void print_exec(int colisoes, long tempo){
    printf("\n\n=============\n");
    printf("Número de Colisões: %d", colisoes);
    printf("\nTempo de Execução %lu ms:\n\n", tempo);
}

FILE* abrir_arquivo_leitura(const char * caminho){
    return fopen(caminho, "r");
}

bool ler_linha(FILE *f, char * conteudoLido, int tamanhoLinha){

    return fgets(conteudoLido, tamanhoLinha, f) != NULL;
}

int fechar_arquivo(FILE* f){
    return fclose(f);
}

bool checar_numero_primo(int numero){
    
    for (int i = 2; i <= numero / 2; i++) {

        // condition for non-prime
        if (numero % i == 0) {
            return true;
        }
    }

    return false;
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