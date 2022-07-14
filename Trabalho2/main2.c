#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define INF 99999

void floydWarshall(int quantVertices);
void printSolution(int quantVertices);
void verticesMaior(int quantVertices);

typedef struct {
    int chave;
    int ligado;
    int peso;
} Aresta;

int ** mat;

int ** dist;

int vertice1,vertice2;

int count = 0;

int main (void){
    int ver = 0,lig = 0,pe = 0;
    char *line_buf = NULL;
    size_t line_buf_size = 0;

    int quantVertices,numeroLinhas = 0,i=0,j = 0;

    FILE *p;
    p = fopen("n25.txt","r");
    if(p == NULL){
        printf("ERRO! O arquivo nao foi aberto!\n");
        exit(100);
    }else 
    {
        //Lendo a primeira linha
        fscanf(p,"%d",&quantVertices);
        printf("quantVertices = %d\n\n",quantVertices);
        
        //Criando a matriz
        mat = (int **) malloc(quantVertices * sizeof(int*));
        for(i = 0; i < quantVertices; i++) {
            mat[i] = (int *) malloc(quantVertices * sizeof(int));
        }
        
        //Zerando a matriz
        for(i = 0 ; i < quantVertices;i++){
            for(j = 0 ; j < quantVertices;j++){
                if(i == j){
                    mat[i][j] = 0;
                }else{
                mat[i][j] = INF;
                }
            }
        }
        
        FILE * arq = fopen("MatZerada.txt","w");
        for(int i = 0 ; i < quantVertices;i++){
            fprintf(arq,"\n");
            for(int j = 0 ; j < quantVertices;j++){
                fprintf(arq,"%7d  ",mat[i][j]);
            }
        }

        while (!feof(p)){
            numeroLinhas++;
            fscanf(p,"%d %d %d",&ver,&lig,&pe);
            mat[ver][lig] = pe;
            mat[lig][ver] = pe;   
        }
        printf("numeroLinhas = %d\n",numeroLinhas);

        FILE * arquivo = fopen("MatPopulada.txt","w");
        for(int i = 0 ; i < quantVertices;i++){
            fprintf(arquivo,"\n");
            for(int j = 0 ; j < quantVertices;j++){
                fprintf(arquivo,"%10d",mat[i][j]);
            }
        }

        //Floyd-Warshall 
        floydWarshall(quantVertices);
        //1. Pegar os vértices que possuem o maior peso do resultado do floydWarshall
        verticesMaior(quantVertices);
        printf("vertice1 = %d\n",vertice1);
        printf("vertice2 = %d\n",vertice2);
        printf("peso = %d\n",dist[vertice1][vertice2]);
        //2. Rodar um dijstra a partir de algum desse vértice até o outro vértice.
        //3. Printar os pais
    }
}


void floydWarshall(int quantVertices){
    int i,j,k;
    //Criando a matriz
    dist = (int **) malloc(quantVertices * sizeof(int*));
    for(i = 0; i < quantVertices; i++) {
        dist[i] = (int *) malloc(quantVertices * sizeof(int));
    }

    for(i = 0;i < quantVertices;i++){
        for(j = 0;j < quantVertices;j++){
            dist[i][j] = mat[i][j];
        }
    }

    FILE * arquivo1 = fopen("dist.txt","w");
    for(int i = 0 ; i < quantVertices;i++){
        fprintf(arquivo1,"\n");
        for(int j = 0 ; j < quantVertices;j++){
            fprintf(arquivo1,"%10d",dist[i][j]);
        }
    }
    
    for(k = 0; k < quantVertices; k++){
        for(i = 0; i < quantVertices; i++){
            for(j = 0; j < quantVertices; j++){
                if (dist[i][k] + dist[k][j] < dist[i][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    printSolution(quantVertices);
}

void printSolution(int quantVertices){
    for (int i = 0; i < quantVertices; i++){
        for (int j = 0; j < quantVertices; j++){
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf ("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

void verticesMaior(int quantVertices){
    int i,j,maior = 0;
    for(i = 0; i < quantVertices; i++){
        for(j = 0; j < quantVertices; j++){
            if(dist[i][j] > maior){
                maior = dist[i][j];
                vertice1 = i;
                vertice2 = j;
            }
        }
    }
}