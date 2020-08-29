#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "cedula.h"
#include "hash_abp.h"
#include "hash_lista.h"
#include "hash_duplo.h"
#include "abp.h"
#define STD_BUF 100


 enum Acao {VOTAR = 0, REMOVER = 1, APURAR = 2, ENCERRAR = 3, INVALIDO = -1};

 enum Estrutura {HASH_DUPLO = 1, HASH_ABP = 2, HASH_LISTA = 3};

 enum Classes {PREFEITO = 1, VEREADOR = 2};

typedef struct
{
    HashLista hashLista;
    HashDuplo hashDuplo;
    HashAbp hashAbp;

}Estruturas;


int lerInteiro(const char * txt){
    printf("%s", txt);
    int r;
    scanf("%d", &r);
    return r;
}

void lerString(const char * txt, char* retorno, int tamanho){
    printf("%s", txt);
    setbuf(stdin, NULL);
    fgets(retorno, tamanho, stdin);
    setbuf(stdin, NULL);

    for(int i =0; i<tamanho; i++){
        
        if(retorno[i] == '\0')
            break;
        
        if(retorno[i] == '\n'){
            retorno[i] = '\0';
            break;
        }
    }
}

void quebrarString(char * s, const char * delimitador, char* resultado[], int size_resultado){
    
    char * token = strtok(s, delimitador);
    int i = 0;

    while(token != NULL && i < size_resultado){
        resultado[i++] = token;

        printf("TOKEN: %s\n", token);

        token = strtok(NULL, delimitador);

        
    }
}


int invalido(const char * dado){
    printf("\nDados inválidos: %s.", dado);
    return 0;
}

int votoInvalido(){
    printf("\nvoto não computado.\n");
    return 0;
}

int pesquisar_voto(Estruturas * est, int estrutura, TChave id, TElemento *e){
    
    if(estrutura == HASH_LISTA)
        return pesquisa_hash_lista(est->hashLista, id, e);
    if(estrutura == HASH_DUPLO)
        return pesquisa_hash_duplo(est->hashDuplo, id, e);
    
    return pesquisa_hash_abp(est->hashAbp, id, e);
}

int registrar_escolha(int classe, int numeroCandidato, TElemento* voto){
    if(classe == PREFEITO){
        if(voto->votouPrefeito)
            return votoInvalido();
        else{
            voto->prefeito = numeroCandidato;
            voto->votouPrefeito = 1;
        }
    }
    else{
         if(voto->votouVereador)
            return votoInvalido();
        else{
            voto->vereador = numeroCandidato;
            voto->votouVereador = 1;
        }
    }
    return 1;
}

int editar_voto(Estruturas * est, int estrutura,  TElemento voto){
    return 1;
}

int inserir_voto(Estruturas * est, int estrutura, TElemento e){
    
    if(estrutura == HASH_LISTA)
        return insere_hash_lista(est->hashLista, e);
    else if(estrutura == HASH_DUPLO)
        return insere_hash_duplo(est->hashDuplo, e);

    return insere_hash_abp(est->hashAbp, e);
}

int votar(Estruturas * est, char * parametros[4]){
  

    //Checando escolha da estrutura
    if(parametros[0] == NULL) return invalido("estrutura escolhida");

    int estrutura = atoi(parametros[0]);
    
    if(estrutura < HASH_DUPLO || estrutura > HASH_LISTA ) 
        return invalido("estrutura escolhida");;


    //Checando classe
    if(parametros[1] == NULL) return invalido("classe do candidato");

    int classe = atoi(parametros[1]);

    if(classe < 1 || classe > 2 ) return invalido("classe do candidato");

    //Checando titulo
    if(parametros[2] == NULL) return invalido("titulo do eleitor");

    if(parametros[3] == NULL) return invalido("numero do candidato");
    int candidato = atoi(parametros[3]);



    //Salvando em TElemento
    TElemento voto;
    strcpy(voto.id.tituloEleitor, parametros[2]);

    int votoExiste = pesquisar_voto(est, estrutura, voto.id, &voto);

    if(!registrar_escolha(classe, candidato, &voto)) return 0;
    
    //Salavando TElemento em estrutura
    return votoExiste == -1 ? inserir_voto(est, estrutura, voto) : editar_voto(est, estrutura, voto);

}


int interpretar_acao(char * acao, char* resultado[4]){
    
    
    quebrarString(acao, " ", resultado, 4);

    printf("ACAO %s\n\n ", acao);
    
    int a = atoi(resultado[0]);

    if(a < VOTAR || a > ENCERRAR)
        a = INVALIDO;

    return a;
}

int entrada_de_dados(){

    int estrutura = lerInteiro("Tipo da estrutura\n1-Hash Duplo\n2-Hash com Abp\n3-Hash com Lista\n->>");
    if(estrutura < 1 || estrutura > 3) return invalido("tipo estrutura invalido");

    char s_acao[STD_BUF];
    char* resultado[4];

    while(true){
        
        lerString("Digite uma ação: ", s_acao, STD_BUF);
        
        int a = interpretar_acao(s_acao, resultado);

        if(a == ENCERRAR) return 1;
        
        switch (a)
        {
        case VOTAR:
            printf("\nAcao de votar");
            break;
        case REMOVER:
            printf("\nAcao de remover");
            break;
        
        case APURAR:
            printf("Acao de apurar");
            break;
        
        case ENCERRAR:
            printf("Acao de encerrar");
            break;

        default:
            break;
        }
    

    }

    return 1;
}

int main()
{
    setlocale(LC_ALL, "PT-BR");

    entrada_de_dados();

    printf("Hello world!\n");
  

    char strs[5][10] = {"foo", "bar", "bletch", "zipty", "zhadfg"};
    char c[100];

   int a = lerInteiro("Fodase? ");
   printf("%d\n", a);

   lerString("FFFFodase? ", c, 100);

   printf("\nc = %s", c);

    //HashAbp t = cria_hash_abp(10);

    //HashLista t = cria_hash_lista(10);

    HashDuplo t = cria_hash_duplo(10);

    TElemento e;

    for (int i = 0; i < 5; i++)
    {
        sprintf(e.id.tituloEleitor, "%s", strs[i]);

        print_tch(e.id);

        insere_hash_duplo(t, e);
        //insere_hash_lista(t, e);
        //insere_hash_abp(t, e);
    }
    
    printf("\n");
    print_hash_duplo(t);
    //print_hash_lista(t);
    //print_hash_abp(t);

    termina_hash_duplo(t);
    //termina_hash_lista(t);
    //termina_hash_abp(t);

    printf("\n");
    system("pause");


    return 0;
}

