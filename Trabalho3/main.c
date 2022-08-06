#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define INF 999999
int populando(double * mat,int numeroLinhas);

//Prim
void inicializa(int numerolinhas,int verticeInicial);
int extrairMinimo(int numerolinhas);
void criaAGM(int numerolinhas,int raiz);
void printaAGM(int numerolinhas);

void maiorSubGrafoInduzido(int numerolinhas);
void printmaiorSubGrafoInduzido();

void quick_sort(int left,int right);
typedef struct {
    int chave;
    int ligado;
    float peso;
} Aresta;

Aresta * arestas;

double ** matrizAdjacencia;

//Variavel global
int numerolinhas = 0;

int * altura;

Aresta * mstFinal;

Aresta resultado[2];

//Variáveis para o PRIM
int * chave;

int * pai;

int * q;

//AGM

Aresta * AGM;

//Maior subgrafo induzido
Aresta * maiorSubInduz;

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
        int total = populando(&matrizAdjacencia[0][0],numerolinhas);
        printf("total = %d\n",total);
        criaAGM(numerolinhas,0);
        printf("Antes da ordenacao :\n");
        printaAGM(numerolinhas);
        printf("--------------------------------------\n");
        printf("Depois da ordenacao :\n");
        quick_sort(0,numerolinhas - 1);
        printaAGM(numerolinhas);
        printf("--------------------------------------\n");
        maiorSubGrafoInduzido(numerolinhas);
        printmaiorSubGrafoInduzido();
    }
}


int populando(double * mat,int numeroLinhas){ //OK
    int i,j,k=0;
    int total = (numeroLinhas*(numeroLinhas-1)) /2;
    arestas = malloc(total * sizeof(Aresta));
    for(i = 0;i <numeroLinhas-1;i++){
        for(j = i+1;j<numeroLinhas;j++){
            arestas[k].chave = i;
            arestas[k].ligado = j;
            arestas[k].peso = mat[i*numeroLinhas+j]; 
            k++;
            }
        }
    return total;
}

void inicializa(int numerolinhas,int verticeInicial){ //OK

    //Alocando os vetores auxiliares
    chave = malloc(numerolinhas * sizeof(int));
    pai = malloc(numerolinhas * sizeof(int));
    q = malloc(numerolinhas * sizeof(int));

    //Iniciando os vetores auxiliares
    for(int i = 0; i < numerolinhas;i++){
        chave[i] = INF;
        pai[i] = INF;
        q[i] = 0;
    }
    chave[verticeInicial] = 0;

    //Inicializando AGM
    AGM = malloc((numerolinhas - 1) * sizeof(Aresta));
}

int extrairMinimo(int numerolinhas){ //OK
    int minimo = 9999999;
    int vertice;
    for(int i = 0; i < numerolinhas;i++){
        if(chave[i] < minimo && q[i] == 0){
            minimo = chave[i];
            vertice = i;
        }
    }
    q[vertice] = 1;
    return vertice;
}

void criaAGM(int numerolinhas,int raiz){
    int u,x=0;
    inicializa(numerolinhas,raiz);
    for(int i = 0; i < numerolinhas;i++){ //Não sei se é numerolinhas -1 ou numerolinhas
        u = extrairMinimo(numerolinhas);
        if(u != raiz){//Precisamos adicionar aresta na resposta final(AGM no meu caso)
            AGM[x].chave = u;
            AGM[x].ligado = raiz;
            AGM[x].peso = matrizAdjacencia[u][raiz];
            raiz = u;
            x++;
        }
        for(int j = 0; j < numerolinhas;j++){ //Para cada adjacente do vertice U
            if(matrizAdjacencia[u][j] != 0 && q[j] != 1){
                if(matrizAdjacencia[u][j] < chave[j]){
                    chave[j] = matrizAdjacencia[u][j];
                    pai[j] = u;
                } 
            }
        }
    }
}

void printaAGM(int numerolinhas){
    for(int i = 0; i <numerolinhas - 1;i++){
        printf("AGM[%d]  chave = %d  ligado = %d  peso = %.2f\n",i,AGM[i].chave,AGM[i].ligado,AGM[i].peso);
    }
}

void quick_sort(int left,int right){
    int i,j;
    double x;
    Aresta y;

    i = left;
    j = right;
    x = AGM[(left + right) / 2].peso;

    while(i <= j){
        while(AGM[i].peso > x && i < right){
            i++;
        }
        while(AGM[j].peso < x && j > left){
            j--;
        }
        if(i <= j){
            y = AGM[i];
            AGM[i] = AGM[j];
            AGM[j] = y;
            i++;
            j--;
        }
    }
    if(j > left){
        quick_sort(left,j);
    }
    if(i < right){
        quick_sort(i,right);
    }
}


void maiorSubGrafoInduzido(int numerolinhas){
    int j = 0, x = 0, y = 2, q = 0;

    maiorSubInduz = malloc(4 * sizeof(Aresta));

    int grau[2][5];
    for(int i = 0; i < 2;i++){
        for(int j = 0; j < 5;j++){
            grau[i][j] = 999999;
        }
    }

    maiorSubInduz[x] = AGM[0];
    grau[0][0] = AGM[0].chave;
    grau[0][1] = AGM[0].ligado;
    grau[1][0] = 1;
    grau[1][1] = 1;

    for(int i = 1; i < numerolinhas - 1 && y < 5;i++){
        while(j < 5 && q == 0){
            if(AGM[i].chave == grau[0][j]){
                if(grau[1][j] < 3){
                    x++;
                    maiorSubInduz[x] = AGM[i]; //Inserindo aresta na resposta final
                    grau[0][y] = AGM[i].ligado;   //Colocando o novo vértice na matriz
                    grau[1][y] = 1;              //Grau do novo vértice = 1
                    grau[1][j] = grau[1][j] + 1; // Grau do vértice que já existe = +1
                    y++;
                    q = 1;
                }
            }
            if(AGM[i].ligado == grau[0][j]){
                if(grau[1][j] < 3){
                    x++;
                    maiorSubInduz[x] = AGM[i]; //Inserindo aresta na resposta final
                    grau[0][y] = AGM[i].chave;   //Colocando o novo vértice na matriz
                    grau[1][y] = 1;              //Grau do novo vértice = 1
                    grau[1][j] = grau[1][j] + 1; // Grau do vértice que já existe = +1
                    y++;
                    q = 1;
                }
            }
            j++;
        }
        j = 0;  
        q = 0;
    }
    // for(int i = 0; i <5;i++){
    //     printf("%d ",grau[0][i]);
    // }
}

void printmaiorSubGrafoInduzido(){
    for(int i = 0; i < 4;i++){
        printf("chave = %d ligado = %d  peso = %.2f\n",maiorSubInduz[i].chave,maiorSubInduz[i].ligado,maiorSubInduz[i].peso);
    }
}