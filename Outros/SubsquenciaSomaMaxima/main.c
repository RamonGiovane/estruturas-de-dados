#include <stdio.h>
#include <stdlib.h>
#define MINIMO -99999999

//Tipo que armazena a soma de um subarray
typedef struct sequencia {
    int max_indice, min_indice, soma;
} Sequencia;

//Pseudo construtor :D
Sequencia sequencia(int min, int max, int sum) {
    Sequencia s;
    s.max_indice = max;
    s.min_indice = min;
    s.soma = sum;

    return s;
}

//Soma máxima do subarray cruzando o ponto médio
Sequencia sub_cruzada_maxima(int v[], int inicio, int meio, int fim) {
    int soma_esq = MINIMO, soma_dir = MINIMO;
    int soma, max_esq = 0, max_dir = 0;

	soma = 0;
    for (int i = meio; i > inicio; i--) {
        soma = soma + v[i];
        if (soma > soma_esq) {
            soma_esq = soma;
            max_esq = i;
        }
    }

	soma = 0;
    for (int i = meio + 1; i < fim; i++) {
        soma = soma + v[i];
        if (soma > soma_dir) {
            soma_dir = soma;
            max_dir = i;
        }
    }

    return sequencia(max_esq, max_dir, soma_dir + soma_esq);
}

//Encontra soma máxima contígua de um subarray num array
Sequencia sub_soma_maxima(int v[], int inicio, int fim) {
    Sequencia dir, esq, centro;

    if (inicio == fim) return sequencia(inicio, fim, v[inicio]);

    int meio = (inicio + fim) / 2;

    esq = sub_soma_maxima(v, inicio, meio);
    dir = sub_soma_maxima(v, meio + 1, fim);
    centro = sub_cruzada_maxima(v, inicio, meio, fim);

    if (esq.soma >= dir.soma && esq.soma >= centro.soma) return esq;
    if (dir.soma >= esq.soma && dir.soma >= centro.soma) return dir;

    return centro;
}

//Testando
int main() {
    int arr[] = {-2, -5, 6, -2, -3, 1, 5, -6};
    int n = 8;
    Sequencia resultado = sub_soma_maxima(arr, 0, n - 1);

    printf("A soma maxima contigua e: %d\nIndo da posicao %d ate a posicao %d.\n\n", resultado.soma, 
        resultado.min_indice, resultado.max_indice);

    return 0;
}