#include <stdio.h>

int main () {
    int quantidade;
    scanf("%d", &quantidade);
    int lista[1000]; //cria uma lista com o tamanho limite

    int i = 0;
    while(i < quantidade && scanf("%d", &lista[i]) == 1) i++; // coloca o scanf em elementos da lista

    for (i=1; i<quantidade; i++) {
        lista[i] = lista[i] + lista [i-1];
    }
    int listainvertida[1000];
    for (i=0; i<quantidade; i++) {

        listainvertida[(quantidade-1)- i] = lista[i];
    }
    for (i=0; i<quantidade; i++){
        printf("%d ", listainvertida[i]);

    }



    return 0;
}