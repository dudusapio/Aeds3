#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void CriaVetoresAux(int quantVertices);
void Inicializa(int s,int quantVertices);

typedef struct {
    int chave;
    int ligado;
    int peso;
} Aresta;

Aresta * arestas;

int * dist;
int * pai;


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

        Inicializa(0,quantVertices);

    }
}

void CriaVetoresAux(int quantVertices){
    dist = malloc(quantVertices * sizeof(int));
    pai = malloc(quantVertices * sizeof(int));
}

void Inicializa(int s,int quantVertices){
    for(int i = 0; i < quantVertices;i++){
        dist[i] = 9999999;
        pai[i] = 9999999;
    }
    dist[s] = 0;
}

// void Relaxa();

// void Dijkstra(){

// }
