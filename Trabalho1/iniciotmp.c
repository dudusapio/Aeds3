                    while(tmp3 != NULL){
                        if(tmp3->prox != NULL){
                            inicioTmp5 = tmp3;
                            inicioTmp6 = tmp3;
                            tmp5 = tmp3;
                            tmp6 = tmp3;
                            while(tmp5 != NULL && tmp5->chave != tmp4->chave){
                                tmp5 = tmp5->prox;
                            }
                            if(tmp5 == NULL){
                                inicioTmp5 = NULL;
                            }
                            while(tmp6 != NULL && tmp6->chave != tmp4->ligado){
                                tmp6 = tmp6->prox;
                            }
                            if(tmp6 == NULL){
                                inicioTmp6 = NULL;
                            }
                        }
                        tmp3 = tmp3->proxBaixo;
                    }