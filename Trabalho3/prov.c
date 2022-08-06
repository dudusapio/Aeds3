void maiorSubGrafoInduzido(int numerolinhas){
    maiorSubInduz = malloc(4 * sizeof(Aresta));

    int grau[2][5];
    for(int i = 0; i < 2;i++){
        for(int j = 0; j < 5;j++){
            grau[i][j] = 999999;
        }
    }

    maiorSubInduz[0] = AGM[0];

    grau[0][0] = AGM[0].chave;
    grau[0][1] = AGM[0].ligado;
    grau[1][0] = 1;
    grau[1][1] = 1;

    for(int i = 1; i < numerolinhas - 1;i++){
        if(AGM[i].chave == grau[0][0] || AGM[i].chave == grau[0][1]){

        }
        if(AGM[i].ligado ==)
    }
}