#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void populando(double * mat,int numeroLinhas);
void printar(int numeroLinhas);
void ordena();
void criarConjunto(int numerolinhas);

typedef struct no_{
    int chave;
    struct no_ * proxBaixo;
    struct no_ * prox;
} no;


typedef struct a_{
    int chave;
    int ligado;
    float peso;
    struct a_ * prox;
} a;

//Variavel global
int numerolinhas = 0;
int x=1,y=1;

//Iniciando a lista das arestas
a * inicio;
no * inicioLista;
no * topo;

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

        criarConjunto(numerolinhas);

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
        no * tmp3 = inicioLista;
        no * tmp5 = inicioLista;
        no * tmp6 = inicioLista;
        no * antesInicioTmp6 = inicioLista;
        topo = inicioLista;
        a * tmp4 = inicio->prox;

        while(tmp4->prox != NULL){
            if(inicioLista->proxBaixo == NULL){ //TESTADO E FUNCIONANDO!
                
                no * tmp = malloc(sizeof(no));
                no * tmp1 = malloc(sizeof(no));

                topo->proxBaixo = tmp;

                tmp->chave = tmp4->chave;
                tmp->prox = tmp1;
                tmp->proxBaixo = NULL;

                tmp1->chave = tmp4->ligado;
                tmp1->prox = NULL;
                tmp1->proxBaixo = NULL;

                topo = tmp;

                //Testes

                // printf("tmp->chave = %d    tmp1->chave = %d\n\n",tmp->chave,tmp1->chave);
                // no * teste = inicioLista->proxBaixo;
                // printf("inicioLista->proxBaixo = %d\n\n",teste->chave); 
                // no * teste2 = tmp->prox;
                // printf("tmp->prox = %d\n\n",teste2->chave);
                // printf("Entrou no 1 if\n\n");

                // no * testeprint = inicioLista->proxBaixo;
                // while(testeprint != NULL){
                //     printf("chaves = %d\n\n",testeprint->chave);
                //     testeprint = testeprint->prox;
                // }

            }
            else{
                //Vou precisar percorrer tanto para baixo quanto para o lado para procurar os elementos
                no * inicioTmp5;
                no * inicioTmp6;
                int tempo5 = 0;
                int tempo6 = 0;
                while(tmp3 != NULL){  //TESTADO E FUNCIONANDO
                    if(tmp3->prox != NULL){
                        if(x == 1){
                            tmp5 = tmp3;
                            inicioTmp5 = tmp3;
                            while(tmp5 != NULL && tmp5->chave != tmp4->chave){
                                tmp5 = tmp5->prox; // tmp5 procura pela chave
                            }
                            if(tmp5 == NULL){
                                inicioTmp5 = NULL;
                            }
                            tempo5++;
                        }
                        if(y == 1){
                            tmp6 = tmp3;
                            inicioTmp6 = tmp3;
                            while(tmp6 != NULL && tmp6->chave != tmp4->ligado){
                                tmp6 = tmp6->prox;  // tmp6 procura pelo ligado
                            }
                            if(tmp6 == NULL){
                                inicioTmp6 = NULL;
                            }
                            tempo6++;
                        }
                        
                        if(tmp5 != NULL){
                            if(tmp5->chave == tmp4->chave){
                                x = 0;
                            }
                        }
                        if(tmp6 != NULL){
                            if(tmp6->chave == tmp4->ligado){
                                y = 0;
                            }
                        }            
                    }
                    tmp3 = tmp3->proxBaixo;
                } 
                // tmp5 = chave 
                //tmp6 = ligado
                //Caso de nenhum dos dois vértices não existirem ainda, nesse caso eu crio uma subárvore com os 2 vértices
                if(tmp5 == NULL && tmp6 == NULL){
                    printf("Entrou no if tmp5 == NULL && tmp6 == NULL\n");
                    no * tmp = malloc(sizeof(no));
                    no * tmp1 = malloc(sizeof(no));

                    topo->proxBaixo = tmp;

                    tmp->chave = tmp4->chave;
                    tmp->prox = tmp1;
                    tmp->proxBaixo = NULL;

                    tmp1->chave = tmp4->ligado;
                    tmp1->prox = NULL;
                    tmp1->proxBaixo = NULL;

                    topo = tmp;                    
                }
                //Nesse caso tmp5 existe e o tmp6 não, logo eu só adiciono o tmp6 na subárvore de tmp5
                //Caso do ligado não existir
                if(tmp5 != NULL && tmp6 == NULL){
                    printf("Entrou no if tmp5(%d) != NULL && tmp6 == NULL\n",tmp5->chave);
                    no * tmp = malloc(sizeof(no));
                    tmp->prox = NULL;
                    tmp->proxBaixo = NULL;
                    tmp->chave = tmp4->ligado;
                    if(tmp5->prox == NULL){
                        tmp5->prox = tmp;
                    }
                    else{
                        while(tmp5->prox != NULL){
                            tmp5 = tmp5->prox;
                        }
                        tmp5->prox = tmp;
                    }
                }
                //O chave não existe
                //O ligado existe, logo na lista do ligado(tmp6) eu tenho que adicionar o chave(tmp5)
                if(tmp5 == NULL && tmp6 != NULL){
                    printf("Entrou no if tmp5 == NULL && tmp6(%d) != NULL\n",tmp6->chave);
                    no * tmp = malloc(sizeof(no));
                    tmp->prox = NULL;
                    tmp->proxBaixo = NULL;
                    tmp->chave = tmp4->chave;
                    if(tmp6->prox == NULL){
                        tmp6->prox = tmp;
                    }
                    else{
                        while(tmp6->prox != NULL){
                            tmp6 = tmp6->prox;
                        }
                        tmp6->prox = tmp;
                    }
                }
                //Caso os dois existirem, mas preciso testar se estão na mesma árvore ou não

                if(tmp5 != NULL && tmp6 != NULL){
                    printf("Entrou no if tmp5(%d) != NULL && tmp6(%d) != NULL\n",tmp5->chave,tmp6->chave);
                    tmp3 = inicioLista;


                    //Tratar caso de tmp6 vim antes do tmp5, preciso rastrear para ver se é possível, se for, preciso tratar esse caso

                    //Nesse momento vou ter inicioTmp5 apontando para o primeiro vértice da subárvore que contém o tmp5 e 
                    //Nesse momento vou ter inicioTmp6 apontando para o primeiro vértice da subárvore que contém o tmp6
                    //Preciso testar se eles estão na mesma subárvore ou não. 
                    //Se tiverem não posso ligar
                    //Se não estiverem eu posso ligar
                    no * teste = inicioTmp5;
                    while(teste != NULL && teste->chave != tmp6->chave){
                        teste = teste->prox;
                    }
                    if(teste == NULL){ //Quer dizer que NÃO encontrou o elemento na lista, logo temos que fazer a ligação de um com outro
                        //Preciso fazer o tmp5 apontar para o último nó, para fazer a ligação tmp5->prox = tmp6, mas preciso quebrar as ligações de tmp6 com a lista principal

                        printf("tmp5->chave = %d   tmp6->chave = %d\n",tmp5->chave,tmp6->chave);

                        //Testar qual vem primeiro, se é o tmp6 ou tmp5
                        printf("tempo5 = %d\n",tempo5);
                        printf("tempo6 = %d\n",tempo6);

                        

                        //Posicionando antesInicioTmp6 antes do inícioTmp6
                        while(antesInicioTmp6->proxBaixo != inicioTmp6){
                            antesInicioTmp6 = antesInicioTmp6->proxBaixo;
                        } 

                       

                        //Testar se inicioTmp6->proxBaixo é nullo, se for nullo, apontar antesInicioTmp6->proxBaixo = NULL
                        if(inicioTmp6->proxBaixo == NULL){
                            antesInicioTmp6->proxBaixo = NULL;
                        }
                        else{
                            antesInicioTmp6->proxBaixo = inicioTmp6->proxBaixo;
                            inicioTmp6->proxBaixo = NULL;
                        }

                        //Quer dizer que o tmp5 já está apontando para o último nó
                        if(tmp5->prox == NULL){
                            tmp5->prox = inicioTmp6;
                        }
                        else{
                            while(tmp5->prox != NULL){
                                tmp5 = tmp5->prox;
                            }
                            tmp5->prox = inicioTmp6;
                        }
                    } 
                }

                count++;
                //printf("count = %d\n",count);
            }
            //Reiniciando as variáveis e ponteiros
            tmp3 = inicioLista;
            x = 1;
            y = 1;
            antesInicioTmp6 = NULL;
            tmp5 = NULL;
            tmp6 = NULL;
            
            
            
            tmp4 = tmp4->prox;
        }
        printf("ta quebrando");
        no * printer = inicioLista->proxBaixo;
        printer = printer->proxBaixo;
        while(printer->prox != NULL){
            printf("vertice = %d\n",printer->chave);
            printer = printer->prox;
        }
        // printf("ta quebrando");
    }
}

void criarConjunto(int numerolinhas){
    //Iniciando os valores do inicial
    inicioLista = malloc(sizeof(no));
    inicioLista->chave = 0;
    inicioLista->prox = NULL;
    inicioLista->proxBaixo = NULL;

    // for(int i = 0;i<numerolinhas;i++){
    //     no * tmp = malloc(sizeof(no));
    //     tmp->chave = i;
    //     tmp->prox = NULL;
    //     topo->proxBaixo = tmp;
    //     topo = tmp;
    // }
    
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
