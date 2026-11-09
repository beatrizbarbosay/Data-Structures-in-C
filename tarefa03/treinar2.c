//inverter a posição dos elementos de um vetor com recursão

#include<stdio.h>
#include<stdlib.h>

void imprimir(int v[], int tam){ //de forma recursiva
    if(tam ==1){
    printf("%d ", v[tam-1]);        
    }else{
        imprimir(v, tam-1);
        printf("%d ", v[tam-1]);
    }
}

int main(void){
    int vetor[10] = {11,258,13,445,58,67,700,8,9,10};
    imprimir(vetor, 10);

    return 0;
}