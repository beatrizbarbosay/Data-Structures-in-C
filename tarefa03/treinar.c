#include <stdio.h>
#include <stdlib.h>
//exemplo: calcular um fatorial

int fatorial(int numero){
    int resultado;
    if(numero==0){
        resultado=1;
    }else{
        resultado = numero*fatorial(numero-1);
    }
    return resultado;
}
int main(void){
    int numero=0;
    int resultado=0;

    scanf("%d", &numero);
    resultado= fatorial(numero);

    printf("%d", resultado);


    return 0;
}