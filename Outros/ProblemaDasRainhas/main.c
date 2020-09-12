#include <stdio.h>
#include <stdlib.h>
// Numero do tabuleiro
#define TAB 6
// Numero de rainha
#define R 6

static int rainhas[TAB][2];

// Estrutura que guarda posicoes já percorridas.
// A primeira dimensao guarda o numero de rainhas
// A segunda dimensao guarda as posicoes do xadrex
// A terceira é necessaria porque as posicoes sao compostas de dois numeros
static int jaPercorrido[TAB][TAB * TAB][2];

// Guarda o numero de posicoes ja percorridas por cada  rainha
static int tamanhoJP[TAB];

static int solucoes = 0;

void printSolucao() {
    printf("\n\n");
    for (int i = 0; i < R; i++) {
       printf("%d: [%d, %d]\n", i+1, rainhas[i][0], rainhas[i][1]);
    }
}

int ja_foi_tentado(int id, int l, int c) {
    // Verifica se está na lista de posicoes ja percorridas
    for (int i = 0; i < tamanhoJP[id]; i++) {
        if (l == TAB) return 0;

        // Se passou por uma posicao ja percorrida
        if (jaPercorrido[id][i][0] == l && jaPercorrido[id][i][1] == c) {
            return 1;
        }
    }

    return 0;
}

int aumenta_linha(int *l, int *c) {
    *c = 0;
    *l += 1;
    return 1;
}
int aumenta_coluna(int *l, int *c) {
    if (*c == TAB - 1) {
        aumenta_linha(l, c);
    } else
        *c += 1;

    return 1;
}

int proxima_pos_livre(int id, int *lin, int *col) {
    int l = *lin, c = *col;
    int status = 0;
    // Se é a primeira rainha, pula os testes
    if (id == 0) return 1;

    // Verificando se pode ser pega por uma das outras rainhas
    for (int i = 0; i < id;) {
        if (l == TAB) return 0;

        // Verifca se bate a LINHA com outra rainha
        if (rainhas[i][0] == l) {
            status = aumenta_linha(&l, &c);
        }

        // Verifica se bate a COLUNA com outra rainha
        else if (rainhas[i][1] == c) {
            status = aumenta_coluna(&l, &c);
        }

        // Verifica se bate as DIAGONAIS com outra rainha
        else if (rainhas[i][0] + rainhas[i][1] == l + c ||
                 rainhas[i][0] - rainhas[i][1] == l - c) {
            status = aumenta_coluna(&l, &c);
        }

        // Verifica se já foi percorrido antes por uma rainha do mesmo id
        else if (ja_foi_tentado(id, l, c)) {
            status = aumenta_coluna(&l, &c);
        }

        if (status == 1) {
            status = 0;
            i = 0;  // Reseta o loop. Deve tentar de novo, com a nova posição
                    // gerada
        }
        else i++;
    }

    *lin = l;
    *col = c;

    return 1;
}

int insere(int id, int lin, int col) {
    int *l = &lin, *c = &col;

    int status = 0;

    // Para se todas as rainhas foram inseridas...
    if (id == R) return 1;

    // Procura uma posição livre
    if (proxima_pos_livre(id, l, c) == 1) {
        // Se achar, guarda a posicao dessa rainha
        rainhas[id][0] = *l;
        rainhas[id][1] = *c;

        // Tenta inserir a proxima
        status = insere(id + 1, 0, 0);

        // Armazena esta posição no vetor de posições percorridas por esta
        // rainha
        jaPercorrido[id][tamanhoJP[id]][0] = *l;
        jaPercorrido[id][tamanhoJP[id]][1] = *c;
        tamanhoJP[id] += 1;

        // Se foi possível inserir a ultima rainha
        if (status == 1) {
            solucoes++;
            printf("Solucoes: %d\n", solucoes);
            printSolucao();
            return 0;  // retorna 0 para que as outras chamadas nao entrarem
                       // aqui
        }

     //   if (id == 0) return 0;

        /*Tenta de novo em uma outra posição, passa-se qualquer coordenada pois
         a
         funcao proxima_pos_livre() será responsável por encontrar um possível
         espaço*/
        return insere(id + 1, 0, 0);
    }


    // Se não tem posição livre retorna 0
    return 0;
}

int main(int argc, char *argv[]) {
    int l = atoi(argv[1]);
    int c = atoi(argv[2]);

    // Insere a primeira rainha (id == 0)
    printf("%d ", insere(0, l, c));

    printf("Hello world!");
    return 0;
}
