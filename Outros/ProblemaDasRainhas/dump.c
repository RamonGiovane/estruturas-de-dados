// typedef int** Tabuleiro;
// void printMatriz(int** m) {
//     for (int i = 0; i < TAB; i++) {
//         printf("\n");
//         for (int x = 0; x < TAB; x++) printf(" %d ", m[i][x]);
//     }

//     printf("\n\n");
// }
// int inserir_rainha(int id, int lin, int col) {
//     if (lin == 8 || col == 8) {
//         indice--;
//         return solucoes;
//     }

//     if (id != 0) {
//         // Verifica se pode ser pega por uma das outras rainhas
//         for (int i = 0; i < id; i++) {
//             if (rainhas[i][0] == lin) return inserir_rainha(id, lin + 1, 0);

//             if (rainhas[i][1] == col) return inserir_rainha(id, lin, col + 1);

//             if (rainhas[i][0] + rainhas[i][1] == lin + col ||
//                 rainhas[i][0] - rainhas[i][1] == lin - col) {
//                 if (col == 7)
//                     return inserir_rainha(id, lin + 1, 0);

//                 else
//                     return inserir_rainha(id, lin, col + 1);
//             }
//         }
//     }

//     rainhas[id][0] = lin;
//     rainhas[id][1] = col;

//     if (++id == 8) {
//         solucoes++;
//         return solucoes;
//     }

//     indice++;
//     return inserir_rainha(id, 0, 0);
// }
// #pragma region
// Tabuleiro cria_tabuleiro() {
//     int** ptr = (int**)malloc(sizeof(int*) * 8);
//     if (ptr) {
//         for (int i = 0; i < 8; i++) ptr[i] = (int*)malloc(sizeof(int) * 8);

//         for (int l = 0; l < 8; l++)
//             for (int c = 0; c < 8; c++) ptr[l][c] = 0;
//     }

//     return ptr;
// }
// // int demarcar_posicoes(Tabuleiro t, int id, int l, int c) {

// //     // Demarcando linhas e colunas
// //     for (int i = 0; i < 8; i++) {
// //         insere_abp(rainhas[id], elemento(l, i, id));
// //         insere_abp(rainhas[id], elemento(i, c, id));
// //         // t[l][i] = id;
// //         // t[i][c] = id;
// //     }

// //     // Demarcando diagonal superior esquerda
// //     int lin = l;
// //     int col = c;

// //     while (lin < 8 && lin >= 0 && col < 8 && col >= 0) {
// //         //t[lin--][col--] = id;
// //         insere_abp(rainhas[id], elemento(lin--, col--, id));

// //     }

// //     //Demarcando diagonal superior direita
// //     lin = l;
// //     col = c;
// //     while (lin < 8 && lin >= 0 && col < 8 && col >= 0) {

// //         //t[lin--][col++] = id;
// //         insere_abp(rainhas[id], elemento(lin--, col++, id));

// //     }

// //     //Demarcando diagonal inferior esquerda
// //     lin = l;
// //     col = c;
// //     while (lin < 8 && lin >= 0 && col < 8 && col >= 0) {

// //         //t[lin++][col--] = id;
// //         insere_abp(rainhas[id], elemento(lin++, col--, id));
// //     }

// //     //Demarcando diagonal inferior direita
// //     lin = l;
// //     col = c;
// //     while (lin < 8 && lin >= 0 && col < 8 && col >= 0) {
// //         //t[lin++][col++] = id;
// //         insere_abp(rainhas[id], elemento(lin++, col++, id));
// //     }

// //     return 1;
// // }
// #pragma endregion
