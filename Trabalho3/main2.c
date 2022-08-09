#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void maiorSubGrafo(int numerolinhas);
void printMaiorSubGrafo();
void heuristicaBuscaLocal(int numerolinhas);
typedef struct {
    int chave;
    int ligado;
    float peso;
} Aresta;

Aresta * subGrafo;

double ** matrizAdjacencia;

//Variavel global
int numerolinhas = 0;

//Iniciando a lista das arestas

int main (int argc, char *argv[]){
    int z = 0,x = 0,y = 0;
    char *line_buf = NULL;
    size_t line_buf_size = 0;

    int **matriz;
    FILE * p;
    p = fopen(argv[1],"r");
    if(p == NULL){
        printf("ERRO! O arquivo nao foi aberto!\n");
        exit(100);
    }else 
    {
        printf("%s\n",argv[1]);
        while(getline(&line_buf, &line_buf_size, p) > 0){
            numerolinhas++;
        }
        printf("numero de linhas = %d\n\n",numerolinhas);
        fclose(p);
        p = fopen(argv[1],"r");
        matriz = calloc(numerolinhas, numerolinhas * sizeof(int*));
        int i = 0;

        while (!feof(p)){
            fscanf(p,"%d %d %d",&z,&x,&y);

            matriz[i] = calloc( 2, sizeof( int ));    
            matriz[i][0] = x;
            matriz[i][1] = y;
            i++;
        }
        //Matriz de adjacencia
        matrizAdjacencia = malloc(numerolinhas * sizeof(double));
        for(int i = 0; i < numerolinhas;i++){
            matrizAdjacencia[i] = malloc(numerolinhas * sizeof(double));
        }
        for(i = 0;i < numerolinhas;i++){
            for(int j = 0;j < numerolinhas;j++){
                matrizAdjacencia[i][j] = sqrt(pow((matriz[i][0] - matriz[j][0]),2) + pow((matriz[i][1] - matriz[j][1]),2));
            }
        }      
        //Printando matriz de adjacência
        FILE * arquivoo = fopen("matrizAdja.txt","w");
        for(i = 0;i < numerolinhas;i++){
            fprintf(arquivoo,"\n");
            for(int j = 0;j < numerolinhas;j++){
                fprintf(arquivoo,"%8f  ",matrizAdjacencia[i][j]);
            }
        } 

        subGrafo = malloc(4 * sizeof(Aresta));

        maiorSubGrafo(numerolinhas);
        printf("-------------------\n");
        heuristicaBuscaLocal(numerolinhas);
    }
} 
void maiorSubGrafo(int numerolinhas){
    int maior = 0;
    int indiceJ,indiceJ2;
    int x = 0;
    int div = numerolinhas/3;
    int count = 0;
    //for(int i = 0; i < numerolinhas;i = i + div){
    for(int i = 0; i < 3;i++){    
        for(int j = count; j < div + count && j < numerolinhas;j++){
            if(matrizAdjacencia[0][j] > maior){
                maior = matrizAdjacencia[0][j];
                indiceJ = j;
            }
        }
        //Aqui vai sair o maior
        subGrafo[x].chave = 0;
        subGrafo[x].ligado = indiceJ;
        subGrafo[x].peso = maior;
        x++;
        maior = 0;
        count = count + div;
    }
    for(int i = 1 ; i < numerolinhas; i++){
        if(matrizAdjacencia[indiceJ][i] > maior){
            maior = matrizAdjacencia[indiceJ][i];
            indiceJ2 = i;
        }
    }
    subGrafo[x].chave = indiceJ;
    subGrafo[x].ligado = indiceJ2;
    subGrafo[x].peso = maior;
    printMaiorSubGrafo();
}


void printMaiorSubGrafo(){
    for(int i = 0 ; i < 4;i++){
        printf("chave = %d  ligado = %d  peso = %.2f\n",subGrafo[i].chave,subGrafo[i].ligado,subGrafo[i].peso);
    }
}


void heuristicaBuscaLocal(int numerolinhas){
    int maior = 0;
    int indiceJ;
    for(int i = 0 ; i < numerolinhas;i++){
        if(subGrafo[1].peso < matrizAdjacencia[subGrafo[0].ligado][i] && subGrafo[2].ligado != i && subGrafo[3].ligado != i){
            subGrafo[1].chave = subGrafo[0].ligado;
            subGrafo[1].ligado = i;
            subGrafo[1].peso = matrizAdjacencia[subGrafo[0].ligado][i];
        }
    }
    printMaiorSubGrafo();
}







