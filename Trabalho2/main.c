#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include<stdbool.h>

void CriaVetoresAux(int quantVertices);
void Inicializa(int s,int quantVertices);
void Relaxa(int chave, int ligado, int peso);
void Dijkstra(int partida,int quantVertices, int numeroLinhas);
int extrairMinimo(int quantVertices);

typedef struct {
    int chave;
    int ligado;
    int peso;
} Aresta;

Aresta * arestas;

int * dist;
int * pai;

int * conjQ; // Distância provisória
int * conjS; // Distancia mínima garantida

int count = 0;

int main (void){
    int ver = 0,lig = 0,pe = 0;
    char *line_buf = NULL;
    size_t line_buf_size = 0;

    int quantVertices,numeroLinhas = 0,i=0;

    FILE *p;
    p = fopen("n25.txt","r");
    if(p == NULL){
        printf("ERRO! O arquivo nao foi aberto!\n");
        exit(100);
    }else 
    {
        //Criando a quantidade certa de elementos no vetor de structs
        while(getline(&line_buf, &line_buf_size, p) > 0){
            arestas = malloc(sizeof(Aresta));
        }
        rewind(p);
        //Lendo a primeira linha
        fscanf(p,"%d",&quantVertices);
        printf("quantVertices = %d\n\n",quantVertices);

        while (!feof(p)){
            numeroLinhas++;
            fscanf(p,"%d %d %d",&ver,&lig,&pe);
            //printf("vertice = %d  ligado %d  peso = %d\n",ver,lig,pe);
            arestas[i].chave = ver;
            arestas[i].ligado = lig;
            arestas[i].peso = pe;
            i++;
        }
        printf("numeroLinhas = %d\n",numeroLinhas);

        CriaVetoresAux(quantVertices);
        

        Dijkstra(0,quantVertices,numeroLinhas);

        for(int i = 0; i < quantVertices;i++){
            printf("dist[%d] = %d\n",i,dist[i]);
        }
        printf("-----------------------------------\n");
        for(int i = 0; i < quantVertices;i++){
            printf("pai[%d] = %d\n",i,pai[i]);
        }
        // printf("-----------------------------------\n");
        // for(int i = 0; i < quantVertices;i++){
        //     printf("conjQ[%d] = %d\n",i,conjQ[i]);
        // }
    }
}

//Funcionando
void CriaVetoresAux(int quantVertices){
    dist = malloc(quantVertices * sizeof(int));
    pai = malloc(quantVertices * sizeof(int));
    conjQ = malloc (quantVertices * sizeof(int));
    conjS = malloc (quantVertices * sizeof(int));
}
//Funcionando
void Inicializa(int s,int quantVertices){
    for(int i = 0; i < quantVertices;i++){
        dist[i] = 9999999;
        pai[i] = 9999999;
        conjQ[i] = 1; //Setando todos como verdadeiro(1)
        conjS[i] = 0; //Setando todos como falso(0), pois ainda não conhecemos a menor distância de nenhum vértice
    }
    dist[s] = 0;

    // for(int i = 0 ; i < quantVertices;i++){
    //     printf("dist[%d] = %d\n",i,dist[i]);
    // }
}

void Relaxa(int chave, int ligado, int peso){
    if(dist[ligado] > (dist[chave] + peso)){
        dist[ligado] = dist[chave] + peso;
        pai[ligado] = chave;
    }
}

void Dijkstra(int partida,int quantVertices,int numeroLinhas){
    Inicializa(partida,quantVertices);
    int p = 0;
    int u = 0;
    u = extrairMinimo(quantVertices);
    printf("u = %d\n",u);
    //Falta a repetição do Enquanto |Q| != 0
        //while(count < quantVertices){   ----- TESTANDO
        //Para cada adjacente...
        for(int i = 0 ; i < numeroLinhas;i++){
            if(arestas[i].chave == u){
                Relaxa(arestas[i].chave,arestas[i].ligado,arestas[i].peso);
            }
        }
    }
}
//Vertice com menor valor tem que ser EXTRAIDO do conjunto Q
int extrairMinimo(int quantVertices){
    int minimo = 999999;
    int verticeMinimo;
    for(int i = 0; i < quantVertices;i++){
        if(conjQ[i] == 1 && dist[i] < minimo){
            minimo = dist[i];
            verticeMinimo = i;
        }
    }
    conjQ[verticeMinimo] = 0;
    conjS[verticeMinimo] = 1;
    count++;
    return verticeMinimo;
}