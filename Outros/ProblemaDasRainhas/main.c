#include <stdio.h>
#include <stdlib.h>
#define TAB 4


static int rainhas[TAB][2];  

//Estrutura que guarda posicoes já percorridas.
//A primeira dimensao guarda o numero de rainhas
//A segunda dimensao guarda as posicoes do xadrex
//A terceira é necessaria porque as posicoes sao compostas de dois numeros                             
static int jaPercorrido[TAB][TAB * TAB][2];

//Guarda o numero de posicoes ja percorridas por cada  rainha
static int tamanhoJP[TAB];


static int indice;

static int solucoes = 0;


int proxima_pos_livre(int id, int* l, int* c) {

    //Status
    int st = 0; //POSSIVELMENTE STACKOVERFLOW

    if (*l == TAB || *c == TAB) return 0;

 
    if (id != 0) {

        // Verifica se pode ser pega por uma das outras rainhas
        for (int i = 0; i < id; i++) {
            
            //Verifica se está na lista de posicoes ja percorridas
            if(i < tamanhoJP[id]){
                if(jaPercorrido[id][i][0] == *l && jaPercorrido[id][i][1] == *c){
                    if(*c < TAB-1)
                        *c += 1;
                    else{
                        *c = 0;
                        *l += 1;
                    }
                    st = 1;
                }
            }
                
            //Verifca se bate a linha
            else if (rainhas[i][0] == *l) {
                *l += 1;
                *c = 0;
                st = 1;
            }

            //Verifica se bate a coluna
            else if (rainhas[i][1] == *c) {
                *c += 1;
                st = 1;
            }

            //Verifica se bate as diagonais
            else if (rainhas[i][0] + rainhas[i][1] == *l + *c ||
                rainhas[i][0] - rainhas[i][1] == *l - *c) {
                if (*c == TAB-1) {
                    *l += 1;
                    *c = 0;
                    st = 1;
                }

                else {
                    *c += 1;
                    st = 1;
                }
            }

            //Se algum valor nao bateu, refaz os testes, com as novas posições passadas.
            if (st == 1) return proxima_pos_livre(id, l, c);
        }
    }

    return 1;
}

int insere(int id, int lin, int col) {
    
    int *l = &lin, *c = &col;

    int status = 0;

    if(id < 0) return 0;

    if(id == TAB) return 1;

    if(proxima_pos_livre(id, l, c) == 1){
        rainhas[id][0] = *l;
        rainhas[id][1] = *c;

        status = insere(id+1, 0, 0);

        //Armazena n/ esta posição no vetor de percorridos por esta rainha
        jaPercorrido[id][tamanhoJP[id]][0] = *l;
        jaPercorrido[id][tamanhoJP[id]][0] = *c;

        tamanhoJP[id] += 1;

        if(status == 1){
            solucoes++;
            return 0;
        }

    }
    
    return insere(id, 0, 0);

}

int main(int argc, char* argv[]) {
  
    int l = atoi(argv[1]);
    int c = atoi(argv[2]);

    printf("%d ", insere(0, l, c));

    printf("Hello world! %d\n");
    return 0;
}
