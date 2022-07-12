#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
    int chave;
    int ligado;
    int peso;
} Aresta;

Aresta * arestas;



int main (void){
    int ver = 0,lig = 0,pe = 0;
    char *line_buf = NULL;
    size_t line_buf_size = 0;

    int vertices,numeroLinhas = 0,i=0;

    FILE *p;
    p = fopen("n500.txt","r");
    if(p == NULL){
        printf("ERRO! O arquivo nao foi aberto!\n");
        exit(100);
    }else 
    {
        //Criando a quantidade certa de elementos no vetor de structs
        while(getline(&line_buf, &line_buf_size, p) > 0){
            arestas = malloc(sizeof(Aresta));
            //numeroLinhas++;
        }
        //printf("numeroLinhas = %d\n",numeroLinhas);
        rewind(p);
        //Lendo a primeira linha
        fscanf(p,"%d",&vertices);
        printf("vertices = %d\n\n",vertices);

        while (!feof(p)){
            numeroLinhas++;
            fscanf(p,"%d %d %d",&ver,&lig,&pe);
            printf("vertice = %d  ligado %d  peso = %d\n",ver,lig,pe);
            arestas[i].chave = ver;
            arestas[i].ligado = lig;
            arestas[i].peso = pe;
            i++;
        }
        printf("numeroLinhas = %d\n",numeroLinhas);
 
    }
}
