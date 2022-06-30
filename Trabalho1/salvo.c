        // // Lógica de juntar os conjuntos
        no * tmp3 = inicioLista->prox;
        no * tmp5 = inicioLista->prox;
        no * tmp6 = inicioLista->prox;
        no * tmp7 = inicioLista->prox;
        no * antecessor = inicioLista->prox;
        a * tmp4 = inicio->prox;
        while(tmp4->prox != NULL){
            tmp3 = inicioLista->prox;
            tmp5 = inicioLista->prox;
            antecessor = inicioLista->prox;;
            //Vendo se tmp3(chave) está na lista principal
            while(tmp3->chave != tmp4->chave && tmp3 != NULL){
                tmp3 = tmp3->proxBaixo;
            }
            //Vendo se tmp5(ligado) está na lista principal 
            while(tmp5->chave != tmp4->ligado && tmp5 != NULL){
                tmp5 = tmp5->proxBaixo;
            }

            //Ambos estão na lista principal
            if(tmp3 != NULL && tmp5 != NULL){
                //Posicionando o antecessor antes do vértice LIGADO
                while(antecessor->proxBaixo != tmp5){
                    antecessor = antecessor->proxBaixo;
                }
                antecessor->proxBaixo = tmp5->proxBaixo;
                tmp5->proxBaixo = NULL;
                tmp3->prox = tmp5;
            }
            //tmp3 não está na lista principal, ele já está na direita de algum outro vértice
            //tmp5 ainda está na lista principal, logo não está na direita de nenhum outro vértice
            if(tmp3 == NULL && tmp5 != NULL){
                //Preciso localizar o tmp3
                while(tmp6->chave != tmp4->chave){
                    if(tmp3->prox != NULL){
                        tmp7 = tmp3;
                        tmp6 = tmp3;
                        //Vai sair desse while com tmp6 apontando para nullo ou se encontrar a chave nessa lista
                        while(tmp6 != NULL && tmp6->chave != tmp4->chave){
                            tmp6 = tmp6->prox;
                        }
                        while(tmp7 != NULL && tmp7->chave != tmp4->ligado){
                            tmp7 = tmp7->prox;
                        }
                        if()
                    }
                    tmp3 = tmp3->proxBaixo;
                }
            }


        }