#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "io.h"

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

        printf("TOKEN: %s\n", token);

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
