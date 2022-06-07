#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main (void){
    int numerolinhas = 0,z = 0,x = 0,y = 0;
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
            printf("z =   %d   x = %d    y = %d\n",z,x,y);
            matriz[i] = calloc( 2, sizeof( int ));    
            matriz[i][0] = x;
            matriz[i][1] = y;
            i++;
        }
        printf("Numero de linhas = %d\n",numerolinhas);
        double matrizAdjacencia[numerolinhas][numerolinhas];
        for(i = 0; i < numerolinhas; i++){ //está indo até o último
            for(int j = 0; j < numerolinhas;j++){
                matrizAdjacencia[i][j] = sqrt(pow((matriz[i][0] - matriz[j][0]),2) + pow((matriz[i][1] - matriz[j][1]),2)); 
            }
        }
        FILE * arq = fopen("resultado.txt","w");
        for(i = 0; i < numerolinhas; i++){
            fprintf(arq, "\n");
            for(int j = 0; j < numerolinhas; j++){
                fprintf(arq, "%.2lf   ",matrizAdjacencia[i][j]);
            }
        }
        // Lista adjacência
        typedef struct no_{
            int valor1;
            int valor2;

            struct no_ * prox;
        } no;

        no * linha;
        no * ptlinha = malloc(sizeof(no));

        ptlinha->prox = NULL;
        ptlinha->valor1 = 0;
        ptlinha->valor2 = 0;
        linha = ptlinha;

        typedef struct no1_{
            int chave;
            struct no1_ * prox;
            no * iniciolinha;
        } no1;

        no1 * lista;
        no1 * ptlista = malloc(sizeof(no));

        
        ptlista->chave = 0;
        ptlista->prox = NULL;
        lista = ptlista;

        for(i = 0; i < numerolinhas;i++){
            no1 * prov = malloc(sizeof(no));
            prov->chave = i;
            prov->iniciolinha = ptlinha;
            lista->prox = prov;
            lista = prov;
            prov->prox = NULL;   
            for(int j = 0;j < numerolinhas; j++){
                no * tmp = malloc(sizeof(no));
                tmp->valor1 = matriz[j][0];
                tmp->valor2 = matriz[j][1];
                linha->prox = tmp;
                linha = tmp;
                tmp->prox = NULL;
            }
        }
    }


}