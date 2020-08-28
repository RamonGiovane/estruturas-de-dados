// int insere_aresta(Grafo g, TChave v1, TChave v2 , TPeso p){
   
//     int p1 = pesquisa_vertice(g, v1);
//     int p2 = pesquisa_vertice(g, v2);
   
//     if(p1 == -1 || p2 == -1)
//         return 0;
    
//     //Ligando os dois vertices, se eles existem
//     g->arestas[p1][p2].conectado = 1;
//     g->arestas[p2][p1].conectado = 1;

//     //Atribuindo os pesos dos vertices
//     g->arestas[p1][p2].peso = p;
//     g->arestas[p2][p1].peso = p;

//     return 1;
 
// }

// int remove_aresta(Grafo g, TChave v1, TChave v2){
//     int p1 = pesquisa_vertice(g, v1);
//     int p2 = pesquisa_vertice(g, v2);
   
//     if(p1 == -1 || p2 == -1)
//         return 0;

//     if(g->arestas[p1][p2].conectado == 0)
//         return 0;
    
//     g->arestas[p1][p2].conectado = 0;
//     g->arestas[p2][p1].conectado = 0;

//     return 1;
// }