#include <stdio.h>
#include <stdlib.h>
// Numero do tabuleiro
#define TAB 8
// Numero de rainha
#define R 8

static int rainhas[TAB][2];

static int solucoes = 0;

void printSolucao() {
    printf("\n\n");
    for (int i = 0; i < R; i++) {
        printf("%d: [%d, %d]\n", i + 1, rainhas[i][0], rainhas[i][1]);
    }
}

int inserir(int linha, int coluna) {
    if (linha == 8) {
        printf("\nSolucao encontrada! %d", ++solucoes);
        printSolucao();
        return 1;
    }

    if (coluna == 8) {
        return 0;
    }

    for (int l = 0; l < linha; l++) {
        if (coluna == rainhas[l][1] ||
            linha + coluna == rainhas[l][0] + rainhas[l][1] ||
            linha - coluna == rainhas[l][0] - rainhas[l][1]) {
            if (inserir(linha, coluna + 1) == 0)
                return 0;

            else
                break;
        }
    }

    rainhas[linha][0] = linha;
    rainhas[linha][1] = coluna;

    inserir(linha + 1, 0);

    return inserir(linha, coluna + 1);
}

int main(int argc, char *argv[]) {
    int l = atoi(argv[1]);
    int c = atoi(argv[2]);

    // Insere a primeira rainha (id == 0)
    inserir(0, 1);

    printf("\nNúmero de Soluções: %d", solucoes);
    printf("Hello world!");
    return 0;
}
