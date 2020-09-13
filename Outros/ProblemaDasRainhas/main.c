#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define N 8
int rainhas[N] = {-1, -1, -1, -1, -1, -1, -1, -1}, solucoes;

// Exibe o tabuleiro
void exibirSolucao() {
    printf("\n\nSolucao %d:\n\n", ++solucoes);

    for (int i = 1; i <= N; i++) printf("\t%d", i);

    for (int lin = 0; lin < N; lin++) {
        printf("\n\n%d", lin + 1);
        for (int col = 0; col < N; col++) {
            if (rainhas[lin] == col)
                printf("\tX");
            else
                printf("\t-");
        }
    }
}

// Verica a poiscao da rainha a ser inserida, com as ranhas ja colocadas
int verificar_posicao(int lin, int col) {
    for (int i = 0; i < N; i++) {
        if (rainhas[i] == -1) continue;

        // Verifica se bate coluna
        if (rainhas[i] == col) return 0;

        // Verifica se bate diagonais
        else if (abs(rainhas[i] - col) == abs(i - lin))
            return 0;
    }

    return 1;
}

// Insere a próxima rainha
void inserir(int lin, int linhaInicial) {
    if (lin == linhaInicial) {
        exibirSolucao();
        return;
    }

    for (int col = 0; col < N; col++) {
        if (verificar_posicao(lin, col)) {
            rainhas[lin] = col;

            // Tenta a proxima rainha. Realiza busca circular
            inserir((lin + 1) % N, linhaInicial);

            // Backtrack
            rainhas[lin] = -1;
        }
    }
}

void solucionar(int linha, int coluna) {
    // Posiciona a primeira rainha
    rainhas[linha] = coluna;

    return inserir((linha + 1) % N, linha);
}

int main(int argc, char* argv[]) {

    int l, c;

    if (argc == 3){
         l = atoi(argv[1]);
         c = atoi(argv[2]);
    }
    if(argc != 3 || l < 1 || l > 8 || c < 1 || c > 8) {
        printf("\nParametros invalidos.\n");
        printf("Voce deve fornecer a linha e a coluna iniciais, sendo valores de 1 a 8.");

    } else {
     
        solucionar(l - 1, c - 1);
        printf("\nNumero de Solucoes: %d", solucoes);
    }
    printf("\n\n");
    return 0;
}
