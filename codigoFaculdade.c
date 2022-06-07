#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double * vet;

// Fila Semantica
int Fila[100];
int topo = -1;

// Rotina de fila semantica
void enfileira(int valor) {
    if (topo == 100){
        printf("Fila cheia!\n");
        exit(100);
    }
    Fila[++topo] = valor;
}

int desemfileira() {
    int tmp;
    int tmp1 = 0;
    if (topo == -1){
        printf("Fila Vazia!\n");
        exit(100);
    }
    tmp = Fila[0];
    for(int i = 0; tmp1 != topo;i++,tmp1++){
        Fila[i] = Fila[i + 1]; 
        Fila[i + 1] = tmp;
    }
    return Fila[topo--];
}

//Escopo funcao busca em largura
void bfs(double *vet, int vertice);

//Variavel global
int numerolinhas = 0;

int main (void){
    int z = 0,x = 0,y = 0;
    char *line_buf = NULL;
    ssize_t line_buf_size = 0;

    int **matriz;
    FILE *p;
    p = fopen("dados.txt","r");
    if(p == NULL){
        printf("ERRO! O arquivo não foi aberto!\n");
        exit(100);
    }else 
    {
        printf("Arquivo aberto com sucesso!\n");
        while(getline(&line_buf, &line_buf_size, p) > 0){
            numerolinhas++;
        }
        fclose(p);
        p = fopen("dados.txt","r");
        matriz = calloc(numerolinhas, numerolinhas * sizeof(int*));
        int i = 0;
        while (!feof(p)){
            fscanf(p,"%d %d %d",&z,&x,&y);
            //printf("z =   %d   x = %d    y = %d\n",z,x,y);
            matriz[i] = calloc( 2, sizeof( int ));    
            matriz[i][0] = x;
            matriz[i][1] = y;
            i++;
        }
        //printf("Numero de linhas = %d\n",numerolinhas);

        //Matriz de adjacência

        double matrizAdjacencia[numerolinhas][numerolinhas];
        for(i = 0;i < numerolinhas;i++){
            for(int j = 0;j < numerolinhas;j++){
                matrizAdjacencia[i][j] = sqrt(pow((matriz[i][0] - matriz[j][0]),2) + pow((matriz[i][1] - matriz[j][1]),2));
            }
        }
        FILE * arq1 = fopen("provisorio.txt","w");
        for(i = 0;i<numerolinhas;i++){
            fprintf(arq1,"\n");
            for(int j = 0;j<numerolinhas;j++){
                fprintf(arq1,"%.2lf     ",matrizAdjacencia[i][j]);
            }
        }

        //Busca em Largura

        FILE * testando = fopen("testando.txt","w");
        vet = malloc(numerolinhas * sizeof(double));
        for(i = 0;i < numerolinhas; i++){
            vet[i] = matrizAdjacencia[i][0];
            fprintf(testando,"vet[%d] = %.2lf\n",i,vet[i]);
        }
        printf("\n\n");
        printf("vet[40] = %.2lf\n",vet[40]);
        printf("vet[46] = %.2lf\n",vet[46]);
        printf("vet[46] = %.2lf\n",vet[47]);
        //bfs(vet,5);

    }

}


void bfs(double *vet, int indiceVertice){
    printf("vettttttttt[10] = %.2lf\n",vet[46]);
    //Nao sei porque todas as posicicoes do vetor menos a ultima esta chegando com o valor 0.
    char cor[numerolinhas];
    int pai[numerolinhas];
    int distancia[numerolinhas];
    int i,u;
    char k[1];
    for(i = 0; i < numerolinhas; i++){
        cor[i] = 'B';
        distancia[i] = 0;
        pai[i] = 9999;
    }
    cor[indiceVertice] = 'C';
    distancia[indiceVertice] = 0;
    pai[indiceVertice] = 9999; // 9999 = ele e o pai

    //Printa o vetor de cores
    for(i = 0;i < numerolinhas;i++){
        printf("cor[%d] = %c\n",i,cor[i]);
    }
    
    enfileira(indiceVertice);
    while (topo != -1){
        u = desemfileira();
        for(i = 0; i < numerolinhas;i++){
            printf("vet[%d] = %.2lf && cor[%d] = %c\n",i,vet[i],i,cor[i]);
            if(vet[i] != 0 && cor[i] == 'B'){ 
                cor[i] = 'C';
                distancia[i] = distancia[i] + 1;
                pai[i] = indiceVertice;
                enfileira(i); 
            }
            cor[u] = 'P';
        }
    }
    printf("vettttttttt[10] = %.2lf\n",vet[10]);
    printf("\n");
    //Printa o vetor de cores
    for(i = 0;i < numerolinhas;i++){
        printf("cor[%d] = %c\n",i,cor[i]);
    }
}