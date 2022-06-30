#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

void populando(double * mat,int numeroLinhas);
void printar(int numeroLinhas);
void ordena();
void initialize(int numeroLinhas);
void PrintMST(int numeroLinha);
void MST(int numeroLinhas);
void PrintaArr(int numeroLinhas);
int find2(int chave);
void initialize2(int numeroLinhas);



//TESTE

void PrintMST2(int numeroLinha);
void MST2(int numeroLinhas);
void Uniao2(int r, int s);


typedef struct a_{
    int chave;
    int ligado;
    float peso;
    bool mst;
    struct a_ * prox;
} a;

//Variavel global
int numerolinhas = 0;

int * arr;

int * chief;

//Iniciando a lista das arestas
a * inicio;

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

        //ordenar        

        inicio = NULL;
        populando(&matrizAdjacencia[0][0],numerolinhas);
        ordena();

        //Printando ordenado:
        a * tmp2 = inicio;
        FILE * arquivo = fopen("ordenadooo.txt","w");
        while(tmp2 != NULL){
        fprintf(arquivo,"chave = %d - ligado = %d  peso = %f\n",tmp2->chave,tmp2->ligado,tmp2->peso);
            tmp2 = tmp2->prox;
        }

        int count = 0;

        // // Lógica de juntar os conjuntos
       MST(numerolinhas);
       PrintMST(numerolinhas);
       printf("teste\n\n\n");
       //PrintaArr(numerolinhas);
    }
}



void ordena(){
    a * tmp = inicio->prox; // Começa no primeiro vértice de fato
    a * menor = inicio->prox;
    a * antecessor = inicio->prox;
    a * antigoMenor = inicio;

    while(antigoMenor->prox != NULL){
        double menorPeso = 100000000;
        //Achando o menor peso e apontando o menor para ele
        while(tmp != NULL){
            if(tmp->peso < menorPeso){
                menorPeso = tmp->peso;
                menor = tmp;
            }
            tmp = tmp->prox;
        }
        //Posicionando o antecessor antes do menor
        while(antecessor->prox != menor){
            antecessor = antecessor->prox;
        }

        //O menor é o último nó, logo precisamos tratar de outra forma:
        if(menor->prox == NULL){
            antecessor->prox = NULL;
            menor->prox = antigoMenor->prox;
            antigoMenor->prox = menor;
        }
        else{
            antecessor->prox = menor->prox;
            menor->prox = antigoMenor->prox;
            antigoMenor->prox = menor;
        }

        //Atualizar variaveis
        antigoMenor = antigoMenor->prox;
        tmp = antigoMenor;
        antecessor = antigoMenor;
        if(antigoMenor->prox != NULL){
            tmp = antigoMenor->prox;
        }
        menor = NULL;
    }
}

void populando(double * mat,int numeroLinhas){
    int i,j;
    inicio = malloc(sizeof(a));
    inicio->chave = 0;
    inicio->ligado = 0;
    inicio->peso = 0;
    inicio->prox = NULL;
    a * topo = inicio;
    int quantidade = 0;
    for(i = 0;i <numeroLinhas;i++){
        for(j = i;j<numeroLinhas;j++){
            if(mat[i*numeroLinhas+j] == 0){
                topo->prox = NULL;
            }
            else{
            a * tmp = malloc(sizeof(a));
            topo->prox = tmp;
            tmp->chave = i;
            tmp->ligado = j;
            tmp->peso = mat[i*numeroLinhas+j];
            tmp->mst = false;
            tmp->prox = NULL;
            topo = topo->prox;
            quantidade++;
            }
        }
    }
    
    printf("quantidade = %d\n",quantidade);
    printar(numeroLinhas);
}

void printar(int numeroLinhas){
    FILE * arq = fopen("teste.txt","w");
    a * tmp = inicio->prox;
    int count = 0;
    while(tmp != NULL){

        fprintf(arq,"%f  ",tmp->peso);
        tmp = tmp->prox;
        count++;
        if(count == numeroLinhas){
            fprintf(arq,"\n");
            count = 0;
        }
    }
}

void initialize(int numeroLinhas){
    arr = malloc(numeroLinhas * sizeof(int));
    for(int i = 0 ; i < numeroLinhas;i++){
        arr[i] = i;
    }
}

int find(int chave){
    return arr[chave];
}

void Uniao(int r, int s,int numeroLinhas,a * tmp){
    for(int i = 0 ; i < numerolinhas;i++){
        if(arr[i] == r){
            arr[i] = s;
            tmp->mst = true;
        }
    }
}

void MST(int numeroLinhas){
    a * tmp = inicio->prox;
    int r,s,count=0;
    initialize(numeroLinhas);
    while(tmp != NULL){
        r = tmp->chave;
        s = tmp->ligado;
        if(find(r) != find(s)){
            Uniao(r,s,numeroLinhas,tmp);
        }
        tmp = tmp->prox;
    }
}

void PrintMST(int numeroLinha){
    a * tmp = inicio->prox;
    while(tmp != NULL){
        if(tmp->mst == true){
            printf("chave = %d - ligado = %d  peso = %f\n",tmp->chave,tmp->ligado,tmp->peso);
        }
        tmp = tmp->prox;
    }
}

void PrintaArr(int numeroLinhas){
    for (int i = 0;i<numeroLinhas;i++){
        printf("arr[%d] = %d\n",i,arr[i]);
    }
}




///////////////////////////////////////////////// TEST NUMBER 2

void initialize2(int numeroLinhas){
    chief = malloc(numeroLinhas * sizeof(int));
    for(int i = 0 ; i < numeroLinhas;i++){
        chief[i] = i;
    }
}

int find2(int chave){
    while(chief[chave] != chave){
        chave = chief[chave];
    }
    return chave;
}

void Uniao2(int r, int s){
    chief[r] = s;
}

void MST2(int numeroLinhas){
    a * tmp = inicio->prox;
    int r,s,count=0;
    initialize2(numeroLinhas);
    while(tmp != NULL){
        r = tmp->chave;
        s = tmp->ligado;
        if(find2(r) != find2(s)){
            tmp->mst = true;
            Uniao2(r,s);
        }
        tmp = tmp->prox;
    }
}

void PrintMST2(int numeroLinha){
    a * tmp = inicio->prox;
    while(tmp != NULL){
        if(tmp->mst == true){
            printf("chave = %d - ligado = %d  peso = %f\n",tmp->chave,tmp->ligado,tmp->peso);
        }
        tmp = tmp->prox;
    }
}