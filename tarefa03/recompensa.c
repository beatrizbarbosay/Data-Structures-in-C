#include <stdio.h>
#include <math.h>


double recompensa(int i, int vezes, int distancia){
    if(distancia==0){ //quando chegar na maria, finaliza a funcao para a possibilidade atual
        return 1;
    }
    if(i==vezes){ //quando ja tiver tentado a quantidade maxima de vezes, termina a funcao
        return 0;
    }
    double probabilidadetotal=0.0; //variavel para armazenar a probabilidade de todas as jogadas
    for(int dado=1; dado<7; dado++){ //passa pelos numeros possiveis de um dado
        if(dado<=distancia){
            double probabilidadeatual = recompensa(i+1, vezes, distancia - dado)/6; //chama a funcao recursiva para calcular todas as possibilidades
            probabilidadetotal+=probabilidadeatual; //faz a soma de todas probabilidades
        }
    }
    return probabilidadetotal;
}

int main(void){
    int vezes=0;
    int distancia=0;
    int i=0; //variavel para simular as jogadas de dado
    scanf("%d %d", &vezes, &distancia);

    double probabilidade=recompensa(i, vezes, distancia);
    printf("%.3f\n", probabilidade);


    return 0;
}