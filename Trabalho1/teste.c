#include <stdio.h>
#include <stdlib.h>

int main (void){
    int *vec,i;
    for(i = 0; i < 5;i++){
        vec = malloc(sizeof(int));
    }
    printf("passou daqui pelko menos!\n");
    for(i = 0; i < 5;i++){
        vec[i] = i;
    }
    printf("passou\n");
    for(i = 0; i < 5;i++){
        printf("vec[%d] = %d\n",i,vec[i]);
    }
}