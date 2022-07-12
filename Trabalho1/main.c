#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int populando(double * mat,int numeroLinhas);
void printmstFinal(int numerolinhas);

void maiorSubgrafo(int numeroLinhas);
void printMaiorSubgrafo();

//Chefe
void initialize2(int numeroLinhas);
int find2(int chave);
void Uniao2(int r, int s);
void MST2(int numeroLinhas, int total);

typedef struct {
    int chave;
    int ligado;
    float peso;
} Aresta;

Aresta * arestas;

void quicksort(Aresta * arestas, int began, int end);

//Variavel global
int numerolinhas = 0;

int * dir;
int * chefe;

int * altura;

Aresta * mstFinal;

Aresta resultado[2];

//Iniciando a lista das arestas

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
            matriz[i] = calloc( 2, sizeof( int ));    
            matriz[i][0] = x;
            matriz[i][1] = y;
            i++;
        }
        //Matriz de adjacência

        double matrizAdjacencia[numerolinhas][numerolinhas];

        // double ** matrizAdjacencia = malloc(numerolinhas * sizeof(double));
        // for(int i = 0; i < numerolinhas;i++){
        //     matrizAdjacencia[i] = malloc((numerolinhas) * sizeof(double));
        // }
        for(i = 0;i < numerolinhas;i++){
            for(int j = 0;j < numerolinhas;j++){
                matrizAdjacencia[i][j] = sqrt(pow((matriz[i][0] - matriz[j][0]),2) + pow((matriz[i][1] - matriz[j][1]),2));
            }
        }

        // //TESTE

        // double ** matrizAdjacencia = malloc((numerolinhas * numerolinhas) * sizeof(double));

        // for(i = 0;i < numerolinhas;i++){
        //     for(int j = 0;j < numerolinhas;j++){
        //         matrizAdjacencia[i*numerolinhas+j] = sqrt(pow((matriz[i][0] - matriz[j][0]),2) + pow((matriz[i][1] - matriz[j][1]),2));
        //     }
        // }        
        // //

        FILE * arq1 = fopen("matrizAdjacencia.txt","w");
        for(i = 0;i<numerolinhas;i++){
            fprintf(arq1,"\n");
            for(int j = 0;j<numerolinhas;j++){
                fprintf(arq1,"%.2lf     ",matrizAdjacencia[i][j]);
            }
        }       
        int total = populando(&matrizAdjacencia[0][0],numerolinhas);
        FILE * arquivo = fopen("vetorDesordenado.txt","w");
        for(int i = 0; i < total; i++){
            fprintf(arquivo,"chave = %d  ligado = %d  peso = %f\n",arestas[i].chave,arestas[i].ligado,arestas[i].peso);
        }

        quicksort(arestas,0,total);

        FILE * arquivo1 = fopen("vetorOrdenado.txt","w");
        for(int i = 0; i < total; i++){
            fprintf(arquivo1,"chave = %d  ligado = %d  peso = %f\n",arestas[i].chave,arestas[i].ligado,arestas[i].peso);
        }

        MST2(numerolinhas,total);
        printmstFinal(numerolinhas);
        maiorSubgrafo(numerolinhas);
        printMaiorSubgrafo();

        for(int i = 0 ; i < 2;i++){
            printf("peso = %f",resultado[i].peso);
        }



        //Desalocando
        free(matriz);
        free(matrizAdjacencia);
        free(arestas);
        free(chefe);
        free(mstFinal);
    }
}


int populando(double * mat,int numeroLinhas){
    int i,j,k=0;
    int total = (numeroLinhas*(numeroLinhas-1))/2;
    arestas = malloc(total * sizeof(Aresta));
    for(i = 0;i <numeroLinhas-1;i++){
        for(j = i+1;j<numeroLinhas;j++){
            arestas[k].chave = i;
            arestas[k].ligado = j;
            arestas[k].peso = mat[(i*numeroLinhas)+j]; 
            //printf("chave = %d  ligado = %d  peso = %f\n",arestas[k].chave,arestas[k].ligado,arestas[k].peso);
            k++;
            }
        //printf("k = %d\n",k);
        }
        
    return total;
}

void quicksort(Aresta * arestas, int began, int end)
{
	int i, j;
    Aresta aux;
    float pivo;
	i = began;
	j = end-1;
	pivo = arestas[(began + end) / 2].peso;
	while(i <= j)
	{
		while(arestas[i].peso < pivo && i < end)
		{
			i++;
		}
		while(arestas[j].peso > pivo && j > began)
		{
			j--;
		}
		if(i <= j)
		{
			aux = arestas[i];
			arestas[i] = arestas[j];
			arestas[j] = aux;
			i++;
			j--;
		}
	}
	if(j > began)
		quicksort(arestas, began, j+1);
	if(i < end)
		quicksort(arestas, i, end);
}

void printmstFinal(int numerolinhas){
    int i;
    for(i = 0; i < numerolinhas - 1;i++){
        printf("mstFinal[%d] ==  chave = %d  ligado = %d  peso = %f\n",i,mstFinal[i].chave,mstFinal[i].ligado,mstFinal[i].peso);
    }
    printf("quantidade = %d\n",i);
}

void initialize2(int numeroLinhas){
    chefe = malloc(numeroLinhas * sizeof(int));
    for(int i = 0 ; i < numeroLinhas;i++){
        chefe[i] = i;
    }
}

int find2(int chave){
    while(chefe[chave] != chave){
        chave = chefe[chave];
    }
    return chave;
}

void Uniao2(int r, int s){
    if(chefe[r] != r){ 
        chefe[s] = chefe[r];
    }
    else{
        chefe[r] = chefe[s];
    }
}


void MST2(int numeroLinhas,int total){
    int i,j = 0;
    mstFinal = malloc((numeroLinhas-1) * sizeof(Aresta));
    int r,s,count=0;
    initialize2(numeroLinhas);
    for(i = 0;i < total && j < numeroLinhas - 1;i++){
        r = arestas[i].chave;
        s = arestas[i].ligado;
        if(find2(r) != find2(s)){ 
            mstFinal[j] = arestas[i];
            Uniao2(r,s);
            j++;
        }
    }
    printf("count = %d\n",count);
}

void maiorSubgrafo(int numeroLinhas){
    int x = 0;
    double somaPesos = 0;
    for(int i = 0;i < numeroLinhas - 1;i++){
        for(int j = i + 1; j < numeroLinhas - 1; j++){
            if(mstFinal[j].chave == mstFinal[i].chave || mstFinal[j].chave == mstFinal[i].ligado || mstFinal[j].ligado == mstFinal[i].chave || mstFinal[j].ligado == mstFinal[i].ligado){
                if(mstFinal[i].peso + mstFinal[j].peso > somaPesos){
                    somaPesos = mstFinal[i].peso + mstFinal[j].peso;
                    resultado[x] = mstFinal[i];
                    resultado[x + 1] = mstFinal[j];
                }
            }
        }
    }
}

void printMaiorSubgrafo(){
    double pesoTotal = resultado[0].peso + resultado[1].peso;
    if(resultado[0].chave == resultado[1].chave || resultado[0].chave == resultado[1].ligado){
        printf("%d %d %d\n",resultado[0].ligado,resultado[1].chave,resultado[1].ligado);
    }
    else{
        printf("%d %d %d\n",resultado[0].chave,resultado[1].chave,resultado[1].ligado);
    }
    printf("%.2f\n",pesoTotal);
}